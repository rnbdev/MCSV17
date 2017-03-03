#include <minisat/core/Dimacs.h>
#include <minisat/core/Solver.h>

#include <zlib.h>
#include <iostream>

using namespace Minisat;


int main(int argc, char** argv) {
  // create Solver
  Solver S;

  gzFile gf;
  if(argc == 1) {
    // no argument given, will read from STDIN
    gf = gzdopen(0, "rb");
  } else {
    // else open the DIMACS file
    gf = gzopen(argv[1], "rb");
  }
  // read the DIMACS and update solver database
  parse_DIMACS(gf, S);

  // done with file, close it
  gzclose(gf);


  // create new var
  S.newVar();

  // create new clause
  vec<Lit> clause;

  // add literals to clause
  clause.push(~mkLit(S.nVars()-1));  // negate using ~
  clause.push(mkLit(0, 0));  // mkLit(x, 0) will create x
  clause.push(mkLit(1, 1));  // mkLit(x, 1) will create ~x
  
  // add clause to solver database
  S.addClause(clause);

  // solve it
  if(S.solve()) {
    // if SAT, print an assignment/model
    std::cout << "SAT\n";
    for(int i = 0; i < S.nVars(); i++) {
      // modelValue returns assignment value for a variable
      std::cout << ((S.modelValue(i) == l_True) ? "" : "-") << (i + 1) << " ";
    }
    std::cout << "\n";
  } else {
    // else UNSAT
    std::cout << "UNSAT\n";
  }


  return 0;
}