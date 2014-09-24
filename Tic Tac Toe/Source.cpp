#include <iostream>
#include <conio.h>
#include <sstream>
using namespace std;

void print();
void placeMove();
void block();
void checkWin();
void AI();


string guess = "0";
string board[3][3] = { { "1", "2", "3" }, { "4", "5", "6" }, { "7", "8", "9" } };
int weightedArray[3][3] = { { 1, 2, 1 }, { 2, 3, 2 }, { 1, 2, 1 } };
bool game = true;
int twoRow = 0;
int bestRow;
int bestCol;
int blockRow = 0;
int blockCol = 0;
string blockYesOrNo = "no";


int main(){


	while (game = true){

		print();
		placeMove();
		
		checkWin();
		block();
		AI();
	}



	_getch();

	

	return 0;

}

void print(){

	for (int row = 0; row < 3; row++){

		for (int col = 0; col < 3; col++){

			cout << board[row][col] << " ";

		}

		cout << endl;

	}

	cout << "Choose a number ";
	cin >> guess;

	

}

void placeMove(){

	for (int row = 0; row < 3; row++){

		for (int col = 0; col < 3; col++){

			if (guess == board[row][col]){

				board[row][col] = "X";
				weightedArray[row][col] = 0;

			}

		}		

	}

}

//class firstPlayer
//{
//public:
//
//	int pOne[3][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
//
//
//};
//
//class secondPlayer
//{
//public:
//
//	int pTwo[3][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
//
//
//};
//
void block(){

	int row = 0;
	int col = 0;

	string xOrO = "X";

	for (row = 0; row < 3; row++){
		for (col = 0; col < 3; col++){
			
			if (board[row][col] == xOrO){
				twoRow += 1;
			}

			if (twoRow == 2){

				for (int row = 0; row < 3; row++){
					if (board[row][col] != "X" && board[row][col] != "O"){
						blockRow = row;
						blockCol = col;
					}
				}
				blockYesOrNo = "yes";
				break;
			}

			if (col == 2)
				twoRow = 0;
		}
	}
	//twoRow = 0;
	//row = 0;
	//col = 0;
	//for (col = 0; col < 3; col++){

	//	if (board[row][col] == xOrO){
	//		twoRow += 1;
	//	}

	//	if (twoRow == 2){
	//		for (int col = 0; col < 3; col++){
	//			if (board[row][col] != "X" && board[row][col] != "O"){
	//				blockRow = row;
	//				blockCol = col;
	//			}
	//		}
	//		blockYesOrNo = "yes";
	//		break;
	//	}
	//	
	//}
	//twoRow = 0;

	//row = 0;
	//col = 0;

	//for (row = 0; row < 3; row++){
	//	

	//	if (board[row][col] == xOrO){
	//		twoRow += 1;
	//	}

	//	if (twoRow == 2){
	//		for (int row = 0; row < 3; row++){
	//			if (board[row][col] != "X" && board[row][col] != "O"){
	//				blockRow = row;
	//				blockCol = col;
	//			}
	//		}
	//		blockYesOrNo = "yes";
	//		break;
	//	}

	//	col++;
	//}

	//twoRow = 0;
	//col = 2;
	//row = 0;
	//	for (row = 0; row < 3; row++){
	//	

	//		if (board[row][col] == xOrO){
	//			twoRow += 1;
	//		}

	//		if (twoRow == 2){
	//			col = 2;
	//			for (int row = 0; row < 3; row++){
	//				if (board[row][col] != "X" && board[row][col] != "O"){
	//					blockRow = row;
	//					blockCol = col;
	//					
	//				}
	//				col--;
	//			}
	//			blockYesOrNo = "yes";
	//			break;
	//		}

	//		col--;
	//}

	//twoRow = 0;
}

void checkWin(){

	int row = 0;
	int col = 0;
	int blockRow = 0;
	int blockCol = 0;
	string xOrO = "X";
	int threeRow = 0;

	for (int row = 0; row < 3; row++){

		if (board[row][col] == xOrO){
			threeRow += 1;
		}

		if (threeRow == 3){
			blockRow = row + 1;
			blockCol = col + 1;
			//cout << "win row";
			break;
		}


	}
	threeRow = 0;

	for (int col = 0; col < 3; col++){

		if (board[row][col] == xOrO){
			threeRow += 1;
		}

		if (threeRow == 3){
			blockRow = row + 1;
			blockCol = col + 1;
			//cout << "win col";
			break;
		}

	}
	threeRow = 0;

	col = 0;

	for (int row = 0; row < 3; row++){


		if (board[row][col] == xOrO){
			threeRow += 1;
		}

		if (threeRow == 3){
			blockRow = row + 1;
			blockCol = col + 1;
			//cout << "win dia";
			break;
		}

		col++;
	}

	threeRow = 0;

	col = 2;
	for (int row = 0; row < 3; row++){


		if (board[row][col] == xOrO){
			threeRow += 1;
		}

		if (threeRow == 3){
			blockRow = row + 1;
			blockCol = col + 1;
			//cout << "win dia 2";
			break;
		}

		col--;
	}

	threeRow = 0;

}

void AI(){

	if (blockYesOrNo == "yes"){

		board[blockRow][blockCol] = "O";
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
			if (highestNum < weightedArray[row][col]){
				highestNum = weightedArray[row][col];
				bestRow = row;
				bestCol = col;

			}
		}
	}
	weightedArray[bestRow][bestCol] = 0;
	board[bestRow][bestCol] = "O";

}