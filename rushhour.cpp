  /**
   @file rushhour.cpp
   @author Autumn Cuellar
   @date 10/1/17
   This program solves the game rush hour
   by recursively checking  all possible
   moves until the board is solved. 
  */
 
 #include<iostream>
 
 using namespace std;
 
 #define SIZE 6
 
  /// this class contains all the information for the car pieces
  
 class Cars
  {
   public:
    Cars();
    Cars(const char type, const char direction, const int x, const int y);
    bool moveForward(bool b[][SIZE], int m);
    bool moveBack(bool b[][SIZE], int m);
    void setPosition(const int x, const int y);
    void setType(const char t);
    void setDirection(const char direct);
    int getXPosition() const;
    int getYPosition() const;
    char getType();
    char getDirection();
   private:
    char type;
    char direction;
    int x_pos;
    int y_pos;
  };
  
  /// this function checks if you won the game
  
 bool DidweWin(Cars a[], int m);
 
  /// this function tries to solve the game
 
 void Solveit(int num_cars, int moves, int& cap, bool& solve, Cars a[], int m, bool b[][SIZE], int n);
 
 int main (void)
  {
    // identifying variables
   
   int cap=10, moves=0, scenario=1, num_car, type, x, y;
   bool solve=false, board[SIZE][SIZE];
   Cars pieces[8], *cur_car=pieces;
   char direction;
   
    // creating an empty board
    
   for (unsigned int i = 0; i < SIZE; i += 1)
    {
     for (unsigned int j = 0; j < SIZE; j += 1)
      {
       board[i][j]=false;  /// if array is all false, this means there is no cars on it
      }	
    }
    
    // upload board and solve it
    
   cin >> num_car;
   
   while (num_car!=0)
    {
     for (unsigned int i = 0; i < num_car; i += 1)
      {
       cin >> type;
       if (type==2)
        {
         (cur_car+i)->setType('C');
        }
       else
        {
         (cur_car+i)->setType('T');
        }
       cin >> direction;
       (cur_car+i)->setDirection(direction);
       cin >> x;
       cin >> y;
       if (type==2 && direction=='H')
        {
         board[x][y]=true;
       	 board[x][y+1]=true;
       	 (cur_car+i)->setPosition(x, y+1);
        }
       else if (type==3 && direction=='H')
        {
       	 board[x][y]=true;
       	 board[x][y+1]=true;
       	 board[x][y+2]=true;
       	 (cur_car+i)->setPosition(x, y+2);
        }
       else if (type==2 && direction=='V')
        {
       	 board[x][y]=true;
       	 board[x+1][y]=true;
       	 (cur_car+i)->setPosition(x+1, y);
        }
       else
        {
         board[x][y]=true;
         board[x+1][y]=true;
         board[x+2][y]=true;
         (cur_car+i)->setPosition(x+2, y);
        }
      }
     Solveit(num_car, moves, cap, solve, pieces, 5, board, SIZE);
     if (solve)
      {
       cout << "Scenario " << scenario << " requires " << cap << " moves" << endl;	
      }
     else
      {
       cout << "Scenario " << scenario << " could not be solved" << endl;
      }
     scenario++;
     cin  >> num_car;
     cap=10;
     moves=0;
    }
  
   return 0;
  }
  
  /**
   Name: Solveit
   @param an int the says how many cars are on the board, an int that keeps track of how many moves have been taken, an int reference that keeps the lowest moves to solve the board, a bool reference that keeps track of if the game was won, a Cars array that holds the car pieces, an int that tells the max number of cars the Cars array can hold, a bool 2x2 array that represents the board, and an int that tells the max rows of the board
   @pre the board and cars must be loaded
   Function: Goes through the board recursively and checks if each car can
   	     move forwards and backwards. This function stops when DidweWin()
   	     returns true orr moves is greater than cap. 
   @return nothing because the boolean reference tells if we win or not 
  */
  
 void Solveit(int num_cars, int moves, int& cap, bool& solve, Cars a[], int m, bool b[][SIZE], int n)
  {
   if (DidweWin(a, m))
    {
     if (moves<=cap)
      {
       cap=moves;	
      }	
     solve=true;
     return;
    }
   if (moves>cap)
    {
     return;	
    }
   Cars* cptr=a;
   for (unsigned int i = 0; i < num_cars; i += 1)
    {
     if ((cptr+i)->moveForward(b, n))
      {
       Solveit(num_cars, moves+1, cap, solve, a, m, b, n);
       (cptr+i)->moveBack(b, n);	
      }	
     if ((cptr+i)->moveBack(b, n))
      {
       Solveit(num_cars, moves+1, cap, solve, a, m, b, n);
       (cptr+i)->moveForward(b, n);
      }
    }
  }
  
  /**
   Name: DidweWin
   @param a Cars array that holds the car pieces and an int that tells the max number of cars the Cars array can hold
   Function: checks if the 0th element in the array is at the right edge
   	     of the board (y=SIZE-1)
   @return true if the car is in that spot otherwise false
  */
  
 bool DidweWin(Cars a[], int m)
  {
   if (a->getYPosition()==(SIZE-1))
    {
     return true;	
    }
   return false;
  }
  
  /**
   Name: Cars (default constructor)
   Function: sets the Cars class members to an invalid value 
  */
  
 Cars :: Cars() : type('N'), direction('n'), x_pos(10), y_pos(10) {}
 
  /**
   Name: Cars (parameterized constructor)
   @param a const char for the type of the vehicle, a const char for the direction the vehicle is going, a const int for the x position on the board, and a const int for the y position on the board
   Function: sets the Cars class member to the values passed by parameters
  */
  
 Cars :: Cars(const char type, const char direction, const int x, const int y) : type(type), direction(direction), x_pos(x), y_pos(y) {}
 
  /**
   Name: moveForward
   @param a boolean 2x2 array for the game board and an int that tells the max rows of the board
   Function: checks if a vehicle can move forward (left or down) and moves it
   @return true if the car wass moved forward otherwise false
  */
 
 bool Cars :: moveForward(bool b[][SIZE], int m)
  {
    if (direction=='H')
     {
      if (y_pos!=SIZE-1 && b[x_pos][y_pos+1]==false)
       {
        if (type=='C')
         {
          b[x_pos][y_pos-1]=false;
      	  b[x_pos][y_pos+1]=true;
      	  ++y_pos;
      	  return true;	
      	 }
      	else
      	 {
      	  b[x_pos][y_pos-2]=false;
      	  ++y_pos;
      	  b[x_pos][y_pos]=true;
      	  return true;
      	 }
       }
      return false;	
     }
    else
     {
      if (x_pos!=m-1 && b[x_pos+1][y_pos]==false)
       {
      	if (type=='C')
      	 {
      	  b[x_pos-1][y_pos]=false;
      	  ++x_pos;
      	  b[x_pos][y_pos]=true;
      	  return true;
      	 }
      	else
      	 {
      	  b[x_pos-2][y_pos]=false;
      	  ++x_pos;
      	  b[x_pos][y_pos]=true;
      	  return true;
      	 }
       }
      return false;
     }
  }
  
  /**
   Name: moveBack
   @param a boolean 2x2 array for the game board and an int that tells the max rows of the board
   Function: checks if a vehicle can move backward (right or up) and moves it
   @return true if the car wass moved backward otherwise false
  */
  
 bool Cars :: moveBack(bool b[][SIZE], int m)
  {
   if (direction=='H')
    {
     if (type=='C')
      {
       if ((y_pos-1)!=0 && b[x_pos][y_pos-2]==false)
        {
       	 b[x_pos][y_pos]=false;
       	 --y_pos;
       	 b[x_pos][y_pos-1]=true;
       	 return true;
        }
       return false;	
      }
     else
      {
       if ((y_pos-2)!=0 && b[x_pos][y_pos-3]==false)
        {
       	 b[x_pos][y_pos]=false;
       	 --y_pos;
       	 b[x_pos][y_pos-2]=true;
       	 return true;
        }
      }	
    }
   else
    {
     if (type=='C')
      {
       if ((x_pos-1)!=0 && b[x_pos-2][y_pos]==false)
        {
       	 b[x_pos][y_pos]=false;
       	 --x_pos;
       	 b[x_pos-1][y_pos]=true;
       	 return true;
        }	
       return false;
      }
     else
      {
       if ((x_pos-2)!=0 && b[x_pos-3][y_pos]==false)
        {
       	 b[x_pos][y_pos]=false;
       	 --x_pos;
       	 b[x_pos-2][y_pos]=true;
       	 return true;
        }
       return false;
      }
    }
  }
  
  /**
   Name: setPosition
   @param a const int for the x position and a const int for the y position
   Function: sets x_pos and y_pos with the x and y coordinates of the front
   	     of a vehicle 
  */
  
 void Cars :: setPosition(const int x, const int y)
  {
   x_pos=x;
   y_pos=y;
  }
  
  /**
   Name: setType
   @param a const char for the type of the vehicle (C=car and T=truck)
   Function: sets the Cars class member type
  */
  
 void Cars :: setType(const char t)
  {
   type=t;
  }
  
  /**
   Name: setDirection
   @param a const char for the direction of the vehicle  (H=left/right and V=up/down)
   Function: sets the Cars class member direction
  */
  
 void Cars :: setDirection(const char direct)
  {
   direction=direct;
  }
  
  /**
   Name: getXPosition
   Function: gets the value of x_pos
   @return an int for the vehicle's front x position
   It has a const siginature.
  */
  
 int Cars :: getXPosition() const
  {
   return x_pos;
  }
  
  /**
   Name: getYPosition
   Function: gets the value of y_pos
   @return an int for the vehicle's front y position
   It has a const siginature.
  */
  
 int Cars :: getYPosition() const
  {
   return y_pos;
  }
  
  /**
   Name: getType
   Function: gets the value of type
   @return a char for the vehicle's type
  */
  
 char Cars :: getType()
  {
   return type;
  }
  
  /**
   Name: getDirection
   Function: gets the value of direction
   @return an int for the vehicle's direction
  */
  
 char Cars :: getDirection()
  {
   return direction;
  }
