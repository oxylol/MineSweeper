#ifndef CMDCOLORS_H
#define CMDCOLORS_H
#include <Windows.h>
#include <stdlib.h>
#include <string>
//----------------------------------------------------------------------------
void showCursor(BOOL, BOOL);	// Visar/gömmer cursorn, block eller _
void resizewindow(int, int);	// Ändrar fönstrets strl och buffer. Ange nytt x- och y värde
void textcolor(int);			// Byter färgen på texten. Ange ny färg
void textbackground(int);		// Byter färgen på backgrunden. Ange ny färg
void gotoxy(int, int);			// Placerar markören. Ange nytt x- och y värde
void fullscreen();				// FullScreen utan system menu
void maximizedWindow();			// 'Fullscreen' med system menu.
void changeFontSize(int, std::string = "Consolas", int = 0); // höjd, bredd, font
typedef enum {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY,
	LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
}COLORS;
//----------------------------------------------------------------------------
#endif
//--