#include <minisat/core/Solver.h>
#include <iostream>

int main() {
  /* we want to solve CNF of this formula --
     (!x1 || x2) && (x1 || !x2) && (!x2 || !x1) && (x2 || x1)

     this is clearly a UNSAT.

     you may want to activate/deactivate some clause.
     that can be done by adding a switch variable to the clauses
     you want to control.

     say, you want to control last clause. then make it,
     (x2 || x1 || !s1)

     then, if s1 is TRUE, then the clause is activated,
     if s1 is FALSE, the clause is satisfied, hence deactivated.
   */

  Minisat::Solver s;
  Minisat::Var x1 = s.newVar();
  Minisat::Var x2 = s.newVar();

  Minisat::Var s1 = s.newVar();

  Minisat::vec<Minisat::Lit> clause;

  clause.push(~Minisat::mkLit(x1));
  clause.push(Minisat::mkLit(x2));

  s.addClause(clause);
  clause.clear();

  clause.push(Minisat::mkLit(x1));
  clause.push(~Minisat::mkLit(x2));

  s.addClause(clause);
  clause.clear();

  clause.push(~Minisat::mkLit(x2));
  clause.push(~Minisat::mkLit(x1));

  s.addClause(clause);
  clause.clear();

  clause.push(Minisat::mkLit(x2));
  clause.push(Minisat::mkLit(x1));
  clause.push(~Minisat::mkLit(s1));

  Minisat::vec<Minisat::Lit> assumptions;
  assumptions.push(~Minisat::mkLit(s1));

  s.addClause(clause);
  clause.clear();

  if(s.solve(assumptions)) {
    std::cout << "SAT" << "\n";
    for(int i = 0; i < s.nVars(); i++) {
      std::cout << (s.modelValue(i) == Minisat::l_True ? "" : "-") << (i + 1) << " ";
    }
    std::cout << "\n";
  } else {
    std::cout << "UNSAT" << "\n";
  }
}