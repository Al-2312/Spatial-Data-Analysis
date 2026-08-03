#ifndef CLASS2D_H
#define CLASS2D_H

#include <string>
#include <vector>

using namespace std;
class class2D {
  
public:
  void StringToInt2D(string line); //function to read line and get inputs
  void Data2D(); //
  int Counter2D();
  int GetCounter2D();
  void Distance();
  void PrintDistance();
  void Frequency2D();

private:
  string data;
  int xValue;
  int yValue;
  int smallJ;
  int largeJ;
  double distance;
  int counter=0;
  vector<int> vectX;
  vector<int> vectY;
  vector<vector <int> > vect2d;
  vector<double> Magnitude;
  vector<int> freqCounter;
};

#endif
