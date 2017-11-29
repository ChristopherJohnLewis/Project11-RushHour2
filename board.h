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

#include "car.h"

class board{

	public:
/**
	  *@brief Default constructor
	  *
	  *@details makes the board and sets the variables
	  *
	  *@pre 
	  *
	  *@post the board has been created with default variables
	  *
	  *@exception None
	  *
	  *@param[in] None
	  *
	  *@return None
	  *
	  *@note the default values for the board are * to represent empty space
*/
		board(){

			cap = 10;
			carInArray = 0;

			for(int j = 0; j < 6; j++){

				for(int i = 0; i < 6; i++){

					boardArr[j][i] = '*';

				}

			}

			bestMoves = 100;

		}
/**
	  *@brief copy constructor
	  *
	  *@details copies the board and the variables from the other board
	  *
	  *@pre another board must exist
	  *
	  *@post the board has been created with the values set to the same as the other board
	  *
	  *@exception None
	  *
	  *@param[in] the board we are copying from
	  *
	  *@return None
	  *
	  *@note
*/
		board(const board& other){

			bestMoves = other.bestMoves;
			carInArray = other.carInArray;
			cap = other.cap;

			for(int j = 0; j < 6; j++){

				for(int i = 0; i < 6; i++){

					boardArr[j][i] = other.boardArr[j][i];

				}

			}

			for(int i = 0; i < 10; i++){

				carArr[i] = other.carArr[i];

			}

		}

/**
	  *@brief operator=
	  *
	  *@details copies the board and the variables from the other board
	  *
	  *@pre another board must exist
	  *
	  *@post the board has been created with the values set to the same as the other board
	  *
	  *@exception if the board being passed in has the same memory position as this board
	  *
	  *@param[in] the board we are copying from
	  *
	  *@return this board so we can chain
	  *
	  *@note
*/

		board& operator=(const board& other){

			if(&other == this){}
			
			else{
				
				bestMoves = other.bestMoves;
				carInArray = other.carInArray;
				cap = other.cap;

				for(int j = 0; j < 6; j++){

					for(int i = 0; i < 6; i++){

						boardArr[j][i] = other.boardArr[j][i];

					}

				}

				for(int i = 0; i < 10; i++){

					carArr[i] = other.carArr[i];

				}

			}

			return (*this);

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

					boardArr[yLoc][xLoc + i] = carNum+48;

				}

			}

			else{

				for(int i = 0; i < sizeCar; i++){

					boardArr[yLoc + i][xLoc] = carNum+48;

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

					boardArr[other.y][other.x + i] = carNum+48;

				}

			}

			else{

				for(int i = 0; i < other.size; i++){

					boardArr[other.y + i][other.x] = carNum+48;

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

					boardArr[carArr[carNum].y][(carArr[carNum].x) + i] = '*';

				}

			}
			else{

				for(int i = 0; i < carArr[carNum].size; i++){

					boardArr[(carArr[carNum].y) + i][(carArr[carNum].x)] = '*';

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

				if((boardArr[carArr[carNum].y][carArr[carNum].x - 1] == '*') && (carArr[carNum].x - 1 >= 0)){
					
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
			
				if((boardArr[(carArr[carNum].y - 1)][carArr[carNum].x] == '*') && (carArr[carNum].y - 1 >= 0)){
					
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
			
				if((boardArr[(carArr[carNum].y )][carArr[carNum].x + carArr[carNum].size] == '*') && (carArr[carNum].x + 1 < 5)){
					
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
				
				if((boardArr[(carArr[carNum].y + carArr[carNum].size)][carArr[carNum].x] == '*') && (carArr[carNum].y + 1 < 6)){
					
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

		int cap;
		int carInArray;
		int bestMoves;
		char boardArr[6][6];
		car carArr[10];

};

#endif