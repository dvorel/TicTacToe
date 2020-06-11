#include <stdio.h>

//osnovno
bool g = true, d = true;
char board[3][3];
int scores;


//funkcije za igru
int check_moves(int*, char b[][3]);
bool check(int*, int, int);
void make_move();
void restart_board();
void show_board();
void init();
bool nastavak_igre();
bool provjera_pobjednika(char b[3][3]);
int upisi_rez(char);

typedef struct locations {
	int x;
	int y;
}Locations;
Locations numms[9];


//minimax funkcije
int minimax(char b[3][3], bool maxi, int depth);
void pc_move();



int main(void) {
	init();
	while (g) {
		restart_board();
		int i = 0;
		while (d) {
			printf("\n\nPC:");
			pc_move();
			show_board();
			d = provjera_pobjednika(board);
			//ako pc nije pobjedio
			if (d) {
				make_move();
				show_board();
				d = provjera_pobjednika(board);
			}
		}

		//za nastavak igre
		g = nastavak_igre();
		d = g;
	}
}

void copy_board(char board[3][3], char source[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = source[i][j];
		}
	}
}

void pc_move() {
	int moves[9];
	int scores[9];
	int n = check_moves(moves, board);
	int move = 0;
	int best = -11;

	for (int i = 0; i < n; i++) {
		char temp_board[3][3];
		copy_board(temp_board, board);
		temp_board[numms[moves[i]].x][numms[moves[i]].y] = 'X';
		scores[i] = minimax(temp_board, false, 0);

		if (scores[i] > best) {
			best = scores[i];
			move = moves[i];
		}
	}
	board[numms[move].x][numms[move].y] = 'X';
	printf(" %d", move);
}

void make_move() {
	int moves[9];
	int n = 0;
	int move;

	n = check_moves(moves, board);

	do {
		printf("\n\nPlayer: ");
		scanf(" %d", &move);
	} while (!check(moves, move, n));
	board[numms[move].x][numms[move].y] = 'O';
}

int check_moves(int *container, char b[][3]) {
	//check for available moves
	int n = 0;
	for (int i = 0; i < 9; i++) {
		if (b[numms[i].x][numms[i].y] - 1 < '9') {
			container[n] = i;
			n++;
		}
	}
	return n;
}

bool check(int *moves, int move, int n) {
	for (int i = 0; i < n; i++) {
		if (moves[i] == move) {
			return true;
		}
	}
	return false;
}

bool provjera_pobjednika(char b[3][3]) {

	//ravno
	for (int i = 0; i < 3; i++) {
		if (b[i][0] == b[i][1] && b[i][1] == b[i][2]) {
			scores += upisi_rez(b[i][0]);
			return false;
		}
		if (b[0][i] == b[1][i] && b[1][i] == b[2][i]) {
			scores += upisi_rez(b[0][i]);
			return false;
		}
	}

	//dijagonale
	if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
		scores += upisi_rez(b[0][0]);
		return false;
	}

	if (b[2][0] == b[1][1] && b[1][1] == b[0][2]) {
		scores += upisi_rez(b[2][0]);
		return false;
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (b[i][j] != 'X' && b[i][j] != 'O') {
				return true;
			}
		}
	}

	printf("\nDraw!");
	return false;
}

int upisi_rez(char player) {
	printf("\n\nPlayer %c won!", player);
	if (player == 'X') {
		printf("\nSCORE = %d", (scores + 10));
		return +10;
	}
	printf("\nSCORE = %d", (scores - 10));
	return -10;
}


bool nastavak_igre() {
	int input;
	printf("\n\n|1| Nova igra\n|2| Izlaz\n-> ");

	do { scanf(" %d", &input); } while (input!=1 && input!=2);

	if (input == 1) {
		return true;
	}
	return false;
}

void init() {	
	//polje lokacija
	//prvi red
	numms[0].x = 0;
	numms[0].y = 0;
	numms[1].x = 0;
	numms[1].y = 1;
	numms[2].x = 0;
	numms[2].y = 2;
	//drugi red
	numms[3].x = 1;
	numms[3].y = 0;
	numms[4].x = 1;
	numms[4].y = 1;
	numms[5].x = 1;
	numms[5].y = 2;
	//treci red
	numms[6].x = 2;
	numms[6].y = 0;
	numms[7].x = 2;
	numms[7].y = 1;
	numms[8].x = 2;
	numms[8].y = 2;
	//---//
}

void show_board() {
	printf("\n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%c", board[i][j]);
			if (j != 2) {
				printf(" | ");
			}
		}
		if (i != 2) {
			printf("\n---------\n");

		}
	}
}

void restart_board() {
	for (int i = 0; i < 9; i++) {
		board[numms[i].x][numms[i].y] = i+'0';
	}
}


//minimax

char minimax_score(char b[3][3]) {
	//ravno
	for (int i = 0; i < 3; i++) {
		if (b[i][0] == b[i][1] && b[i][1] == b[i][2]) {
			return b[i][0];
		}
		if (b[0][i] == b[1][i] && b[1][i] == b[2][i]) {
			return b[0][i];
		}
	}
	//dijagonale
	if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
		return b[0][0];
	}

	if (b[2][0] == b[1][1] && b[1][1] == b[0][2]) {
		return b[2][0];
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (b[i][j] != 'X' && b[i][j] != 'O') {
				return 'N';
			}
		}
	}
	return 'D';
}

int minimax_who(char player) {
	switch (player) {
	case 'X':
		return +10;
	case 'O':
		return -10;
	case 'D':
		return 0;
	}
	return -1;
}

int minimax(char b[3][3], bool maxi, int depth) {
	//ako je kraj u minimax algoritmu
	int rezultat = minimax_who(minimax_score(b));
	if (rezultat != -1) {
		return rezultat;
	}

	if (maxi) {
		int bestScore = -11;
		int n = 0;
		int moves[9];
		n = check_moves(moves, b);

		for (int i = 0; i < n; i++) {
			char temp_board[3][3];
			copy_board(temp_board, b);
			//napravi sljedeci pokret
			temp_board[numms[moves[i]].x][numms[moves[i]].y] = 'X';
			int s = minimax(temp_board, false, depth + 1);
			if (s > bestScore) {
				bestScore = s;
			}
		}
		return bestScore;
	}
	else {
		int bestScore = 11;
		int n = 0;
		int moves[9];
		n = check_moves(moves, b);

		for (int i = 0; i < n; i++) {
			char temp_board[3][3];
			copy_board(temp_board, b);
			//napravi sljedeci pokret
			temp_board[numms[moves[i]].x][numms[moves[i]].y] = 'O';
			int s = minimax(temp_board, true, depth + 1);
			if (s < bestScore) {
				bestScore = s;
			}
		}
		return bestScore;
	}
}
