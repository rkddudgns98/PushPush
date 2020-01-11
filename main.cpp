#include <stdio.h>
#include <windows.h>
#include "Console.h"
#include <conio.h>


#define WIDTH 60
#define LENGTH 20


int stage[20][20] = { 0 };	//�������� �� �迭 ����


struct ST_OBJECT
{
	int x;
	int y;
	int clearpoint;
	bool bActive;
};


ST_OBJECT g_stPlayer = { 0 };
ST_OBJECT g_stKey[10] = { 0 };
ST_OBJECT g_stLock[10] = { 0 };

int StageClear() {
	int a = 0;
	for (int i = 0; i < 10; i++)
	{
		a = a + g_stKey[i].clearpoint;
	}
	return a;
}



int main() {
	SetConsoleSize(WIDTH, LENGTH);	//�ܼ�â ũ�� ����

	bool gamestate = false;	//�������࿩��

	int clear = 0;	//Ŭ���� ����
	bool stage_bActive[100] = { false };//�������� �ܰ� ����

	//���ӽ���
	gamestate = true;

	//�������� �ܰ� ����
	stage_bActive[0] = true;

	//�� �������� �ʱ�ȭ
	//�������� 1 �ʱ�ȭ 
	if (stage_bActive[0])
	{
		//�÷��̾� ��ǥ ����
		g_stPlayer.x = 4;
		g_stPlayer.y = 4;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 4;

		//���� ��ǥ ����
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

		//�ڹ��� ��ǥ ����
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
		g_stPlayer.x = 4;
		g_stPlayer.y = 4;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 4;

		//���� ��ǥ ����
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

		//�ڹ��� ��ǥ ����
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
	//�������� 3 �ʱ�ȭ



	//���ӽ���
	while (gamestate)
	{
		Clear();


		//���� ���� ���
		for (int i = 0; i < 20; i++)
		{
			GotoXY((WIDTH * 2) / 3, i);
			printf("��");
		}


		//�������� �ܰ躰 �� ���
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (stage[i][j] == 1)
				{
					GotoXY(2 * i, j);
					printf("��");
				}
			}
		}


		//����Ű ���� ����
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) //���ʹ���Ű
		{
			g_stPlayer.x--;
			if (stage[g_stPlayer.x][g_stPlayer.y] == 1) g_stPlayer.x++;		//�ʹ����� ����������

			for (int i = 0; i <10; i++)		//���踦 �о����� 
			{
				if (g_stKey[i].bActive)
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
			}
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
		}


		//�ڹ��� ���
		for (int i = 0; i < 10; i++)
		{
			if (g_stLock[i].bActive)
			{
				GotoXY(g_stLock[i].x * 2, g_stLock[i].y);
				printf("��");
			}
		}


		//���� ���
		for (int i = 0; i < 10; i++)
		{
			if (g_stKey[i].bActive)
			{
				GotoXY(g_stKey[i].x * 2, g_stKey[i].y);
				printf("��");
			}
		}


		//�÷��̾� ���
		if (g_stPlayer.bActive)
		{
			GotoXY(g_stPlayer.x * 2, g_stPlayer.y);
			printf("��");
		}


		//�������� Ŭ���� ����
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
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

		clear = g_stKey[0].clearpoint + g_stKey[1].clearpoint + g_stKey[2].clearpoint + g_stKey[3].clearpoint;

		if (clear == g_stPlayer.clearpoint)
		{
			return 0;

			clear = 0;
		}

		Sleep(50);
	}

	return 0;
}