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

#ifndef LIVE_VREGS_H
#define LIVE_VREGS_H

#include <string>
#include "instruction.h"
#include "highlevel_defuse.h"
#include "dataflow.h"

//! @file
//! Dataflow analysis to determine which virtual registers (in high-level code)
//! contain live values.

//! Dataflow analysis to determine which virtual registers (in high-level code)
//! contain live values.
class LiveVregsAnalysis : public BackwardAnalysis {
public:
  // We assume that there are never more than this many vregs used
  static const unsigned MAX_VREGS = 256;

  //! Fact type is a bitset of live virtual register numbers.
  typedef std::bitset<MAX_VREGS> FactType;

  //! The "top" fact is an unknown value that combines nondestructively
  //! with known facts. For this analysis, it's the empty set.
  FactType get_top_fact() const { return FactType(); }

  //! Combine live sets. For this analysis, we use union.
  FactType combine_facts(const FactType &left, const FactType &right) const {
    return left | right;
  }

  //! Model an instruction.
  //! @param ins the Instruction to model (backwards)
  //! @param fact initially represents what is true after the instruction
  //!             (in program order), and will be updated to represent what
  //!             is true before the instruction (in program order)
  void model_instruction(Instruction *ins, FactType &fact) const {
    // Model an instruction (backwards).  If the instruction is a def,
    // the assigned-to vreg is killed.  Every vreg used in the instruction,
    // the vreg becomes alive (or is kept alive.)

    if (HighLevel::is_def(ins)) {
      Operand operand = ins->get_operand(0);
      assert(operand.has_base_reg());
      fact.reset(operand.get_base_reg());
    }

    for (unsigned i = 0; i < ins->get_num_operands(); i++) {
      if (HighLevel::is_use(ins, i)) {
        Operand operand = ins->get_operand(i);

        assert(operand.has_base_reg());
        fact.set(operand.get_base_reg());

        if (operand.has_index_reg()) {
          fact.set(operand.get_index_reg());
        }
      }
    }
  }

  //! Model basic blocks by modeling the individual instructions
  //! in analysis order.
  ModelInstructionsInBasicBlock<LiveVregsAnalysis> MODEL_BLOCK;

  //! Convert a dataflow fact to a string (for printing the CFG annotated with
  //! dataflow facts)
  //! @param fact dataflow fact (set of virtual register numbers)
  //! @return string representation of the dataflow fact
  std::string fact_to_string(const FactType &fact) const {
    std::string s("{");
    for (unsigned i = 0; i < MAX_VREGS; i++) {
      if (fact.test(i)) {
        if (s != "{") { s += ","; }
        s += std::to_string(i);
      }
    }
    s += "}";
    return s;
  }
};

//! Convenient typedef for the type of a dataflow object for executing
//! LiveVregsAnalysis on a ControlFlowGraph.
typedef Dataflow<LiveVregsAnalysis> LiveVregs;

#endif // LIVE_VREGS_H
