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
int stopCounter = 0;


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

	if (stopCounter == 0) {
		//draw 3x3 grid of values
		Sleep(500);
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				draw(stop[1][0], b, c, j);
			}
			if (j == 1) {
				draw(d, e, f, j);
			}
			if (j == 2) {
				draw(g, h, i, j);
			}
			//PLACE STOP ROTATE HERE IN EACH MOVEMENT, SAVING THE POSITIONS INTO THE stop[] ARRAY
		}
		//move each row down by 1 digit, giving the illusion of rotation
		Sleep(500);
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				draw(g, h, i, j);
			}
			if (j == 1) {
				draw(a, b, c, j);
			}
			if (j == 2) {
				draw(d, e, f, j);
			}
		}
		//move each row down again
		Sleep(500);
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				draw(d, e, g, j);
			}
			if (j == 1) {
				draw(g, h, i, j);
			}
			if (j == 2) {
				draw(a, b, c, j);
			}
		}
	}
	if (stopCounter == 1) {
		//draw 3x3 grid of values
		Sleep(500);
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
		Sleep(500);
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				draw(a, h, i, j);
			}
			if (j == 1) {
				draw(d, b, c, j);
			}
			if (j == 2) {
				draw(g, e, f, j);
			}
		}
		//move each row down again
		Sleep(500);
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				draw(a, e, f, j);
			}
			if (j == 1) {
				draw(d, h, i, j);
			}
			if (j == 2) {
				draw(g, b, c, j);
			}
		}
	}
	if (stopCounter == 2){
		//draw 3x3 grid of values
		Sleep(500);
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
		Sleep(500);
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				draw(a, b, i, j);
			}
			if (j == 1) {
				draw(d, e, c, j);
			}
			if (j == 2) {
				draw(g, h, f, j);
			}
		}
		//move each row down again
		Sleep(500);
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				draw(a, b, f, j);
			}
			if (j == 1) {
				draw(d, e, i, j);
			}
			if (j == 2) {
				draw(g, h, c, j);
			}
		}
	}
	if (stopCounter == 3) {
		//draw 3x3 grid of values
		Sleep(500);
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
	}
}

/*
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
	char* stop[3][3];
	bool game_running = true;

	char values[3][3];
	values[0][0] = 'a'; //a
	values[1][0] = 'a'; //b
	values[2][0] = 'a'; //c
	values[0][1] = 'b'; //d
	values[1][1] = 'b'; //e
	values[2][1] = 'b'; //f
	values[0][2] = 'c'; //g
	values[1][2] = 'c'; //h
	values[2][2] = 'c'; //i

	draw(values[0][0], values[1][0], values[2][0], 0);
	draw(values[0][1], values[1][1], values[2][1], 1);
	draw(values[0][2], values[1][2], values[2][2], 2);


	while (game_running == true) {
		rotate(values[0][0], values[1][0], values[2][0], values[0][1], values[1][1], values[2][1], values[0][2], values[1][2], values[2][2]);
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
