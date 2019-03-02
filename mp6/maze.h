#ifndef MAZE_H
#define MAZE_H
#include <vector>
#include "cs225/PNG.h"
#include "dsets.h"
#include "cs225/HSLAPixel.h"
using namespace std;
using namespace cs225;

class SquareMaze{
public:
  SquareMaze();
  void makeMaze(int width, int height);
  bool canTravel(int x, int y, int dir) const;
  void setWall(int x, int y, int dir, bool exists);
  vector<int> solveMaze();
  vector<int> solveMaze(int entrance);
  // void findExitHelper(int x, int y, vector<int> & path);
  // bool solveHelper(int x, int y, vector<int> & path, int exitX);
  PNG* drawMaze() const;
  PNG* drawMaze(int entrance) const;
  PNG* drawMazeWithSolution();
  PNG* drawMazeWithSolution(int entrance);
  int exitX;
private:
  int width;
  int height;
  vector<bool> rightWall;
  vector<bool> downWall;
  vector<int> lastRow;
};


#endif
