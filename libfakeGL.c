/*
 * Wrap OpenGL(TM) library calls with versions that provide debug information
 *
 * Copyright (C) 2000-2002 Marcelo E. Magallon <marcelo.magallon@bigfoot.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * OpenGL(TM) is a trademark of Silicon Graphics, Inc.
 *
 * Modified by Carson brownlee <brownlee@cs.utah.edu>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <assert.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "spyglass.h"
#include "CMakeDefines.h"
//#define OPENGLLIB "/usr/lib/libGL.so.1"

/*
 * The GNU C compiler has this really nice feature: it will call all the
 * functions with attribute constructor before calling main().  This means we
 * can initilize the function table before the program starts
 */

#if defined(__GNUC__)
static void spyglass_init(void) __attribute__ ((__constructor__));
#else
static void spyglass_init(void);
#endif

#if !defined(OPENGLLIB)
  FAIL_MISERABLY
/*#define OPENGLLIB "/usr/lib/nvidia-current/libGL.so.1"
#define OPENGLLIB "/usr/lib64/libGL.so.1"
#define OPENGLLIB "/scratch/01336/carson/VisIt2.4.0/Mesa-7.8.2/lib/libGL.so"
*/
#endif

static int __sgInsideBegin = 0;

#define BUFFER_SIZE 1024

static int flag_fifo, msg_fifo;
static char args[BUFFER_SIZE];
static char msg[BUFFER_SIZE];

static void __sgPrintError();

static char * gl_lookup_bitfields_by_nr(GLbitfield bitfield);
static const char * gl_lookup_enum_by_nr(int nr, enum_index_st * table, size_t size);

typedef char (*read_flag_write_msg_func)(char *);
typedef char* (*format_function_call_func)(int, const char *);
typedef struct {
    read_flag_write_msg_func read_flag_write_msg;
    format_function_call_func format_function_call;
} sg_dispatch_table;

static char read_flag_write_msg_fifo(char *msg);
static char read_flag_write_msg_simple(char *msg);

static char* format_function_call_fifo(int, const char *);
static char* format_function_call_simple(int, const char *);

const sg_dispatch_table *dt = NULL;

static const sg_dispatch_table sg_dispatch_table_fifo = {
    read_flag_write_msg_fifo,
    format_function_call_fifo
};

static const sg_dispatch_table sg_dispatch_table_simple = {
    read_flag_write_msg_simple,
    format_function_call_simple
};

#define tableSize(t) (sizeof(t)/sizeof(*t))

/*
 * Yes, this is ugly.
 */

#include "gl_function_table.c"

static void * open_GL_lib(void);
static void load_library_symbols(void);
#if defined(LINK_ENUMS_HACK)
static void link_enums(void);
#endif
static void init_fifos(void);

static void spyglass_init(void)
{
  /*printf("using gluray\n");*/

    static int done = 0;

    if (!done)
    {
        init_fifos();
        /*printf("load_lib_sym\n");*/
        load_library_symbols();
        /*printf("done load_lib_sym\n");*/
#if defined(LINK_ENUMS_HACK)
        link_enums();
#endif
        done = 1;
    }
    /*printf("done gluray_init\n");*/
}

static void init_fifos(void)
{
    msg_fifo = open(getenv("__SG_FIFO_DATA"), O_WRONLY);
    flag_fifo = open(getenv("__SG_FIFO_CONTROL"), O_RDONLY);

    if (msg_fifo == -1 || flag_fifo == -1)
        if (msg_fifo == -1 && flag_fifo == -1)
            dt = &sg_dispatch_table_simple;
        else {
            fprintf(stderr, "E: Can't open fifos\n");
            exit(1);
        }
    else
        dt = &sg_dispatch_table_fifo;
}

static
char read_flag_write_msg_fifo(char *msg)
{
    char buf[BUFFER_SIZE];
    write(msg_fifo, msg, strlen(msg));
    read(flag_fifo, buf, sizeof(buf));
    return buf[0];
}

static char read_flag_write_msg_simple(char *msg)
{
    fprintf(stderr, msg);
    return (char)0;
}

static char* format_function_call_fifo(int f, const char * args)
{
    sprintf(msg, "%d\n%s", f, args);
    return msg;
}

static char* format_function_call_simple(int f, const char * args)
{
    sprintf(msg, "%s%s", symbol_info[f].name, args);
    return msg;
}

/*
 * Systems without RTLD_NEXT must open the OpenGL library to get the proper
 * symbol table.  Grmpf!
 *
 * There's at least one example case where this breaks: Quake Arena and its
 * kind.  Arena dlopens libGL, which means the only way for this to work is to
 * /be/ libGL (in order for Arena to dlopen it).  Since the idea is not reverse
 * engineering Quake, I think the LD_PRELOAD path is better for now.  /If/ you
 * want to trace Quake, you have to tell it to use this library as libGL and
 * modify this library to dlopen that GL library directly, remove RTLD_NEXT and
 * use the handle returned by dlopen instead.
 */

static void * open_GL_lib(void)
{
#if !defined(RTLD_NEXT) || defined(DLOPEN_GL_LIB)
  /*printf("not using RTLD_NEXT\n");*/
    void * h;
    if (!(h = dlopen(OPENGLLIB, RTLD_NOW | RTLD_LOCAL)))
    {
        fprintf(stderr,
                "Couldn't open OpenGL library %s, aborting\n",
                OPENGLLIB);
        exit(1);
    }
    return h;
#else
    /*printf("using RTLD_NEXT\n");*/
 //   exit(3);
    return RTLD_NEXT;
#endif
}

static void close_GL_lib(void * h)
{
#if !defined(RTLD_NEXT) || defined(DLOPEN_GL_LIB)
    dlclose(h);
#else
    (void)h;
#endif
}

static void load_library_symbols(void)
{
    int i;
    char * msg;
    void * h = open_GL_lib();

    for (i=0; symbol_info[i].doit; ++i)
    {
        *(symbol_info[i].doit) = dlsym(h, symbol_info[i].name);
        if ((msg = dlerror()) != NULL)
        {
            //fprintf(stderr, "dlsym(%s): %s\n", symbol_info[i].name, msg);
        }
    }

    close_GL_lib(h);
}

int cmp_key(const void * a, const void * b)
{
    int k = ((enum_index_st *)a)->n;
    int n = ((enum_index_st *)b)->n;
    return (k < n) ? -1 : ((k == n) ? 0 : 1);
}

#if defined(LINK_ENUMS_HACK)
static void link_enums(void)
{
    int i;

    for (i=0; i < tableSize(all_enums); ++i)
    {
        int j;
        enum_index_st * t = all_enums[i];
        for (j=0; t[j].n != -1; ++j)
        {
            if (!t[j].e)
            {
                enum_index_st * e =
                    bsearch(t + j,
                            all_enum, tableSize(all_enum), sizeof(*all_enum),
                            cmp_key);
                assert(e != NULL);
                t[j].e = e->e;
            }
        }
    }
}
#endif

static char * gl_lookup_bitfields_by_nr(GLbitfield bitfield)
{
    const static struct
    {
        const char *c;
        int v;
    } all_bitvalues[] = {
        { "GL_CURRENT_BIT",             GL_CURRENT_BIT },
        { "GL_POINT_BIT",               GL_POINT_BIT },
        { "GL_LINE_BIT",                GL_LINE_BIT },
        { "GL_POLYGON_BIT",             GL_POLYGON_BIT },
        { "GL_POLYGON_STIPPLE_BIT",     GL_POLYGON_STIPPLE_BIT },
        { "GL_PIXEL_MODE_BIT",          GL_PIXEL_MODE_BIT },
        { "GL_LIGHTING_BIT",            GL_LIGHTING_BIT },
        { "GL_FOG_BIT",                 GL_FOG_BIT },
        { "GL_DEPTH_BUFFER_BIT",        GL_DEPTH_BUFFER_BIT },
        { "GL_ACCUM_BUFFER_BIT",        GL_ACCUM_BUFFER_BIT },
        { "GL_STENCIL_BUFFER_BIT",      GL_STENCIL_BUFFER_BIT },
        { "GL_VIEWPORT_BIT",            GL_VIEWPORT_BIT },
        { "GL_TRANSFORM_BIT",           GL_TRANSFORM_BIT },
        { "GL_ENABLE_BIT",              GL_ENABLE_BIT },
        { "GL_COLOR_BUFFER_BIT",        GL_COLOR_BUFFER_BIT },
        { "GL_HINT_BIT",                GL_HINT_BIT },
        { "GL_EVAL_BIT",                GL_EVAL_BIT },
        { "GL_LIST_BIT",                GL_LIST_BIT },
        { "GL_TEXTURE_BIT",             GL_TEXTURE_BIT },
        { "GL_SCISSOR_BIT",             GL_SCISSOR_BIT },
        { "GL_CLIENT_PIXEL_STORE_BIT",  GL_CLIENT_PIXEL_STORE_BIT },
        { "GL_CLIENT_VERTEX_ARRAY_BIT", GL_CLIENT_VERTEX_ARRAY_BIT }
    };

    if (bitfield == GL_ALL_ATTRIB_BITS)
        return "GL_ALL_ATTRIB_BITS";
#if defined(GL_ALL_CLIENT_ATTRIB_BITS)

    else if (bitfield == GL_ALL_CLIENT_ATTRIB_BITS)
        return "GL_ALL_CLIENT_ATTRIB_BITS";
#endif

    else
    {
        int l;
        static char s[1024];
        char *p = s;
        int len=sizeof(s)-1;
        int i = 0;
        GLbitfield bits = bitfield;
        const int elements = sizeof(all_bitvalues)/sizeof(*all_bitvalues);

        s[0] = 0;

        for(i=0; i < elements && bits && len; ++i)
        {
            if (bits & all_bitvalues[i].v)
            {
                if (strncat(p, all_bitvalues[i].c, len))
                {
                    len -= l = strlen(all_bitvalues[i].c);
                    p += l;
                }
                bits &= ~all_bitvalues[i].v;
                if (bits)
                {
                    if (strncat(p, " | ", len))
                    {
                        len -= 3;
                        p += 3;
                    }
                }
            }
        }

        if (bits)
        {
            snprintf(p, len, "%X", bits);
        }

        return s;
    }
}

static const char * gl_lookup_enum_by_nr(
    int nr, enum_index_st * table, size_t size)
{
    enum_index_st e, *f;

    e.n = nr;
    e.e = NULL;

    if (!(f = bsearch(&e, table, size, sizeof(*table), cmp_key)))
        f = bsearch(&e, all_enums, tableSize(all_enums), sizeof(*all_enums),
                    cmp_key);

    return f ? f->e : NULL;
}

static inline const char * gl_lookup_error_by_nr(int error)
{
    const int size = tableSize(_ErrorCode_enum_);
    return gl_lookup_enum_by_nr(error, _ErrorCode_enum_, size);
}

static void __sgPrintError()
{
    if (!__sgInsideBegin)
    {
        GLenum error;
        while ((error = next_glGetError()) != GL_NO_ERROR)
        {
            const char * errorname = gl_lookup_error_by_nr(error);
            if (errorname)
                sprintf(msg, "Error: %s\n", errorname);
            else
                sprintf(msg, "Error: unkown (%d)\n", error);
            dt->read_flag_write_msg(msg);
        }
    }
    else if (__sgInsideBegin > 1)
    {
        sprintf(msg, "Error: nested glBegin() call.\n");
        dt->read_flag_write_msg(msg);
    }
}

const symbol_info_st * const sgGetSymbolTable()
{
    return symbol_info;
}
