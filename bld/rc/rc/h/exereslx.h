/****************************************************************************
*
*                            Open Watcom Project
*
* Copyright (c) 2023-2023 The Open Watcom Contributors. All Rights Reserved.
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  LX resource manipulation routines interface.
*
****************************************************************************/


#ifndef EXERESLX_INCLUDED
#define EXERESLX_INCLUDED

#include "rctypes.h"


extern bool BuildLXResourceObjects( ExeFileInfo *dst, ResFileInfo *resfiles,
                            object_record *res_obj, unsigned_32 rva, unsigned_32 offset, bool writebyfile );
extern bool RcBuildLXResourceObjects( ExeFileInfo *dst, ResFileInfo *resfiles );

extern RcStatus WriteLXResourceObjects( ExeFileInfo *dst, ResFileInfo *res );
extern RcStatus RcWriteLXResourceObjects( ExeFileInfo *dst, ResFileInfo *res );

#endif
