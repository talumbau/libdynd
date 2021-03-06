//
// Copyright (C) 2011-14 Mark Wiebe, DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cmath>

#include "inc_gtest.hpp"

#include <dynd/json_formatter.hpp>
#include <dynd/json_parser.hpp>
#include <dynd/types/var_dim_type.hpp>
#include <dynd/types/fixed_dim_type.hpp>
#include <dynd/types/cstruct_type.hpp>
#include <dynd/types/date_type.hpp>
#include <dynd/types/string_type.hpp>
#include <dynd/types/json_type.hpp>

using namespace std;
using namespace dynd;

TEST(JSONFormatter, Builtins) {
    nd::array n;
    n = true;
    EXPECT_EQ("true", format_json(n).as<string>());
    n = false;
    EXPECT_EQ("false", format_json(n).as<string>());
    n = (int8_t)-27;
    EXPECT_EQ("-27", format_json(n).as<string>());
    n = (int16_t)-30000;
    EXPECT_EQ("-30000", format_json(n).as<string>());
    n = (int32_t)-2000000000;
    EXPECT_EQ("-2000000000", format_json(n).as<string>());
    n = (int64_t)-10000000000LL;
    EXPECT_EQ("-10000000000", format_json(n).as<string>());
    n = (uint8_t)200;
    EXPECT_EQ("200", format_json(n).as<string>());
    n = (uint16_t)40000;
    EXPECT_EQ("40000", format_json(n).as<string>());
    n = (uint32_t)3000000000u;
    EXPECT_EQ("3000000000", format_json(n).as<string>());
    n = (uint64_t)10000000000LL;
    EXPECT_EQ("10000000000", format_json(n).as<string>());
    n = 3.125f;
    EXPECT_EQ("3.125", format_json(n).as<string>());
    n = 3.125;
    EXPECT_EQ("3.125", format_json(n).as<string>());
}

TEST(JSONFormatter, String) {
    nd::array n;
    n = "testing string";
    EXPECT_EQ("\"testing string\"", format_json(n).as<string>());
    n = " \" \\ / \b \f \n \r \t ";
    EXPECT_EQ("\" \\\" \\\\ \\/ \\b \\f \\n \\r \\t \"", format_json(n).as<string>());
    n = nd::array("testing string").ucast(ndt::make_string(string_encoding_utf_16)).eval();
    EXPECT_EQ("\"testing string\"", format_json(n).as<string>());
    n = nd::array("testing string").ucast(ndt::make_string(string_encoding_utf_32)).eval();
    EXPECT_EQ("\"testing string\"", format_json(n).as<string>());
}

TEST(JSONFormatter, JSON) {
    nd::array n;
    n = nd::array("[ 1, 3, 5] ").ucast(ndt::make_json());
    EXPECT_EQ("[ 1, 3, 5] ", format_json(n).as<string>());
}

TEST(JSONFormatter, Struct) {
    nd::array n = parse_json("{ a: int32, b: string, c: json }",
                    "{ \"b\": \"testing\",  \"a\":    100,\n"
                    "\"c\": [   {\"first\":true, \"second\":3}, null,\n \"test\"]  }");
    EXPECT_EQ("{\"a\":100,\"b\":\"testing\","
                    "\"c\":[   {\"first\":true, \"second\":3}, null,\n \"test\"]}",
                    format_json(n).as<string>());
}

TEST(JSONFormatter, UniformDim) {
    nd::array n;
    float vals[] = {3.5f, -1.25f, 4.75f};
    // Strided dimension
    n = vals;
    EXPECT_EQ("[3.5,-1.25,4.75]", format_json(n).as<string>());
    // Variable-sized dimension
    n = parse_json("var * string", "[\"testing\", \"one\", \"two\"] ");
    EXPECT_EQ("[\"testing\",\"one\",\"two\"]", format_json(n).as<string>());
    // Fixed dimension
    n = parse_json("3 * string", "[\"testing\", \"one\", \"two\"] ");
    EXPECT_EQ("[\"testing\",\"one\",\"two\"]", format_json(n).as<string>());
}

