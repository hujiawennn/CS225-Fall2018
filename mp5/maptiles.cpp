/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

LUVAPixel converToPixel(Point<3> point) {
   return LUVAPixel(point[0], point[1], point[2]);
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    map <Point<3>, TileImage*> map;
    MosaicCanvas* newMosaic = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> points;
    for (unsigned i = 0; i < theTiles.size(); i++) {
      LUVAPixel tempPixel = theTiles[i].getAverageColor();
      Point<3> tempPoint = convertToXYZ(tempPixel);
      points.push_back(tempPoint);
      map[tempPoint] = &theTiles[i];
    }
    KDTree<3> treeTiles(points);
    for (int i = 0; i < theSource.getRows(); i++) {
      for (int j = 0; j < theSource.getColumns(); j++) {
        LUVAPixel tempPixel = theSource.getRegionColor(i, j);
        Point<3> tempPoint = convertToXYZ(tempPixel);
        Point<3> nearestNeigh = treeTiles.findNearestNeighbor(tempPoint);
        TileImage*& tileNeeded = map[nearestNeigh];
        newMosaic->setTile(i, j, tileNeeded);
      }
    }
    return newMosaic;
}
