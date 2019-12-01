#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h>  
#include <conio.h> 
#include <windows.h> 
#include <time.h> 
#include <string> 
#include <iostream>

using namespace std;

//Global Variables!
HANDLE hconsole;						// handle to console 
CONSOLE_SCREEN_BUFFER_INFO con_info;	// holds screen info 						
char input = 'A';
int stopCounter = 0;
char values[3][3];						//	fruit machine outputs
char storage[3][3];						// stores positions of fruitmachine outputs when rotating/swapping



void init_Graphics()
{
	// this function initializes the console graphics engine 


	COORD console_size = { 110, 30 }; // size of console 


	srand((unsigned)time(NULL));// seed the random number generator with time 


	// open i/o channel to console screen 
	hconsole = CreateFile(TEXT("CONOUT$"), GENERIC_WRITE | GENERIC_READ,

		FILE_SHARE_READ | FILE_SHARE_WRITE,

		0L, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0L);


	// make sure we are in 80x25 

	SetConsoleScreenBufferSize(hconsole, console_size);

	// get details for console screen                        

	GetConsoleScreenBufferInfo(hconsole, &con_info);

} // end init_Graphics 

void draw(char a, char b, char c, int y) {

	COORD cursor_pos;	//new coordinate variable
	cursor_pos.X = 0;	//setting x variable in coordinate position to 0, meaning the program writes only by starting on the left
	cursor_pos.Y = y;	//setting y variable in coordinate position to whatever line you want to print on
	SetConsoleCursorPosition(hconsole, cursor_pos);	//This function from one of the libraries tells the program where to write, using the cursor_pos X and Y values

	cout << '\r' <<"   "<< a <<"   "<< b <<"   "<< c;

	SetConsoleCursorPosition(hconsole, { 0,6 });
	cout << "Enter S to spin, Enter X to stop spinning" ;
}

void valueStorage() {

		storage[0][0] = values[0][0];
		storage[0][1] = values[0][1];
		storage[0][2] = values[0][2];
		storage[1][0] = values[1][0];
		storage[1][1] = values[1][1];
		storage[1][2] = values[1][2];
		storage[2][0] = values[2][0];
		storage[2][1] = values[2][1];
		storage[2][2] = values[2][2];

}


void rotate() {
	if (stopCounter == 0) {
		cout << stopCounter;
		Sleep(500);
		valueStorage();

		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				cout << "\n" << values[0][0] << values[1][0] << values[2][0] << j;
				draw(values[0][0], values[1][0], values[2][0], j);
				Sleep(500);
			}
			if (j == 1) {
				cout << "\n\n" << values[0][1] << values[1][1] << values[2][1] << j;
				draw(values[0][1], values[1][1], values[2][1], j);
				Sleep(500);
			}
			if (j == 2) {
				cout << "\n\n\n" << values[0][2] << values[1][2] << values[2][2] << j;
				draw(values[0][2], values[1][2], values[2][2], j);
				Sleep(500);
			}
		}
			/*
			ROTATION STEP ONE:
			values[0][0] = storage[0][2];
			values[0][1] = storage[0][0];
			values[0][2] = storage[0][1];

			ROTATION STEP TWO
			values[0][0] = storage[0][1];
			values[0][1] = storage[0][2];
			values[0][2] = storage[0][0];

			ROTATION STEP THREE:
			values[0][0] = storage[0][0];
			values[0][1] = storage[0][1];
			values[0][2] = storage[0][2];
			*/
	}
}
/*
	//draw 3x3 grid of values
	for (int j = 0; j < 3; j++) {
		if (j == 0) {
			draw(values[0][0], values[1][0], values[2][0], j);
		}
		if (j == 1) {
			draw(values[0][1], values[1][1], values[2][1], j);
		}
		if (j == 2) {
			draw(values[0][2], values[1][2], values[2][2], j);
		}
	}
	//move each row down by 1 digit, giving the illusion of rotation
	Sleep(500);
}
*/

/*
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				draw(values[0][0], values[1][0], values[2][0], j);
			}
			if (j == 1) {
				draw(values[0][1], values[1][1], values[2][1], j);
			}
			if (j == 2) {
				draw(values[0][2], values[1][2], values[2][2], j);
			}












		}
		//move each row down again
		Sleep(500);
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				draw(values[0][1], values[1][1], values[2][1], j);
			}
			if (j == 1) {
				draw(values[0][2], values[1][2], values[2][2], j);
			}
			if (j == 2) {
				draw(values[0][0], values[1][0], values[2][0], j);
			}
		}
	}
	if (stopCounter == 1) {
		//draw 3x3 grid of values
		Sleep(500);
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				draw(values[0][0], values[1][0], values[2][0], j);
			}
			if (j == 1) {
				draw(values[0][1], values[1][1], values[2][1], j);
			}
			if (j == 2) {
				draw(values[0][2], values[1][2], values[2][2], j);
			}
		}
		//move each row down by 1 digit, giving the illusion of rotation
		Sleep(500);
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				draw(values[0][0], values[1][2], values[2][2], j);
			}
			if (j == 1) {
				draw(values[0][1], values[1][0], values[2][0], j);
			}
			if (j == 2) {
				draw(values[0][2], values[1][1], values[2][1], j);
			}
		}
		//move each row down again
		Sleep(500);
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				draw(values[0][0], values[1][1], values[2][1], j);
			}
			if (j == 1) {
				draw(values[0][1], values[1][2], values[2][2], j);
			}
			if (j == 2) {
				draw(values[0][2], values[1][0], values[2][0], j);
			}
		}
	}
	if (stopCounter == 2){
		//draw 3x3 grid of values
		Sleep(500);
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				draw(values[0][0], values[1][0], values[2][0], j);
			}
			if (j == 1) {
				draw(values[0][1], values[1][1], values[2][1], j);
			}
			if (j == 2) {
				draw(values[0][2], values[1][2], values[2][2], j);
			}
		}
		//move each row down by 1 digit, giving the illusion of rotation
		Sleep(500);
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				draw(values[0][0], values[1][0], values[2][2], j);
			}
			if (j == 1) {
				draw(values[0][1], values[1][1], values[2][0], j);
			}
			if (j == 2) {
				draw(values[0][2], values[1][2], values[2][1], j);
			}
		}
		//move each row down again
		Sleep(500);
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				draw(values[0][0], values[1][0], values[2][1], j);
			}
			if (j == 1) {
				draw(values[0][1], values[1][1], values[2][2], j);
			}
			if (j == 2) {
				draw(values[0][2], values[1][2], values[2][0], j);
			}
		}
	}
	if (stopCounter == 3) {
		//draw 3x3 grid of values
		Sleep(500);
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				draw(values[0][0], values[1][0], values[2][0], j);
			}
			if (j == 1) {
				draw(values[0][1], values[1][1], values[2][1], j);
			}
			if (j == 2) {
				draw(values[0][2], values[1][2], values[2][2], j);
			}
		}
	}
}

char savePositions(char a, char b, char c, char d, char e, char f, char g, char h, char i, int stopCounter) {
	
	if (stopCounter == 1){

		stop[0][0] = a;
		stop[1][0] = d;
		stop[2][0] = g;
	}

		stop[0][1] = b;
		stop[1][1] = e;
		stop[2][1] = h;
	
	return a, b, c, d, e, f, g, h, i;
}
*/


int main() {

	init_Graphics();

	int y;
	bool game_running = true;

	values[0][0] = 'a'; //a
	values[1][0] = 'a'; //b
	values[2][0] = 'a'; //c
	values[0][1] = 'b'; //d
	values[1][1] = 'b'; //e
	values[2][1] = 'b'; //f
	values[0][2] = 'c'; //g
	values[1][2] = 'c'; //h
	values[2][2] = 'c'; //i


	while (game_running == true) {
		rotate();
		//kbhit asks for input and then continues regardless of input, but due to this if loop program only continues if a key is hit.
		if (_kbhit()){
			//getch pauses console until a character is entered,
			//toupper then changes the character to its upper case equivalent.
			input = toupper(_getch());

			//If the user inputs S, the rotate function runs (until the user inputs X, which will cause it to move to the next while loop.)
			if (input == 'S'){
				cout << "\n" << input;
			}
			//When the user inputs X, the counter that tracks the number of stops increases by 1 and the stopRotate function runs.
			//after stopRotate completes, input is then set to S to run the rotate function, beginning rotation once more.
			while (input == 'X'){
				cout << "\n" << input;
				stopCounter += 1;
				input = 'S';
				/*
				savePositions(values[0][0], values[1][0], values[2][0], values[0][1], values[1][1], values[2][1], values[0][2], values[1][2], values[2][2], stopCounter);
				*/
			} 
		}
	}

	return 0;
}

/*
IDEAS FOR IMPROVING :
Random characters also flash random colours
Enter how much money youre entering at the start, keep track of money as you play,
Kicking you out when you run out of money
Allow for multiple fruit machine games to be played
*/
/*
int RNG() {
	//Random Number Generator
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int e = 0;
	int f = 0;
	int g = 0;
	int h = 0;
	int i = 0;


	srand(time(NULL));
	a, b, c, d, e, f, g, h, i = rand() % 10 + 1;

	return a, b, c, d, e, f, g, h, i;
}
*/
/*
USER INTERFACE:
Display 3 columns of random characters on the console
*/
/*
USER INPUT/USER INTERFACE: 
The user hits play, the characters in each column should rotate rapidly
and then can choose when to stop the first column from rotating, then the second column and finally stop the third column
*/
/*
WIN DETECTION:
IF the symbols in all three match, display a message indicating that the user has hit the jackpot, 
ELSE IF the symbols in only two columns are the same provide a smaller prize.
ELSE IF no symbols match, provide no prize.
*/
/*
WHILE THE USER HAS NOT INPUTTED ANYTHING, ROTATE
temporary variable equal to first element in the array
for loop
set value at i equal to i+1
set i+1 equal to temp variable
Win check
(based on week 6 lecture tic tac toe, win check code cannot be copied directly.)
horizontal match check is minimum requirement
*/




//possibly change stopCounter to three seperate boolean values.


//ok now the things stop rotating but they always stop in the default position.
//make stopRotate save the current positions and pass them back into rotate.
//maybe make each move in rotation save a value.


//rotate function takes 1 integer as appose to all characters (int is between 0-2)
//directly swap elements in collumn array as appose to positions of those chararcters on screen
//temporary variable to store the value that the element is being swapped to.
//[1][0] swapping to [1][1] you would save what is in [1][1] and then store that in [1][2],
//saving whatever was in [1][2] and moving that to [1][0]


//values[0][0], values[1][0], values[2][0], values[0][1], values[1][1], values[2][1], values[0][2], values[1][2], values[2][2]
