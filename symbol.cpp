// Copyright (c) 2021-2023, David H. Hovemeyer <david.hovemeyer@gmail.com>
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

#include <cassert>
#include "symbol.h"

Symbol::Symbol(const std::string &name, Kind kind, StorageClass storage_class, const Type *type)
  : m_name(name)
  , m_kind(kind)
  , m_storage_class(storage_class)
  , m_type(type)
  , m_offset(0U) {
}

Symbol::~Symbol() {
}

void Symbol::promote_fn_decl_to_def() {
  assert(m_kind == FUNC_DECL);
  m_kind = FUNC_DEF;
}

void Symbol::set_codegen_name(const std::string &codegen_name) {
  m_codegen_name = codegen_name;
}

std::string Symbol::get_codegen_name() const {
  return m_codegen_name.empty() ? m_name : m_codegen_name;
}
