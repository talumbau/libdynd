//
// Copyright (C) 2011 Mark Wiebe (mwwiebe@gmail.com)
// All rights reserved.
//
// This is unreleased proprietary software.
//
#ifndef _DND__CONFIG_HPP_
#define _DND__CONFIG_HPP_

#ifdef __clang__

//#  define DND_RVALUE_REFS
//#  define DND_INIT_LIST

// NOTE: I hacked the g++ system headers, adding explicit copy constructors and assignment
//       operators to both shared_ptr and __shared_ptr (in shared_ptr_base.h), so that clang
//       would accept them. This is because the LLVM JIT used by CLING complains about inline
//       assembly with the boost version, but not with the g++ version.
//#define USE_BOOST_SHARED_PTR
// TODO: versions with constexpr
#  define DND_CONSTEXPR constexpr

#elif defined(__GNUC__)

// TODO: Specific gcc versions with rvalue ref support
#  define DND_RVALUE_REFS
// TODO: Specific gcc versions with initializer list support
#  define DND_INIT_LIST
// TODO: versions with constexpr
#  define DND_CONSTEXPR constexpr

#elif defined(_MSC_VER) && _MSC_VER >= 1600

// Use enable_if from std::tr1
#  define DND_USE_TR1_ENABLE_IF
// No DND_CONSTEXPR yet
#  define DND_CONSTEXPR
#endif

// If RValue References are supported
#ifdef DND_RVALUE_REFS
#  define DND_MOVE(x) (std::move(x))
#else
#  define DND_MOVE(x) (x)
#endif

// Whether to use boost's shared_ptr or the standard library's
#ifdef DND_USE_BOOST_SHARED_PTR
#include <boost/shared_ptr.hpp>
namespace dnd {
    using ::boost::shared_ptr;
    using ::boost::make_shared;
}
#else
#include <memory>
namespace dnd {
    using ::std::shared_ptr;
    using ::std::make_shared;
}
#endif

// If Initializer Lists are supported
#ifdef DND_INIT_LIST
#include <initializer_list>
#endif

// If being run from the CLING C++ interpreter
#ifdef DND_CLING
// 1) Used g++ shared_ptr instead of boost shared_ptr (see above in clang config section).
//    This allowed dtypes to be created in cling!
// 2) Don't use the memcpy function (it has inline assembly).

inline void DND_MEMCPY(void *dst, const void *src, intptr_t count)
{
    char *cdst = (char *)dst;
    const char *csrc = (const char *)src;
    while (count--) {
        *cdst++ = *csrc++;
    }
}
#else
#include <cstring>
#define DND_MEMCPY(a, b, c) std::memcpy(a, b, c)
#endif

#ifdef DND_USE_TR1_ENABLE_IF
#include <type_traits>
namespace dnd {
    using std::tr1::enable_if;
}
#else
#include <boost/utility/enable_if.hpp>
namespace dnd {
    using boost::enable_if;
}
#endif

#endif // _DND__CONFIG_HPP_