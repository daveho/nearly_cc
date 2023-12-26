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

#include <string>
#include <memory>
#include "highlevel.h"
#include "instruction_seq.h"
#include "ast_visitor.h"
#include "options.h"
#include "function.h"

// A HighLevelCodegen visitor generates high-level IR code for
// a single function. Code generation is initiated by visiting
// a function definition AST node.
class HighLevelCodegen : public ASTVisitor {
private:
  const Options &m_options;
  std::shared_ptr<Function> m_function;
  int m_next_label_num;
  std::string m_return_label_name; // name of the label that return instructions should target

public:
  // the next_label_num controls where the next_label() member function
  HighLevelCodegen(const Options &options, int next_label_num);
  virtual ~HighLevelCodegen();

  // Create a high-level InstructionSequence from a function definition AST.
  // The resulting InstructionSequence should be stored in the Function object.
  void generate(const std::shared_ptr<Function> &function);

  std::shared_ptr<InstructionSequence> get_hl_iseq() { return m_function->get_hl_iseq(); }

  int get_next_label_num() const { return m_next_label_num; }

  virtual void visit_function_definition(Node *n);
  virtual void visit_statement_list(Node *n);
  virtual void visit_expression_statement(Node *n);
  virtual void visit_return_statement(Node *n);
  virtual void visit_return_expression_statement(Node *n);
  virtual void visit_while_statement(Node *n);
  virtual void visit_do_while_statement(Node *n);
  virtual void visit_for_statement(Node *n);
  virtual void visit_if_statement(Node *n);
  virtual void visit_if_else_statement(Node *n);
  virtual void visit_binary_expression(Node *n);
  virtual void visit_unary_expression(Node *n);
  virtual void visit_function_call_expression(Node *n);
  virtual void visit_field_ref_expression(Node *n);
  virtual void visit_indirect_field_ref_expression(Node *n);
  virtual void visit_array_element_ref_expression(Node *n);
  virtual void visit_variable_ref(Node *n);
  virtual void visit_literal_value(Node *n);
  virtual void visit_implicit_conversion(Node *n);

private:
  std::string next_label();
  // TODO: additional private member functions
};
