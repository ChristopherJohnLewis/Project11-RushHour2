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
#include <queue>
#include <map>

//#include "Timer.h" //Found out the 8 car case finishes in about 103.4 seconds
#include "car.h"
#include "board.h"

bool readIn(board& playBoard);
bool DidWeWin(const board& playBoard);
bool SolveIt(std::queue<std::string>& workQueue, std::map<std::string, int>& dictionary, int& finalMoves);

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
	int finalMoves = 0;
	std::queue<std::string> workQueue;
	std::map<std::string, int> dictionary;

	int i = 1;

	while(readIn(playBoard)){
		// Reset containers for next scenario.
		finalMoves = 0;
		while(!workQueue.empty())
		{
			workQueue.pop();
		}
		dictionary.clear();
		
		// Push first board.
		workQueue.push(playBoard.getBoard());
		dictionary.insert(std::pair<std::string, int>(playBoard.getBoard(), 0));
		if(SolveIt(workQueue, dictionary, finalMoves))
		{
			std::cout << "Scenario "<< i << " requires " << finalMoves << " moves" << std::endl;
		}
		else
		{
			std::cout << "Scenario "<< i << "is unsolvable." << std::endl;
		}
		i++;
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
	if(playBoard.getCar(0).x + playBoard.getCar(0).size == 6)
	{
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
bool SolveIt(std::queue<std::string>& workQueue, std::map<std::string, int>& dictionary, int& finalMoves){
	bool done = false, solved = false;
	int moves = 0;
	board playBoard;
	
	while(!done)
	{
		if(workQueue.size() == 0)	// Count should only be 0 if there are no more options left to move.
		{
			done = true;
			solved = false;
		}
		for(unsigned int i = 0; i < workQueue.size() && !done; i++)
		{
			playBoard.setBoard(workQueue.front());
			workQueue.pop();
			if(DidWeWin(playBoard))
			{
				finalMoves = moves;
				done = true;
				solved = true;
			}
			workQueue.push(playBoard.getBoard());
		}
		moves++;	// Increment moves for each level of tree.
		for(unsigned int i = 0; i < workQueue.size() && !done; i++)
		{
			playBoard.setBoard(workQueue.front());
			workQueue.pop();
			for(int j = 0; j < playBoard.getNumOfCars(); j++)
			{
				if(playBoard.moveForward(j))
				{
					if(dictionary.find(playBoard.getBoard()) == dictionary.end())
					{
						dictionary.insert(std::pair<std::string, int>(playBoard.getBoard(), moves));
						workQueue.push(playBoard.getBoard());
					}
					playBoard.moveBack(j);
				}
				if(playBoard.moveBack(j))
				{
					if(dictionary.find(playBoard.getBoard()) == dictionary.end())
					{
						dictionary.insert(std::pair<std::string, int>(playBoard.getBoard(), moves));
						workQueue.push(playBoard.getBoard());
					}
					playBoard.moveForward(j);
				}
			}
		}
	}
	
	return solved;
}
