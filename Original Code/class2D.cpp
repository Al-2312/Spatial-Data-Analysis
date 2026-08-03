#include "class2D.h"
#include <iostream>
#include <vector>
#include <cmath> 
#include <string>
using namespace std;

void class2D::StringToInt2D(string line)
{
  
  data=line;
  int i,k;
  string xString,yString;
  for ( i = 0; i < data.size(); i++) 
  {
    if (isdigit(data[i]) == true) 
    {
      xString = xString + data[i];
      if (isdigit(data[i + 1]) == false) 
      {
       xValue= stoi(xString); //convert to int
        k=i+1; //start next over here for y value
        break;
      }
    }
  }//end string to INt

  //convert y string to int
  for ( i = k; i < data.size(); i++) 
  {
    if (isdigit(data[i]) == true) 
    {  
      yString = yString + data[i];
      if (isdigit(data[i + 1]) == false) 
      {
       yValue= stoi(yString);
        break;
      }
    }
  }//end for 
  
}// End String to Int 

void class2D::Data2D(){
  vector<int> temp(2); //create vector size two
  temp[0]=xValue; //input x value vector
  temp[1]=yValue; //inpuyt y value in vector
  vect2d.push_back(temp); //push the pair to the larger 2d vector
  
  int magnitudeInside= (xValue*xValue)+(yValue*yValue);// Making magitude vector for farthest distance  doing it here to make it faster
  double magnitudePower=pow(magnitudeInside,.5);  
  Magnitude.push_back(magnitudePower);
}



void class2D::Distance(){
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
  int xDist=pow( (vect2d[largeJ][0]-vect2d[smallJ][0]), 2 );
  int yDist=pow( (vect2d[largeJ][1]-vect2d[smallJ][1]), 2 );
   distance= pow((xDist+yDist),0.5);
}//end Distance()


void class2D::PrintDistance()
{
cout<<"The distance between the smallest point ("<< vect2d[smallJ][0]<<" , ";
  cout<<vect2d[smallJ][1]<<") and the largest point ";
cout<<"("<<vect2d[largeJ][0]<<" , "<<vect2d[largeJ][1]<<") ";
cout<< " is "<<distance<<"\n";
}


void class2D::Frequency2D(){
  int i,j;
  int totalCounter =0;
    vector<int> freqCounter(vect2d.size(),0);
    for( i = 0; i<vect2d.size(); ++i){
        if(freqCounter[i]== -1){
          continue;
        }

        for( j=i+1;j<vect2d.size();j++){
          if(vect2d[i]==vect2d[j]){
            freqCounter[i]++;
            freqCounter[j]= -1;
          }
        }
    }
    cout<<" The Frequences with at least 2: \n";
    for( i =0;i< vect2d.size();i++){
      if( freqCounter[i]!= -1 && freqCounter[i]+1 >= 2){
        totalCounter=totalCounter+freqCounter[i] + 1;
       //cout<< "(" << vect2d[i][0] << ", " << vect2d[i][1] << "): " << freqCounter[i] + 1 << "\n";
      }
    }
    cout<<"Total at least 2 Frequency: "<<totalCounter<<"\n";
  
}//END Function



int class2D::Counter2D(){
  counter++;
  return counter;
}

int class2D::GetCounter2D(){
  return counter;
}


