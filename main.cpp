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

//열쇠가 서로 겹치지 않음 - 하.. 해당열쇠에 대하여 다른열쇠와 겹칠경우 좌표이동인데 일일이 다 구현했음 머리가 나쁨
void OverLapingLeftZero(int count)
{
	for (int i = 1; i < count; i++)
	{
		if (g_stKey[0].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[0].y == g_stKey[i].y)
			{
				g_stKey[0].x++;
				g_stPlayer.x++;
			}
		}
	}
}
void OverLapingLeftOne(int count)
{
	for (int i = 0; i < 1; i++)
	{
		if (g_stKey[1].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[1].y == g_stKey[i].y)
			{
				g_stKey[1].x++;
				g_stPlayer.x++;
			}
		}
	}
	for (int i = 2; i < count; i++)
	{
		if (g_stKey[1].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[1].y == g_stKey[i].y)
			{
				g_stKey[1].x++;
				g_stPlayer.x++;
			}
		}
	}
}
void OverLapingLeftTwo(int count)
{
	for (int i = 0; i < 2; i++)
	{
		if (g_stKey[2].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[2].y == g_stKey[i].y)
			{
				g_stKey[2].x++;
				g_stPlayer.x++;
			}
		}
	}
	for (int i = 3; i < count; i++)
	{
		if (g_stKey[2].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[2].y == g_stKey[i].y)
			{
				g_stKey[2].x++;
				g_stPlayer.x++;
			}
		}
	}
}
void OverLapingLeftThree(int count)
{
	for (int i = 0; i < 3; i++)
	{
		if (g_stKey[3].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[3].y == g_stKey[i].y)
			{
				g_stKey[3].x++;
				g_stPlayer.x++;
			}
		}
	}
	for (int i = 4; i < count; i++)
	{
		if (g_stKey[3].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[3].y == g_stKey[i].y)
			{
				g_stKey[3].x++;
				g_stPlayer.x++;
			}
		}
	}
}
void OverLapingLeftFour(int count)
{
	for (int i = 0; i < 4; i++)
	{
		if (g_stKey[4].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[4].y == g_stKey[i].y)
			{
				g_stKey[4].x++;
				g_stPlayer.x++;
			}
		}
	}
	for (int i = 5; i < count; i++)
	{
		if (g_stKey[4].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[4].y == g_stKey[i].y)
			{
				g_stKey[4].x++;
				g_stPlayer.x++;
			}
		}
	}
}
void OverLapingLeftFive(int count)
{
	for (int i = 0; i < 5; i++)
	{
		if (g_stKey[5].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[5].y == g_stKey[i].y)
			{
				g_stKey[5].x++;
				g_stPlayer.x++;
			}
		}
	}
	for (int i = 6; i < count; i++)
	{
		if (g_stKey[5].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[5].y == g_stKey[i].y)
			{
				g_stKey[5].x++;
				g_stPlayer.x++;
			}
		}
	}
}
void OverLapingLeftSix(int count)
{
	for (int i = 0; i < 6; i++)
	{
		if (g_stKey[6].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[6].y == g_stKey[i].y)
			{
				g_stKey[6].x++;
				g_stPlayer.x++;
			}
		}
	}
	for (int i = 7; i < count; i++)
	{
		if (g_stKey[6].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[6].y == g_stKey[i].y)
			{
				g_stKey[6].x++;
				g_stPlayer.x++;
			}
		}
	}
}
void OverLapingLeftSeven(int count)
{
	for (int i = 0; i < 7; i++)
	{
		if (g_stKey[7].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[7].y == g_stKey[i].y)
			{
				g_stKey[7].x++;
				g_stPlayer.x++;
			}
		}
	}
	for (int i = 8; i < count; i++)
	{
		if (g_stKey[7].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[7].y == g_stKey[i].y)
			{
				g_stKey[7].x++;
				g_stPlayer.x++;
			}
		}
	}
}
void OverLapingLeftEight(int count)
{
	for (int i = 0; i < 8; i++)
	{
		if (g_stKey[8].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[8].y == g_stKey[i].y)
			{
				g_stKey[8].x++;
				g_stPlayer.x++;
			}
		}
	}
	for (int i = 9; i < count; i++)
	{
		if (g_stKey[8].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[8].y == g_stKey[i].y)
			{
				g_stKey[8].x++;
				g_stPlayer.x++;
			}
		}
	}
}
void OverLapingLeftNine(int count)
{
	for (int i = 0; i < 9; i++)
	{
		if (g_stKey[9].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[9].y == g_stKey[i].y)
			{
				g_stKey[9].x++;
				g_stPlayer.x++;
			}
		}
	}
}

void OverLapingRightZero(int count)
{
	for (int i = 1; i < count; i++)
	{
		if (g_stKey[0].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[0].y == g_stKey[i].y)
			{
				g_stKey[0].x--;
				g_stPlayer.x--;
			}
		}
	}
}
void OverLapingRightOne(int count)
{
	for (int i = 0; i < 1; i++)
	{
		if (g_stKey[1].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[1].y == g_stKey[i].y)
			{
				g_stKey[1].x--;
				g_stPlayer.x--;
			}
		}
	}
	for (int i = 2; i < count; i++)
	{
		if (g_stKey[1].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[1].y == g_stKey[i].y)
			{
				g_stKey[1].x--;
				g_stPlayer.x--;
			}
		}
	}
}
void OverLapingRightTwo(int count)
{
	for (int i = 0; i < 2; i++)
	{
		if (g_stKey[2].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[2].y == g_stKey[i].y)
			{
				g_stKey[2].x--;
				g_stPlayer.x--;
			}
		}
	}
	for (int i = 3; i < count; i++)
	{
		if (g_stKey[2].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[2].y == g_stKey[i].y)
			{
				g_stKey[2].x--;
				g_stPlayer.x--;
			}
		}
	}
}
void OverLapingRightThree(int count)
{
	for (int i = 0; i < 3; i++)
	{
		if (g_stKey[3].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[3].y == g_stKey[i].y)
			{
				g_stKey[3].x--;
				g_stPlayer.x--;
			}
		}
	}
	for (int i = 4; i < count; i++)
	{
		if (g_stKey[3].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[3].y == g_stKey[i].y)
			{
				g_stKey[3].x--;
				g_stPlayer.x--;
			}
		}
	}
}
void OverLapingRightFour(int count)
{
	for (int i = 0; i < 4; i++)
	{
		if (g_stKey[4].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[4].y == g_stKey[i].y)
			{
				g_stKey[4].x--;
				g_stPlayer.x--;
			}
		}
	}
	for (int i = 5; i < count; i++)
	{
		if (g_stKey[4].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[4].y == g_stKey[i].y)
			{
				g_stKey[4].x--;
				g_stPlayer.x--;
			}
		}
	}
}
void OverLapingRightFive(int count)
{
	for (int i = 0; i < 5; i++)
	{
		if (g_stKey[5].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[5].y == g_stKey[i].y)
			{
				g_stKey[5].x--;
				g_stPlayer.x--;
			}
		}
	}
	for (int i = 6; i < count; i++)
	{
		if (g_stKey[5].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[5].y == g_stKey[i].y)
			{
				g_stKey[5].x--;
				g_stPlayer.x--;
			}
		}
	}
}
void OverLapingRightSix(int count)
{
	for (int i = 0; i < 6; i++)
	{
		if (g_stKey[6].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[6].y == g_stKey[i].y)
			{
				g_stKey[6].x--;
				g_stPlayer.x--;
			}
		}
	}
	for (int i = 7; i < count; i++)
	{
		if (g_stKey[6].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[6].y == g_stKey[i].y)
			{
				g_stKey[6].x--;
				g_stPlayer.x--;
			}
		}
	}
}
void OverLapingRightSeven(int count)
{
	for (int i = 0; i < 7; i++)
	{
		if (g_stKey[7].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[7].y == g_stKey[i].y)
			{
				g_stKey[7].x--;
				g_stPlayer.x--;
			}
		}
	}
	for (int i = 8; i < count; i++)
	{
		if (g_stKey[7].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[7].y == g_stKey[i].y)
			{
				g_stKey[7].x--;
				g_stPlayer.x--;
			}
		}
	}
}
void OverLapingRightEight(int count)
{
	for (int i = 0; i < 8; i++)
	{
		if (g_stKey[8].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[8].y == g_stKey[i].y)
			{
				g_stKey[8].x--;
				g_stPlayer.x--;
			}
		}
	}
	for (int i = 9; i < count; i++)
	{
		if (g_stKey[8].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[8].y == g_stKey[i].y)
			{
				g_stKey[8].x--;
				g_stPlayer.x--;
			}
		}
	}
}
void OverLapingRightNine(int count)
{
	for (int i = 0; i < 9; i++)
	{
		if (g_stKey[9].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[9].y == g_stKey[i].y)
			{
				g_stKey[9].x--;
				g_stPlayer.x--;
			}
		}
	}
}

void OverLapingDownZero(int count)
{
	for (int i = 1; i < count; i++)
	{
		if (g_stKey[0].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[0].y == g_stKey[i].y)
			{
				g_stKey[0].y--;
				g_stPlayer.y--;
			}
		}
	}
}
void OverLapingDownOne(int count)
{
	for (int i = 0; i < 1; i++)
	{
		if (g_stKey[1].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[1].y == g_stKey[i].y)
			{
				g_stKey[1].y--;
				g_stPlayer.y--;
			}
		}
	}
	for (int i = 2; i < count; i++)
	{
		if (g_stKey[1].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[1].y == g_stKey[i].y)
			{
				g_stKey[1].y--;
				g_stPlayer.y--;
			}
		}
	}
}
void OverLapingDownTwo(int count)
{
	for (int i = 0; i < 2; i++)
	{
		if (g_stKey[2].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[2].y == g_stKey[i].y)
			{
				g_stKey[2].y--;
				g_stPlayer.y--;
			}
		}
	}
	for (int i = 3; i < count; i++)
	{
		if (g_stKey[2].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[2].y == g_stKey[i].y)
			{
				g_stKey[2].y--;
				g_stPlayer.y--;
			}
		}
	}
}
void OverLapingDownThree(int count)
{
	for (int i = 0; i < 3; i++)
	{
		if (g_stKey[3].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[3].y == g_stKey[i].y)
			{
				g_stKey[3].y--;
				g_stPlayer.y--;
			}
		}
	}
	for (int i = 4; i < count; i++)
	{
		if (g_stKey[3].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[3].y == g_stKey[i].y)
			{
				g_stKey[3].y--;
				g_stPlayer.y--;
			}
		}
	}
}
void OverLapingDownFour(int count)
{
	for (int i = 0; i < 4; i++)
	{
		if (g_stKey[4].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[4].y == g_stKey[i].y)
			{
				g_stKey[4].y--;
				g_stPlayer.y--;
			}
		}
	}
	for (int i = 5; i < count; i++)
	{
		if (g_stKey[4].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[4].y == g_stKey[i].y)
			{
				g_stKey[4].y--;
				g_stPlayer.y--;
			}
		}
	}
}
void OverLapingDownFive(int count)
{
	for (int i = 0; i < 5; i++)
	{
		if (g_stKey[5].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[5].y == g_stKey[i].y)
			{
				g_stKey[5].y--;
				g_stPlayer.y--;
			}
		}
	}
	for (int i = 6; i < count; i++)
	{
		if (g_stKey[5].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[5].y == g_stKey[i].y)
			{
				g_stKey[5].y--;
				g_stPlayer.y--;
			}
		}
	}
}
void OverLapingDownSix(int count)
{
	for (int i = 0; i < 6; i++)
	{
		if (g_stKey[6].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[6].y == g_stKey[i].y)
			{
				g_stKey[6].y--;
				g_stPlayer.y--;
			}
		}
	}
	for (int i = 7; i < count; i++)
	{
		if (g_stKey[6].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[6].y == g_stKey[i].y)
			{
				g_stKey[6].y--;
				g_stPlayer.y--;
			}
		}
	}
}
void OverLapingDownSeven(int count)
{
	for (int i = 0; i < 7; i++)
	{
		if (g_stKey[7].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[7].y == g_stKey[i].y)
			{
				g_stKey[7].y--;
				g_stPlayer.y--;
			}
		}
	}
	for (int i = 8; i < count; i++)
	{
		if (g_stKey[7].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[7].y == g_stKey[i].y)
			{
				g_stKey[7].y--;
				g_stPlayer.y--;
			}
		}
	}
}
void OverLapingDownEight(int count)
{
	for (int i = 0; i < 8; i++)
	{
		if (g_stKey[8].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[8].y == g_stKey[i].y)
			{
				g_stKey[8].y--;
				g_stPlayer.y--;
			}
		}
	}
	for (int i = 9; i < count; i++)
	{
		if (g_stKey[8].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[8].y == g_stKey[i].y)
			{
				g_stKey[8].y--;
				g_stPlayer.y--;
			}
		}
	}
}
void OverLapingDownNine(int count)
{
	for (int i = 0; i < 9; i++)
	{
		if (g_stKey[9].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[9].y == g_stKey[i].y)
			{
				g_stKey[9].y--;
				g_stPlayer.y--;
			}
		}
	}
}

void OverLapingUpZero(int count)
{
	for (int i = 1; i < count; i++)
	{
		if (g_stKey[0].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[0].y == g_stKey[i].y)
			{
				g_stKey[0].y++;
				g_stPlayer.y++;
			}
		}
	}
}
void OverLapingUpOne(int count)
{
	for (int i = 0; i < 1; i++)
	{
		if (g_stKey[1].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[1].y == g_stKey[i].y)
			{
				g_stKey[1].y++;
				g_stPlayer.y++;
			}
		}
	}
	for (int i = 2; i < count; i++)
	{
		if (g_stKey[1].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[1].y == g_stKey[i].y)
			{
				g_stKey[1].y++;
				g_stPlayer.y++;
			}
		}
	}
}
void OverLapingUpTwo(int count)
{
	for (int i = 0; i < 2; i++)
	{
		if (g_stKey[2].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[2].y == g_stKey[i].y)
			{
				g_stKey[2].y++;
				g_stPlayer.y++;
			}
		}
	}
	for (int i = 3; i < count; i++)
	{
		if (g_stKey[2].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[2].y == g_stKey[i].y)
			{
				g_stKey[2].y++;
				g_stPlayer.y++;
			}
		}
	}
}
void OverLapingUpThree(int count)
{
	for (int i = 0; i < 3; i++)
	{
		if (g_stKey[3].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[3].y == g_stKey[i].y)
			{
				g_stKey[3].y++;
				g_stPlayer.y++;
			}
		}
	}
	for (int i = 4; i < count; i++)
	{
		if (g_stKey[3].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[3].y == g_stKey[i].y)
			{
				g_stKey[3].y++;
				g_stPlayer.y++;
			}
		}
	}
}
void OverLapingUpFour(int count)
{
	for (int i = 0; i < 4; i++)
	{
		if (g_stKey[4].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[4].y == g_stKey[i].y)
			{
				g_stKey[4].y++;
				g_stPlayer.y++;
			}
		}
	}
	for (int i = 5; i < count; i++)
	{
		if (g_stKey[4].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[4].y == g_stKey[i].y)
			{
				g_stKey[4].y++;
				g_stPlayer.y++;
			}
		}
	}
}
void OverLapingUpFive(int count)
{
	for (int i = 0; i < 5; i++)
	{
		if (g_stKey[5].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[5].y == g_stKey[i].y)
			{
				g_stKey[5].y++;
				g_stPlayer.y++;
			}
		}
	}
	for (int i = 6; i < count; i++)
	{
		if (g_stKey[5].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[5].y == g_stKey[i].y)
			{
				g_stKey[5].y++;
				g_stPlayer.y++;
			}
		}
	}
}
void OverLapingUpSix(int count)
{
	for (int i = 0; i < 6; i++)
	{
		if (g_stKey[6].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[6].y == g_stKey[i].y)
			{
				g_stKey[6].y++;
				g_stPlayer.y++;
			}
		}
	}
	for (int i = 7; i < count; i++)
	{
		if (g_stKey[6].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[6].y == g_stKey[i].y)
			{
				g_stKey[6].y++;
				g_stPlayer.y++;
			}
		}
	}
}
void OverLapingUpSeven(int count)
{
	for (int i = 0; i < 7; i++)
	{
		if (g_stKey[7].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[7].y == g_stKey[i].y)
			{
				g_stKey[7].y++;
				g_stPlayer.y++;
			}
		}
	}
	for (int i = 8; i < count; i++)
	{
		if (g_stKey[7].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[7].y == g_stKey[i].y)
			{
				g_stKey[7].y++;
				g_stPlayer.y++;
			}
		}
	}
}
void OverLapingUpEight(int count)
{
	for (int i = 0; i < 8; i++)
	{
		if (g_stKey[8].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[8].y == g_stKey[i].y)
			{
				g_stKey[8].y++;
				g_stPlayer.y++;
			}
		}
	}
	for (int i = 9; i < count; i++)
	{
		if (g_stKey[8].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[8].y == g_stKey[i].y)
			{
				g_stKey[8].y++;
				g_stPlayer.y++;
			}
		}
	}
}
void OverLapingUpNine(int count)
{
	for (int i = 0; i < 9; i++)
	{
		if (g_stKey[9].x == g_stKey[i].x)		//겹치지 않게
		{
			if (g_stKey[9].y == g_stKey[i].y)
			{
				g_stKey[9].y++;
				g_stPlayer.y++;
			}
		}
	}
}

void OverLapingLeft(int clearpoint)
{
	OverLapingLeftZero(clearpoint);
	OverLapingLeftOne(clearpoint);
	if (clearpoint > 2)
	OverLapingLeftTwo(clearpoint);
	if (clearpoint > 3)
	OverLapingLeftThree(clearpoint);
	if (clearpoint > 4)
	OverLapingLeftFour(clearpoint);
	if (clearpoint > 5)
	OverLapingLeftFive(clearpoint);
	if (clearpoint > 6)
	OverLapingLeftSix(clearpoint);
	if (clearpoint > 7)
	OverLapingLeftSeven(clearpoint);
	if (clearpoint > 8)
	OverLapingLeftEight(clearpoint);
	if (clearpoint > 9)
	OverLapingLeftNine(clearpoint);
}
void OverLapingRight(int clearpoint)
{
	OverLapingRightZero(clearpoint);
	OverLapingRightOne(clearpoint);
	if (clearpoint > 2)
		OverLapingRightTwo(clearpoint);
	if (clearpoint > 3)
		OverLapingRightThree(clearpoint);
	if (clearpoint > 4)
		OverLapingRightFour(clearpoint);
	if (clearpoint > 5)
		OverLapingRightFive(clearpoint);
	if (clearpoint > 6)
		OverLapingRightSix(clearpoint);
	if (clearpoint > 7)
		OverLapingRightSeven(clearpoint);
	if (clearpoint > 8)
		OverLapingRightEight(clearpoint);
	if (clearpoint > 9)
		OverLapingRightNine(clearpoint);
}
void OverLapingUp(int clearpoint)
{
	OverLapingUpZero(clearpoint);
	OverLapingUpOne(clearpoint);
	if (clearpoint > 2)
		OverLapingUpTwo(clearpoint);
	if (clearpoint > 3)
		OverLapingUpThree(clearpoint);
	if (clearpoint > 4)
		OverLapingUpFour(clearpoint);
	if (clearpoint > 5)
		OverLapingUpFive(clearpoint);
	if (clearpoint > 6)
		OverLapingUpSix(clearpoint);
	if (clearpoint > 7)
		OverLapingUpSeven(clearpoint);
	if (clearpoint > 8)
		OverLapingUpEight(clearpoint);
	if (clearpoint > 9)
		OverLapingUpNine(clearpoint);
}
void OverLapingDown(int clearpoint)
{
	OverLapingDownZero(clearpoint);
	OverLapingDownOne(clearpoint);
	if (clearpoint > 2)
		OverLapingDownTwo(clearpoint);
	if (clearpoint > 3)
		OverLapingDownThree(clearpoint);
	if (clearpoint > 4)
		OverLapingDownFour(clearpoint);
	if (clearpoint > 5)
		OverLapingDownFive(clearpoint);
	if (clearpoint > 6)
		OverLapingDownSix(clearpoint);
	if (clearpoint > 7)
		OverLapingDownSeven(clearpoint);
	if (clearpoint > 8)
		OverLapingDownEight(clearpoint);
	if (clearpoint > 9)
		OverLapingDownNine(clearpoint);
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

		//스테이지 설정이 종료되었으면 게임시작
		if (stagephase >= 0)
		{
			//게임시작
			gamestate = true;
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
void InitStage()
{
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
	//스테이지 4 초기화
	if (stage_bActive[3])
	{
		//플레이어 좌표 설정
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
		g_stPlayer.clearpoint = 5;

		//열쇠 좌표 설정
		g_stKey[0].x = 2;
		g_stKey[0].y = 2;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 2;
		g_stKey[1].y = 3;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 2;
		g_stKey[2].y = 5;
		g_stKey[2].bActive = true;

		g_stKey[3].x = 3;
		g_stKey[3].y = 4;
		g_stKey[3].bActive = true;

		g_stKey[4].x = 3;
		g_stKey[4].y = 6;
		g_stKey[4].bActive = true;


		//자물쇠 좌표 설정
		g_stLock[0].x = 1;
		g_stLock[0].y = 5;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 1;
		g_stLock[1].y = 6;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 2;
		g_stLock[2].y = 6;
		g_stLock[2].bActive = true;

		g_stLock[3].x = 3;
		g_stLock[3].y = 6;
		g_stLock[3].bActive = true;

		g_stLock[4].x = 4;
		g_stLock[4].y = 6;
		g_stLock[4].bActive = true;

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
		g_stPlayer.x = 2;
		g_stPlayer.y = 1;
		g_stPlayer.bActive = true;

		//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
		g_stPlayer.clearpoint = 3;

		//열쇠 좌표 설정
		g_stKey[0].x = 3;
		g_stKey[0].y = 2;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 2;
		g_stKey[1].y = 5;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 5;
		g_stKey[2].y = 6;
		g_stKey[2].bActive = true;

		//자물쇠 좌표 설정
		g_stLock[0].x = 1;
		g_stLock[0].y = 4;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 1;
		g_stLock[1].y = 5;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 1;
		g_stLock[2].y = 6;
		g_stLock[2].bActive = true;
		
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
		g_stPlayer.x = 8;
		g_stPlayer.y = 1;
		g_stPlayer.bActive = true;

		//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
		g_stPlayer.clearpoint = 5;

		//열쇠 좌표 설정
		g_stKey[0].x = 3;
		g_stKey[0].y = 3;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 4;
		g_stKey[1].y = 4;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 4;
		g_stKey[2].y = 5;
		g_stKey[2].bActive = true;

		g_stKey[3].x = 5;
		g_stKey[3].y = 3;
		g_stKey[3].bActive = true;

		g_stKey[4].x = 7;
		g_stKey[4].y = 3;
		g_stKey[4].bActive = true;


		//자물쇠 좌표 설정
		g_stLock[0].x = 1;
		g_stLock[0].y = 6;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 2;
		g_stLock[1].y = 6;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 3;
		g_stLock[2].y = 6;
		g_stLock[2].bActive = true;

		g_stLock[3].x = 4;
		g_stLock[3].y = 6;
		g_stLock[3].bActive = true;

		g_stLock[4].x = 5;
		g_stLock[4].y = 6;
		g_stLock[4].bActive = true;

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
		g_stPlayer.x = 8;
		g_stPlayer.y = 3;
		g_stPlayer.bActive = true;

		//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
		g_stPlayer.clearpoint = 5;

		//열쇠 좌표 설정
		g_stKey[0].x = 3;
		g_stKey[0].y = 3;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 4;
		g_stKey[1].y = 2;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 4;
		g_stKey[2].y = 4;
		g_stKey[2].bActive = true;

		g_stKey[3].x = 5;
		g_stKey[3].y = 3;
		g_stKey[3].bActive = true;

		g_stKey[4].x = 6;
		g_stKey[4].y = 4;
		g_stKey[4].bActive = true;


		//자물쇠 좌표 설정
		g_stLock[0].x = 1;
		g_stLock[0].y = 3;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 1;
		g_stLock[1].y = 4;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 2;
		g_stLock[2].y = 2;
		g_stLock[2].bActive = true;

		g_stLock[3].x = 2;
		g_stLock[3].y = 3;
		g_stLock[3].bActive = true;

		g_stLock[4].x = 2;
		g_stLock[4].y = 4;
		g_stLock[4].bActive = true;

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
		g_stPlayer.x = 8;
		g_stPlayer.y = 7;
		g_stPlayer.bActive = true;

		//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
		g_stPlayer.clearpoint = 6;

		//열쇠 좌표 설정
		g_stKey[0].x = 2;
		g_stKey[0].y = 3;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 2;
		g_stKey[1].y = 6;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 5;
		g_stKey[2].y = 2;
		g_stKey[2].bActive = true;

		g_stKey[3].x = 5;
		g_stKey[3].y = 6;
		g_stKey[3].bActive = true;

		g_stKey[4].x = 8;
		g_stKey[4].y = 3;
		g_stKey[4].bActive = true;

		g_stKey[5].x = 8;
		g_stKey[5].y = 6;
		g_stKey[5].bActive = true;

		//자물쇠 좌표 설정
		g_stLock[0].x = 4;
		g_stLock[0].y = 4;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 4;
		g_stLock[1].y = 5;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 5;
		g_stLock[2].y = 4;
		g_stLock[2].bActive = true;

		g_stLock[3].x = 5;
		g_stLock[3].y = 5;
		g_stLock[3].bActive = true;

		g_stLock[4].x = 6;
		g_stLock[4].y = 4;
		g_stLock[4].bActive = true;

		g_stLock[5].x = 6;
		g_stLock[5].y = 5;
		g_stLock[5].bActive = true;

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
		g_stPlayer.x = 1;
		g_stPlayer.y = 3;
		g_stPlayer.bActive = true;

		//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
		g_stPlayer.clearpoint = 5;

		//열쇠 좌표 설정
		g_stKey[0].x = 2;
		g_stKey[0].y = 4;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 3;
		g_stKey[1].y = 2;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 3;
		g_stKey[2].y = 3;
		g_stKey[2].bActive = true;

		g_stKey[3].x = 4;
		g_stKey[3].y = 2;
		g_stKey[3].bActive = true;

		g_stKey[4].x = 5;
		g_stKey[4].y = 2;
		g_stKey[4].bActive = true;


		//자물쇠 좌표 설정
		g_stLock[0].x = 3;
		g_stLock[0].y = 4;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 4;
		g_stLock[1].y = 3;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 4;
		g_stLock[2].y = 4;
		g_stLock[2].bActive = true;

		g_stLock[3].x = 5;
		g_stLock[3].y = 3;
		g_stLock[3].bActive = true;

		g_stLock[4].x = 5;
		g_stLock[4].y = 4;
		g_stLock[4].bActive = true;

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
		g_stPlayer.x = 8;
		g_stPlayer.y = 4;
		g_stPlayer.bActive = true;

		//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
		g_stPlayer.clearpoint = 4;

		//열쇠 좌표 설정
		g_stKey[0].x = 2;
		g_stKey[0].y = 2;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 3;
		g_stKey[1].y = 3;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 8;
		g_stKey[2].y = 2;
		g_stKey[2].bActive = true;

		g_stKey[3].x = 9;
		g_stKey[3].y = 3;
		g_stKey[3].bActive = true;
	   
		//자물쇠 좌표 설정
		g_stLock[0].x = 4;
		g_stLock[0].y = 3;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 5;
		g_stLock[1].y = 3;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 6;
		g_stLock[2].y = 3;
		g_stLock[2].bActive = true;

		g_stLock[3].x = 7;
		g_stLock[3].y = 3;
		g_stLock[3].bActive = true;

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
	if (stage_bActive[3])
	{
		//플레이어 좌표 설정
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
		g_stPlayer.clearpoint = 5;

		//열쇠 좌표 설정
		g_stKey[0].x = 2;
		g_stKey[0].y = 2;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 2;
		g_stKey[1].y = 3;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 2;
		g_stKey[2].y = 5;
		g_stKey[2].bActive = true;

		g_stKey[3].x = 3;
		g_stKey[3].y = 4;
		g_stKey[3].bActive = true;

		g_stKey[4].x = 3;
		g_stKey[4].y = 6;
		g_stKey[4].bActive = true;


		//자물쇠 좌표 설정
		g_stLock[0].x = 1;
		g_stLock[0].y = 5;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 1;
		g_stLock[1].y = 6;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 2;
		g_stLock[2].y = 6;
		g_stLock[2].bActive = true;

		g_stLock[3].x = 3;
		g_stLock[3].y = 6;
		g_stLock[3].bActive = true;

		g_stLock[4].x = 4;
		g_stLock[4].y = 6;
		g_stLock[4].bActive = true;

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
	//스테이지 12 초기화
	if (stage_bActive[3])
	{
		//플레이어 좌표 설정
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
		g_stPlayer.clearpoint = 5;

		//열쇠 좌표 설정
		g_stKey[0].x = 2;
		g_stKey[0].y = 2;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 2;
		g_stKey[1].y = 3;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 2;
		g_stKey[2].y = 5;
		g_stKey[2].bActive = true;

		g_stKey[3].x = 3;
		g_stKey[3].y = 4;
		g_stKey[3].bActive = true;

		g_stKey[4].x = 3;
		g_stKey[4].y = 6;
		g_stKey[4].bActive = true;


		//자물쇠 좌표 설정
		g_stLock[0].x = 1;
		g_stLock[0].y = 5;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 1;
		g_stLock[1].y = 6;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 2;
		g_stLock[2].y = 6;
		g_stLock[2].bActive = true;

		g_stLock[3].x = 3;
		g_stLock[3].y = 6;
		g_stLock[3].bActive = true;

		g_stLock[4].x = 4;
		g_stLock[4].y = 6;
		g_stLock[4].bActive = true;

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
	//스테이지 13 초기화
	if (stage_bActive[3])
	{
		//플레이어 좌표 설정
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
		g_stPlayer.clearpoint = 5;

		//열쇠 좌표 설정
		g_stKey[0].x = 2;
		g_stKey[0].y = 2;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 2;
		g_stKey[1].y = 3;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 2;
		g_stKey[2].y = 5;
		g_stKey[2].bActive = true;

		g_stKey[3].x = 3;
		g_stKey[3].y = 4;
		g_stKey[3].bActive = true;

		g_stKey[4].x = 3;
		g_stKey[4].y = 6;
		g_stKey[4].bActive = true;


		//자물쇠 좌표 설정
		g_stLock[0].x = 1;
		g_stLock[0].y = 5;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 1;
		g_stLock[1].y = 6;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 2;
		g_stLock[2].y = 6;
		g_stLock[2].bActive = true;

		g_stLock[3].x = 3;
		g_stLock[3].y = 6;
		g_stLock[3].bActive = true;

		g_stLock[4].x = 4;
		g_stLock[4].y = 6;
		g_stLock[4].bActive = true;

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
	//스테이지 14 초기화
	if (stage_bActive[3])
	{
		//플레이어 좌표 설정
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
		g_stPlayer.clearpoint = 5;

		//열쇠 좌표 설정
		g_stKey[0].x = 2;
		g_stKey[0].y = 2;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 2;
		g_stKey[1].y = 3;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 2;
		g_stKey[2].y = 5;
		g_stKey[2].bActive = true;

		g_stKey[3].x = 3;
		g_stKey[3].y = 4;
		g_stKey[3].bActive = true;

		g_stKey[4].x = 3;
		g_stKey[4].y = 6;
		g_stKey[4].bActive = true;


		//자물쇠 좌표 설정
		g_stLock[0].x = 1;
		g_stLock[0].y = 5;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 1;
		g_stLock[1].y = 6;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 2;
		g_stLock[2].y = 6;
		g_stLock[2].bActive = true;

		g_stLock[3].x = 3;
		g_stLock[3].y = 6;
		g_stLock[3].bActive = true;

		g_stLock[4].x = 4;
		g_stLock[4].y = 6;
		g_stLock[4].bActive = true;

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
	//스테이지 15 초기화
	if (stage_bActive[3])
	{
		//플레이어 좌표 설정
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
		g_stPlayer.clearpoint = 5;

		//열쇠 좌표 설정
		g_stKey[0].x = 2;
		g_stKey[0].y = 2;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 2;
		g_stKey[1].y = 3;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 2;
		g_stKey[2].y = 5;
		g_stKey[2].bActive = true;

		g_stKey[3].x = 3;
		g_stKey[3].y = 4;
		g_stKey[3].bActive = true;

		g_stKey[4].x = 3;
		g_stKey[4].y = 6;
		g_stKey[4].bActive = true;


		//자물쇠 좌표 설정
		g_stLock[0].x = 1;
		g_stLock[0].y = 5;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 1;
		g_stLock[1].y = 6;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 2;
		g_stLock[2].y = 6;
		g_stLock[2].bActive = true;

		g_stLock[3].x = 3;
		g_stLock[3].y = 6;
		g_stLock[3].bActive = true;

		g_stLock[4].x = 4;
		g_stLock[4].y = 6;
		g_stLock[4].bActive = true;

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
	//스테이지 16 초기화
	if (stage_bActive[3])
	{
		//플레이어 좌표 설정
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
		g_stPlayer.clearpoint = 5;

		//열쇠 좌표 설정
		g_stKey[0].x = 2;
		g_stKey[0].y = 2;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 2;
		g_stKey[1].y = 3;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 2;
		g_stKey[2].y = 5;
		g_stKey[2].bActive = true;

		g_stKey[3].x = 3;
		g_stKey[3].y = 4;
		g_stKey[3].bActive = true;

		g_stKey[4].x = 3;
		g_stKey[4].y = 6;
		g_stKey[4].bActive = true;


		//자물쇠 좌표 설정
		g_stLock[0].x = 1;
		g_stLock[0].y = 5;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 1;
		g_stLock[1].y = 6;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 2;
		g_stLock[2].y = 6;
		g_stLock[2].bActive = true;

		g_stLock[3].x = 3;
		g_stLock[3].y = 6;
		g_stLock[3].bActive = true;

		g_stLock[4].x = 4;
		g_stLock[4].y = 6;
		g_stLock[4].bActive = true;

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
	//스테이지 17 초기화
	if (stage_bActive[3])
	{
		//플레이어 좌표 설정
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
		g_stPlayer.clearpoint = 5;

		//열쇠 좌표 설정
		g_stKey[0].x = 2;
		g_stKey[0].y = 2;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 2;
		g_stKey[1].y = 3;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 2;
		g_stKey[2].y = 5;
		g_stKey[2].bActive = true;

		g_stKey[3].x = 3;
		g_stKey[3].y = 4;
		g_stKey[3].bActive = true;

		g_stKey[4].x = 3;
		g_stKey[4].y = 6;
		g_stKey[4].bActive = true;


		//자물쇠 좌표 설정
		g_stLock[0].x = 1;
		g_stLock[0].y = 5;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 1;
		g_stLock[1].y = 6;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 2;
		g_stLock[2].y = 6;
		g_stLock[2].bActive = true;

		g_stLock[3].x = 3;
		g_stLock[3].y = 6;
		g_stLock[3].bActive = true;

		g_stLock[4].x = 4;
		g_stLock[4].y = 6;
		g_stLock[4].bActive = true;

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
	//스테이지 18 초기화
	if (stage_bActive[3])
	{
		//플레이어 좌표 설정
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
		g_stPlayer.clearpoint = 5;

		//열쇠 좌표 설정
		g_stKey[0].x = 2;
		g_stKey[0].y = 2;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 2;
		g_stKey[1].y = 3;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 2;
		g_stKey[2].y = 5;
		g_stKey[2].bActive = true;

		g_stKey[3].x = 3;
		g_stKey[3].y = 4;
		g_stKey[3].bActive = true;

		g_stKey[4].x = 3;
		g_stKey[4].y = 6;
		g_stKey[4].bActive = true;


		//자물쇠 좌표 설정
		g_stLock[0].x = 1;
		g_stLock[0].y = 5;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 1;
		g_stLock[1].y = 6;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 2;
		g_stLock[2].y = 6;
		g_stLock[2].bActive = true;

		g_stLock[3].x = 3;
		g_stLock[3].y = 6;
		g_stLock[3].bActive = true;

		g_stLock[4].x = 4;
		g_stLock[4].y = 6;
		g_stLock[4].bActive = true;

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
	//스테이지 19 초기화
	if (stage_bActive[3])
	{
		//플레이어 좌표 설정
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
		g_stPlayer.clearpoint = 5;

		//열쇠 좌표 설정
		g_stKey[0].x = 2;
		g_stKey[0].y = 2;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 2;
		g_stKey[1].y = 3;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 2;
		g_stKey[2].y = 5;
		g_stKey[2].bActive = true;

		g_stKey[3].x = 3;
		g_stKey[3].y = 4;
		g_stKey[3].bActive = true;

		g_stKey[4].x = 3;
		g_stKey[4].y = 6;
		g_stKey[4].bActive = true;


		//자물쇠 좌표 설정
		g_stLock[0].x = 1;
		g_stLock[0].y = 5;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 1;
		g_stLock[1].y = 6;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 2;
		g_stLock[2].y = 6;
		g_stLock[2].bActive = true;

		g_stLock[3].x = 3;
		g_stLock[3].y = 6;
		g_stLock[3].bActive = true;

		g_stLock[4].x = 4;
		g_stLock[4].y = 6;
		g_stLock[4].bActive = true;

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
	//스테이지 20 초기화
	if (stage_bActive[3])
	{
		//플레이어 좌표 설정
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//클리어 변수 설정 (열쇠,자물쇠의 개수와 같음)
		g_stPlayer.clearpoint = 5;

		//열쇠 좌표 설정
		g_stKey[0].x = 2;
		g_stKey[0].y = 2;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 2;
		g_stKey[1].y = 3;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 2;
		g_stKey[2].y = 5;
		g_stKey[2].bActive = true;

		g_stKey[3].x = 3;
		g_stKey[3].y = 4;
		g_stKey[3].bActive = true;

		g_stKey[4].x = 3;
		g_stKey[4].y = 6;
		g_stKey[4].bActive = true;


		//자물쇠 좌표 설정
		g_stLock[0].x = 1;
		g_stLock[0].y = 5;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 1;
		g_stLock[1].y = 6;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 2;
		g_stLock[2].y = 6;
		g_stLock[2].bActive = true;

		g_stLock[3].x = 3;
		g_stLock[3].y = 6;
		g_stLock[3].bActive = true;

		g_stLock[4].x = 4;
		g_stLock[4].y = 6;
		g_stLock[4].bActive = true;

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

		OverLapingLeft(g_stPlayer.clearpoint);
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
		OverLapingRight(g_stPlayer.clearpoint);
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
		OverLapingUp(g_stPlayer.clearpoint);
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
		OverLapingDown(g_stPlayer.clearpoint);
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
		if (stagephase > STAGE_MAX)
			stagephase = STAGE_MAX;
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

	//q로 나갔을 때
	while (1) {
		system("cls");
		GotoXY(2, 2);
		printf("#Ending");
		GotoXY(2, 4);
		printf("#Push Push Game");
		GotoXY(2, 6);
		printf("#You Clear Stage %d",stagephase);
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