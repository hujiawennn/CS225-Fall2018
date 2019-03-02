/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if (first[curDim] == second[curDim])
     {
       return first < second;
     }
     return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double currentDistance = calDistance(target, currentBest);
     double potentialDistance = calDistance(target, potential);
     if (currentDistance == potentialDistance)
     {
       return potential < currentBest;
     }
     return currentDistance > potentialDistance;
}

template <int Dim>
double KDTree<Dim>:: calDistance(const Point<Dim> & m,
                              const Point<Dim> & n) const
{
     double dis = 0;
     for (int i = 0; i < Dim; i++)
     {
       dis = dis + (m[i] - n[i])*(m[i] - n[i]);
     }
     return dis;

}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     points = newPoints;
     size = points.size();
     root = KDTreeHelper(0, points.size() - 1, 0);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::KDTreeHelper(int left,
                                                             int right,
                                                             int dim) {
  if (left > right) {
    return NULL;
  }
  KDTreeNode * temp = new KDTreeNode;
  int mid = (left + right) / 2;
  quickSelect(left, right, mid, dim % Dim);
  int newDim = (dim + 1) % Dim;
  temp->point = points[mid];
  temp->left = KDTreeHelper(left, mid - 1, newDim);
  temp->right = KDTreeHelper(mid + 1, right, newDim);
  return temp;
}

template <int Dim>
void KDTree<Dim>::quickSelect(int left, int right, int k, int dim) {
    if (left >= right) {
      return;
    }
    int pivotIndex = (left + right) /2;
    pivotIndex = partition(left, right, pivotIndex, dim);
    if (pivotIndex == k) {
      return;
    }
    if (k < pivotIndex) {
      right = pivotIndex - 1;
      return quickSelect(left, right, k, dim);
    } else {
      left = pivotIndex + 1;
      return quickSelect(left, right, k, dim);
    }
  }

template <int Dim>
int KDTree<Dim>::partition(int left, int right, int k, int dim) {
  Point<Dim> pivotP = points[k];
  Point<Dim> temp = points[right];
  points[right] = points[k];
  points[k] = temp;
  int wall = left;
  for (int i = left; i < right; i++) {
    if (smallerDimVal(points[i], pivotP, dim) || pivotP == points[i]) {
      temp = points[wall];
      points[wall] = points[i];
      points[i] = temp;
      wall++;
    }
  }
  temp = points[right];
  points[right] = points[wall];
  points[wall] = temp;
  return wall;
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   root = other.root;
   size = other.size();
   points = other.points;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != & rhs) {
    clear (root);
    root = rhs.root;
    size = rhs.size();
    points = rhs.points;
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   clear(root);
}

template <int Dim>
void KDTree<Dim>::clear(KDTree<Dim>::KDTreeNode * root) {
  if (root == NULL) {
    return;
  }
  if (root != NULL) {
    clear(root->left);
    clear(root->right);
    delete root;
    root = NULL;
  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> nearestNeighbor = root->point;
    nearestNeighbor = findNNHelper(query, root, nearestNeighbor, 0);
    return nearestNeighbor;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNNHelper(const Point<Dim>& query,
                                     KDTreeNode* subroot,
                                     Point<Dim>& nearestNeighbor,
                                     int dim) const
{
  if (shouldReplace(query, nearestNeighbor, subroot->point)) {
    nearestNeighbor = subroot->point;
  }
  if (smallerDimVal(query,subroot->point, dim)) {
    if (subroot->left != NULL) {
      nearestNeighbor = findNNHelper(query, subroot->left, nearestNeighbor,
                                      (dim + 1) % Dim);
    }
    double currDis = (query[dim] - (subroot->point)[dim])*(query[dim]
                                 - (subroot->point)[dim]);
    if (calDistance(query, nearestNeighbor) >= currDis
                           && subroot->right != NULL) {
      nearestNeighbor = findNNHelper(query, subroot->right, nearestNeighbor,
                                      (dim + 1) % Dim);
    }
  } else {
    if (subroot->right != NULL) {
      nearestNeighbor = findNNHelper(query, subroot->right, nearestNeighbor,
                                      (dim + 1) % Dim);
    }
    double currDis = (query[dim] - (subroot->point)[dim]) * (query[dim]
                                 - (subroot->point)[dim]);
    if (calDistance(query, nearestNeighbor) >= currDis
                                            && subroot->left != NULL) {
      nearestNeighbor = findNNHelper(query, subroot->left, nearestNeighbor,
                                      (dim + 1) % Dim);
    }
  }
  return nearestNeighbor;
}
