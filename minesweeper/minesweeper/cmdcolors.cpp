#include "cmdcolors.h"
//----------------------------------------------------------------------------
static int __BACKGROUND = BLACK;
static int __FOREGROUND = LIGHTGRAY;
//----------------------------------------------------------------------------
void showCursor(BOOL _val, BOOL _type) {
	CONSOLE_CURSOR_INFO info;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	info.dwSize = 10 + 90 * _type;
	info.bVisible = _val;
	SetConsoleCursorInfo(consoleHandle, &info);
}
//----------------------------------------------------------------------------
void resizewindow(int _x, int _y) {
	SMALL_RECT DisplayArea = { 0, 0, 0, 0 };
	DisplayArea.Right = _x;
	DisplayArea.Bottom = _y;
	COORD ScrnXY = { (_x + 1), (_y + 1) };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO SBInfo;
	GetConsoleScreenBufferInfo(hOut, &SBInfo);

	SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);
	SetConsoleScreenBufferSize(hOut, ScrnXY);
}
//----------------------------------------------------------------------------
void textcolor(int color) {
	__FOREGROUND = color;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (__BACKGROUND << 4));
}
//----------------------------------------------------------------------------
void textbackground(int color) {
	__BACKGROUND = color;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), __FOREGROUND + (color << 4));
}
//----------------------------------------------------------------------------
void gotoxy(int _x, int _y) {
	COORD coord;
	coord.X = _x;
	coord.Y = _y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//----------------------------------------------------------------------------
void fullscreen() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleDisplayMode(consoleHandle, CONSOLE_FULLSCREEN_MODE, 0);
}
//----------------------------------------------------------------------------
void maximizedWindow() {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}
//----------------------------------------------------------------------------
void changeFontSize(int height, std::string f, int width) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = width;
	cfi.dwFontSize.Y = height;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wstring font = std::wstring(f.begin(), f.end());
	wcscpy_s(cfi.FaceName, font.c_str());
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}