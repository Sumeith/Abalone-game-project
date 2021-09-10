/**
 * int Elligence - 2021COMP315ProjectGroupA
 * 
 * Team members:    Sumeith Ishwanthlal (219006284)
 *                  Sandhya Singh       (219010492)
 *                  Tashvir Singh       (219044683)
 *                  Siphiwe Maphalala   (217034316)          
 */

 /**
  * board.cpp
  * 
  * This file has been modified from the guided part of the project.
  * 
  * The changes occurred:   setMarbles()                        //function   
  *                         connectHorizontal                   //function
  *                         connectDiagonal                     //function
  *                         mapCells                            //function
  *                         board::board()                      //board constructor
  *                         board::board(const board& copy)     //board copy constructor
  *                         board::~board()                     //board destructor
  *                         board::operator std::string()       //board string operator
  *                         board::validateMove                 //member function of board class
  *                         board::executeMove                  //member function of board class
  * 
  * 
  * This member function has been added: board::validateWinner
  *                             
  * Please Note: There are comments where the changes have been made.
  * 
  */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "board.h"
#include <iomanip>
#include <iostream>

string traverse(const cell* start, const int& pd, const int& sd, const int& td) {
    string ts;
    const cell* linep = start;
    while (linep != nullptr/*linep->getAdjacent(pd)!=nullptr || linep->getAdjacent(sd)!=nullptr*/) {
        const cell* cellp = linep;
        while (cellp != nullptr) {
            ts += (cellp->getLocation() + ' ');
            cellp = cellp->getAdjacent(td);
        }
        if (linep->getAdjacent(pd) == nullptr)
            linep = linep->getAdjacent(sd);
        else
            linep = linep->getAdjacent(pd);
    }
    /*const cell* cellp = linep;
    while(cellp!=nullptr){
        ts+=(cellp->getLocation()+' ');
        cellp=cellp->getAdjacent(td);
    }*/
    return ts;
}

/*
 * The setMarbles function has been modified:
 * The increment condition of the for loop has been changed.
 * It now uses a pre-increment instead of a post-increment in the increment condition of the for loop.
 * This change would help to improve efficiency.
 */
void setMarbles(cell* row, const int& z, const char& m) {
    //The increment condition has been updated
    for (int i = 0; i < z; ++i) {
        row[i].setMarble(m);
    }
    if (z == 7) {
        char pos[4] = {0, 1, 5, 6};
        //The increment condition has been updated
        for (int i = 0; i < 4; ++i) {
            row[pos[i]].setMarble('+');
        }
    }
}

/*
 * The connectHorizontal function has been modified:
 * The increment condition of the for loop has been changed.
 * It now uses a pre-increment instead of a post-increment in the increment condition of the for loop.
 * This change would help to improve efficiency.
 */
void connectHorizontal(cell* row, const int& rz) {
    //The increment condition has been updated
    for (int i = 0; i < rz - 1; ++i) {
        row[i].setAdjacent(row + i + 1, 1);
    }
    //row[0].setAdjacent(row+1,1);
    //row[rz-2].setAdjacent(row+rz-1,1);    
}

/*
 * The connectDiagonal function has been modified:
 * The increment condition of the for loop has been changed.
 * It now uses a pre-increment instead of a post-increment in the increment condition of the for loop.
 * This change would help to improve efficiency.
 */
void connectDiagonal(cell* lrow, cell* srow, const int& f, const int& sz, const bool& top) {
    //The increment condition has been updated
    for (int i = f; i < (f + sz); ++i) {
        if (top) {
            if (f == 0) {//connecting from cell 0 in longer row
                lrow[i].setAdjacent(srow + i, 0);
            } else if (f == 1) {//connecting from cell 1 in longer row
                lrow[i].setAdjacent(srow + i - 1, 5);
            } else return;
        } else {
            if (f == 0) {
                lrow[i].setAdjacent(srow + i, 2);
            } else if (f == 1) {
                lrow[i].setAdjacent(srow + i - 1, 3);
            } else return;
        }
    }
}

/*
 * The mapCells function has been modified:
 * The increment condition of the for loop has been changed.
 * It now uses a pre-increment instead of a post-increment in the increment condition of the for loop.
 * This change would help to improve efficiency.
 */
void mapCells(cell* row, map<string, cell*>& cm, const char& r, const int& z) {
    int f = 1;
    if (r >= 'A' && r <= 'E') {
        f = 1;
    } else if (r > 'E' && r <= 'I') {
        f = r - 'E' + 1;
    } else return;
    //The increment condition has been updated
    for (int i = 0; i < z; ++i) {
        stringstream ss;
        ss << r;
        ss << (i + f);
        string lc = ss.str();
        row[i].setLocation(lc);
        cm[lc] = row + i;
    }
}

/*
 * The board constructor has been modified:
 * The increment condition of the for loop has been changed.
 * It now uses a pre-increment instead of a post-increment in the increment condition of the for loop.
 * This change would help to improve efficiency.
 * 
 * The variable previousMarble has been initialized in the constructor initialization list
 */
board::board() : woc(0), boc(0), previousMarble(' ') {
    char r = 'I';
    //The increment condition has been updated
    for (int i = 0; i < 9; ++i) {
        if (i < 5) {
            rows.push_back(new cell[5 + i]);
            connectHorizontal(rows[i], 5 + i);
            mapCells(rows[i], cells, r--, 5 + i);
            if (i < 3) {
                setMarbles(rows[i], 5 + i, 'O');
            } else
                setMarbles(rows[i], 5 + i, '+');
        } else {
            rows.push_back(new cell[5 + 8 - i]);
            connectHorizontal(rows[i], 5 + 8 - i);
            mapCells(rows[i], cells, r--, 5 + 8 - i);
            if (i >= 6) {
                setMarbles(rows[i], 5 + 8 - i, '@');
            } else
                setMarbles(rows[i], 5 + 8 - i, '+');
        }
    }
    //The increment condition has been updated
    for (int i = 1; i < 9; ++i) {
        if (i < 5) {
            connectDiagonal(rows[i], rows[i - 1], 0, 5 + i - 1, true);
            connectDiagonal(rows[i], rows[i - 1], 1, 5 + i - 1, true);
        } else {
            connectDiagonal(rows[i - 1], rows[i], 0, 5 + 8 - i, false);
            connectDiagonal(rows[i - 1], rows[i], 1, 5 + 8 - i, false);
        }
    }
}

/*
 * The board copy constructor has been modified:
 * the variable previousMarble is initialized accordingly.
 */
board::board(const board& copy) : board() {//constructor delegation - C++11
    woc = copy.woc;
    boc = copy.boc;
    //previousMarble is initialized accordingly
    previousMarble = copy.previousMarble;
    map<string, cell*>::const_iterator it = copy.cells.begin();
    while (it != copy.cells.end()) {
        (cells[it->first])->setMarble((*(it->second)).getMarble());
        it++;
    }
}

/*
 * The board destructor has been modified:
 * The increment condition of the for loop has been changed.
 * It now uses a pre-increment instead of a post-increment in the increment condition of the for loop.
 * This change would help to improve efficiency.
 */
board::~board() {
    //The increment condition has been updated
    for (int i = 0; i < 9; ++i) {
        delete[] rows[i];
        rows[i] = nullptr;
    }
    cells.clear();
    //cout<<"good bye!";
}

/*
 * The string operator has been modified:
 * The increment condition of the for loop has been changed.
 * It now uses a pre-increment instead of a post-increment in the increment condition of the for loop.
 * This change would help to improve efficiency.
 */
board::operator std::string() const {
    stringstream ss;
    char r = 'I';
    int d = 9;
    //The increment condition has been updated
    for (int i = 0; i < 9; ++i) {
        if (i < 5) {
            ss << setw(5 - i) << r << " ";
            //The increment condition has been updated
            for (int k = 0; k < 5 + i; ++k) {
                ss << rows[i][k].getMarble() << " ";
            }
            ss << endl;
            r--;
        } else {
            ss << setw(i - 3) << r << " ";
            //The increment condition has been updated
            for (int k = 0; k < 5 + 8 - i; ++k) {
                ss << rows[i][k].getMarble() << " ";
            }
            ss << d << endl;
            r--;
            d--;
        }
    }
    d = 1;
    ss << setw(8) << d++ << " ";
    //The increment condition has been updated
    for (; d < 6; ++d)
        ss << d << " ";
    ss << endl;
    //The increment condition has been updated
    for (int i = 0; i < woc; ++i)
        ss << 'O' << " ";
    ss << endl;
    //The increment condition has been updated
    for (int i = 0; i < boc; ++i)
        ss << '@' << " ";
    ss << endl;
    return ss.str();
}

string board::traverseDiagonal() const {
    //backward diagonal - nw to se
    /*
    map<string,cell*>::const_iterator it = cells.find(string("A1"));
    cell* start = it->second;
    return traverse(start,1,0,5); 
     */
    //forward diagonal - sw to ne
    /**/
    map<string, cell*>::const_iterator it = cells.find(string("E1"));
    cell* start = it->second;
    return traverse(start, 0, 1, 2);
    /**/
}

string board::traverseHorizontal() const {
    map<string, cell*>::const_iterator it = cells.find(string("A1"));
    cell* start = it->second;
    return traverse(start, 5, 0, 1);
}

/*
 * The validateMove member function of the board class has been modified:
 * 
 * The function is no longer a constant function
 * 
 * The additional parameter invalidMoveMessage is passed by reference to the function.
 * 
 * The increment condition of the for loop has been changed.
 * It now uses a pre-increment instead of a post-increment in the increment condition of the for loop.
 * This change would help to improve efficiency.
 */
bool board::validateMove(const string& l, const int& n, const int& fd, const int& md, int& mtype, bool& scoreMove, string& invalidMoveMessage){
    /*
     * if statements are added to validate the input from the moves.txt file.
     */
    //if statement to manipulate the invalidMoveMessage variable.
    if (n < 1 || n > 3) {
        invalidMoveMessage = " - Invalid move: You can only move up to 3 marbles";
        return false;
    }
    //if statement to manipulate the invalidMoveMessage variable.
    if (fd < 0 || fd > 5) {
        invalidMoveMessage = " - Invalid move: You have entered incorrect follow direction. A direction can take the values [0,5]";
        return false;
    }
    //if statement to manipulate the invalidMoveMessage variable.
    if (md < 0 || md > 5) {
        invalidMoveMessage = " - Invalid move: You have entered incorrect move direction. A direction can take the values [0,5]";
        return false;
    }

    //updated if statement to manipulate the invalidMoveMessage variable.
    if (!cell::validateLocation(l))//confirm existence of location
    {
        invalidMoveMessage = " - Invalid move: You have entered an invalid location.";
        return false;
    } else {
        cell* cp = cells.at(l); //initialize to leading cell
        const char marble = cp->getMarble();
        //updated if statement to manipulate the invalidMoveMessage variable.
        if (marble == '+')//trying to move a space
        {
            invalidMoveMessage = " - Invalid move: There is no marble available to move.";
            return false;
        }
        //The increment condition has been updated
        for (int i = 1; i < n; ++i) {
            cp = cp->getAdjacent(fd);
            //updated if statement to manipulate the invalidMoveMessage variable.
            if (cp == nullptr || marble != cp->getMarble())//confirm availability and type of claimed resources
            {
                invalidMoveMessage = " - Invalid move: The number of marbles specified is not available. Also note that you can only move marbles of the same colour.";
                return false;
            }
        }
        if (fd == getAdjacentIndex(md)) {//in-line move
            cp = cells.at(l); //initialize to leading cell
            mtype = 0; //how many opponent marbles are in front of the leading marble i.e in the move direction
            //The increment condition has been updated
            for (int i = 0; i < n; ++i) {
                cp = cp->getAdjacent(md);
                if (cp != nullptr) {//confirm availability of required resources
                    //updated if statement to manipulate the invalidMoveMessage variable.
                    if (marble == cp->getMarble())//met own marble instead of space
                    {
                        invalidMoveMessage = " - Invalid move: You cannot push your own marble.";
                        return false;
                    }
                    if ('+' != cp->getMarble())//if it belongs to opponent
                        mtype++; //count opponent marbles
                    else
                        break;
                } else {
                    if (mtype > 0)//opponent's marble will be pushed off the board
                        scoreMove = true;
                        //updated else clause to manipulate the invalidMoveMessage variable.
                    else//if trying to push your own marble off the board
                    {
                        invalidMoveMessage = " - Invalid move: You cannot push your own marble off the board.";
                        return false;
                    }
                    break;
                }
            }
            //updated else block to manipulate the invalidMoveMessage variable.
            if (mtype >= n)//should only push fewer than n of the opponent's marbles
            {
                invalidMoveMessage = " - Invalid move: You do not have a Sumito Advantage. You need more marbles than your opponent's marbles in order to push them.";
                return false;
            }
        } else {//broad-side move
            mtype = -1;
            //updated if statement to manipulate the invalidMoveMessage variable.
            if (n <= 1)//broad-side move must use at least 2 marbles
            {
                invalidMoveMessage = " - Invalid move: Broad-side moves must use at least 2 marbles";
                return false;
            }
            cp = cells.at(l);
            //The increment condition has been updated
            for (int i = 0; i < n; ++i) {
                cell* dp = cp->getAdjacent(md); //destination pointer
                if (dp != nullptr && '+' == dp->getMarble())//is there an empty space to move to?
                    cp = cp->getAdjacent(fd);
                    //updated else block to manipulate the invalidMoveMessage variable.
                else {
                    invalidMoveMessage = " - Invalid move: Broad side moves, must move to an empty space and it cannot push an opponents marble.";
                    return false;
                }
            }
        }
        /*
         * If statement is added
         * It ensures the players alternate their turns 
         * and by doing so, a player can not make two moves in a row.
         */
        if(previousMarble != marble){
            previousMarble = marble;
        }else{
            invalidMoveMessage = " - Invalid move: Players' turns should alternate. A player can not make two turns in a row.";
            return false;
        }
        return true;
    }
}

/*
 * The executeMove member function of the board class has been modified:
 * 
 * The increment condition of the for loop has been changed.
 * It now uses a pre-increment instead of a post-increment in the increment condition of the for loop.
 * This change would help to improve efficiency.
 * 
 * The additional parameter invalidMoveMessage is passed by reference to the function.
 */
//additional parameter invalidMoveMessage is passed by reference  
bool board::executeMove(const string& l, const int& n, const int& fd, const int& md, string& invalidMoveMessage) {
    int moveType = 0; //default to in-line with no following marbles
    bool scoreMove = false;
    //additional parameter invalidMoveMessage is passed be reference to the validateMove function
    bool valid = validateMove(l, n, fd, md, moveType, scoreMove, invalidMoveMessage);
    if (valid) {
        if (moveType == -1) {//broad-side
            cell* cp = cells.at(l);
            //The increment condition has been updated
            for (int i = 0; i < n; ++i) {
                cell* dp = cp->getAdjacent(md); //destination pointer
                dp->setMarble(cp->getMarble());
                cp->setMarble('+');
                cp = cp->getAdjacent(fd);
            }
        } else {//in-line
            cell* cp = cells.at(l), *rearp = cp;
            const char marble = cp->getMarble();
            cell* frontp = cp->getAdjacent(md);
            //The increment condition has been updated
            for (int i = 1; i < n; ++i) {
                rearp = rearp->getAdjacent(fd);
            }
            if (scoreMove) {
                frontp->setMarble(rearp->getMarble());
                rearp->setMarble('+');
                if (marble == 'O')
                    boc++;
                if (marble == '@')
                    woc++;
            } else {
                cell* tipp = frontp;
                //The increment condition has been updated
                for (int i = 0; i < moveType; ++i) {
                    tipp = tipp->getAdjacent(md);
                }
                tipp->setMarble(frontp->getMarble());
                frontp->setMarble(rearp->getMarble());
                rearp->setMarble('+');
            }
        }
    }
    return valid;
}

/*
 * Added validateWinner() function as a member function of the board class
 * This function will provide a win condition for the game.
 * Also note this is a read-only member function (constant member function). 
 * 
 * This function will return an appropriate winning message if a player has won the game.
 * This function will also return true if a player has won the game or false otherwise.
 */
bool board::validateWinner(string& winnerMessage) const {
    /*
     * if statements to determine if a player has won the game
     * winnerMessage variable is also manipulated accordingly.
     */
    if (woc >= 6) {
        winnerMessage = "Congratulations: Black is the Winner! ";
        return true;
    }
    if (boc >= 6) {
        winnerMessage = "Congratulations: White is the Winner! ";
        return true;
    }
    return false;
}