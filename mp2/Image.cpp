#include "Image.h"
using namespace cs225;
#include <stdio.h>
#include <math.h>
#include <iostream>
void Image::lighten(){
  for (unsigned i = 0; i < width(); i++) {
    for (unsigned int j = 0; j < height(); j++) {
      HSLAPixel & pixel = getPixel(i, j);
      pixel.l += 0.1;
      if (pixel.l > 1) {
        pixel.l =1;
      } else if (pixel.l < 0) {
        pixel.l = 0;
      }
    }
  }
}

void Image::lighten(double amount){
  for (unsigned int i = 0; i < width(); i++) {
    for (unsigned j = 0; j < height(); j++) {
      HSLAPixel & pixel = getPixel(i, j);
      pixel.l += amount;
      if (pixel.l > 1) {
        pixel.l =1;
      } else if (pixel.l < 0) {
        pixel.l = 0;
    }
  }
}
}

void Image::darken(){
  for (unsigned i = 0; i < width(); i++) {
    for (unsigned j = 0; j < height(); j++) {
      HSLAPixel & pixel = getPixel(i, j);
      pixel.l -= 0.1;
      if (pixel.l > 1) {
        pixel.l =1;
      } else if (pixel.l < 0) {
        pixel.l = 0;
    }
    }
  }
}

void Image::darken(double amount){
  for (unsigned i = 0; i < width(); i++) {
    for (unsigned j = 0; j < height(); j++) {
      HSLAPixel & pixel = getPixel(i, j);
      pixel.l -= amount;
      if (pixel.l > 1) {
        pixel.l =1;
      } else if (pixel.l < 0) {
        pixel.l = 0;
    }
    }
  }
}

void Image::saturate(){
  for (unsigned i = 0; i < width(); i++) {
    for (unsigned j = 0; j < height(); j++) {
      HSLAPixel & pixel = getPixel(i, j);
      pixel.s += 0.1;
      if (pixel.s > 1) {
        pixel.s =1;
      } else if (pixel.s < 0) {
        pixel.s = 0;
    }
    }
  }
}

void Image::saturate(double amount){
for (unsigned i = 0; i < width(); i++) {
  for (unsigned j = 0; j < height(); j++) {
    HSLAPixel & pixel = getPixel(i, j);
    pixel.s += amount;
    if (pixel.s > 1) {
      pixel.s =1;
    } else if (pixel.s < 0) {
      pixel.s = 0;
  }
  }
}
}

void Image::desaturate(){
  for (unsigned i = 0; i < width(); i++) {
    for (unsigned j = 0; j < height(); j++) {
      HSLAPixel & pixel = getPixel(i, j);
      pixel.s -= 0.1;
      if (pixel.s > 1) {
        pixel.s =1;
      } else if (pixel.s < 0) {
        pixel.s = 0;
    }
    }
  }
}

void Image::desaturate(double amount){
for (unsigned i = 0; i < width(); i++) {
  for (unsigned j = 0; j < height(); j++) {
    HSLAPixel & pixel = getPixel(i, j);
    pixel.s -= amount;
    if (pixel.s > 1) {
      pixel.s =1;
    } else if (pixel.s < 0) {
      pixel.s = 0;
  }
  }
}
}

void Image::grayscale(){
  for (unsigned x = 0; x < width(); x++) {
  for (unsigned y = 0; y < height(); y++) {
    HSLAPixel & pixel = getPixel(x, y);
    pixel.s = 0;
    if (pixel.s > 1) {
      pixel.s =1;
    } else if (pixel.s < 0) {
      pixel.s = 0;
  }
  }
}
}

void Image::rotateColor(double degrees) {
  for (unsigned x = 0; x < width(); x++) {
  for (unsigned y = 0; y < height(); y++) {
    HSLAPixel & pixel = getPixel(x, y);
    if (degrees < 0) {
      degrees += 360;
    }
    pixel.h += degrees;
    if (pixel.h >= 360) {
      pixel.h -= 360;
    }
  }
}
}

void Image::illinify(){
  for (unsigned x = 0; x < width(); x++) {
  for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x,y);
      if ( pixel.h > 113.5 && pixel.h < 293.5 ) {
        pixel.h = 216;
      } else {
        pixel.h = 11;
      }
    }
  }
}

void Image::scale(double factor){
  int newWidth = floor(width() * factor);
  int newHeight = floor(height() * factor);
  PNG * copy = new PNG(width(), height());
  for (unsigned x = 0; x < width(); x++){
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & oldPixel = getPixel(x,y);
      HSLAPixel & newPixel = copy->getPixel(x, y);
      newPixel = oldPixel;
    }
  }
  resize(newWidth,newHeight);
  for (int x = 0; x < newWidth; x++) {
    for (int y = 0; y < newHeight; y++){
      HSLAPixel & copyPixel = copy->getPixel( floor(x/factor),floor(y/factor));
      HSLAPixel & resizedPixel = getPixel(x, y);
      resizedPixel = copyPixel;
    }
  }
}

void Image::scale(unsigned w, unsigned h) {
  double factorW = w / width();
  double factorH = h / height();
  if (factorW <= factorH) {
    scale(factorW);
  } else {
    scale(factorH);
  }
}
