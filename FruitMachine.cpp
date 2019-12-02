#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h>  
#include <conio.h> 
#include <windows.h> 
#include <time.h> 
#include <string> 
#include <iostream>

using namespace std;

//GLOBAL VARIABLES
HANDLE hconsole;						// handle to console 
CONSOLE_SCREEN_BUFFER_INFO con_info;	// holds screen info 						
char input = 'A';
char tryAgain = 'A';
int stopCounter = 0;
char values[3][3];						//	fruit machine outputs
char storage[3][3];						// stores positions of fruitmachine outputs when rotating/swapping
int coins = 50;
int matchCounter = 0;
bool gameRunning = false;
bool programRunning = true;
void init_Graphics();
int wager = 0;

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

}

void Set_Color(int fcolor, int bcolor = 0)

{

	// this function sets the color of the console output 

	SetConsoleTextAttribute(hconsole, (WORD)((bcolor << 4) |

		fcolor));



}

void draw(char a, char b, char c, int y) {

	COORD cursor_pos;	//new coordinate variable
	cursor_pos.X = 5;	//setting x variable in coordinate position to 0, meaning the program writes only by starting on the left
	cursor_pos.Y = y;	//setting y variable in coordinate position to whatever line you want to print on
	
	//Display row
	SetConsoleCursorPosition(hconsole, cursor_pos);	//This function from one of the libraries tells the program where to write, using the cursor_pos X and Y values
	cout <<"   "<< a <<"   "<< b <<"   "<< c;

	//Display UI
	SetConsoleCursorPosition(hconsole, { 0,0 });
	cout << "<------------------------->\n" << endl;
	cout << "        F R U I T    " << endl;
	cout << "      M A C H I N E!  \n" << endl;
	cout << "<------------------------->\n" << endl;
	
	SetConsoleCursorPosition(hconsole, { 0,11 });
	cout << "<------------------------->";
	SetConsoleCursorPosition(hconsole, { 8,13 });
	cout << "Coins: " << coins;
	SetConsoleCursorPosition(hconsole, { 1,14 });
	cout << "Press X to stop spinning" << endl;
	cout << "\n<------------------------->";
}

void valueStorage() {

		//Store matrix for swapping of values
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
	valueStorage();
	for (int l = 0; l < 3; l++) {
		Sleep(100);
		for (int j = 7; j < 10; j++) {
			if (j == 7) {
				draw(values[0][0], values[1][0], values[2][0], j);
			}
			if (j == 8) {
				draw(values[0][1], values[1][1], values[2][1], j);
			}
			if (j == 9) {
				draw(values[0][2], values[1][2], values[2][2], j);
			}
		}

		//FULL ROTATION:
		if (stopCounter == 0) {
			//Column 1
			values[0][0] = storage[0][2];
			values[0][1] = storage[0][0];
			values[0][2] = storage[0][1];
			//Column 2
			values[1][0] = storage[1][2];
			values[1][1] = storage[1][0];
			values[1][2] = storage[1][1];
			//Column 3
			values[2][0] = storage[2][2];
			values[2][1] = storage[2][0];
			values[2][2] = storage[2][1];
		}

		//SECOND AND THIRD COLUMN ROTATION:
		if (stopCounter == 1) {
			//Column 2
			values[1][0] = storage[1][2];
			values[1][1] = storage[1][0];
			values[1][2] = storage[1][1];
			//Column 3
			values[2][0] = storage[2][2];
			values[2][1] = storage[2][0];
			values[2][2] = storage[2][1];
		}
		//EXCLUSIVLEY THIRD COLUMN ROTATION:
		if (stopCounter == 2) {
			//Column 3
			values[2][0] = storage[2][2];
			values[2][1] = storage[2][0];
			values[2][2] = storage[2][1];
		}
	}
}

void winCheck() {
	//Give the user 1 second to look over the machines output before clearing the screen to make way for the new output.
	Sleep(1000);
	system("cls");

	//Check if first row is equal to second row
	//If they are equal, increase matchCounter by one
	//Then check if second row is equal to third row
	//If they are equal, increase matchCounter by one
	//This is effective as only checks one row but as the rows below will match if the top row matches, only one check is required.
	//This also means if only the last two or first two rows match the counter only increase by one, but if all three match, the counter increases by two
	if (values[0][0] == values[1][0]) {
		matchCounter += 1;
	}
	if (values[1][0] == values[2][0]) {
		matchCounter += 1;
	}


	//If 0 rows match, no prize
	//If 2 rows match, small prize
	//If 3 rows match, jackpot prize
	if (matchCounter == 0) {
		coins -= wager*1.5;
		//Check for loss
		if (coins < 1) {
			system("cls");
			cout << "<------------------------->" << endl;
			cout << "\n       O U T   O F\n        C O I N S" << endl;
			cout << "\n         G A M E \n         O V E R\n" << endl;
			cout << "<------------------------->" << endl;
			Sleep(2500);
			gameRunning = false;
			programRunning = false;
			return;
		}
		Set_Color(4, 0);
		cout << "<------------------------->\n" << endl;
		cout << "        F R U I T    " << endl;
		cout << "      M A C H I N E!  \n" << endl;
		cout << "<------------------------->\n" << endl;
		cout << "NO MATCHES. You lose "<< wager*1.5<<" coins." << endl;
		Set_Color(15, 0);
		cout << "\nYou can try and win it back..." << endl;
	}
	if (matchCounter == 1) {
		coins += wager*1.5;
		cout << "<------------------------->\n" << endl;
		cout << "        F R U I T    " << endl;
		cout << "      M A C H I N E!  \n" << endl;
		cout << "<------------------------->\n" << endl;
		cout << "TWO MATCHES! You win "<< wager*1.5 << " coins. \n\nStill not quite a jackpot..." << endl;
	}
	if (matchCounter == 2) {
		coins += wager*2;
		//Jackpot changes display to green
		Set_Color(6, 0);
		cout << "<------------------------->\n" << endl;
		cout << "        F R U I T    " << endl;
		cout << "      M A C H I N E!  \n" << endl;
		cout << "<------------------------->\n" << endl;
		cout << "JACKPOT! YOU WIN " << wager*2 << " COINS!" << endl;
		Set_Color(15, 0);
		cout << "\nThere's still more money to be won..." << endl;
		
	}

	//Input Y to roll again, Press N to exit. 
	//This uses toupper and _getch for the same reasons as those in main()
	cout << "\nTry again? Y/N";
	tryAgain = toupper(_getch());
	if (tryAgain == 'Y') {
		gameRunning = true;
	}
	if (tryAgain == 'N') {
		system("cls");
		cout << "<------------------------->" << endl;
		cout << "\n        G A M E \n          O V E R\n" << endl;
		cout << "<------------------------->" << endl;
		cout << "\nYou end the game with " << coins << " coins.";
		Sleep(2500);
		gameRunning = false;
		programRunning = false;
		return;
		cout << "\n\n\n\n";
	}
	
	//Input validation
	while (tryAgain != 'Y' && tryAgain != 'N'){
		cout << "\nEnter 'Y' to try again \nor \nEnter 'N' to exit the game." << endl;
		tryAgain = toupper(_getch());
	}


}

int main() {

	init_Graphics();

	int y;
	cout << "<------------------------->\n" << endl;
	cout << "        F R U I T    " << endl;
	cout << "      M A C H I N E!  \n" << endl;
	cout << "<------------------------->\n" << endl;
	cout << "PRESS ANY BUTTON TO START." << endl;

	if (_getch()) {
		programRunning = true;
		gameRunning = true;
		system("cls");
	}
	
	cout << "<------------------------->\n" << endl;
	cout << "        F R U I T    " << endl;
	cout << "      M A C H I N E!  \n" << endl;
	cout << "<------------------------->\n" << endl;
	cout << "You start with 50 coins";
	Sleep(500);
	cout << ".";
	Sleep(500);
	cout << ".";
	Sleep(500);
	cout << "." << endl;
	Sleep(500);




	while (programRunning == true) {

		values[0][0] = 'a'; //a
		values[1][0] = 'a'; //b
		values[2][0] = 'a'; //c
		values[0][1] = 'b'; //d
		values[1][1] = 'b'; //e
		values[2][1] = 'b'; //f
		values[0][2] = 'c'; //g
		values[1][2] = 'c'; //h
		values[2][2] = 'c'; //i

		system("cls");
		stopCounter = 0;
		matchCounter = 0;
		wager = 0;

		cout << "<------------------------->\n" << endl;
		cout << "        F R U I T    " << endl;
		cout << "      M A C H I N E!  \n" << endl;
		cout << "<------------------------->\n" << endl;
		cout << "Enter your wager: ";
		cin >> wager;
		Sleep(500);
		system("cls");
		cout << "<------------------------->\n" << endl;
		cout << "   S T A R T I N G  I N    " << endl;
		cout << "       T H R E E...  \n" << endl;
		cout << "<------------------------->\n" << endl;
		Sleep(500);
		system("cls");
		cout << "<------------------------->\n" << endl;
		cout << "   S T A R T I N G  I N    " << endl;
		cout << "         T W O...  \n" << endl;
		cout << "<------------------------->\n" << endl;
		Sleep(500);
		system("cls");
		cout << "<------------------------->\n" << endl;
		cout << "   S T A R T I N G  I N    " << endl;
		cout << "         O N E...  \n" << endl;
		cout << "<------------------------->\n" << endl;
		Sleep(500);
		system("cls");

		gameRunning = true;
		while (gameRunning == true) {
			rotate();
			//kbhit asks for input and then continues regardless of input, but due to this if loop program only continues if a key is hit.
			if (_kbhit()) {
				//getch pauses console until a character is entered,
				//toupper then changes the character to its upper case equivalent.
				input = toupper(_getch());
				//When the user inputs X, the counter that tracks the number of stops increases by 1.
				if (input == 'X') {
					stopCounter += 1;
				}
				if (stopCounter > 2) {
					gameRunning = false;
				}
			}
		}
		winCheck();
	}
	return 0;
}

/*
IDEAS FOR IMPROVING :
Change it to 7 rows or at the very least >3

Constrain the window size to set dimensions! Always display title at the top and coins at the bottom of this window!
*/
