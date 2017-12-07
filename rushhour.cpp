/**
  *@file rushhour.cpp
  *
  *@brief The main running file, where most of the operation happens
  *
  *@details Implements the algorithm that we need to solve the game as well as reads in to the board
  *
  *@version 2.00
  *@author Chris Lewis, Autumn Cuellar, Alex Pasinski (December 5, 2017)
*/

//
// Header Files //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <iostream>
#include <queue>
#include <map>
#include <vector>

#include "car.h"
#include "board.h"

bool readIn(board& playBoard);
bool DidWeWin(const board& playBoard);
bool SolveIt(std::queue<std::string>& workQueue, std::map<std::string, int>& dictionary, board& playBoard, int& finalMoves);

/**
	  *@brief main
	  *
	  *@details initializes the board and runs all of the algorithms
	  *
	  *@pre 
	  *
	  *@post the board has been solved and the user has quit the program
	  *
	  *@exception none
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
		// solve the board and output the results
		if(SolveIt(workQueue, dictionary, playBoard, finalMoves))
		{
			std::cout << "Scenario "<< i << " requires " << finalMoves << " moves" << std::endl;
		}
		else
		{
			std::cout << "Scenario "<< i << " is unsolvable." << std::endl;
		}
		i++;
		playBoard.clear(); // Reset board for next scenario.
	}

	return 0;

}

/**
	  *@brief ReadIn
	  *
	  *@details reads input from the user into the board
	  *
	  *@post the board has been filled in
	  *
	  *@exception None
	  *
	  *@param[in] the board that we are filling in (initially filled with '*')
	  *
	  *@param[out] the board has been filled in with the cars
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
	  *@details Checks if the 0th element car is at the border of the board
	  *
	  *@pre Board must have been made and has atleast one car in it
	  *
	  *@post the board has been evaluated
	  *
	  *@exception None
	  *
	  *@param[in] takes in the board that we are currently using to solve the problem
	  *
	  *@return bool that says if the car has made it to the end of the board or not
	  *
	  *@note None
*/
bool DidWeWin(const board& playBoard){
	for(int i = 0; i < board::MAX_SIZE; i++)
	{
		if(playBoard.getBoard()[i*board::MAX_SIZE+5] == '0')
		{
			return true;
		}
	}
	return false;
}

/**
	  *@brief SolveIt
	  *
	  *@details the main algorithm in the program. It tests every single move the car can make. Breadth-first search is being used.
	  *
	  *@pre Board must have been made and has atleast one car in it
	  *
	  *@post the board has been solved (or can't be solved)
	  *
	  *@exception None
	  *
	  *@param[in] takes in an int reference that says how many moves to solve the board, a map holding the boards we visted, a queue holding the current boards to use, and a board for the original board  
	  *
	  *@return true if the board was solved, otherwise false
	  *
	  *@note moves is only really used after the first recursive call
*/
bool SolveIt(std::queue<std::string>& workQueue, std::map<std::string, int>& dictionary, board& playBoard, int& finalMoves){
	bool done = false, solved = false;	// Done tells us if we've reached a stopping point and solved tells us if we've solved it.
	int moves = 0;	// Used to store the number of moves so far.
	int count = workQueue.size();	// Used so that we can loop through each queue once without going until the queue is empty.
	std::queue<car> carQueue;	// This queue holds the cars for each instance of a board in the workQueue.
	
	// Since the queue can't easily be made to hold arrays of cars, we instead loop through each element in the car array push it onto the queue
	// Because the queues are pushed and popped at the same rate, we can be confident in simply pushing each car on without an array structure to hold them.
	for(int i = 0; i < playBoard.getNumOfCars(); i++)
	{
		carQueue.push(playBoard.getCar(i));
	}
	
	while(!done) 
	{
		count = workQueue.size();
		if(workQueue.size() == 0)	// workQueue should only be 0 if there are no more options left to move.
		{
			done = true;
			solved = false;
		}
		
		// Check each board in the queue to see if we won by popping and pushing them around.
		for(unsigned int i = 0; i < workQueue.size() && !done; i++)
		{
			playBoard.setBoard(workQueue.front());
			if(DidWeWin(playBoard))
			{
				finalMoves = moves;
				done = true;
				solved = true;
			}
			workQueue.pop();
			workQueue.push(playBoard.getBoard());
			

		}
		
		moves++;	// Increment moves for each level of tree.
		for(int i = 0; i < count && !done; i++)
		{
			playBoard.setBoard(workQueue.front());
			for(int i = 0; i < playBoard.getNumOfCars(); i++)
			{
				playBoard.setCar(i, carQueue.front());
				carQueue.pop();
			}
			
			workQueue.pop();
			for(int j = 0; j < playBoard.getNumOfCars(); j++)
			{
				if(playBoard.moveForward(j))
				{
					if(dictionary.find(playBoard.getBoard()) == dictionary.end())
					{
						dictionary.insert(std::pair<std::string, int>(playBoard.getBoard(), moves));
						workQueue.push(playBoard.getBoard());
						for(int i = 0; i < playBoard.getNumOfCars(); i++)
						{
							carQueue.push(playBoard.getCar(i));
						}
					}
					playBoard.moveBack(j);
				}
				
				if(playBoard.moveBack(j))
				{
					if(dictionary.find(playBoard.getBoard()) == dictionary.end())
					{
						dictionary.insert(std::pair<std::string, int>(playBoard.getBoard(), moves));
						workQueue.push(playBoard.getBoard());
						for(int i = 0; i < playBoard.getNumOfCars(); i++)
						{
							carQueue.push(playBoard.getCar(i));
						}
					}
					playBoard.moveForward(j);
				}
			}
		}
	}
	
	return solved;
}
