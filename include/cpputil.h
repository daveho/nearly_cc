// Copyright (c) 2021-2024, David H. Hovemeyer <david.hovemeyer@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

#ifndef CPPUTIL_H
#define CPPUTIL_H

//! @file
//! Utility functions for C++ code

#include <string>
#include <bitset>

namespace cpputil {

//! Use `printf` formatting to create a `std::string` value.
//! @param fmt the format string
//! @param ... the arguments (corresponding to conversions in the format string)
//! @return the formatted string
std::string format(const char *fmt, ...)
#ifdef __GNUC__
    __attribute__ ((format (printf, 1, 2)))
#endif
    ;

//! Format a `std::string` value from `printf`-style format string
//! and `va_list` containing argument values.
//! @param fmt the format string
//! @param args the arguments (corresponding to conversions in the format string)
//! @return the formatted string
std::string vformat(const char *fmt, va_list args);

//! Stringify a `std::bitset` by converting it to a comma-separated
//! list of integers (set members) surrounded by curly braces.
//! @tparam LEN bitset length (inferred from the argument)
//! @param b the bitset to stringify
template< std::size_t LEN >
std::string stringify_bitset( const std::bitset<LEN> &b ) {
  std::string s;
  s += "{";
  for (unsigned i = 0; i < LEN; ++i) {
    if (b.test(i)) {
      if (s.size() > 1)
        s += ",";
      s += std::to_string(i);
    }
  }
  s += "}";
  return s;
}

}

#endif // CPPUTIL_H
