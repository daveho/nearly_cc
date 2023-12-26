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

#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <cassert>
#include <map>
#include "node.h"
#include "symtab.h"
#include "instruction_seq.h"

// Function encapsulates all of the information needed to generate
// and optimize code for a function. This includes (at a minimum)
// the function name, function definition AST, the symbol table entry,
// generated high-level code, and generated low-level code.  However, you
// can add any additional fields that would be helpful.  In particular,
// any information about a function that needs to be communicated between
// phases, such as storage allocation decisions, can also be collected in
// the Function object.
class Function {
private:
  std::string m_name;
  Node *m_funcdef_ast; // function definition AST node
  Symbol *m_symbol; // function symbol table entry
  std::shared_ptr<InstructionSequence> m_hl_iseq; // high-level code
  std::shared_ptr<InstructionSequence> m_ll_iseq; // low-level code

public:
  Function(const std::string &name, Node *funcdef_ast, Symbol *symbol);
  ~Function();

  std::string get_name() const;

  Node *get_funcdef_ast() const;
  Symbol *get_symbol() const;

  std::shared_ptr<InstructionSequence> get_hl_iseq() const;
  void set_hl_iseq(const std::shared_ptr<InstructionSequence> &hl_iseq);

  std::shared_ptr<InstructionSequence> get_ll_iseq() const;
  void set_ll_iseq(const std::shared_ptr<InstructionSequence> &ll_iseq);

};

#endif // FUNCTION_H
