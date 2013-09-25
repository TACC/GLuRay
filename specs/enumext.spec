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
#
# $Date: 2002/09/25 16:43:18 $ $Revision: 1.1.1.1 $
# $Header: /cvsroot/spyglass/spyglass-gui/src/lib/specs/enumext.spec,v 1.1.1.1 2002/09/25 16:43:18 mem Exp $

# List of GL enumerants for glext.h header
#
# This is NOT the master GL enumerant registry (enum.spec).
#
# Unlike enum.spec, enumext.spec is
#   (1) In order by extension number
#   (2) Includes only extensions and 1.2/1.3 core enumerants, since
#	it's assumed all <gl.h> today support at least OpenGL 1.1
#   (3) Has no 'Extensions' section, since enums are always
#	conditionally protected against multiple definition
#	by glextenum.pl.
#   (4) Is processed by glextenum.pl, which has evolved
#	from enum.pl - should merge back into one script.

# glext.h version number - this should be automatically updated,
#   when changing either enum or template spec files.

passthru:
passthru: /* Header file version number, required by OpenGL ABI for Linux */
passthru: /* glext.h last updated 2002/03/13 */
passthru: /* Current version at http://oss.sgi.com/projects/ogl-sample/registry/ */
passthru: #define GL_GLEXT_VERSION 10

###############################################################################
#
# OpenGL 1.2 enums
#
###############################################################################

VERSION_1_2 enum:
	CONSTANT_COLOR					= 0x8001 # Equivalent to EXT_blend_color
	ONE_MINUS_CONSTANT_COLOR			= 0x8002
	CONSTANT_ALPHA					= 0x8003
	ONE_MINUS_CONSTANT_ALPHA			= 0x8004
	BLEND_COLOR					= 0x8005 # 4 F
	FUNC_ADD					= 0x8006 # Equivalent to EXT_blend_minmax
	MIN						= 0x8007
	MAX						= 0x8008
	BLEND_EQUATION					= 0x8009 # 1 I
	FUNC_SUBTRACT					= 0x800A # Equivalent to EXT_blend_subtract
	FUNC_REVERSE_SUBTRACT				= 0x800B
	CONVOLUTION_1D					= 0x8010 # 1 I # Equivalent to EXT_convolution
	CONVOLUTION_2D					= 0x8011 # 1 I
	SEPARABLE_2D					= 0x8012 # 1 I
	CONVOLUTION_BORDER_MODE				= 0x8013
	CONVOLUTION_FILTER_SCALE			= 0x8014
	CONVOLUTION_FILTER_BIAS				= 0x8015
	REDUCE						= 0x8016
	CONVOLUTION_FORMAT				= 0x8017
	CONVOLUTION_WIDTH				= 0x8018
	CONVOLUTION_HEIGHT				= 0x8019
	MAX_CONVOLUTION_WIDTH				= 0x801A
	MAX_CONVOLUTION_HEIGHT				= 0x801B
	POST_CONVOLUTION_RED_SCALE			= 0x801C # 1 F
	POST_CONVOLUTION_GREEN_SCALE			= 0x801D # 1 F
	POST_CONVOLUTION_BLUE_SCALE			= 0x801E # 1 F
	POST_CONVOLUTION_ALPHA_SCALE			= 0x801F # 1 F
	POST_CONVOLUTION_RED_BIAS			= 0x8020 # 1 F
	POST_CONVOLUTION_GREEN_BIAS			= 0x8021 # 1 F
	POST_CONVOLUTION_BLUE_BIAS			= 0x8022 # 1 F
	POST_CONVOLUTION_ALPHA_BIAS			= 0x8023 # 1 F
	HISTOGRAM					= 0x8024 # 1 I # Equivalent to EXT_histogram
	PROXY_HISTOGRAM					= 0x8025
	HISTOGRAM_WIDTH					= 0x8026
	HISTOGRAM_FORMAT				= 0x8027
	HISTOGRAM_RED_SIZE				= 0x8028
	HISTOGRAM_GREEN_SIZE				= 0x8029
	HISTOGRAM_BLUE_SIZE				= 0x802A
	HISTOGRAM_ALPHA_SIZE				= 0x802B
	HISTOGRAM_LUMINANCE_SIZE			= 0x802C
	HISTOGRAM_SINK					= 0x802D
	MINMAX						= 0x802E # 1 I
	MINMAX_FORMAT					= 0x802F
	MINMAX_SINK					= 0x8030
	TABLE_TOO_LARGE					= 0x8031
	UNSIGNED_BYTE_3_3_2				= 0x8032 # Equivalent to EXT_packed_pixels
	UNSIGNED_SHORT_4_4_4_4				= 0x8033
	UNSIGNED_SHORT_5_5_5_1				= 0x8034
	UNSIGNED_INT_8_8_8_8				= 0x8035
	UNSIGNED_INT_10_10_10_2				= 0x8036
	RESCALE_NORMAL					= 0x803A # 1 I # Equivalent to EXT_rescale_normal
	UNSIGNED_BYTE_2_3_3_REV				= 0x8362 # New for OpenGL 1.2
	UNSIGNED_SHORT_5_6_5				= 0x8363
	UNSIGNED_SHORT_5_6_5_REV			= 0x8364
	UNSIGNED_SHORT_4_4_4_4_REV			= 0x8365
	UNSIGNED_SHORT_1_5_5_5_REV			= 0x8366
	UNSIGNED_INT_8_8_8_8_REV			= 0x8367
	UNSIGNED_INT_2_10_10_10_REV			= 0x8368
	COLOR_MATRIX					= 0x80B1 # 16 F # Equivalent to SGI_color_matrix
	COLOR_MATRIX_STACK_DEPTH			= 0x80B2 # 1 I
	MAX_COLOR_MATRIX_STACK_DEPTH			= 0x80B3 # 1 I
	POST_COLOR_MATRIX_RED_SCALE			= 0x80B4 # 1 F
	POST_COLOR_MATRIX_GREEN_SCALE			= 0x80B5 # 1 F
	POST_COLOR_MATRIX_BLUE_SCALE			= 0x80B6 # 1 F
	POST_COLOR_MATRIX_ALPHA_SCALE			= 0x80B7 # 1 F
	POST_COLOR_MATRIX_RED_BIAS			= 0x80B8 # 1 F
	POST_COLOR_MATRIX_GREEN_BIAS			= 0x80B9 # 1 F
	POST_COLOR_MATRIX_BLUE_BIAS			= 0x80BA # 1 F
	COLOR_TABLE					= 0x80D0 # 1 I # Equivalent to SGI_color_table
	POST_CONVOLUTION_COLOR_TABLE			= 0x80D1 # 1 I
	POST_COLOR_MATRIX_COLOR_TABLE			= 0x80D2 # 1 I
	PROXY_COLOR_TABLE				= 0x80D3
	PROXY_POST_CONVOLUTION_COLOR_TABLE		= 0x80D4
	PROXY_POST_COLOR_MATRIX_COLOR_TABLE		= 0x80D5
	COLOR_TABLE_SCALE				= 0x80D6
	COLOR_TABLE_BIAS				= 0x80D7
	COLOR_TABLE_FORMAT				= 0x80D8
	COLOR_TABLE_WIDTH				= 0x80D9
	COLOR_TABLE_RED_SIZE				= 0x80DA
	COLOR_TABLE_GREEN_SIZE				= 0x80DB
	COLOR_TABLE_BLUE_SIZE				= 0x80DC
	COLOR_TABLE_ALPHA_SIZE				= 0x80DD
	COLOR_TABLE_LUMINANCE_SIZE			= 0x80DE
	COLOR_TABLE_INTENSITY_SIZE			= 0x80DF
	BGR						= 0x80E0
	BGRA						= 0x80E1
	MAX_ELEMENTS_VERTICES				= 0x80E8
	MAX_ELEMENTS_INDICES				= 0x80E9
	CLAMP_TO_EDGE					= 0x812F # Equivalent to SGIS_texture_edge_clamp
	TEXTURE_MIN_LOD					= 0x813A # Equivalent to SGIS_texture_lod
	TEXTURE_MAX_LOD					= 0x813B
	TEXTURE_BASE_LEVEL				= 0x813C
	TEXTURE_MAX_LEVEL				= 0x813D
	IGNORE_BORDER					= 0x8150
	CONSTANT_BORDER					= 0x8151
	WRAP_BORDER					= 0x8152
	REPLICATE_BORDER				= 0x8153
	CONVOLUTION_BORDER_COLOR			= 0x8154
	LIGHT_MODEL_COLOR_CONTROL			= 0x81F8 # 1 I
	SINGLE_COLOR					= 0x81F9
	SEPARATE_SPECULAR_COLOR				= 0x81FA
	SMOOTH_POINT_SIZE_RANGE				= 0x0B12 # 2 F
	SMOOTH_POINT_SIZE_GRANULARITY			= 0x0B13 # 1 F
	SMOOTH_LINE_WIDTH_RANGE				= 0x0B22 # 2 F
	SMOOTH_LINE_WIDTH_GRANULARITY			= 0x0B23 # 1 F
	ALIASED_POINT_SIZE_RANGE			= 0x846D # 2 F
	ALIASED_LINE_WIDTH_RANGE			= 0x846E # 2 F

###############################################################################
#
# OpenGL 1.3 enums
#
###############################################################################

VERSION_1_3 enum:
	TEXTURE0					= 0x84C0	# Promoted from ARB_multitexture
	TEXTURE1					= 0x84C1
	TEXTURE2					= 0x84C2
	TEXTURE3					= 0x84C3
	TEXTURE4					= 0x84C4
	TEXTURE5					= 0x84C5
	TEXTURE6					= 0x84C6
	TEXTURE7					= 0x84C7
	TEXTURE8					= 0x84C8
	TEXTURE9					= 0x84C9
	TEXTURE10					= 0x84CA
	TEXTURE11					= 0x84CB
	TEXTURE12					= 0x84CC
	TEXTURE13					= 0x84CD
	TEXTURE14					= 0x84CE
	TEXTURE15					= 0x84CF
	TEXTURE16					= 0x84D0
	TEXTURE17					= 0x84D1
	TEXTURE18					= 0x84D2
	TEXTURE19					= 0x84D3
	TEXTURE20					= 0x84D4
	TEXTURE21					= 0x84D5
	TEXTURE22					= 0x84D6
	TEXTURE23					= 0x84D7
	TEXTURE24					= 0x84D8
	TEXTURE25					= 0x84D9
	TEXTURE26					= 0x84DA
	TEXTURE27					= 0x84DB
	TEXTURE28					= 0x84DC
	TEXTURE29					= 0x84DD
	TEXTURE30					= 0x84DE
	TEXTURE31					= 0x84DF
	ACTIVE_TEXTURE					= 0x84E0 # 1 I
	CLIENT_ACTIVE_TEXTURE				= 0x84E1 # 1 I
	MAX_TEXTURE_UNITS				= 0x84E2 # 1 I
	TRANSPOSE_MODELVIEW_MATRIX			= 0x84E3 # 16 F # Promoted from ARB_transpose_matrix
	TRANSPOSE_PROJECTION_MATRIX			= 0x84E4 # 16 F
	TRANSPOSE_TEXTURE_MATRIX			= 0x84E5 # 16 F
	TRANSPOSE_COLOR_MATRIX				= 0x84E6 # 16 F
	MULTISAMPLE					= 0x809D	# Promoted from ARB_multisample
	SAMPLE_ALPHA_TO_COVERAGE			= 0x809E
	SAMPLE_ALPHA_TO_ONE				= 0x809F
	SAMPLE_COVERAGE					= 0x80A0
	SAMPLE_BUFFERS					= 0x80A8
	SAMPLES						= 0x80A9
	SAMPLE_COVERAGE_VALUE				= 0x80AA
	SAMPLE_COVERAGE_INVERT				= 0x80AB
	MULTISAMPLE_BIT					= 0x20000000
	NORMAL_MAP					= 0x8511	# Promoted from ARB_texture_cube_map
	REFLECTION_MAP					= 0x8512
	TEXTURE_CUBE_MAP				= 0x8513
	TEXTURE_BINDING_CUBE_MAP			= 0x8514
	TEXTURE_CUBE_MAP_POSITIVE_X			= 0x8515
	TEXTURE_CUBE_MAP_NEGATIVE_X			= 0x8516
	TEXTURE_CUBE_MAP_POSITIVE_Y			= 0x8517
	TEXTURE_CUBE_MAP_NEGATIVE_Y			= 0x8518
	TEXTURE_CUBE_MAP_POSITIVE_Z			= 0x8519
	TEXTURE_CUBE_MAP_NEGATIVE_Z			= 0x851A
	PROXY_TEXTURE_CUBE_MAP				= 0x851B
	MAX_CUBE_MAP_TEXTURE_SIZE			= 0x851C
	COMPRESSED_ALPHA				= 0x84E9	# Promoted from ARB_texture_compression
	COMPRESSED_LUMINANCE				= 0x84EA
	COMPRESSED_LUMINANCE_ALPHA			= 0x84EB
	COMPRESSED_INTENSITY				= 0x84EC
	COMPRESSED_RGB					= 0x84ED
	COMPRESSED_RGBA					= 0x84EE
	TEXTURE_COMPRESSION_HINT			= 0x84EF
	TEXTURE_COMPRESSED_IMAGE_SIZE			= 0x86A0
	TEXTURE_COMPRESSED				= 0x86A1
	NUM_COMPRESSED_TEXTURE_FORMATS			= 0x86A2
	COMPRESSED_TEXTURE_FORMATS			= 0x86A3
	CLAMP_TO_BORDER					= 0x812D	# Promoted from ARB_texture_border_clamp
	CLAMP_TO_BORDER_SGIS				= 0x812D
	COMBINE						= 0x8570	# Promoted from ARB_texture_env_combine
	COMBINE_RGB					= 0x8571
	COMBINE_ALPHA					= 0x8572
	SOURCE0_RGB					= 0x8580
	SOURCE1_RGB					= 0x8581
	SOURCE2_RGB					= 0x8582
	SOURCE0_ALPHA					= 0x8588
	SOURCE1_ALPHA					= 0x8589
	SOURCE2_ALPHA					= 0x858A
	OPERAND0_RGB					= 0x8590
	OPERAND1_RGB					= 0x8591
	OPERAND2_RGB					= 0x8592
	OPERAND0_ALPHA					= 0x8598
	OPERAND1_ALPHA					= 0x8599
	OPERAND2_ALPHA					= 0x859A
	RGB_SCALE					= 0x8573
	ADD_SIGNED					= 0x8574
	INTERPOLATE					= 0x8575
	SUBTRACT					= 0x84E7
	CONSTANT					= 0x8576
	PRIMARY_COLOR					= 0x8577
	PREVIOUS					= 0x8578
	DOT3_RGB					= 0x86AE	# Promoted from ARB_texture_env_dot3
	DOT3_RGBA					= 0x86AF

###############################################################################
#
# ARB extensions, in ARB extension order
#
###############################################################################

###############################################################################

# ARB Extension #1
ARB_multitexture enum:
	TEXTURE0_ARB					= 0x84C0
	TEXTURE1_ARB					= 0x84C1
	TEXTURE2_ARB					= 0x84C2
	TEXTURE3_ARB					= 0x84C3
	TEXTURE4_ARB					= 0x84C4
	TEXTURE5_ARB					= 0x84C5
	TEXTURE6_ARB					= 0x84C6
	TEXTURE7_ARB					= 0x84C7
	TEXTURE8_ARB					= 0x84C8
	TEXTURE9_ARB					= 0x84C9
	TEXTURE10_ARB					= 0x84CA
	TEXTURE11_ARB					= 0x84CB
	TEXTURE12_ARB					= 0x84CC
	TEXTURE13_ARB					= 0x84CD
	TEXTURE14_ARB					= 0x84CE
	TEXTURE15_ARB					= 0x84CF
	TEXTURE16_ARB					= 0x84D0
	TEXTURE17_ARB					= 0x84D1
	TEXTURE18_ARB					= 0x84D2
	TEXTURE19_ARB					= 0x84D3
	TEXTURE20_ARB					= 0x84D4
	TEXTURE21_ARB					= 0x84D5
	TEXTURE22_ARB					= 0x84D6
	TEXTURE23_ARB					= 0x84D7
	TEXTURE24_ARB					= 0x84D8
	TEXTURE25_ARB					= 0x84D9
	TEXTURE26_ARB					= 0x84DA
	TEXTURE27_ARB					= 0x84DB
	TEXTURE28_ARB					= 0x84DC
	TEXTURE29_ARB					= 0x84DD
	TEXTURE30_ARB					= 0x84DE
	TEXTURE31_ARB					= 0x84DF
	ACTIVE_TEXTURE_ARB				= 0x84E0 # 1 I
	CLIENT_ACTIVE_TEXTURE_ARB			= 0x84E1 # 1 I
	MAX_TEXTURE_UNITS_ARB				= 0x84E2 # 1 I

###############################################################################

# No new tokens
# ARB Extension #2 - GLX_ARB_get_proc_address

###############################################################################

# ARB Extension #3
ARB_transpose_matrix enum:
	TRANSPOSE_MODELVIEW_MATRIX_ARB			= 0x84E3 # 16 F
	TRANSPOSE_PROJECTION_MATRIX_ARB			= 0x84E4 # 16 F
	TRANSPOSE_TEXTURE_MATRIX_ARB			= 0x84E5 # 16 F
	TRANSPOSE_COLOR_MATRIX_ARB			= 0x84E6 # 16 F

###############################################################################

# No new tokens
# ARB Extension #4 - WGL_ARB_buffer_region

###############################################################################

# ARB Extension #5
ARB_multisample enum:
	MULTISAMPLE_ARB					= 0x809D
	SAMPLE_ALPHA_TO_COVERAGE_ARB			= 0x809E
	SAMPLE_ALPHA_TO_ONE_ARB				= 0x809F
	SAMPLE_COVERAGE_ARB				= 0x80A0
	SAMPLE_BUFFERS_ARB				= 0x80A8
	SAMPLES_ARB					= 0x80A9
	SAMPLE_COVERAGE_VALUE_ARB			= 0x80AA
	SAMPLE_COVERAGE_INVERT_ARB			= 0x80AB
	MULTISAMPLE_BIT_ARB				= 0x20000000

###############################################################################

# No new tokens
# ARB Extension #6
ARB_texture_env_add enum:

###############################################################################

# ARB Extension #7
ARB_texture_cube_map enum:
	NORMAL_MAP_ARB					= 0x8511
	REFLECTION_MAP_ARB				= 0x8512
	TEXTURE_CUBE_MAP_ARB				= 0x8513
	TEXTURE_BINDING_CUBE_MAP_ARB			= 0x8514
	TEXTURE_CUBE_MAP_POSITIVE_X_ARB			= 0x8515
	TEXTURE_CUBE_MAP_NEGATIVE_X_ARB			= 0x8516
	TEXTURE_CUBE_MAP_POSITIVE_Y_ARB			= 0x8517
	TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB			= 0x8518
	TEXTURE_CUBE_MAP_POSITIVE_Z_ARB			= 0x8519
	TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB			= 0x851A
	PROXY_TEXTURE_CUBE_MAP_ARB			= 0x851B
	MAX_CUBE_MAP_TEXTURE_SIZE_ARB			= 0x851C

###############################################################################

# No new tokens
# ARB Extension #8 - WGL_ARB_extensions_string
# ARB Extension #9 - WGL_ARB_pixel_format
# ARB Extension #10 - WGL_ARB_make_current_read
# ARB Extension #11 - WGL_ARB_pbuffer

###############################################################################

# ARB Extension #12
ARB_texture_compression enum:
	COMPRESSED_ALPHA_ARB				= 0x84E9
	COMPRESSED_LUMINANCE_ARB			= 0x84EA
	COMPRESSED_LUMINANCE_ALPHA_ARB			= 0x84EB
	COMPRESSED_INTENSITY_ARB			= 0x84EC
	COMPRESSED_RGB_ARB				= 0x84ED
	COMPRESSED_RGBA_ARB				= 0x84EE
	TEXTURE_COMPRESSION_HINT_ARB			= 0x84EF
	TEXTURE_COMPRESSED_IMAGE_SIZE_ARB		= 0x86A0
	TEXTURE_COMPRESSED_ARB				= 0x86A1
	NUM_COMPRESSED_TEXTURE_FORMATS_ARB		= 0x86A2
	COMPRESSED_TEXTURE_FORMATS_ARB			= 0x86A3

###############################################################################

# ARB Extension #13
# Promoted from #36 SGIS_texture_border_clamp
ARB_texture_border_clamp enum:
	CLAMP_TO_BORDER_ARB				= 0x812D
	CLAMP_TO_BORDER_SGIS				= 0x812D

###############################################################################

# ARB Extension #14
# Promoted from #54 {SGIS,EXT}_point_parameters
ARB_point_parameters enum:
	POINT_SIZE_MIN_ARB				= 0x8126 # 1 F
	POINT_SIZE_MIN_EXT				= 0x8126 # 1 F
	POINT_SIZE_MIN_SGIS				= 0x8126 # 1 F
	POINT_SIZE_MAX_ARB				= 0x8127 # 1 F
	POINT_SIZE_MAX_EXT				= 0x8127 # 1 F
	POINT_SIZE_MAX_SGIS				= 0x8127 # 1 F
	POINT_FADE_THRESHOLD_SIZE_ARB			= 0x8128 # 1 F
	POINT_FADE_THRESHOLD_SIZE_EXT			= 0x8128 # 1 F
	POINT_FADE_THRESHOLD_SIZE_SGIS			= 0x8128 # 1 F
	POINT_DISTANCE_ATTENUATION_ARB			= 0x8129 # 3 F
	DISTANCE_ATTENUATION_EXT			= 0x8129 # 3 F
	DISTANCE_ATTENUATION_SGIS			= 0x8129 # 3 F

###############################################################################

# ARB Extension #15
ARB_vertex_blend enum:
	MAX_VERTEX_UNITS_ARB				= 0x86A4
	ACTIVE_VERTEX_UNITS_ARB				= 0x86A5
	WEIGHT_SUM_UNITY_ARB				= 0x86A6
	VERTEX_BLEND_ARB				= 0x86A7
	CURRENT_WEIGHT_ARB				= 0x86A8
	WEIGHT_ARRAY_TYPE_ARB				= 0x86A9
	WEIGHT_ARRAY_STRIDE_ARB				= 0x86AA
	WEIGHT_ARRAY_SIZE_ARB				= 0x86AB
	WEIGHT_ARRAY_POINTER_ARB			= 0x86AC
	WEIGHT_ARRAY_ARB				= 0x86AD
	MODELVIEW0_ARB					= 0x1700
	MODELVIEW1_ARB					= 0x850A
	MODELVIEW2_ARB					= 0x8722
	MODELVIEW3_ARB					= 0x8723
	MODELVIEW4_ARB					= 0x8724
	MODELVIEW5_ARB					= 0x8725
	MODELVIEW6_ARB					= 0x8726
	MODELVIEW7_ARB					= 0x8727
	MODELVIEW8_ARB					= 0x8728
	MODELVIEW9_ARB					= 0x8729
	MODELVIEW10_ARB					= 0x872A
	MODELVIEW11_ARB					= 0x872B
	MODELVIEW12_ARB					= 0x872C
	MODELVIEW13_ARB					= 0x872D
	MODELVIEW14_ARB					= 0x872E
	MODELVIEW15_ARB					= 0x872F
	MODELVIEW16_ARB					= 0x8730
	MODELVIEW17_ARB					= 0x8731
	MODELVIEW18_ARB					= 0x8732
	MODELVIEW19_ARB					= 0x8733
	MODELVIEW20_ARB					= 0x8734
	MODELVIEW21_ARB					= 0x8735
	MODELVIEW22_ARB					= 0x8736
	MODELVIEW23_ARB					= 0x8737
	MODELVIEW24_ARB					= 0x8738
	MODELVIEW25_ARB					= 0x8739
	MODELVIEW26_ARB					= 0x873A
	MODELVIEW27_ARB					= 0x873B
	MODELVIEW28_ARB					= 0x873C
	MODELVIEW29_ARB					= 0x873D
	MODELVIEW30_ARB					= 0x873E
	MODELVIEW31_ARB					= 0x873F

###############################################################################

# ARB Extension #16
ARB_matrix_palette enum:
	MATRIX_PALETTE_ARB				= 0x8840
	MAX_MATRIX_PALETTE_STACK_DEPTH_ARB		= 0x8841
	MAX_PALETTE_MATRICES_ARB			= 0x8842
	CURRENT_PALETTE_MATRIX_ARB			= 0x8843
	MATRIX_INDEX_ARRAY_ARB				= 0x8844
	CURRENT_MATRIX_INDEX_ARB			= 0x8845
	MATRIX_INDEX_ARRAY_SIZE_ARB			= 0x8846
	MATRIX_INDEX_ARRAY_TYPE_ARB			= 0x8847
	MATRIX_INDEX_ARRAY_STRIDE_ARB			= 0x8848
	MATRIX_INDEX_ARRAY_POINTER_ARB			= 0x8849

###############################################################################

# ARB Extension #17
# Shares enum values with EXT_texture_env_combine
ARB_texture_env_combine enum:
	COMBINE_ARB					= 0x8570
	COMBINE_RGB_ARB					= 0x8571
	COMBINE_ALPHA_ARB				= 0x8572
	SOURCE0_RGB_ARB					= 0x8580
	SOURCE1_RGB_ARB					= 0x8581
	SOURCE2_RGB_ARB					= 0x8582
	SOURCE0_ALPHA_ARB				= 0x8588
	SOURCE1_ALPHA_ARB				= 0x8589
	SOURCE2_ALPHA_ARB				= 0x858A
	OPERAND0_RGB_ARB				= 0x8590
	OPERAND1_RGB_ARB				= 0x8591
	OPERAND2_RGB_ARB				= 0x8592
	OPERAND0_ALPHA_ARB				= 0x8598
	OPERAND1_ALPHA_ARB				= 0x8599
	OPERAND2_ALPHA_ARB				= 0x859A
	RGB_SCALE_ARB					= 0x8573
	ADD_SIGNED_ARB					= 0x8574
	INTERPOLATE_ARB					= 0x8575
	SUBTRACT_ARB					= 0x84E7
	CONSTANT_ARB					= 0x8576
	PRIMARY_COLOR_ARB				= 0x8577
	PREVIOUS_ARB					= 0x8578

###############################################################################

# No new tokens
# ARB Extension #18
ARB_texture_env_crossbar enum:

###############################################################################

# ARB Extension #19
# Promoted from #220 EXT_texture_env_dot3
ARB_texture_env_dot3 enum:
	DOT3_RGB_ARB					= 0x86AE
	DOT3_RGB_EXT					= 0x86AE
	DOT3_RGBA_ARB					= 0x86AF
	DOT3_RGBA_EXT					= 0x86AF

###############################################################################

# No new tokens
# ARB Extension #20 - WGL_ARB_render_texture

###############################################################################

# ARB Extension #21
ARB_texture_mirrored_repeat enum:
	MIRRORED_REPEAT_ARB				= 0x8370

###############################################################################

# ARB Extension #22
ARB_depth_texture enum:
	DEPTH_COMPONENT16_ARB				= 0x81A5
	DEPTH_COMPONENT24_ARB				= 0x81A6
	DEPTH_COMPONENT32_ARB				= 0x81A7
	TEXTURE_DEPTH_SIZE_ARB				= 0x884A
	DEPTH_TEXTURE_MODE_ARB				= 0x884B

###############################################################################

# ARB Extension #23
ARB_shadow enum:
       TEXTURE_COMPARE_MODE_ARB				= 0x884C
       TEXTURE_COMPARE_FUNC_ARB				= 0x884D
       COMPARE_R_TO_TEXTURE_ARB				= 0x884E

###############################################################################

# ARB Extension #24
ARB_shadow_ambient enum:
	TEXTURE_COMPARE_FAIL_VALUE_ARB			= 0x80BF

###############################################################################

# No new tokens
# ARB Extension #25
ARB_window_pos enum:

###############################################################################
#
# non-ARB extensions follow, in registry order
#
###############################################################################

###############################################################################

# Extension #1
EXT_abgr enum:
	ABGR_EXT					= 0x8000

###############################################################################

# Extension #2
EXT_blend_color enum:
	CONSTANT_COLOR_EXT				= 0x8001
	ONE_MINUS_CONSTANT_COLOR_EXT			= 0x8002
	CONSTANT_ALPHA_EXT				= 0x8003
	ONE_MINUS_CONSTANT_ALPHA_EXT			= 0x8004
	BLEND_COLOR_EXT					= 0x8005 # 4 F

###############################################################################

# Extension #3
EXT_polygon_offset enum:
	POLYGON_OFFSET_EXT				= 0x8037
	POLYGON_OFFSET_FACTOR_EXT			= 0x8038
	POLYGON_OFFSET_BIAS_EXT				= 0x8039 # 1 F

###############################################################################

# Extension #4
EXT_texture enum:
	ALPHA4_EXT					= 0x803B
	ALPHA8_EXT					= 0x803C
	ALPHA12_EXT					= 0x803D
	ALPHA16_EXT					= 0x803E
	LUMINANCE4_EXT					= 0x803F
	LUMINANCE8_EXT					= 0x8040
	LUMINANCE12_EXT					= 0x8041
	LUMINANCE16_EXT					= 0x8042
	LUMINANCE4_ALPHA4_EXT				= 0x8043
	LUMINANCE6_ALPHA2_EXT				= 0x8044
	LUMINANCE8_ALPHA8_EXT				= 0x8045
	LUMINANCE12_ALPHA4_EXT				= 0x8046
	LUMINANCE12_ALPHA12_EXT				= 0x8047
	LUMINANCE16_ALPHA16_EXT				= 0x8048
	INTENSITY_EXT					= 0x8049
	INTENSITY4_EXT					= 0x804A
	INTENSITY8_EXT					= 0x804B
	INTENSITY12_EXT					= 0x804C
	INTENSITY16_EXT					= 0x804D
	RGB2_EXT					= 0x804E
	RGB4_EXT					= 0x804F
	RGB5_EXT					= 0x8050
	RGB8_EXT					= 0x8051
	RGB10_EXT					= 0x8052
	RGB12_EXT					= 0x8053
	RGB16_EXT					= 0x8054
	RGBA2_EXT					= 0x8055
	RGBA4_EXT					= 0x8056
	RGB5_A1_EXT					= 0x8057
	RGBA8_EXT					= 0x8058
	RGB10_A2_EXT					= 0x8059
	RGBA12_EXT					= 0x805A
	RGBA16_EXT					= 0x805B
	TEXTURE_RED_SIZE_EXT				= 0x805C
	TEXTURE_GREEN_SIZE_EXT				= 0x805D
	TEXTURE_BLUE_SIZE_EXT				= 0x805E
	TEXTURE_ALPHA_SIZE_EXT				= 0x805F
	TEXTURE_LUMINANCE_SIZE_EXT			= 0x8060
	TEXTURE_INTENSITY_SIZE_EXT			= 0x8061
	REPLACE_EXT					= 0x8062
	PROXY_TEXTURE_1D_EXT				= 0x8063
	PROXY_TEXTURE_2D_EXT				= 0x8064
	TEXTURE_TOO_LARGE_EXT				= 0x8065

###############################################################################

# Extension #5 - skipped

###############################################################################

# Extension #6
EXT_texture3D enum:
	PACK_SKIP_IMAGES				= 0x806B # 1 I
	PACK_SKIP_IMAGES_EXT				= 0x806B # 1 I
	PACK_IMAGE_HEIGHT				= 0x806C # 1 F
	PACK_IMAGE_HEIGHT_EXT				= 0x806C # 1 F
	UNPACK_SKIP_IMAGES				= 0x806D # 1 I
	UNPACK_SKIP_IMAGES_EXT				= 0x806D # 1 I
	UNPACK_IMAGE_HEIGHT				= 0x806E # 1 F
	UNPACK_IMAGE_HEIGHT_EXT				= 0x806E # 1 F
	TEXTURE_3D					= 0x806F # 1 I
	TEXTURE_3D_EXT					= 0x806F # 1 I
	PROXY_TEXTURE_3D				= 0x8070
	PROXY_TEXTURE_3D_EXT				= 0x8070
	TEXTURE_DEPTH					= 0x8071
	TEXTURE_DEPTH_EXT				= 0x8071
	TEXTURE_WRAP_R					= 0x8072
	TEXTURE_WRAP_R_EXT				= 0x8072
	MAX_3D_TEXTURE_SIZE				= 0x8073 # 1 I
	MAX_3D_TEXTURE_SIZE_EXT				= 0x8073 # 1 I

###############################################################################

# Extension #7
SGIS_texture_filter4 enum:
	FILTER4_SGIS					= 0x8146
	TEXTURE_FILTER4_SIZE_SGIS			= 0x8147

###############################################################################

# Extension #8 - skipped

###############################################################################

# No new tokens
# Extension #9
EXT_subtexture enum:

###############################################################################

# No new tokens
# Extension #10
EXT_copy_texture enum:

###############################################################################

# Extension #11
EXT_histogram enum:
	HISTOGRAM_EXT					= 0x8024 # 1 I
	PROXY_HISTOGRAM_EXT				= 0x8025
	HISTOGRAM_WIDTH_EXT				= 0x8026
	HISTOGRAM_FORMAT_EXT				= 0x8027
	HISTOGRAM_RED_SIZE_EXT				= 0x8028
	HISTOGRAM_GREEN_SIZE_EXT			= 0x8029
	HISTOGRAM_BLUE_SIZE_EXT				= 0x802A
	HISTOGRAM_ALPHA_SIZE_EXT			= 0x802B
	HISTOGRAM_LUMINANCE_SIZE_EXT			= 0x802C
	HISTOGRAM_SINK_EXT				= 0x802D
	MINMAX_EXT					= 0x802E # 1 I
	MINMAX_FORMAT_EXT				= 0x802F
	MINMAX_SINK_EXT					= 0x8030
	TABLE_TOO_LARGE_EXT				= 0x8031

###############################################################################

# Extension #12
EXT_convolution enum:
	CONVOLUTION_1D_EXT				= 0x8010 # 1 I
	CONVOLUTION_2D_EXT				= 0x8011 # 1 I
	SEPARABLE_2D_EXT				= 0x8012 # 1 I
	CONVOLUTION_BORDER_MODE_EXT			= 0x8013
	CONVOLUTION_FILTER_SCALE_EXT			= 0x8014
	CONVOLUTION_FILTER_BIAS_EXT			= 0x8015
	REDUCE_EXT					= 0x8016
	CONVOLUTION_FORMAT_EXT				= 0x8017
	CONVOLUTION_WIDTH_EXT				= 0x8018
	CONVOLUTION_HEIGHT_EXT				= 0x8019
	MAX_CONVOLUTION_WIDTH_EXT			= 0x801A
	MAX_CONVOLUTION_HEIGHT_EXT			= 0x801B
	POST_CONVOLUTION_RED_SCALE_EXT			= 0x801C # 1 F
	POST_CONVOLUTION_GREEN_SCALE_EXT		= 0x801D # 1 F
	POST_CONVOLUTION_BLUE_SCALE_EXT			= 0x801E # 1 F
	POST_CONVOLUTION_ALPHA_SCALE_EXT		= 0x801F # 1 F
	POST_CONVOLUTION_RED_BIAS_EXT			= 0x8020 # 1 F
	POST_CONVOLUTION_GREEN_BIAS_EXT			= 0x8021 # 1 F
	POST_CONVOLUTION_BLUE_BIAS_EXT			= 0x8022 # 1 F
	POST_CONVOLUTION_ALPHA_BIAS_EXT			= 0x8023 # 1 F

###############################################################################

# Extension #13
SGI_color_matrix enum:
	COLOR_MATRIX_SGI				= 0x80B1 # 16 F
	COLOR_MATRIX_STACK_DEPTH_SGI			= 0x80B2 # 1 I
	MAX_COLOR_MATRIX_STACK_DEPTH_SGI		= 0x80B3 # 1 I
	POST_COLOR_MATRIX_RED_SCALE_SGI			= 0x80B4 # 1 F
	POST_COLOR_MATRIX_GREEN_SCALE_SGI		= 0x80B5 # 1 F
	POST_COLOR_MATRIX_BLUE_SCALE_SGI		= 0x80B6 # 1 F
	POST_COLOR_MATRIX_ALPHA_SCALE_SGI		= 0x80B7 # 1 F
	POST_COLOR_MATRIX_RED_BIAS_SGI			= 0x80B8 # 1 F
	POST_COLOR_MATRIX_GREEN_BIAS_SGI		= 0x80B9 # 1 F
	POST_COLOR_MATRIX_BLUE_BIAS_SGI			= 0x80BA # 1 F
	POST_COLOR_MATRIX_ALPHA_BIAS_SGI		= 0x80BB # 1 F

###############################################################################

# Extension #14
SGI_color_table enum:
	COLOR_TABLE_SGI					= 0x80D0 # 1 I
	POST_CONVOLUTION_COLOR_TABLE_SGI		= 0x80D1 # 1 I
	POST_COLOR_MATRIX_COLOR_TABLE_SGI		= 0x80D2 # 1 I
	PROXY_COLOR_TABLE_SGI				= 0x80D3
	PROXY_POST_CONVOLUTION_COLOR_TABLE_SGI		= 0x80D4
	PROXY_POST_COLOR_MATRIX_COLOR_TABLE_SGI		= 0x80D5
	COLOR_TABLE_SCALE_SGI				= 0x80D6
	COLOR_TABLE_BIAS_SGI				= 0x80D7
	COLOR_TABLE_FORMAT_SGI				= 0x80D8
	COLOR_TABLE_WIDTH_SGI				= 0x80D9
	COLOR_TABLE_RED_SIZE_SGI			= 0x80DA
	COLOR_TABLE_GREEN_SIZE_SGI			= 0x80DB
	COLOR_TABLE_BLUE_SIZE_SGI			= 0x80DC
	COLOR_TABLE_ALPHA_SIZE_SGI			= 0x80DD
	COLOR_TABLE_LUMINANCE_SIZE_SGI			= 0x80DE
	COLOR_TABLE_INTENSITY_SIZE_SGI			= 0x80DF

###############################################################################

# Extension #15
SGIS_pixel_texture enum:
	PIXEL_TEXTURE_SGIS				= 0x8353 # 1 I
	PIXEL_FRAGMENT_RGB_SOURCE_SGIS			= 0x8354 # 1 I
	PIXEL_FRAGMENT_ALPHA_SOURCE_SGIS		= 0x8355 # 1 I
	PIXEL_GROUP_COLOR_SGIS				= 0x8356 # 1 I

###############################################################################

# Extension #15a
SGIX_pixel_texture enum:
	PIXEL_TEX_GEN_SGIX				= 0x8139 # 1 I
	PIXEL_TEX_GEN_MODE_SGIX				= 0x832B # 1 I

###############################################################################

# Extension #16
SGIS_texture4D enum:
	PACK_SKIP_VOLUMES_SGIS				= 0x8130 # 1 I
	PACK_IMAGE_DEPTH_SGIS				= 0x8131 # 1 I
	UNPACK_SKIP_VOLUMES_SGIS			= 0x8132 # 1 I
	UNPACK_IMAGE_DEPTH_SGIS				= 0x8133 # 1 I
	TEXTURE_4D_SGIS					= 0x8134 # 1 I
	PROXY_TEXTURE_4D_SGIS				= 0x8135
	TEXTURE_4DSIZE_SGIS				= 0x8136
	TEXTURE_WRAP_Q_SGIS				= 0x8137
	MAX_4D_TEXTURE_SIZE_SGIS			= 0x8138 # 1 I
	TEXTURE_4D_BINDING_SGIS				= 0x814F # 1 I

###############################################################################

# Extension #17
SGI_texture_color_table enum:
	TEXTURE_COLOR_TABLE_SGI				= 0x80BC # 1 I
	PROXY_TEXTURE_COLOR_TABLE_SGI			= 0x80BD

###############################################################################

# Extension #18
EXT_cmyka enum:
	CMYK_EXT					= 0x800C
	CMYKA_EXT					= 0x800D
	PACK_CMYK_HINT_EXT				= 0x800E # 1 I
	UNPACK_CMYK_HINT_EXT				= 0x800F # 1 I

###############################################################################

# Extension #19 - skipped

###############################################################################

# Extension #20
EXT_texture_object enum:
	TEXTURE_PRIORITY_EXT				= 0x8066
	TEXTURE_RESIDENT_EXT				= 0x8067
	TEXTURE_1D_BINDING_EXT				= 0x8068
	TEXTURE_2D_BINDING_EXT				= 0x8069
	TEXTURE_3D_BINDING_EXT				= 0x806A # 1 I

###############################################################################

# Extension #21
SGIS_detail_texture enum:
	DETAIL_TEXTURE_2D_SGIS				= 0x8095
	DETAIL_TEXTURE_2D_BINDING_SGIS			= 0x8096 # 1 I
	LINEAR_DETAIL_SGIS				= 0x8097
	LINEAR_DETAIL_ALPHA_SGIS			= 0x8098
	LINEAR_DETAIL_COLOR_SGIS			= 0x8099
	DETAIL_TEXTURE_LEVEL_SGIS			= 0x809A
	DETAIL_TEXTURE_MODE_SGIS			= 0x809B
	DETAIL_TEXTURE_FUNC_POINTS_SGIS			= 0x809C

###############################################################################

# Extension #22
SGIS_sharpen_texture enum:
	LINEAR_SHARPEN_SGIS				= 0x80AD
	LINEAR_SHARPEN_ALPHA_SGIS			= 0x80AE
	LINEAR_SHARPEN_COLOR_SGIS			= 0x80AF
	SHARPEN_TEXTURE_FUNC_POINTS_SGIS		= 0x80B0

###############################################################################

# Extension #23
EXT_packed_pixels enum:
	UNSIGNED_BYTE_3_3_2_EXT				= 0x8032
	UNSIGNED_SHORT_4_4_4_4_EXT			= 0x8033
	UNSIGNED_SHORT_5_5_5_1_EXT			= 0x8034
	UNSIGNED_INT_8_8_8_8_EXT			= 0x8035
	UNSIGNED_INT_10_10_10_2_EXT			= 0x8036

###############################################################################

# Extension #24
SGIS_texture_lod enum:
	TEXTURE_MIN_LOD_SGIS				= 0x813A
	TEXTURE_MAX_LOD_SGIS				= 0x813B
	TEXTURE_BASE_LEVEL_SGIS				= 0x813C
	TEXTURE_MAX_LEVEL_SGIS				= 0x813D

###############################################################################

# Extension #25
SGIS_multisample enum:
	MULTISAMPLE_SGIS				= 0x809D # 1 I
	SAMPLE_ALPHA_TO_MASK_SGIS			= 0x809E # 1 I
	SAMPLE_ALPHA_TO_ONE_SGIS			= 0x809F # 1 I
	SAMPLE_MASK_SGIS				= 0x80A0 # 1 I
	1PASS_SGIS					= 0x80A1
	2PASS_0_SGIS					= 0x80A2
	2PASS_1_SGIS					= 0x80A3
	4PASS_0_SGIS					= 0x80A4
	4PASS_1_SGIS					= 0x80A5
	4PASS_2_SGIS					= 0x80A6
	4PASS_3_SGIS					= 0x80A7
	SAMPLE_BUFFERS_SGIS				= 0x80A8 # 1 I
	SAMPLES_SGIS					= 0x80A9 # 1 I
	SAMPLE_MASK_VALUE_SGIS				= 0x80AA # 1 F
	SAMPLE_MASK_INVERT_SGIS				= 0x80AB # 1 I
	SAMPLE_PATTERN_SGIS				= 0x80AC # 1 I

###############################################################################

# Extension #26 - no specification?
# SGIS_premultiply_blend enum:

##############################################################################

# Extension #27
# Diamond ships an otherwise identical IBM_rescale_normal extension;
#  Dan Brokenshire says this is deprecated and should not be advertised.
EXT_rescale_normal enum:
	RESCALE_NORMAL_EXT				= 0x803A # 1 I

###############################################################################

# Extension #28 - GLX_EXT_visual_info

###############################################################################

# Extension #29 - skipped

###############################################################################

# Extension #30
EXT_vertex_array enum:
	VERTEX_ARRAY_EXT				= 0x8074
	NORMAL_ARRAY_EXT				= 0x8075
	COLOR_ARRAY_EXT					= 0x8076
	INDEX_ARRAY_EXT					= 0x8077
	TEXTURE_COORD_ARRAY_EXT				= 0x8078
	EDGE_FLAG_ARRAY_EXT				= 0x8079
	VERTEX_ARRAY_SIZE_EXT				= 0x807A
	VERTEX_ARRAY_TYPE_EXT				= 0x807B
	VERTEX_ARRAY_STRIDE_EXT				= 0x807C
	VERTEX_ARRAY_COUNT_EXT				= 0x807D # 1 I
	NORMAL_ARRAY_TYPE_EXT				= 0x807E
	NORMAL_ARRAY_STRIDE_EXT				= 0x807F
	NORMAL_ARRAY_COUNT_EXT				= 0x8080 # 1 I
	COLOR_ARRAY_SIZE_EXT				= 0x8081
	COLOR_ARRAY_TYPE_EXT				= 0x8082
	COLOR_ARRAY_STRIDE_EXT				= 0x8083
	COLOR_ARRAY_COUNT_EXT				= 0x8084 # 1 I
	INDEX_ARRAY_TYPE_EXT				= 0x8085
	INDEX_ARRAY_STRIDE_EXT				= 0x8086
	INDEX_ARRAY_COUNT_EXT				= 0x8087 # 1 I
	TEXTURE_COORD_ARRAY_SIZE_EXT			= 0x8088
	TEXTURE_COORD_ARRAY_TYPE_EXT			= 0x8089
	TEXTURE_COORD_ARRAY_STRIDE_EXT			= 0x808A
	TEXTURE_COORD_ARRAY_COUNT_EXT			= 0x808B # 1 I
	EDGE_FLAG_ARRAY_STRIDE_EXT			= 0x808C
	EDGE_FLAG_ARRAY_COUNT_EXT			= 0x808D # 1 I
	VERTEX_ARRAY_POINTER_EXT			= 0x808E
	NORMAL_ARRAY_POINTER_EXT			= 0x808F
	COLOR_ARRAY_POINTER_EXT				= 0x8090
	INDEX_ARRAY_POINTER_EXT				= 0x8091
	TEXTURE_COORD_ARRAY_POINTER_EXT			= 0x8092
	EDGE_FLAG_ARRAY_POINTER_EXT			= 0x8093

###############################################################################

# Extension #31
EXT_misc_attribute enum:
#	 MISC_BIT					 = 0x????

###############################################################################

# Extension #32
SGIS_generate_mipmap enum:
	GENERATE_MIPMAP_SGIS				= 0x8191
	GENERATE_MIPMAP_HINT_SGIS			= 0x8192 # 1 I

###############################################################################

# Extension #33
SGIX_clipmap enum:
	LINEAR_CLIPMAP_LINEAR_SGIX			= 0x8170
	TEXTURE_CLIPMAP_CENTER_SGIX			= 0x8171
	TEXTURE_CLIPMAP_FRAME_SGIX			= 0x8172
	TEXTURE_CLIPMAP_OFFSET_SGIX			= 0x8173
	TEXTURE_CLIPMAP_VIRTUAL_DEPTH_SGIX		= 0x8174
	TEXTURE_CLIPMAP_LOD_OFFSET_SGIX			= 0x8175
	TEXTURE_CLIPMAP_DEPTH_SGIX			= 0x8176
	MAX_CLIPMAP_DEPTH_SGIX				= 0x8177 # 1 I
	MAX_CLIPMAP_VIRTUAL_DEPTH_SGIX			= 0x8178 # 1 I
	NEAREST_CLIPMAP_NEAREST_SGIX			= 0x844D
	NEAREST_CLIPMAP_LINEAR_SGIX			= 0x844E
	LINEAR_CLIPMAP_NEAREST_SGIX			= 0x844F

###############################################################################

# Extension #34
SGIX_shadow enum:
	TEXTURE_COMPARE_SGIX				= 0x819A
	TEXTURE_COMPARE_OPERATOR_SGIX			= 0x819B
	TEXTURE_LEQUAL_R_SGIX				= 0x819C
	TEXTURE_GEQUAL_R_SGIX				= 0x819D

###############################################################################

# Extension #35
SGIS_texture_edge_clamp enum:
	CLAMP_TO_EDGE_SGIS				= 0x812F

###############################################################################

# Extension #36
# Promoted to ARB_texture_border_clamp
# SGIS_texture_border_clamp

###############################################################################

# Extension #37
EXT_blend_minmax enum:
	FUNC_ADD_EXT					= 0x8006
	MIN_EXT						= 0x8007
	MAX_EXT						= 0x8008
	BLEND_EQUATION_EXT				= 0x8009 # 1 I

###############################################################################

# Extension #38
EXT_blend_subtract enum:
	FUNC_SUBTRACT_EXT				= 0x800A
	FUNC_REVERSE_SUBTRACT_EXT			= 0x800B

###############################################################################

# No new tokens
# Extension #39
EXT_blend_logic_op enum:

###############################################################################

# Extension #40 - GLX_SGI_swap_control
# Extension #41 - GLX_SGI_video_sync
# Extension #42 - GLX_SGI_make_current_read
# Extension #43 - GLX_SGIX_video_source
# Extension #44 - GLX_EXT_visual_rating

###############################################################################

# Extension #45
SGIX_interlace enum:
	INTERLACE_SGIX					= 0x8094 # 1 I

###############################################################################

# Extension #46
SGIX_pixel_tiles enum:
	PIXEL_TILE_BEST_ALIGNMENT_SGIX			= 0x813E # 1 I
	PIXEL_TILE_CACHE_INCREMENT_SGIX			= 0x813F # 1 I
	PIXEL_TILE_WIDTH_SGIX				= 0x8140 # 1 I
	PIXEL_TILE_HEIGHT_SGIX				= 0x8141 # 1 I
	PIXEL_TILE_GRID_WIDTH_SGIX			= 0x8142 # 1 I

	PIXEL_TILE_GRID_HEIGHT_SGIX			= 0x8143 # 1 I
	PIXEL_TILE_GRID_DEPTH_SGIX			= 0x8144 # 1 I
	PIXEL_TILE_CACHE_SIZE_SGIX			= 0x8145 # 1 I

###############################################################################

# Extension #47 - GLX_EXT_import_context

###############################################################################

# Extension #48 - skipped

###############################################################################

# Extension #49 - GLX_SGIX_fbconfig
# Extension #50 - GLX_SGIX_pbuffer

###############################################################################

# Extension #51
SGIS_texture_select enum:
	DUAL_ALPHA4_SGIS				= 0x8110
	DUAL_ALPHA8_SGIS				= 0x8111
	DUAL_ALPHA12_SGIS				= 0x8112
	DUAL_ALPHA16_SGIS				= 0x8113
	DUAL_LUMINANCE4_SGIS				= 0x8114
	DUAL_LUMINANCE8_SGIS				= 0x8115
	DUAL_LUMINANCE12_SGIS				= 0x8116
	DUAL_LUMINANCE16_SGIS				= 0x8117
	DUAL_INTENSITY4_SGIS				= 0x8118
	DUAL_INTENSITY8_SGIS				= 0x8119
	DUAL_INTENSITY12_SGIS				= 0x811A
	DUAL_INTENSITY16_SGIS				= 0x811B
	DUAL_LUMINANCE_ALPHA4_SGIS			= 0x811C
	DUAL_LUMINANCE_ALPHA8_SGIS			= 0x811D
	QUAD_ALPHA4_SGIS				= 0x811E
	QUAD_ALPHA8_SGIS				= 0x811F
	QUAD_LUMINANCE4_SGIS				= 0x8120
	QUAD_LUMINANCE8_SGIS				= 0x8121
	QUAD_INTENSITY4_SGIS				= 0x8122
	QUAD_INTENSITY8_SGIS				= 0x8123
	DUAL_TEXTURE_SELECT_SGIS			= 0x8124
	QUAD_TEXTURE_SELECT_SGIS			= 0x8125

###############################################################################

# Extension #52
SGIX_sprite enum:
	SPRITE_SGIX					= 0x8148 # 1 I
	SPRITE_MODE_SGIX				= 0x8149 # 1 I
	SPRITE_AXIS_SGIX				= 0x814A # 3 F
	SPRITE_TRANSLATION_SGIX				= 0x814B # 3 F
	SPRITE_AXIAL_SGIX				= 0x814C
	SPRITE_OBJECT_ALIGNED_SGIX			= 0x814D
	SPRITE_EYE_ALIGNED_SGIX				= 0x814E

###############################################################################

# Extension #53
SGIX_texture_multi_buffer enum:
	TEXTURE_MULTI_BUFFER_HINT_SGIX			= 0x812E

###############################################################################

# Extension #54
# Promoted to ARB_point_parameters
# {SGIS,EXT}_point_parameters

###############################################################################

# Extension #55
SGIX_instruments enum:
	INSTRUMENT_BUFFER_POINTER_SGIX			= 0x8180
	INSTRUMENT_MEASUREMENTS_SGIX			= 0x8181 # 1 I

###############################################################################

# Extension #56
SGIX_texture_scale_bias enum:
	POST_TEXTURE_FILTER_BIAS_SGIX			= 0x8179
	POST_TEXTURE_FILTER_SCALE_SGIX			= 0x817A
	POST_TEXTURE_FILTER_BIAS_RANGE_SGIX		= 0x817B # 2 F
	POST_TEXTURE_FILTER_SCALE_RANGE_SGIX		= 0x817C # 2 F

###############################################################################

# Extension #57
SGIX_framezoom enum:
	FRAMEZOOM_SGIX					= 0x818B # 1 I
	FRAMEZOOM_FACTOR_SGIX				= 0x818C # 1 I
	MAX_FRAMEZOOM_FACTOR_SGIX			= 0x818D # 1 I

###############################################################################

# No new tokens
# Extension #58
SGIX_tag_sample_buffer enum:

###############################################################################

# Extension #59
FfdMaskSGIX enum:
	TEXTURE_DEFORMATION_BIT_SGIX			= 0x00000001
	GEOMETRY_DEFORMATION_BIT_SGIX			= 0x00000002
SGIX_polynomial_ffd enum:
	GEOMETRY_DEFORMATION_SGIX			= 0x8194
	TEXTURE_DEFORMATION_SGIX			= 0x8195
	DEFORMATIONS_MASK_SGIX				= 0x8196 # 1 I
	MAX_DEFORMATION_ORDER_SGIX			= 0x8197

###############################################################################

# Extension #60
SGIX_reference_plane enum:
	REFERENCE_PLANE_SGIX				= 0x817D # 1 I
	REFERENCE_PLANE_EQUATION_SGIX			= 0x817E # 4 F

###############################################################################

# No new tokens
# Extension #61
SGIX_flush_raster enum:

###############################################################################

# Extension #62 - GLX_SGIX_cushion

###############################################################################

# Extension #63
SGIX_depth_texture enum:
	DEPTH_COMPONENT16_SGIX				= 0x81A5
	DEPTH_COMPONENT24_SGIX				= 0x81A6
	DEPTH_COMPONENT32_SGIX				= 0x81A7

###############################################################################

# Extension #64
SGIS_fog_function enum:
	FOG_FUNC_SGIS					= 0x812A
	FOG_FUNC_POINTS_SGIS				= 0x812B # 1 I
	MAX_FOG_FUNC_POINTS_SGIS			= 0x812C # 1 I

###############################################################################

# Extension #65
SGIX_fog_offset enum:
	FOG_OFFSET_SGIX					= 0x8198 # 1 I
	FOG_OFFSET_VALUE_SGIX				= 0x8199 # 4 F

###############################################################################

# Extension #66
HP_image_transform enum:
	IMAGE_SCALE_X_HP				= 0x8155
	IMAGE_SCALE_Y_HP				= 0x8156
	IMAGE_TRANSLATE_X_HP				= 0x8157
	IMAGE_TRANSLATE_Y_HP				= 0x8158
	IMAGE_ROTATE_ANGLE_HP				= 0x8159
	IMAGE_ROTATE_ORIGIN_X_HP			= 0x815A
	IMAGE_ROTATE_ORIGIN_Y_HP			= 0x815B
	IMAGE_MAG_FILTER_HP				= 0x815C
	IMAGE_MIN_FILTER_HP				= 0x815D
	IMAGE_CUBIC_WEIGHT_HP				= 0x815E
	CUBIC_HP					= 0x815F
	AVERAGE_HP					= 0x8160
	IMAGE_TRANSFORM_2D_HP				= 0x8161
	POST_IMAGE_TRANSFORM_COLOR_TABLE_HP		= 0x8162
	PROXY_POST_IMAGE_TRANSFORM_COLOR_TABLE_HP	= 0x8163

###############################################################################

# Extension #67
HP_convolution_border_modes enum:
	IGNORE_BORDER_HP				= 0x8150
	CONSTANT_BORDER_HP				= 0x8151
	REPLICATE_BORDER_HP				= 0x8153
	CONVOLUTION_BORDER_COLOR_HP			= 0x8154

###############################################################################

#@ Unknown tokens
# Extension #68
INGR_palette_buffer enum:

###############################################################################

# Extension #69
SGIX_texture_add_env enum:
	TEXTURE_ENV_BIAS_SGIX				= 0x80BE

###############################################################################

# Extension #70 - skipped
# Extension #71 - skipped
# Extension #72 - skipped
# Extension #73 - skipped

###############################################################################

# No new tokens
# Extension #74
EXT_color_subtable enum:

###############################################################################

# Extension #75 - GLU_EXT_object_space_tess

###############################################################################

# Extension #76
PGI_vertex_hints enum:
	VERTEX_DATA_HINT_PGI				= 0x1A22A
	VERTEX_CONSISTENT_HINT_PGI			= 0x1A22B
	MATERIAL_SIDE_HINT_PGI				= 0x1A22C
	MAX_VERTEX_HINT_PGI				= 0x1A22D
	COLOR3_BIT_PGI					= 0x00010000
	COLOR4_BIT_PGI					= 0x00020000
	EDGEFLAG_BIT_PGI				= 0x00040000
	INDEX_BIT_PGI					= 0x00080000
	MAT_AMBIENT_BIT_PGI				= 0x00100000
	MAT_AMBIENT_AND_DIFFUSE_BIT_PGI			= 0x00200000
	MAT_DIFFUSE_BIT_PGI				= 0x00400000
	MAT_EMISSION_BIT_PGI				= 0x00800000
	MAT_COLOR_INDEXES_BIT_PGI			= 0x01000000
	MAT_SHININESS_BIT_PGI				= 0x02000000
	MAT_SPECULAR_BIT_PGI				= 0x04000000
	NORMAL_BIT_PGI					= 0x08000000
	TEXCOORD1_BIT_PGI				= 0x10000000
	TEXCOORD2_BIT_PGI				= 0x20000000
	TEXCOORD3_BIT_PGI				= 0x40000000
	TEXCOORD4_BIT_PGI				= 0x80000000
	VERTEX23_BIT_PGI				= 0x00000004
	VERTEX4_BIT_PGI					= 0x00000008

###############################################################################

# Extension #77
PGI_misc_hints enum:
	PREFER_DOUBLEBUFFER_HINT_PGI			= 0x1A1F8
	CONSERVE_MEMORY_HINT_PGI			= 0x1A1FD
	RECLAIM_MEMORY_HINT_PGI				= 0x1A1FE
	NATIVE_GRAPHICS_HANDLE_PGI			= 0x1A202
	NATIVE_GRAPHICS_BEGIN_HINT_PGI			= 0x1A203
	NATIVE_GRAPHICS_END_HINT_PGI			= 0x1A204
	ALWAYS_FAST_HINT_PGI				= 0x1A20C
	ALWAYS_SOFT_HINT_PGI				= 0x1A20D
	ALLOW_DRAW_OBJ_HINT_PGI				= 0x1A20E
	ALLOW_DRAW_WIN_HINT_PGI				= 0x1A20F
	ALLOW_DRAW_FRG_HINT_PGI				= 0x1A210
	ALLOW_DRAW_MEM_HINT_PGI				= 0x1A211
	STRICT_DEPTHFUNC_HINT_PGI			= 0x1A216
	STRICT_LIGHTING_HINT_PGI			= 0x1A217
	STRICT_SCISSOR_HINT_PGI				= 0x1A218
	FULL_STIPPLE_HINT_PGI				= 0x1A219
	CLIP_NEAR_HINT_PGI				= 0x1A220
	CLIP_FAR_HINT_PGI				= 0x1A221
	WIDE_LINE_HINT_PGI				= 0x1A222
	BACK_NORMALS_HINT_PGI				= 0x1A223

###############################################################################

# Extension #78
EXT_paletted_texture enum:
	COLOR_INDEX1_EXT				= 0x80E2
	COLOR_INDEX2_EXT				= 0x80E3
	COLOR_INDEX4_EXT				= 0x80E4
	COLOR_INDEX8_EXT				= 0x80E5
	COLOR_INDEX12_EXT				= 0x80E6
	COLOR_INDEX16_EXT				= 0x80E7
	TEXTURE_INDEX_SIZE_EXT				= 0x80ED

###############################################################################

# Extension #79
EXT_clip_volume_hint enum:
	CLIP_VOLUME_CLIPPING_HINT_EXT			= 0x80F0

###############################################################################

# Extension #80
SGIX_list_priority enum:
	LIST_PRIORITY_SGIX				= 0x8182

###############################################################################

# Extension #81
SGIX_ir_instrument1 enum:
	IR_INSTRUMENT1_SGIX				= 0x817F # 1 I

###############################################################################

# Extension #82
SGIX_calligraphic_fragment enum:
	CALLIGRAPHIC_FRAGMENT_SGIX			= 0x8183 # 1 I

###############################################################################

# Extension #83 - GLX_SGIX_video_resize

###############################################################################

# Extension #84
SGIX_texture_lod_bias enum:
	TEXTURE_LOD_BIAS_S_SGIX				= 0x818E
	TEXTURE_LOD_BIAS_T_SGIX				= 0x818F
	TEXTURE_LOD_BIAS_R_SGIX				= 0x8190

###############################################################################

# Extension #85 - skipped

###############################################################################

# Extension #86 - GLX_SGIX_dmbuffer

###############################################################################

# Extension #87 - skipped
# Extension #88 - skipped
# Extension #89 - skipped

###############################################################################

# Extension #90
SGIX_shadow_ambient enum:
	SHADOW_AMBIENT_SGIX				= 0x80BF

###############################################################################

# Extension #91 - GLX_SGIX_swap_group
# Extension #92 - GLX_SGIX_swap_barrier

###############################################################################

# No new tokens
# Extension #93
EXT_index_texture enum:

###############################################################################

# Extension #94
# Promoted from SGI?
EXT_index_material enum:
	INDEX_MATERIAL_EXT				= 0x81B8
	INDEX_MATERIAL_PARAMETER_EXT			= 0x81B9
	INDEX_MATERIAL_FACE_EXT				= 0x81BA

###############################################################################

# Extension #95
# Promoted from SGI?
EXT_index_func enum:
	INDEX_TEST_EXT					= 0x81B5
	INDEX_TEST_FUNC_EXT				= 0x81B6
	INDEX_TEST_REF_EXT				= 0x81B7

###############################################################################

# Extension #96
# Promoted from SGI?
EXT_index_array_formats enum:
	IUI_V2F_EXT					= 0x81AD
	IUI_V3F_EXT					= 0x81AE
	IUI_N3F_V2F_EXT					= 0x81AF
	IUI_N3F_V3F_EXT					= 0x81B0
	T2F_IUI_V2F_EXT					= 0x81B1
	T2F_IUI_V3F_EXT					= 0x81B2
	T2F_IUI_N3F_V2F_EXT				= 0x81B3
	T2F_IUI_N3F_V3F_EXT				= 0x81B4

###############################################################################

# Extension #97
# Promoted from SGI?
EXT_compiled_vertex_array enum:
	ARRAY_ELEMENT_LOCK_FIRST_EXT			= 0x81A8
	ARRAY_ELEMENT_LOCK_COUNT_EXT			= 0x81A9

###############################################################################

# Extension #98
# Promoted from SGI?
EXT_cull_vertex enum:
	CULL_VERTEX_EXT					= 0x81AA
	CULL_VERTEX_EYE_POSITION_EXT			= 0x81AB
	CULL_VERTEX_OBJECT_POSITION_EXT			= 0x81AC

###############################################################################

# Extension #99 - skipped

###############################################################################

# Extension #100 - GLU_EXT_nurbs_tessellator

###############################################################################

# Extension #101
SGIX_ycrcb enum:
	YCRCB_422_SGIX					= 0x81BB
	YCRCB_444_SGIX					= 0x81BC

###############################################################################

# Extension #102
SGIX_fragment_lighting enum:
	FRAGMENT_LIGHTING_SGIX				= 0x8400 # 1 I
	FRAGMENT_COLOR_MATERIAL_SGIX			= 0x8401 # 1 I
	FRAGMENT_COLOR_MATERIAL_FACE_SGIX		= 0x8402 # 1 I
	FRAGMENT_COLOR_MATERIAL_PARAMETER_SGIX		= 0x8403 # 1 I
	MAX_FRAGMENT_LIGHTS_SGIX			= 0x8404 # 1 I
	MAX_ACTIVE_LIGHTS_SGIX				= 0x8405 # 1 I
	CURRENT_RASTER_NORMAL_SGIX			= 0x8406 # 1 I
	LIGHT_ENV_MODE_SGIX				= 0x8407 # 1 I
	FRAGMENT_LIGHT_MODEL_LOCAL_VIEWER_SGIX		= 0x8408 # 1 I
	FRAGMENT_LIGHT_MODEL_TWO_SIDE_SGIX		= 0x8409 # 1 I
	FRAGMENT_LIGHT_MODEL_AMBIENT_SGIX		= 0x840A # 4 F
	FRAGMENT_LIGHT_MODEL_NORMAL_INTERPOLATION_SGIX	= 0x840B # 1 I
	FRAGMENT_LIGHT0_SGIX				= 0x840C # 1 I
	FRAGMENT_LIGHT1_SGIX				= 0x840D
	FRAGMENT_LIGHT2_SGIX				= 0x840E
	FRAGMENT_LIGHT3_SGIX				= 0x840F
	FRAGMENT_LIGHT4_SGIX				= 0x8410
	FRAGMENT_LIGHT5_SGIX				= 0x8411
	FRAGMENT_LIGHT6_SGIX				= 0x8412
	FRAGMENT_LIGHT7_SGIX				= 0x8413

# SGIX_fragment_lighting_future_use: 0x8414-0x842B

###############################################################################

# Extension #103 - skipped
# Extension #104 - skipped
# Extension #105 - skipped
# Extension #106 - skipped
# Extension #107 - skipped
# Extension #108 - skipped
# Extension #109 - skipped

###############################################################################

# Extension #110
IBM_rasterpos_clip enum:
	RASTER_POSITION_UNCLIPPED_IBM			= 0x19262

###############################################################################

# Extension #111
HP_texture_lighting enum:
	TEXTURE_LIGHTING_MODE_HP			= 0x8167
	TEXTURE_POST_SPECULAR_HP			= 0x8168
	TEXTURE_PRE_SPECULAR_HP				= 0x8169

###############################################################################

# Extension #112
EXT_draw_range_elements enum:
	MAX_ELEMENTS_VERTICES_EXT			= 0x80E8
	MAX_ELEMENTS_INDICES_EXT			= 0x80E9

###############################################################################

# Extension #113
WIN_phong_shading enum:
	PHONG_WIN					= 0x80EA
	PHONG_HINT_WIN					= 0x80EB

###############################################################################

# Extension #114
WIN_specular_fog enum:
	FOG_SPECULAR_TEXTURE_WIN			= 0x80EC

###############################################################################

# Extension #115 - skipped
# Extension #116 - skipped

###############################################################################

# Extension #117
EXT_light_texture enum:
	FRAGMENT_MATERIAL_EXT				= 0x8349
	FRAGMENT_NORMAL_EXT				= 0x834A
	FRAGMENT_COLOR_EXT				= 0x834C
	ATTENUATION_EXT					= 0x834D
	SHADOW_ATTENUATION_EXT				= 0x834E
	TEXTURE_APPLICATION_MODE_EXT			= 0x834F # 1 I
	TEXTURE_LIGHT_EXT				= 0x8350 # 1 I
	TEXTURE_MATERIAL_FACE_EXT			= 0x8351 # 1 I
	TEXTURE_MATERIAL_PARAMETER_EXT			= 0x8352 # 1 I
	use EXT_fog_coord FRAGMENT_DEPTH_EXT

###############################################################################

# Extension #118 - skipped

###############################################################################

# Extension #119
SGIX_blend_alpha_minmax enum:
	ALPHA_MIN_SGIX					= 0x8320
	ALPHA_MAX_SGIX					= 0x8321

###############################################################################

# Extension #120 - skipped
# Extension #121 - skipped
# Extension #122 - skipped
# Extension #123 - skipped
# Extension #124 - skipped
# Extension #125 - skipped

###############################################################################

# Extension #126
SGIX_impact_pixel_texture enum:
	PIXEL_TEX_GEN_Q_CEILING_SGIX			= 0x8184
	PIXEL_TEX_GEN_Q_ROUND_SGIX			= 0x8185
	PIXEL_TEX_GEN_Q_FLOOR_SGIX			= 0x8186
	PIXEL_TEX_GEN_ALPHA_REPLACE_SGIX		= 0x8187
	PIXEL_TEX_GEN_ALPHA_NO_REPLACE_SGIX		= 0x8188
	PIXEL_TEX_GEN_ALPHA_LS_SGIX			= 0x8189
	PIXEL_TEX_GEN_ALPHA_MS_SGIX			= 0x818A

###############################################################################

# Extension #127 - skipped
# Extension #128 - skipped

###############################################################################

# Extension #129
EXT_bgra enum:
	BGR_EXT						= 0x80E0
	BGRA_EXT					= 0x80E1

###############################################################################

# Extension #130 - skipped
# Extension #131 - skipped

###############################################################################

# Extension #132
SGIX_async enum:
	ASYNC_MARKER_SGIX				= 0x8329

###############################################################################

# Extension #133
SGIX_async_pixel enum:
	ASYNC_TEX_IMAGE_SGIX				= 0x835C
	ASYNC_DRAW_PIXELS_SGIX				= 0x835D
	ASYNC_READ_PIXELS_SGIX				= 0x835E
	MAX_ASYNC_TEX_IMAGE_SGIX			= 0x835F
	MAX_ASYNC_DRAW_PIXELS_SGIX			= 0x8360
	MAX_ASYNC_READ_PIXELS_SGIX			= 0x8361

###############################################################################

# Extension #134
SGIX_async_histogram enum:
	ASYNC_HISTOGRAM_SGIX				= 0x832C
	MAX_ASYNC_HISTOGRAM_SGIX			= 0x832D

###############################################################################

# Intel has not implemented this; enums never assigned
# Extension #135
INTEL_texture_scissor enum:
#	 TEXTURE_SCISSOR_INTEL				 = 0x????
#	 TEXTURE_SCISSOR_INTEL				 = 0x????
#	 TEXTURE_SCISSOR_FUNC_INTEL			 = 0x????
#	 TEXTURE_SCISSOR_S_INTEL			 = 0x????
#	 TEXTURE_SCISSOR_T_INTEL			 = 0x????
#	 TEXTURE_SCISSOR_R_INTEL			 = 0x????

###############################################################################

# Extension #136
INTEL_parallel_arrays enum:
	PARALLEL_ARRAYS_INTEL				= 0x83F4
	VERTEX_ARRAY_PARALLEL_POINTERS_INTEL		= 0x83F5
	NORMAL_ARRAY_PARALLEL_POINTERS_INTEL		= 0x83F6
	COLOR_ARRAY_PARALLEL_POINTERS_INTEL		= 0x83F7
	TEXTURE_COORD_ARRAY_PARALLEL_POINTERS_INTEL	= 0x83F8

###############################################################################

# Extension #137
HP_occlusion_test enum:
	OCCLUSION_TEST_HP				= 0x8165
	OCCLUSION_TEST_RESULT_HP			= 0x8166

###############################################################################

# Extension #138
EXT_pixel_transform enum:
	PIXEL_TRANSFORM_2D_EXT				= 0x8330
	PIXEL_MAG_FILTER_EXT				= 0x8331
	PIXEL_MIN_FILTER_EXT				= 0x8332
	PIXEL_CUBIC_WEIGHT_EXT				= 0x8333
	CUBIC_EXT					= 0x8334
	AVERAGE_EXT					= 0x8335
	PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT		= 0x8336
	MAX_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT		= 0x8337
	PIXEL_TRANSFORM_2D_MATRIX_EXT			= 0x8338

###############################################################################

# Unknown enum values
# Extension #139
EXT_pixel_transform_color_table enum:

#	 PIXEL_TRANSFORM_COLOR_TABLE_EXT
#	 PROXY_PIXEL_TRANSFORM_COLOR_TABLE_EXT

###############################################################################

# Extension #140 - skipped

###############################################################################

# Extension #141
EXT_shared_texture_palette enum:
	SHARED_TEXTURE_PALETTE_EXT			= 0x81FB

###############################################################################

# Extension #142 - GLX_SGIS_blended_overlay

###############################################################################

# Extension #143 - SGIS_shared_multisample
#	MULTISAMPLE_SUB_RECT_POSITION_SGIS		= <TBD>
#	MULTISAMPLE_SUB_RECT_DIMS_SGIS			= <TBD>

###############################################################################

# Extension #144
EXT_separate_specular_color enum:
	LIGHT_MODEL_COLOR_CONTROL_EXT			= 0x81F8
	SINGLE_COLOR_EXT				= 0x81F9
	SEPARATE_SPECULAR_COLOR_EXT			= 0x81FA

###############################################################################

# Extension #145
EXT_secondary_color enum:
	COLOR_SUM_EXT					= 0x8458 # 1 I
	CURRENT_SECONDARY_COLOR_EXT			= 0x8459 # 3 F
	SECONDARY_COLOR_ARRAY_SIZE_EXT			= 0x845A # 1 I
	SECONDARY_COLOR_ARRAY_TYPE_EXT			= 0x845B # 1 I
	SECONDARY_COLOR_ARRAY_STRIDE_EXT		= 0x845C # 1 I
	SECONDARY_COLOR_ARRAY_POINTER_EXT		= 0x845D
	SECONDARY_COLOR_ARRAY_EXT			= 0x845E # 1 I

###############################################################################

# Dead extension - EXT_texture_env_combine was finished instead
# Extension #146
#EXT_texture_env enum:

###############################################################################

# Extension #147
EXT_texture_perturb_normal enum:
	PERTURB_EXT					= 0x85AE
	TEXTURE_NORMAL_EXT				= 0x85AF

###############################################################################

# No new tokens
# Extension #148
# Diamond ships an otherwise identical IBM_multi_draw_arrays extension;
#  Dan Brokenshire says this is deprecated and should not be advertised.
EXT_multi_draw_arrays enum:

###############################################################################

# Extension #149
EXT_fog_coord enum:
	FOG_COORDINATE_SOURCE_EXT			= 0x8450 # 1 I
	FOG_COORDINATE_EXT				= 0x8451
	FRAGMENT_DEPTH_EXT				= 0x8452
	CURRENT_FOG_COORDINATE_EXT			= 0x8453 # 1 F
	FOG_COORDINATE_ARRAY_TYPE_EXT			= 0x8454 # 1 I
	FOG_COORDINATE_ARRAY_STRIDE_EXT			= 0x8455 # 1 I
	FOG_COORDINATE_ARRAY_POINTER_EXT		= 0x8456
	FOG_COORDINATE_ARRAY_EXT			= 0x8457 # 1 I

###############################################################################

# Extension #150 - skipped
# Extension #151 - skipped
# Extension #152 - skipped
# Extension #153 - skipped
# Extension #154 - skipped

###############################################################################

# Extension #155
REND_screen_coordinates enum:
	SCREEN_COORDINATES_REND				= 0x8490
	INVERTED_SCREEN_W_REND				= 0x8491

###############################################################################

# Extension #156
EXT_coordinate_frame enum:
	TANGENT_ARRAY_EXT				= 0x8439
	BINORMAL_ARRAY_EXT				= 0x843A
	CURRENT_TANGENT_EXT				= 0x843B
	CURRENT_BINORMAL_EXT				= 0x843C
	TANGENT_ARRAY_TYPE_EXT				= 0x843E
	TANGENT_ARRAY_STRIDE_EXT			= 0x843F
	BINORMAL_ARRAY_TYPE_EXT				= 0x8440
	BINORMAL_ARRAY_STRIDE_EXT			= 0x8441
	TANGENT_ARRAY_POINTER_EXT			= 0x8442
	BINORMAL_ARRAY_POINTER_EXT			= 0x8443
	MAP1_TANGENT_EXT				= 0x8444
	MAP2_TANGENT_EXT				= 0x8445
	MAP1_BINORMAL_EXT				= 0x8446
	MAP2_BINORMAL_EXT				= 0x8447

###############################################################################

# Extension #157 - skipped

###############################################################################

# Extension #158
EXT_texture_env_combine enum:
	COMBINE_EXT					= 0x8570
	COMBINE_RGB_EXT					= 0x8571
	COMBINE_ALPHA_EXT				= 0x8572
	RGB_SCALE_EXT					= 0x8573
	ADD_SIGNED_EXT					= 0x8574
	INTERPOLATE_EXT					= 0x8575
	CONSTANT_EXT					= 0x8576
	PRIMARY_COLOR_EXT				= 0x8577
	PREVIOUS_EXT					= 0x8578
	SOURCE0_RGB_EXT					= 0x8580
	SOURCE1_RGB_EXT					= 0x8581
	SOURCE2_RGB_EXT					= 0x8582
	SOURCE0_ALPHA_EXT				= 0x8588
	SOURCE1_ALPHA_EXT				= 0x8589
	SOURCE2_ALPHA_EXT				= 0x858A
	OPERAND0_RGB_EXT				= 0x8590
	OPERAND1_RGB_EXT				= 0x8591
	OPERAND2_RGB_EXT				= 0x8592
	OPERAND0_ALPHA_EXT				= 0x8598
	OPERAND1_ALPHA_EXT				= 0x8599
	OPERAND2_ALPHA_EXT				= 0x859A

###############################################################################

# Extension #159
APPLE_specular_vector enum:
	LIGHT_MODEL_SPECULAR_VECTOR_APPLE		= 0x85B0

###############################################################################

# Extension #160
APPLE_transform_hint enum:
	TRANSFORM_HINT_APPLE				= 0x85B1

###############################################################################

# Extension #161
SGIX_fog_scale enum:
	FOG_SCALE_SGIX					= 0x81FC
	FOG_SCALE_VALUE_SGIX				= 0x81FD

###############################################################################

# Extension #162 - skipped

###############################################################################

# Extension #163
SUNX_constant_data enum:
	UNPACK_CONSTANT_DATA_SUNX			= 0x81D5
	TEXTURE_CONSTANT_DATA_SUNX			= 0x81D6

###############################################################################

# Extension #164
SUN_global_alpha enum:
	GLOBAL_ALPHA_SUN				= 0x81D9
	GLOBAL_ALPHA_FACTOR_SUN				= 0x81DA

###############################################################################

# Extension #165
SUN_triangle_list enum:
	RESTART_SUN					= 0x0001
	REPLACE_MIDDLE_SUN				= 0x0002
	REPLACE_OLDEST_SUN				= 0x0003
	TRIANGLE_LIST_SUN				= 0x81D7
	REPLACEMENT_CODE_SUN				= 0x81D8
	REPLACEMENT_CODE_ARRAY_SUN			= 0x85C0
	REPLACEMENT_CODE_ARRAY_TYPE_SUN			= 0x85C1
	REPLACEMENT_CODE_ARRAY_STRIDE_SUN		= 0x85C2
	REPLACEMENT_CODE_ARRAY_POINTER_SUN		= 0x85C3
	R1UI_V3F_SUN					= 0x85C4
	R1UI_C4UB_V3F_SUN				= 0x85C5
	R1UI_C3F_V3F_SUN				= 0x85C6
	R1UI_N3F_V3F_SUN				= 0x85C7
	R1UI_C4F_N3F_V3F_SUN				= 0x85C8
	R1UI_T2F_V3F_SUN				= 0x85C9
	R1UI_T2F_N3F_V3F_SUN				= 0x85CA
	R1UI_T2F_C4F_N3F_V3F_SUN			= 0x85CB

###############################################################################

# No new tokens
# Extension #166
SUN_vertex enum:

###############################################################################

# Extension #167 - WGL_EXT_display_color_table
# Extension #168 - WGL_EXT_extensions_string
# Extension #169 - WGL_EXT_make_current_read
# Extension #170 - WGL_EXT_pixel_format
# Extension #171 - WGL_EXT_pbuffer
# Extension #172 - WGL_EXT_swap_control

###############################################################################

# Extension #173
EXT_blend_func_separate enum:
	BLEND_DST_RGB_EXT				= 0x80C8
	BLEND_SRC_RGB_EXT				= 0x80C9
	BLEND_DST_ALPHA_EXT				= 0x80CA
	BLEND_SRC_ALPHA_EXT				= 0x80CB

###############################################################################

# Extension #174
INGR_color_clamp enum:
	RED_MIN_CLAMP_INGR				= 0x8560
	GREEN_MIN_CLAMP_INGR				= 0x8561
	BLUE_MIN_CLAMP_INGR				= 0x8562
	ALPHA_MIN_CLAMP_INGR				= 0x8563
	RED_MAX_CLAMP_INGR				= 0x8564
	GREEN_MAX_CLAMP_INGR				= 0x8565
	BLUE_MAX_CLAMP_INGR				= 0x8566
	ALPHA_MAX_CLAMP_INGR				= 0x8567

###############################################################################

# Extension #175
INGR_interlace_read enum:
	INTERLACE_READ_INGR				= 0x8568

###############################################################################

# Extension #176
EXT_stencil_wrap enum:
	INCR_WRAP_EXT					= 0x8507
	DECR_WRAP_EXT					= 0x8508

###############################################################################

# Extension #177 - skipped

###############################################################################

# Extension #178
EXT_422_pixels enum:
	422_EXT						= 0x80CC
	422_REV_EXT					= 0x80CD
	422_AVERAGE_EXT					= 0x80CE
	422_REV_AVERAGE_EXT				= 0x80CF

###############################################################################

# Extension #179
NV_texgen_reflection enum:
	NORMAL_MAP_NV					= 0x8511
	REFLECTION_MAP_NV				= 0x8512

###############################################################################

# Extension #180 - skipped
# Extension #181 - skipped

###############################################################################

# Is this shipping? No extension number assigned.
# Extension #?
EXT_texture_cube_map enum:
	NORMAL_MAP_EXT					= 0x8511
	REFLECTION_MAP_EXT				= 0x8512
	TEXTURE_CUBE_MAP_EXT				= 0x8513
	TEXTURE_BINDING_CUBE_MAP_EXT			= 0x8514
	TEXTURE_CUBE_MAP_POSITIVE_X_EXT			= 0x8515
	TEXTURE_CUBE_MAP_NEGATIVE_X_EXT			= 0x8516
	TEXTURE_CUBE_MAP_POSITIVE_Y_EXT			= 0x8517
	TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT			= 0x8518
	TEXTURE_CUBE_MAP_POSITIVE_Z_EXT			= 0x8519
	TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT			= 0x851A
	PROXY_TEXTURE_CUBE_MAP_EXT			= 0x851B
	MAX_CUBE_MAP_TEXTURE_SIZE_EXT			= 0x851C

###############################################################################

# Extension #182
SUN_convolution_border_modes enum:
	WRAP_BORDER_SUN					= 0x81D4

###############################################################################

# Extension #183 - GLX_SUN_transparent_index

###############################################################################

# Extension #184 - skipped

###############################################################################

# No new tokens
# Extension #185
EXT_texture_env_add enum:

###############################################################################

# Extension #186
EXT_texture_lod_bias enum:
	MAX_TEXTURE_LOD_BIAS_EXT			= 0x84FD
	TEXTURE_FILTER_CONTROL_EXT			= 0x8500
	TEXTURE_LOD_BIAS_EXT				= 0x8501

###############################################################################

# Extension #187
EXT_texture_filter_anisotropic enum:
	TEXTURE_MAX_ANISOTROPY_EXT			= 0x84FE
	MAX_TEXTURE_MAX_ANISOTROPY_EXT			= 0x84FF

###############################################################################

# Extension #188
EXT_vertex_weighting enum:
	MODELVIEW0_STACK_DEPTH_EXT			= GL_MODELVIEW_STACK_DEPTH
	MODELVIEW1_STACK_DEPTH_EXT			= 0x8502
	MODELVIEW0_MATRIX_EXT				= GL_MODELVIEW_MATRIX
	MODELVIEW1_MATRIX_EXT				= 0x8506
	VERTEX_WEIGHTING_EXT				= 0x8509
	MODELVIEW0_EXT					= GL_MODELVIEW
	MODELVIEW1_EXT					= 0x850A
	CURRENT_VERTEX_WEIGHT_EXT			= 0x850B
	VERTEX_WEIGHT_ARRAY_EXT				= 0x850C
	VERTEX_WEIGHT_ARRAY_SIZE_EXT			= 0x850D
	VERTEX_WEIGHT_ARRAY_TYPE_EXT			= 0x850E
	VERTEX_WEIGHT_ARRAY_STRIDE_EXT			= 0x850F
	VERTEX_WEIGHT_ARRAY_POINTER_EXT			= 0x8510

###############################################################################

# Extension #189
NV_light_max_exponent enum:
	MAX_SHININESS_NV				= 0x8504
	MAX_SPOT_EXPONENT_NV				= 0x8505

###############################################################################

# Extension #190
NV_vertex_array_range enum:
	VERTEX_ARRAY_RANGE_NV				= 0x851D
	VERTEX_ARRAY_RANGE_LENGTH_NV			= 0x851E
	VERTEX_ARRAY_RANGE_VALID_NV			= 0x851F
	MAX_VERTEX_ARRAY_RANGE_ELEMENT_NV		= 0x8520
	VERTEX_ARRAY_RANGE_POINTER_NV			= 0x8521

###############################################################################

# Extension #191
NV_register_combiners enum:
	REGISTER_COMBINERS_NV				= 0x8522
	VARIABLE_A_NV					= 0x8523
	VARIABLE_B_NV					= 0x8524
	VARIABLE_C_NV					= 0x8525
	VARIABLE_D_NV					= 0x8526
	VARIABLE_E_NV					= 0x8527
	VARIABLE_F_NV					= 0x8528
	VARIABLE_G_NV					= 0x8529
	CONSTANT_COLOR0_NV				= 0x852A
	CONSTANT_COLOR1_NV				= 0x852B
	PRIMARY_COLOR_NV				= 0x852C
	SECONDARY_COLOR_NV				= 0x852D
	SPARE0_NV					= 0x852E
	SPARE1_NV					= 0x852F
	DISCARD_NV					= 0x8530
	E_TIMES_F_NV					= 0x8531
	SPARE0_PLUS_SECONDARY_COLOR_NV			= 0x8532
	UNSIGNED_IDENTITY_NV				= 0x8536
	UNSIGNED_INVERT_NV				= 0x8537
	EXPAND_NORMAL_NV				= 0x8538
	EXPAND_NEGATE_NV				= 0x8539
	HALF_BIAS_NORMAL_NV				= 0x853A
	HALF_BIAS_NEGATE_NV				= 0x853B
	SIGNED_IDENTITY_NV				= 0x853C
	SIGNED_NEGATE_NV				= 0x853D
	SCALE_BY_TWO_NV					= 0x853E
	SCALE_BY_FOUR_NV				= 0x853F
	SCALE_BY_ONE_HALF_NV				= 0x8540
	BIAS_BY_NEGATIVE_ONE_HALF_NV			= 0x8541
	COMBINER_INPUT_NV				= 0x8542
	COMBINER_MAPPING_NV				= 0x8543
	COMBINER_COMPONENT_USAGE_NV			= 0x8544
	COMBINER_AB_DOT_PRODUCT_NV			= 0x8545
	COMBINER_CD_DOT_PRODUCT_NV			= 0x8546
	COMBINER_MUX_SUM_NV				= 0x8547
	COMBINER_SCALE_NV				= 0x8548
	COMBINER_BIAS_NV				= 0x8549
	COMBINER_AB_OUTPUT_NV				= 0x854A
	COMBINER_CD_OUTPUT_NV				= 0x854B
	COMBINER_SUM_OUTPUT_NV				= 0x854C
	MAX_GENERAL_COMBINERS_NV			= 0x854D
	NUM_GENERAL_COMBINERS_NV			= 0x854E
	COLOR_SUM_CLAMP_NV				= 0x854F
	COMBINER0_NV					= 0x8550
	COMBINER1_NV					= 0x8551
	COMBINER2_NV					= 0x8552
	COMBINER3_NV					= 0x8553
	COMBINER4_NV					= 0x8554
	COMBINER5_NV					= 0x8555
	COMBINER6_NV					= 0x8556
	COMBINER7_NV					= 0x8557
	use ARB_multitexture TEXTURE0_ARB
	use ARB_multitexture TEXTURE1_ARB
	use BlendingFactorDest ZERO
	use DrawBufferMode NONE
	use GetPName FOG

###############################################################################

# Extension #192
NV_fog_distance enum:
	FOG_DISTANCE_MODE_NV				= 0x855A
	EYE_RADIAL_NV					= 0x855B
	EYE_PLANE_ABSOLUTE_NV				= 0x855C
	use TextureGenParameter EYE_PLANE

###############################################################################

# Extension #193
NV_texgen_emboss enum:
	EMBOSS_LIGHT_NV					= 0x855D
	EMBOSS_CONSTANT_NV				= 0x855E
	EMBOSS_MAP_NV					= 0x855F

###############################################################################

# No new tokens
# Extension #194
NV_blend_square enum:

###############################################################################

# Extension #195
NV_texture_env_combine4 enum:
	COMBINE4_NV					= 0x8503
	SOURCE3_RGB_NV					= 0x8583
	SOURCE3_ALPHA_NV				= 0x858B
	OPERAND3_RGB_NV					= 0x8593
	OPERAND3_ALPHA_NV				= 0x859B

###############################################################################

# No new tokens
# Extension #196
MESA_resize_buffers enum:

###############################################################################

# No new tokens
# Extension #197
MESA_window_pos enum:

###############################################################################

# Extension #198
EXT_texture_compression_s3tc enum:
	COMPRESSED_RGB_S3TC_DXT1_EXT			= 0x83F0
	COMPRESSED_RGBA_S3TC_DXT1_EXT			= 0x83F1
	COMPRESSED_RGBA_S3TC_DXT3_EXT			= 0x83F2
	COMPRESSED_RGBA_S3TC_DXT5_EXT			= 0x83F3

###############################################################################

# Extension #199
IBM_cull_vertex enum:
	CULL_VERTEX_IBM					= 103050

###############################################################################

# No new tokens
# Extension #200
IBM_multimode_draw_arrays enum:

###############################################################################

# Extension #201
IBM_vertex_array_lists enum:
	VERTEX_ARRAY_LIST_IBM				= 103070
	NORMAL_ARRAY_LIST_IBM				= 103071
	COLOR_ARRAY_LIST_IBM				= 103072
	INDEX_ARRAY_LIST_IBM				= 103073
	TEXTURE_COORD_ARRAY_LIST_IBM			= 103074
	EDGE_FLAG_ARRAY_LIST_IBM			= 103075
	FOG_COORDINATE_ARRAY_LIST_IBM			= 103076
	SECONDARY_COLOR_ARRAY_LIST_IBM			= 103077
	VERTEX_ARRAY_LIST_STRIDE_IBM			= 103080
	NORMAL_ARRAY_LIST_STRIDE_IBM			= 103081
	COLOR_ARRAY_LIST_STRIDE_IBM			= 103082
	INDEX_ARRAY_LIST_STRIDE_IBM			= 103083
	TEXTURE_COORD_ARRAY_LIST_STRIDE_IBM		= 103084
	EDGE_FLAG_ARRAY_LIST_STRIDE_IBM			= 103085
	FOG_COORDINATE_ARRAY_LIST_STRIDE_IBM		= 103086
	SECONDARY_COLOR_ARRAY_LIST_STRIDE_IBM		= 103087

###############################################################################

# Extension #202
SGIX_subsample enum:
	PACK_SUBSAMPLE_RATE_SGIX			= 0x85A0
	UNPACK_SUBSAMPLE_RATE_SGIX			= 0x85A1
	PIXEL_SUBSAMPLE_4444_SGIX			= 0x85A2
	PIXEL_SUBSAMPLE_2424_SGIX			= 0x85A3
	PIXEL_SUBSAMPLE_4242_SGIX			= 0x85A4

###############################################################################

# Extension #203
SGIX_ycrcb_subsample enum:
	PACK_SUBSAMPLE_RATE_SGIX			= 0x85A0
	UNPACK_SUBSAMPLE_RATE_SGIX			= 0x85A1
	PIXEL_SUBSAMPLE_4444_SGIX			= 0x85A2
	PIXEL_SUBSAMPLE_2424_SGIX			= 0x85A3
	PIXEL_SUBSAMPLE_4242_SGIX			= 0x85A4

###############################################################################

# Extension #204
SGIX_ycrcba enum:
	YCRCB_SGIX					= 0x8318
	YCRCBA_SGIX					= 0x8319

###############################################################################

# Extension #205
SGI_depth_pass_instrument enum:
	DEPTH_PASS_INSTRUMENT_SGIX			= 0x8310
	DEPTH_PASS_INSTRUMENT_COUNTERS_SGIX		= 0x8311
	DEPTH_PASS_INSTRUMENT_MAX_SGIX			= 0x8312

###############################################################################

# Extension #206
3DFX_texture_compression_FXT1 enum:
	COMPRESSED_RGB_FXT1_3DFX			= 0x86B0
	COMPRESSED_RGBA_FXT1_3DFX			= 0x86B1

###############################################################################

# Extension #207
3DFX_multisample enum:
	MULTISAMPLE_3DFX				= 0x86B2
	SAMPLE_BUFFERS_3DFX				= 0x86B3
	SAMPLES_3DFX					= 0x86B4
	MULTISAMPLE_BIT_3DFX				= 0x20000000

###############################################################################

# No new tokens
# Extension #208
3DFX_tbuffer enum:

###############################################################################

# Extension #209
EXT_multisample enum:
	MULTISAMPLE_EXT					= 0x809D
	SAMPLE_ALPHA_TO_MASK_EXT			= 0x809E
	SAMPLE_ALPHA_TO_ONE_EXT				= 0x809F
	SAMPLE_MASK_EXT					= 0x80A0
	1PASS_EXT					= 0x80A1
	2PASS_0_EXT					= 0x80A2
	2PASS_1_EXT					= 0x80A3
	4PASS_0_EXT					= 0x80A4
	4PASS_1_EXT					= 0x80A5
	4PASS_2_EXT					= 0x80A6
	4PASS_3_EXT					= 0x80A7
	SAMPLE_BUFFERS_EXT				= 0x80A8 # 1 I
	SAMPLES_EXT					= 0x80A9 # 1 I
	SAMPLE_MASK_VALUE_EXT				= 0x80AA # 1 F
	SAMPLE_MASK_INVERT_EXT				= 0x80AB # 1 I
	SAMPLE_PATTERN_EXT				= 0x80AC # 1 I
	MULTISAMPLE_BIT_EXT				= 0x20000000

###############################################################################

# Extension #210
SGIX_vertex_preclip enum:
	VERTEX_PRECLIP_SGIX				= 0x83EE
	VERTEX_PRECLIP_HINT_SGIX			= 0x83EF

###############################################################################

# Extension #211
SGIX_convolution_accuracy enum:
	CONVOLUTION_HINT_SGIX				= 0x8316 # 1 I

###############################################################################

# Extension #212
SGIX_resample enum:
	PACK_RESAMPLE_SGIX				= 0x842C
	UNPACK_RESAMPLE_SGIX				= 0x842D
	RESAMPLE_REPLICATE_SGIX				= 0x842E
	RESAMPLE_ZERO_FILL_SGIX				= 0x842F
	RESAMPLE_DECIMATE_SGIX				= 0x8430

###############################################################################

# Extension #213
SGIS_point_line_texgen enum:
	EYE_DISTANCE_TO_POINT_SGIS			= 0x81F0
	OBJECT_DISTANCE_TO_POINT_SGIS			= 0x81F1
	EYE_DISTANCE_TO_LINE_SGIS			= 0x81F2
	OBJECT_DISTANCE_TO_LINE_SGIS			= 0x81F3
	EYE_POINT_SGIS					= 0x81F4
	OBJECT_POINT_SGIS				= 0x81F5
	EYE_LINE_SGIS					= 0x81F6
	OBJECT_LINE_SGIS				= 0x81F7

###############################################################################

# Extension #214
SGIS_texture_color_mask enum:
	TEXTURE_COLOR_WRITEMASK_SGIS			= 0x81EF

###############################################################################

# Extension #220
# Promoted to ARB_texture_env_dot3
# EXT_texture_env_dot3

###############################################################################

# Extension #222
NV_fence enum:
	ALL_COMPLETED_NV				= 0x84F2
	FENCE_STATUS_NV					= 0x84F3
	FENCE_CONDITION_NV				= 0x84F4

###############################################################################

# Extension #224
IBM_texture_mirrored_repeat enum:
	MIRRORED_REPEAT_IBM				= 0x8370

###############################################################################

# Extension #225
NV_evaluators enum:
	EVAL_2D_NV					= 0x86C0
	EVAL_TRIANGULAR_2D_NV				= 0x86C1
	MAP_TESSELLATION_NV				= 0x86C2
	MAP_ATTRIB_U_ORDER_NV				= 0x86C3
	MAP_ATTRIB_V_ORDER_NV				= 0x86C4
	EVAL_FRACTIONAL_TESSELLATION_NV			= 0x86C5
	EVAL_VERTEX_ATTRIB0_NV				= 0x86C6
	EVAL_VERTEX_ATTRIB1_NV				= 0x86C7
	EVAL_VERTEX_ATTRIB2_NV				= 0x86C8
	EVAL_VERTEX_ATTRIB3_NV				= 0x86C9
	EVAL_VERTEX_ATTRIB4_NV				= 0x86CA
	EVAL_VERTEX_ATTRIB5_NV				= 0x86CB
	EVAL_VERTEX_ATTRIB6_NV				= 0x86CC
	EVAL_VERTEX_ATTRIB7_NV				= 0x86CD
	EVAL_VERTEX_ATTRIB8_NV				= 0x86CE
	EVAL_VERTEX_ATTRIB9_NV				= 0x86CF
	EVAL_VERTEX_ATTRIB10_NV				= 0x86D0
	EVAL_VERTEX_ATTRIB11_NV				= 0x86D1
	EVAL_VERTEX_ATTRIB12_NV				= 0x86D2
	EVAL_VERTEX_ATTRIB13_NV				= 0x86D3
	EVAL_VERTEX_ATTRIB14_NV				= 0x86D4
	EVAL_VERTEX_ATTRIB15_NV				= 0x86D5
	MAX_MAP_TESSELLATION_NV				= 0x86D6
	MAX_RATIONAL_EVAL_ORDER_NV			= 0x86D7

###############################################################################

# Extension #226
NV_packed_depth_stencil enum:
	DEPTH_STENCIL_NV				= 0x84F9
	UNSIGNED_INT_24_8_NV				= 0x84FA

###############################################################################

# Extension #227
NV_register_combiners2 enum:
	PER_STAGE_CONSTANTS_NV				= 0x8535

###############################################################################

# No new tokens
# Extension #228
NV_texture_compression_vtc enum:

###############################################################################

# Extension #229
NV_texture_rectangle enum:
	TEXTURE_RECTANGLE_NV				= 0x84F5
	TEXTURE_BINDING_RECTANGLE_NV			= 0x84F6
	PROXY_TEXTURE_RECTANGLE_NV			= 0x84F7
	MAX_TEXTURE_RECTANGLE_SIZE_NV			= 0x84F8

###############################################################################

# Extension #230
NV_texture_shader enum:
	TEXTURE_SHADER_NV				= 0x86DE
	RGBA_UNSIGNED_DOT_PRODUCT_MAPPING_NV		= 0x86D9
	SHADER_OPERATION_NV				= 0x86DF
	CULL_MODES_NV					= 0x86E0
	OFFSET_TEXTURE_MATRIX_NV			= 0x86E1
	OFFSET_TEXTURE_2D_MATRIX_NV			= 0x86E1
	OFFSET_TEXTURE_SCALE_NV				= 0x86E2
	OFFSET_TEXTURE_2D_SCALE_NV			= 0x86E2
	OFFSET_TEXTURE_BIAS_NV				= 0x86E3
	OFFSET_TEXTURE_2D_BIAS_NV			= 0x86E3
	PREVIOUS_TEXTURE_INPUT_NV			= 0x86E4
	CONST_EYE_NV					= 0x86E5
	SHADER_CONSISTENT_NV				= 0x86DD
	PASS_THROUGH_NV					= 0x86E6
	CULL_FRAGMENT_NV				= 0x86E7
	OFFSET_TEXTURE_2D_NV				= 0x86E8
	OFFSET_TEXTURE_RECTANGLE_NV			= 0x864C
	OFFSET_TEXTURE_RECTANGLE_SCALE_NV		= 0x864D
	DEPENDENT_AR_TEXTURE_2D_NV			= 0x86E9
	DEPENDENT_GB_TEXTURE_2D_NV			= 0x86EA
	DOT_PRODUCT_NV					= 0x86EC
	DOT_PRODUCT_DEPTH_REPLACE_NV			= 0x86ED
	DOT_PRODUCT_TEXTURE_2D_NV			= 0x86EE
	DOT_PRODUCT_TEXTURE_RECTANGLE_NV		= 0x864E
	DOT_PRODUCT_TEXTURE_CUBE_MAP_NV			= 0x86F0
	DOT_PRODUCT_DIFFUSE_CUBE_MAP_NV			= 0x86F1
	DOT_PRODUCT_REFLECT_CUBE_MAP_NV			= 0x86F2
	DOT_PRODUCT_CONST_EYE_REFLECT_CUBE_MAP_NV	= 0x86F3
	HILO_NV						= 0x86F4
	DSDT_NV						= 0x86F5
	DSDT_MAG_NV					= 0x86F6
	DSDT_MAG_VIB_NV					= 0x86F7
	UNSIGNED_INT_S8_S8_8_8_NV			= 0x86DA
	UNSIGNED_INT_8_8_S8_S8_REV_NV			= 0x86DB
	SIGNED_RGBA_NV					= 0x86FB
	SIGNED_RGBA8_NV					= 0x86FC
	SIGNED_RGB_NV					= 0x86FE
	SIGNED_RGB8_NV					= 0x86FF
	SIGNED_LUMINANCE_NV				= 0x8701
	SIGNED_LUMINANCE8_NV				= 0x8702
	SIGNED_LUMINANCE_ALPHA_NV			= 0x8703
	SIGNED_LUMINANCE8_ALPHA8_NV			= 0x8704
	SIGNED_ALPHA_NV					= 0x8705
	SIGNED_ALPHA8_NV				= 0x8706
	SIGNED_INTENSITY_NV				= 0x8707
	SIGNED_INTENSITY8_NV				= 0x8708
	SIGNED_RGB_UNSIGNED_ALPHA_NV			= 0x870C
	SIGNED_RGB8_UNSIGNED_ALPHA8_NV			= 0x870D
	HILO16_NV					= 0x86F8
	SIGNED_HILO_NV					= 0x86F9
	SIGNED_HILO16_NV				= 0x86FA
	DSDT8_NV					= 0x8709
	DSDT8_MAG8_NV					= 0x870A
	DSDT_MAG_INTENSITY_NV				= 0x86DC
	DSDT8_MAG8_INTENSITY8_NV			= 0x870B
	HI_SCALE_NV					= 0x870E
	LO_SCALE_NV					= 0x870F
	DS_SCALE_NV					= 0x8710
	DT_SCALE_NV					= 0x8711
	MAGNITUDE_SCALE_NV				= 0x8712
	VIBRANCE_SCALE_NV				= 0x8713
	HI_BIAS_NV					= 0x8714
	LO_BIAS_NV					= 0x8715
	DS_BIAS_NV					= 0x8716
	DT_BIAS_NV					= 0x8717
	MAGNITUDE_BIAS_NV				= 0x8718
	VIBRANCE_BIAS_NV				= 0x8719
	TEXTURE_BORDER_VALUES_NV			= 0x871A
	TEXTURE_HI_SIZE_NV				= 0x871B
	TEXTURE_LO_SIZE_NV				= 0x871C
	TEXTURE_DS_SIZE_NV				= 0x871D
	TEXTURE_DT_SIZE_NV				= 0x871E
	TEXTURE_MAG_SIZE_NV				= 0x871F

###############################################################################

# Extension #231
NV_texture_shader2 enum:
	DOT_PRODUCT_TEXTURE_3D_NV			= 0x86EF

###############################################################################

# Extension #232
NV_vertex_array_range2 enum:
	VERTEX_ARRAY_RANGE_WITHOUT_FLUSH_NV		= 0x8533

###############################################################################

# Extension #233
NV_vertex_program enum:
	VERTEX_PROGRAM_NV				= 0x8620
	VERTEX_PROGRAM_POINT_SIZE_NV			= 0x8642
	VERTEX_PROGRAM_TWO_SIDE_NV			= 0x8643
	VERTEX_STATE_PROGRAM_NV				= 0x8621
	ATTRIB_ARRAY_SIZE_NV				= 0x8623
	ATTRIB_ARRAY_STRIDE_NV				= 0x8624
	ATTRIB_ARRAY_TYPE_NV				= 0x8625
	CURRENT_ATTRIB_NV				= 0x8626
	PROGRAM_PARAMETER_NV				= 0x8644
	ATTRIB_ARRAY_POINTER_NV				= 0x8645
	PROGRAM_TARGET_NV				= 0x8646
	PROGRAM_LENGTH_NV				= 0x8627
	PROGRAM_RESIDENT_NV				= 0x8647
	PROGRAM_STRING_NV				= 0x8628
	TRACK_MATRIX_NV					= 0x8648
	TRACK_MATRIX_TRANSFORM_NV			= 0x8649
	MAX_TRACK_MATRIX_STACK_DEPTH_NV			= 0x862E
	MAX_TRACK_MATRICES_NV				= 0x862F
	CURRENT_MATRIX_STACK_DEPTH_NV			= 0x8640
	CURRENT_MATRIX_NV				= 0x8641
	VERTEX_PROGRAM_BINDING_NV			= 0x864A
	PROGRAM_ERROR_POSITION_NV			= 0x864B
	MODELVIEW_PROJECTION_NV				= 0x8629
	MATRIX0_NV					= 0x8630
	MATRIX1_NV					= 0x8631
	MATRIX2_NV					= 0x8632
	MATRIX3_NV					= 0x8633
	MATRIX4_NV					= 0x8634
	MATRIX5_NV					= 0x8635
	MATRIX6_NV					= 0x8636
	MATRIX7_NV					= 0x8637
	IDENTITY_NV					= 0x862A
	INVERSE_NV					= 0x862B
	TRANSPOSE_NV					= 0x862C
	INVERSE_TRANSPOSE_NV				= 0x862D
	VERTEX_ATTRIB_ARRAY0_NV				= 0x8650
	VERTEX_ATTRIB_ARRAY1_NV				= 0x8651
	VERTEX_ATTRIB_ARRAY2_NV				= 0x8652
	VERTEX_ATTRIB_ARRAY3_NV				= 0x8653
	VERTEX_ATTRIB_ARRAY4_NV				= 0x8654
	VERTEX_ATTRIB_ARRAY5_NV				= 0x8655
	VERTEX_ATTRIB_ARRAY6_NV				= 0x8656
	VERTEX_ATTRIB_ARRAY7_NV				= 0x8657
	VERTEX_ATTRIB_ARRAY8_NV				= 0x8658
	VERTEX_ATTRIB_ARRAY9_NV				= 0x8659
	VERTEX_ATTRIB_ARRAY10_NV			= 0x865A
	VERTEX_ATTRIB_ARRAY11_NV			= 0x865B
	VERTEX_ATTRIB_ARRAY12_NV			= 0x865C
	VERTEX_ATTRIB_ARRAY13_NV			= 0x865D
	VERTEX_ATTRIB_ARRAY14_NV			= 0x865E
	VERTEX_ATTRIB_ARRAY15_NV			= 0x865F
	MAP1_VERTEX_ATTRIB0_4_NV			= 0x8660
	MAP1_VERTEX_ATTRIB1_4_NV			= 0x8661
	MAP1_VERTEX_ATTRIB2_4_NV			= 0x8662
	MAP1_VERTEX_ATTRIB3_4_NV			= 0x8663
	MAP1_VERTEX_ATTRIB4_4_NV			= 0x8664
	MAP1_VERTEX_ATTRIB5_4_NV			= 0x8665
	MAP1_VERTEX_ATTRIB6_4_NV			= 0x8666
	MAP1_VERTEX_ATTRIB7_4_NV			= 0x8667
	MAP1_VERTEX_ATTRIB8_4_NV			= 0x8668
	MAP1_VERTEX_ATTRIB9_4_NV			= 0x8669
	MAP1_VERTEX_ATTRIB10_4_NV			= 0x866A
	MAP1_VERTEX_ATTRIB11_4_NV			= 0x866B
	MAP1_VERTEX_ATTRIB12_4_NV			= 0x866C
	MAP1_VERTEX_ATTRIB13_4_NV			= 0x866D
	MAP1_VERTEX_ATTRIB14_4_NV			= 0x866E
	MAP1_VERTEX_ATTRIB15_4_NV			= 0x866F
	MAP2_VERTEX_ATTRIB0_4_NV			= 0x8670
	MAP2_VERTEX_ATTRIB1_4_NV			= 0x8671
	MAP2_VERTEX_ATTRIB2_4_NV			= 0x8672
	MAP2_VERTEX_ATTRIB3_4_NV			= 0x8673
	MAP2_VERTEX_ATTRIB4_4_NV			= 0x8674
	MAP2_VERTEX_ATTRIB5_4_NV			= 0x8675
	MAP2_VERTEX_ATTRIB6_4_NV			= 0x8676
	MAP2_VERTEX_ATTRIB7_4_NV			= 0x8677
	MAP2_VERTEX_ATTRIB8_4_NV			= 0x8678
	MAP2_VERTEX_ATTRIB9_4_NV			= 0x8679
	MAP2_VERTEX_ATTRIB10_4_NV			= 0x867A
	MAP2_VERTEX_ATTRIB11_4_NV			= 0x867B
	MAP2_VERTEX_ATTRIB12_4_NV			= 0x867C
	MAP2_VERTEX_ATTRIB13_4_NV			= 0x867D
	MAP2_VERTEX_ATTRIB14_4_NV			= 0x867E
	MAP2_VERTEX_ATTRIB15_4_NV			= 0x867F

###############################################################################

# Extension #235
SGIX_texture_coordinate_clamp enum:
	TEXTURE_MAX_CLAMP_S_SGIX			= 0x8369
	TEXTURE_MAX_CLAMP_T_SGIX			= 0x836A
	TEXTURE_MAX_CLAMP_R_SGIX			= 0x836B

###############################################################################

# Extension #236
SGIX_scalebias_hint enum:
	SCALEBIAS_HINT_SGIX				= 0x8322

###############################################################################

# Extension #237 - GLX_OML_swap_method
# Extension #238 - GLX_OML_sync_control

###############################################################################

# Extension #239
OML_interlace enum:
	INTERLACE_OML					= 0x8980
	INTERLACE_READ_OML				= 0x8981

###############################################################################

# Extension #240
OML_subsample enum:
	FORMAT_SUBSAMPLE_24_24_OML			= 0x8982
	FORMAT_SUBSAMPLE_244_244_OML			= 0x8983

###############################################################################

# Extension #241
OML_resample enum:
	PACK_RESAMPLE_OML				= 0x8984
	UNPACK_RESAMPLE_OML				= 0x8985
	RESAMPLE_REPLICATE_OML				= 0x8986
	RESAMPLE_ZERO_FILL_OML				= 0x8987
	RESAMPLE_AVERAGE_OML				= 0x8988
	RESAMPLE_DECIMATE_OML				= 0x8989

###############################################################################

# Extension #242 - WGL_OML_sync_control

###############################################################################

# Extension #243
NV_copy_depth_to_color enum:
	DEPTH_STENCIL_TO_RGBA_NV			= 0x886E
	DEPTH_STENCIL_TO_BGRA_NV			= 0x886F

###############################################################################

# Extension #244
ATI_envmap_bumpmap enum:
	BUMP_ROT_MATRIX_ATI				= 0x8775
	BUMP_ROT_MATRIX_SIZE_ATI			= 0x8776
	BUMP_NUM_TEX_UNITS_ATI				= 0x8777
	BUMP_TEX_UNITS_ATI				= 0x8778
	DUDV_ATI					= 0x8779
	DU8DV8_ATI					= 0x877A
	BUMP_ENVMAP_ATI					= 0x877B
	BUMP_TARGET_ATI					= 0x877C

###############################################################################

# Extension #245
ATI_fragment_shader enum:
	FRAGMENT_SHADER_ATI				= 0x8920
	REG_0_ATI					= 0x8921
	REG_1_ATI					= 0x8922
	REG_2_ATI					= 0x8923
	REG_3_ATI					= 0x8924
	REG_4_ATI					= 0x8925
	REG_5_ATI					= 0x8926
	REG_6_ATI					= 0x8927
	REG_7_ATI					= 0x8928
	REG_8_ATI					= 0x8929
	REG_9_ATI					= 0x892A
	REG_10_ATI					= 0x892B
	REG_11_ATI					= 0x892C
	REG_12_ATI					= 0x892D
	REG_13_ATI					= 0x892E
	REG_14_ATI					= 0x892F
	REG_15_ATI					= 0x8930
	REG_16_ATI					= 0x8931
	REG_17_ATI					= 0x8932
	REG_18_ATI					= 0x8933
	REG_19_ATI					= 0x8934
	REG_20_ATI					= 0x8935
	REG_21_ATI					= 0x8936
	REG_22_ATI					= 0x8937
	REG_23_ATI					= 0x8938
	REG_24_ATI					= 0x8939
	REG_25_ATI					= 0x893A
	REG_26_ATI					= 0x893B
	REG_27_ATI					= 0x893C
	REG_28_ATI					= 0x893D
	REG_29_ATI					= 0x893E
	REG_30_ATI					= 0x893F
	REG_31_ATI					= 0x8940
	CON_0_ATI					= 0x8941
	CON_1_ATI					= 0x8942
	CON_2_ATI					= 0x8943
	CON_3_ATI					= 0x8944
	CON_4_ATI					= 0x8945
	CON_5_ATI					= 0x8946
	CON_6_ATI					= 0x8947
	CON_7_ATI					= 0x8948
	CON_8_ATI					= 0x8949
	CON_9_ATI					= 0x894A
	CON_10_ATI					= 0x894B
	CON_11_ATI					= 0x894C
	CON_12_ATI					= 0x894D
	CON_13_ATI					= 0x894E
	CON_14_ATI					= 0x894F
	CON_15_ATI					= 0x8950
	CON_16_ATI					= 0x8951
	CON_17_ATI					= 0x8952
	CON_18_ATI					= 0x8953
	CON_19_ATI					= 0x8954
	CON_20_ATI					= 0x8955
	CON_21_ATI					= 0x8956
	CON_22_ATI					= 0x8957
	CON_23_ATI					= 0x8958
	CON_24_ATI					= 0x8959
	CON_25_ATI					= 0x895A
	CON_26_ATI					= 0x895B
	CON_27_ATI					= 0x895C
	CON_28_ATI					= 0x895D
	CON_29_ATI					= 0x895E
	CON_30_ATI					= 0x895F
	CON_31_ATI					= 0x8960
	MOV_ATI						= 0x8961
	ADD_ATI						= 0x8963
	MUL_ATI						= 0x8964
	SUB_ATI						= 0x8965
	DOT3_ATI					= 0x8966
	DOT4_ATI					= 0x8967
	MAD_ATI						= 0x8968
	LERP_ATI					= 0x8969
	CND_ATI						= 0x896A
	CND0_ATI					= 0x896B
	DOT2_ADD_ATI					= 0x896C
	SECONDARY_INTERPOLATOR_ATI			= 0x896D
	NUM_FRAGMENT_REGISTERS_ATI			= 0x896E
	NUM_FRAGMENT_CONSTANTS_ATI			= 0x896F
	NUM_PASSES_ATI					= 0x8970
	NUM_INSTRUCTIONS_PER_PASS_ATI			= 0x8971
	NUM_INSTRUCTIONS_TOTAL_ATI			= 0x8972
	NUM_INPUT_INTERPOLATOR_COMPONENTS_ATI		= 0x8973
	NUM_LOOPBACK_COMPONENTS_ATI			= 0x8974
	COLOR_ALPHA_PAIRING_ATI				= 0x8975
	SWIZZLE_STR_ATI					= 0x8976
	SWIZZLE_STQ_ATI					= 0x8977
	SWIZZLE_STR_DR_ATI				= 0x8978
	SWIZZLE_STQ_DQ_ATI				= 0x8979
	SWIZZLE_STRQ_ATI				= 0x897A
	SWIZZLE_STRQ_DQ_ATI				= 0x897B
	RED_BIT_ATI					= 0x00000001
	GREEN_BIT_ATI					= 0x00000002
	BLUE_BIT_ATI					= 0x00000004
	2X_BIT_ATI					= 0x00000001
	4X_BIT_ATI					= 0x00000002
	8X_BIT_ATI					= 0x00000004
	HALF_BIT_ATI					= 0x00000008
	QUARTER_BIT_ATI					= 0x00000010
	EIGHTH_BIT_ATI					= 0x00000020
	SATURATE_BIT_ATI				= 0x00000040
	2X_BIT_ATI					= 0x00000001
	COMP_BIT_ATI					= 0x00000002
	NEGATE_BIT_ATI					= 0x00000004
	BIAS_BIT_ATI					= 0x00000008

###############################################################################

# Extension #246
ATI_pn_triangles enum:
	PN_TRIANGLES_ATI				= 0x87F0
	MAX_PN_TRIANGLES_TESSELATION_LEVEL_ATI		= 0x87F1
	PN_TRIANGLES_POINT_MODE_ATI			= 0x87F2
	PN_TRIANGLES_NORMAL_MODE_ATI			= 0x87F3
	PN_TRIANGLES_TESSELATION_LEVEL_ATI		= 0x87F4
	PN_TRIANGLES_POINT_MODE_LINEAR_ATI		= 0x87F5
	PN_TRIANGLES_POINT_MODE_CUBIC_ATI		= 0x87F6
	PN_TRIANGLES_NORMAL_MODE_LINEAR_ATI		= 0x87F7
	PN_TRIANGLES_NORMAL_MODE_QUADRATIC_ATI		= 0x87F8

###############################################################################

# Extension #247
ATI_vertex_array_object enum:
	STATIC_ATI					= 0x8760
	DYNAMIC_ATI					= 0x8761
	PRESERVE_ATI					= 0x8762
	DISCARD_ATI					= 0x8763
	OBJECT_BUFFER_SIZE_ATI				= 0x8764
	OBJECT_BUFFER_USAGE_ATI				= 0x8765
	ARRAY_OBJECT_BUFFER_ATI				= 0x8766
	ARRAY_OBJECT_OFFSET_ATI				= 0x8767

###############################################################################

# Extension #248
EXT_vertex_shader enum:
	VERTEX_SHADER_EXT				= 0x8780
	VERTEX_SHADER_BINDING_EXT			= 0x8781
	OP_INDEX_EXT					= 0x8782
	OP_NEGATE_EXT					= 0x8783
	OP_DOT3_EXT					= 0x8784
	OP_DOT4_EXT					= 0x8785
	OP_MUL_EXT					= 0x8786
	OP_ADD_EXT					= 0x8787
	OP_MADD_EXT					= 0x8788
	OP_FRAC_EXT					= 0x8789
	OP_MAX_EXT					= 0x878A
	OP_MIN_EXT					= 0x878B
	OP_SET_GE_EXT					= 0x878C
	OP_SET_LT_EXT					= 0x878D
	OP_CLAMP_EXT					= 0x878E
	OP_FLOOR_EXT					= 0x878F
	OP_ROUND_EXT					= 0x8790
	OP_EXP_BASE_2_EXT				= 0x8791
	OP_LOG_BASE_2_EXT				= 0x8792
	OP_POWER_EXT					= 0x8793
	OP_RECIP_EXT					= 0x8794
	OP_RECIP_SQRT_EXT				= 0x8795
	OP_SUB_EXT					= 0x8796
	OP_CROSS_PRODUCT_EXT				= 0x8797
	OP_MULTIPLY_MATRIX_EXT				= 0x8798
	OP_MOV_EXT					= 0x8799
	OUTPUT_VERTEX_EXT				= 0x879A
	OUTPUT_COLOR0_EXT				= 0x879B
	OUTPUT_COLOR1_EXT				= 0x879C
	OUTPUT_TEXTURE_COORD0_EXT			= 0x879D
	OUTPUT_TEXTURE_COORD1_EXT			= 0x879E
	OUTPUT_TEXTURE_COORD2_EXT			= 0x879F
	OUTPUT_TEXTURE_COORD3_EXT			= 0x87A0
	OUTPUT_TEXTURE_COORD4_EXT			= 0x87A1
	OUTPUT_TEXTURE_COORD5_EXT			= 0x87A2
	OUTPUT_TEXTURE_COORD6_EXT			= 0x87A3
	OUTPUT_TEXTURE_COORD7_EXT			= 0x87A4
	OUTPUT_TEXTURE_COORD8_EXT			= 0x87A5
	OUTPUT_TEXTURE_COORD9_EXT			= 0x87A6
	OUTPUT_TEXTURE_COORD10_EXT			= 0x87A7
	OUTPUT_TEXTURE_COORD11_EXT			= 0x87A8
	OUTPUT_TEXTURE_COORD12_EXT			= 0x87A9
	OUTPUT_TEXTURE_COORD13_EXT			= 0x87AA
	OUTPUT_TEXTURE_COORD14_EXT			= 0x87AB
	OUTPUT_TEXTURE_COORD15_EXT			= 0x87AC
	OUTPUT_TEXTURE_COORD16_EXT			= 0x87AD
	OUTPUT_TEXTURE_COORD17_EXT			= 0x87AE
	OUTPUT_TEXTURE_COORD18_EXT			= 0x87AF
	OUTPUT_TEXTURE_COORD19_EXT			= 0x87B0
	OUTPUT_TEXTURE_COORD20_EXT			= 0x87B1
	OUTPUT_TEXTURE_COORD21_EXT			= 0x87B2
	OUTPUT_TEXTURE_COORD22_EXT			= 0x87B3
	OUTPUT_TEXTURE_COORD23_EXT			= 0x87B4
	OUTPUT_TEXTURE_COORD24_EXT			= 0x87B5
	OUTPUT_TEXTURE_COORD25_EXT			= 0x87B6
	OUTPUT_TEXTURE_COORD26_EXT			= 0x87B7
	OUTPUT_TEXTURE_COORD27_EXT			= 0x87B8
	OUTPUT_TEXTURE_COORD28_EXT			= 0x87B9
	OUTPUT_TEXTURE_COORD29_EXT			= 0x87BA
	OUTPUT_TEXTURE_COORD30_EXT			= 0x87BB
	OUTPUT_TEXTURE_COORD31_EXT			= 0x87BC
	OUTPUT_FOG_EXT					= 0x87BD
	SCALAR_EXT					= 0x87BE
	VECTOR_EXT					= 0x87BF
	MATRIX_EXT					= 0x87C0
	VARIANT_EXT					= 0x87C1
	INVARIANT_EXT					= 0x87C2
	LOCAL_CONSTANT_EXT				= 0x87C3
	LOCAL_EXT					= 0x87C4
	MAX_VERTEX_SHADER_INSTRUCTIONS_EXT		= 0x87C5
	MAX_VERTEX_SHADER_VARIANTS_EXT			= 0x87C6
	MAX_VERTEX_SHADER_INVARIANTS_EXT		= 0x87C7
	MAX_VERTEX_SHADER_LOCAL_CONSTANTS_EXT		= 0x87C8
	MAX_VERTEX_SHADER_LOCALS_EXT			= 0x87C9
	MAX_OPTIMIZED_VERTEX_SHADER_INSTRUCTIONS_EXT	= 0x87CA
	MAX_OPTIMIZED_VERTEX_SHADER_VARIANTS_EXT	= 0x87CB
	MAX_OPTIMIZED_VERTEX_SHADER_LOCAL_CONSTANTS_EXT = 0x87CC
	MAX_OPTIMIZED_VERTEX_SHADER_INARIANTS_EXT	= 0x87CD
	MAX_OPTIMIZED_VERTEX_SHADER_LOCALS_EXT		= 0x87CE
	VERTEX_SHADER_INSTRUCTIONS_EXT			= 0x87CF
	VERTEX_SHADER_VARIANTS_EXT			= 0x87D0
	VERTEX_SHADER_INVARIANTS_EXT			= 0x87D1
	VERTEX_SHADER_LOCAL_CONSTANTS_EXT		= 0x87D2
	VERTEX_SHADER_LOCALS_EXT			= 0x87D3
	VERTEX_SHADER_OPTIMIZED_EXT			= 0x87D4
	X_EXT						= 0x87D5
	Y_EXT						= 0x87D6
	Z_EXT						= 0x87D7
	W_EXT						= 0x87D8
	NEGATIVE_X_EXT					= 0x87D9
	NEGATIVE_Y_EXT					= 0x87DA
	NEGATIVE_Z_EXT					= 0x87DB
	NEGATIVE_W_EXT					= 0x87DC
	ZERO_EXT					= 0x87DD
	ONE_EXT						= 0x87DE
	NEGATIVE_ONE_EXT				= 0x87DF
	NORMALIZED_RANGE_EXT				= 0x87E0
	FULL_RANGE_EXT					= 0x87E1
	CURRENT_VERTEX_EXT				= 0x87E2
	MVP_MATRIX_EXT					= 0x87E3
	VARIANT_VALUE_EXT				= 0x87E4
	VARIANT_DATATYPE_EXT				= 0x87E5
	VARIANT_ARRAY_STRIDE_EXT			= 0x87E6
	VARIANT_ARRAY_TYPE_EXT				= 0x87E7
	VARIANT_ARRAY_EXT				= 0x87E8
	VARIANT_ARRAY_POINTER_EXT			= 0x87E9
	INVARIANT_VALUE_EXT				= 0x87EA
	INVARIANT_DATATYPE_EXT				= 0x87EB
	LOCAL_CONSTANT_VALUE_EXT			= 0x87EC
	LOCAL_CONSTANT_DATATYPE_EXT			= 0x87ED

###############################################################################

# Extension #249
ATI_vertex_streams enum:
	MAX_VERTEX_STREAMS_ATI				= 0x876B
	VERTEX_STREAM0_ATI				= 0x876C
	VERTEX_STREAM1_ATI				= 0x876D
	VERTEX_STREAM2_ATI				= 0x876E
	VERTEX_STREAM3_ATI				= 0x876F
	VERTEX_STREAM4_ATI				= 0x8770
	VERTEX_STREAM5_ATI				= 0x8771
	VERTEX_STREAM6_ATI				= 0x8772
	VERTEX_STREAM7_ATI				= 0x8773
	VERTEX_SOURCE_ATI				= 0x8774

###############################################################################

# Extension #250 - WGL_I3D_digital_video_control
# Extension #251 - WGL_I3D_gamma
# Extension #252 - WGL_I3D_genlock
# Extension #253 - WGL_I3D_image_buffer
# Extension #254 - WGL_I3D_swap_frame_lock
# Extension #255 - WGL_I3D_swap_frame_usage

###############################################################################

# Extension #256
ATI_element_array enum:
	ELEMENT_ARRAY_ATI				= 0x8768
	ELEMENT_ARRAY_TYPE_ATI				= 0x8769
	ELEMENT_ARRAY_POINTER_ATI			= 0x876A

###############################################################################

# Extension #257
SUN_mesh_array enum:
	QUAD_MESH_SUN					= 0x8614
	TRIANGLE_MESH_SUN				= 0x8615

###############################################################################

# Extension #258
SUN_slice_accum enum:
	SLICE_ACCUM_SUN					= 0x85CC

###############################################################################

# Extension #259
NV_multisample_filter_hint enum:
	MULTISAMPLE_FILTER_HINT_NV			= 0x8534

