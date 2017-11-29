/**
  *@file Timer.cpp
  *
  *@brief Implementation file for the Timer class
  *
  *@details Implements all member functions for the Timer class
  *
  *@version 1.00
  *@author Chris Lewis (September 27, 2017)
*/

//
// Header Files //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include "Timer.h"

#include <ctime>
#include <stdexcept>
#include <iostream>
#include <sys/time.h>

//
// class/data structure member implementation ////////////////////////////////////////////////////////////////////////////////////////////////
//

/**
	  *@brief default constructor
	  *
	  *@details initializes all of the member variables
	  *
	  *@post a Timer has been made
	  *
	  *@exception None
	  *
	  *@return None
	  *
	  *@note None
*/
Timer::Timer(){

	beginTime.tv_sec = -1; 
	duration.tv_sec = -1;

	timerWasStarted = false;

}

/**
	  *@brief start()
	  *
	  *@details starts the timer and sets the beginTime variable
	  *
	  *@pre a timer must have been made
	  *
	  *@post the beginTime has been set and timerWasStarted = true
	  *
	  *@exception If the gettime of day function fails it sends out a runtime_error
	  *
	  *@return None
	  *
	  *@note None
*/
void Timer::start() throw (runtime_error){

	if( -1 == gettimeofday(&beginTime, NULL) ) throw (std::runtime_error("timer::start() runtime_error"));

	timerWasStarted = true;

}
/**
	  *@brief stop()
	  *
	  *@details stops the timer
	  *
	  *@pre the timer has been started and a timer exists
	  *
	  *@post the timer is stopped and duration gets set
	  *
	  *@exception if the timer was not started
	  *
	  *@return None
	  *
	  *@note None
*/
void Timer::stop() throw (logic_error){

	if(timerWasStarted == false) throw (std::logic_error("Timer::stop() timer was not started"));

	gettimeofday(&duration, NULL);
	timerWasStarted = false;

}

/**
	  *@brief getElapsedTime()
	  *
	  *@details obtains the time between beginTime and duration
	  *
	  *@pre the timer must have ran before
	  *
	  *@post the change in time has been calculated
	  *
	  *@exception if the timer is still running or the timer has not been ran
	  *
	  *@return double, the difference in time between beginTime and duration
	  *
	  *@note None
*/
double Timer::getElapsedTime() const throw (logic_error){

	if(timerWasStarted) throw (std::logic_error("timer::getElapsedTime() timer is still going"));
	if(beginTime.tv_sec == -1) throw (std::logic_error("timer::getElapsedTime() timer has not been ran"));

	double t1,t2;

	t1 = beginTime.tv_sec * 1000000 + beginTime.tv_usec;
    t2 = duration.tv_sec * 1000000 + duration.tv_usec;
    
    return (t2 - t1)/1000000.0;

}
