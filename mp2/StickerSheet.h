/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include <vector>
#include "Image.h"

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
