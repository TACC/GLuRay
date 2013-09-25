#!/usr/bin/perl -w
#
# Generate a declarations and wrapper functions using the Sample
# Implementation spec files.
#
# Copyright (C) 2000-2002 Marcelo E. Magallon <mem@users.sf.net>
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; either version 2 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License along with
# this program; see the file COPYING.  If not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

use strict;
use warnings;
use File::Basename qw(dirname);

use constant DOWARN => 1;

BEGIN { $SIG{'__WARN__'} = sub { warn @_ if DOWARN } }

sub debug {
    print STDERR map { "D: " . $_ . "\n" } @_;
}

do {
    my $fh = select;
    foreach (*STDOUT{IO}, *STDERR{IO}) {
        select $_;
        $| = 1;
    }
    select $fh;
};

my @maps = qw(
    specs/gl.tm
    specs/glx.tm
);
my %enumdata = (
    "specs/enum.spec" => "GL",
    "specs/enumext.spec" => "GL",
);
my %specdata = (
    "specs/gl.spec" => "gl",
    "specs/glx.spec" => "glX"
);
my %format_table = (
    "GLboolean"   => "%u",  # unsigned char, argument promotion
    "GLbyte"      => "%d",  # signed char, argument promotion
    "GLclampd"    => "%g",  # double
    "GLclampf"    => "%g",  # float, argument promotion
    "GLdouble"    => "%g",  # double
    "GLfloat"     => "%g",  # float, argument promotion
    "GLint"       => "%d",  # int
    "GLshort"     => "%d",  # short int, argument promotion
    "GLsizei"     => "%d",  # int
    "GLubyte"     => "%u",  # unsigned char, argument promotion
    "GLuint"      => "%u",  # unsigned int
    "GLushort"    => "%u",  # unsigned short int, argument promotion

    # X stuff

    "Bool"        => "%d",  # int
    "Font"        => "%ld", # long int
    "Pixmap"      => "%ld", # long int
    "Window"      => "%ld", # long int

    # GLX stuff

    "GLXFBConfig" => "%p",  # pointer to opaque struct
    "GLXFBConfigSGIX" => "%p",  # pointer to opaque struct
    "GLXPixmap"   => "%ld", # long int
    "GLXPbuffer"  => "%ld", # long int
    "GLXDrawable" => "%ld", # long int
    "GLXContext"  => "%p",  # pointer to opaque struct

    "unsigned long" => "%lu",   # unsigned long
);

my %typemap;

# Parse one typemap adding entries to the given typemap

sub parseTypeMap($\%)
{
    my ($filename, $typemap) = @_;

    open TM, "<$filename"
        or die "Can't open $filename $!\n";

    while (<TM>) {
        chomp;
        my ($name, $type) = (split /,\s*/)[0,3];
        $typemap->{$name} = $type;
    }

    close TM;
}

# parseEnum: parse one enum file, adding the result to the given hash.

# XXX: HACK!
my @enums;
sub parseEnum($$\%) {
    (my $file = shift) or warn "no filename", return;
    my ($prefix, $enum) = @_;
    my $e;

    open ENUM, "<$file"
        or die "Can't open $file: $!\n";

    while (<ENUM>) {
        chomp;
        # throw away comments (# on the first column) and emtpy lines
        next if /^(?:#|\s*$)/;
        if (/^(\S+) (define|enum):/o) {
            $e = ($2 eq "enum")?$1:"";
            push @enums, $e;
        } elsif ($e) {
            if (/^\t(\S+)\t+=\s*(\w+)(:?\s+#\s+(\d+)\s+(\w+))?/o) {
                # name and value pairs
                $enum->{$e}{"${prefix}_$1"} = $2;
            } elsif (/^\tuse\s+(\S+)\s+(\S+)/o) {
                # make a reference, the enum might not be in the table yet
                $enum->{$e}{"${prefix}_$2"} = \$enum->{$1}{"${prefix}_$2"};
            }
        }
    }

    close ENUM;
}

# parseSpec: parse one spec file

sub parseSpec($$\%) {
    my ($file, $prefix, $hooks) = @_;
    my $function = {};
    my @functions;

    open REG, "<$file"
        or die "Can't open $file: $!\n";

    while (<REG>) {
        chomp;
        s/#.*//;                        # throw comments away
        next if /^\S+:/;                # Not interested in the header
        if (/^\s*$/) {                  # empty lines delimit definitions
            $function = {};
            $function->{param}{types} = {}; # Need to initialize this one
        } elsif (/^(\w+)\((\w+(?:,\s*\w+)*|)\)/) { # a function definition
            $function->{name} = $prefix.$1;
            $function->{param}{names} = [split /,\s*/, $2];
            foreach (qw(prehook posthook)) {
                $function->{$_} = $hooks->{$function->{name}}{$_}
                    if exists $hooks->{$function->{name}}{$_};
            }
            push @functions, $function;
        } elsif (/^\treturn\s+(\w+)/) { # the return type
            $function->{return} = $1;
        } elsif (my ($n, $t, $p, $s) =
            /^\tparam\s+             # a parameter definition
             (\w+)\s+                # 1: parameter name
             (\w+)\s+                # 2: parameter type
             (in|out)\s+             # 3: input or output
             (array|value|reference) # 4: storage class
            /gox) {
# if ($s eq "array"):
#     /\G\s+\[(.+)\](?:\s+retained)/
#         $1 can be:
#             constant size ~ \d+
#             variable size ~ parameter name
#             computed size ~ COMPSIZE(.*)
            my ($attr, $qual) = ("", "");
            $attr = "const " if ($p eq "in" && $s =~ /array|reference/);
            $qual = " *"
                if (($p eq "out" && $t !~ /Pointer$/) ||
                    $s =~ /array|reference/);
            $function->{param}{types}{$n} = {
                type => $t, attr => $attr, qual => $qual
            };
        } else {
            #warn "This line was not understood: '$_'\n"
        }
    }

    close REG;

    return @functions;
}

# parse the given hookfile

sub parseHook($$) {
    my ($hookfile, $prefix) = @_;
    my ($func, $section, %hooks);

    open HOOK, "<$hookfile";
    while (<HOOK>) {
        chomp;
        if (/^\s*$/) {
            undef $func;
            undef $section;
        } elsif (/^(\w+)$/) {
            $func = $prefix.$1;
        } elsif ($func) {
            if (/^\t(\w+):/) {
                $section = $1;
                $hooks{$func}{$section} = ();
            } elsif (/^\t\t(.+)/) {
                push @{$hooks{$func}{$section}}, "$1\n";
            }
        }
    }
    close HOOK;

    return %hooks;
}

# Load all the typemaps passed as arguments

sub loadTypeMaps(@) {
    my %typemap;

    foreach my $typemap (@_) { parseTypeMap($typemap, %typemap) }

    # Have to special case this, it isn't defined
    $typemap{GLstring} = $typemap{String} = "const GLubyte *";
    $typemap{GLXstring} = "const char *";
    # And this is fscked
    $typemap{void} = "void";

    return %typemap;
}

# Load all the enums passed as arguments

sub loadEnums(\%) {
    my $p = shift;
    my %enums;
    my %all;

    parseEnum $_, $p->{$_}, %enums for (keys %{$p});

    # flatten references inside the enum list and remove undefined items
    while (my ($name, $enum) = each %enums) {
        while (my ($k, $v) = each %{$enum}) {
            $enum->{$k} = $v = $$v while ref $v;
            if (defined $v) {
                $all{$k} = \$enum->{$k};
            } else {
                warn "Missing definition for $k referenced by $name\n";
                delete $enum->{$k};
            }
        }
    }

    # If the value matches GL_\w+, then it's a reference to that constant
    foreach (values %all) {
        $$_ = ${$all{$$_}} if $$_ =~ /^GL_\w+$/;
    }

    # print out individual enum structs
    foreach my $name (sort keys %enums) {
        my $enum = $enums{$name};
        print
            "static enum_index_st _${name}_enum_[] = {\n",
            join(",\n",
                map { "    { $enum->{$_}, \"$_\" }" }
                sort { hex $enum->{$a} <=> hex $enum->{$b} }
                keys %{$enum}),
            "\n};\n";
    }

    # and print a big one with all the enums
    print
        "static enum_index_st all_enums[] = {\n",
        join(",\n",
            map { "    { ${$all{$_}}, \"$_\" }" }
            sort { hex ${$all{$a}} <=> hex ${$all{$b}} }
            keys %all),
        "\n};\n\n";
}

sub block(@) {
    map { " "x4 . $_ if $_ } @_
}

sub formatArgs($\@\%) {
    my ($i, $pn, $pt) = @_;
    my @format = ();
    my @args = ();
    foreach (@$pn) {
        if ($pt->{$_}{qual} ne "") {
            push @format, $_;
        } elsif (exists $format_table{$typemap{$pt->{$_}{type}}}) {
            push @format, $format_table{$typemap{$pt->{$_}{type}}};
            push @args, $_;
        } elsif ($typemap{$pt->{$_}{type}} eq "GLenum") {
            my $enum = $pt->{$_}{type};
            push @format, "%s";
            # XXX: Hideous
            if (scalar(grep /^$enum$/, @enums))
            {
                $enum = "_${enum}_enum_";
                push @args, "gl_lookup_enum_by_nr($_, $enum, tableSize($enum))";
            } else {
                push @args, "gl_lookup_enum_by_nr($_, all_enums, tableSize(all_enums))";
            }
        } elsif ($typemap{$pt->{$_}{type}} eq "GLbitfield") {
            push @format, "%s";
            push @args, "gl_lookup_bitfields_by_nr($_)";
        } elsif ($typemap{$pt->{$_}{type}} =~ /\*$/) {
            # FIXME -> pointers should be handled in a diferent way
            push @format, "%p";
            push @args, $_;
        } else {
            push @format, $_;
            warn "I don't know how to handle type $typemap{$pt->{$_}{type}} ($_)\n";
        }
    }
    return
        "sprintf(args, " .
        join(",\n\t", '"(' . join(", ", @format) . ');\n"', @args) .
        ");\n";
}

sub printFunctionDecl($) {
    my $f = shift;
    my ($name, $return) = ($f->{name}, $typemap{$f->{return}});

    my %pt = %{$f->{param}{types}};
    my @pn = @{$f->{param}{names}};

    my $args = join ", ",
        map {
            $pt{$_}{attr} . $typemap{$pt{$_}{type}} . $pt{$_}{qual} . " $_"
        } @pn;

    print
        "static $return (*next_$name)($args) = NULL;\n\n",
}

sub printFunctionDef($$) {
    my ($f, $i) = @_;

    my ($name, $return) = ($f->{name}, $typemap{$f->{return}});
    my $isvoid = $return eq "void";

    my %pt = %{$f->{param}{types}};
    my @pn = @{$f->{param}{names}};

    my $prehook = exists $f->{prehook} ? $f->{prehook} : [];
    my $posthook = exists $f->{posthook} ? $f->{posthook} : [];

    my $args = join ", ",
        map {
            $pt{$_}{attr} . $typemap{$pt{$_}{type}} . $pt{$_}{qual} . " $_"
        } @pn;

    print
        # The function definition
        "$return $name($args) {\n",
        block(
            # Declare variable to hold the return value if needed
            !$isvoid ?  "$return result;\n" : "",

            @{$prehook},

            # Print a call to print a call to the function
            formatArgs($i, @pn, %pt),

            # Call the real function, saving the result if there's one
            (!$isvoid ?  "result = " : "") .
            "next_$name(" . join(", ", @pn) . ");",

            @{$posthook},

            # check for errors
            "__sgPrintError();\n ",

            "#if OUTPUT_MSGS\n dt->read_flag_write_msg(dt->format_function_call($i, args));\n#endif\n",

            !$isvoid ? "return result;\n" : ""
        ),
        "}\n\n";
}

sub loadRegistry(\%) {
    my $files = shift;
    my @functions;

    foreach my $file (keys %{$files}) {
        #my ($func, $return, @pn, %pt);
        my $prefix = $files->{$file};
        my $hook = dirname($file) . "/$prefix.hook";
        my %hooks;
        my %function;

        if (-e $hook) {
            %hooks = parseHook($hook, $prefix);
        } else {
            warn "$hook doesn't exist\n";
        }

        foreach my $func (keys %hooks) {
            print join("\n", @{$hooks{$func}{global}}), "\n"
                if (defined $hooks{$func}{global});
        }

        push @functions, parseSpec($file, $prefix, %hooks);
    }

    @functions = sort { $a->{name} cmp $b->{name} } @functions;

    printFunctionDecl($_) for @functions;
    print
        "static symbol_info_st symbol_info[] = {\n",
        (map { '    {(void(*))&next_'.$_->{name}.', "'.$_->{name}."\"},\n" }
            @functions),
        "    {NULL, NULL}\n",
        "};\n\n";

    for(my $i=0; $i < scalar(@functions); ++$i) {
        printFunctionDef($functions[$i], $i);
    }
}

%typemap = loadTypeMaps(@maps);
loadEnums(%enumdata);
loadRegistry(%specdata);
