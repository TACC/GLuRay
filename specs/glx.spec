# License Applicability. Except to the extent portions of this file are
# made subject to an alternative license as permitted in the SGI Free
# Software License B, Version 1.1 (the "License"), the contents of this
# file are subject only to the provisions of the License. You may not use
# this file except in compliance with the License. You may obtain a copy
# of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
# Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
#
# http://oss.sgi.com/projects/FreeB
#
# Note that, as provided in the License, the Software is distributed on an
# "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
# DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
# CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
# PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
#
# Original Code. The Original Code is: OpenGL Sample Implementation,
# Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
# Inc. The Original Code is Copyright (c) 1991-2002 Silicon Graphics, Inc.
# Copyright in any portions created by third parties is as indicated
# elsewhere herein. All Rights Reserved.
#
# Additional Notice Provisions: This software was created using the
# OpenGL(R) version 1.2.1 Sample Implementation published by SGI, but has
# not been independently verified as being compliant with the OpenGL(R)
# version 1.2.1 Specification.

required-props:
param:		retval retained
dlflags:	notlistable handcode nop
glxflags:	client-handcode server-handcode
glxvendorglx:	*
vectorequiv:	*
category:	pixel-rw bgn-end display-list drawing drawing-control feedback framebuf misc modeling pixel-op pixel-rw state-req xform glx glxopcode
glxopcode:		*

###############################################################################
#
# GLX1.0 commands
#
###############################################################################
Render()
	return		 void
	category	 glx
	dlflags		 notlistable
	glxflags	 client-handcode server-handcode
	glxopcode	 1


RenderLarge()
	return		 void
	category	 glx
	dlflags		 notlistable
	glxflags	 client-handcode server-handcode
	glxopcode	 2


CreateContext(dpy, visual, share_list, direct)
	return		 GLXContext
	param		 dpy		DisplayPointer in value
	param		 visual		XVisualInfoPointer in value
	param		 share_list	GLXContext in value
	param		 direct		Bool in value
	glxflags	 client-handcode server-handcode
	category	 glx
	dlflags		 notlistable
	glxopcode	 3


DestroyContext(dpy, ctx)
	return		 void
	param		 dpy		DisplayPointer in value
	param		 ctx		GLXContext in value
	glxflags	 client-handcode server-handcode
	category	 glx
	dlflags		 notlistable
	glxopcode	 4


MakeCurrent(dpy, drawable, ctx)
	return		 Bool
	param		 dpy		DisplayPointer in value
	param		 drawable	GLXDrawable in value
	param		 ctx		GLXContext in value
	category	 glx
	dlflags		 notlistable
	glxopcode	 5


IsDirect(dpy, ctx)
	return		 Bool
	param		 dpy		DisplayPointer in value
	param		 ctx		GLXContext in value
	glxflags	 client-handcode server-handcode
	category	 glx
	dlflags		 notlistable
	glxopcode	 6


QueryVersion(dpy, major, minor)
	return		 Bool
	param		 dpy		DisplayPointer in value
	param		 major		Int32 out reference
	param		 minor		Int32 out reference
	category	 glx
	dlflags		 notlistable
	glxflags	 client-handcode server-handcode
	glxopcode	 7


WaitGL()
	return		 void
	category	 glx
	dlflags		 notlistable
	glxflags	 client-handcode server-handcode
	glxopcode	 8


WaitX()
	return		 void
	category	 glx
	dlflags		 notlistable
	glxflags	 client-handcode server-handcode
	glxopcode	 9


CopyContext(dpy, source, dest, mask)
	return		 void
	param		 dpy		DisplayPointer in value
	param		 source		GLXContext in value
	param		 dest		GLXContext in value
	param		 mask		ulong in value
	category	 glx
	dlflags		 notlistable
	glxflags	 client-handcode server-handcode
	glxopcode	 10


SwapBuffers(dpy, drawable)
	return		 void
	param		 dpy		DisplayPointer in value
	param		 drawable	GLXDrawable in value
	category	 glx
	dlflags		 notlistable
	glxflags	 client-handcode server-handcode
	glxopcode	 11


UseXFont(font, first, count, list_base)
	return		 void
	param		 font		Font in value
	param		 first		Int32 in value
	param		 count		Int32 in value
	param		 list_base	Int32 in value
	category	 glx
	dlflags		 notlistable
	glxflags	 client-handcode server-handcode
	glxopcode	 12


CreateGLXPixmap(dpy, visual, pixmap)
	return		 GLXPixmap
	param		 dpy		DisplayPointer in value
	param		 visual		XVisualInfoPointer in value
	param		 pixmap		Pixmap in value
	category	 glx
	dlflags		 notlistable
	glxflags	 client-handcode server-handcode
	glxopcode	 13

GetVisualConfigs()
	return		 void
	category	 glx
	dlflags		 notlistable
	glxflags	 client-handcode server-handcode
	glxopcode	 14


DestroyGLXPixmap(dpy, pixmap)
	return		 void
	param		 dpy		DisplayPointer in value
	param		 pixmap		GLXPixmap in value
	glxflags	 client-handcode
	category	 glx
	dlflags		 notlistable
	glxopcode	 15


VendorPrivate()
	return		void
	glxflags	client-handcode server-handcode
	category	glx
	dlflags		notlistable
	glxopcode	16


VendorPrivateWithReply()
	return		void
	glxflags	client-handcode server-handcode
	category	glx
	dlflags		notlistable
	glxopcode	17

###############################################################################
#
# GLX1.1 commands
#
###############################################################################
QueryExtensionsString(dpy, screen)
	return		GLXstring
	param		dpy		DisplayPointer in value
	param		screen		Int32 in value
	glxflags	client-handcode server-handcode
	category	glx
	dlflags		notlistable
	glxopcode	18

QueryServerString(dpy, screen, name)
	return		GLXstring
	param		dpy		DisplayPointer in value
	param		screen		Int32 in value
	param		name		Int32 in value
	glxflags	client-handcode server-handcode
	category	glx
	dlflags		notlistable
	glxopcode	19

ClientInfo()
	return		void
	glxflags	client-handcode server-handcode
	category	glx
	dlflags		notlistable
	glxopcode	20

###############################################################################
#
# GLX1.3 commands
#
###############################################################################
GetFBConfigs(dpy, screen, nelements)
	return		GLXFBConfigPointer
	param		dpy		DisplayPointer in value
	param		screen		Int32 in value
	param		nelements	Int32 out reference
	category	glx
	dlflags		notlistable
	glxflags	client-handcode server-handcode
	glxopcode	21

CreatePixmap(dpy, config, pixmap, attriblist)
	return		GLXPixmap
	param		dpy		DisplayPointer in value
	param		config		GLXFBConfig in value
	param		pixmap		Pixmap in value
	param		attriblist	Int32 in array
	dlflags		notlistable
	glxflags	client-handcode server-handcode
	category	glx
	glxopcode	22

DestroyPixmap(dpy, pixmap)
	return		void
	param		dpy		DisplayPointer in value
	param		pixmap		Pixmap in value
	dlflags		notlistable
	glxflags	client-handcode server-handcode
	category	glx
	glxopcode	23

CreateNewContext(dpy, config, render_type, share_list, direct)
	return		GLXContext
	param		dpy		DisplayPointer in value
	param		config		GLXFBConfig in value
	param		render_type	Int32 in value
	param		share_list	GLXContext in value
	param		direct		Bool in value
	dlflags		notlistable
	glxflags	client-handcode server-handcode
	category	glx
	glxopcode	24

QueryContext(dpy, context, attribute, value)
	return		Int32
	param		dpy		DisplayPointer in value
	param		context		GLXContext in value
	param		attribute	Int32 in value
	param		value		Int32 out reference
	dlflags		notlistable
	glxflags	client-handcode server-handcode
	category	glx
	glxopcode	25

MakeContextCurrent(dpy, drawdrawable, readdrawable, context)
	return		Bool
	param		dpy		DisplayPointer in value
	param		drawdrawable	GLXDrawable in value
	param		readdrawable	GLXDrawable in value
	param		context		GLXContext in value
	dlflags		notlistable
	glxflags	client-handcode server-handcode
	category	glx
	glxopcode	26

CreatePbuffer(dpy, config, attrib_list)
	return		GLXPbuffer
	param		dpy		DisplayPointer in value
	param		config		GLXFBConfig in value
	param		attrib_list	Int32 in array
	dlflags		notlistable
	glxflags	client-handcode server-handcode
	category	glx
	glxopcode	27

DestroyPbuffer(dpy, pbuffer)
	return		void
	param		dpy		DisplayPointer in value
	param		pbuffer		GLXPbuffer in value
	dlflags		notlistable
	glxflags	client-handcode
	category	glx
	glxopcode	28

GetDrawableAttributes(drawable)
	return		void
	param		drawable	Int32 in value
	dlflags		notlistable
	glxflags	client-handcode server-handcode
	category	glx
	glxopcode	29

ChangeDrawableAttributes(drawable)
	return		void
	param		drawable	Int32 in value
	dlflags		notlistable
	glxflags	client-handcode server-handcode
	category	glx
	glxopcode	30

CreateWindow(dpy, config, window, attrib_list)
	return		GLXWindow
	param		dpy		DisplayPointer in value
	param		config		GLXFBConfig in value
	param		window		Window in value
	param		attrib_list	Int32 in array
	dlflags		notlistable
	glxflags	client-handcode server-handcode
	category	glx
	glxopcode	31

DestroyWindow(dpy, window)
	return		void
	param		dpy		DisplayPointer in value
	param		window		Window in value
	dlflags		notlistable
	glxflags	client-handcode server-handcode
	category	glx
	glxopcode	32

ChooseVisual(dpy, screen, attriblist)
	return		XVisualInfoPointer
	param		dpy		DisplayPointer in value
	param		screen		Int32 in value
	param		attriblist	Int32 out array
	category	glx

###############################################################################
#
# IRIX5.3 extension commands
#
###############################################################################

###############################################################################
#
# SGI_swap_control extension commands
#
###############################################################################
SwapIntervalSGI()
	return		void
	glxflags	client-handcode server-handcode
	category	glx
	dlflags		notlistable
	glxvendorglx	65536

###############################################################################
#
# IRIX5.3-PATCH154 extension commands
#
###############################################################################

###############################################################################
#
# SGI_make_current_read extension commands
#
###############################################################################
MakeCurrentReadSGI(drawable, readdrawable, context)
	return		void
	param		drawable	Int32 in value
	param		readdrawable	Int32 in value
	param		context		Int32 in value
	glxflags	client-handcode server-handcode
	category	glx
	dlflags		notlistable
	glxvendorglx	65537

###############################################################################
#
# SGIX_video_source extension commands
#
###############################################################################
CreateGLXVideoSourceSGIX(dpy, screen, server, path, class, node)
	return		void
	param		dpy			Int32 in value
	param		screen			Int32 in value
	param		server			Int32 in value
	param		path			Int32 in value
	param		class			Int32 in value
	param		node			Int32 in value
	glxflags	client-handcode server-handcode
	category	glx
	dlflags		notlistable
	glxvendorglx	65538

DestroyGLXVideoSourceSGIX(dpy, glxvideosource)
	return		void
	param		dpy			Int32 in value
	param		glxvideosource		Int32 in value
	glxflags	client-handcode server-handcode
	category	glx
	dlflags		notlistable
	glxvendorglx	65539

###############################################################################
#
# IRIX6.2 extension commands
#
###############################################################################

###############################################################################
#
# EXT_import_context extension commands
#
###############################################################################
QueryContextInfoEXT(dpy, context, attribute, value)
	return		 Int32
	param		dpy		DisplayPointer in value
	param		context		GLXContext in value
	param		attribute	Int32 in value
	param		value		Int32 out reference
	category	 glx
	dlflags		 notlistable
	glxflags	 client-handcode server-handcode
	glxvendorglx	 1024

###############################################################################
#
# SGIX_fbconfig extension commands
#
###############################################################################
# GetFBConfigsSGIX()
# 	return		 void
# 	category	 glx
# 	dlflags		 notlistable
# 	glxflags	 client-handcode server-handcode
# 	glxvendorglx	 65540
# 
# CreateContextWithConfigSGIX(dpy, config, renderType, share_list, allow_direct)
# 	return		 GLXContext
# 	param		 dpy		DisplayPointer in value
# 	param		 config		GLXFBConfigSGIX in value
# 	param		 renderType	Int32 in value
# 	param		 share_list	GLXContext in value
# 	param		 allow_direct	Bool in value
# 	glxflags	 client-handcode server-handcode
# 	category	 glx
# 	dlflags		 notlistable
# 	glxvendorglx	 65541
# 
# CreateGLXPixmapWithConfigSGIX(dpy, config, pixmap, attriblist)
# 	return		GLXPixmap
# 	param		dpy		DisplayPointer in value
# 	param		config		GLXFBConfigSGIX in value
# 	param		pixmap		Pixmap in value
# 	param		attriblist	Int32 in array
# 	category	glx
# 	dlflags		notlistable
# 	glxflags	client-handcode server-handcode
# 	glxvendorglx	65542

###############################################################################
#
# SGIX_pbuffer extension commands
#
###############################################################################

CreateGLXPbufferSGIX(dpy, config, width, height, attriblist)
	return		 GLXPbuffer
	param		 dpy		DisplayPointer in value
	param		 config		GLXFBConfig in value
	param		 width		UInt32 in value
	param		 height		UInt32 in value
	param		 attriblist	Int32 in array
	dlflags		 notlistable
	glxflags	 client-handcode server-handcode
	category	 glx
	glxvendorglx	 65543

DestroyGLXPbufferSGIX(dpy, pbuffer)
	return		 void
	param		 dpy		DisplayPointer in value
	param		 pbuffer	GLXPbuffer in value
	dlflags		 notlistable
	glxflags	 client-handcode
	category	 glx
	glxvendorglx	 65544

ChangeDrawableAttributesSGIX(drawable)
	return		 void
	param		 drawable	Int32 in value
	dlflags		 notlistable
	glxflags	 client-handcode server-handcode
	category	 glx
	glxvendorglx	 65545

GetDrawableAttributesSGIX(drawable)
	return		 void
	param		 drawable	Int32 in value
	dlflags		 notlistable
	glxflags	 client-handcode server-handcode
	category	 glx
	glxvendorglx	 65546

###############################################################################
#
# SGIX_swap_group extension commands
#
###############################################################################

JoinSwapGroupSGIX(dpy, drawable, member)
	return		void
	param		dpy		DisplayPointer in value
	param		drawable	GLXDrawable in value
	param		member		GLXDrawable in value
	glxflags	client-handcode server-handcode
	category	glx
	dlflags		notlistable
	glxvendorglx	65547

###############################################################################
#
# SGIX_swap_barrier extension commands
#
###############################################################################

BindSwapBarrierSGIX(dpy, drawable, barrier)
	return		void
	param		dpy		DisplayPointer in value
	param		drawable	GLXDrawable in value
	param		barrier		Int32 in value
	glxflags	client-handcode server-handcode
	category	glx
	dlflags		notlistable
	glxvendorglx	65548

QueryMaxSwapBarriersSGIX(dpy, screen, max)
	return		Bool
	param		dpy		DisplayPointer in value
	param		screen		Int32 in value
	param		max		Int32 out value
	glxflags	client-handcode server-handcode
	category	glx
	dlflags		notlistable
	glxvendorglx	65549

###############################################################################
#
# SGIX_hyperpipe_group extension commands
#
###############################################################################

QueryHyperpipeNetworkSGIX()
	return		void
	glxflags	client-handcode server-handcode
	category	glx
	dlflags		notlistable
	glxvendorglx	65550

QueryHyperpipeConfigSGIX()
	return		void
	glxflags	client-handcode server-handcode
	category	glx
	dlflags		notlistable
	glxvendorglx	65551

HyperpipeConfigSGIX()
	return		void
	glxflags	client-handcode server-handcode
	category	glx
	dlflags		notlistable
	glxvendorglx	65552

DestroyHyperpipeConfigSGIX()
	return		void
	glxflags	client-handcode server-handcode
	category	glx
	dlflags		notlistable
	glxvendorglx	65553
