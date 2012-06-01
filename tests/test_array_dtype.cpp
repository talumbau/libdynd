#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stdint.h>
#include "inc_gtest.hpp"

#include "dnd/dtype_casting.hpp"
#include "dnd/array_dtype.hpp"

using namespace std;
using namespace dnd;

TEST(ArrayDType, LosslessCasting) {
    intptr_t shape_235[] = {2,3,5}, shape_215[] = {2,1,5}, shape_35[] = {3,5};
    dtype adt_int_235 = make_array_dtype<int>(3, shape_235);
    dtype adt_int_215 = make_array_dtype<int>(3, shape_215);
    dtype adt_int_35 = make_array_dtype<int>(2, shape_35);

    dtype adt_int16_215 = make_array_dtype<int16_t>(3, shape_215);
    dtype adt_int64_215 = make_array_dtype<int64_t>(3, shape_215);

    // Broadcasting equal types treated as lossless
    EXPECT_TRUE(casting_is_lossless(adt_int_235, adt_int_215));
    EXPECT_TRUE(casting_is_lossless(adt_int_235, adt_int_35));
    EXPECT_FALSE(casting_is_lossless(adt_int_215, adt_int_235));
    EXPECT_TRUE(casting_is_lossless(adt_int_235, make_dtype<int>()));

    // Broadcasting unequal type follows the element type's rules
    EXPECT_TRUE(casting_is_lossless(adt_int_235, adt_int16_215));
    EXPECT_FALSE(casting_is_lossless(adt_int_235, adt_int64_215));

    // Scalars broadcast to arrays
    EXPECT_TRUE(casting_is_lossless(adt_int_235, make_dtype<int16_t>()));
    EXPECT_FALSE(casting_is_lossless(adt_int_235, make_dtype<int64_t>()));
    EXPECT_FALSE(casting_is_lossless(make_dtype<int64_t>(), adt_int_235));
}

TEST(ArrayDType, StringOutput) {
    intptr_t shape_235[] = {2,3,5};
    dtype adt_int_235 = make_array_dtype<int>(3, shape_235);

    // Verify the current string representation [note it does not include strides at the moment]
    stringstream ss;
    ss << adt_int_235;
    EXPECT_EQ("array<int32, (2,3,5)>", ss.str());
}