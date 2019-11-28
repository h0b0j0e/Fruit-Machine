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
char stop[3][3];						// stores positions of fruitmachine outputs
char input = 'A';

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

void rotate(char a, char b, char c, char d, char e, char f, char g, char h, char i) {
	//draw 3x3 grid of values
	Sleep(250);
	for (int j = 0; j < 3; j++) {
		if (j == 0) {
			draw(a, b, c, j);
		}
		if (j == 1) {
			draw(d, e, f, j);
		}
		if (j == 2) {
			draw(g, h, i, j);
		}
	}
	//move each row down by 1 digit, giving the illusion of rotation
	Sleep(250);
	for (int j = 0; j < 3; j++) {
		if (j == 0) {
			draw(f, g, h, j);
		}
		if (j == 1) {
			draw(a, b, c, j);
		}
		if (j == 2) {
			draw(d, e, g, j);
		}
	}
	//move each row down again
	Sleep(250);
	for (int j = 0; j < 3; j++) {
		if (j == 0) {
			draw(d, e, g, j);
		}
		if (j == 1) {
			draw(f, g, h, j);
		}
		if (j == 2) {
			draw(a, b, c, j);
		}
	}
}

void stopRotate(char a, char b, char c, char d, char e, char f, char g, char h, char i, int stopCounter) {

	//If S has been pressed once, print out 3x3 grid of values, save the values in the first column to an array
	while (stopCounter == 1) {
		draw(a, b, c, 0);
		draw(d, e, f, 1);
		draw(g, h, i, 2);

		stop[0][0] = a;
		stop[1][0] = d;
		stop[2][0] = g;
		Sleep(250);
	}
	//If S has been pressed twice, print out 3x3 grid of values, replacing the first column with the values stored from the first time S was pressed.
	//This is to give the illusion that that column has "stopped spinning"
	//Then save the values in the second collumn to an array
	while (stopCounter == 2) {
		draw(stop[0][0], b, c, 0);
		draw(stop[1][0], e, f, 1);
		draw(stop[2][0], h, i, 2);

		stop[0][1] = b;
		stop[1][1] = e;
		stop[2][1] = h;
		Sleep(250);
	}
	while (stopCounter == 3) {
		draw(stop[0][0], stop[0][1], c, 0);
		draw(stop[1][0], stop[1][1], f, 1);
		draw(stop[2][0], stop[2][1], i, 2);
	}

}

int main() {

	init_Graphics();

	int y;
	char* stop[3][3];
	int stopCounter = 0;
	bool game_running = true;

	char values[3][3];
	values[0][0] = '1'; //a
	values[1][0] = '2'; //b
	values[2][0] = '3'; //c
	values[0][1] = '4'; //d
	values[1][1] = '5'; //e
	values[2][1] = '6'; //f
	values[0][2] = '7'; //g
	values[1][2] = '8'; //h
	values[2][2] = '9'; //i

	draw(values[0][0], values[1][0], values[2][0], 0);
	draw(values[0][1], values[1][1], values[2][1], 1);
	draw(values[0][2], values[1][2], values[2][2], 2);


	while (game_running == true) {
		cout << input;
		//kbhit asks for input and then continues regardless of input, but due to this if loop program only continues if a key is hit.
		if (_kbhit()){
			//getch pauses console until a character is entered,
			//toupper then changes the character to its upper case equivalent.
			input = toupper(_getch());

			//If the user inputs S, the rotate function runs (until the user inputs X, which will cause it to move to the next while loop.)
			while (input == 'S'){
				rotate(values[0][0], values[1][0], values[2][0], values[0][1], values[1][1], values[2][1], values[0][2], values[1][2], values[2][2]);
			}
			//When the user inputs X, the counter that tracks the number of stops increases by 1 and the stopRotate function runs.
			//after stopRotate completes, input is then set to S to run the rotate function, beginning rotation once more.
			while (input == 'X'){
				system("cls");
				cout << "\n\n		FUCK!\n\n";
				stopCounter += 1;
				Sleep(2500);
				input = 'S';
				/*
				stopRotate(values[0][0], values[1][0], values[2][0], values[0][1], values[1][1], values[2][1], values[0][2], values[1][2], values[2][2], stopCounter);
				*/
			} 
			return 0;
		}
	}
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


//so the program seems to run the rotate function perfectly fine,
//it doesnt take in any new inputs(TEST IF THIS IS TRUE AS IT MAY JUST NOT EXIT THE ROTATE FUNCTION/RUN THE STOPROTATE FUNCTION)(FUCK! IS TESTING THIS)
//basically: stopRotate either doesn't run or doesn't work.
//it might not run because rotate doesn't end?
//it might not run because input isn't taken?
//it might not run because it doesn't succesfully draw/freeze the columns in place.
