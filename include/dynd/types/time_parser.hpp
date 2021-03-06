//
// Copyright (C) 2011-14 Mark Wiebe, DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#ifndef _DYND__TIME_PARSER_HPP_
#define _DYND__TIME_PARSER_HPP_

#include <dynd/config.hpp>

namespace dynd {

struct time_hmst;

/**
 * Parses a time.
 *
 * \param begin  The start of the UTF-8 buffer to parse.
 * \param end  One past the last character of the buffer to parse.
 * \param out_hmst  The time to fill.
 *
 * \returns  True if the parse is successful, false otherwise.
 */
bool string_to_time(const char *begin, const char *end, time_hmst &out_hmst);

namespace parse {

    /**
     * Parses a time
     *
     * \param begin  The start of a range of UTF-8 characters. This is modified
     *               to point immediately after the parsed time if true is returned.
     * \param end  The end of a range of UTF-8 characters.
     * \param out_hmst  The time to fill.
     *
     * \returns  True if a time was parsed successfully, false otherwise.
     */
    bool parse_time(const char *&begin, const char *end, time_hmst &out_hmst);

    /**
     * Without skipping whitespace, parses an AM/PM indicator string and modifies
     * the provided hour appropriately. If the AM/PM is incompatible with the
     * hour value, sets the hour value to -1.
     */
    bool parse_time_ampm(const char *&begin, const char *end, int& inout_hour);

} // namespace parse

} // namespace parse

#endif // _DYND__TIME_PARSER_HPP_
