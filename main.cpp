#include <stdio.h>
#include <windows.h>
#include <conio.h>
#pragma warning(disable: 4996)

//�ܼ�â ũ��
#define WIDTH 60
#define LENGTH 20

#define STAGE_MAX 25

//����, �ؽ�Ʈ�� ǥ��
int BackColor = 0;
int TextColor = 7;


int stage[20][20] = { 0 };	//�������� �� �迭 ����
bool gamestate = false;	//�������࿩��
bool stagestate = false;	//�������࿩��
int clear = 0;	//Ŭ���� ����
int stagephase = 0; //�������� �ܰ�
bool stage_bActive[100] = { false };//�������� �ܰ� ���࿩�� ����


//������Ʈ ����ü ����
struct ST_OBJECT
{
	int x;
	int y;
	int clearpoint;
	bool bActive;
};

//������Ʈ ����
ST_OBJECT g_stPlayer;
ST_OBJECT g_stKey[10];
ST_OBJECT g_stLock[10];

//Ŀ�� ��ǥ ���� �Լ�
void GotoXY(int _x, int _y)
{
	COORD pos = { _x, _y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//�� ���� �Լ�
void SetColor(unsigned char _BgColor, unsigned char _TextColor)
{
	if (_BgColor > 15 || _TextColor > 15) return;

	unsigned short ColorNum = (_BgColor << 4) | _TextColor;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ColorNum);
}
//�ֻܼ����� �����Լ�
void SetConsoleSize(int _col, int _lines)
{
	char setText[100];
	sprintf_s(setText, "mode con cols=%d lines=%d", _col, _lines);
	system(setText);
}


//���谡 ���� ��ġ�� �ʰ�
void KeyOverLapingLeftBase(int a,int clearpoint)
{
	for (int i = 0; i < a; i++)
	{
		if (g_stKey[a].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[a].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[a].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[a].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[a].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[a].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[a].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[a].x == g_stKey[i].x)		//��ġ�� �ʰ�
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

//���۸޴�
void StartMenu()
{
	//�ܼ�â ũ�� ����
	SetConsoleSize(WIDTH, LENGTH);


	while (1) {
		system("cls");
		GotoXY(2, 2);
		printf("#Push Push Game");
		GotoXY(2, 4);
		printf("#Enter Stage: ");

		//���������� �Է¹���, stagephase�� 0���� �����ϹǷ� -1�� ���� ��
		scanf("%d", &stagephase);
		stagephase--;

		//�������� ������ ����Ǿ����� ���ӽ���
		if (stagephase >= 0)
		{
			//���ӽ���
			gamestate = true;
			break;
		}

		Sleep(50);
	}
}

//�ʱ�ȭ ���� �Լ�
void Init()
{
	//�������� Ȱ��ȭ
	stagestate = true;

	//�ش� �������� ����
	stage_bActive[stagephase] = true;

	//Ŭ���� ���� �ʱ�ȭ
	clear = 0;

	//�������� �� ��ǥ �ʱ�ȭ
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			stage[i][j] = 0;
		}
	}

	//����, �ڹ��� ��ǥ �ʱ�ȭ
	for (int i = 0; i < 10; i++)
	{
		g_stKey[i].x = 0;
		g_stKey[i].y = 0;
		g_stKey[i].clearpoint = 0;
		g_stLock[i].x = 0;
		g_stLock[i].y = 0;
	}

}


//�������� �ʱ�ȭ ���� �Լ�
//�÷��̾� ��ǥ �����Լ�, Ŭ���� ���� ����(����,�ڹ����� ������ ����)
void InitStagePlayer(int clearpoint, int x, int y)	//clearpoint, x,y��ǥ
{
	g_stPlayer.x = x;
	g_stPlayer.y = y;
	g_stPlayer.bActive = true;
	g_stPlayer.clearpoint = clearpoint;
}
//���� ��ǥ �����Լ�
void InitStageKey(int i,int x, int y)	//���° key, x,y��ǥ
{
	g_stKey[i].x = x;
	g_stKey[i].y = y;
	g_stKey[i].bActive = true;
}
//�ڹ��� ��ǥ �����Լ�
void InitStageLock(int i, int x, int y)	//���° Lock, x,y��ǥ
{
	g_stLock[i].x = x;
	g_stLock[i].y = y;
	g_stLock[i].bActive = true;
}
//���������� �ʱ�ȭ
void InitStage()
{
	//�� �������� �ʱ�ȭ
	//�������� 1 �ʱ�ȭ 
	if (stage_bActive[0])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(4, 4, 4);

		//���� ��ǥ ����
		InitStageKey(0, 3, 3);
		InitStageKey(1, 3, 4);
		InitStageKey(2, 4, 5);
		InitStageKey(3, 5, 3);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 1, 4);
		InitStageLock(1, 3, 1);
		InitStageLock(2, 4, 6);
		InitStageLock(3, 6, 3);

		//�������� �� ��ǥ ����
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
	//�������� 2 �ʱ�ȭ
	if (stage_bActive[1])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(3, 1, 1);

		//���� ��ǥ ����
		InitStageKey(0, 2, 2);
		InitStageKey(1, 3, 2);
		InitStageKey(2, 2, 3);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 7, 3);
		InitStageLock(1, 7, 4);
		InitStageLock(2, 7, 5);
		
		//�������� �� ��ǥ ����
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
	//�������� 3 �ʱ�ȭ
	if (stage_bActive[2])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(4, 2, 3);

		//���� ��ǥ ����
		InitStageKey(0, 2, 2);
		InitStageKey(1, 4, 3);
		InitStageKey(2, 6, 4);
		InitStageKey(3, 7, 3);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 2, 4);
		InitStageLock(1, 2, 5);
		InitStageLock(2, 3, 4);
		InitStageLock(3, 3, 5);

		//�������� �� ��ǥ ����
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
	//�������� 4 �ʱ�ȭ
	if (stage_bActive[3])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(5, 1, 2);

		//���� ��ǥ ����
		InitStageKey(0, 2, 2);
		InitStageKey(1, 2, 3);
		InitStageKey(2, 2, 5);
		InitStageKey(3, 3, 4);
		InitStageKey(4, 3, 6);
	
		//�ڹ��� ��ǥ ����
		InitStageLock(0, 1, 5);
		InitStageLock(1, 1, 6);
		InitStageLock(2, 2, 6);
		InitStageLock(3, 3, 6);
		InitStageLock(3, 4, 6);
		
		//�������� �� ��ǥ ����
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
	//�������� 5 �ʱ�ȭ
	if (stage_bActive[4])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(3, 2, 1);

		//���� ��ǥ ����
		InitStageKey(0, 3, 2);
		InitStageKey(1, 2, 5);
		InitStageKey(2, 5, 6);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 1, 4);
		InitStageLock(1, 1, 5);
		InitStageLock(2, 1, 6);

		//�������� �� ��ǥ ����
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
	//�������� 6 �ʱ�ȭ
	if (stage_bActive[5])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(5, 8, 1);

		//���� ��ǥ ����
		InitStageKey(0, 3, 3);
		InitStageKey(1, 4, 4);
		InitStageKey(2, 4, 5);
		InitStageKey(3, 5, 3);
		InitStageKey(4, 7, 3);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 1, 6);
		InitStageLock(1, 2, 6);
		InitStageLock(2, 3, 6);
		InitStageLock(3, 4, 6);
		InitStageLock(4, 5, 6);
		
		//�������� �� ��ǥ ����
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
	//�������� 7 �ʱ�ȭ
	if (stage_bActive[6])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(5, 8, 3);

		//���� ��ǥ ����
		InitStageKey(0, 3, 3);
		InitStageKey(1, 4, 2);
		InitStageKey(2, 4, 4);
		InitStageKey(3, 5, 3);
		InitStageKey(4, 6, 4);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 1, 3);
		InitStageLock(1, 1, 4);
		InitStageLock(2, 2, 2);
		InitStageLock(3, 2, 3);
		InitStageLock(4, 2, 4);
				
		//�������� �� ��ǥ ����
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
	//�������� 8 �ʱ�ȭ
	if (stage_bActive[7])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(6, 8, 7);

		//���� ��ǥ ����
		InitStageKey(0, 2, 3);
		InitStageKey(1, 2, 6);
		InitStageKey(2, 5, 2);
		InitStageKey(3, 5, 6);
		InitStageKey(4, 8, 3);
		InitStageKey(5, 8, 6);
	
		//�ڹ��� ��ǥ ����
		InitStageLock(0, 4, 4);
		InitStageLock(1, 4, 5);
		InitStageLock(2, 5, 4);
		InitStageLock(3, 5, 5);
		InitStageLock(4, 6, 4);
		InitStageLock(5, 6, 5);
	
		//�������� �� ��ǥ ����
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
	//�������� 9 �ʱ�ȭ
	if (stage_bActive[8])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(5, 1, 3);

		//���� ��ǥ ����
		InitStageKey(0, 2, 4);
		InitStageKey(1, 3, 2);
		InitStageKey(2, 3, 3);
		InitStageKey(3, 4, 2);
		InitStageKey(4, 5, 2);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 3, 4);
		InitStageLock(1, 4, 3);
		InitStageLock(2, 4, 4);
		InitStageLock(3, 5, 3);
		InitStageLock(4, 5, 4);

		//�������� �� ��ǥ ����
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
	//�������� 10 �ʱ�ȭ
	if (stage_bActive[9])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(4, 8, 4);

		//���� ��ǥ ����
		InitStageKey(0, 2, 2);
		InitStageKey(1, 3, 3);
		InitStageKey(2, 8, 2);
		InitStageKey(3, 9, 3);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 4, 3);
		InitStageLock(1, 5, 3);
		InitStageLock(2, 6, 3);
		InitStageLock(3, 7, 3);
			   
		//�������� �� ��ǥ ����
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
	//�������� 11 �ʱ�ȭ
	if (stage_bActive[10])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(4, 5, 1);

		//���� ��ǥ ����
		InitStageKey(0, 3, 2);
		InitStageKey(1, 4, 3);
		InitStageKey(2, 5, 4);
		InitStageKey(3, 4, 4);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 4, 2);
		InitStageLock(1, 3, 3);
		InitStageLock(2, 5, 3);
		InitStageLock(3, 4, 4);
		
		//�������� �� ��ǥ ����
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
	//�������� 12 �ʱ�ȭ
	if (stage_bActive[11])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(4, 3, 6);

		//���� ��ǥ ����
		InitStageKey(0, 3, 4);
		InitStageKey(1, 4, 3);
		InitStageKey(2, 4, 5);
		InitStageKey(3, 5, 5);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 3, 1);
		InitStageLock(1, 4, 1);
		InitStageLock(2, 4, 2);
		InitStageLock(3, 5, 3);
		
		//�������� �� ��ǥ ����
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
	//�������� 13 �ʱ�ȭ
	if (stage_bActive[12])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(6, 1, 3);

		//���� ��ǥ ����
		InitStageKey(0, 2, 2);
		InitStageKey(1, 2, 3);
		InitStageKey(2, 2, 4);
		InitStageKey(3, 5, 2);
		InitStageKey(4, 5, 4);
		InitStageKey(5, 4, 3);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 3, 2);
		InitStageLock(1, 3, 3);
		InitStageLock(2, 3, 4);
		InitStageLock(3, 4, 2);
		InitStageLock(4, 4, 3);
		InitStageLock(5, 4, 4);

		//�������� �� ��ǥ ����
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
	//�������� 14 �ʱ�ȭ
	if (stage_bActive[13])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(6, 4, 5);

		//���� ��ǥ ����
		InitStageKey(0, 2, 2);
		InitStageKey(1, 2, 4);
		InitStageKey(2, 3, 4);
		InitStageKey(3, 4, 2);
		InitStageKey(4, 5, 2);
		InitStageKey(5, 5, 4);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 1, 3);
		InitStageLock(1, 2, 3);
		InitStageLock(2, 3, 3);
		InitStageLock(3, 4, 3);
		InitStageLock(4, 5, 3);
		InitStageLock(5, 6, 3);

		//�������� �� ��ǥ ����
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
	//�������� 15 �ʱ�ȭ
	if (stage_bActive[14])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(6, 6, 7);

		//���� ��ǥ ����
		InitStageKey(0, 4, 2);
		InitStageKey(1, 4, 3);
		InitStageKey(2, 4, 5);
		InitStageKey(3, 5, 4);
		InitStageKey(4, 6, 5);
		InitStageKey(5, 7, 6);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 1, 4);
		InitStageLock(1, 1, 5);
		InitStageLock(2, 2, 4);
		InitStageLock(3, 2, 5);
		InitStageLock(4, 3, 4);
		InitStageLock(5, 3, 5);
	
		//�������� �� ��ǥ ����
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
	//�������� 16 �ʱ�ȭ
	if (stage_bActive[15])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(4, 3, 5);

		//���� ��ǥ ����
		InitStageKey(0, 2, 2);
		InitStageKey(1, 3, 2);
		InitStageKey(2, 4, 2);
		InitStageKey(3, 6, 4);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 4, 3);
		InitStageLock(1, 4, 4);
		InitStageLock(2, 5, 3);
		InitStageLock(3, 5, 4);

		//�������� �� ��ǥ ����
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
	//�������� 17 �ʱ�ȭ
	if (stage_bActive[16])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(6, 7, 7);

		//���� ��ǥ ����
		InitStageKey(0, 4, 3);
		InitStageKey(1, 4, 5);
		InitStageKey(2, 5, 2);
		InitStageKey(3, 5, 4);
		InitStageKey(4, 7, 3);
		InitStageKey(5, 7, 5);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 6, 2);
		InitStageLock(1, 7, 1);
		InitStageLock(2, 7, 2);
		InitStageLock(3, 7, 3);
		InitStageLock(4, 8, 2);
		InitStageLock(5, 8, 3);

		//�������� �� ��ǥ ����
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
	//�������� 18 �ʱ�ȭ
	if (stage_bActive[17])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(7, 5, 6);

		//���� ��ǥ ����
		InitStageKey(0, 2, 4);
		InitStageKey(1, 3, 3);
		InitStageKey(2, 3, 4);
		InitStageKey(3, 5, 3);
		InitStageKey(4, 6, 2);
		InitStageKey(5, 7, 3);
		InitStageKey(6, 7, 4);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 2, 1);
		InitStageLock(1, 3, 1);
		InitStageLock(2, 3, 2);
		InitStageLock(3, 4, 1);
		InitStageLock(4, 4, 2);
		InitStageLock(5, 5, 1);
		InitStageLock(6, 5, 2);

		//�������� �� ��ǥ ����
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
	//�������� 19 �ʱ�ȭ
	if (stage_bActive[18])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(8, 4, 6);

		//���� ��ǥ ����
		InitStageKey(0, 2, 3);
		InitStageKey(1, 2, 5);
		InitStageKey(2, 3, 1);
		InitStageKey(3, 3, 3);
		InitStageKey(4, 3, 4);
		InitStageKey(5, 3, 5);
		InitStageKey(6, 4, 3);
		InitStageKey(7, 4, 5);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 1, 1);
		InitStageLock(1, 1, 2);
		InitStageLock(2, 2, 1);
		InitStageLock(3, 2, 2);
		InitStageLock(4, 4, 1);
		InitStageLock(5, 4, 2);
		InitStageLock(6, 5, 1);
		InitStageLock(7, 5, 2);

		//�������� �� ��ǥ ����
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
	//�������� 20 �ʱ�ȭ
	if (stage_bActive[19])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(7, 1, 5);

		//���� ��ǥ ����
		InitStageKey(0, 2, 4);
		InitStageKey(1, 3, 5);
		InitStageKey(2, 4, 4);
		InitStageKey(3, 5, 5);
		InitStageKey(4, 6, 3);
		InitStageKey(5, 7, 4);
		InitStageKey(6, 8, 4);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 4, 2);
		InitStageLock(1, 5, 1);
		InitStageLock(2, 5, 2);
		InitStageLock(3, 6, 1);
		InitStageLock(4, 6, 2);
		InitStageLock(5, 7, 1);
		InitStageLock(6, 7, 2);

		//�������� �� ��ǥ ����
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
	//�������� 21 �ʱ�ȭ
	if (stage_bActive[20])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(6, 7, 7);

		//���� ��ǥ ����
		InitStageKey(0, 2, 6);
		InitStageKey(1, 3, 2);
		InitStageKey(2, 4, 2);
		InitStageKey(3, 5, 4);
		InitStageKey(4, 5, 6);
		InitStageKey(5, 6, 5);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 2, 3);
		InitStageLock(1, 2, 4);
		InitStageLock(2, 3, 3);
		InitStageLock(3, 3, 4);
		InitStageLock(4, 4, 3);
		InitStageLock(5, 4, 4);

		//�������� �� ��ǥ ����
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
	//�������� 22 �ʱ�ȭ
	if (stage_bActive[21])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(6, 8, 3);

		//���� ��ǥ ����
		InitStageKey(0, 2, 3);
		InitStageKey(1, 3, 4);
		InitStageKey(2, 4, 2);
		InitStageKey(3, 4, 4);
		InitStageKey(4, 6, 2);
		InitStageKey(5, 6, 3);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 3, 6);
		InitStageLock(1, 4, 6);
		InitStageLock(2, 5, 5);
		InitStageLock(3, 5, 6);
		InitStageLock(4, 6, 5);
		InitStageLock(5, 6, 6);

		//�������� �� ��ǥ ����
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
	//�������� 23 �ʱ�ȭ
	if (stage_bActive[22])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(6, 1, 8);

		//���� ��ǥ ����
		InitStageKey(0, 2, 6);
		InitStageKey(1, 3, 7);
		InitStageKey(2, 4, 3);
		InitStageKey(3, 6, 5);
		InitStageKey(4, 7, 6);
		InitStageKey(5, 8, 6);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 5, 2);
		InitStageLock(1, 5, 3);
		InitStageLock(2, 6, 1);
		InitStageLock(3, 6, 2);
		InitStageLock(4, 6, 3);
		InitStageLock(5, 6, 4);

		//�������� �� ��ǥ ����
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
	//�������� 24 �ʱ�ȭ
	if (stage_bActive[23])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(6, 4, 5);

		//���� ��ǥ ����
		InitStageKey(0, 2, 3);
		InitStageKey(1, 2, 4);
		InitStageKey(2, 3, 2);
		InitStageKey(3, 4, 4);
		InitStageKey(4, 6, 3);
		InitStageKey(5, 6, 4);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 1, 1);
		InitStageLock(1, 2, 1);
		InitStageLock(2, 3, 1);
		InitStageLock(3, 4, 1);
		InitStageLock(4, 5, 1);
		InitStageLock(5, 6, 1);

		//�������� �� ��ǥ ����
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
	//�������� 25 �ʱ�ȭ
	if (stage_bActive[24])
	{
		//�÷��̾� ��ǥ ����
		InitStagePlayer(5, 2, 3);

		//���� ��ǥ ����
		InitStageKey(0, 3, 3);
		InitStageKey(1, 3, 4);
		InitStageKey(2, 6, 2);
		InitStageKey(3, 6, 4);
		InitStageKey(4, 9, 3);

		//�ڹ��� ��ǥ ����
		InitStageLock(0, 4, 3);
		InitStageLock(1, 6, 1);
		InitStageLock(2, 6, 3);
		InitStageLock(3, 6, 5);
		InitStageLock(4, 8, 3);

		//�������� �� ��ǥ ����
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

//�� ����Լ� ����
void PrintStage()
{
	//���� ���� ���
	for (int i = 0; i < 20; i++)
	{
		GotoXY((WIDTH * 2) / 3, i);
		printf("��");
	}

	//���� ����
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
	printf("#Control: �����");
	GotoXY((WIDTH * 2) / 3 + 2, 16);
	printf("#Move �� to ��");

	//�������� �ܰ躰 �� ���
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (stage[i][j] == 1)
			{
				GotoXY(2 * i, j);

				TextColor = 3;
				SetColor(BackColor, TextColor);
				printf("��");

				TextColor = 7;
				SetColor(BackColor, TextColor);
			}
		}
	}

}

//Ű�Է� ����
void InputProcessor()
{
	//����Ű ���� ����
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) //���ʹ���Ű
	{
		g_stPlayer.x--;

		if (stage[g_stPlayer.x][g_stPlayer.y] == 1) g_stPlayer.x++;		//�ʹ����� ����������

		for (int i = 0; i < 10; i++)		//���踦 �о����� 
		{
			if (g_stPlayer.x == g_stKey[i].x)
			{
				if (g_stPlayer.y == g_stKey[i].y)
				{
					g_stKey[i].x--;
					if (stage[g_stKey[i].x][g_stKey[i].y] == 1)	//���赵 �ʹ����� ����������
					{
						g_stKey[i].x++;
						g_stPlayer.x++;
					}
				}
			}
		}

		KeyOverLapingLeft(g_stPlayer.clearpoint);
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) //�����ʹ���Ű
	{
		g_stPlayer.x++;
		if (stage[g_stPlayer.x][g_stPlayer.y] == 1) g_stPlayer.x--;		//�ʹ����� ����������

		for (int i = 0; i < 10; i++)		//���踦 �о����� 
		{
			if (g_stKey[i].bActive)
			{
				if (g_stPlayer.x == g_stKey[i].x)
				{
					if (g_stPlayer.y == g_stKey[i].y)
					{
						g_stKey[i].x++;
						if (stage[g_stKey[i].x][g_stKey[i].y] == 1)	//���赵 �ʹ����� ����������
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

	if (GetAsyncKeyState(VK_UP) & 0x8000) //���ʹ���Ű
	{
		g_stPlayer.y--;
		if (stage[g_stPlayer.x][g_stPlayer.y] == 1) g_stPlayer.y++;		//�ʹ����� ����������

		for (int i = 0; i < 10; i++)		//���踦 �о����� 
		{
			if (g_stKey[i].bActive)
			{
				if (g_stPlayer.x == g_stKey[i].x)
				{
					if (g_stPlayer.y == g_stKey[i].y)
					{
						g_stKey[i].y--;
						if (stage[g_stKey[i].x][g_stKey[i].y] == 1)	//���赵 �ʹ����� ����������
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

	if (GetAsyncKeyState(VK_DOWN) & 0x8000) //�Ʒ��ʹ���Ű
	{
		g_stPlayer.y++;
		if (stage[g_stPlayer.x][g_stPlayer.y] == 1) g_stPlayer.y--;		//�ʹ����� ����������

		for (int i = 0; i < 10; i++)		//���踦 �о����� 
		{
			if (g_stKey[i].bActive)
			{
				if (g_stPlayer.x == g_stKey[i].x)
				{
					if (g_stPlayer.y == g_stKey[i].y)
					{
						g_stKey[i].y++;
						if (stage[g_stKey[i].x][g_stKey[i].y] == 1)	//���赵 �ʹ����� ����������
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

	//�������� �����
	if (GetAsyncKeyState('R') & 0x8000)
	{
		stagestate = false;
	}

	//���� ��������
	if (GetAsyncKeyState('S') & 0x8000)
	{
		stage_bActive[stagephase] = false;
		stagestate = false;
		stagephase++;
		if (stagephase >= STAGE_MAX)
			stagephase = STAGE_MAX-1;
	}

	//���� ��������
	if (GetAsyncKeyState('B') & 0x8000)
	{
		stage_bActive[stagephase] = false;
		stagestate = false;
		stagephase--;
		if (stagephase < 0)
			stagephase = 0;
	}

	//��������
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		stagestate = false;
		gamestate = false;
	}
	}

//�ڹ��� ���
void PrintLock()
{
	//�ڹ��� ���
	for (int i = 0; i < g_stPlayer.clearpoint; i++)
	{
		if (g_stLock[i].bActive)
		{
			GotoXY(g_stLock[i].x * 2, g_stLock[i].y);
			printf("��");
		}
	}
}
//���� ���
void PrintKey()
{
	//���� ���
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

			printf("��");

			if (TextColor == 12)
			{
				TextColor = 7;
				SetColor(BackColor, TextColor);
			}
		}
	}
}
//�÷��̾� ���
void PrintPlayer()
{
	//�÷��̾� ���
	if (g_stPlayer.bActive)
	{
		GotoXY(g_stPlayer.x * 2, g_stPlayer.y);

		TextColor = 6;
		SetColor(BackColor, TextColor);
		printf("��");

		TextColor = 7;
		SetColor(BackColor, TextColor);
	}
}

//Ŭ���� �Լ�
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
	//�������� Ŭ���� ����
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

	//�������� Ŭ�����ϸ� ���� ����������
	if (g_stPlayer.clearpoint == clear)
	{
		stage_bActive[stagephase] = false;
		stagephase++;
		stagestate = false;
	}

	//��Ŭ���� ���ӳ�
	if (stagephase > STAGE_MAX)
	{
		stagestate = false;
		gamestate = false;
	}
}

//���� �Լ�
void Ending()
{
	//��� Ŭ����
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

	//������ ��������� ��
	while (1) {
		system("cls");
		GotoXY(2, 2);
		printf("#Ending");
		GotoXY(2, 4);
		printf("#Push Push Game");
		GotoXY(2, 6);
		printf("#You Clear Stage %d", stagephase);
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

		//���ӽ���
		while (stagestate)
		{
			//ȭ�������
			system("cls");

			//�������� ���
			PrintStage();

			//�Է�Ű ����
			InputProcessor();

			//�ڹ��� ���
			PrintLock();

			//���� ���
			PrintKey();

			//�÷��̾� ���
			PrintPlayer();

			//�ش罺������ Ŭ���� ����
			ClearStage();

			//ȭ����ȯ �ӵ�
			Sleep(70);
		}
	}

	Ending();

	return 0;
}