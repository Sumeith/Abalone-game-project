/**
 * int Elligence - 2021COMP315ProjectGroupA
 * 
 * Team members:    Sumeith Ishwanthlal (219006284)
 *                  Sandhya Singh       (219010492)
 *                  Tashvir Singh       (219044683)
 *                  Siphiwe Maphalala   (217034316)          
 */

 /**
  * main.cpp
  * 
  * This file has been modified from the guided part of the project.
  * 
  * The changes occurred:   main()              //the main function
  * 
  * Please Note: There are comments where the changes have been made.
  */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: MSCS
 *
 * Created on 12 March 2020, 8:38 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "board.h"

using namespace std;

/*
 * The main function has been updated 
 * 
 * The variables invalidMoveMessage and winnerMessage has been declared and initialized.
 * 
 * If a move is valid, the game will state that it is a valid move.
 * Then, the new state of the board would be displayed.
 * 
 * If the win condition is met, the application terminates successfully,
 * and an appropriate message is displayed with the winnerMessage variable. 
 * 
 * If an error occurs, an appropriate error message is displayed with the invalidMoveMessage variable.  
 */
int main(int argc, char** argv) {
    
    //invalidMoveMessage stores and displays the invalid move message
    string invalidMoveMessage = " - Invalid move!";
    
    //winnerMessage stores and displays the appropriate message if a player has won the game.
    string winnerMessage= "Game still in progress";
    
    if(argc==2){
        board abalone;
        string ibs(abalone);
        cout<<"Initial Abalone board state:"<<endl;
        cout<<ibs<<endl;        
        ifstream log(argv[1]);//sequence of game moves
        string l;
        int n, fd, md;
        while(log>>l>>n>>fd>>md){
            cout<<"Move: "<<l<<" "<<n<<" "<<fd<<" "<<md;
            //added the parameter invalidMoveMessage to executeMove() function which is passed by reference
            bool valid = abalone.executeMove(l,n,fd,md,invalidMoveMessage);
            if(valid){
                string nbs(abalone);
                //The game will state that the move is valid
                cout<<" - Valid Move - Next Abalone board state: "<<endl;
                cout<<nbs<<endl;
                /*
                 * if statement that would determine if a player has won the game.
                 * An appropriate winning message will be displayed.
                 * The application will then terminate successfully.
                 */
                if(abalone.validateWinner(winnerMessage)){
                    cout<<winnerMessage<<endl;
                    return 0;
                }
            }
            else{
                //The Invalid Move Message is displayed
                cout<< invalidMoveMessage << "\n" << endl;
            }
        }
        /*
         * All the moves in the moves in the moves.txt have been executed 
         * but there is no winner as yet.
         */
        cout << "All the moves have been executed." << endl;
        cout << "No winner can be announced - A player must push 6 of the opponent's marbles in order to win the game." << endl;
        return 0;
    }
    return -1;
}

