#include <iostream>
#include <conio.h>
#include <sstream>
using namespace std;

void print();
void placeMove();
void block();
void checkWin(string cpuOrPlayer);
void AI();
void moveMSG();
void startMSG();
void aiMoveMSG();
void notValidMSG();
void playerWinMSG();
void checkWinCol(int col, string cpuOrPlayer);
void checkWinRow(int row, string cpuOrPlayer);
void checkWinDia(string cpuOrPlayer);
void checkWinOtherDia(string cpuOrPlayer);
void cpuWinMSG();
void checkCanWin();
void draw();
void drawMSG();
void validInput();
void validInputMSG();
class Validator;
class ai;

string guess = "0";
string board[3][3] = { { "1", "2", "3" }, { "4", "5", "6" }, { "7", "8", "9" } };
int weightedArray[3][3] = { { 1, 2, 1 }, { 2, 3, 2 }, { 1, 2, 1 } };
int weightedBoardFirst[3][3] = { { 4, 1, 3 }, { 1, 2, 1 }, { 3, 1, 4 } };
bool game = true;
bool tryAgain = false;

int bestRow;
int bestCol;
int blockRow = 0;
int blockCol = 0;
string blockYesOrNo = "no";
string cpuXOrO;
string playerXOrO;
string firstOrSecond;

//validates inputs
class Validator
{
public:
	bool inputMechanism(string* inputString, int low, int high)
	{
		
		char tempKey = ' ';
		const static int maxLineLength = 0;
		bool empty = false;

		do{
			tempKey = _getch();
			if ((tempKey >= low && tempKey <= high))//ascii range 32 to 126
			{
				//when valid char pressed, accept and print to screen
				if (maxLineLength >= (*inputString).length())
				{
					(*inputString) += tempKey;
					printf("%c", tempKey);
					empty = true;
				}
			}//end if
			else if (tempKey == 8)//ascii backspace
			{
				//if back pressed, pop char off string, and erase from screen
				if ((*inputString).length() > 0)
				{
					(*inputString).erase((*inputString).length() - 1, 1);
					printf("\b \b");
				}
			} //end else if
			else if (tempKey == -32)//drop off any arrow key pressed
			{
				_getch();
			}// end else if

		} while (tempKey != 13 || empty == false);

		printf("\n");
		return true;
	}//end method inputMechanism
};//end class

//contains all the interface methods
class interface
{
public:

	Validator val;
	//display invalid input message
	void validInputMSG(){

		cout << "Invalid input please enter a valid input" << endl;

	}

	//shows the starting message and takes input for who goes first
	void startMSG(){
		cout << "Enter 1 to have first move or 2 for the computer to go first: ";
		string tempFirstOrSecond;
		if (val.inputMechanism(&tempFirstOrSecond, 49, 50) == true){
			firstOrSecond = tempFirstOrSecond;
		}

	}

	//prints the game board
	void print(){

		for (int row = 0; row < 3; row++){
			for (int col = 0; col < 3; col++){
				cout << "[" << board[row][col] << "]";
			}
			cout << endl;
		}
	}

	//asks the user for input to make a move
	void moveMSG(){
		cout << "Choose a number: ";
		string tempGuess;
		if (val.inputMechanism(&tempGuess, 49, 57) == true){
			guess = tempGuess;
		}
	}

	//displays message that the cpu has made a move
	void aiMoveMSG(){
		cout << "The computers move" << endl;
	}

	//if player move not valid gives message and asks for new input
	void notValidMSG(){
		cout << "Not a valid move please try again" << endl;
		cin >> guess;
	}

	//displays message saying the player won
	void playerWinMSG(){
		cout << endl << "Congratulations you win!" << endl;
	}

	//displays message saying the cpu won
	void cpuWinMSG(){
		cout << endl << "The computer has won!" << endl;
	}

	//displays message if there is a draw
	void drawMSG(){
		cout << "It is a draw" << endl;
	}

};

//contains all the ai's logic and makes its moves
class ai
{
public:
	void AI(){

		if (firstOrSecond == "1"){
			cpuXOrO = "O";

			
			if (blockYesOrNo == "yes"){

				board[blockRow][blockCol] = "O";
				weightedArray[blockRow][blockCol] = 0;
				blockYesOrNo = "no";
				return;
			}

			int highestNum = 0;

			if (board[1][1] == "X"){

				for (int row = 0; row < 3; row++){
					for (int col = 0; col < 3; col++){
						if (weightedArray[row][col] == 1){
							weightedArray[row][col] = 3;
						}
					}
				}

			}

			for (int row = 0; row < 3; row++){
				for (int col = 0; col < 3; col++){

					if (board[0][1] == playerXOrO && board[1][0] == playerXOrO && board[0][0] != cpuXOrO){
						bestRow = 0;
						bestCol = 0;
						weightedArray[bestRow][bestCol] = 0;
						board[bestRow][bestCol] = cpuXOrO;
						return;
					}

					if (board[0][1] == playerXOrO && board[1][2] == playerXOrO && board[0][2] != cpuXOrO){
						bestRow = 0;
						bestCol = 2;
						weightedArray[bestRow][bestCol] = 0;
						board[bestRow][bestCol] = cpuXOrO;
						return;
					}

					if (board[1][0] == playerXOrO && board[2][1] == playerXOrO && board[2][0] != cpuXOrO){
						bestRow = 2;
						bestCol = 0;
						weightedArray[bestRow][bestCol] = 0;
						board[bestRow][bestCol] = cpuXOrO;
						return;
					}

					if (board[2][1] == playerXOrO && board[1][2] == playerXOrO && board[2][2] != cpuXOrO){
						bestRow = 2;
						bestCol = 2;
						weightedArray[bestRow][bestCol] = 0;
						board[bestRow][bestCol] = cpuXOrO;
						return;
					}

					if (highestNum < weightedArray[row][col]){
						highestNum = weightedArray[row][col];
						bestRow = row;
						bestCol = col;

					}
				}


			}
			weightedArray[bestRow][bestCol] = 0;
			board[bestRow][bestCol] = cpuXOrO;



		}

		if (firstOrSecond == "2"){
			cpuXOrO = "X";

			if (blockYesOrNo == "yes"){

				board[blockRow][blockCol] = "X";
				weightedBoardFirst[blockRow][blockCol];
				blockYesOrNo = "no";
				return;
			}

			int highestNum = 0;

			for (int row = 0; row < 3; row++){
				for (int col = 0; col < 3; col++){
					if (highestNum < weightedBoardFirst[row][col]){
						highestNum = weightedBoardFirst[row][col];
						bestRow = row;
						bestCol = col;

					}
				}
			}
			weightedBoardFirst[bestRow][bestCol] = 0;
			board[bestRow][bestCol] = cpuXOrO;

		}
	}

};

//checks in the input is valid
void validInput(){

	Validator validator;
	string tempFirstOrSecond = firstOrSecond;
	
	if (validator.inputMechanism(&tempFirstOrSecond, 49, 57) == false){
		return;

	}

	
	
	
}

//calls on all the funtions and methods
int main(){

	ai AiMove;
	interface inter;
	inter.startMSG();
	

	while (game = true){
			
		if (firstOrSecond == "1"){//player goes first

			inter.print();
			checkWin(playerXOrO);
			if (game == false){
				break;
			}
			inter.moveMSG();
		
			placeMove();
			inter.print();
			draw();
			if (game == false){
				inter.print();
				break;
			}

			checkWin(playerXOrO);
			if (game == false){
				break;
			}
			checkCanWin();
			if (game == false){
				inter.print();
				break;
			}
			block();
			AiMove.AI();
			inter.aiMoveMSG();
			checkWin(cpuXOrO);

			if (game == false){
				break;
			}
			
		}

		if (firstOrSecond == "2"){

			checkCanWin();
			if (game == false){
				inter.print();
				break;
			}
			block();
			AiMove.AI();
			inter.aiMoveMSG();
			draw();
			if (game == false){
				inter.print();
				break;
			}
			checkWin(cpuXOrO);
			if (game == false){
				inter.print();
				break;
			}
			inter.print();
			inter.moveMSG();
			placeMove();
			inter.print();
			checkWin(playerXOrO);
			if (game == false){
				break;
			}
		}
	}
	_getch();
	return 0;
}


//takes the users input and places there input on the board
void placeMove(){

	interface inter;

	if (firstOrSecond == "1"){
		playerXOrO = "X";
	}
	if (firstOrSecond == "2"){
		playerXOrO = "O";
	}

	bool valid = true;

	while (valid = true) {
		for (int row = 0; row < 3; row++){

			for (int col = 0; col < 3; col++){

				if (guess == board[row][col]){

					board[row][col] = playerXOrO;
					if (firstOrSecond == "1"){
						weightedArray[row][col] = 0;
					}
					if (firstOrSecond == "2"){
						weightedBoardFirst[row][col] = 0;
					}

					return;

				}

			}
			
		}
		//inter.notValidMSG();
	}
}

//runs through a column to check for 2 or 3 in a row
void checkCol(int colNum, string blockOrWin, string playerOrCpu){

	interface inter;

	int inARow = 0;
	int row = 0;
	int col = colNum;

		for (row = 0; row < 3; row++){


			if (board[row][col] == playerOrCpu){
				inARow++;

			}

			if (inARow == 2){
				if (blockOrWin == "block"){
					for (int row = 0; row < 3; row++){
						if (board[row][col] != "X" && board[row][col] != "O"){
							blockRow = row;
							blockCol = col;
							blockYesOrNo = "yes";
							break;
						}
					}

				}
				if (blockOrWin == "win"){

					for (int row = 0; row < 3; row++){
						if (board[row][col] != "X" && board[row][col] != "O"){
							board[row][col] = cpuXOrO;
							inter.cpuWinMSG();
							game = false;

						}

					}

				}
			}
			}
} // works 

//runs through a row to check for 2 or 3 in a row
void checkRow(int rowNum, string blockOrWin, string playerOrCpu){

	interface inter;

	int col = 0;
	int row = rowNum;
	int twoRow = 0;

	for (col = 0; col < 3; col++){

		if (board[row][col] == playerOrCpu){
			twoRow += 1;
		}

		if (twoRow == 2){
			if (blockOrWin == "block"){
				for (int col = 0; col < 3; col++){
					if (board[row][col] != "X" && board[row][col] != "O"){
						blockRow = row;
						blockCol = col;
						blockYesOrNo = "yes";
						break;
					}
				}

			}
			if (blockOrWin == "win"){

				for (int col = 0; col < 3; col++){
					if (board[row][col] != "X" && board[row][col] != "O"){
						board[row][col] = cpuXOrO;
						inter.cpuWinMSG();
						game = false;

					}

				}

			}

			}
		}
		
	}

//runs through a diagonal to check for 2 or 3 in a row
void checkDia(string blockOrWin, string playerOrCpu){

	interface inter;

	int row = 0;
	int col = 0;
	int twoRow = 0;
	int tempCol = 0;

	for (row = 0; row < 3; row++){
		

		if (board[row][col] == playerOrCpu){
			twoRow += 1;
		}

		if (twoRow == 2){
			col = 0;
			for (row = 0; row < 3; row++){
				if (blockOrWin == "block"){
					if (board[row][tempCol] != "X" && board[row][tempCol] != "O"){
									blockRow = row;
									blockCol = tempCol;
									blockYesOrNo = "yes";
									break;
								}

								tempCol++;
							}


				}
					
			

			if (blockOrWin == "win"){

				for (row = 0; row < 3; row++){

					if (board[row][tempCol] != "X" && board[row][tempCol] != "O"){
						board[row][tempCol] = cpuXOrO;
						inter.cpuWinMSG();
						game = false;

					}

					tempCol++;
				}


			}

		}

		col++;
	}

}

//runs through a diagonal to check for 2 or 3 in a row
void checkOtherDia(string blockOrWin, string playerOrCpu){

	interface inter;

	int row = 0;
	int col = 2;
	int twoRow = 0;
	int tempCol = 2;

	for (row = 0; row < 3; row++){


		if (board[row][col] == playerOrCpu){
			twoRow += 1;
		}

		if (twoRow == 2){
			col = 2;
			if (blockOrWin == "block"){
				for (row = 0; row < 3; row++){


					if (board[row][tempCol] != "X" && board[row][tempCol] != "O"){
						blockRow = row;
						blockCol = tempCol;
						blockYesOrNo = "yes";
						break;
					}

					tempCol--;
				}

			}
			if (blockOrWin == "win"){

				for (row = 0; row < 3; row++){

					if (board[row][tempCol] != "X" && board[row][tempCol] != "O"){
						board[row][tempCol] = cpuXOrO;
						inter.cpuWinMSG();
						game = false;

					}

					tempCol--;
				}


			}
		
		}

		col--;
	}

}

//runs through the array to see if the ai should block
void block(){

	int row = 0;
	int col = 0;

	checkCol(0, "block", playerXOrO);
	checkCol(1, "block", playerXOrO);
	checkCol(2, "block", playerXOrO);

	checkRow(0, "block", playerXOrO);
	checkRow(1, "block", playerXOrO);
	checkRow(2, "block", playerXOrO);

	checkDia("block", playerXOrO);
	checkOtherDia("block", playerXOrO);

}

//runs though the array to check if the player or cpu has won
void checkWin(string cpuOrPlayer){
	checkWinCol(0, cpuOrPlayer);
	checkWinCol(1, cpuOrPlayer);
	checkWinCol(2, cpuOrPlayer);

	checkWinRow(0, cpuOrPlayer);
	checkWinRow(1, cpuOrPlayer);
	checkWinRow(2, cpuOrPlayer);

	checkWinDia(cpuOrPlayer);
	checkWinOtherDia(cpuOrPlayer);
	
}

//checks column for 3 in a row
void checkWinCol(int col, string cpuOrPlayer){
	
	interface inter;

	int row = 0;
	int threeRow = 0;

	for (row = 0; row < 3; row++){

		if (board[row][col] == cpuOrPlayer){
			threeRow++;

		}

		if (threeRow == 3){
			if (cpuOrPlayer == playerXOrO){
				inter.playerWinMSG();
				game = false;
				}
			if (cpuOrPlayer == cpuXOrO){
				inter.cpuWinMSG();
				game = false;
				}
			}
		}

	}

//checks row for 3 in a row
void checkWinRow(int row, string cpuOrPlayer){

	interface inter;

	int col = 0;
	int threeRow = 0;

	for (col = 0; col < 3; col++){

		if (board[row][col] == cpuOrPlayer){
			threeRow++;

		}

		if (threeRow == 3){
			if (cpuOrPlayer == playerXOrO){
				inter.playerWinMSG();
				game = false;
			}
			if (cpuOrPlayer == cpuXOrO){
				inter.cpuWinMSG();
				game = false;
			}
		}
	}

}

//checks diagonal for 3 in a row
void checkWinOtherDia(string cpuOrPlayer){

	interface inter;

	int row = 0;
	int col = 2;
	int threeRow = 0;


	for (row = 0; row < 3; row++){


		if (board[row][col] == cpuOrPlayer){
			threeRow += 1;
		}

		if (threeRow == 3){
			if (cpuOrPlayer == playerXOrO){
				inter.playerWinMSG();
				game = false;
			}
			if (cpuOrPlayer == cpuXOrO){
				inter.cpuWinMSG();
				game = false;
			}
		}
		col--;
	}
}

//checks diagonal for 3 in a row
void checkWinDia(string cpuOrPlayer){

	interface inter;

	int row = 0;
	int col = 0;
	int threeRow = 0;


	for (row = 0; row < 3; row++){


		if (board[row][col] == cpuOrPlayer){
			threeRow += 1;
		}

		if (threeRow == 3){
			if (cpuOrPlayer == playerXOrO){
				inter.playerWinMSG();
				game = false;
			}
			if (cpuOrPlayer == cpuXOrO){
				inter.cpuWinMSG();
				game = false;
			}
		}
		col++;
	}
}

//runs though the array to see if the cpu can win
void checkCanWin(){

	checkCol(0, "win", cpuXOrO);
	checkCol(1, "win", cpuXOrO);
	checkCol(2, "win", cpuXOrO);
	
	checkRow(0, "win", cpuXOrO);
	checkRow(1, "win", cpuXOrO);
	checkRow(2, "win", cpuXOrO);

	checkDia("win", cpuXOrO);
	checkOtherDia("win", cpuXOrO);
}

//checks if the player and cpu have come to a draw
void draw(){

	interface inter;

	int count = 0;

	for (int row = 0; row < 3; row++){
		for (int col = 0; col < 3; col++){
			if (board[row][col] == "X" || board[row][col] == "O"){
				count++;
			}
		}
	}

	if (count == 9){
		inter.drawMSG();
		game = false;
	}

}

//makes sure inputs are valid


