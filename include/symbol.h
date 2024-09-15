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

#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include "has_operand.h"
class Type;

class Symbol : public HasOperand {
public:
  enum Kind {
    VAR_DEF,
    FUNC_DEF,
    FUNC_DECL,
    STRUCT_TYPE_DEF,
    UNION_TYPE_DEF,
  };

  enum StorageClass {
    STATIC,
    EXTERN,
    AUTO,
    GLOBAL,
    NONE,
  };

private:
  std::string m_name;
  Kind m_kind;
  StorageClass m_storage_class;
  const Type *m_type;
  std::string m_codegen_name;
  unsigned m_offset;

  // copy constructor and assignment operator are not allowed
  Symbol(const Symbol &);
  Symbol &operator=(const Symbol &);

public:
  Symbol(const std::string &name, Kind kind, StorageClass storage_class, const Type *type);
  virtual ~Symbol();

  const std::string &get_name() const    { return m_name; }
  Kind get_kind() const                  { return m_kind; }
  StorageClass get_storage_class() const { return m_storage_class; }
  const Type *get_type() const           { return m_type; }

  void promote_fn_decl_to_def();

  void set_codegen_name(const std::string &codegen_name);
  std::string get_codegen_name() const;

  void set_offset(unsigned offset) { m_offset = offset; }
  unsigned get_offset() const      { return m_offset; }
};


#endif // SYMBOL_H
