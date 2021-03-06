//
// Copyright (C) 2011-14 Mark Wiebe, DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#include <iostream>
#include <sstream>
#include <stdexcept>
#include "inc_gtest.hpp"

#include <dynd/array.hpp>
#include <dynd/types/tuple_type.hpp>
#include <dynd/types/fixedstring_type.hpp>

using namespace std;
using namespace dynd;

TEST(TupleDType, CreateOneField) {
    ndt::type dt;
    const tuple_type *tdt;

    // Tuple with one field
    dt = ndt::make_tuple(ndt::make_type<int32_t>());
    EXPECT_EQ(tuple_type_id, dt.get_type_id());
    EXPECT_EQ(4u, dt.get_data_size());
    EXPECT_EQ(4u, dt.get_data_alignment());
    EXPECT_TRUE(dt.is_pod());
    EXPECT_EQ(0u, (dt.get_flags()&(type_flag_blockref|type_flag_destructor)));
    tdt = static_cast<const tuple_type *>(dt.extended());
    EXPECT_TRUE(tdt->is_standard_layout());
    EXPECT_EQ(1u, tdt->get_fields().size());
    EXPECT_EQ(1u, tdt->get_offsets().size());
    EXPECT_EQ(ndt::make_type<int32_t>(), tdt->get_fields()[0]);
    EXPECT_EQ(0u, tdt->get_offsets()[0]);
}

