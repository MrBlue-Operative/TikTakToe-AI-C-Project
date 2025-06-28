#include<bits/stdc++.h>
using namespace std;

struct Move {
	int row, col;
};

char player = 'x', opponent = 'o';

// This function returns true if there are moves
// remaining on the board. It returns false if
// there are no moves left to play.
bool isMovesLeft(char board[3][3]) {
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
			if (board[i][j]=='_')
				return true;
	return false;
}

// This is the evaluation function
int evaluate(char b[3][3]) {
	// Checking for Rows for X or O victory.
	for (int row = 0; row<3; row++) {
		if (b[row][0]==b[row][1] &&
		        b[row][1]==b[row][2]) {
			if (b[row][0]==player)
				return +10;
			else if (b[row][0]==opponent)
				return -10;
		}
	}

	// Checking for Columns for X or O victory.
	for (int col = 0; col<3; col++) {
		if (b[0][col]==b[1][col] &&
		        b[1][col]==b[2][col]) {
			if (b[0][col]==player)
				return +10;

			else if (b[0][col]==opponent)
				return -10;
		}
	}

	// Checking for Diagonals for X or O victory.
	if (b[0][0]==b[1][1] && b[1][1]==b[2][2]) {
		if (b[0][0]==player)
			return +10;
		else if (b[0][0]==opponent)
			return -10;
	}

	if (b[0][2]==b[1][1] && b[1][1]==b[2][0]) {
		if (b[0][2]==player)
			return +10;
		else if (b[0][2]==opponent)
			return -10;
	}

	// Else if none of them have won then return 0
	return 0;
}

// This is the minimax function. It considers all
// the possible ways the game can go and returns
// the value of the board
int minimax(char board[3][3], int depth, bool isMax) {
	int score = evaluate(board);

	// If Maximizer has won the game return his/her
	// evaluated score
	if (score == 10)
		return score;

	// If Minimizer has won the game return his/her
	// evaluated score
	if (score == -10)
		return score;

	// If there are no more moves and no winner then
	// it is a tie
	if (isMovesLeft(board)==false)
		return 0;

	// If this maximizer's move
	if (isMax) {
		int best = -1000;

		// Traverse all cells
		for (int i = 0; i<3; i++) {
			for (int j = 0; j<3; j++) {
				// Check if cell is empty
				if (board[i][j]=='_') {
					// Make the move
					board[i][j] = player;

					best = max( best,
					            minimax(board, depth+1, !isMax) );

					board[i][j] = '_';
				}
			}
		}
		return best;
	}

	// If this minimizer's move
	else {
		int best = 1000;

		for (int i = 0; i<3; i++) {
			for (int j = 0; j<3; j++) {
				if (board[i][j]=='_') {
					// Make the move
					board[i][j] = opponent;

					best = min(best,
					           minimax(board, depth+1, !isMax));

					// Undo the move
					board[i][j] = '_';
				}
			}
		}
		return best;
	}
}

// This will return the best possible move for the player
Move findBestMove(char board[3][3]) {
	int bestVal = -1000;
	Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;

	for (int i = 0; i<3; i++) {
		for (int j = 0; j<3; j++) {
			// Check if cell is empty
			if (board[i][j]=='_') {
				// Make the move
				board[i][j] = player;

				// compute evaluation function for this
				// move.
				int moveVal = minimax(board, 0, false);

				// Undo the move
				board[i][j] = '_';

				// If the value of the current move is
				// more than the best value, then update
				// best/
				if (moveVal > bestVal) {
					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}

	return bestMove;
}
void display(char board[3][3]) {
	cout << board[0][0] << '|' << board[0][1] << '|' << board[0][2] << endl;
	cout << "------" << endl;
	cout << board[1][0] << '|' << board[1][1] << '|' << board[1][2] << endl;
	cout << "------" << endl;
	cout << board[2][0] << '|' << board[2][1] << '|' << board[2][2] << endl;
}
bool checkWinner(char symbols[3][3], char e) {
	// Rows
	if(symbols[0][0] == e && symbols[0][1] == e && symbols[0][2] == e) return true;
	if(symbols[1][0] == e && symbols[1][1] == e && symbols[1][2] == e) return true;
	if(symbols[2][0] == e && symbols[2][1] == e && symbols[2][2] == e) return true;

	// Columns
	if(symbols[0][0] == e && symbols[1][0] == e && symbols[2][0] == e) return true;
	if(symbols[0][1] == e && symbols[1][1] == e && symbols[2][1] == e) return true;
	if(symbols[0][2] == e && symbols[1][2] == e && symbols[2][2] == e) return true;

	// Diagonals
	if(symbols[0][0] == e && symbols[1][1] == e && symbols[2][2] == e) return true;
	if(symbols[0][2] == e && symbols[1][1] == e && symbols[2][0] == e) return true;

	return false;
}
Move InputFunction() {
	int number = 0;
	Move coordinates;
	cout << "Enter the Box number : ";
	cin >> number;
	number--;
	coordinates.row = (number/3);
	coordinates.col = (number%3);
	return coordinates;
}
// Driver code
int main() {
	char board[3][3] = {
		{ '_', '_', '_' },
		{ '_', '_', '_' },
		{ '_', '_', '_' }
	};
	int x,y;
	bool running = true;
	while(isMovesLeft(board) && running) {
		system("cls");
		display(board);
		label:
		Move getInput = InputFunction();
		if(board[getInput.row][getInput.col] == '_'){
			board[getInput.row][getInput.col] = opponent;
		}else{
			cout << "Invalid! Box is occupied!" << endl;
			goto label;
		}
		if(checkWinner(board, opponent)) {
			running = false;
			cout << "Player Won!" << endl;
			break;
		}
		Move bestMove = findBestMove(board);
		board[bestMove.row][bestMove.col] = player;
		if(checkWinner(board, player)) {
			system("cls");
			display(board);
			running = false;
			cout << "Computer Won!" << endl;
			break;
		}
	}
	if(running) {
		system("cls");
		display(board);
		cout << "Its a Draw!" << endl;
	}
	return 0;
}
