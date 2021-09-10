/**
 * int Elligence - 2021COMP315ProjectGroupA
 * 
 * Team members:    Sumeith Ishwanthlal (219006284)
 *                  Sandhya Singh       (219010492)
 *                  Tashvir Singh       (219044683)
 *                  Siphiwe Maphalala   (217034316)          
 */

 /**
  * cell.h
  * 
  * This file has remained unchanged from the guided part of the project.
  * 
  */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cell.h
 * Author: MSCS
 *
 * Created on 12 March 2020, 8:39 AM
 */

#ifndef CELL_H
#define CELL_H

#include <string>
#include <vector>

using namespace std;
int getAdjacentIndex(const int& i);
class cell{    
    char marble;
    vector<cell*> adjacent;//six directions: north-east clockwise to north-west
    string location; 
    
public:
    char getMarble() const;
    void setMarble(const char&);//set marble to either O, @ or +.
    cell* getAdjacent(const int&) const;
    void setAdjacent(cell*,const int&);//only set each neighbour once.
    string getLocation() const;
    static bool validateLocation(const string& l);
    void setLocation(const string& l);
    cell();//set all 6 neighbours to null.
};

#endif /* CELL_H */

