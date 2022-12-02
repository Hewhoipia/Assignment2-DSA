#include "ConcatStringTree.h"

int main() {
    ConcatStringTree *A = new ConcatStringTree("Hello,");
    ConcatStringTree *B = new ConcatStringTree((" fuck"));
    ConcatStringTree *C = new ConcatStringTree((" this"));
    ConcatStringTree *D = new ConcatStringTree((" course!"));
    ConcatStringTree *E = new ConcatStringTree(A->concat(*B));
    ConcatStringTree *F = new ConcatStringTree(C->concat(*D));
    ConcatStringTree *G = new ConcatStringTree(E->concat(*F));
    ConcatStringTree* H = new ConcatStringTree("Hey! ");
    ConcatStringTree* T = new ConcatStringTree(H->concat(*A));
    return 0;
}