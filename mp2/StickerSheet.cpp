#include "StickerSheet.h"
#include <vector>
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

//Initialize the sticker sheet with a base picture and the ability to hold a max
//number of stickers with indices 0 through max - 1;
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
