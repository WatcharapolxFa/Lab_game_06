#include<stdio.h>
#include<conio.h>
#include<windows.h>

void draw_ship(int, int);
void gotoxy1(int, int);
void erase_ship(int, int);
void setcursor(bool);
void setcolor(int, int);
void bullet(int, int);
void gotoxy2(int, int);
void erase_bullet(int, int);

int main()

{
	char ch = ' ';
	int direct = 0;
	int x = 38, y = 20;
	int a = 41, b = 19;
	draw_ship(x, y);

	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') { direct = 1; }
			if (ch == 'd') { direct = 2; }
			if (ch == 'w') { direct = 3; }
			if (ch == 's') { direct = 4; }
			if (ch == ' ') { direct = 5; }
			fflush(stdin);
		}
		if (direct > 0 && direct < 5)
		{
			a = x + 3; b = y - 1;
			if (direct == 1 && x > 0) { erase_ship(x, y); draw_ship(--x, y); }
			if (direct == 2 && x < 113) { erase_ship(x, y); draw_ship(++x, y); }
			//if (direct == 3 && y > 0) { erase_ship(x, y); draw_ship(x, --y); }
			if (direct == 4 && y < 30) { erase_ship(x, y); draw_ship(x, y); }
		}
		else if (direct == 5 && b > 0)
		{
			erase_bullet(a, b);
			bullet(a, --b);
			Sleep(100);
		}
		Sleep(100);
		setcolor(2, 0);
	} while (ch != 'x');
	return 0;
}

void draw_ship(int x, int y)
{
	setcursor(0);
	setcolor(2, 4);
	gotoxy1(x, y);
	printf(" <-0-> ");
}

void erase_ship(int x, int y)
{
	gotoxy1(x, y);
	printf("       ");

}
void erase_bullet(int x, int y)
{


	gotoxy2(x, y + 6);
	for (int i = 0; i < 5; i++) {
		printf(" ");
		gotoxy2(x, y + 4);
	}

}
void bullet(int x, int y)
{


	gotoxy2(x, y);
	for (int i = 0; i < 5; i++) {

		printf("|\n");
		gotoxy2(x, y + 1);


	}
}
void gotoxy2(int a, int b)
{
	COORD d = { a, b };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
}
void gotoxy1(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}