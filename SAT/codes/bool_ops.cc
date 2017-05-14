#include <minisat/core/Solver.h>

Minisat::Lit land(Minisat::Solver &s, const Minisat::Lit &p1, const Minisat::Lit &p2) {
  // q = p1 & p2
  Minisat::Lit q = Minisat::mkLit(s.newVar());

  Minisat::vec<Minisat::Lit> clause;

  // q -> (p1 & p2) = !q | (p1 & p2) = (!q | p1) & (!q | p2)
  // (p1 & p2) -> q = (!p1 | !p2 | q)

  // adding (!q | p1)
  clause.push(~q);
  clause.push(p1);
  s.addClause(clause);
  clause.clear();

  // adding (!q | p2)
  clause.push(~q);
  clause.push(p2);
  s.addClause(clause);
  clause.clear();

  // adding (!p1 | !p2 | q)
  clause.push(~p1);
  clause.push(~p2);
  clause.push(q);
  s.addClause(clause);
  clause.clear();

  return q;
}

Minisat::Lit lor(Minisat::Solver &s, const Minisat::Lit &p1, const Minisat::Lit &p2) {
  // q = p1 | p2
  Minisat::Lit q = Minisat::mkLit(s.newVar());

  Minisat::vec<Minisat::Lit> clause;

  // q -> (p1 | p2) = (!q | p1 | p2)
  // (p1 | p2) -> q = (!p1 & !p2) | q = (!p1 | q) & (!p2 | q)

  // adding (!q | p1 | p2)
  clause.push(~q);
  clause.push(p1);
  clause.push(p2);
  s.addClause(clause);
  clause.clear();

  // adding (!p1 | q)
  clause.push(~p1);
  clause.push(q);
  s.addClause(clause);
  clause.clear();

  // adding (!p2 | q)
  clause.push(~p2);
  clause.push(q);
  s.addClause(clause);
  clause.clear();

  return q;
}
