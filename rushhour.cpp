/**
  *@file rushhour.cpp
  *
  *@brief The main running file, where most of the operation happens
  *
  *@details Implements the algorithm that we need to solve the game as well as reads in to the board
  *
  *@version 1.00
  *@author Chris Lewis (October 4, 2017)
*/

//
// Header Files //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <iostream>
#include <string>

#include "Timer.h" //Found out the 8 car case finishes in about 103.4 seconds
#include "car.h"
#include "board.h"

bool readIn(board& playBoard);
bool DidWeWin(const board& playBoard);
void SolveIt(int moves, board& playBoard);
std::string char_to_string (char array[][6], int n);
void string_to_char(std::string str, char temp[][6], int n);

/**
	  *@brief main
	  *
	  *@details initializes the board and runs all of the algorithms
	  *
	  *@pre 
	  *
	  *@post the board has been solved and the user has quit the program
	  *
	  *@exception None
	  *
	  *@return None
	  *
	  *@note None
*/
int main(){

	board playBoard; 

	int i = 1;

	while(readIn(playBoard)){

		Timer stdTimer;
		stdTimer.start();

		SolveIt(0, playBoard);

		stdTimer.stop();
		std::cout<<"Elapsed Time = " << stdTimer.getElapsedTime()<<" seconds"<<std::endl;

		if(playBoard.bestMoves == 100){

			std::cout << "Not able to be solved in less than " << playBoard.cap << " moves"<<std::endl;
			continue;

		}
		
		std::cout << "Scenario "<< i << " requires " << playBoard.bestMoves << " moves" << std::endl;
		playBoard.cap = 10;
		playBoard.bestMoves = 100;

	}

	return 0;

}

/**
	  *@brief ReadIn
	  *
	  *@details reads in from the user into the board
	  *
	  *@post the board has been filled in
	  *
	  *@exception None
	  *
	  *@param[in] the board that we are filling in (should be filled with '*')
	  *
	  *@param[out] the board has been filled in
	  *
	  *@return if the numCars the user entered in is 0 return false to exit out of the loop in main, if true it continues
	  *
	  *@note None
*/
bool readIn(board& playBoard){

	int numCars, sizeCar, xLoc, yLoc;
	char orientation;
	bool doScenario = true;
	std::cin >> numCars;
	if(numCars == 0) doScenario = false;

	else{

		for(int i = 0; i < numCars; i++){
			
			std::cin >> sizeCar >> orientation >> yLoc >> xLoc;
			playBoard.add(sizeCar, orientation, xLoc, yLoc, i);
	  
		}

 	}

 	return (doScenario);

} 

/**
	  *@brief didWeWin
	  *
	  *@details Checks if the 0th element car is at the border of the array
	  *
	  *@pre Board must have been made and has atleast one car in it
	  *
	  *@post the board has been evaluated
	  *
	  *@exception None
	  *
	  *@param[in] takes in the board that we use to solve the problem
	  *
	  *@return bool that says if the car has made it to the end of the array or not
	  *
	  *@note None
*/
bool DidWeWin(const board& playBoard){

	if(playBoard.carArr[0].x + playBoard.carArr[0].size == 6){

		return true;

	}

	return false;

}

/**
	  *@brief SolveIt
	  *
	  *@details the main algorithm in the program. It tests every single move the car can make recursively. A depth first brute first way of doing things.
	  *
	  *@pre Board must have been made and has atleast one car in it
	  *
	  *@post the board has been solved (or can't be solved)
	  *
	  *@exception None
	  *
	  *@param[in] takes in an int that says how many moves we've done in this current section of the tree. The board that has all of the data in it
	  *
	  *@return None
	  *
	  *@note moves is only really used after the first recursive call
*/
void SolveIt(int moves, board& playBoard){

	if(moves > playBoard.cap) return;

	if(DidWeWin(playBoard)){

		playBoard.bestMoves = moves;
		playBoard.cap = moves;

	}

	for(int i = 0; i < playBoard.carInArray; i++){

		if(playBoard.moveForward(i)){

 			SolveIt(moves+1, playBoard);
 			playBoard.moveBack(i);

 		}

 		if(playBoard.moveBack(i)){

 			SolveIt(moves+1, playBoard);
 			playBoard.moveForward(i);

		}

	}

}
std::string char_to_string (char array[][6], int n)
  {
   std::string temp;
   for (unsigned int i = 0; i < 1; i += 1)
    {
     temp+=array[i];
     temp+="\0";	
    }
   return temp;
  } 
void string_to_char(std::string str, char temp[][6], int n)
 {
  int i=0, j=0;
  for (unsigned int n = 0; n < 36; n += 1)
   {
    temp[i][j]=str[n];
    j++;
    if (j==6)
     {
      i++;
      j=0;	
     }
   }
  }
