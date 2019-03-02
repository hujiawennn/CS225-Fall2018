#include <cmath>
#include <iterator>
#include <iostream>
#include <vector>
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
using namespace std;
/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  d = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* input,Point p,double tolerance, PNG png) {
  pos = p;
  tole = tolerance;
  im = png;
  d = input;
  startPixel = im.getPixel((pos).x, (pos).y);
  Point trivial = d->pop();
  vec.resize(im.width()*im.height(), true);
  vec[pos.x + (pos.y)*im.width()] = false;
  addNeighbors_(pos);
  checkEnd = false;
}

void ImageTraversal::Iterator::addNeighbors_(Point p) {
  unsigned currX = p.x;
  unsigned currY = p.y;
  if (currX + 1 < im.width()){
    d->add(Point(currX + 1, currY));
  }
  if (currY + 1 < im.height()){
    d->add(Point(currX, currY + 1));
  }
  if (currX >= 1){
  d->add(Point(currX - 1, currY));
  }
  if (currY >= 1){
  d->add(Point(currX, currY - 1));
  }
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  Point temp;
  double x;
  bool visited;
  while (!d->empty()) {
    temp = d->pop();
    HSLAPixel& thisPixel = im.getPixel(temp.x, temp.y);
    x = calculateDelta(startPixel, thisPixel);
    visited = checkVisted_(temp.x,temp.y);
    if (x <= tole && visited) {
      break;
    }
  }
  pos = temp;
  vec[temp.x + temp.y * im.width()] = false;
    if (d->empty()) {
      return *this;
    }
  addNeighbors_(temp);
  return *this;
}

bool ImageTraversal::Iterator::checkVisted_(unsigned x, unsigned y) {
  if (vec[x+y*im.width()] == false) {return false;}
  return true;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  return pos;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  //return checkEnd != other.checkEnd;
  bool thisEmpty = false;
  bool otherEmpty = false;

  if (d == NULL) { thisEmpty = true; }
  if (other.d == NULL) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = d->empty(); }
  if (!otherEmpty) { otherEmpty = other.d->empty(); }

  if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
  else if ((!thisEmpty)&&(!otherEmpty)) return (d != other.d); //both not empty then compare the traversals
  else return true; // one is empty while the other is not, return true
}

ImageTraversal::ImageTraversal(const PNG image,const Point point,double tolerance) {
  startPoint_ = point;
  image_ = image;
  tolerance_ = tolerance;
}
