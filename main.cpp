#include <stdio.h>
#include <windows.h>
#include "Console.h"


#define WIDTH 60
#define LENGTH 20
#define MAP 40

struct ST_OBJECT
{
	int x;
	int y;
};


ST_OBJECT g_stPlayer;
ST_OBJECT g_stKey;
ST_OBJECT g_stLock;

int main() {

	SetConsoleSize(WIDTH, LENGTH);

	g_stPlayer.x = 20;
	g_stPlayer.y = 10;


	int map[MAP][20] = { 0 };

	



	while (1) 
	{
		Clear();

		for (int i = 0; i < 20; i++)
		{
			GotoXY(MAP, i);
			printf("■");
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {	//왼쪽방향키
			g_stPlayer.x = g_stPlayer.x - 2;
			if (g_stPlayer.x < 0) g_stPlayer.x = 0;
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {	//오른쪽방향키
			g_stPlayer.x = g_stPlayer.x + 2;
			if (g_stPlayer.x > MAP-2) g_stPlayer.x = MAP - 2;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000) {	//위쪽방향키
			g_stPlayer.y--;
			if (g_stPlayer.y < 0) g_stPlayer.y = 0;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {	//아래쪽방향키
			g_stPlayer.y++;
			if (g_stPlayer.y > LENGTH-1) g_stPlayer.y = LENGTH - 1;
		}

		GotoXY(g_stPlayer.x, g_stPlayer.y);
		printf("★");

		Sleep(50);
	}

	return 0;
}