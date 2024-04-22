#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
#include <chrono>
#include <ctime> 
#include "cmdcolors.h"

using namespace ::std;
int level = 0;
int board_size = 99;
int bombs = 30;
int x = 0, y = 0, dX = 0, dY = 0;
bool game_over = false;
int level_check = 0;
string username;

vector<vector<int>> bomb_xy;
vector<vector<int>> board(board_size, vector<int>(board_size, 0));
vector<vector<bool>> revealed(board_size, vector<bool>(board_size, false));

vector<vector<int>> bomb() {

	vector<vector<bool>> used(board_size, vector<bool>(board_size, false));
	vector<int> x;
	vector<int> y;

	for (int i = 0; i < bombs;) {
		int ry = rand() % board_size + 1;
		int rx = rand() % board_size + 1;
		if (!used[ry - 1][rx - 1]) {
			x.push_back(rx - 1);
			y.push_back(ry - 1);
			i++;
			used[ry - 1][rx - 1] = true;
		}
	}
	return { x,y };
}



// Define menu options and level levels as arrays of strings
const int menuOptionCount = 5;
string menuOptions[menuOptionCount] = { " New game     ",
										" Continue     ",
										" Highscore    ",
										" Instructions ",
										" Exit         " };
const int levelOptionCount = 3;
string levelOptions[levelOptionCount] = { " Level 1      ",
													" Level 2      ",
													" Level 3      ", };


//----MENU-------------------------------------
void init() {
	setlocale(LC_ALL, "");
	textcolor(WHITE);
	showCursor(false, false);
	textbackground(BLACK);
	system("CLS");
}


// Print the menu options
void printMenu(int tal, string vald[], int antal) {
	for (int i = 0; i < antal; i++) {
		textcolor(WHITE);
		textbackground(BLACK);
		if (tal == i) {
			textcolor(BLUE);
			textbackground(WHITE);
		}
		gotoxy(2, 2 + i);
		cout << vald[i];
	}
	textcolor(WHITE);
	textbackground(BLACK);
}

// Handle user key presses for menu navigation
int handleKey(int k, int a, int max) {

	if (k == 72) { // Pil upp 72
		a--;
		if (a < 0) {
			a = max;
		}
	}
	else if (k == 80) { // Pil ner 80
		a++;
		if (a > max) {
			a = 0;
		}
	}
	return a;
}

// Display the menu and handle user input
int menu(string vald[], int ant) {
	system("CLS");
	int key = 0, choice = 0;
	while (key != 13) {
		printMenu(choice, vald, ant);
		key = _getch();
		if (key == 224 || key == 0) {
			key = _getch();
		}
		choice = handleKey(key, choice, ant - 1);
	}
	return choice;
}

//---------------------------------------------


void board_constructor() {
	int bomb_count = 0;

	for (int y = 0; y < board_size; y++) {
		for (int x = 0; x < board_size; x++) {
			for (int a = -1; a <= 1; a++) {
				for (int b = -1; b <= 1; b++) {
					int ny = y + a;
					int nx = x + b;
					if (ny >= 0 && ny < board_size && nx >= 0 && nx < board_size && board[ny][nx] == 9) {
						bomb_count++;
					}
				}
			}
			if (board[y][x] != 9)
				board[y][x] = bomb_count;
			bomb_count = 0;
		}
	}
}


void level_handeler() {
	switch (level)
	{
	case 0:
		board_size = 9;
		bombs = 10;
		break;

	case 1:
		board_size = 16;
		bombs = 40;
		break;

	case 2:
		board_size = 24;
		bombs = 99;
		break;

	default:
		break;
	}
}
void color(int o, int p) {
	switch (board[o][p])
	{
	case 0:
		textcolor(BLACK);
		break;
	
	case 1:
		textcolor(LIGHTBLUE);
		break;
	case 2:
		textcolor(LIGHTGREEN);
		break;
	case 3:
		textcolor(LIGHTRED);
		break;
	case 4:
		textcolor(LIGHTMAGENTA);
		break;
	case 5:
		textcolor(LIGHTCYAN);
		break;
	case 6:
		textcolor(LIGHTGRAY);
		break;
	case 7:
		textcolor(WHITE);
		break;
	case 8:
		textcolor(DARKGRAY);
		break;
	case 9:
		textcolor(RED);
		break;
	default:
		break;
	}
}
void display_board() {
	for (int y = 0; y < board_size; y++)
	{
		for (int x = 0; x < board_size; x++)
		{
			if (revealed[y][x] == true) {
				color(y, x);
				color(y, x);
				if (board[y][x] == 9)
					cout << char(254) << " ";
				else
					cout << board[y][x] << " ";
			}
			else {
				textcolor(WHITE);
				cout << char(254) << " ";
			}

		}
		cout << endl;
	}
}


void display_player() {
	gotoxy(x, y);
}


void reveal_3x3(int nx1, int ny1) {
	for (int a = -1; a <= 1; a++)
	{
		for (int b = -1; b <= 1; b++)
		{
			int ny2 = ny1 + a;
			int nx2 = nx1 / 2 + b;
			if (((ny2 >= 0 && ny2 < board_size) && (nx2 >= 0 && nx2 < board_size)) && board[ny2][nx2] != 0 && board[ny2][nx2] != 9) {
				color(ny2, nx2);
				gotoxy(nx2 * 2, ny2);
				revealed[ny2][nx2] = true;
				cout << board[ny2][nx2];
			}
		}
	}
}

void reveal_empty(int y1, int x1) {

	if (board[y1][x1 / 2] == 0) {
		for (int a = -1; a <= 1; a++)
		{
			for (int b = -1; b <= 1; b++)
			{
				int ny = y1 + a;
				int nx = x1 / 2 + b;
				if (((ny >= 0 && ny < board_size) && (nx >= 0 && nx < board_size)) && board[ny][nx] == 0 && revealed[ny][nx] == false) {
					textcolor(BLACK);
					gotoxy(nx * 2, ny);
					cout << board[ny][nx];
					reveal_3x3(nx * 2, ny);
					revealed[ny][nx] = true;
					reveal_empty(ny, nx * 2);
				}
			}
		}
	}
}

void gameKeys(int key) {

	if (key == 75 || key == 77) {
		if (key == 75) {
			dX = -2;
		}
		if (key == 77) {
			dX = 2;
		}
	}
	else
	{
		dX = 0;
	}

	if (key == 72 || key == 80) {
		if (key == 72) {
			dY = -1;
		}
		if (key == 80) {
			dY = 1;
		}
	}
	else
	{
		dY = 0;
	}

	if (key == 32) {
		color(y, x / 2);
		if (board[y][x / 2] == 9) {
			cout << char(254);
			game_over = true;
		}
		else if (board[y][x / 2] == 0) {
			cout << " ";
		}
		else
		{
			cout << board[y][x / 2];
		}
		revealed[y][x / 2] = true;
		reveal_empty(y, x);
	}
}

bool cntrl() {
	bool border_hit = false;
	if (x + dX < 0 || x + dX > board_size * 2 - 1 || y + dY < 0 || y + dY > board_size - 1) {
		border_hit = true;
	}
	return border_hit;
}
void move() {
	if (cntrl() == false)
	{
		x += dX;
		y += dY;
	}
}

bool win_check() {

	bool win = true;

	for (int i = 0; i < board_size; i++)
	{
		for (int p = 0; p < board_size; p++)
		{
			if (board[i][p] != 9 && revealed[i][p] == false) {
				win = false;
			}
		}
	}

	// if l is pressed win
	if (GetAsyncKeyState(0x4C)) {
		win = true;
	}


	return win;
}

void display_highscore() {
	ifstream file;
	file.open("score.txt");
	vector<string> scores;

	string score;

	while (!file.eof()) {
		getline(file, score);
		scores.push_back(score);
	}
	file.close();

	for (int i = 0; i < scores.size(); i++)
	{
		if (scores[i].find(username) != string::npos) {
			textcolor(RED);
		}
		else {
			textcolor(WHITE);
		}

		cout << scores[i] << endl;
	}
}

void save_score(double elapsed_time, string user) {
	ofstream file("score.txt", ios::app);
	if (file.is_open()) {

		file << user << "    Score: " << elapsed_time << " seconds" << "\n";

		file.close();
	}
	else {
		cout << "Unable to open the score file." << endl;
	}
}

//save progress to text file
void save() {
	ofstream file("save.txt");
	if (file.is_open()) {

		
		file << "Board Size: " << board_size << endl;
		file << "Bombs: " << bombs << endl;
		for (int i = 0; i < bombs; i++)
		{
			file << bomb_xy[0][i] << "," << bomb_xy[1][i] << endl;
		}
		file << "Difficulty: " << level << endl;
		file << "Player X: " << x << endl;
		file << "Player Y: " << y << endl;
		file << "Board: " << endl;
		for (int i = 0; i < board_size; i++)
		{
			for (int p = 0; p < board_size; p++)
			{
				file << board[i][p];
			}
			file << endl;
		}
		file << "Revealed: " << endl;
		for (int i = 0; i < board_size; i++)
		{
			for (int p = 0; p < board_size; p++)
			{
				file << revealed[i][p];
			}
			file << endl;
		}
		file << "User: " << username << endl;
		file.close();
	}
	else {
		cout << "Unable to open the save file." << endl;
	}
}
//load progress from text file
void load() {
	ifstream file("save.txt");
	if (file.is_open()) {
		string line;
		vector<string> board_str;
		vector<string> revealed_str;
		getline(file, line);
		board_size = stoi(line.substr(12, line.length() - 12));
		getline(file, line);
		bombs = stoi(line.substr(7, line.length() - 7));

		bomb_xy.push_back(vector<int>());
		bomb_xy.push_back(vector<int>());
		for (int i = 0; i < bombs; i++)
		{
			getline(file, line);
			bomb_xy[0].push_back(stoi(line.substr(0, line.find(","))));
			bomb_xy[1].push_back(stoi(line.substr(line.find(",") + 1, line.length() - line.find(",") - 1)));
		}

		getline(file, line);
		level = stoi(line.substr(12, line.length() - 12));
		getline(file, line);
		x = stoi(line.substr(10, line.length() - 10));
		getline(file, line);
		y = stoi(line.substr(10, line.length() - 10));
		getline(file, line);

		for (int i = 0; i < board_size; i++)
		{
			getline(file, line);
			board_str.push_back(line);
		}

		getline(file, line);
		
		for (int i = 0; i < board_size; i++)
		{
			getline(file, line);
			revealed_str.push_back(line);
		}

		for (int i = 0; i < board_size; i++)
		{
			for (int p = 0; p < board_size; p++)
			{
				board[i][p] = stoi(board_str[i].substr(p, 1));
				revealed[i][p] = stoi(revealed_str[i].substr(p, 1));
			}
		}

		getline(file, line);
		username = line.substr(6, line.length() - 6);

		file.close();
	}


	else {
		cout << "Unable to open the save file." << endl;
	}
	
}

bool continued = false;
void clear() {
	for (int i = 0; i < board_size; i++)
	{
		for (int p = 0; p < board_size; p++)
		{
			x = 0;
			y = 0;
			board[i][p] = 0;
			revealed[i][p] = false;
		}
	}

	bomb_xy.clear();
	game_over = false;

}


void level_cleared() {
	level += 1;
	cout << "Level " << level << " cleared!" << endl;
	level_check++;
}



void game() {


	//----------------------------------------------
	//not mine
	auto start = chrono::system_clock::now();
	//----------------------------------------------


	if (continued == false) {
		bomb_xy = bomb();
	}

	for (int i = 0; i < bombs; i++)
	{
		board[bomb_xy[0][i]][bomb_xy[1][i]] = 9;
	}

	board_constructor();
	display_board();


	int key = 0;
	while (key != 27 && !win_check() && !game_over && level != 3) {
		dX = 0;
		dY = 0;
		if (_kbhit()) {
			key = _getch();
			if (key == 224 || key == 0) {
				key = _getch();
			}
			gameKeys(key);
		}
		move();
		save();
		display_player();
	}
	gotoxy(0, board_size + 1);
	
	textcolor(WHITE);

	if (game_over) {
		cout << "You lose!" << endl;
	}

	if (win_check() && level_check >= 2) {


		//----------------------------------------------
				//not mine
		auto end = chrono::system_clock::now();

		chrono::duration<double> elapsed_seconds = end - start;
		time_t end_time = chrono::system_clock::to_time_t(end);
		cout << "elapsed time: " << elapsed_seconds.count() << endl;
		//---------------------------------------------

		cout << "Enter your name: ";



		cin >> username;

		system("pause");

		save_score(elapsed_seconds.count(),username);
	}
	else if (win_check()) {
		clear();
		level_cleared();
		level_handeler();
		system("pause");
		system("CLS");
		game();
	}

}

int main() {


	srand(time(NULL));

	int val = 0;

	while (val != 4) {
		val = menu(menuOptions, menuOptionCount);
		
		switch (val)
		{
		case 0:
			level = menu(levelOptions, levelOptionCount);
			level_handeler();
			showCursor(true, true);
			system("CLS");
			clear();
			continued = false;
			game();
			system("PAUSE");
			break;

		case 1:
			system("CLS");
			continued = true;
			load();
			game();
			system("PAUSE");

			break;

		case 2:
			system("CLS");
			display_highscore();
			system("PAUSE");

			break;

		case 3:
			return 0;
			break;

		default:
			break;
		}
		clear();

	}

	system("pause");
	return 0;
}