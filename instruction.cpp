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
#include "instruction.h"

Instruction::Instruction(int opcode)
  : Instruction(opcode, Operand(), Operand(), Operand(), 0) {
}

Instruction::Instruction(int opcode, const Operand &op1)
  : Instruction(opcode, op1, Operand(), Operand(), 1) {
}

Instruction::Instruction(int opcode, const Operand &op1, const Operand &op2)
  : Instruction(opcode, op1, op2, Operand(), 2) {
}

Instruction::Instruction(int opcode, const Operand &op1, const Operand &op2, const Operand &op3, unsigned num_operands)
  : m_opcode(opcode)
  , m_num_operands(num_operands)
  , m_operands { op1, op2, op3 }
  , m_symbol(nullptr) {
}

Instruction::~Instruction() {
}

int Instruction::get_opcode() const {
  return m_opcode;
}

unsigned Instruction::get_num_operands() const {
  return m_num_operands;
}

const Operand &Instruction::get_operand(unsigned index) const {
  assert(index < m_num_operands);
  return m_operands[index];
}


void Instruction::set_operand(unsigned index, const Operand &operand) {
  assert(index < m_num_operands);
  m_operands[index] = operand;
}

Operand Instruction::get_last_operand() const {
  assert(m_num_operands > 0);
  return m_operands[m_num_operands - 1];
}
