/**
 * int Elligence - 2021COMP315ProjectGroupA
 * 
 * Team members:    Sumeith Ishwanthlal (219006284)
 *                  Sandhya Singh       (219010492)
 *                  Tashvir Singh       (219044683)
 *                  Siphiwe Maphalala   (217034316)          
 */

 /**
  * cell.cpp
  * 
  * This file has remained mostly unchanged from the guided part of the project.
  * 
  * The changes occurred:    cell::cell()   //the cell constructor
  * 
  * Please Note: There are comments where the changes have been made.
  * 
  */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "cell.h"
#include <iostream>
int getAdjacentIndex(const int& i){
    if(i<3)
        return i+3;
    else
        return i-3;
}
char cell::getMarble()const{
    return marble;
}
void cell::setMarble(const char& m){
    if(m=='O' || m=='@' || m=='+'){
        marble=m;
    }
}

cell* cell::getAdjacent(const int& i)const{
    return adjacent.at(i);
}
void cell::setAdjacent(cell* a,const int& i){
    if(adjacent.at(i)==nullptr){
        adjacent.at(i)=a;
        a->setAdjacent(this,getAdjacentIndex(i));
    }
}
string cell::getLocation() const{
    return location;
}

bool cell::validateLocation(const string& l){
    bool validPosition = false;
    if(l.size()==2 && l[0]>='A' && l[0]<='I' && l[1]>='1' && l[1]<='9'){
        if (l[0]>='A' && l[0]<='E'){
            if ((5 + l[0]-'A') > (l[1]-'1'))// A5, A4 ...
                validPosition = true;
        }
        else
            if ((l[0]-'F') < (l[1] - '1'))// F2, F3 ... 
                validPosition = true;
    }
    return validPosition;
}
void cell::setLocation(const string& l){    
    if (validateLocation(l))
        location = l;
    else{
        throw "Invalid Location!";
    }    
}

/*
 * The cell constructor has been modified:
 * The increment condition of the for loop has been changed.
 * It now uses a pre-increment instead of a post-increment in the increment condition of the for loop.
 * This change would help to improve efficiency.
 */
cell::cell(){
    //The increment condition has been updated
    for(int i=0;i<6;++i){
        adjacent.push_back(nullptr);
    }
}
