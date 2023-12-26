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

#ifndef INSTRUCTION_SEQ_H
#define INSTRUCTION_SEQ_H

#include <vector>
#include <string>
#include <map>
#include "instruction_seq_iter.h"

class Instruction;

// An InstructionSequence can be used to represent a basic block
// in a control flow graph. These are the kinds of basic blocks.
enum BasicBlockKind {
  BASICBLOCK_ENTRY,     // special "entry" block
  BASICBLOCK_EXIT,      // special "exit" block
  BASICBLOCK_INTERIOR,  // normal basic block in the "interior" of the CFG
};

class InstructionSequence {
private:
  struct Slot {
    std::string label;
    Instruction *ins;
  };

  std::vector<Slot> m_instructions;
  std::map<std::string, unsigned> m_label_map; // label to instruction index map
  std::string m_next_label;

  // These fields are only used for InstructionSequences
  BasicBlockKind m_kind;
  std::string m_block_label;
  unsigned m_block_id;
  int m_code_order;

  // copy constructor and assignment operator are not allowed
  InstructionSequence(const InstructionSequence &);
  InstructionSequence &operator=(const InstructionSequence &);

public:
  // Iterator types, providing a pointer to an Instruction object when
  // dereferenced. These are random access.
  typedef ISeqIterator<std::vector<Slot>::const_iterator> const_iterator;
  typedef ISeqIterator<std::vector<Slot>::const_reverse_iterator> const_reverse_iterator;

  InstructionSequence();
  InstructionSequence(BasicBlockKind kind, int code_order, const std::string &block_label);
  virtual ~InstructionSequence();

  // Return a dynamically-allocated duplicate of this InstructionSequence
  InstructionSequence *duplicate() const;

  // get begin and end const_iterators
  const_iterator cbegin() const { return const_iterator(m_instructions.cbegin()); }
  const_iterator cend() const { return const_iterator(m_instructions.cend()); }

  // get begin and end const_reverse_iterators
  const_reverse_iterator crbegin() const { return const_reverse_iterator(m_instructions.crbegin()); }
  const_reverse_iterator crend() const { return const_reverse_iterator(m_instructions.crend()); }

  // apply a function to each Instruction in order
  template<typename Fn>
  void apply_to_all(Fn f) {
    for (auto i = cbegin(); i != cend(); ++i)
      f(*i);
  }

  // Append a pointer to an Instruction.
  // The InstructionSequence will assume responsibility for deleting the
  // Instruction object.
  void append(Instruction *ins);

  // Get number of Instructions.
  unsigned get_length() const;

  // Get Instruction at specified index.
  Instruction *get_instruction(unsigned index) const;

  // Get the last Instruction.
  Instruction *get_last_instruction() const;

  // Define a label. The next Instruction appended will be labeled with
  // this label.
  void define_label(const std::string &label);

  // Determine if Instruction at given index has a label.
  bool has_label(unsigned index) const { return !m_instructions.at(index).label.empty(); }

  // Get label at specified index
  std::string get_label_at_index(unsigned index) const { return m_instructions.at(index).label; }

  // Determine if Instruction referred to by specified iterator has a label.
  bool has_label(const_iterator i) const { return i.has_label(); }

  // Determine if the InstructionSequence has a label at the end
  bool has_label_at_end() const;

  // Return a forward const iterator positioned at the instruction with
  // the specified label, or the end iterator if there is no instruction
  // with the specified label
  const_iterator get_iterator_at_labeled_position(const std::string &label) const;

  // Find Instruction labeled with specified label.
  // Returns null pointer if no Instruction has the specified label.
  Instruction *find_labeled_instruction(const std::string &label) const;

  // Return the index of instruction labeled with the specified label.
  unsigned get_index_of_labeled_instruction(const std::string &label) const;

  // Member functions used for basic blocks
  BasicBlockKind get_kind() const { return m_kind; }
  void set_kind(BasicBlockKind kind) { m_kind = kind; }
  bool has_block_label() const { return !m_block_label.empty(); }
  std::string get_block_label() const { return m_block_label; }
  void set_block_label(const std::string &block_label) { m_block_label = block_label; }
  unsigned get_block_id() const { return m_block_id; }
  void set_block_id(unsigned block_id) { m_block_id = block_id; }
  int get_code_order() const { return m_code_order; }
  void set_code_order(int code_order) { m_code_order = code_order; }
};

#endif // INSTRUCTION_SEQ_H
