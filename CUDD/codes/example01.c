#include <stdio.h>

#include <cudd.h>

// test restrict and constains

int main() {
    DdManager* manager=Cudd_Init(4,
                                 0,
                                 CUDD_UNIQUE_SLOTS,
                                 CUDD_CACHE_SLOTS,
                                 0);

    // left shift rotation on two bits
    DdNode * x0 = Cudd_bddIthVar(manager, 0);
    DdNode * x1 = Cudd_bddIthVar(manager, 1);
    DdNode * x2 = Cudd_bddIthVar(manager, 2);
    DdNode * x3 = Cudd_bddIthVar(manager, 3);

    DdNode *T, *T0, *T1;

    T0 = Cudd_bddXnor(manager, x0, x3);
    Cudd_Ref(T0);

    T1 = Cudd_bddXnor(manager, x1, x2);
    Cudd_Ref(T1);

    T = Cudd_bddAnd(manager, T0, T1);
    Cudd_Ref(T);

    // T0, T1 are not needed anymore, recursively dereference them
    Cudd_RecursiveDeref(manager, T0);
    Cudd_RecursiveDeref(manager, T1);

    // states x0 && !x1
    DdNode * S;
    S = Cudd_bddAnd(manager, x0, Cudd_Not(x1));
    Cudd_Ref(S);

    DdNode * img = Cudd_bddRestrict(manager, T, S);
    Cudd_Ref(img);

    DdNode *one, *zero;
    one = Cudd_ReadOne(manager);
    zero = Cudd_ReadLogicZero(manager);

    Cudd_Ref(one);
    Cudd_Ref(zero);

    // validity check
    printf(img == one ? "valid\n" : "not valid\n");

    // unsat check
    printf(img == zero ? "unsat\n" : "sat\n");

    // equivalence check
    printf(img == T ? "equal\n" : "not equal\n");

    char *inpnames[4];
    inpnames[0] = "x0";
    inpnames[1] = "x1";
    inpnames[2] = "x2";
    inpnames[3] = "x3";

    char *outnames[3];
    outnames[0] = "T(x1x0, x3x2) : x1 == x2 && x0 == x3";
    outnames[1] = "S(x1x0) : !x1 && x0";
    outnames[2] = "Img(T, S) : S'(x3x2) = x3 && !x2";

    DdNode * outputs[3];
    outputs[0] = T;
    outputs[1] = S;
    outputs[2] = img;

    FILE * f = fopen("foo_viz.dot", "w");

    Cudd_DumpDot(manager, 3, outputs, inpnames, outnames, f);

    fclose(f);

    Cudd_RecursiveDeref(manager, T);
    Cudd_RecursiveDeref(manager, S);
    Cudd_RecursiveDeref(manager, img);
    Cudd_RecursiveDeref(manager, one);
    Cudd_RecursiveDeref(manager, zero);

    Cudd_Quit(manager);
    return 0;
}
