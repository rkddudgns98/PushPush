#include <stdio.h>
#include <windows.h>
#include "Console.h"
#include <conio.h>


#define WIDTH 60
#define LENGTH 20

struct ST_OBJECT
{
	int x;
	int y;
	bool bActive;
};


ST_OBJECT g_stPlayer = { 0 };
ST_OBJECT g_stKey[10] = { 0 };
ST_OBJECT g_stLock[10] = { 0 };

int main() {

	SetConsoleSize(WIDTH, LENGTH);	//콘솔창 크기 변경

	//게임시작 변수 초기화
	bool gamestate = false;

	//게임시작
	gamestate = true;

	//스테이지 초기화
	int stage[20][20] = { 0 };	

	//스테이지 선언
	bool stage1_bActive = false;	

	//스테이지시작
	stage1_bActive = true;	

	//각 스테이지 초기화
	if (stage1_bActive)
	{	
		//플레이어 좌표 설정
		g_stPlayer.x = 4; 
		g_stPlayer.y = 4;

		//열쇠 좌표 설정
		g_stKey[0].x = 3;
		g_stKey[0].y = 3;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 3;
		g_stKey[1].y = 4;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 4;
		g_stKey[2].y = 5;
		g_stKey[2].bActive = true;

		g_stKey[3].x = 5;
		g_stKey[3].y = 3;
		g_stKey[3].bActive = true;

		stage[0][3] = { 1 };
		stage[0][4] = { 1 };
		stage[0][5] = { 1 };
		stage[1][3] = { 1 };
		stage[1][5] = { 1 };
		stage[2][0] = { 1 };
		stage[2][1] = { 1 };
		stage[2][2] = { 1 };
		stage[2][3] = { 1 };
		stage[2][5] = { 1 };
		stage[3][0] = { 1 };
		stage[3][5] = { 1 };
		stage[3][6] = { 1 };
		stage[3][7] = { 1 };
		stage[4][0] = { 1 };
		stage[4][1] = { 1 };
		stage[4][2] = { 1 };
		stage[4][7] = { 1 };
		stage[5][2] = { 1 };
		stage[5][4] = { 1 };
		stage[5][5] = { 1 };
		stage[5][6] = { 1 };
		stage[5][7] = { 1 };
		stage[6][2] = { 1 };
		stage[6][4] = { 1 };
		stage[7][2] = { 1 };
		stage[7][3] = { 1 };
		stage[7][4] = { 1 };
	}  

	//게임시작
	while (gamestate)
	{
		Clear();

		//스테이지 벽 출력
		for (int i = 0; i < 20; i++)
		{
			GotoXY((WIDTH * 2) / 3, i);
			printf("■");
		}

		//스테이지 출력
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (stage[i][j] == 1)
				{
					GotoXY(2 * i, j);
					printf("■");
				}
			}
		}

		for (int i = 0; i < 10; i++)
		{
			if (g_stKey[i].bActive)
			{
				GotoXY(g_stKey[i].x*2, g_stKey[i].y);
				printf("♥");
			}
		}



		//방향키 제어 설정
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) //왼쪽방향키
		{
			g_stPlayer.x--;
			if (stage[g_stPlayer.x][g_stPlayer.y] == 1) g_stPlayer.x++;		//맵안에서 나갈수없음
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) //오른쪽방향키
		{
			g_stPlayer.x++;
			if (stage[g_stPlayer.x][g_stPlayer.y] == 1) g_stPlayer.x--;		//맵안에서 나갈수없음
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000) //위쪽방향키
		{
			g_stPlayer.y--;
			if (stage[g_stPlayer.x][g_stPlayer.y] == 1) g_stPlayer.y++;		//맵안에서 나갈수없음
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000) //아래쪽방향키
		{
			g_stPlayer.y++;
			if (stage[g_stPlayer.x][g_stPlayer.y] == 1) g_stPlayer.y--;		//맵안에서 나갈수없음
		}

		//플레이어 출력
		GotoXY(g_stPlayer.x * 2, g_stPlayer.y);
		printf("★");

		Sleep(50);
	}

	return 0;
}