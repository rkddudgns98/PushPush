#include <stdio.h>
#include <windows.h>
#include <conio.h>
#pragma warning(disable: 4996)

//콘솔창 크기
#define WIDTH 60
#define LENGTH 20

#define STAGE_MAX 25

//배경색, 텍스트색 표현
int BackColor = 0;
int TextColor = 7;


int stage[20][20] = { 0 };	//스테이지 맵 배열 선언
bool gamestate = false;	//게임진행여부
bool stagestate = false;	//게임진행여부
int clear = 0;	//클리어 변수
int stagephase = 0; //스테이지 단계
bool stage_bActive[100] = { false };//스테이지 단계 진행여부 선언


//오브젝트 구조체 정의
struct ST_OBJECT
{
	int x;
	int y;
	int clearpoint;
	bool bActive;
};

//오브젝트 생성
ST_OBJECT g_stPlayer;
ST_OBJECT g_stKey[10];
ST_OBJECT g_stLock[10];

//커서 좌표 설정 함수
void GotoXY(int _x, int _y)
{
	COORD pos = { _x, _y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//색 설정 함수
void SetColor(unsigned char _BgColor, unsigned char _TextColor)
{
	if (_BgColor > 15 || _TextColor > 15) return;

	unsigned short ColorNum = (_BgColor << 4) | _TextColor;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ColorNum);
}
//콘솔사이즈 설정함수
void SetConsoleSize(int _col, int _lines)
{
	char setText[100];
	sprintf_s(setText, "mode con cols=%d lines=%d", _col, _lines);
	system(setText);
}


//열쇠가 서로 겹치지 않게
void KeyOverLapingLeftBase(int a,int clearpoint)
{
	for (int i = 0; i < a; i++)
	{
		if (g_stKey[a].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[a].y == g_stKey[i].y)
			{
				g_stKey[a].x++;
				g_stPlayer.x++;
			}
		}
	}
	for (int i = a+1; i < clearpoint; i++)
	{
		if (g_stKey[a].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[a].y == g_stKey[i].y)
			{
				g_stKey[a].x++;
				g_stPlayer.x++;
			}
		}
	}
}
void KeyOverLapingRightBase(int a,int count)
{
	for (int i = 0; i < a; i++)
	{
		if (g_stKey[a].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[a].y == g_stKey[i].y)
			{
				g_stKey[a].x--;
				g_stPlayer.x--;
			}
		}
	}
	for (int i = a+1; i < count; i++)
	{
		if (g_stKey[a].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[a].y == g_stKey[i].y)
			{
				g_stKey[a].x--;
				g_stPlayer.x--;
			}
		}
	}
}
void KeyOverLapingDownBase(int a,int count)
{
	for (int i = 0; i < a; i++)
	{
		if (g_stKey[a].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[a].y == g_stKey[i].y)
			{
				g_stKey[a].y--;
				g_stPlayer.y--;
			}
		}
	}
	for (int i = a+1; i < count; i++)
	{
		if (g_stKey[a].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[a].y == g_stKey[i].y)
			{
				g_stKey[a].y--;
				g_stPlayer.y--;
			}
		}
	}
}
void KeyOverLapingUpBase(int a, int count)
{
	for (int i = 0; i < a; i++)
	{
		if (g_stKey[a].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[a].y == g_stKey[i].y)
			{
				g_stKey[a].y++;
				g_stPlayer.y++;
			}
		}
	}
	for (int i = a+1; i < count; i++)
	{
		if (g_stKey[a].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[a].y == g_stKey[i].y)
			{
				g_stKey[a].y++;
				g_stPlayer.y++;
			}
		}
	}
}

void KeyOverLapingLeft(int clearpoint)
{
	for (int i = 0; i < 10; i++)
	{
		if (clearpoint > i)
			KeyOverLapingLeftBase(i, clearpoint);
	}
}
void KeyOverLapingRight(int clearpoint)
{
	for (int i = 0; i < 10; i++)
	{
		if (clearpoint > i)
			KeyOverLapingRightBase(i, clearpoint);
	}
}
void KeyOverLapingUp(int clearpoint)
{
	for (int i = 0; i < 10; i++)
	{
		if (clearpoint > i)
			KeyOverLapingUpBase(i, clearpoint);
	}
}
void KeyOverLapingDown(int clearpoint)
{
	for (int i = 0; i < 10; i++)
	{
		if (clearpoint > i)
			KeyOverLapingDownBase(i, clearpoint);
	}
}

//시작메뉴
void StartMenu()
{
	//콘솔창 크기 설정
	SetConsoleSize(WIDTH, LENGTH);


	while (1) {
		system("cls");
		GotoXY(2, 2);
		printf("#Push Push Game");
		GotoXY(2, 4);
		printf("#Enter Stage: ");

		//스테이지를 입력받음, stagephase는 0부터 시작하므로 -1을 해준 것
		scanf("%d", &stagephase);
		stagephase--;

		//잘못된 스테이지 입력시 1라운드부터 시작할지 게임을 종료할지
		if (stagephase >= STAGE_MAX || stagephase < 0)
		{
			while (1)
			{
				system("cls");

				GotoXY(2, 2);
				printf("#%d stage is the last", STAGE_MAX);

				GotoXY(2, 4);
				printf("#Start Stage 1? Y/N");

				if (GetAsyncKeyState('Y') & 0x8000)
				{
					stagephase = 0;
					break;
				}

				if (GetAsyncKeyState('N') & 0x8000)
				{
					stagephase = -1;
					break;
				}

				Sleep(50);
			}
		}

		//스테이지 설정이 종료되었으면 게임시작
		if (stagephase >= 0)
		{
			//게임시작
			gamestate = true;
			break;
		}
		//스테이지 설정이 취소되었으면 게임종료
		if (stagephase < 0)
		{
			//게임종료
			gamestate = false;
			break;
		}
		
		Sleep(50);
	}
}

//초기화 설정 함수
void Init()
{
	//스테이지 활성화
	stagestate = true;

	//해당 스테이지 시작
	stage_bActive[stagephase] = true;

	//클리어 변수 초기화
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

}


//스테이지 초기화 설정 함수
//플레이어 좌표 설정함수, 클리어 변수 설정(열쇠,자물쇠의 개수와 같음)
void InitStagePlayer(int clearpoint, int x, int y)	//clearpoint, x,y좌표
{
	g_stPlayer.x = x;
	g_stPlayer.y = y;
	g_stPlayer.bActive = true;
	g_stPlayer.clearpoint = clearpoint;
}
//열쇠 좌표 설정함수
void InitStageKey(int i,int x, int y)	//몇번째 key, x,y좌표
{
	g_stKey[i].x = x;
	g_stKey[i].y = y;
	g_stKey[i].bActive = true;
}
//자물쇠 좌표 설정함수
void InitStageLock(int i, int x, int y)	//몇번째 Lock, x,y좌표
{
	g_stLock[i].x = x;
	g_stLock[i].y = y;
	g_stLock[i].bActive = true;
}
//각스테이지 초기화
void InitStage()
{
	//각 스테이지 초기화
	//스테이지 1 초기화 
	if (stage_bActive[0])
	{
		//플레이어 좌표 설정
		InitStagePlayer(4, 4, 4);

		//열쇠 좌표 설정
		InitStageKey(0, 3, 3);
		InitStageKey(1, 3, 4);
		InitStageKey(2, 4, 5);
		InitStageKey(3, 5, 3);

		//자물쇠 좌표 설정
		InitStageLock(0, 1, 4);
		InitStageLock(1, 3, 1);
		InitStageLock(2, 4, 6);
		InitStageLock(3, 6, 3);

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
		InitStagePlayer(3, 1, 1);

		//열쇠 좌표 설정
		InitStageKey(0, 2, 2);
		InitStageKey(1, 3, 2);
		InitStageKey(2, 2, 3);

		//자물쇠 좌표 설정
		InitStageLock(0, 7, 3);
		InitStageLock(1, 7, 4);
		InitStageLock(2, 7, 5);
		
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
		InitStagePlayer(4, 2, 3);

		//열쇠 좌표 설정
		InitStageKey(0, 2, 2);
		InitStageKey(1, 4, 3);
		InitStageKey(2, 6, 4);
		InitStageKey(3, 7, 3);

		//자물쇠 좌표 설정
		InitStageLock(0, 2, 4);
		InitStageLock(1, 2, 5);
		InitStageLock(2, 3, 4);
		InitStageLock(3, 3, 5);

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
	//스테이지 4 초기화
	if (stage_bActive[3])
	{
		//플레이어 좌표 설정
		InitStagePlayer(5, 1, 2);

		//열쇠 좌표 설정
		InitStageKey(0, 2, 2);
		InitStageKey(1, 2, 3);
		InitStageKey(2, 2, 5);
		InitStageKey(3, 3, 4);
		InitStageKey(4, 3, 6);
	
		//자물쇠 좌표 설정
		InitStageLock(0, 1, 5);
		InitStageLock(1, 1, 6);
		InitStageLock(2, 2, 6);
		InitStageLock(3, 3, 6);
		InitStageLock(3, 4, 6);
		
		//스테이지 벽 좌표 설정
		stage[0][1] = { 1 };
		stage[0][2] = { 1 };
		stage[0][3] = { 1 };
		stage[0][4] = { 1 };
		stage[0][5] = { 1 };
		stage[0][6] = { 1 };
		stage[0][7] = { 1 };
		stage[1][0] = { 1 };
		stage[1][1] = { 1 };
		stage[1][3] = { 1 };
		stage[1][4] = { 1 };
		stage[1][7] = { 1 };
		stage[2][0] = { 1 };
		stage[2][7] = { 1 };
		stage[3][0] = { 1 };
		stage[3][7] = { 1 };
		stage[4][0] = { 1 };
		stage[4][1] = { 1 };
		stage[4][2] = { 1 };
		stage[4][3] = { 1 };
		stage[4][7] = { 1 };
		stage[5][3] = { 1 };
		stage[5][4] = { 1 };
		stage[5][5] = { 1 };
		stage[5][6] = { 1 };
		stage[5][7] = { 1 };
	}
	//스테이지 5 초기화
	if (stage_bActive[4])
	{
		//플레이어 좌표 설정
		InitStagePlayer(3, 2, 1);

		//열쇠 좌표 설정
		InitStageKey(0, 3, 2);
		InitStageKey(1, 2, 5);
		InitStageKey(2, 5, 6);

		//자물쇠 좌표 설정
		InitStageLock(0, 1, 4);
		InitStageLock(1, 1, 5);
		InitStageLock(2, 1, 6);

		//스테이지 벽 좌표 설정
		stage[0][3] = { 1 };
		stage[0][4] = { 1 };
		stage[0][5] = { 1 };
		stage[0][6] = { 1 };
		stage[0][7] = { 1 };
		stage[1][0] = { 1 };
		stage[1][1] = { 1 };
		stage[1][2] = { 1 };
		stage[1][3] = { 1 };
		stage[1][7] = { 1 };
		stage[2][0] = { 1 };
		stage[2][3] = { 1 };
		stage[2][4] = { 1 };
		stage[2][7] = { 1 };
		stage[3][0] = { 1 };
		stage[3][7] = { 1 };
		stage[4][0] = { 1 };
		stage[4][1] = { 1 };
		stage[4][3] = { 1 };
		stage[4][4] = { 1 };
		stage[4][7] = { 1 };
		stage[5][0] = { 1 };
		stage[5][1] = { 1 };
		stage[5][5] = { 1 };
		stage[5][7] = { 1 };
		stage[6][1] = { 1 };
		stage[6][2] = { 1 };
		stage[6][3] = { 1 };
		stage[6][7] = { 1 };
		stage[7][3] = { 1 };
		stage[7][4] = { 1 };
		stage[7][5] = { 1 };
		stage[7][6] = { 1 };
		stage[7][7] = { 1 };
	}
	//스테이지 6 초기화
	if (stage_bActive[5])
	{
		//플레이어 좌표 설정
		InitStagePlayer(5, 8, 1);

		//열쇠 좌표 설정
		InitStageKey(0, 3, 3);
		InitStageKey(1, 4, 4);
		InitStageKey(2, 4, 5);
		InitStageKey(3, 5, 3);
		InitStageKey(4, 7, 3);

		//자물쇠 좌표 설정
		InitStageLock(0, 1, 6);
		InitStageLock(1, 2, 6);
		InitStageLock(2, 3, 6);
		InitStageLock(3, 4, 6);
		InitStageLock(4, 5, 6);
		
		//스테이지 벽 좌표 설정
		stage[0][5] = { 1 };
		stage[0][6] = { 1 };
		stage[0][7] = { 1 };
		stage[1][5] = { 1 };
		stage[1][7] = { 1 };
		stage[2][1] = { 1 };
		stage[2][2] = { 1 };
		stage[2][3] = { 1 };
		stage[2][4] = { 1 };
		stage[2][5] = { 1 };
		stage[2][7] = { 1 };
		stage[3][0] = { 1 };
		stage[3][1] = { 1 };
		stage[3][7] = { 1 };
		stage[4][0] = { 1 };
		stage[4][7] = { 1 };
		stage[5][0] = { 1 };
		stage[5][4] = { 1 };
		stage[5][7] = { 1 };
		stage[6][0] = { 1 };
		stage[6][1] = { 1 };
		stage[6][2] = { 1 };
		stage[6][4] = { 1 };
		stage[6][5] = { 1 };
		stage[6][7] = { 1 };
		stage[7][0] = { 1 };
		stage[7][7] = { 1 };
		stage[8][0] = { 1 };
		stage[8][5] = { 1 };
		stage[8][6] = { 1 };
		stage[8][7] = { 1 };
		stage[9][0] = { 1 };
		stage[9][1] = { 1 };
		stage[9][2] = { 1 };
		stage[9][3] = { 1 };
		stage[9][4] = { 1 };
		stage[9][5] = { 1 };
		stage[9][7] = { 1 };
	}
	//스테이지 7 초기화
	if (stage_bActive[6])
	{
		//플레이어 좌표 설정
		InitStagePlayer(5, 8, 3);

		//열쇠 좌표 설정
		InitStageKey(0, 3, 3);
		InitStageKey(1, 4, 2);
		InitStageKey(2, 4, 4);
		InitStageKey(3, 5, 3);
		InitStageKey(4, 6, 4);

		//자물쇠 좌표 설정
		InitStageLock(0, 1, 3);
		InitStageLock(1, 1, 4);
		InitStageLock(2, 2, 2);
		InitStageLock(3, 2, 3);
		InitStageLock(4, 2, 4);
				
		//스테이지 벽 좌표 설정
		stage[0][2] = { 1 };
		stage[0][3] = { 1 };
		stage[0][4] = { 1 };
		stage[0][5] = { 1 };
		stage[1][1] = { 1 };
		stage[1][2] = { 1 };
		stage[1][5] = { 1 };
		stage[2][1] = { 1 };
		stage[2][5] = { 1 };
		stage[3][0] = { 1 };
		stage[3][1] = { 1 };
		stage[3][5] = { 1 };
		stage[4][0] = { 1 };
		stage[4][5] = { 1 };
		stage[5][0] = { 1 };
		stage[5][2] = { 1 };
		stage[5][5] = { 1 };
		stage[5][6] = { 1 };
		stage[6][0] = { 1 };
		stage[6][2] = { 1 };
		stage[6][6] = { 1 };
		stage[7][0] = { 1 };
		stage[7][6] = { 1 };
		stage[8][0] = { 1 };
		stage[8][1] = { 1 };
		stage[8][2] = { 1 };
		stage[8][4] = { 1 };
		stage[8][5] = { 1 };
		stage[8][6] = { 1 };
		stage[9][2] = { 1 };
		stage[9][3] = { 1 };
		stage[9][4] = { 1 };
	}
	//스테이지 8 초기화
	if (stage_bActive[7])
	{
		//플레이어 좌표 설정
		InitStagePlayer(6, 8, 7);

		//열쇠 좌표 설정
		InitStageKey(0, 2, 3);
		InitStageKey(1, 2, 6);
		InitStageKey(2, 5, 2);
		InitStageKey(3, 5, 6);
		InitStageKey(4, 8, 3);
		InitStageKey(5, 8, 6);
	
		//자물쇠 좌표 설정
		InitStageLock(0, 4, 4);
		InitStageLock(1, 4, 5);
		InitStageLock(2, 5, 4);
		InitStageLock(3, 5, 5);
		InitStageLock(4, 6, 4);
		InitStageLock(5, 6, 5);
	
		//스테이지 벽 좌표 설정
		stage[0][5] = { 1 };
		stage[0][6] = { 1 };
		stage[0][7] = { 1 };
		stage[0][8] = { 1 };
		stage[1][0] = { 1 };
		stage[1][1] = { 1 };
		stage[1][2] = { 1 };
		stage[1][3] = { 1 };
		stage[1][4] = { 1 };
		stage[1][5] = { 1 };
		stage[1][8] = { 1 };
		stage[2][0] = { 1 };
		stage[2][8] = { 1 };
		stage[3][0] = { 1 };
		stage[3][4] = { 1 };
		stage[3][5] = { 1 };
		stage[3][8] = { 1 };
		stage[4][0] = { 1 };
		stage[4][1] = { 1 };
		stage[4][3] = { 1 };
		stage[4][8] = { 1 };
		stage[5][0] = { 1 };
		stage[5][1] = { 1 };
		stage[5][3] = { 1 };
		stage[5][8] = { 1 };
		stage[6][0] = { 1 };
		stage[6][3] = { 1 };
		stage[6][7] = { 1 };
		stage[6][8] = { 1 };
		stage[7][0] = { 1 };
		stage[7][4] = { 1 };
		stage[7][5] = { 1 };
		stage[7][8] = { 1 };
		stage[8][0] = { 1 };
		stage[8][8] = { 1 };
		stage[9][0] = { 1 };
		stage[9][1] = { 1 };
		stage[9][2] = { 1 };
		stage[9][3] = { 1 };
		stage[9][4] = { 1 };
		stage[9][5] = { 1 };
		stage[9][8] = { 1 };
		stage[10][5] = { 1 };
		stage[10][6] = { 1 };
		stage[10][7] = { 1 };
		stage[10][8] = { 1 };
	}
	//스테이지 9 초기화
	if (stage_bActive[8])
	{
		//플레이어 좌표 설정
		InitStagePlayer(5, 1, 3);

		//열쇠 좌표 설정
		InitStageKey(0, 2, 4);
		InitStageKey(1, 3, 2);
		InitStageKey(2, 3, 3);
		InitStageKey(3, 4, 2);
		InitStageKey(4, 5, 2);

		//자물쇠 좌표 설정
		InitStageLock(0, 3, 4);
		InitStageLock(1, 4, 3);
		InitStageLock(2, 4, 4);
		InitStageLock(3, 5, 3);
		InitStageLock(4, 5, 4);

		//스테이지 벽 좌표 설정
		stage[0][2] = { 1 };
		stage[0][3] = { 1 };
		stage[0][4] = { 1 };
		stage[0][5] = { 1 };
		stage[1][2] = { 1 };
		stage[1][5] = { 1 };
		stage[2][0] = { 1 };
		stage[2][1] = { 1 };
		stage[2][2] = { 1 };
		stage[2][5] = { 1 };
		stage[3][0] = { 1 };
		stage[3][5] = { 1 };
		stage[3][6] = { 1 };
		stage[4][0] = { 1 };
		stage[4][6] = { 1 };
		stage[5][0] = { 1 };
		stage[5][6] = { 1 };
		stage[6][0] = { 1 };
		stage[6][4] = { 1 };
		stage[6][5] = { 1 };
		stage[6][6] = { 1 };
		stage[7][0] = { 1 };
		stage[7][1] = { 1 };
		stage[7][2] = { 1 };
		stage[7][3] = { 1 };
		stage[7][4] = { 1 };
		stage[7][5] = { 1 };
	}
	//스테이지 10 초기화
	if (stage_bActive[9])
	{
		//플레이어 좌표 설정
		InitStagePlayer(4, 8, 4);

		//열쇠 좌표 설정
		InitStageKey(0, 2, 2);
		InitStageKey(1, 3, 3);
		InitStageKey(2, 8, 2);
		InitStageKey(3, 9, 3);

		//자물쇠 좌표 설정
		InitStageLock(0, 4, 3);
		InitStageLock(1, 5, 3);
		InitStageLock(2, 6, 3);
		InitStageLock(3, 7, 3);
			   
		//스테이지 벽 좌표 설정
		stage[0][1] = { 1 };
		stage[0][2] = { 1 };
		stage[0][3] = { 1 };
		stage[0][4] = { 1 };
		stage[1][0] = { 1 };
		stage[1][1] = { 1 };
		stage[1][4] = { 1 };
		stage[1][5] = { 1 };
		stage[2][0] = { 1 };
		stage[2][5] = { 1 };
		stage[3][0] = { 1 };
		stage[3][5] = { 1 };
		stage[4][0] = { 1 };
		stage[4][1] = { 1 };
		stage[4][2] = { 1 };
		stage[4][5] = { 1 };
		stage[5][2] = { 1 };
		stage[5][5] = { 1 };
		stage[6][2] = { 1 };
		stage[6][4] = { 1 };
		stage[6][5] = { 1 };
		stage[7][0] = { 1 };
		stage[7][1] = { 1 };
		stage[7][2] = { 1 };
		stage[7][5] = { 1 };
		stage[8][0] = { 1 };
		stage[8][5] = { 1 };
		stage[9][0] = { 1 };
		stage[9][5] = { 1 };
		stage[10][0] = { 1 };
		stage[10][4] = { 1 };
		stage[10][5] = { 1 };
		stage[11][0] = { 1 };
		stage[11][1] = { 1 };
		stage[11][2] = { 1 };
		stage[11][3] = { 1 };
		stage[11][4] = { 1 };
	}
	//스테이지 11 초기화
	if (stage_bActive[10])
	{
		//플레이어 좌표 설정
		InitStagePlayer(4, 5, 1);

		//열쇠 좌표 설정
		InitStageKey(0, 3, 2);
		InitStageKey(1, 4, 3);
		InitStageKey(2, 5, 4);
		InitStageKey(3, 4, 4);

		//자물쇠 좌표 설정
		InitStageLock(0, 4, 2);
		InitStageLock(1, 3, 3);
		InitStageLock(2, 5, 3);
		InitStageLock(3, 4, 4);
		
		//스테이지 벽 좌표 설정
		stage[0][1] = { 1 };
		stage[0][2] = { 1 };
		stage[0][3] = { 1 };
		stage[0][4] = { 1 };
		stage[1][1] = { 1 };
		stage[1][4] = { 1 };
		stage[2][0] = { 1 };
		stage[2][1] = { 1 };
		stage[2][4] = { 1 };
		stage[2][5] = { 1 };
		stage[2][6] = { 1 };
		stage[3][0] = { 1 };
		stage[3][6] = { 1 };
		stage[4][0] = { 1 };
		stage[4][6] = { 1 };
		stage[5][0] = { 1 };
		stage[5][6] = { 1 };
		stage[6][0] = { 1 };
		stage[6][1] = { 1 };
		stage[6][2] = { 1 };
		stage[6][5] = { 1 };
		stage[6][6] = { 1 };
		stage[7][2] = { 1 };
		stage[7][3] = { 1 };
		stage[7][4] = { 1 };
		stage[7][5] = { 1 };
	}
	//스테이지 12 초기화
	if (stage_bActive[11])
	{
		//플레이어 좌표 설정
		InitStagePlayer(4, 3, 6);

		//열쇠 좌표 설정
		InitStageKey(0, 3, 4);
		InitStageKey(1, 4, 3);
		InitStageKey(2, 4, 5);
		InitStageKey(3, 5, 5);

		//자물쇠 좌표 설정
		InitStageLock(0, 3, 1);
		InitStageLock(1, 4, 1);
		InitStageLock(2, 4, 2);
		InitStageLock(3, 5, 3);
		
		//스테이지 벽 좌표 설정
		stage[0][4] = { 1 };
		stage[0][5] = { 1 };
		stage[0][6] = { 1 };
		stage[0][7] = { 1 };
		stage[1][2] = { 1 };
		stage[1][3] = { 1 };
		stage[1][4] = { 1 };
		stage[1][7] = { 1 };
		stage[2][0] = { 1 };
		stage[2][1] = { 1 };
		stage[2][2] = { 1 };
		stage[2][7] = { 1 };
		stage[3][0] = { 1 };
		stage[3][5] = { 1 };
		stage[3][7] = { 1 };
		stage[4][0] = { 1 };
		stage[4][7] = { 1 };
		stage[5][0] = { 1 };
		stage[5][1] = { 1 };
		stage[5][2] = { 1 };
		stage[5][7] = { 1 };
		stage[6][2] = { 1 };
		stage[6][3] = { 1 };
		stage[6][4] = { 1 };
		stage[6][7] = { 1 };
		stage[7][4] = { 1 };
		stage[7][5] = { 1 };
		stage[7][6] = { 1 };
		stage[7][7] = { 1 };
	}
	//스테이지 13 초기화
	if (stage_bActive[12])
	{
		//플레이어 좌표 설정
		InitStagePlayer(6, 1, 3);

		//열쇠 좌표 설정
		InitStageKey(0, 2, 2);
		InitStageKey(1, 2, 3);
		InitStageKey(2, 2, 4);
		InitStageKey(3, 5, 2);
		InitStageKey(4, 5, 4);
		InitStageKey(5, 4, 3);

		//자물쇠 좌표 설정
		InitStageLock(0, 3, 2);
		InitStageLock(1, 3, 3);
		InitStageLock(2, 3, 4);
		InitStageLock(3, 4, 2);
		InitStageLock(4, 4, 3);
		InitStageLock(5, 4, 4);

		//스테이지 벽 좌표 설정
		stage[0][0] = { 1 };
		stage[0][1] = { 1 };
		stage[0][2] = { 1 };
		stage[0][3] = { 1 };
		stage[0][4] = { 1 };
		stage[0][5] = { 1 };
		stage[0][6] = { 1 };
		stage[1][0] = { 1 };
		stage[1][6] = { 1 };
		stage[2][0] = { 1 };
		stage[2][6] = { 1 };
		stage[3][0] = { 1 };
		stage[3][1] = { 1 };
		stage[3][5] = { 1 };
		stage[3][6] = { 1 };
		stage[4][0] = { 1 };
		stage[4][6] = { 1 };
		stage[5][0] = { 1 };
		stage[5][6] = { 1 };
		stage[6][0] = { 1 };
		stage[6][3] = { 1 };
		stage[6][6] = { 1 };
		stage[7][0] = { 1 };
		stage[7][1] = { 1 };
		stage[7][2] = { 1 };
		stage[7][3] = { 1 };
		stage[7][4] = { 1 };
		stage[7][5] = { 1 };
		stage[7][6] = { 1 };
	}
	//스테이지 14 초기화
	if (stage_bActive[13])
	{
		//플레이어 좌표 설정
		InitStagePlayer(6, 4, 5);

		//열쇠 좌표 설정
		InitStageKey(0, 2, 2);
		InitStageKey(1, 2, 4);
		InitStageKey(2, 3, 4);
		InitStageKey(3, 4, 2);
		InitStageKey(4, 5, 2);
		InitStageKey(5, 5, 4);

		//자물쇠 좌표 설정
		InitStageLock(0, 1, 3);
		InitStageLock(1, 2, 3);
		InitStageLock(2, 3, 3);
		InitStageLock(3, 4, 3);
		InitStageLock(4, 5, 3);
		InitStageLock(5, 6, 3);

		//스테이지 벽 좌표 설정
		stage[0][1] = { 1 };
		stage[0][2] = { 1 };
		stage[0][3] = { 1 };
		stage[0][4] = { 1 };
		stage[0][5] = { 1 };
		stage[1][0] = { 1 };
		stage[1][1] = { 1 };
		stage[1][5] = { 1 };
		stage[2][0] = { 1 };
		stage[2][5] = { 1 };
		stage[2][6] = { 1 };
		stage[3][0] = { 1 };
		stage[3][6] = { 1 };
		stage[4][0] = { 1 };
		stage[4][6] = { 1 };
		stage[5][0] = { 1 };
		stage[5][5] = { 1 };
		stage[5][6] = { 1 };
		stage[6][0] = { 1 };
		stage[6][1] = { 1 };
		stage[6][5] = { 1 };
		stage[7][1] = { 1 };
		stage[7][2] = { 1 };
		stage[7][3] = { 1 };
		stage[7][4] = { 1 };
		stage[7][5] = { 1 };
	}
	//스테이지 15 초기화
	if (stage_bActive[14])
	{
		//플레이어 좌표 설정
		InitStagePlayer(6, 6, 7);

		//열쇠 좌표 설정
		InitStageKey(0, 4, 2);
		InitStageKey(1, 4, 3);
		InitStageKey(2, 4, 5);
		InitStageKey(3, 5, 4);
		InitStageKey(4, 6, 5);
		InitStageKey(5, 7, 6);

		//자물쇠 좌표 설정
		InitStageLock(0, 1, 4);
		InitStageLock(1, 1, 5);
		InitStageLock(2, 2, 4);
		InitStageLock(3, 2, 5);
		InitStageLock(4, 3, 4);
		InitStageLock(5, 3, 5);
	
		//스테이지 벽 좌표 설정
		stage[0][3] = { 1 };
		stage[0][4] = { 1 };
		stage[0][5] = { 1 };
		stage[0][6] = { 1 };
		stage[1][3] = { 1 };
		stage[1][6] = { 1 };
		stage[2][0] = { 1 };
		stage[2][1] = { 1 };
		stage[2][2] = { 1 };
		stage[2][3] = { 1 };
		stage[2][6] = { 1 };
		stage[3][0] = { 1 };
		stage[3][6] = { 1 };
		stage[3][7] = { 1 };
		stage[3][8] = { 1 };
		stage[4][0] = { 1 };
		stage[4][8] = { 1 };
		stage[5][0] = { 1 };
		stage[5][5] = { 1 };
		stage[5][6] = { 1 };
		stage[5][8] = { 1 };
		stage[6][0] = { 1 };
		stage[6][3] = { 1 };
		stage[6][8] = { 1 };
		stage[7][0] = { 1 };
		stage[7][1] = { 1 };
		stage[7][3] = { 1 };
		stage[7][8] = { 1 };
		stage[8][1] = { 1 };
		stage[8][5] = { 1 };
		stage[8][8] = { 1 };
		stage[9][1] = { 1 };
		stage[9][2] = { 1 };
		stage[9][3] = { 1 };
		stage[9][4] = { 1 };
		stage[9][5] = { 1 };
		stage[9][6] = { 1 };
		stage[9][7] = { 1 };
		stage[9][8] = { 1 };
	}
	//스테이지 16 초기화
	if (stage_bActive[15])
	{
		//플레이어 좌표 설정
		InitStagePlayer(4, 3, 5);

		//열쇠 좌표 설정
		InitStageKey(0, 2, 2);
		InitStageKey(1, 3, 2);
		InitStageKey(2, 4, 2);
		InitStageKey(3, 6, 4);

		//자물쇠 좌표 설정
		InitStageLock(0, 4, 3);
		InitStageLock(1, 4, 4);
		InitStageLock(2, 5, 3);
		InitStageLock(3, 5, 4);

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
		stage[2][0] = { 1 };
		stage[2][6] = { 1 };
		stage[3][0] = { 1 };
		stage[3][3] = { 1 };
		stage[3][6] = { 1 };
		stage[4][0] = { 1 };
		stage[4][6] = { 1 };
		stage[5][0] = { 1 };
		stage[5][1] = { 1 };
		stage[5][2] = { 1 };
		stage[5][6] = { 1 };
		stage[6][2] = { 1 };
		stage[6][3] = { 1 };
		stage[6][6] = { 1 };
		stage[7][3] = { 1 };
		stage[7][6] = { 1 };
		stage[8][3] = { 1 };
		stage[8][4] = { 1 };
		stage[8][5] = { 1 };
		stage[8][6] = { 1 };
	}
	//스테이지 17 초기화
	if (stage_bActive[16])
	{
		//플레이어 좌표 설정
		InitStagePlayer(6, 7, 7);

		//열쇠 좌표 설정
		InitStageKey(0, 4, 3);
		InitStageKey(1, 4, 5);
		InitStageKey(2, 5, 2);
		InitStageKey(3, 5, 4);
		InitStageKey(4, 7, 3);
		InitStageKey(5, 7, 5);

		//자물쇠 좌표 설정
		InitStageLock(0, 6, 2);
		InitStageLock(1, 7, 1);
		InitStageLock(2, 7, 2);
		InitStageLock(3, 7, 3);
		InitStageLock(4, 8, 2);
		InitStageLock(5, 8, 3);

		//스테이지 벽 좌표 설정
		stage[0][4] = { 1 };
		stage[0][5] = { 1 };
		stage[0][6] = { 1 };
		stage[0][7] = { 1 };
		stage[1][2] = { 1 };
		stage[1][3] = { 1 };
		stage[1][4] = { 1 };
		stage[1][7] = { 1 };
		stage[2][0] = { 1 };
		stage[2][1] = { 1 };
		stage[2][2] = { 1 };
		stage[2][7] = { 1 };
		stage[3][0] = { 1 };
		stage[3][4] = { 1 };
		stage[3][7] = { 1 };
		stage[4][0] = { 1 };
		stage[4][4] = { 1 };
		stage[4][6] = { 1 };
		stage[4][7] = { 1 };
		stage[5][0] = { 1 };
		stage[5][7] = { 1 };
		stage[6][0] = { 1 };
		stage[6][1] = { 1 };
		stage[6][3] = { 1 };
		stage[6][4] = { 1 };
		stage[6][7] = { 1 };
		stage[6][8] = { 1 };
		stage[7][0] = { 1 };
		stage[7][8] = { 1 };
		stage[8][0] = { 1 };
		stage[8][4] = { 1 };
		stage[8][8] = { 1 };
		stage[9][0] = { 1 };
		stage[9][1] = { 1 };
		stage[9][2] = { 1 };
		stage[9][3] = { 1 };
		stage[9][4] = { 1 };
		stage[9][5] = { 1 };
		stage[9][6] = { 1 };
		stage[9][7] = { 1 };
		stage[9][8] = { 1 };
	}
	//스테이지 18 초기화
	if (stage_bActive[17])
	{
		//플레이어 좌표 설정
		InitStagePlayer(7, 5, 6);

		//열쇠 좌표 설정
		InitStageKey(0, 2, 4);
		InitStageKey(1, 3, 3);
		InitStageKey(2, 3, 4);
		InitStageKey(3, 5, 3);
		InitStageKey(4, 6, 2);
		InitStageKey(5, 7, 3);
		InitStageKey(6, 7, 4);

		//자물쇠 좌표 설정
		InitStageLock(0, 2, 1);
		InitStageLock(1, 3, 1);
		InitStageLock(2, 3, 2);
		InitStageLock(3, 4, 1);
		InitStageLock(4, 4, 2);
		InitStageLock(5, 5, 1);
		InitStageLock(6, 5, 2);

		//스테이지 벽 좌표 설정
		stage[0][2] = { 1 };
		stage[0][3] = { 1 };
		stage[0][4] = { 1 };
		stage[0][5] = { 1 };
		stage[0][6] = { 1 };
		stage[1][0] = { 1 };
		stage[1][1] = { 1 };
		stage[1][2] = { 1 };
		stage[1][6] = { 1 };
		stage[2][0] = { 1 };
		stage[2][2] = { 1 };
		stage[2][6] = { 1 };
		stage[3][0] = { 1 };
		stage[3][6] = { 1 };
		stage[3][7] = { 1 };
		stage[4][0] = { 1 };
		stage[4][3] = { 1 };
		stage[4][7] = { 1 };
		stage[5][0] = { 1 };
		stage[5][5] = { 1 };
		stage[5][7] = { 1 };
		stage[6][0] = { 1 };
		stage[6][4] = { 1 };
		stage[6][7] = { 1 };
		stage[7][0] = { 1 };
		stage[7][1] = { 1 };
		stage[7][2] = { 1 };
		stage[7][6] = { 1 };
		stage[7][7] = { 1 };
		stage[8][2] = { 1 };
		stage[8][6] = { 1 };
		stage[9][2] = { 1 };
		stage[9][3] = { 1 };
		stage[9][4] = { 1 };
		stage[9][5] = { 1 };
		stage[9][6] = { 1 };
	}
	//스테이지 19 초기화
	if (stage_bActive[18])
	{
		//플레이어 좌표 설정
		InitStagePlayer(8, 4, 6);

		//열쇠 좌표 설정
		InitStageKey(0, 2, 3);
		InitStageKey(1, 2, 5);
		InitStageKey(2, 3, 1);
		InitStageKey(3, 3, 3);
		InitStageKey(4, 3, 4);
		InitStageKey(5, 3, 5);
		InitStageKey(6, 4, 3);
		InitStageKey(7, 4, 5);

		//자물쇠 좌표 설정
		InitStageLock(0, 1, 1);
		InitStageLock(1, 1, 2);
		InitStageLock(2, 2, 1);
		InitStageLock(3, 2, 2);
		InitStageLock(4, 4, 1);
		InitStageLock(5, 4, 2);
		InitStageLock(6, 5, 1);
		InitStageLock(7, 5, 2);

		//스테이지 벽 좌표 설정
		stage[0][0] = { 1 };
		stage[0][1] = { 1 };
		stage[0][2] = { 1 };
		stage[0][3] = { 1 };
		stage[0][4] = { 1 };
		stage[0][5] = { 1 };
		stage[0][6] = { 1 };
		stage[0][7] = { 1 };
		stage[1][0] = { 1 };
		stage[1][7] = { 1 };
		stage[2][0] = { 1 };
		stage[2][7] = { 1 };
		stage[3][0] = { 1 };
		stage[3][2] = { 1 };
		stage[3][6] = { 1 };
		stage[3][7] = { 1 };
		stage[4][0] = { 1 };
		stage[4][7] = { 1 };
		stage[5][0] = { 1 };
		stage[5][7] = { 1 };
		stage[6][0] = { 1 };
		stage[6][1] = { 1 };
		stage[6][2] = { 1 };
		stage[6][3] = { 1 };
		stage[6][4] = { 1 };
		stage[6][5] = { 1 };
		stage[6][6] = { 1 };
		stage[6][7] = { 1 };
	}
	//스테이지 20 초기화
	if (stage_bActive[19])
	{
		//플레이어 좌표 설정
		InitStagePlayer(7, 1, 5);

		//열쇠 좌표 설정
		InitStageKey(0, 2, 4);
		InitStageKey(1, 3, 5);
		InitStageKey(2, 4, 4);
		InitStageKey(3, 5, 5);
		InitStageKey(4, 6, 3);
		InitStageKey(5, 7, 4);
		InitStageKey(6, 8, 4);

		//자물쇠 좌표 설정
		InitStageLock(0, 4, 2);
		InitStageLock(1, 5, 1);
		InitStageLock(2, 5, 2);
		InitStageLock(3, 6, 1);
		InitStageLock(4, 6, 2);
		InitStageLock(5, 7, 1);
		InitStageLock(6, 7, 2);

		//스테이지 벽 좌표 설정
		stage[0][2] = { 1 };
		stage[0][3] = { 1 };
		stage[0][4] = { 1 };
		stage[0][5] = { 1 };
		stage[0][6] = { 1 };
		stage[0][7] = { 1 };
		stage[1][2] = { 1 };
		stage[1][7] = { 1 };
		stage[2][2] = { 1 };
		stage[2][7] = { 1 };
		stage[3][0] = { 1 };
		stage[3][1] = { 1 };
		stage[3][2] = { 1 };
		stage[3][3] = { 1 };
		stage[3][7] = { 1 };
		stage[4][0] = { 1 };
		stage[4][3] = { 1 };
		stage[4][6] = { 1 };
		stage[4][7] = { 1 };
		stage[5][0] = { 1 };
		stage[5][3] = { 1 };
		stage[5][6] = { 1 };
		stage[6][0] = { 1 };
		stage[6][6] = { 1 };
		stage[6][7] = { 1 };
		stage[7][0] = { 1 };
		stage[7][7] = { 1 };
		stage[8][0] = { 1 };
		stage[8][1] = { 1 };
		stage[8][2] = { 1 };
		stage[8][3] = { 1 };
		stage[8][7] = { 1 };
		stage[9][3] = { 1 };
		stage[9][7] = { 1 };
		stage[10][3] = { 1 };
		stage[10][4] = { 1 };
		stage[10][5] = { 1 };
		stage[10][6] = { 1 };
		stage[10][7] = { 1 };
	}
	//스테이지 21 초기화
	if (stage_bActive[20])
	{
		//플레이어 좌표 설정
		InitStagePlayer(6, 7, 7);

		//열쇠 좌표 설정
		InitStageKey(0, 2, 6);
		InitStageKey(1, 3, 2);
		InitStageKey(2, 4, 2);
		InitStageKey(3, 5, 4);
		InitStageKey(4, 5, 6);
		InitStageKey(5, 6, 5);

		//자물쇠 좌표 설정
		InitStageLock(0, 2, 3);
		InitStageLock(1, 2, 4);
		InitStageLock(2, 3, 3);
		InitStageLock(3, 3, 4);
		InitStageLock(4, 4, 3);
		InitStageLock(5, 4, 4);

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
		stage[2][2] = { 1 };
		stage[2][8] = { 1 };
		stage[3][0] = { 1 };
		stage[3][5] = { 1 };
		stage[3][8] = { 1 };
		stage[4][0] = { 1 };
		stage[4][5] = { 1 };
		stage[4][7] = { 1 };
		stage[4][8] = { 1 };
		stage[5][0] = { 1 };
		stage[5][3] = { 1 };
		stage[5][8] = { 1 };
		stage[6][0] = { 1 };
		stage[6][8] = { 1 };
		stage[7][0] = { 1 };
		stage[7][1] = { 1 };
		stage[7][2] = { 1 };
		stage[7][3] = { 1 };
		stage[7][4] = { 1 };
		stage[7][8] = { 1 };
		stage[8][4] = { 1 };
		stage[8][5] = { 1 };
		stage[8][6] = { 1 };
		stage[8][7] = { 1 };
		stage[8][8] = { 1 };
	}
	//스테이지 22 초기화
	if (stage_bActive[21])
	{
		//플레이어 좌표 설정
		InitStagePlayer(6, 8, 3);

		//열쇠 좌표 설정
		InitStageKey(0, 2, 3);
		InitStageKey(1, 3, 4);
		InitStageKey(2, 4, 2);
		InitStageKey(3, 4, 4);
		InitStageKey(4, 6, 2);
		InitStageKey(5, 6, 3);

		//자물쇠 좌표 설정
		InitStageLock(0, 3, 6);
		InitStageLock(1, 4, 6);
		InitStageLock(2, 5, 5);
		InitStageLock(3, 5, 6);
		InitStageLock(4, 6, 5);
		InitStageLock(5, 6, 6);

		//스테이지 벽 좌표 설정
		stage[0][1] = { 1 };
		stage[0][2] = { 1 };
		stage[0][3] = { 1 };
		stage[0][4] = { 1 };
		stage[1][1] = { 1 };
		stage[1][4] = { 1 };
		stage[2][0] = { 1 };
		stage[2][1] = { 1 };
		stage[2][4] = { 1 };
		stage[2][5] = { 1 };
		stage[2][6] = { 1 };
		stage[2][7] = { 1 };
		stage[3][0] = { 1 };
		stage[3][7] = { 1 };
		stage[4][0] = { 1 };
		stage[4][7] = { 1 };
		stage[5][0] = { 1 };
		stage[5][4] = { 1 };
		stage[5][7] = { 1 };
		stage[6][0] = { 1 };
		stage[6][1] = { 1 };
		stage[6][4] = { 1 };
		stage[6][7] = { 1 };
		stage[7][1] = { 1 };
		stage[7][4] = { 1 };
		stage[7][5] = { 1 };
		stage[7][6] = { 1 };
		stage[7][7] = { 1 };
		stage[8][1] = { 1 };
		stage[8][4] = { 1 };
		stage[9][1] = { 1 };
		stage[9][2] = { 1 };
		stage[9][3] = { 1 };
		stage[9][4] = { 1 };
	}
	//스테이지 23 초기화
	if (stage_bActive[22])
	{
		//플레이어 좌표 설정
		InitStagePlayer(6, 1, 8);

		//열쇠 좌표 설정
		InitStageKey(0, 2, 6);
		InitStageKey(1, 3, 7);
		InitStageKey(2, 4, 3);
		InitStageKey(3, 6, 5);
		InitStageKey(4, 7, 6);
		InitStageKey(5, 8, 6);

		//자물쇠 좌표 설정
		InitStageLock(0, 5, 2);
		InitStageLock(1, 5, 3);
		InitStageLock(2, 6, 1);
		InitStageLock(3, 6, 2);
		InitStageLock(4, 6, 3);
		InitStageLock(5, 6, 4);

		//스테이지 벽 좌표 설정
		stage[0][5] = { 1 };
		stage[0][6] = { 1 };
		stage[0][7] = { 1 };
		stage[0][8] = { 1 };
		stage[0][9] = { 1 };
		stage[1][1] = { 1 };
		stage[1][2] = { 1 };
		stage[1][3] = { 1 };
		stage[1][4] = { 1 };
		stage[1][5] = { 1 };
		stage[1][9] = { 1 };
		stage[2][1] = { 1 };
		stage[2][5] = { 1 };
		stage[2][7] = { 1 };
		stage[2][9] = { 1 };
		stage[3][1] = { 1 };
		stage[3][9] = { 1 };
		stage[4][1] = { 1 };
		stage[4][2] = { 1 };
		stage[4][4] = { 1 };
		stage[4][5] = { 1 };
		stage[4][7] = { 1 };
		stage[4][8] = { 1 };
		stage[4][9] = { 1 };
		stage[5][0] = { 1 };
		stage[5][1] = { 1 };
		stage[5][5] = { 1 };
		stage[5][8] = { 1 };
		stage[6][0] = { 1 };
		stage[6][8] = { 1 };
		stage[7][0] = { 1 };
		stage[7][2] = { 1 };
		stage[7][4] = { 1 };
		stage[7][5] = { 1 };
		stage[7][7] = { 1 };
		stage[7][8] = { 1 };
		stage[8][0] = { 1 };
		stage[8][2] = { 1 };
		stage[8][8] = { 1 };
		stage[9][0] = { 1 };
		stage[9][4] = { 1 };
		stage[9][8] = { 1 };
		stage[10][0] = { 1 };
		stage[10][1] = { 1 };
		stage[10][2] = { 1 };
		stage[10][3] = { 1 };
		stage[10][4] = { 1 };
		stage[10][5] = { 1 };
		stage[10][6] = { 1 };
		stage[10][7] = { 1 };
		stage[10][8] = { 1 };
	}
	//스테이지 24 초기화
	if (stage_bActive[23])
	{
		//플레이어 좌표 설정
		InitStagePlayer(6, 4, 5);

		//열쇠 좌표 설정
		InitStageKey(0, 2, 3);
		InitStageKey(1, 2, 4);
		InitStageKey(2, 3, 2);
		InitStageKey(3, 4, 4);
		InitStageKey(4, 6, 3);
		InitStageKey(5, 6, 4);

		//자물쇠 좌표 설정
		InitStageLock(0, 1, 1);
		InitStageLock(1, 2, 1);
		InitStageLock(2, 3, 1);
		InitStageLock(3, 4, 1);
		InitStageLock(4, 5, 1);
		InitStageLock(5, 6, 1);

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
		stage[2][0] = { 1 };
		stage[2][6] = { 1 };
		stage[3][0] = { 1 };
		stage[3][6] = { 1 };
		stage[4][0] = { 1 };
		stage[4][3] = { 1 };
		stage[4][6] = { 1 };
		stage[5][0] = { 1 };
		stage[5][2] = { 1 };
		stage[5][6] = { 1 };
		stage[6][0] = { 1 };
		stage[6][6] = { 1 };
		stage[7][0] = { 1 };
		stage[7][1] = { 1 };
		stage[7][2] = { 1 };
		stage[7][6] = { 1 };
		stage[8][2] = { 1 };
		stage[8][3] = { 1 };
		stage[8][4] = { 1 };
		stage[8][5] = { 1 };
		stage[8][6] = { 1 };
	}
	//스테이지 25 초기화
	if (stage_bActive[24])
	{
		//플레이어 좌표 설정
		InitStagePlayer(5, 2, 3);

		//열쇠 좌표 설정
		InitStageKey(0, 3, 3);
		InitStageKey(1, 3, 4);
		InitStageKey(2, 6, 2);
		InitStageKey(3, 6, 4);
		InitStageKey(4, 9, 3);

		//자물쇠 좌표 설정
		InitStageLock(0, 4, 3);
		InitStageLock(1, 6, 1);
		InitStageLock(2, 6, 3);
		InitStageLock(3, 6, 5);
		InitStageLock(4, 8, 3);

		//스테이지 벽 좌표 설정
		stage[0][1] = { 1 };
		stage[0][2] = { 1 };
		stage[0][3] = { 1 };
		stage[0][4] = { 1 };
		stage[1][1] = { 1 };
		stage[1][4] = { 1 };
		stage[1][5] = { 1 };
		stage[1][6] = { 1 };
		stage[2][0] = { 1 };
		stage[2][1] = { 1 };
		stage[2][6] = { 1 };
		stage[3][0] = { 1 };
		stage[3][6] = { 1 };
		stage[4][0] = { 1 };
		stage[4][2] = { 1 };
		stage[4][4] = { 1 };
		stage[4][6] = { 1 };
		stage[5][0] = { 1 };
		stage[5][2] = { 1 };
		stage[5][4] = { 1 };
		stage[5][6] = { 1 };
		stage[6][0] = { 1 };
		stage[6][6] = { 1 };
		stage[7][0] = { 1 };
		stage[7][2] = { 1 };
		stage[7][4] = { 1 };
		stage[7][6] = { 1 };
		stage[8][0] = { 1 };
		stage[8][2] = { 1 };
		stage[8][4] = { 1 };
		stage[8][6] = { 1 };
		stage[9][0] = { 1 };
		stage[9][6] = { 1 };
		stage[10][0] = { 1 };
		stage[10][3] = { 1 };
		stage[10][4] = { 1 };
		stage[10][5] = { 1 };
		stage[10][6] = { 1 };
		stage[11][0] = { 1 };
		stage[11][1] = { 1 };
		stage[11][2] = { 1 };
		stage[11][3] = { 1 };
	}
	
}

//맵 출력함수 설정
void PrintStage()
{
	//게임 구역 출력
	for (int i = 0; i < 20; i++)
	{
		GotoXY((WIDTH * 2) / 3, i);
		printf("■");
	}

	//게임 설명
	GotoXY((WIDTH * 2) / 3 + 2, 2);
	printf("#Stage: %d", stagephase + 1);
	GotoXY((WIDTH * 2) / 3 + 2, 4);
	printf("#If You Want to#");
	GotoXY((WIDTH * 2) / 3 + 2, 6);
	printf("Reset press 'R'");
	GotoXY((WIDTH * 2) / 3 + 2, 8);
	printf("Skip press 'S'");
	GotoXY((WIDTH * 2) / 3 + 2, 10);
	printf("Go Back press 'B'");
	GotoXY((WIDTH * 2) / 3 + 2, 12);
	printf("Quit press 'ESC'");
	GotoXY((WIDTH * 2) / 3 + 2, 14);
	printf("#Control: ←↑↓→");
	GotoXY((WIDTH * 2) / 3 + 2, 16);
	printf("#Move ♥ to ♡");

	//스테이지 단계별 맵 출력
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (stage[i][j] == 1)
			{
				GotoXY(2 * i, j);

				TextColor = 3;
				SetColor(BackColor, TextColor);
				printf("■");

				TextColor = 7;
				SetColor(BackColor, TextColor);
			}
		}
	}

}

//키입력 설정
void InputProcessor()
{
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

		KeyOverLapingLeft(g_stPlayer.clearpoint);
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
		KeyOverLapingRight(g_stPlayer.clearpoint);
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
		KeyOverLapingUp(g_stPlayer.clearpoint);
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
		KeyOverLapingDown(g_stPlayer.clearpoint);
	}

	//스테이지 재시작
	if (GetAsyncKeyState('R') & 0x8000)
	{
		stagestate = false;
	}

	//다음 스테이지
	if (GetAsyncKeyState('S') & 0x8000)
	{
		stage_bActive[stagephase] = false;
		stagestate = false;
		stagephase++;
		if (stagephase >= STAGE_MAX)
			stagephase = STAGE_MAX-1;
	}

	//이전 스테이지
	if (GetAsyncKeyState('B') & 0x8000)
	{
		stage_bActive[stagephase] = false;
		stagestate = false;
		stagephase--;
		if (stagephase < 0)
			stagephase = 0;
	}

	//게임종료
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		stagestate = false;
		gamestate = false;
	}
	}

//자물쇠 출력
void PrintLock()
{
	//자물쇠 출력
	for (int i = 0; i < g_stPlayer.clearpoint; i++)
	{
		if (g_stLock[i].bActive)
		{
			GotoXY(g_stLock[i].x * 2, g_stLock[i].y);
			printf("♡");
		}
	}
}
//열쇠 출력
void PrintKey()
{
	//열쇠 출력
	for (int i = 0; i < g_stPlayer.clearpoint; i++)
	{
		if (g_stKey[i].bActive)
		{
			GotoXY(g_stKey[i].x * 2, g_stKey[i].y);

			for (int j = 0; j < g_stPlayer.clearpoint; j++)
				if (g_stKey[i].x == g_stLock[j].x)
				{
					if (g_stKey[i].y == g_stLock[j].y)
					{
						TextColor = 12;
						SetColor(BackColor, TextColor);
					}
				}

			printf("♥");

			if (TextColor == 12)
			{
				TextColor = 7;
				SetColor(BackColor, TextColor);
			}
		}
	}
}
//플레이어 출력
void PrintPlayer()
{
	//플레이어 출력
	if (g_stPlayer.bActive)
	{
		GotoXY(g_stPlayer.x * 2, g_stPlayer.y);

		TextColor = 6;
		SetColor(BackColor, TextColor);
		printf("★");

		TextColor = 7;
		SetColor(BackColor, TextColor);
	}
}

//클리어 함수
int SumClearPoint() {
	int a = 0;
	for (int i = 0; i < g_stPlayer.clearpoint; i++)
	{
		a = a + g_stKey[i].clearpoint;
	}
	return a;
}
void ClearStage()
{
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
			}
		}
	}

	clear = SumClearPoint();

	//스테이지 클리어하면 다음 스테이지로
	if (g_stPlayer.clearpoint == clear)
	{
		stage_bActive[stagephase] = false;
		stagephase++;
		stagestate = false;
	}

	//올클리어 게임끝
	if (stagephase > STAGE_MAX)
	{
		stagestate = false;
		gamestate = false;
	}
}

//엔딩 함수
void Ending()
{
	//모두 클리어
	if (stagephase > STAGE_MAX)
	{
		while (1) {
			system("cls");
			GotoXY(2, 2);
			printf("#Push Push Game");
			GotoXY(2, 4);
			printf("#Congratulations *^^*");
			GotoXY(2, 6);
			printf("#You Clear All Stage");
			GotoXY(2, 8);
			printf("\n");
			Sleep(50);
		}
	}

	//게임이 종료시켰을 때
	while (1) {
		system("cls");
		GotoXY(2, 2);
		printf("#Ending");
		GotoXY(2, 4);
		printf("#Push Push Game");
		if (stagephase <= 0) {
			GotoXY(2, 6);
			printf("#Please Restart Push Push");

		}
		if (stagephase > 0) {
			GotoXY(2, 6);
			printf("#You Clear Stage %d", stagephase);
		}
		GotoXY(2, 8);
		printf("\n");
		Sleep(50);
	}
}

int main() {

	StartMenu();

	while (gamestate)
	{
		Init();

		InitStage();

		//게임시작
		while (stagestate)
		{
			//화면지우기
			system("cls");

			//스테이지 출력
			PrintStage();

			//입력키 설정
			InputProcessor();

			//자물쇠 출력
			PrintLock();

			//열쇠 출력
			PrintKey();

			//플레이어 출력
			PrintPlayer();

			//해당스테이지 클리어 과정
			ClearStage();

			//화면전환 속도
			Sleep(70);
		}
	}

	Ending();

	return 0;
}