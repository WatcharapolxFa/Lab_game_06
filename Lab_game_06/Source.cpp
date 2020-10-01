#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
void gotoxy(int, int);
void draw_ship(int, int);
void erase_ship(int, int);
void setcolor(int, int);
void setcursor(bool);
void  Draw_bullet(int, int);
void bullet_ship(int, int);
void draw_star(int x, int y);
void erase_bullet(int x, int y);
char cursor(int x, int y);
void draw_scroll(int x, int y);
void erase_star(int x, int y);

struct ans
{
	char ch = ' ';
	int x = 38, y = 20;
	int nub[2];
	int bullet[5]; // ¡ÃÐÊØ¹
	int position_x[5]; //µÓáË¹è§¡ÃÐÊØ¹ á¡¹ x 5 ¹Ñ´
	int position_y[5]; //µÓáË¹è§¡ÃÐÊØ¹ á¡¹ y 5 ¹Ñ´
	int star;
	int star_x[20];
	int star_y[20];
	int scr = 0;
}gogo;


int main()
{


	setcursor(0);
	srand(time(NULL));
	
	for (gogo.star = 0; gogo.star < 20; gogo.star++)
	{
		gogo.star_x[gogo.star] = rand() % 100;

		gogo.star_y[gogo.star] = rand() % 5;
		gogo.star_y[gogo.star] += 1;

		draw_star(gogo.star_x[gogo.star], gogo.star_y[gogo.star]);


	}
	draw_ship(gogo.x, gogo.y);
	for (int i = 0; i < 5; i++)
	{
		gogo.bullet[i] = 0;
	}

	do {
		draw_scroll(gogo.x, gogo.y);
		if (_kbhit()) {
			gogo.ch = _getch();

			if (gogo.ch == 'w')
			{
				gogo.nub[0] = 1;
			}

			if (gogo.ch == 'a')
			{
				gogo.nub[0] = 2;
			}

			if (gogo.ch == 's')
			{
				gogo.nub[0] = 3;
			}

			if (gogo.ch == 'd')
			{
				gogo.nub[0] = 4;
			}

			if (gogo.ch == ' ')
			{
				for (int i = 0; i < 5; i++)
				{
				
					if (gogo.bullet[i] == 0)
					{
						gogo.bullet[i] = 1;
						gogo.position_x[i] = gogo.x + 2;
						gogo.position_y[i] = gogo.y - 2;
						Draw_bullet(gogo.position_x[i], gogo.position_y[i]);
						break;
					}

				}
			}
			fflush(stdin);


		}
		if (gogo.nub[0] == 1 && gogo.x > 0)
		{
			erase_ship(gogo.x, gogo.y); draw_ship(gogo.x, gogo.y);
		}
		if (gogo.nub[0] == 2 && gogo.y < 50 && gogo.x > 0)
		{
			erase_ship(gogo.x, gogo.y); draw_ship(--gogo.x, gogo.y);
		}
		if (gogo.nub[0] == 3 && gogo.y > 0)
		{
			erase_ship(gogo.x, gogo.y); draw_ship(gogo.x, gogo.y);
		}
		if (gogo.nub[0] == 4 && gogo.x < 95)
		{
			erase_ship(gogo.x, gogo.y); draw_ship(++gogo.x, gogo.y);
		}


		for (int i = 0; i < 5; i++) {
			if (gogo.bullet[i] == 1)
			{
				erase_bullet(gogo.position_x[i], gogo.position_y[i]);
				if (gogo.position_y[i] > 0)
				{
					if (cursor(gogo.position_x[i], gogo.position_y[i] - 1) == '*') // 
					{
						Beep(1000, 100);
						gogo.bullet[i] = 0;
						erase_bullet(gogo.position_x[i], gogo.position_y[i] - 1);
						erase_star(gogo.position_x[i], gogo.position_y[i] - 1);//
						gogo.scr++;
						draw_star(rand() % 100, rand() % 5);
						
					}
					else
					{
						Draw_bullet(gogo.position_x[i], --gogo.position_y[i]);// 
					}
				}
				else
				{
					erase_bullet(gogo.position_x[i], gogo.position_y[i]);
					gogo.bullet[i] = 0;
				}
			}
		}

		Sleep(100);
		setcolor(2, 0);
	} while (gogo.ch != 'x');


	return 0;
}

// Ship position
void gotoxy(int x, int y)
{
	COORD c = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Draw_star
void draw_star(int x, int y)
{
	setcolor(5, 0);
	gotoxy(x, y);
	printf("*");
}
// Erase_star
void erase_star(int x, int y)
{
	setcolor(0, 0);
	gotoxy(x, y);
	printf(" ");
}

// Draw_ship
void draw_ship(int x, int y)
{
	setcursor(0);
	setcolor(2, 4);
	gotoxy(x, y); printf("<-0->");
}

// erase_ship
void erase_ship(int x, int y)
{
	setcolor(0, 0);
	gotoxy(x, y); printf("     ");
}

// erase_bullet
void erase_bullet(int x, int y)
{
	setcolor(0, 0);
	gotoxy(x, y); printf(" ");
}
//set color
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
// setcursor
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
// Draw_bullet
void Draw_bullet(int x, int y)
{
	setcolor(6, 0);
	gotoxy(x, y);
	printf("^");
}
// bullet_ship
void bullet_ship(int x, int y)
{
	setcolor(0, 0);
	gotoxy(x, y); printf("     ");
}

char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];

}

// Draw_scroll
void draw_scroll(int x, int y)
{	setcolor(12, 15);
	gotoxy(105, 1);
	printf("============");
	gotoxy(105, 3);
	setcolor(12, 0);
	printf("Score : %d", gogo.scr);
	setcolor(12, 15);
	gotoxy(105, 5);
	printf("============");
	
}