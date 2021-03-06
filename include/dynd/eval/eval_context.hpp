//
// Copyright (C) 2011-14 Mark Wiebe, DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#ifndef _DYND__EVAL_CONTEXT_HPP_
#define _DYND__EVAL_CONTEXT_HPP_

#include <dynd/config.hpp>

#ifdef DYND_USE_STD_ATOMIC
#include <atomic>
#endif

#include <dynd/config.hpp>
#include <dynd/typed_data_assign.hpp>
#include <dynd/types/date_util.hpp>

namespace dynd { namespace eval {

struct eval_context {
    // If the compiler supports atomics, use them for access
    // to the evaluation context settings, 
#ifdef DYND_USE_STD_ATOMIC
    // Default error mode for computations
    std::atomic<assign_error_mode> default_errmode;
    // Default error mode for CUDA device to device computations
    std::atomic<assign_error_mode> default_cuda_device_errmode;
    // Parse order of ambiguous date strings
    std::atomic<date_parse_order_t> date_parse_order;
    // Century selection for 2 digit years in date strings
    std::atomic<int> century_window;
#else
    // Default error mode for computations
    assign_error_mode default_errmode;
    // Default error mode for CUDA device to device computations
    assign_error_mode default_cuda_device_errmode;
    // Parse order of ambiguous date strings
    date_parse_order_t date_parse_order;
    // Century selection for 2 digit years in date strings
    int century_window;
#endif

    DYND_CONSTEXPR eval_context()
        : default_errmode(assign_error_fractional),
          default_cuda_device_errmode(assign_error_none),
          date_parse_order(date_parse_no_ambig), century_window(70)
    {
    }

#ifdef DYND_USE_STD_ATOMIC
    DYND_CONSTEXPR eval_context(const eval_context &rhs)
        : default_errmode(rhs.default_errmode.load()),
          default_cuda_device_errmode(rhs.default_cuda_device_errmode.load()),
          date_parse_order(rhs.date_parse_order.load()),
          century_window(rhs.century_window.load())
    {
    }
#endif
};

extern const eval_context default_eval_context;

}} // namespace dynd::eval

#endif // _DYND__EVAL_CONTEXT_HPP_
