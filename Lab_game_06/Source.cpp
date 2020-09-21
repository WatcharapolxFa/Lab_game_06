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

struct ans
{
	char ch = ' ';
	int x = 38, y = 20;
	int nub[2];
	int bullet[5]; // กระสุน
	int position_x[5]; //ตำแหน่งกระสุน แกน x 5 นัด
	int position_y[5]; //ตำแหน่งกระสุน แกน y 5 นัด
}gogo;

int main()
{
	setcursor(0);

	draw_ship(gogo.x, gogo.y);
	for (int i = 0; i < 5; i++)
	{
		gogo.bullet[i] = 0;
	}

	do {
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
					//โชว์กระสุน
					if (gogo.bullet[i] == 0)
					{
						gogo.bullet[i] = 1;
						gogo.position_x[i] = gogo.x;
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
		if (gogo.nub[0] == 4 && gogo.x < 113)
		{
			erase_ship(gogo.x, gogo.y); draw_ship(++gogo.x, gogo.y);
		}


		for (int i = 0; i < 5; i++) {
			if (gogo.bullet[i] == 1)
			{

				bullet_ship(gogo.position_x[i], gogo.position_y[i]);
				gogo.position_y[i] = gogo.position_y[i] - 1;
				if (gogo.position_y[i] > 0) {
					Draw_bullet(gogo.position_x[i], gogo.position_y[i]);
				}
				else
				{
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


// Draw_ship
void draw_ship(int x, int y)
{
	setcursor(0);
	setcolor(2, 4);
	gotoxy(x, y); printf(" <-0-> ");
}

// erase_ship
void erase_ship(int x, int y)
{
	setcolor(0, 0);
	gotoxy(x, y); printf("       ");
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
	printf(" < ^ > ");

}
// bullet_ship
void bullet_ship(int x, int y)
{
	setcolor(0, 0);
	gotoxy(x, y); printf("        ");
}