#include<bits/stdc++.h>
#include<conio.h> // in this library there is a function kbhit(keyboard hit) if this returns true
// means we have pressed a key
#include<windows.h>// allows interaction with windows api

using namespace std;

#define MAX_LENGTH 1000//defines maximum length a snake can grow

//Directions
const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';

int consoleWidth, consoleHeight;// score ka pta chlega

void initScreen()//screen initialise krega console width kya h console height kya h we know
{
    /*The term "handle" refers to a special type of identifier or reference that is used in the Windows
     operating system to manage resources. Handles are commonly used in Windows programming to represent
      and interact with various system objects like files, processes, threads, and windows.
    Here's a breakdown of the line:
    HANDLE: This is a data type defined in the Windows API. It is essentially a pointer to a system 
    object or resource. Handles are generic in the sense that they can represent different types of 
    objects, and their exact type is often context-dependent.   
    GetStdHandle(STD_OUTPUT_HANDLE): This function retrieves a handle to a standard device (like 
    standard input, standard output, or standard error). In this case, STD_OUTPUT_HANDLE specifies the
     standard output device, which is typically the console window where text is displayed. So, 
     GetStdHandle(STD_OUTPUT_HANDLE) returns a handle to the console's output buffer.
    hConsole: This is a variable of type HANDLE that will store the returned handle. 
    Once hConsole holds this handle, it can be used in other functions to perform operations on the 
    console window, such as changing its size, position, or writing to it.*/
    //In simpler terms, the line is obtaining a reference (handle) to the console's output buffer,
    // which can be later used to manipulate or interact with the console window.
    // windows library ke andr ek handle class predefined hoti h aur GetStdHandle krke ek method hota h
    //GetStdHandle(STD_OUTPUT_HANDLE): This function retrieves a handle to the standard output (console
    // window). The returned handle (hConsole) is stored in hConsole.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//console ki window ka control h
    CONSOLE_SCREEN_BUFFER_INFO csbi;//This line declares a structure of type CONSOLE_SCREEN_BUFFER_INFO
    // named csbi. This structure contains information about the console's screen buffer.
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    /*GetConsoleScreenBufferInfo: This function retrieves information about the console screen buffer.
hConsole: The handle to the console window that we obtained earlier.
&csbi: The address of the csbi structure where the retrieved information will be stored.*/
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    /*CONSOLE_SCREEN_BUFFER_INFO: This is a structure provided by the Windows API that contains 
    information about the console's screen buffer. It provides details about the current state of the 
    console, such as its size, cursor position, and more.
srWindow: Within the CONSOLE_SCREEN_BUFFER_INFO structure, srWindow is another structure member.
 It represents the region (or window) of the console screen buffer that is currently visible in the
  console window. In other words, it defines the area of the console's screen buffer that is currently 
  being displayed to the user in the console window.
srWindow.Top and srWindow.Bottom: These are members of the srWindow structure that represent the top 
and bottom row indices of the visible region/window in the screen buffer, respectively.*/
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

struct Point{
    int xCoord;
    int yCoord;
    Point(){
        //point represents a point on screen (x and y)
    }
    Point(int x, int y)
    {
        xCoord = x;
        yCoord = y;
    }
};


class Snake{//snake manages the snake movement, growth and direction
    int length;
    char direction;
public:
    Point body[MAX_LENGTH];
    Snake(int x, int y)
    {
       length = 1;
       body[0] = Point(x,y);
       direction = DIR_RIGHT;
    }

    int getLength(){
        return length;
    }

    void changeDirection(char newDirection){
        if(newDirection == DIR_UP && direction != DIR_DOWN)
        {
            direction = newDirection;
        }
        else if(newDirection == DIR_DOWN && direction != DIR_UP)
        {
            direction = newDirection;
        }
        else if(newDirection == DIR_LEFT && direction != DIR_RIGHT)
        {
            direction = newDirection;
        }
        else if(newDirection == DIR_RIGHT && direction != DIR_LEFT)
        {
            direction = newDirection;
        }
    }


    bool move(Point food){

        for(int i= length-1;i>0;i--)  // lenght = 4
        {
            body[i] = body[i-1];//body move kr rha h ek place aage aur last waala add ho jayega last me
        }

        switch(direction)
        {
            int val;
            //agr upr jaa rha toh sirf y coordinate change ho rha aur jitna upr jayega utna y cordinate
            // km hoga
            /*Retrieves the current yCoord of the snake's head.
            Decreases the yCoord by 1 to move the snake upwards.
            The break statement exits the switch block, preventing the code from executing the 
            other cases.*/
            case DIR_UP:
                val = body[0].yCoord;
                body[0].yCoord = val-1;
                break;
            case DIR_DOWN:
                val = body[0].yCoord;
                body[0].yCoord = val+1;
                break;
            case DIR_RIGHT:
                val = body[0].xCoord;
                body[0].xCoord = val+1;
                break;
            case DIR_LEFT:
                val = body[0].xCoord;
                body[0].xCoord = val-1;
                break;

        }

        //snake bites itself
        for(int i=1;i<length;i++)
        {
            if(body[0].xCoord == body[i].xCoord && body[0].yCoord == body[i].yCoord)
            {
                return false;
            }
        }

        //snake eats food
        if(food.xCoord == body[0].xCoord && food.yCoord == body[0].yCoord)
        /*This if statement checks if the coordinates of the food (food.xCoord and food.yCoord)
     match the coordinates of the snake's head (body[0].xCoord and body[0].yCoord). In other words,
      it checks if the snake's head is positioned on the same cell as the food.*/
        {
            body[length] = Point(body[length-1].xCoord, body[length-1].yCoord);
            //extending length by passing the parameters of point function
            /*body[length]: This accesses the Point structure at the length position of the snake's body.
             This position represents the tail of the snake.
                Point(body[length-1].xCoord, body[length-1].yCoord): This creates a new Point object 
                using the coordinates of the current last segment of the snake (body[length-1]).
                 Essentially, it's duplicating the last segment of the snake, preparing to extend its 
                 length.*/
            length++;
        }

        return true;

    }
};


class Board{//board manages the game board including the snake , food and game state
/*Snake *snake: A pointer to a Snake object, representing the snake on the board.
Point food: An object representing the position of the food on the board.
int score: An integer representing the current score of the game.*/
    Snake *snake;
    const char SNAKE_BODY = 'O';
    Point food;
    const char FOOD = 'o';
    int score;
public:
    Board(){
        spawnFood();//places a new food item randomly on the board
        /*Calls spawnFood() to place the initial food on the board.
Creates a new Snake object with initial coordinates.
Initializes the score to zero.*/
        snake = new Snake(10,10);
        score = 0;
    }

    ~Board(){//destructor coz dynamically create kiye h
        delete snake;
    }

    int getScore(){
        return score;
    }

    void spawnFood(){//Randomly places the food (Point object) on the game board.
        int x = rand() % consoleWidth;
        int y = rand() % consoleHeight;
        food = Point(x, y);
    }

    void displayCurrentScore(){//displaying score in the middle of the console
        gotoxy(consoleWidth/2,0);
        cout<<"Current Score : "<< score;
    }

    void gotoxy(int x, int y)
    {//Sets the console cursor position to the specified x and y coordinates using Windows 
    //API functions
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);//s a part of the Windows 
        //Console API and is used to set the position of the cursor within the console window.
    }

    void draw(){//clears the screen and redraws the snake again
        system("cls");
        for(int i=0;i<snake->getLength();i++)
        {
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout<<SNAKE_BODY;
        }

        gotoxy(food.xCoord, food.yCoord);
        cout<<FOOD;

        displayCurrentScore();
    }

    bool update(){//updates the game state by moving the snake and checking for collision
       bool isAlive = snake->move(food);//if it is alive snake moves and searches for more food
       if(isAlive == false)
       {
           return false;
       }

        if(food.xCoord == snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord)//checks if the
        //coordinate of the food matces the coordinate of the snakes body  if yes score is added and 
        //searches for more food
        {
            score++;
            spawnFood();
        }
       return true;
    }

    void getInput(){//captures users input to change snakes direction
        if(kbhit())
        {
            int key = getch();
            if(key == 'w' || key == 'W')
            {
                snake->changeDirection(DIR_UP);
            }
            else if(key == 'a' || key == 'A')
            {
                snake->changeDirection(DIR_LEFT);
            }
            else if(key == 's' || key == 'S')
            {
                snake->changeDirection(DIR_DOWN);
            }
            else if(key == 'd' || key == 'D')
            {
                snake->changeDirection(DIR_RIGHT);
            }
        }
    }

};
//The game's main loop runs until the snake collides with itself (update() returns false).
//The game loop captures user input, updates the game state, and redraws the board with a delay (Sleep(100)) to control the game's speed.
//End Game:Once the game ends, the final score is displayed.
int main(){
    srand(time(0));
    initScreen();
    Board *board = new Board();
    while(board->update())
    {
        board->getInput();
        board->draw();
        Sleep(100);
    }

    cout<<"Game over"<<endl;
    cout<<"Final score is :"<<board->getScore();
    return 0;
}