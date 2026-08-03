#include "class3D.h"
#include <iostream>
#include <vector>
#include <cmath> 
#include <string>
#include <map>
using namespace std;


void class3D::StringToInt3D(string line){
  data=line;
  int i,k,j;
  string xString,yString,zString;
  for ( i = 0; i < data.size(); i++) {
    if (isdigit(data[i]) == true) {
      xString = xString + data[i];
      if (isdigit(data[i + 1]) == false) {
       xValue= stoi(xString);
        k=i+1;
        break;
      }
    }
  }//end string to INt

  for ( i = k; i < data.size(); i++) {
    if (isdigit(data[i]) == true) {
      yString = yString + data[i];
      if (isdigit(data[i + 1]) == false) {
       yValue= stoi(yString);
        j=i+1;
        break;
      }
    }
  }//end for 

  for ( i = j; i < data.size(); i++) {
    if (isdigit(data[i]) == true) {
      zString = zString + data[i];
      if (isdigit(data[i + 1]) == false) {
       zValue= stoi(zString);
        break;
      }
    }
  }//end for 
  
}// End String to Int 

void class3D::Data3D(){
  vector<int> temp(3);
  temp[0]=xValue;
  temp[1]=yValue;
  temp[2]=zValue;
  vect3D.push_back(temp);
  
  int magnitudeInside= (xValue*xValue)+(yValue*yValue)+(zValue*zValue);
  double magnitudePower=pow(magnitudeInside,.5);  
  Magnitude.push_back(magnitudePower);
}



void class3D::Distance(){
  int i;
  double smallest=2147483647;
  double largest=-2147483647;
  for(i=0;i<counter;i++){
    if(Magnitude.at(i)>largest){
      largest=Magnitude.at(i);
      largeJ=i;
    }
    if(Magnitude.at(i)<smallest){
      smallest=Magnitude.at(i);
      smallJ=i;
    }
  }//end for
  int xDist=pow( (vect3D[largeJ][0]-vect3D[smallJ][0]), 2 );
  int yDist=pow( (vect3D[largeJ][1]-vect3D[smallJ][1]), 2 );
  int zDist=pow( (vect3D[largeJ][2]-vect3D[smallJ][2]), 2 );
   distance= pow((xDist+yDist+zDist),0.5);
}//end Distance()


void class3D::PrintDistance(){
cout<<"The distance between the smallest point ("<< vect3D[smallJ][0]<<" , ";
  cout<<vect3D[smallJ][1]<<" , "<<vect3D[smallJ][2]<<") and the largest point ";
cout<<"("<<vect3D[largeJ][0]<<" , "<<vect3D[largeJ][1]<<" , ";
cout<<vect3D[largeJ][2]<< ")  is "<<distance<<"\n";
}

void class3D::Frequency3D(){

  map<vector<int>, int> threeDFrequency;  // create map, acting as hash - table with format:  {unique 3d point : frequency  }
  for (vector<int> point : vect3D) {
    /*
    threeDFrequency of type map allows random fast access and  insertion.  
    */
    threeDFrequency[point]++;
  }
  int totalCounter{};
  for (auto entry : threeDFrequency) {
    //cout << entry.first[0] << ", " << entry.first[1] << ", " << entry.first[2] << " : " << entry.second << endl;
  

  totalCounter+= entry.second;
}
  cout<<"Total Frequency of 3D points (total number of 3D points): "<<totalCounter<<"\n";
  
}//END Function

int class3D::Counter3D(){
  counter++;
  return counter;
}

int class3D::GetCounter3D(){
  return counter;
}

