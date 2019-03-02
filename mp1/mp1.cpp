#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void rotate(std::string inputFile, std::string outputFile) {
  PNG oldPic;
  oldPic.readFromFile(inputFile);
  unsigned int w = oldPic.width();
  unsigned int h = oldPic.height();
  PNG newPic = PNG(w, h);

  for (unsigned int i = 0; i < w; i++) {
    for (unsigned int j = 0; j < h; j++) {
      HSLAPixel &a = oldPic.getPixel(i,j);
      HSLAPixel &newLocation = newPic.getPixel(w - 1 -i,h - 1 - j);
      newLocation = a;
    }
  }
  newPic.writeToFile(outputFile);
}


//create microsoft logo;
PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  unsigned int block = width / 80;
  // creating a block with red;
  for (unsigned int i = block * 30; i < block * 39; i ++) {
    for (unsigned int j = block * 30; j < block * 39; j ++) {
      HSLAPixel &r = png.getPixel(i,j);
      r.h = 8;
      r.s = 0.74;
      r.l = 0.54;
      r.a = 1;
    }
  }
  // creating a block with green;
  for (unsigned int i = block * 40; i < block * 49; i++) {
    for (unsigned int j = block * 30; j < block * 39; j++) {
      HSLAPixel &g = png.getPixel(i,j);
      g.h = 85;
      g.s = 0.60;
      g.l = 0.45;
      g.a = 1;
    }
  }
  // creating a block with blue;
  for (unsigned int i = block * 30; i < block * 39; i++) {
    for (unsigned int j = block * 40; j < block * 49; j++) {
      HSLAPixel &b = png.getPixel(i,j);
      b.h = 206;
      b.s = 0.89;
      b.l = 0.60;
      b.a = 1;
    }
  }
  // creating a block with yellow;
  for (unsigned int i = block * 40; i < block * 49; i++) {
    for (unsigned int j = block * 40; j < block * 49; j++) {
      HSLAPixel &y = png.getPixel(i,j);
      y.h = 40;
      y.s = 1;
      y.l = 0.6;
      y.a = 1;
    }
  }
  for (unsigned int i = 0; i < width; i++) {
    for (unsigned int j = 0; j < height; j++) {
      HSLAPixel &w = png.getPixel(i,j);
      if (w.l == 1) {
        w.h = 202;
        w.s = 0.73;
        w.l = 0.75;
        w.a = 1;
      }
    }
  }
  for (unsigned int i = block * 39; i < block * 40; i++) {
    for (unsigned int j = block * 30; j < block * 49; j++) {
      HSLAPixel &a = png.getPixel(i,j);
      a.l = 1;
    }
  }
  for (unsigned int i = block * 30; i < block * 49; i++) {
    for (unsigned int j = block * 39; j < block * 40; j++){
      HSLAPixel & b = png.getPixel(i,j);
      b.l = 1;
    }
  }
  for (unsigned int i = block * 25; i < block * 30; i++) {
    for (unsigned int j = block * 25; j < block * 54; j++) {
      HSLAPixel & b = png.getPixel(i,j);
      b.l = 1;
    }
  }
  for (unsigned int i = block * 25; i < block * 54; i++) {
    for (unsigned int j = block * 25; j < block * 30; j++) {
      HSLAPixel & b = png.getPixel(i,j);
      b.l = 1;
    }
  }
  for (unsigned int i = block * 49; i < block * 54; i++) {
    for (unsigned int j = block * 25; j < block * 54; j++) {
      HSLAPixel & b = png.getPixel(i,j);
      b.l = 1;
    }
  }
  for (unsigned int i = block * 25; i < block * 54; i++) {
    for (unsigned int j = block * 49; j < block * 54; j++) {
      HSLAPixel & b = png.getPixel(i,j);
      b.l = 1;
    }
  }
  for (unsigned int i = 0; i < width; i+=4) {
    for (unsigned int j = 0; j < height; j+=4) {
        HSLAPixel & m = png.getPixel(i,j);
        if (m.h == 202) {
          m.l = 1;
        }
    }
  }
  return png;
}
