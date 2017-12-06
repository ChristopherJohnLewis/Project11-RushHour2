/**
  *@file car.h
  *
  *@brief something to keep track of the values the cars need
  *
  *@details creates a simple car class to hold the 4 values that defines the car
  *
  *@version 1.00
  *@author Chris Lewis, Autumn Cuellar, Alex Pasinski (December 5, 2017)
*/

#ifndef CAR_H
#define CAR_H

class car{

	public:
/**
	  *@brief default constructor
	  *
	  *@details sets all of the values in the car to values that dont matter
	  *
	  *@pre None
	  *
	  *@post the car has been created
	  *
	  *@exception None
	  *
	  *@param[in] None
	  *
	  *@return None
	  *
	  *@note 
*/
		car(){
			
			x = 0;
			y = 0;
			direction = '~';
			size = 0;

		}
/**
	  *@brief parameterized constructor
	  *
	  *@details sets all of the values in car to what are passed in
	  *
	  *@pre 
	  *
	  *@post the car has been initialized to the values passed in
	  *
	  *@exception None
	  *
	  *@param[in] takes in an int, char, int, and int that correspond to size of the car, orientation of the car, x coordinate, and y coordinate of the car respectively
	  *
	  *@return None
	  *
	  *@note not really ever used but included for posterity
*/
		car(int sizeCar, char orientation, int xLoc, int yLoc){

			x = xLoc;
			y = yLoc;
			direction = orientation;
			size = sizeCar;

		}
/**
	  *@brief copy constructor
	  *
	  *@details sets all of the values in the newly created car to the values in a different car
	  *
	  *@pre another car must have been created
	  *
	  *@post a new car has been created
	  *
	  *@exception None
	  *
	  *@param[in] takes in a car by const reference to copy the data of.
	  *
	  *@return None
	  *
	  *@note 
*/
		car(const car& other){

			x = other.x;
			y = other.y;
			direction = other.direction;
			size = other.size;

		}
/**
	  *@brief operator=
	  *
	  *@details sets the values of this car to the values of the car passed in
	  *
	  *@pre this car must have been created
	  *
	  *@post this car has been set to the values in the other car
	  *
	  *@exception if the car doesn't exist (size 0), or the car is at the same memory address as this car doesn't do anything
	  *
	  *@param[in] takes in the car we are copying from via  const reference
	  *
	  *@return always returns this car by reference so that we can chain
	  *
	  *@note 
*/
		car& operator=(const car& other){

			if(other.size == 0){}
			
			if(&other == this){}
			
			else{
				
				x = other.x;
				y = other.y;
				direction = other.direction;
				size = other.size;

			}

			return (*this);

		}
/**
	  *@brief changeCar
	  *
	  *@details sets the values of this car to the values passed to it
	  *
	  *@pre this car must have been created
	  *
	  *@post this car has been set to the values passed into it
	  *
	  *@exception None
	  *
	  *@param[in] an int, char, int, int. these correspond to the size of the car, direction the car is, the x coordinate and the y coordinate of the car's top-right most place
	  *
	  *@return None
	  *
	  *@note 
*/
		void changeCar(int sizeCar, char directionCar, int xPos, int yPos){

			size = sizeCar;
			direction = directionCar;
			x = xPos;
			y = yPos;

		}
		
		int size;
		char direction;
		int x;
		int y;

};

#endif
