/**
 * int Elligence - 2021COMP315ProjectGroupA
 * 
 * Team members:    Sumeith Ishwanthlal (219006284)
 *                  Sandhya Singh       (219010492)
 *                  Tashvir Singh       (219044683)
 *                  Siphiwe Maphalala   (217034316)          
 */

 /**
  * board.h
  * 
  * This file has been modified from the guided part of the project.
  * 
  * The changes occurred:   class board         //board class declaration
  * 
  * Please Note: There are comments where the changes have been made.
  * 
  */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   board.h
 * Author: MSCS
 *
 * Created on 12 March 2020, 8:55 AM
 */

#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include <map>
#include <sstream>

using namespace std;

class board {
    vector<cell*> rows;
    map<string, cell*> cells;
    int woc; //white marbles off the board count.
    int boc; //black marbles off the board count.
    
    //added the previousMarble attribute
    char previousMarble; //keeps track of which player (White or Black) played last
    
public:
    /*
     * Since previousMarble attribute has been added 
     * the following member functions has been updated in board.cpp: 
     *          board()             //The board constructor
     *          board(const board&) //The copy constructor  
     */
    board(); //create 61 cells on the heap, and connect them.
    board(const board&); //copy constructor
    ~board(); //recycle 61 cells.
    operator std::string() const; //cast this object into a string.
    string traverseHorizontal() const;
    string traverseDiagonal() const;
    
    //added the parameter string& invalidMoveMessage to the validateMove() and the executeMove() functions
    //Also validateMove is no longer a constant member function
    bool validateMove(const string& l, const int& n, const int& fd, const int& md, int& mtype, bool& scoreMove, string& invalidMoveMessage);
    bool executeMove(const string& l, const int& n, const int& fd, const int& md, string& invalidMoveMessage);

    /*
     * Added validateWinner() function as a member function of the board class
     * This function will provide a win condition for the game.
     * Also note that this is a read-only member function (constant).
     * 
     * This function will return an appropriate winning message if a player has won the game.
     * This function will also return true if a player has won the game or false otherwise.
     */
    bool validateWinner(string& winnermessage) const;
};



#endif /* BOARD_H */

