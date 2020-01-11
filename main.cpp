#include <stdio.h>
#include <windows.h>
#include "Console.h"
#include <conio.h>


#define WIDTH 60
#define LENGTH 20


int stage[20][20] = { 0 };	//스테이지 맵 배열 선언


struct ST_OBJECT
{
	int x;
	int y;
	int clearpoint;
	bool bActive;
};


ST_OBJECT g_stPlayer;
ST_OBJECT g_stKey[10] = { 0 };
ST_OBJECT g_stLock[10] = { 0 };

int SumClearPoint() {
	int a = 0;
	for (int i = 0; i < g_stPlayer.clearpoint; i++)
	{
		a = a + g_stKey[i].clearpoint;
	}
	return a;
}


int main() {
	SetConsoleSize(WIDTH, LENGTH);	//콘솔창 크기 변경

	bool gamestate = false;	//게임진행여부
	int clear = 0;	//클리어 변수
	int stagephase = 0; //스테이지 단계


	bool stage_bActive[100] = { false };//스테이지 단계 선언

	//게임시작
	gamestate = true;


	while (gamestate)
	{
		//스테이지 시작
		stage_bActive[stagephase] = true;

		//
		clear = 0;

		//스테이지 맵 좌표 초기화
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				stage[i][j] = 0;
			}
		}

		//열쇠, 자물쇠 좌표 초기화
		for (int i = 0; i < 10; i++)
		{
			g_stKey[i].x = 0;
			g_stKey[i].y = 0;
			g_stKey[i].clearpoint = 0;
			g_stLock[i].x = 0;
			g_stLock[i].y = 0;
		}

		//각 스테이지 초기화
		//스테이지 1 초기화 
		if (stage_bActive[0])
		{
			//플레이어 좌표 설정
			g_stPlayer.x = 4;
			g_stPlayer.y = 4;
			g_stPlayer.bActive = true;

			//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
			g_stPlayer.clearpoint = 4;

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

			//자물쇠 좌표 설정
			g_stLock[0].x = 1;
			g_stLock[0].y = 4;
			g_stLock[0].bActive = true;

			g_stLock[1].x = 3;
			g_stLock[1].y = 1;
			g_stLock[1].bActive = true;

			g_stLock[2].x = 4;
			g_stLock[2].y = 6;
			g_stLock[2].bActive = true;

			g_stLock[3].x = 6;
			g_stLock[3].y = 3;
			g_stLock[3].bActive = true;

			//스테이지 벽 좌표 설정
			
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
		//스테이지 2 초기화
		if (stage_bActive[1])
		{
			//플레이어 좌표 설정
			g_stPlayer.x = 1;
			g_stPlayer.y = 1;
			g_stPlayer.bActive = true;

			//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
			g_stPlayer.clearpoint = 3;

			//열쇠 좌표 설정
			g_stKey[0].x = 2;
			g_stKey[0].y = 2;
			g_stKey[0].bActive = true;

			g_stKey[1].x = 3;
			g_stKey[1].y = 2;
			g_stKey[1].bActive = true;

			g_stKey[2].x = 2;
			g_stKey[2].y = 3;
			g_stKey[2].bActive = true;

			//자물쇠 좌표 설정
			g_stLock[0].x = 7;
			g_stLock[0].y = 3;
			g_stLock[0].bActive = true;

			g_stLock[1].x = 7;
			g_stLock[1].y = 4;
			g_stLock[1].bActive = true;

			g_stLock[2].x = 7;
			g_stLock[2].y = 5;
			g_stLock[2].bActive = true;

			//스테이지 벽 좌표 설정
			stage[0][0] = { 1 };
			stage[0][1] = { 1 };
			stage[0][2] = { 1 };
			stage[0][3] = { 1 };
			stage[0][4] = { 1 };
			stage[1][0] = { 1 };
			stage[1][4] = { 1 };
			stage[1][5] = { 1 };
			stage[1][6] = { 1 };
			stage[1][7] = { 1 };
			stage[1][8] = { 1 };
			stage[2][0] = { 1 };
			stage[2][4] = { 1 };
			stage[2][5] = { 1 };
			stage[2][8] = { 1 };
			stage[3][0] = { 1 };
			stage[3][8] = { 1 };
			stage[4][0] = { 1 };
			stage[4][1] = { 1 };
			stage[4][2] = { 1 };
			stage[4][3] = { 1 };
			stage[4][4] = { 1 };
			stage[4][8] = { 1 };
			stage[5][4] = { 1 };
			stage[5][6] = { 1 };
			stage[5][7] = { 1 };
			stage[5][8] = { 1 };
			stage[6][2] = { 1 };
			stage[6][3] = { 1 };
			stage[6][4] = { 1 };
			stage[6][7] = { 1 };
			stage[7][2] = { 1 };
			stage[7][7] = { 1 };
			stage[8][2] = { 1 };
			stage[8][3] = { 1 };
			stage[8][4] = { 1 };
			stage[8][5] = { 1 };
			stage[8][6] = { 1 };
			stage[8][7] = { 1 };
		}
		//스테이지 3 초기화
		if (stage_bActive[2])
		{
			//플레이어 좌표 설정
			g_stPlayer.x = 2;
			g_stPlayer.y = 3;
			g_stPlayer.bActive = true;

			//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
			g_stPlayer.clearpoint = 4;

			//열쇠 좌표 설정
			g_stKey[0].x = 2;
			g_stKey[0].y = 2;
			g_stKey[0].bActive = true;

			g_stKey[1].x = 4;
			g_stKey[1].y = 3;
			g_stKey[1].bActive = true;

			g_stKey[2].x = 6;
			g_stKey[2].y = 4;
			g_stKey[2].bActive = true;

			g_stKey[3].x = 7;
			g_stKey[3].y = 3;
			g_stKey[3].bActive = true;


			//자물쇠 좌표 설정
			g_stLock[0].x = 2;
			g_stLock[0].y = 4;
			g_stLock[0].bActive = true;

			g_stLock[1].x = 2;
			g_stLock[1].y = 5;
			g_stLock[1].bActive = true;

			g_stLock[2].x = 3;
			g_stLock[2].y = 4;
			g_stLock[2].bActive = true;

			g_stLock[3].x = 3;
			g_stLock[3].y = 5;
			g_stLock[3].bActive = true;

			//스테이지 벽 좌표 설정
			stage[0][2] = { 1 };
			stage[0][3] = { 1 };
			stage[0][4] = { 1 };
			stage[0][5] = { 1 };
			stage[1][0] = { 1 };
			stage[1][1] = { 1 };
			stage[1][2] = { 1 };
			stage[1][5] = { 1 };
			stage[1][6] = { 1 };
			stage[2][0] = { 1 };
			stage[2][6] = { 1 };
			stage[3][0] = { 1 };
			stage[3][2] = { 1 };
			stage[3][6] = { 1 };
			stage[4][0] = { 1 };
			stage[4][2] = { 1 };
			stage[4][4] = { 1 };
			stage[4][5] = { 1 };
			stage[4][6] = { 1 };
			stage[5][0] = { 1 };
			stage[5][2] = { 1 };
			stage[5][6] = { 1 };
			stage[6][0] = { 1 };
			stage[6][6] = { 1 };
			stage[7][0] = { 1 };
			stage[7][1] = { 1 };
			stage[7][6] = { 1 };
			stage[8][1] = { 1 };
			stage[8][4] = { 1 };
			stage[8][5] = { 1 };
			stage[8][6] = { 1 };
			stage[9][1] = { 1 };
			stage[9][2] = { 1 };
			stage[9][3] = { 1 };
			stage[9][4] = { 1 };
		}



		//게임시작
		while (gamestate)
		{
			Clear();

			//게임 구역 출력
			for (int i = 0; i < 20; i++)
			{
				GotoXY((WIDTH * 2) / 3, i);
				printf("■");
			}

			//'r'설명
			GotoXY((WIDTH * 2) / 3 + 2, 2);
			printf("If you want reset");
			GotoXY((WIDTH * 2) / 3 + 2, 3);
			printf("press 'R'");
			GotoXY((WIDTH * 2) / 3 + 2, 5);
			printf("Control: ←↑↓→");
			GotoXY((WIDTH * 2) / 3 + 2, 7);
			printf("Move ♥ to ♡");


			//스테이지 단계별 맵 출력
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


			//방향키 제어 설정
			if (GetAsyncKeyState(VK_LEFT) & 0x8000) //왼쪽방향키
			{
				g_stPlayer.x--;
				if (stage[g_stPlayer.x][g_stPlayer.y] == 1) g_stPlayer.x++;		//맵밖으로 나갈수없음

				for (int i = 0; i < 10; i++)		//열쇠를 밀었을때 
				{
					if (g_stPlayer.x == g_stKey[i].x)
					{
						if (g_stPlayer.y == g_stKey[i].y)
						{
							g_stKey[i].x--;
							if (stage[g_stKey[i].x][g_stKey[i].y] == 1)	//열쇠도 맵밖으로 나갈수없음
							{
								g_stKey[i].x++;
								g_stPlayer.x++;
							}
						}
					}
				}
					
				if (g_stKey[0].x == g_stKey[1].x)		//겹치지 않게
				{
					if (g_stKey[0].y == g_stKey[1].y)
					{
						g_stKey[0].x++;
						g_stPlayer.x++;
					}
				}
				if (g_stKey[0].x == g_stKey[2].x)
				{
					if (g_stKey[0].y == g_stKey[2].y)
					{
						g_stKey[0].x++;
						g_stPlayer.x++;
					}
				}
				if (g_stKey[0].x == g_stKey[3].x)
				{
					if (g_stKey[0].y == g_stKey[3].y)
					{
						g_stKey[0].x++;
						g_stPlayer.x++;
					}
				}


				if (g_stKey[1].x == g_stKey[0].x)		//겹치지 않게
				{
					if (g_stKey[1].y == g_stKey[0].y)
					{
						g_stKey[1].x++;
						g_stPlayer.x++;
					}
				}
				if (g_stKey[1].x == g_stKey[2].x)		
				{
					if (g_stKey[1].y == g_stKey[2].y)
					{
						g_stKey[1].x++;
						g_stPlayer.x++;
					}
				}
				if (g_stKey[1].x == g_stKey[3].x)		
				{
					if (g_stKey[1].y == g_stKey[3].y)
					{
						g_stKey[1].x++;
						g_stPlayer.x++;
					}
				}

				if (g_stKey[2].x == g_stKey[0].x)		//겹치지 않게
				{
					if (g_stKey[2].y == g_stKey[0].y)
					{
						g_stKey[2].x++;
						g_stPlayer.x++;
					}
				}
				if (g_stKey[2].x == g_stKey[1].x)		
				{
					if (g_stKey[2].y == g_stKey[1].y)
					{
						g_stKey[2].x++;
						g_stPlayer.x++;
					}
				}
				if (g_stKey[2].x == g_stKey[3].x)
				{
					if (g_stKey[2].y == g_stKey[3].y)
					{
						g_stKey[2].x++;
						g_stPlayer.x++;
					}
				}

				if (g_stKey[3].x == g_stKey[0].x)		//겹치지 않게
				{
					if (g_stKey[3].y == g_stKey[0].y)
					{
						g_stKey[3].x++;
						g_stPlayer.x++;
					}
				}
				if (g_stKey[3].x == g_stKey[1].x)		
				{
					if (g_stKey[3].y == g_stKey[1].y)
					{
						g_stKey[3].x++;
						g_stPlayer.x++;
					}
				}
				if (g_stKey[3].x == g_stKey[2].x)		
				{
					if (g_stKey[3].y == g_stKey[2].y)
					{
						g_stKey[3].x++;
						g_stPlayer.x++;
					}
				}
			}

			if (GetAsyncKeyState(VK_RIGHT) & 0x8000) //오른쪽방향키
			{
				g_stPlayer.x++;
				if (stage[g_stPlayer.x][g_stPlayer.y] == 1) g_stPlayer.x--;		//맵밖으로 나갈수없음

				for (int i = 0; i < 10; i++)		//열쇠를 밀었을때 
				{
					if (g_stKey[i].bActive)
					{
						if (g_stPlayer.x == g_stKey[i].x)
						{
							if (g_stPlayer.y == g_stKey[i].y)
							{
								g_stKey[i].x++;
								if (stage[g_stKey[i].x][g_stKey[i].y] == 1)	//열쇠도 맵밖으로 나갈수없음
								{
									g_stKey[i].x--;
									g_stPlayer.x--;
								}
							}
						}
					}
				}

				if (g_stKey[0].x == g_stKey[1].x)		//겹치지 않게
				{
					if (g_stKey[0].y == g_stKey[1].y)
					{
						g_stKey[0].x--;
						g_stPlayer.x--;
					}
				}
				if (g_stKey[0].x == g_stKey[2].x)
				{
					if (g_stKey[0].y == g_stKey[2].y)
					{
						g_stKey[0].x--;
						g_stPlayer.x--;
					}
				}
				if (g_stKey[0].x == g_stKey[3].x)
				{
					if (g_stKey[0].y == g_stKey[3].y)
					{
						g_stKey[0].x--;
						g_stPlayer.x--;
					}
				}


				if (g_stKey[1].x == g_stKey[0].x)		//겹치지 않게
				{
					if (g_stKey[1].y == g_stKey[0].y)
					{
						g_stKey[1].x--;
						g_stPlayer.x--;
					}
				}
				if (g_stKey[1].x == g_stKey[2].x)
				{
					if (g_stKey[1].y == g_stKey[2].y)
					{
						g_stKey[1].x--;
						g_stPlayer.x--;
					}
				}
				if (g_stKey[1].x == g_stKey[3].x)
				{
					if (g_stKey[1].y == g_stKey[3].y)
					{
						g_stKey[1].x--;
						g_stPlayer.x--;
					}
				}

				if (g_stKey[2].x == g_stKey[0].x)		//겹치지 않게
				{
					if (g_stKey[2].y == g_stKey[0].y)
					{
						g_stKey[2].x--;
						g_stPlayer.x--;
					}
				}
				if (g_stKey[2].x == g_stKey[1].x)
				{
					if (g_stKey[2].y == g_stKey[1].y)
					{
						g_stKey[2].x--;
						g_stPlayer.x--;
					}
				}
				if (g_stKey[2].x == g_stKey[3].x)
				{
					if (g_stKey[2].y == g_stKey[3].y)
					{
						g_stKey[2].x--;
						g_stPlayer.x--;
					}
				}

				if (g_stKey[3].x == g_stKey[0].x)		//겹치지 않게
				{
					if (g_stKey[3].y == g_stKey[0].y)
					{
						g_stKey[3].x--;
						g_stPlayer.x--;
					}
				}
				if (g_stKey[3].x == g_stKey[1].x)
				{
					if (g_stKey[3].y == g_stKey[1].y)
					{
						g_stKey[3].x--;
						g_stPlayer.x--;
					}
				}
				if (g_stKey[3].x == g_stKey[2].x)
				{
					if (g_stKey[3].y == g_stKey[2].y)
					{
						g_stKey[3].x--;
						g_stPlayer.x--;
					}
				}
			}

			if (GetAsyncKeyState(VK_UP) & 0x8000) //위쪽방향키
			{
				g_stPlayer.y--;
				if (stage[g_stPlayer.x][g_stPlayer.y] == 1) g_stPlayer.y++;		//맵밖으로 나갈수없음

				for (int i = 0; i < 10; i++)		//열쇠를 밀었을때 
				{
					if (g_stKey[i].bActive)
					{
						if (g_stPlayer.x == g_stKey[i].x)
						{
							if (g_stPlayer.y == g_stKey[i].y)
							{
								g_stKey[i].y--;
								if (stage[g_stKey[i].x][g_stKey[i].y] == 1)	//열쇠도 맵밖으로 나갈수없음
								{
									g_stKey[i].y++;
									g_stPlayer.y++;
								}
							}
						}
					}
				}
				if (g_stKey[0].x == g_stKey[1].x)		//겹치지 않게
				{
					if (g_stKey[0].y == g_stKey[1].y)
					{
						g_stKey[0].y++;
						g_stPlayer.y++;
					}
				}
				if (g_stKey[0].x == g_stKey[2].x)
				{
					if (g_stKey[0].y == g_stKey[2].y)
					{
						g_stKey[0].y++;
						g_stPlayer.y++;
					}
				}
				if (g_stKey[0].x == g_stKey[3].x)
				{
					if (g_stKey[0].y == g_stKey[3].y)
					{
						g_stKey[0].y++;
						g_stPlayer.y++;
					}
				}


				if (g_stKey[1].x == g_stKey[0].x)		//겹치지 않게
				{
					if (g_stKey[1].y == g_stKey[0].y)
					{
						g_stKey[1].y++;
						g_stPlayer.y++;
					}
				}
				if (g_stKey[1].x == g_stKey[2].x)
				{
					if (g_stKey[1].y == g_stKey[2].y)
					{
						g_stKey[1].y++;
						g_stPlayer.y++;
					}
				}
				if (g_stKey[1].x == g_stKey[3].x)
				{
					if (g_stKey[1].y == g_stKey[3].y)
					{
						g_stKey[1].y++;
						g_stPlayer.y++;
					}
				}

				if (g_stKey[2].x == g_stKey[0].x)		//겹치지 않게
				{
					if (g_stKey[2].y == g_stKey[0].y)
					{
						g_stKey[2].y++;
						g_stPlayer.y++;
					}
				}
				if (g_stKey[2].x == g_stKey[1].x)
				{
					if (g_stKey[2].y == g_stKey[1].y)
					{
						g_stKey[2].y++;
						g_stPlayer.y++;
					}
				}
				if (g_stKey[2].x == g_stKey[3].x)
				{
					if (g_stKey[2].y == g_stKey[3].y)
					{
						g_stKey[2].y++;
						g_stPlayer.y++;
					}
				}

				if (g_stKey[3].x == g_stKey[0].x)		//겹치지 않게
				{
					if (g_stKey[3].y == g_stKey[0].y)
					{
						g_stKey[3].y++;
						g_stPlayer.y++;
					}
				}
				if (g_stKey[3].x == g_stKey[1].x)
				{
					if (g_stKey[3].y == g_stKey[1].y)
					{
						g_stKey[3].y++;
						g_stPlayer.y++;
					}
				}
				if (g_stKey[3].x == g_stKey[2].x)
				{
					if (g_stKey[3].y == g_stKey[2].y)
					{
						g_stKey[3].y++;
						g_stPlayer.y++;
					}
				}
			}

			if (GetAsyncKeyState(VK_DOWN) & 0x8000) //아래쪽방향키
			{
				g_stPlayer.y++;
				if (stage[g_stPlayer.x][g_stPlayer.y] == 1) g_stPlayer.y--;		//맵밖으로 나갈수없음

				for (int i = 0; i < 10; i++)		//열쇠를 밀었을때 
				{
					if (g_stKey[i].bActive)
					{
						if (g_stPlayer.x == g_stKey[i].x)
						{
							if (g_stPlayer.y == g_stKey[i].y)
							{
								g_stKey[i].y++;
								if (stage[g_stKey[i].x][g_stKey[i].y] == 1)	//열쇠도 맵밖으로 나갈수없음
								{
									g_stKey[i].y--;
									g_stPlayer.y--;
								}
							}
						}
					}
				}
				if (g_stKey[0].x == g_stKey[1].x)		//겹치지 않게
				{
					if (g_stKey[0].y == g_stKey[1].y)
					{
						g_stKey[0].y--;
						g_stPlayer.y--;
					}
				}
				if (g_stKey[0].x == g_stKey[2].x)
				{
					if (g_stKey[0].y == g_stKey[2].y)
					{
						g_stKey[0].y--;
						g_stPlayer.y--;
					}
				}
				if (g_stKey[0].x == g_stKey[3].x)
				{
					if (g_stKey[0].y == g_stKey[3].y)
					{
						g_stKey[0].y--;
						g_stPlayer.y--;
					}
				}


				if (g_stKey[1].x == g_stKey[0].x)		//겹치지 않게
				{
					if (g_stKey[1].y == g_stKey[0].y)
					{
						g_stKey[1].y--;
						g_stPlayer.y--;
					}
				}
				if (g_stKey[1].x == g_stKey[2].x)
				{
					if (g_stKey[1].y == g_stKey[2].y)
					{
						g_stKey[1].y--;
						g_stPlayer.y--;
					}
				}
				if (g_stKey[1].x == g_stKey[3].x)
				{
					if (g_stKey[1].y == g_stKey[3].y)
					{
						g_stKey[1].y--;
						g_stPlayer.y--;
					}
				}

				if (g_stKey[2].x == g_stKey[0].x)		//겹치지 않게
				{
					if (g_stKey[2].y == g_stKey[0].y)
					{
						g_stKey[2].y--;
						g_stPlayer.y--;
					}
				}
				if (g_stKey[2].x == g_stKey[1].x)
				{
					if (g_stKey[2].y == g_stKey[1].y)
					{
						g_stKey[2].y--;
						g_stPlayer.y--;
					}
				}
				if (g_stKey[2].x == g_stKey[3].x)
				{
					if (g_stKey[2].y == g_stKey[3].y)
					{
						g_stKey[2].y--;
						g_stPlayer.y--;
					}
				}

				if (g_stKey[3].x == g_stKey[0].x)		//겹치지 않게
				{
					if (g_stKey[3].y == g_stKey[0].y)
					{
						g_stKey[3].y--;
						g_stPlayer.y--;
					}
				}
				if (g_stKey[3].x == g_stKey[1].x)
				{
					if (g_stKey[3].y == g_stKey[1].y)
					{
						g_stKey[3].y--;
						g_stPlayer.y--;
					}
				}
				if (g_stKey[3].x == g_stKey[2].x)
				{
					if (g_stKey[3].y == g_stKey[2].y)
					{
						g_stKey[3].y--;
						g_stPlayer.y--;
					}
				}
			}

			if (GetAsyncKeyState('R') & 0x8000)
			{
				break;
			}

			//자물쇠 출력
			for (int i = 0; i < g_stPlayer.clearpoint; i++)
			{
				if (g_stLock[i].bActive)
				{
					GotoXY(g_stLock[i].x * 2, g_stLock[i].y);
					printf("♡");
				}
			}


			//열쇠 출력
			for (int i = 0; i < g_stPlayer.clearpoint; i++)
			{
				if (g_stKey[i].bActive)
				{
					GotoXY(g_stKey[i].x * 2, g_stKey[i].y);
					printf("♥");
				}
			}


			//플레이어 출력
			if (g_stPlayer.bActive)
			{
				GotoXY(g_stPlayer.x * 2, g_stPlayer.y);
				printf("★");
			}


			//스테이지 클리어 과정
			for (int i = 0; i < g_stPlayer.clearpoint; i++)
			{
				for (int j = 0; j < g_stPlayer.clearpoint; j++)
				{
					if (g_stKey[i].x == g_stLock[j].x)
					{
						if (g_stKey[i].y == g_stLock[j].y)
						{
							g_stKey[i].clearpoint = 1;
						}
						else
						{
							g_stKey[i].clearpoint = 0;
						}
					}
				}
			}

			clear = SumClearPoint();

			if (g_stPlayer.clearpoint == clear)
			{
				stage_bActive[stagephase] = false;
				stagephase++;
				break;
			}

			Sleep(70);
		}
	}

	return 0;
}