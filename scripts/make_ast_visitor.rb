#! /usr/bin/env ruby

# This script should should read from ast.h via STDIN
# (see the Makefile)

HEADER_BEGIN = <<'EOF1'
#ifndef AST_VISITOR_H
#define AST_VISITOR_H

// Generated ASTVisitor class
// Do not edit this file!

class Node;

class ASTVisitor {
public:
  ASTVisitor();
  virtual ~ASTVisitor();

  virtual void visit(Node *ast);

EOF1

DEFAULT_METHOD_IMPL = <<'EOF2'
  recur_on_children(ast);
}

EOF2

HEADER_END = <<'EOF3'

  virtual void recur_on_children(Node *ast);
};

#endif // AST_VISITOR_H
EOF3

IMPL_BEGIN = <<'EOF4'
// Generated ASTVisitor class
// Do not edit this file!

#include "node.h"
#include "ast.h"
#include "ast_visitor.h"

ASTVisitor::ASTVisitor() {
}

ASTVisitor::~ASTVisitor() {
}

EOF4

IMPL_END = <<'EOF5'

void ASTVisitor::recur_on_children(Node *ast) {
  unsigned num_kids = ast->get_num_kids();
  for (unsigned i = 0; i < num_kids; i++) {
    visit(ast->get_kid(i));
  }
}
EOF5

def to_method_name(t)
  trimmed_name = t[4..-1]
  return "visit_#{trimmed_name.downcase}"
end

# Find all of the AST node types
node_types = []
STDIN.each_line do |line|
  if m = /(AST_[A-Z_]+)/.match(line)
    node_types.push(m[1]) if m[1] != 'AST_H'
  end
end

#node_types.each do |t|
#  puts t
#end

File.open('ast_visitor.h', 'w') do |outf|
  outf.print HEADER_BEGIN

  node_types.each do |t|
    outf.puts "  virtual void #{to_method_name(t)}(Node *ast);"
  end

  outf.print HEADER_END
end

File.open('ast_visitor.cpp', 'w') do |outf|
  outf.print IMPL_BEGIN

  outf.puts "void ASTVisitor::visit(Node *ast) {"
  outf.puts "  switch (ast->get_tag()) {"
  node_types.each do |t|
    outf.puts "  case #{t}:"
    outf.puts "    #{to_method_name(t)}(ast);"
    outf.puts "    break;"
  end
  outf.puts "  }"
  outf.puts "}"
  outf.puts ""

  node_types.each do |t|
    outf.puts "void ASTVisitor::#{to_method_name(t)}(Node *ast) {"
    outf.print DEFAULT_METHOD_IMPL
  end

  outf.print IMPL_END
end
