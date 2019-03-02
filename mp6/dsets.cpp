/* Your code here! */
#include "dsets.h"
#include <vector>
using namespace std;
void DisjointSets::addelements(int num) {
  for (int i = 0; i < num; i++) {
    sets.push_back(-1);
  }
  return;
}

int DisjointSets::find (int elem) {
  if (sets[elem] < 0) {
    return elem;
  }
  return find(sets[elem]);
}

void DisjointSets::setunion(int a, int b) {
  int rootFi = find(a);
  int rootSe = find(b);
  if (rootFi == rootSe) {
    return;
  }
  int newSize = sets[rootFi] + sets[rootSe];
  if (sets[rootFi] <= sets[rootSe]) {
    sets[rootSe] = rootFi;
    sets[rootFi] = newSize;
  } else {
    sets[rootFi] = rootSe;
    sets[rootSe] = newSize;
  }
  return;
}

int DisjointSets::size(int elem) {
  int root = find(elem);
  return -1 * sets[root];
}
