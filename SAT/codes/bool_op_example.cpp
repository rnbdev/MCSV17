#include <iostream>
#include <minisat/core/Solver.h>
#include "bool_ops.cc"

int main() {
  Minisat::Solver S;

  // say I want to negate, f = (a | b) & (a | !b)

  Minisat::Lit a, b, f, c1, c2;
  a = Minisat::mkLit(S.newVar());
  b = Minisat::mkLit(S.newVar());

  c1 = lor(S, a,  b); // c1 = a |  b
  c2 = lor(S, a, ~b); // c2 = a | !b

  f = land(S, c1, c2); // f = c1 & c2 = (a | b) & (a | !b)

  Minisat::vec<Minisat::Lit> clause;
  clause.push(~f); // this way, solver is solving for !f
  S.addClause(clause);
  clause.clear();

  if(S.solve()) {
    std::cout << "SAT\n";
    std::cout << ((S.modelValue(a) == Minisat::l_True) ? "" : "-") << "a" << " ";
    std::cout << ((S.modelValue(b) == Minisat::l_True) ? "" : "-") << "b" << " ";
    std::cout << ((S.modelValue(f) == Minisat::l_True) ? "" : "-") << "c" << " ";
    std::cout << "\n";
  } else {
    std::cout << "UNSAT\n";
  }

  return 0;
}