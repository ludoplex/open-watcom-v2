/****************************************************************************
*
*                            Open Watcom Project
*
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
* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
*               DESCRIBE IT HERE!
*
****************************************************************************/


#include "wio.h"
#include "global.h"
#include "semantic.h"
#include "rcerrors.h"
#include "reserr.h"
#include "depend.h"
#include "rcrtns.h"
#include "rccore.h"

#include "clibext.h"


#define BUFFER_SIZE     1024

static bool copyAResource( FILE *fp, WResDirWindow *wind,
                            char *buffer, const char *filename )
/****************************************************************/
{
    ResLocation         loc;
    WResLangInfo        *langinfo;
    WResTypeInfo        *typeinfo;
    WResResInfo         *resinfo;
//    RcStatus            rc;
    int                 err_code;

    langinfo = WResGetLangInfo( *wind );
    resinfo = WResGetResInfo( *wind );
    typeinfo = WResGetTypeInfo( *wind );
    loc.start = SemStartResource();
    /* rc = */ CopyData( langinfo->Offset, langinfo->Length, fp, buffer, BUFFER_SIZE, &err_code );
    loc.len = SemEndResource( loc.start );
    SemAddResource2( &resinfo->ResName, &typeinfo->TypeName, langinfo->MemoryFlags, loc, filename );
    return( false );
}

static bool copyResourcesFromRes( const char *full_filename )
/***********************************************************/
{
    FILE                *fp;
    WResDir             dir;
    bool                dup_discarded;
    WResDirWindow       wind;
    char                *buffer;
    bool                error;

    buffer = NULL;
    dir = WResInitDir();
    fp = RcIoOpenInput( full_filename, false );
    if( fp == NULL ) {
        RcError( ERR_CANT_OPEN_FILE, full_filename, strerror( errno ) );
        goto HANDLE_ERROR;
    }

    error = WResReadDir( fp, dir, &dup_discarded );
    if( error ) {
        switch( LastWresStatus() ) {
        case WRS_BAD_SIG:
            RcError( ERR_INVALID_RES, full_filename );
            break;
        case WRS_BAD_VERSION:
            RcError( ERR_BAD_RES_VER, full_filename );
            break;
        default:
            RcError( ERR_READING_RES, full_filename, LastWresErrStr() );
            break;
        }
        goto HANDLE_ERROR;
    }

    if( WResGetTargetOS( dir ) != WResGetTargetOS( CurrResFile.dir ) ) {
        RcError( ERR_RES_OS_MISMATCH, full_filename );
        goto HANDLE_ERROR;
    }
    buffer = RESALLOC( BUFFER_SIZE );
    wind = WResFirstResource( dir );
    while( !WResIsEmptyWindow( wind ) ) {
        copyAResource( fp, &wind, buffer, full_filename );
        wind = WResNextResource( wind, dir );
    }
    RESFREE( buffer );
    WResFreeDir( dir );
    RESCLOSE( fp );
    return( false );

HANDLE_ERROR:
    ErrorHasOccured = true;
    WResFreeDir( dir );
    if( fp != NULL )
        RESCLOSE( fp );
    return( true );
}

void SemWINAddResFile( char *filename )
/*************************************/
{
    char                full_filename[_MAX_PATH];

    if( RcFindResource( filename, full_filename ) == -1 ) {
        RcError( ERR_CANT_FIND_FILE, filename );
        goto HANDLE_ERROR;
    }
    if( AddDependency( full_filename ) )
        goto HANDLE_ERROR;
    if( copyResourcesFromRes( full_filename ) )
        goto HANDLE_ERROR;
    RESFREE( filename );
    return;

HANDLE_ERROR:
    ErrorHasOccured = true;
    RESFREE( filename );
}
