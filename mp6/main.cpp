#include <iostream>
#include "dsets.h"
#include "maze.h"
using namespace std;
using namespace cs225;
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

class Image : public cs225::PNG {
public:
  void lighten();
  void lighten(double amount);
  void darken();
  void darken(double amount);
  void saturate();
  void saturate(double amount);
  void desaturate();
  void desaturate(double amount);
  void grayscale();
  void rotateColor(double degrees);
  void illinify();
  void scale(double factor);
  void scale(unsigned w, unsigned h);
};

class StickerSheet{
private:
  unsigned int maxNumOfLayer;
  Image baseImage;
  void _copy(const StickerSheet &);
  void _destroy();

public:
  StickerSheet(const Image &picture, unsigned max);
  ~StickerSheet();
  StickerSheet(const StickerSheet &);
  const StickerSheet & operator=(const StickerSheet & other);
  void changeMaxStickers(unsigned max);
  unsigned int getMaxNumbOfLayer() const;
  int addSticker(Image &, unsigned, unsigned);
  bool translate(unsigned,unsigned,unsigned);
  void removeSticker(unsigned);
  Image* getSticker(unsigned) const;
  Image getBaseImage() const;
  Image render() const;
  std::vector<Image*> vec;
  std::vector<int> vecX;
  std::vector<int> vecY;
  Image* layer;
  unsigned int layerCount;
};

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

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
  maxNumOfLayer = max;
  baseImage = picture;
  layerCount = 0;
  // for (int i = 0; i < maxNumOfLayer; i++) {
  //   layer = new Image();
  //   vec.push_back(layer);
  vec.resize(maxNumOfLayer);
  vecX.resize(maxNumOfLayer);
  vecY.resize(maxNumOfLayer);
  }

//free space
StickerSheet::~StickerSheet() {

}

//copy helper
void StickerSheet::_copy(const StickerSheet & other) {
  maxNumOfLayer = other.getMaxNumbOfLayer();
  vec.resize(maxNumOfLayer);
  vecX.resize(maxNumOfLayer);
  vecY.resize(maxNumOfLayer);
  baseImage = other.getBaseImage();
  for (unsigned int i = 0; i < other.layerCount; i++) {
    vec[i] = other.vec[i];
    vecX[i] = other.vecX[i];
    vecY[i] = other.vecY[i];
  }
  layerCount = other.layerCount;
}

//copy
StickerSheet::StickerSheet(const StickerSheet &other) {
  _copy(other);
}


//assignment operator
const StickerSheet & StickerSheet::operator=(const StickerSheet & other){
  _copy(other);
  return *this;
}


//modify the max number of stickers
void StickerSheet::changeMaxStickers(unsigned max){
  // if (max >= maxNumOfLayer) {
  //   int numToAdd = max - maxNumOfLayer;
  //   layer = NULL;
  //   for (int i = 0; i < numToAdd; i++) {
  //     layer = new Image();
  //     vec.push_back(layer);
  //     vecX.push_back(0);
  //     vecY.push_back(0);
  //     layerCount++;
  //   }
  //   maxNumOfLayer = max;
  // } else {
    vec.resize(max);
    vecY.resize(max);
    vecX.resize(max);
    maxNumOfLayer = max;
    if (layerCount > max) {
      layerCount = max;
    }
    // }
  // }
}


//add a sticker to the sheet, so that the top-left of the sticker (x,y) on the
//sheet;
int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
    if (layerCount + 1 > maxNumOfLayer) {
      return -1;
    } else {
      vec[layerCount] = & sticker;
      vecX[layerCount] = x;
      vecY[layerCount] = y;
      layerCount++;
    }
    return 0;
}

//change coordinate of the image
//if the layer is invalid or does not contain a sticker -> false
bool StickerSheet::translate(unsigned index,unsigned x,unsigned y) {
  if (index >= maxNumOfLayer || vec[index] == NULL) {
    return false;
  } else {
    vecX[index] = x;
    vecY[index] = y;
  }
  return true;
}

//remove sticker
void StickerSheet::removeSticker(unsigned index) {
  vec[index] = NULL;
}

//returns a pointer to the sticker, not a copy of it
//if index is invalid, return NULL;
Image* StickerSheet::getSticker(unsigned index) const {
  if (index >= maxNumOfLayer || vec[index] == NULL){
    return NULL;
  } else {
    return vec[index];
  }
}



Image StickerSheet::render() const{
  Image finalSheet = getBaseImage();
  for(unsigned int a = 0; a < layerCount; a++) {
    if (vec[a] == NULL) {
      continue;
    } else {
      Image mySticker = *vec[a];
    unsigned int xStart = vecX[a];
    unsigned int yStart = vecY[a];
    unsigned int xEnd = xStart + mySticker.width();
    unsigned int yEnd = yStart + mySticker.height();
    unsigned int imageWidth = finalSheet.width();
    unsigned int imageHeight = finalSheet.height();
    if (xEnd >= imageWidth) {
      finalSheet.resize(xEnd + 1, imageWidth);
    } else if (yEnd >= imageHeight) {
      finalSheet.resize(imageWidth, yEnd + 1);
    }
    for (unsigned int i = 0; i < mySticker.width(); i++) {
      for (unsigned int j = 0; j < mySticker.height(); j++) {
        cs225::HSLAPixel & pixel = finalSheet.getPixel(xStart+i, yStart+j);
        cs225::HSLAPixel & stiPixel = mySticker.getPixel(i,j);
        if (stiPixel.a == 0) {
          continue;
        }
        pixel.h = stiPixel.h;
        pixel.s = stiPixel.s;
        pixel.l = stiPixel.l;
        pixel.a = stiPixel.a;
      }
    }
  }
}
  return finalSheet;
}



unsigned int StickerSheet::getMaxNumbOfLayer() const{
  return maxNumOfLayer;
}

Image StickerSheet::getBaseImage() const{
    return baseImage;
}

int main()
{
    // Write your own main here
    Image base, sticker1, sticker2;
    PNG* blankBase = new PNG (400, 400);
    blankBase->writeToFile("base" + string(".png"));
    base.readFromFile("base.png");
    StickerSheet sheet = StickerSheet(base, 5);
    SquareMaze maze1;
    maze1.makeMaze(3, 6);
    PNG* vertical = maze1.drawMazeWithSolution(0);
    vertical->writeToFile("vertical" + string (".png"));
    sticker1.readFromFile("vertical.png");
    int entrance2 = maze1.exitX;
    SquareMaze maze2;
    maze2.makeMaze(6, 2);
    PNG* horizontal = maze2.drawMazeWithSolution(entrance2);
    horizontal->writeToFile("horizontal" + string (".png"));
    sticker2.readFromFile("horizontal.png");
    sheet.addSticker(sticker1, 150, 200);
    sheet.addSticker(sticker2, 150, 260);
    Image result = sheet.render();
    result.writeToFile("creative.png");
    return 0;
    //generate creative.png
}
