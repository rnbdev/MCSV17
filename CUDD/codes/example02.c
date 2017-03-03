#include <stdio.h>

#include <cudd.h>

int main() {
  DdManager * manager = Cudd_Init(4, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0);

  DdNode * vars[6];
  for(int i = 0; i < 6; i++) {
    vars[i] = Cudd_bddIthVar(manager, i);
  }

  DdNode *s1, *s2;

  s1 = Cudd_bddAnd(manager, vars[0], Cudd_Not(vars[1]));
  s1 = Cudd_bddAnd(manager, s1, vars[2]);

  s2 = Cudd_bddAnd(manager, vars[3], Cudd_Not(vars[4]));
  s2 = Cudd_bddAnd(manager, s2, Cudd_Not(vars[5]));

  DdNode *T = Cudd_bddAnd(manager, s1, s2);
  Cudd_Ref(T);

  DdNode *c = Cudd_bddAnd(manager, vars[0], vars[1]);
  c = Cudd_bddAnd(manager, c, vars[2]);

  DdNode *t1 = Cudd_bddExistAbstract(manager, T, c);

  FILE *f = fopen("foo_viz.dot", "w");

  DdNode * outs[2];
  outs[0] = T;
  outs[1] = t1;

  Cudd_DumpDot(manager, 2, outs, NULL, NULL, f);

  fclose(f);
  Cudd_Quit(manager);
  return 0;
  
}