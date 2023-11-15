// Low-level functions for atomic operations: version for CPUs providing
// atomic builtins -*- C++ -*-

// Copyright (C) 2006-2023 Free Software Foundation, Inc.
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

#include <bits/atomic_word.h>
#include <bits/c++config.h>

namespace __gnu_cxx _GLIBCXX_VISIBILITY(default) {
_GLIBCXX_BEGIN_NAMESPACE_VERSION

static inline int __DIntr() {
  int eie, res;

  asm volatile("mfc0\t%0, $12" : "=r"(eie));
  eie &= 0x10000;
  res = eie != 0;

  if (!eie)
    return 0;

  asm(".p2align 3");
  do {
    asm volatile("di");
    asm volatile("sync.p");
    asm volatile("mfc0\t%0, $12" : "=r"(eie));
    eie &= 0x10000;
  } while (eie);

  return res;
}

static inline int __EIntr() {
  int eie;

  asm volatile("mfc0\t%0, $12" : "=r"(eie));
  eie &= 0x10000;
  asm volatile("ei");

  return eie != 0;
}

_Atomic_word __attribute__((__unused__))
__exchange_and_add(volatile _Atomic_word *__mem, int __val) throw() {
  _Atomic_word __result;
  int isr = __DIntr();

  __result = *__mem;
  *__mem += __val;

  if (isr)
    __EIntr();

  return __result;
}

void __attribute__((__unused__))
__atomic_add(volatile _Atomic_word *__mem, int __val) throw() {
  __exchange_and_add(__mem, __val);
}

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace __gnu_cxx _GLIBCXX_VISIBILITY(default)
