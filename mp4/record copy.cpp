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

}

ImageTraversal::Iterator::Iterator(ImageTraversal* input,Point p,double tolerance, PNG png) {
  pos = p;
  tole = tolerance;
  im = png;
  d = input;
  startPixel = im.getPixel((pos).x, (pos).y);
  Point trivial = d->pop();
  vec.reserve(im.width()*im.height());
  vec.push_back(pos.x + (pos.y)*im.width());
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
  Point temp = d->pop();
  HSLAPixel& thisPixel = im.getPixel(temp.x, temp.y);
  double x = calculateDelta(startPixel, thisPixel);
  bool visited = checkVisted_(temp.x,temp.y);
  while (!d->empty() && (visited || x > tole)) {
    temp = d->pop();
    thisPixel = im.getPixel(temp.x, temp.y);
    x = calculateDelta(startPixel, thisPixel);
    visited = checkVisted_(temp.x,temp.y);
  }
  pos = temp;
  vec.push_back(temp.x + temp.y * im.width());
//  if (checkVisted_(temp.x+1,temp.y) && checkVisted_(temp.x, temp.y+1) && checkVisted_(temp.x -1,temp.y) && checkVisted_(temp.x,temp.y-1)) {
    if (d->empty()) {
      checkEnd = true;
      return *this;
    }
//  }
  addNeighbors_(temp);
  return *this;
}

bool ImageTraversal::Iterator::checkVisted_(unsigned x, unsigned y) {
  int checkValue = x + y * im.width();
  for (unsigned i = 0; i < vec.size(); i++) {
    if (vec[i] == checkValue) {
      return true;
    }
  }
  return false;
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
  // if (this->im == other.im) {
  //   if (this->pos == other.pos) {
  //     return false;
  //   }
  // }
  // return true;
  return checkEnd != other.checkEnd;
}

ImageTraversal::ImageTraversal(const PNG image,const Point point,double tolerance) {
  startPoint_ = point;
  image_ = image;
  tolerance_ = tolerance;
}
