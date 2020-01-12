#include <stdio.h>
#include <windows.h>
#include "Console.h"
#include <conio.h>
#pragma warning(disable: 4996)

//�ܼ�â ũ��
#define WIDTH 60
#define LENGTH 20

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


//���谡 ���� ��ġ�� ���� - ��.. �ش翭�迡 ���Ͽ� �ٸ������ ��ĥ��� ��ǥ�̵��ε� ������ �� �������� �Ӹ��� ����
void OverLapingLeftZero(int count)
{
	for (int i = 1; i < count; i++)
	{
		if (g_stKey[0].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[1].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[1].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[2].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[2].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[3].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[3].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[4].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[4].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[5].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[5].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[6].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[6].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[7].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[7].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[8].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[8].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[9].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[0].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[1].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[1].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[2].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[2].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[3].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[3].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[4].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[4].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[5].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[5].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[6].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[6].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[7].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[7].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[8].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[8].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[9].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[0].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[1].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[1].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[2].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[2].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[3].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[3].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[4].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[4].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[5].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[5].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[6].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[6].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[7].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[7].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[8].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[8].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[9].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[0].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[1].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[1].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[2].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[2].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[3].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[3].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[4].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[4].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[5].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[5].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[6].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[6].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[7].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[7].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[8].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[8].x == g_stKey[i].x)		//��ġ�� �ʰ�
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
		if (g_stKey[9].x == g_stKey[i].x)		//��ġ�� �ʰ�
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

//���۸޴�
void StartMenu()
{
	//�ܼ�â ũ�� ����
	SetConsoleSize(WIDTH, LENGTH);


	while (1) {
		Clear();
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
void InitStage()
{
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
		g_stPlayer.x = 1;
		g_stPlayer.y = 1;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 3;

		//���� ��ǥ ����
		g_stKey[0].x = 2;
		g_stKey[0].y = 2;
		g_stKey[0].bActive = true;

		g_stKey[1].x = 3;
		g_stKey[1].y = 2;
		g_stKey[1].bActive = true;

		g_stKey[2].x = 2;
		g_stKey[2].y = 3;
		g_stKey[2].bActive = true;

		//�ڹ��� ��ǥ ����
		g_stLock[0].x = 7;
		g_stLock[0].y = 3;
		g_stLock[0].bActive = true;

		g_stLock[1].x = 7;
		g_stLock[1].y = 4;
		g_stLock[1].bActive = true;

		g_stLock[2].x = 7;
		g_stLock[2].y = 5;
		g_stLock[2].bActive = true;

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
		g_stPlayer.x = 2;
		g_stPlayer.y = 3;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 4;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 5;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
	if (stage_bActive[3])
	{
		//�÷��̾� ��ǥ ����
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 5;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
	//�������� 6 �ʱ�ȭ
	if (stage_bActive[3])
	{
		//�÷��̾� ��ǥ ����
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 5;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
	//�������� 7 �ʱ�ȭ
	if (stage_bActive[3])
	{
		//�÷��̾� ��ǥ ����
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 5;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
	//�������� 8 �ʱ�ȭ
	if (stage_bActive[3])
	{
		//�÷��̾� ��ǥ ����
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 5;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
	//�������� 9 �ʱ�ȭ
	if (stage_bActive[3])
	{
		//�÷��̾� ��ǥ ����
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 5;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
	//�������� 10 �ʱ�ȭ
	if (stage_bActive[3])
	{
		//�÷��̾� ��ǥ ����
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 5;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
	//�������� 11 �ʱ�ȭ
	if (stage_bActive[3])
	{
		//�÷��̾� ��ǥ ����
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 5;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
	//�������� 12 �ʱ�ȭ
	if (stage_bActive[3])
	{
		//�÷��̾� ��ǥ ����
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 5;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
	//�������� 13 �ʱ�ȭ
	if (stage_bActive[3])
	{
		//�÷��̾� ��ǥ ����
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 5;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
	//�������� 14 �ʱ�ȭ
	if (stage_bActive[3])
	{
		//�÷��̾� ��ǥ ����
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 5;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
	//�������� 15 �ʱ�ȭ
	if (stage_bActive[3])
	{
		//�÷��̾� ��ǥ ����
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 5;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
	//�������� 16 �ʱ�ȭ
	if (stage_bActive[3])
	{
		//�÷��̾� ��ǥ ����
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 5;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
	//�������� 17 �ʱ�ȭ
	if (stage_bActive[3])
	{
		//�÷��̾� ��ǥ ����
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 5;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
	//�������� 18 �ʱ�ȭ
	if (stage_bActive[3])
	{
		//�÷��̾� ��ǥ ����
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 5;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
	//�������� 19 �ʱ�ȭ
	if (stage_bActive[3])
	{
		//�÷��̾� ��ǥ ����
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 5;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
	//�������� 20 �ʱ�ȭ
	if (stage_bActive[3])
	{
		//�÷��̾� ��ǥ ����
		g_stPlayer.x = 1;
		g_stPlayer.y = 2;
		g_stPlayer.bActive = true;

		//Ŭ���� ���� ���� (����,�ڹ����� ������ ����)
		g_stPlayer.clearpoint = 5;

		//���� ��ǥ ����
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


		//�ڹ��� ��ǥ ����
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
	printf("Stage: %d", stagephase + 1);
	GotoXY((WIDTH * 2) / 3 + 2, 4);
	printf("If you want to");
	GotoXY((WIDTH * 2) / 3 + 2, 5);
	printf("reset press 'R'");
	GotoXY((WIDTH * 2) / 3 + 2, 7);
	printf("If you want to");
	GotoXY((WIDTH * 2) / 3 + 2, 8);
	printf("quit press 'ESC'");
	GotoXY((WIDTH * 2) / 3 + 2, 10);
	printf("Control: �����");
	GotoXY((WIDTH * 2) / 3 + 2, 12);
	printf("Move �� to ��");

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

//����Ű ����
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

		OverLapingLeft(g_stPlayer.clearpoint);
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
		OverLapingRight(g_stPlayer.clearpoint);
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
		OverLapingUp(g_stPlayer.clearpoint);
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
		OverLapingDown(g_stPlayer.clearpoint);
	}

	//�������� �����
	if (GetAsyncKeyState('R') & 0x8000)
	{
		stagestate = false;
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
}

//���� �Լ�
void Ending()
{
	while (1) {
		Clear();
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
		
		//���ӽ���
		while (stagestate)
		{	
			//ȭ�������
			Clear();

			//�������� ���
			PrintStage();

			//����Ű ����
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