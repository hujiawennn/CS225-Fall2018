#include "maze.h"
#include <vector>
#include <cstdlib>
#include <map>
#include <queue>
using namespace std;

SquareMaze::SquareMaze(){

}

void SquareMaze::makeMaze(int w, int h) {
    width = w;
    height = h;
    for (int i = 0; i < width*height; i++) {
        rightWall.push_back(true);
        downWall.push_back(true);
    }
    DisjointSets dsets;
    dsets.addelements(width * height);
    int count = 0;
    while(count < width*height - 1) {
        int Xcord = rand() % width;
        int Ycord = rand() % height;
        bool rightws = rand() % 2;
        if (rightws) {
          if (Xcord < width - 1 && dsets.find(Ycord * width + Xcord)
                                != dsets.find(Ycord * width + Xcord + 1)) {
           rightWall[Ycord * width + Xcord] = false;
           dsets.setunion(Ycord * width + Xcord, Ycord * width + Xcord + 1);
           count++;
         }
        } else {
          if (Ycord < height - 1 && dsets.find(Ycord * width + Xcord)
                              != dsets.find((Ycord + 1) * width + Xcord)) {
            downWall[Ycord * width + Xcord] = false;
            dsets.setunion(Ycord * width + Xcord, (Ycord + 1) * width + Xcord);
            count++;
          }
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (dir == 0) { // +1 to the x coordinate
        return (!rightWall[y * width + x]);
    } else if (dir == 1) { //+1 to the y coordinate
        return (!downWall[y * width + x]);
    } else if (dir == 2) { //-1 to the x coordinate
        if ( x - 1 < 0) { return false; }
        else { return !rightWall[y * width + (x - 1)]; }
    } else if (dir == 3) { // -1 to the y coordinate
        if ( y - 1 < 0) { return false; }
        else { return !downWall[(y-1) * width + x]; }
    } else {
        return false;
    }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if(dir == 0) {
        rightWall[y * width + x] = exists;
    } else if (dir == 1) {
        downWall[ y * width + x] = exists;
    }
}



std::vector<int> SquareMaze::solveMaze() {
    std::vector<bool> checked(width * height);
    for (unsigned i = 0; i < checked.size(); i++) {
        checked[i] = false;
    }
    std::vector<int> lastRow;
    std::map<int, int> steps;  //take acount of path
    std::queue<int> queue;
    queue.push(0);
    while(!queue.empty()) {
        int temp = queue.front(); //name of the cell starting at 0 at the leftTop corner
        checked[temp] = true;
        int x = temp % width;
        int y = temp / width; //row number
        queue.pop();
        if (y == height - 1) {
            lastRow.push_back(temp);
        }
        if (canTravel(x, y, 0) && !checked[temp + 1]) {
            checked[temp + 1] = true;
            queue.push(temp + 1);
            steps.insert(std::pair<int, int>(temp + 1, temp));
        }
        if (canTravel(x, y, 1) && !checked[temp + width]) {
            checked[temp + width] = true;
            queue.push(temp + width);
            steps.insert(std::pair<int, int>(temp + width, temp));
        }
        if (canTravel(x, y, 2) && !checked[temp - 1]) {
            checked[temp - 1] = true;
            queue.push(temp - 1);
            steps.insert(std::pair<int, int>(temp - 1, temp));
        }
        if (canTravel(x, y, 3) && !checked[temp - width]) {
            checked[temp - width] = true;
            queue.push(temp - width);
            steps.insert(std::pair<int, int>(temp - width, temp));
        }
    }
    std::vector<int> dire;
    int last = lastRow[width - 1];
    while (last != 0) {
        int previous = steps[last];
        if (previous + 1 == last) {
          dire.push_back(0);
        }
        if (previous - 1 == last) {
          dire.push_back(2);
        }
        if (previous + width == last) {
          dire.push_back(1);
        }
        if (previous - width == last) {
           dire.push_back(3);
        }
        last = previous;
    }
    reverse(dire.begin(), dire.end());
    return dire;
}

std::vector<int>SquareMaze::solveMaze(int entrance) {
      std::vector<bool> checked(width * height);
      for (unsigned i = 0; i < checked.size(); i++) {
          checked[i] = false;
      }
      std::vector<int> lastRow;
      std::map<int, int> steps;  //take acount of path
      std::queue<int> queue;
      queue.push(entrance);
      while(!queue.empty()) {
          int temp = queue.front(); //name of the cell starting at 0 at the leftTop corner
          checked[temp] = true;
          int x = temp % width;
          int y = temp / width; //row number
          queue.pop();
          if (y == height - 1) {
              lastRow.push_back(temp);
          }
          if (canTravel(x, y, 0) && !checked[temp + 1]) {
              checked[temp + 1] = true;
              queue.push(temp + 1);
              steps.insert(std::pair<int, int>(temp + 1, temp));
          }
          if (canTravel(x, y, 1) && !checked[temp + width]) {
              checked[temp + width] = true;
              queue.push(temp + width);
              steps.insert(std::pair<int, int>(temp + width, temp));
          }
          if (canTravel(x, y, 2) && !checked[temp - 1]) {
              checked[temp - 1] = true;
              queue.push(temp - 1);
              steps.insert(std::pair<int, int>(temp - 1, temp));
          }
          if (canTravel(x, y, 3) && !checked[temp - width]) {
              checked[temp - width] = true;
              queue.push(temp - width);
              steps.insert(std::pair<int, int>(temp - width, temp));
          }
      }
      std::vector<int> dire;
      int last = lastRow[width - 1];
      while (last != 0) {
          int previous = steps[last];
          if (previous + 1 == last) {
            dire.push_back(0);
          }
          if (previous - 1 == last) {
            dire.push_back(2);
          }
          if (previous + width == last) {
            dire.push_back(1);
          }
          if (previous - width == last) {
             dire.push_back(3);
          }
          last = previous;
      }
      reverse(dire.begin(), dire.end());
      return dire;
}

//First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1).
//where height and width were the arguments to makeMaze.
//Blacken the entire topmost row and leftmost column of pixels,
//except the entrance (1,0) through (9,0). For each square in the maze, call its maze coordinates (x,y).
//If the right wall exists, then blacken the pixels with coordinates
//((x+1)*10,y*10+k) for k from 0 to 10. If the bottom wall exists,
//then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.
//DO NO MODIFY THIS!!!
PNG* SquareMaze::drawMaze() const {
     PNG* result = new PNG(width * 10 + 1, height * 10 + 1);
     HSLAPixel & temp = result->getPixel(0,0);
     temp.l = 0;
     for (int column = 10; column < width * 10; column++) {
       HSLAPixel & temp = result->getPixel(column, 0);
       temp.l = 0;
     }
     for (int row = 0; row < height * 10; row ++) {
       HSLAPixel & temp = result->getPixel(0, row);
       temp.l = 0;
     }
     for (int i = 0; i < width * height; i++) {
       int x = i % width;
       int y = i / width;
       if (rightWall[i]) {
         for (int j = 0; j <= 10; j++) {
           HSLAPixel & temp = result->getPixel((x + 1)*10, y * 10 + j);
           temp.l = 0;
         }
       }
       if (downWall[i]) {
         for (int k = 0; k <= 10; k++) {
           HSLAPixel & temp = result->getPixel(x * 10 + k, (y + 1) * 10);
           temp.l = 0;
         }
       }
     }
     return result;
}

PNG* SquareMaze::drawMaze(int entrance) const{
      PNG* result = new PNG(width * 10 + 1, height * 10 + 1);
      for (int column = 0; column < width * 10; column++) {
        HSLAPixel & temp = result->getPixel(column, 0);
        temp.l = 0;
      }
      for (int i = 0; i <= 10; i++) {
        HSLAPixel & temp = result->getPixel(entrance * 10 + i, 0);
        temp.l = 1;
      }
      for (int row = 0; row < height * 10; row ++) {
        HSLAPixel & temp = result->getPixel(0, row);
        temp.l = 0;
      }
      for (int i = 0; i < width * height; i++) {
        int x = i % width;
        int y = i / width;
        if (rightWall[i]) {
          for (int j = 0; j <= 10; j++) {
            HSLAPixel & temp = result->getPixel((x + 1)*10, y * 10 + j);
            temp.l = 0;
          }
        }
        if (downWall[i]) {
          for (int k = 0; k <= 10; k++) {
            HSLAPixel & temp = result->getPixel(x * 10 + k, (y + 1) * 10);
            temp.l = 0;
          }
        }
      }
      return result;
}

// PNG* SquareMaze::drawCreativeMaze() const{
//   PNG* result = new PNG (width * 10 + 1, height * 10 + 1);
//
// }

//DO NOT MODIFY THIS!!
PNG* SquareMaze::drawMazeWithSolution() {
  PNG* result = drawMaze();
  vector<int> path = solveMaze();
  int x = 5;
  int y = 5;
  for (size_t i = 0; i < path.size(); i++) {
    if (path[i] == 0) {
      for (int j = 0; j <= 10; j++) {
        HSLAPixel & temp = result->getPixel(x + j, y);
        temp.h = 0;
        temp.s = 1;
        temp.l = 0.5;
        temp.a = 1;
      }
      x += 10;
    }
    if (path[i] == 1) {
      for (int j = 0; j <= 10; j++) {
        HSLAPixel & temp = result->getPixel(x, y + j);
        temp.h = 0;
        temp.s = 1;
        temp.l = 0.5;
        temp.a = 1;
      }
      y += 10;
    }
    if (path[i] == 2) {
      for (int j = 0; j <= 10; j++) {
        HSLAPixel & temp = result->getPixel(x - j, y);
        temp.h = 0;
        temp.s = 1;
        temp.l = 0.5;
        temp.a = 1;
      }
      x -= 10;
    }
    if (path[i] == 3) {
      for (int j = 0; j <= 10; j++) {
        HSLAPixel & temp = result->getPixel(x, y - j);
        temp.h = 0;
        temp.s = 1;
        temp.l = 0.5;
        temp.a = 1;
      }
      y -= 10;
    }
  }
  exitX = x / 10;
  for (int i = 1; i <= 9; i++) {
    HSLAPixel & temp = result->getPixel(exitX * 10 + i, height * 10);
    temp.l = 1;
  }
  return result;
}

PNG* SquareMaze::drawMazeWithSolution(int entrance){
    PNG* result = drawMaze(entrance);
    vector<int> path = solveMaze(entrance);
    int x = 5 + entrance * 10;
    int y = 5;
    for (int i = 0; i < 5; i++) {
      HSLAPixel & temp = result->getPixel(x, i);
      temp.h = 205;
      temp.s = 1;
      temp.l = 0.5;
      temp.a = 1;
    }
    for (size_t i = 0; i < path.size(); i++) {
        if (path[i] == 0) {
          for (int j = 0; j <= 10; j++) {
            HSLAPixel & temp = result->getPixel(x + j, y);
            temp.h = 205;
            temp.s = 1;
            temp.l = 0.5;
            temp.a = 1;
          }
          x += 10;
        }
        if (path[i] == 1) {
          for (int j = 0; j <= 10; j++) {
            HSLAPixel & temp = result->getPixel(x, y + j);
            temp.h = 205;
            temp.s = 1;
            temp.l = 0.5;
            temp.a = 1;
          }
          y += 10;
        }
        if (path[i] == 2) {
          for (int j = 0; j <= 10; j++) {
            HSLAPixel & temp = result->getPixel(x - j, y);
            temp.h = 205;
            temp.s = 1;
            temp.l = 0.5;
            temp.a = 1;
          }
          x -= 10;
        }
        if (path[i] == 3) {
          for (int j = 0; j <= 10; j++) {
            HSLAPixel & temp = result->getPixel(x, y - j);
            temp.h = 205;
            temp.s = 1;
            temp.l = 0.5;
            temp.a = 1;
          }
          y -= 10;
        }
        if (i == path.size() - 1) {
          for (int j = 0; j <= 5; j++) {
            HSLAPixel & temp = result->getPixel(x, y + j);
            temp.h = 205;
            temp.s = 1;
            temp.l = 0.5;
            temp.a = 1;
          }
        }
    }
    exitX = x / 10;
    for (int i = 1; i <= 9; i++) {
      HSLAPixel & temp = result->getPixel(exitX * 10 + i, height * 10);
      temp.l = 1;
    }
    return result;
}
