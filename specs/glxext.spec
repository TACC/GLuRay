# glxext.spec file
# DON'T REMOVE PREVIOUS LINE!!! libspec depends on it!
#
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
# Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
# Copyright in any portions created by third parties is as indicated
# elsewhere herein. All Rights Reserved.
#
# Additional Notice Provisions: This software was created using the
# OpenGL(R) version 1.2.1 Sample Implementation published by SGI, but has
# not been independently verified as being compliant with the OpenGL(R)
# version 1.2.1 Specification.

required-props:
param:		retval retained
glxflags:	client-handcode client-intercept server-handcode
glxvendorglx:	*
vectorequiv:	*
category:	VERSION_1_3 VERSION_1_4 ARB_get_proc_address ARB_multisample EXT_import_context SGIX_dmbuffer SGIX_fbconfig SGIX_pbuffer SGIX_swap_barrier SGIX_swap_group SGIX_video_resize SGIX_video_source SGI_cushion SGI_make_current_read SGI_swap_control SGI_video_sync SUN_get_transparent_index MESA_copy_sub_buffer MESA_pixmap_colormap MESA_release_buffers MESA_set_3dfx_mode SGIX_visual_select_group
glxopcode:	*

#
# Boilerplate to define types used by some extensions. This is done
#   up front, since it involves some complexities in protecting
#   the declarations whether or not the -protect flag is given to
#   the generator scripts.
#

passthru: #ifndef GLX_ARB_get_proc_address
passthru: typedef void (*__GLXextFuncPtr)();
passthru: #endif
passthru:
passthru: #ifndef GLX_SGIX_video_source
passthru: typedef XID GLXVideoSourceSGIX;
passthru: #endif
passthru:
passthru: #ifndef GLX_SGIX_fbconfig
passthru: typedef XID GLXFBConfigIDSGIX;
passthru: typedef struct __GLXFBConfigRec *GLXFBConfigSGIX;
passthru: #endif
passthru:
passthru: #ifndef GLX_SGIX_pbuffer
passthru: typedef XID GLXPbufferSGIX;
passthru: typedef struct {
passthru:     int type;
passthru:     unsigned long serial;	  /* # of last request processed by server */
passthru:     Bool send_event;		  /* true if this came for SendEvent request */
passthru:     Display *display;		  /* display the event was read from */
passthru:     GLXDrawable drawable;	  /* i.d. of Drawable */
passthru:     int event_type;		  /* GLX_DAMAGED_SGIX or GLX_SAVED_SGIX */
passthru:     int draw_type;		  /* GLX_WINDOW_SGIX or GLX_PBUFFER_SGIX */
passthru:     unsigned int mask;	  /* mask indicating which buffers are affected*/
passthru:     int x, y;
passthru:     int width, height;
passthru:     int count;		  /* if nonzero, at least this many more */
passthru: } GLXBufferClobberEventSGIX;
passthru: #endif
passthru:

###############################################################################
#
# GLX 1.3 commands
#
###############################################################################

GetFBConfigs(dpy, screen, nelements)
	return		GLXFBConfigPointer
	param		dpy		Display out reference
	param		screen		int in value
	param		nelements	int out reference
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	21

ChooseFBConfig(dpy, screen, attrib_list, nelements)
	return		GLXFBConfigPointer
	param		dpy		Display out reference
	param		screen		int in value
	param		attrib_list	int in reference
	param		nelements	int out reference
	category	VERSION_1_3
	glxflags	client-handcode client-intercept server-handcode

GetFBConfigAttrib(dpy, config, attribute, value)
	return		int
	param		dpy		Display out reference
	param		config		GLXFBConfig in value
	param		attribute	int in value
	param		value		int out reference
	category	VERSION_1_3
	glxflags	client-handcode client-intercept server-handcode

GetVisualFromFBConfig(dpy, config)
	return		XVisualInfoPointer
	param		dpy		Display out reference
	param		config		GLXFBConfig in value
	category	VERSION_1_3
	glxflags	client-handcode client-intercept server-handcode

CreateWindow(dpy, config, win, attrib_list)
	return		GLXWindow
	param		dpy		Display out reference
	param		config		GLXFBConfig in value
	param		win		Window in value
	param		attrib_list	int in reference
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	31

DestroyWindow(dpy, win)
	return		void
	param		dpy		Display out reference
	param		win		GLXWindow in value
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	32

CreatePixmap(dpy, config, pixmap, attrib_list)
	return		GLXPixmap
	param		dpy		Display out reference
	param		config		GLXFBConfig in value
	param		pixmap		Pixmap in value
	param		attrib_list	int in reference
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	22

DestroyPixmap(dpy, pixmap)
	return		void
	param		dpy		Display out reference
	param		pixmap		GLXPixmap in value
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	23

CreatePbuffer(dpy, config, attrib_list)
	return		GLXPbuffer
	param		dpy		Display out reference
	param		config		GLXFBConfig in value
	param		attrib_list	int in reference
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	27

DestroyPbuffer(dpy, pbuf)
	return		void
	param		dpy		Display out reference
	param		pbuf		GLXPbuffer in value
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	28

# glXGetDrawableAttributes -> GLX opcode 29
# glXChangeDrawableAttributes -> GLX opcode 30

# Uses glXGetDrawableAttributes protocol
QueryDrawable(dpy, draw, attribute, value)
	return		void
	param		dpy		Display out reference
	param		draw		GLXDrawable in value
	param		attribute	int in value
	param		value		Uint out reference
	category	VERSION_1_3
	glxflags	client-handcode client-intercept server-handcode

CreateNewContext(dpy, config, render_type, share_list, direct)
	return		GLXContext
	param		dpy		Display out reference
	param		config		GLXFBConfig in value
	param		render_type	int in value
	param		share_list	GLXContext in value
	param		direct		Bool in value
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	24

MakeContextCurrent(dpy, draw, read, ctx)
	return		Bool
	param		dpy		Display out reference
	param		draw		GLXDrawable in value
	param		read		GLXDrawable in value
	param		ctx		GLXContext in value
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	26

GetCurrentReadDrawable()
	return		GLXDrawable
	category	VERSION_1_3
	glxflags	client-handcode client-intercept server-handcode

GetCurrentDisplay()
	return		DisplayPointer
	category	VERSION_1_3
	glxflags	client-handcode client-intercept server-handcode

QueryContext(dpy, ctx, attribute, value)
	return		int
	param		dpy		Display out reference
	param		ctx		GLXContext in value
	param		attribute	int in value
	param		value		int out reference
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	25

# Uses glXChangeDrawableAttributes protocol
SelectEvent(dpy, draw, event_mask)
	return		void
	param		dpy		Display out reference
	param		draw		GLXDrawable in value
	param		event_mask	ulong in value
	category	VERSION_1_3
	glxflags	client-handcode server-handcode

# Uses glXGetDrawableAttributes protocol
GetSelectedEvent(dpy, draw, event_mask)
	return		void
	param		dpy		Display out reference
	param		draw		GLXDrawable in value
	param		event_mask	ulong out reference
	category	VERSION_1_3
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# GLX 1.4 commands
#
###############################################################################

GetProcAddress(procName)
	return		FunctionPointer
	param		procName	GLubyte in reference
	category	VERSION_1_4
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# ARB Extension #2
# ARB_get_proc_address commands
# @promoted to core in GLX 1.4, but there's no provision for aliasing
# @in GLX spec files, yet
#
###############################################################################

GetProcAddressARB(procName)
	return		FunctionPointer
	param		procName	GLubyte in reference
	category	ARB_get_proc_address
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# ARB Extension #5
# ARB_multisample commands
#
###############################################################################

# (none)
newcategory: ARB_multisample

###############################################################################
#
# Extension #25
# SGIS_multisample commands
#
###############################################################################

# (none)
newcategory: SGIS_multisample

###############################################################################
#
# Extension #28
# EXT_visual_info commands
#
###############################################################################

# (none)
newcategory: EXT_visual_info

###############################################################################
#
# Extension #40
# SGI_swap_control commands
#
###############################################################################

SwapIntervalSGI(interval)
	return		int
	param		interval	int in value
	category	SGI_swap_control
	glxflags	client-handcode server-handcode
	glxvendorglx	65536

###############################################################################
#
# Extension #41
# SGI_video_sync commands
#
###############################################################################

GetVideoSyncSGI(count)
	return		int
	param		count		Uint out reference
	category	SGI_video_sync
	glxflags	client-handcode client-intercept server-handcode

WaitVideoSyncSGI(divisor, remainder, count)
	return		int
	param		divisor		int in value
	param		remainder	int in value
	param		count		Uint out reference
	category	SGI_video_sync
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# Extension #42
# SGI_make_current_read commands
#
###############################################################################

MakeCurrentReadSGI(dpy, draw, read, ctx)
	return		Bool
	param		dpy		Display out reference
	param		draw		GLXDrawable in value
	param		read		GLXDrawable in value
	param		ctx		GLXContext in value
	category	SGI_make_current_read
	glxflags	client-handcode server-handcode
	glxvendorglx	65537

GetCurrentReadDrawableSGI()
	return		GLXDrawable
	category	SGI_make_current_read
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# Extension #43
# SGIX_video_source commands
#
###############################################################################

newcategory: SGIX_video_source
passthru: #ifdef _VL_H

CreateGLXVideoSourceSGIX(display, screen, server, path, nodeClass, drainNode)
	return		GLXVideoSourceSGIX
	param		display		Display out reference
	param		screen		int in value
	param		server		VLServer in value
	param		path		VLPath in value
	param		nodeClass	int in value
	param		drainNode	VLNode in value
	category	SGIX_video_source
	glxflags	client-handcode server-handcode
	glxvendorglx	65538

DestroyGLXVideoSourceSGIX(dpy, glxvideosource)
	return		void
	param		dpy		Display out reference
	param		glxvideosource	GLXVideoSourceSGIX in value
	category	SGIX_video_source
	glxflags	client-handcode server-handcode
	glxvendorglx	65539

endcategory:
passthru: #endif /* _VL_H */

###############################################################################
#
# Extension #44
# EXT_visual_rating commands
#
###############################################################################

# (none)
newcategory: EXT_visual_rating

###############################################################################
#
# Extension #47
# EXT_import_context commands
#
###############################################################################

GetCurrentDisplayEXT()
	return		DisplayPointer
	category	EXT_import_context
	glxflags	client-handcode client-intercept server-handcode

QueryContextInfoEXT(dpy, context, attribute,value)
	return		int
	param		dpy		Display out reference
	param		context		GLXContext in value
	param		attribute	int in value
	param		value		int out reference
	category	EXT_import_context
	glxflags	client-handcode server-handcode
	glxvendorglx	1024

#@ Should be const GLXContext?
GetContextIDEXT(context)
	return		GLXContextID
	param		context		GLXContext in value
	category	EXT_import_context
	glxflags	client-handcode client-intercept server-handcode

ImportContextEXT(dpy, contextID)
	return		GLXContext
	param		dpy		Display out reference
	param		contextID	GLXContextID in value
	category	EXT_import_context
	glxflags	client-handcode client-intercept server-handcode

FreeContextEXT(dpy, context)
	return		void
	param		dpy		Display out reference
	param		context		GLXContext in value
	category	EXT_import_context
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# Extension #49
# SGIX_fbconfig commands
#
###############################################################################

# GetFBConfigsSGIX protocol -> VendorPrivate opcode 65540

GetFBConfigAttribSGIX(dpy, config, attribute, value)
	return		int
	param		dpy		Display out reference
	param		config		GLXFBConfigSGIX in value
	param		attribute	int in value
	param		value		int out reference
	category	SGIX_fbconfig
	glxflags	client-handcode client-intercept server-handcode

ChooseFBConfigSGIX(dpy, screen, attrib_list, nelements)
	return		GLXFBConfigSGIXPointer
	param		dpy		Display out reference
	param		screen		int in value
	param		attrib_list	int out reference
	param		nelements	int out reference
	category	SGIX_fbconfig
	glxflags	client-handcode client-intercept server-handcode

CreateGLXPixmapWithConfigSGIX(dpy, config, pixmap)
	return		GLXPixmap
	param		dpy		Display out reference
	param		config		GLXFBConfigSGIX in value
	param		pixmap		Pixmap in value
	category	SGIX_fbconfig
	glxflags	client-handcode server-handcode
	glxvendorglx	65542

CreateContextWithConfigSGIX(dpy, config, render_type, share_list, direct)
	return		GLXContext
	param		dpy		Display out reference
	param		config		GLXFBConfigSGIX in value
	param		render_type	int in value
	param		share_list	GLXContext in value
	param		direct		Bool in value
	category	SGIX_fbconfig
	glxflags	client-handcode server-handcode
	glxvendorglx	65541

GetVisualFromFBConfigSGIX(dpy, config)
	return		XVisualInfoPointer
	param		dpy		Display out reference
	param		config		GLXFBConfigSGIX in value
	category	SGIX_fbconfig
	glxflags	client-handcode client-intercept server-handcode

GetFBConfigFromVisualSGIX(dpy, vis)
	return		GLXFBConfigSGIX
	param		dpy		Display out reference
	param		vis		XVisualInfo out reference
	category	SGIX_fbconfig
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# Extension #50
# SGIX_pbuffer commands
#
###############################################################################

# ChangeDrawableAttributesSGIX protocol -> VendorPrivate opcode 65545
# GetDrawableAttributesSGIX protocol -> VendorPrivate opcode 65546

CreateGLXPbufferSGIX(dpy, config, width,  height, attrib_list)
	return		GLXPbufferSGIX
	param		dpy		Display out reference
	param		config		GLXFBConfigSGIX in value
	param		width		Uint in value
	param		height		Uint in value
	param		attrib_list	int out reference
	category	SGIX_pbuffer
	glxflags	client-handcode server-handcode
	glxvendorglx	65543

DestroyGLXPbufferSGIX(dpy, pbuf)
	return		void
	param		dpy		Display out reference
	param		pbuf		GLXPbufferSGIX in value
	category	SGIX_pbuffer
	glxflags	client-handcode
	glxvendorglx	65544

QueryGLXPbufferSGIX(dpy, pbuf, attribute, value)
	return		int
	param		dpy		Display out reference
	param		pbuf		GLXPbufferSGIX in value
	param		attribute	int in value
	param		value		Uint out reference
	category	SGIX_pbuffer

SelectEventSGIX(dpy, drawable, mask)
	return		void
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		mask		ulong in value
	category	SGIX_pbuffer

GetSelectedEventSGIX(dpy, drawable, mask)
	return		void
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		mask		ulong out reference
	category	SGIX_pbuffer

###############################################################################
#
# Extension #62
# SGI_cushion commands
#
###############################################################################

CushionSGI(dpy, window, cushion)
	return		void
	param		dpy		Display out reference
	param		window		Window in value
	param		cushion		float in value
	category	SGI_cushion

###############################################################################
#
# Extension #83
# SGIX_video_resize commands
#
###############################################################################

BindChannelToWindowSGIX(display, screen, channel, window)
	return		int
	param		display		Display out reference
	param		screen		int in value
	param		channel		int in value
	param		window		Window in value
	category	SGIX_video_resize

ChannelRectSGIX(display, screen, channel, x, y, w, h)
	return		int
	param		display		Display out reference
	param		screen		int in value
	param		channel		int in value
	param		x		int in value
	param		y		int in value
	param		w		int in value
	param		h		int in value
	category	SGIX_video_resize

QueryChannelRectSGIX(display, screen, channel, dx, dy, dw, dh)
	return		int
	param		display		Display out reference
	param		screen		int in value
	param		channel		int in value
	param		dx		int out reference
	param		dy		int out reference
	param		dw		int out reference
	param		dh		int out reference
	category	SGIX_video_resize

QueryChannelDeltasSGIX(display, screen, channel, x, y, w, h)
	return		int
	param		display		Display out reference
	param		screen		int in value
	param		channel		int in value
	param		x		int out reference
	param		y		int out reference
	param		w		int out reference
	param		h		int out reference
	category	SGIX_video_resize

# @@@ Not in man page - this entry point may not be shipping?
ChannelRectSyncSGIX(display, screen, channel, synctype)
	return		int
	param		display		Display out reference
	param		screen		int in value
	param		channel		int in value
	param		synctype	GLenum in value
	category	SGIX_video_resize

###############################################################################
#
# Extension #86
# SGIX_dmbuffer commands
#
###############################################################################

newcategory: SGIX_dmbuffer
passthru: #ifdef _DM_BUFFER_H_

AssociateDMPbufferSGIX(dpy, pbuffer, params, dmbuffer)
	return		Bool
	param		dpy		Display out reference
	param		pbuffer		GLXPbufferSGIX in value
	param		params		DMparams out reference
	param		dmbuffer	DMbuffer in value
	category	SGIX_dmbuffer

endcategory:
passthru: #endif /* _DM_BUFFER_H_ */

###############################################################################
#
# Extension #91
# SGIX_swap_group commands
#
###############################################################################

JoinSwapGroupSGIX(dpy, drawable, member)
	return		void
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		member		GLXDrawable in value
	category	SGIX_swap_group
	glxflags	client-handcode server-handcode
	glxvendorglx	65547

###############################################################################
#
# Extension #92
# SGIX_swap_barrier commands
#
###############################################################################

BindSwapBarrierSGIX(dpy, drawable, barrier)
	return		void
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		barrier		int in value
	category	SGIX_swap_barrier
	glxflags	client-handcode server-handcode
	glxvendorglx	65548

QueryMaxSwapBarriersSGIX(dpy, screen, max)
	return		Bool
	param		dpy		Display out reference
	param		screen		int in value
	param		max		int out reference
	category	SGIX_swap_barrier
	glxflags	client-handcode server-handcode
	glxvendorglx	65549

###############################################################################
#
# Extension #183
# SUN_get_transparent_index commands
#
###############################################################################

GetTransparentIndexSUN(dpy, overlay, underlay, pTransparentIndex)
	return		Status
	param		dpy		Display out reference
	param		overlay		Window in value
	param		underlay	Window in value
	param		pTransparentIndex	long out reference
	category	SUN_get_transparent_index

###############################################################################
#
# Extension #215
# MESA_copy_sub_buffer commands
#
###############################################################################

CopySubBufferMESA(dpy, drawable, x, y, width, height)
	return		void
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		x		int in value
	param		y		int in value
	param		width		int in value
	param		height		int in value
	category	MESA_copy_sub_buffer
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# Extension #216
# MESA_pixmap_colormap commands
#
###############################################################################

CreateGLXPixmapMESA(dpy, visual, pixmap, cmap)
	return		GLXPixmap
	param		dpy		Display out reference
	param		visual		XVisualInfo out reference
	param		pixmap		Pixmap in value
	param		cmap		Colormap in value
	category	MESA_pixmap_colormap
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# Extension #217
# MESA_release_buffers commands
#
###############################################################################

ReleaseBuffersMESA(dpy, drawable)
	return		Bool
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	category	MESA_release_buffers
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# Extension #218
# MESA_set_3dfx_mode commands
#
###############################################################################

# Brian's spec has this as returning 'GLboolean' and taking 'GLint mode'
Set3DfxModeMESA(mode)
	return		Bool
	param		mode		int in value
	category	MESA_set_3dfx_mode
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# Extension #234
# GLX_SGIX_visual_select_group commands
#
###############################################################################

# (none)
newcategory: SGIX_visual_select_group

###############################################################################
#
# Extension #237
# GLX_OML_swap_method commands
#
###############################################################################

# (none)
newcategory:  GLX_OML_swap_method

###############################################################################
#
# Extension #238
# GLX_OML_sync_control commands
#
###############################################################################

# ??? TO BE DONE ???
#    Bool glXGetSyncValuesOML(Display* dpy, GLXDrawable drawable, int64_t* ust, int64_t* msc, int64_t* sbc)
#    Bool glXGetMscRateOML(Display* dpy, GLXDrawable drawable, int32_t* numerator, int32_t* denominator)
#    int64_t glXSwapBuffersMscOML(Display* dpy, GLXDrawable drawable, int64_t target_msc, int64_t divisor, int64_t remainder)
#    Bool glXWaitForMscOML(Display* dpy, GLXDrawable drawable, int64_t target_msc, int64_t divisor, int64_t remainder, int64_t* ust, int64_t* msc, int64_t* sbc)
#    Bool glXWaitForSbcOML(Display* dpy, GLXDrawable drawable, int64_t target_sbc, int64_t* ust, int64_t* msc, int64_t* sbc)
newcategory:  GLX_OML_sync_control
