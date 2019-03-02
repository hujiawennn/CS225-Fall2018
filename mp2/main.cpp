#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"

int main() {
  Image base,sticker1,sticker2,sticker3,sticker4;
  base.readFromFile("base.png");
  sticker1.readFromFile("1.png");
  sticker2.readFromFile("2.png");
  sticker3.readFromFile("3.png");
  sticker4.readFromFile("4.png");
  StickerSheet sheet = StickerSheet(base,5);
  sheet.addSticker(sticker1, 0, 0);
  sheet.addSticker(sticker2, 450, 0);
  sheet.addSticker(sticker3, 890, 0);
  sheet.addSticker(sticker4, 450, 620);
  Image result = sheet.render();
  result.writeToFile("myImage.png");

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //



  return 0;
}
