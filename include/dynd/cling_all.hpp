//
// Copyright (C) 2011-12, Dynamic NDArray Developers
// BSD 2-Clause License, see LICENSE.txt
//

#ifndef _DND__CLING_ALL_HPP_
#define _DND__CLING_ALL_HPP_

// When CLING is enabled, we avoid certain glibc operations
// that generate inline assembly, unsupported by the LLVM JIT.
#define DND_CLING

#include <dynd/ndarray.hpp>
#include <dynd/ndarray_arange.hpp>

using namespace std;
using namespace dynd;

#endif // _DND__CLING_ALL_HPP_