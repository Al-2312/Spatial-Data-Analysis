#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "class2D.h"
#include "class3D.h"
// Allan Yunayev
using namespace std;

bool Check3d(string data) {
  bool check;
  if (data.find('Z') != string::npos) {
    check = true;
  } else {
    check = false;
  }
  return check;
}


int main() {
  string line;
  class2D point2D;
  class3D point3D;
  ifstream myfile("../FinalProject.txt");
  if (myfile.is_open()) {
    while (getline(myfile, line)) {

      if (Check3d(line) == true) {
        point3D.StringToInt3D(line);
        point3D.Data3D();
        point3D.Counter3D();
      } // 3d if
        
      else {
        point2D.StringToInt2D(line);
        point2D.Data2D();
        point2D.Counter2D();
      }
    } // end while
    myfile.close();
  }

 
  cout<<"Please wait one minute.\n";
  point2D.Frequency2D();
  cout << "\n";
  cout <<"2D Points:\n\n"; 
  cout << "There are " <<  point2D.GetCounter2D() << " 2D points\n\n";
  point2D.Distance();
  point2D.PrintDistance();


  cout << "\n";
  cout <<"3D Points:\n\n"; 
  cout << "There are " << point3D.GetCounter3D() << " 3D points\n";
  point3D.Distance();
  point3D.PrintDistance();
 
  
  cout<<"3D Frequency takes 20 minutes to load but 194218 points have at least 2 frequencys\n";
  // 194218 HAVE AT LEAST 2 FREQ
  cout << "\n";
  cout <<"3D Points:\n\n"; 
  point3D.Frequency3D();


  return 0; 
}
