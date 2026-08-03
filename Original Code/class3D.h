#ifndef CLASS3D_H
#define CLASS3D_H

#include <string>
#include <vector>

using namespace std;
class class3D {
  
public:
  /*class3D(string line); */
  void StringToInt3D(string line);
  void Data3D();
  int Counter3D();
  int GetCounter3D();
  void Distance();
  void PrintDistance();
 void Frequency3D();

private:
  string data;
  int xValue;
  int yValue;
  int zValue;
  int smallJ;
  int largeJ;
  double distance;
  int counter=0;
  vector<int> vectX;
  vector<int> vectY;
  vector<int> vectZ;
  vector<vector <int> > vect3D;
  vector<double> Magnitude;
  vector<int> freqCounter;
};

#endif
