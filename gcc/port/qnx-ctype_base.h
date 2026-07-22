// Locale support -*- C++ -*-

// Copyright (C) 2002-2014 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file bits/ctype_base.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{locale}
 */

//
// ISO C++ 14882: 22.1  Locales
//

// Information as gleaned from /usr/include/ctype.h.
//
// NB: QNX's <ctype.h> exposes the classification bits as short, unguarded
// macros (_UP=0x02, _LO=0x10, _DI=0x20, _XD=0x01, _SP=0x04, _PU=0x08,
// _CN=0x40, _BB=0x80, _XA=0x200, _XS=0x100, _XB=0x400). Those macros collide
// with libstdc++ identifiers (e.g. _UP in <bits/unique_ptr.h>), so os_defines.h
// undefs them project-wide. We therefore hardcode the mask values here instead
// of referencing the macros — the QNX 6.5 ctype ABI is frozen, so these are
// stable. (Keep in sync with <ctype.h> should the platform ever change.)

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  /// @brief  Base class for ctype.
  struct ctype_base
  {
    // Non-standard typedefs.
    typedef const unsigned char*	__to_type;

    // NB: Offsets into ctype<char>::_M_table force a particular size
    // on the mask type. Because of this, we don't use an enum.
    typedef short		mask;
    static const mask upper   = 0x002;	// _UP
    static const mask lower   = 0x010;	// _LO
    static const mask alpha   = 0x212;	// _LO | _UP | _XA
    static const mask digit   = 0x020;	// _DI
    static const mask xdigit  = 0x001;	// _XD
    static const mask space   = 0x144;	// _CN | _SP | _XS
    static const mask print   = 0x23e;	// _DI | _LO | _PU | _SP | _UP | _XA
    static const mask graph   = 0x23a;	// _DI | _LO | _PU | _UP | _XA
    static const mask cntrl   = 0x080;	// _BB
    static const mask punct   = 0x008;	// _PU
    static const mask alnum   = 0x232;	// _DI | _LO | _UP | _XA
  };

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace
