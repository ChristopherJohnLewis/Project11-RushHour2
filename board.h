/**
  *@file board.h
  *
  *@brief the board that we are playing on
  *
  *@details The class that keeps track of the cars, and the board that we are playing on
  *
  *@version 1.00
  *@author Chris Lewis (October 4, 2017)
*/

#ifndef BOARD_H
#define BOARD_H

#include <string>
#include "car.h"

class board{

public:
	
	static const int MAX_SIZE = 6;
	static const int MAX_CARS = 18;

	std::string getBoard() const
	{
		return boardArr;
	}
	
	void setBoard(std::string newBoard)
	{
		boardArr = newBoard;
	}
	
	car getCar(int carNum) const
	{
		return carArr[carNum];
	}
	
	int getNumOfCars() const
	{
		return carInArray;
	}
		
/**
	  *@brief add
	  *
	  *@details adds the values passed in as a car to the board
	  *
	  *@pre the board must have existed
	  *
	  *@post the board has a car added to it
	  *
	  *@exception None
	  *
	  *@param[in] takes in all of the things necessary to create a car
	  *
	  *@return None
	  *
	  *@note this is overloaded in the next function
*/
		void add(const int sizeCar, const char orientation, const int xLoc, const int yLoc, const int carNum){

			carInArray++;

			if(orientation == 'H'){

				for(int i = 0; i < sizeCar; i++){
					boardArr[yLoc * MAX_SIZE + (xLoc + i)] = carNum+48;
					
				}

			}

			else{

				for(int i = 0; i < sizeCar; i++){
					boardArr[(yLoc + i) * MAX_SIZE + xLoc] = carNum+48;

				}				

			}

			carArr[carNum].changeCar(sizeCar, orientation, xLoc, yLoc);

		}
/**
	  *@brief add (overloaded)
	  *
	  *@details adds the car to the board via a const reference to another car and assigns the right value to it via the int passed in
	  *
	  *@pre a board must exist already
	  *
	  *@post the board has been updated with another car
	  *
	  *@exception None
	  *
	  *@param[in] the car we are copying from and the int that we are assigning the car to
	  *
	  *@return None
	  *
	  *@note this is overloaded above
*/
		void add(const car& other, int carNum){

			carInArray++;

			if(other.direction == 'H'){

				for(int i = 0; i < other.size; i++){

					boardArr[other.y * MAX_SIZE + (other.x + i)] = carNum+48;
					
				}

			}

			else{

				for(int i = 0; i < other.size; i++){

					boardArr[(other.y + i) * MAX_SIZE + other.x] = carNum+48;

				}				

			}

		}
/**
	  *@brief deleteCar
	  *
	  *@details deletes the car from the array 
	  *
	  *@pre a car must exist
	  *
	  *@post the car has been effectively erased from the board
	  *
	  *@exception None
	  *
	  *@param[in] an int that represents the car's number
	  *
	  *@return None
	  *
	  *@note
*/
		void deleteCar(const int carNum){

			carInArray--;

			if (carArr[carNum].direction == 'H'){

				for(int i = 0; i < carArr[carNum].size; i++){

					boardArr[carArr[carNum].y * MAX_SIZE + (carArr[carNum].x + i)] = '*';
					
				}

			}
			else{

				for(int i = 0; i < carArr[carNum].size; i++){

					boardArr[(carArr[carNum].y + i) * MAX_SIZE + carArr[carNum].x] = '*';

				}

			}

		}
/**
	  *@brief moveBack
	  *
	  *@details moves the car one space back by deleting it and then adding it back on
	  *
	  *@pre a car must exist
	  *
	  *@post the car has been moved on the board
	  *
	  *@exception if their is something stopping the car from going backwards (another car or border) returns false
	  *
	  *@param[in] the number of the car that we want to move back
	  *
	  *@return true if the function executed properly false if the exception has been hit
	  *
	  *@note
*/
		bool moveBack(const int carNum){

			bool ableMove;

			if(carArr[carNum].direction == 'H'){

				if((boardArr[carArr[carNum].y * MAX_SIZE + (carArr[carNum].x - 1)] == '*') && (carArr[carNum].x - 1 >= 0)){
					
					ableMove = true;

					deleteCar(carNum);
					carArr[carNum].x -= 1;

					add(carArr[carNum], carNum);

				}

				else{

					ableMove = false;

				}

			}

			else{
			
				
				if((boardArr[(carArr[carNum].y - 1) * MAX_SIZE + carArr[carNum].x] == '*') && (carArr[carNum].y - 1 >= 0)){
					
					ableMove = true;
	
					deleteCar(carNum);
					carArr[carNum].y -= 1;
	
					add(carArr[carNum], carNum);
	
				}

				else{

					ableMove = false;

				}

			}

			return ableMove;

		}
/**
	  *@brief moveForward
	  *
	  *@details moves the car forwards by deleting it and then adding it one space forward
	  *
	  *@pre a car must be created 
	  *
	  *@post the car has moved one space forward on the board
	  *
	  *@exception if the car has something obstructing it from going forward returns false
	  *
	  *@param[in] the number of the car we are moving forward
	  *
	  *@return true if the function executes properly and false if the exception has been hit
	  *
	  *@note 
*/
		bool moveForward(const int carNum){

			bool ableMove;

			if(carArr[carNum].direction == 'H'){
			
				if((boardArr[(carArr[carNum].y) * MAX_SIZE + (carArr[carNum].x + carArr[carNum].size)] == '*') && (carArr[carNum].x + 1 < 5))
				{
					ableMove = true;

					deleteCar(carNum);
					carArr[carNum].x += 1;

					add(carArr[carNum], carNum);
				}

				else{

					ableMove = false;

				}

			}

			else{
				if((boardArr[(carArr[carNum].y + carArr[carNum].size) * MAX_SIZE + carArr[carNum].x] == '*') && (carArr[carNum].y + 1 < 6))
				{
					ableMove = true;

					deleteCar(carNum);
					carArr[carNum].y += 1;

					add(carArr[carNum], carNum);
				}

				else{

					ableMove = false;

				}

			}
			
			return ableMove;

		}
		
private:
	int carInArray;
	car carArr[MAX_CARS];
	std::string boardArr;

};

#endif
