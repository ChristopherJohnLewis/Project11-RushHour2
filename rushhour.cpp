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
bool SolveIt(int moves, std::queue<std::string> workQueue, std::map<std::string, int> dictionary, int count, int& finalMoves);
std::string char_to_string(char** array);
void string_to_char(std::string str, char temp[board::MAX_SIZE][board::MAX_SIZE]);

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
		std::string currBoard;
		currBoard = char_to_string(playBoard.getBoard());
		workQueue.push(currBoard);
		dictionary.insert(std::pair<std::string, int>(currBoard, 0));
		if(SolveIt(0, workQueue, dictionary, 1, finalMoves))
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
	if(playBoard.carArr[0].x + playBoard.carArr[0].size == 6)
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
bool SolveIt(int moves, std::queue<std::string> workQueue, std::map<std::string, int> dictionary, int count, int& finalMoves){
	std::string currBoard;
	char tempBuffer[board::MAX_SIZE][board::MAX_SIZE];
	int newCount = 0;
	board playBoard;
	if(count == 0)	// Count should only be 0 if there are no more options left to move.
	{
		return false;
	}
	for(int i = 0; i < count; i++)
	{
		string_to_char(workQueue.front(), tempBuffer);
		playBoard.setBoard(tempBuffer);
		currBoard = char_to_string(playBoard.getBoard());
		workQueue.pop();
		if(DidWeWin(playBoard))
		{
			finalMoves = moves;
			return true;
		}
		workQueue.push(currBoard);
	}
	for(int i = 0; i < count; i++)
	{
		string_to_char(workQueue.front(), tempBuffer);
		playBoard.setBoard(tempBuffer);
		workQueue.pop();
		for(int i = 0; i < playBoard.carInArray; i++)
		{
			if(playBoard.moveForward(i))
			{
				currBoard = char_to_string(playBoard.getBoard());
				if(dictionary.find(currBoard) != dictionary.end())
				{
					dictionary.insert(std::pair<std::string, int>(currBoard, moves));
					workQueue.push(currBoard);
					newCount++;
				}
				playBoard.moveBack(i);
			}
			if(playBoard.moveBack(i))
			{
				currBoard = char_to_string(playBoard.getBoard());
				if(dictionary.find(currBoard) != dictionary.end())
				{
					dictionary.insert(std::pair<std::string, int>(currBoard, moves));
					workQueue.push(currBoard);
					newCount++;
				}
				playBoard.moveForward(i);
			}
		}
	}
	return SolveIt(moves+1, workQueue, dictionary, newCount, finalMoves);	
}

std::string char_to_string (char** array)
  {
   std::string temp;
   for (unsigned int i = 0; i < 1; i += 1)
    {
     temp+=array[i];
     temp+="\0";	
    }
   return temp;
  } 

void string_to_char(std::string str, char temp[board::MAX_SIZE][board::MAX_SIZE])
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
