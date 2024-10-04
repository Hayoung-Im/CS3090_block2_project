#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
using namespace std;
const int BOARD_X = 40;
const int BOARD_Y = 28;
const int MAP_X = 12;
const int MAP_Y = 22;
int gameMap[MAP_Y][MAP_X];	//0 = blank, 1 = shadow, 2 = built, 3 = block, 4 = wall
clock_t startTime = 0, pauseTime = 0;				//Game time, Pause time check
clock_t cntTime = 0;		//variable to time DropBlock
clock_t dropTime = 0, raiseTime = 0;
int dropTimeSet = 1000;		//cntTime - determine what dropTime DropBlock  executed
int raiseTimeSet = 2100000000;		//cntTime - determine when block go up [raiseTime]
bool fallen = false;			//block reach bottom, turns true
void gotoxy(int x, int y);
class Block
{
private:
	int p1_X; int p1_Y;			//block value
	int p2_X; int p2_Y;
	int p3_X; int p3_Y;
	int p4_X; int p4_Y;
	int rotAxisX; int rotAxisY;	//rotation x&y value
	int numRot;					//# of rotate
	int blockShape;				//block shape
public:
	void InIt(void)
	{
		p1_X = 0, p1_Y = 0;
		p2_X = 0, p2_Y = 0;
		p3_X = 0, p3_Y = 0;
		p4_X = 0, p4_Y = 0;
		rotAxisX = 0, rotAxisY = 0;
		numRot = 0;
		blockShape = 0;
	}
	bool MakeBlock(void)		//Game over
	{
		int i, j;
		srand(clock());
		int blockNumber = rand() % 7;
		switch (blockNumber)
		{
		case 0:			//T shape
			i = 2;
			j = 4;
			p1_X = j; p1_Y = i;
			p2_X = j + 1; p2_Y = i;
			p3_X = j + 2; p3_Y = i;
			p4_X = j + 1; p4_Y = i - 1;
			rotAxisX = j + 1; rotAxisY = i;
			numRot = 0;
			blockShape = 0;
			if (gameMap[p1_Y][p1_X] == 2 ||
				gameMap[p2_Y][p2_X] == 2 ||
				gameMap[p3_Y][p3_X] == 2 ||
				gameMap[p4_Y][p4_X] == 2)
				return true;
			break;
		case 1:			// shape 1
			i = 1;
			j = 4;
			p1_X = j; p1_Y = i;
			p2_X = j + 1; p2_Y = i;
			p3_X = j + 1; p3_Y = i + 1;
			p4_X = j + 2; p4_Y = i + 1;
			rotAxisX = j + 1; rotAxisY = i;
			numRot = 0;
			blockShape = 1;
			if (gameMap[p1_Y][p1_X] == 2 ||
				gameMap[p2_Y][p2_X] == 2 ||
				gameMap[p3_Y][p3_X] == 2 ||
				gameMap[p4_Y][p4_X] == 2)
				return true;
			break;
		case 2:			// shape 2
			i = 1;
			j = 5;
			p1_X = j; p1_Y = i;
			p2_X = j + 1; p2_Y = i;
			p3_X = j - 1; p3_Y = i + 1;
			p4_X = j; p4_Y = i + 1;
			rotAxisX = j; rotAxisY = i;
			numRot = 0;
			blockShape = 2;
			if (gameMap[p1_Y][p1_X] == 2 ||
				gameMap[p2_Y][p2_X] == 2 ||
				gameMap[p3_Y][p3_X] == 2 ||
				gameMap[p4_Y][p4_X] == 2)
				return true;
			break;
		case 3:			// L shape
			i = 1;
			j = 4;
			p1_X = j; p1_Y = i;
			p2_X = j; p2_Y = i + 1;
			p3_X = j + 1; p3_Y = i + 1;
			p4_X = j + 2; p4_Y = i + 1;
			rotAxisX = j + 1; rotAxisY = i;
			numRot = 0;
			blockShape = 3;
			if (gameMap[p1_Y][p1_X] == 2 ||
				gameMap[p2_Y][p2_X] == 2 ||
				gameMap[p3_Y][p3_X] == 2 ||
				gameMap[p4_Y][p4_X] == 2)
				return true;
			break;
		case 4:			//L shape opposite
			i = 2;
			j = 4;
			p1_X = j; p1_Y = i;
			p2_X = j + 1; p2_Y = i;
			p3_X = j + 2; p3_Y = i;
			p4_X = j + 2; p4_Y = i - 1;
			rotAxisX = j + 1; rotAxisY = i - 1;
			numRot = 0;
			blockShape = 4;
			if (gameMap[p1_Y][p1_X] == 2 ||
				gameMap[p2_Y][p2_X] == 2 ||
				gameMap[p3_Y][p3_X] == 2 ||
				gameMap[p4_Y][p4_X] == 2)
				return true;
			break;
		case 5:			//1shape
			i = 1;
			j = 4;
			p1_X = j; p1_Y = i;
			p2_X = j + 1; p2_Y = i;
			p3_X = j + 2; p3_Y = i;
			p4_X = j + 3; p4_Y = i;
			rotAxisX = j + 2; rotAxisY = i;
			numRot = 0;
			blockShape = 5;
			if (gameMap[p1_Y][p1_X] == 2 ||
				gameMap[p2_Y][p2_X] == 2 ||
				gameMap[p3_Y][p3_X] == 2 ||
				gameMap[p4_Y][p4_X] == 2)
				return true;
			break;
		case 6:			//ㅁshape
			i = 1;
			j = 4;
			p1_X = j; p1_Y = i;
			p2_X = j + 1; p2_Y = i;
			p3_X = j; p3_Y = i + 1;
			p4_X = j + 1; p4_Y = i + 1;
			rotAxisX = 0; rotAxisY = 0;
			numRot = 0;
			blockShape = 6;
			if (gameMap[p1_Y][p1_X] == 2 ||
				gameMap[p2_Y][p2_X] == 2 ||
				gameMap[p3_Y][p3_X] == 2 ||
				gameMap[p4_Y][p4_X] == 2)
				return true;
			break;
		}
		gameMap[p1_Y][p1_X] = 3;
		gameMap[p2_Y][p2_X] = 3;
		gameMap[p3_Y][p3_X] = 3;
		gameMap[p4_Y][p4_X] = 3;
		return false;
	}
	void MakeShadow(void)
	{
		int tp1_X = p1_X; int tp1_Y = p1_Y;	
		int tp2_X = p2_X; int tp2_Y = p2_Y;
		int tp3_X = p3_X; int tp3_Y = p3_Y;
		int tp4_X = p4_X; int tp4_Y = p4_Y;

		gameMap[tp1_Y][tp1_X] = 0;					
		gameMap[tp2_Y][tp2_X] = 0;
		gameMap[tp3_Y][tp3_X] = 0;
		gameMap[tp4_Y][tp4_X] = 0;

		while (gameMap[tp1_Y + 1][tp1_X] < 2 &&
			gameMap[tp2_Y + 1][tp2_X] < 2 &&
			gameMap[tp3_Y + 1][tp3_X] < 2 &&
			gameMap[tp4_Y + 1][tp4_X] < 2)	
		{
			++tp1_Y;
			++tp2_Y;
			++tp3_Y;
			++tp4_Y;
		}
		gameMap[tp1_Y][tp1_X] = 1;					
		gameMap[tp2_Y][tp2_X] = 1;
		gameMap[tp3_Y][tp3_X] = 1;
		gameMap[tp4_Y][tp4_X] = 1;

		gameMap[p1_Y][p1_X] = 3;		
		gameMap[p2_Y][p2_X] = 3;
		gameMap[p3_Y][p3_X] = 3;
		gameMap[p4_Y][p4_X] = 3;
	}
	void EraseShadow(void)
	{
		int tp1_X = p1_X; int tp1_Y = p1_Y;	
		int tp2_X = p2_X; int tp2_Y = p2_Y;
		int tp3_X = p3_X; int tp3_Y = p3_Y;
		int tp4_X = p4_X; int tp4_Y = p4_Y;

		gameMap[tp1_Y][tp1_X] = 0;					
		gameMap[tp2_Y][tp2_X] = 0;
		gameMap[tp3_Y][tp3_X] = 0;
		gameMap[tp4_Y][tp4_X] = 0;

		while (gameMap[tp1_Y + 1][tp1_X] < 2 &&
			gameMap[tp2_Y + 1][tp2_X] < 2 &&
			gameMap[tp3_Y + 1][tp3_X] < 2 &&
			gameMap[tp4_Y + 1][tp4_X] < 2)	
		{
			++tp1_Y;
			++tp2_Y;
			++tp3_Y;
			++tp4_Y;
		}
		gameMap[tp1_Y][tp1_X] = 0;					
		gameMap[tp2_Y][tp2_X] = 0;
		gameMap[tp3_Y][tp3_X] = 0;
		gameMap[tp4_Y][tp4_X] = 0;

		gameMap[p1_Y][p1_X] = 3;		
		gameMap[p2_Y][p2_X] = 3;
		gameMap[p3_Y][p3_X] = 3;
		gameMap[p4_Y][p4_X] = 3;
	}
	bool MoveBlock(void)		
	{
		int input;							
		if (_kbhit())
		{
			gameMap[p1_Y][p1_X] = 0;	
			gameMap[p2_Y][p2_X] = 0;
			gameMap[p3_Y][p3_X] = 0;
			gameMap[p4_Y][p4_X] = 0;

			input = _getch();
			if (input == 224)
			{
				input = _getch();
				switch (input)
				{
				case 72:	//위
					RotateBlock();
					break;
				case 80:	//아래
					if (!(gameMap[p1_Y + 1][p1_X] < 2 &&
						gameMap[p2_Y + 1][p2_X] < 2 &&
						gameMap[p3_Y + 1][p3_X] < 2 &&
						gameMap[p4_Y + 1][p4_X] < 2))	
					{
						gameMap[p1_Y][p1_X] = 2;		
						gameMap[p2_Y][p2_X] = 2;
						gameMap[p3_Y][p3_X] = 2;
						gameMap[p4_Y][p4_X] = 2;
						return true;
					}
					++p1_Y;
					++p2_Y;
					++p3_Y;
					++p4_Y;
					++rotAxisY;
					break;
				case 75:	//왼쪽
					if (!(gameMap[p1_Y][p1_X - 1] < 2 &&
						gameMap[p2_Y][p2_X - 1] < 2 &&
						gameMap[p3_Y][p3_X - 1] < 2 &&
						gameMap[p4_Y][p4_X - 1] < 2))	
						break;
					--p1_X;
					--p2_X;
					--p3_X;
					--p4_X;
					--rotAxisX;
					break;
				case 77:	
					if (!(gameMap[p1_Y][p1_X + 1] < 2 &&
						gameMap[p2_Y][p2_X + 1] < 2 &&
						gameMap[p3_Y][p3_X + 1] < 2 &&
						gameMap[p4_Y][p4_X + 1] < 2))	
						break;
					++p1_X;
					++p2_X;
					++p3_X;
					++p4_X;
					++rotAxisX;
					break;
				default:
					break;
				}
			}
			else if (input == 32)		
			{
				while (gameMap[p1_Y + 1][p1_X] < 2 &&
					gameMap[p2_Y + 1][p2_X] < 2 &&
					gameMap[p3_Y + 1][p3_X] < 2 &&
					gameMap[p4_Y + 1][p4_X] < 2)	
				{
					++p1_Y;
					++p2_Y;
					++p3_Y;
					++p4_Y;
				}
				gameMap[p1_Y][p1_X] = 2;		
				gameMap[p2_Y][p2_X] = 2;
				gameMap[p3_Y][p3_X] = 2;
				gameMap[p4_Y][p4_X] = 2;
				return true;
			}
			else if (input == 112 || input == 80)			
			{
				gotoxy(13, 5);
				printf("  Pause");
				clock_t PT1 = clock();
				system("pause>null");					
				clock_t PT2 = clock();
				pauseTime += PT2 - PT1;
			}
			gameMap[p1_Y][p1_X] = 3;		
			gameMap[p2_Y][p2_X] = 3;
			gameMap[p3_Y][p3_X] = 3;
			gameMap[p4_Y][p4_X] = 3;
		}										
		return false;
	}
	void RotateBlock(void)
	{
		switch (blockShape)
		{
		case 0:
			if (numRot % 4 == 0)
			{
				if (!(gameMap[rotAxisY + 1][rotAxisX] < 2 &&
					gameMap[rotAxisY][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX] < 2))
					break;
				p1_X = rotAxisX; p1_Y = rotAxisY + 1;
				p4_X = rotAxisX - 1; p4_Y = rotAxisY;
				p3_X = rotAxisX; p3_Y = rotAxisY - 1;
				++numRot;
			}
			else if (numRot % 4 == 1)
			{
				if (!(gameMap[rotAxisY][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX] < 2 &&
					gameMap[rotAxisY][rotAxisX - 1] < 2))
					break;
				p1_X = rotAxisX + 1; p1_Y = rotAxisY;
				p4_X = rotAxisX; p4_Y = rotAxisY + 1;
				p3_X = rotAxisX - 1; p3_Y = rotAxisY;
				++numRot;
			}
			else if (numRot % 4 == 2)
			{
				if (!(gameMap[rotAxisY - 1][rotAxisX] < 2 &&
					gameMap[rotAxisY][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX] < 2))
					break;
				p1_X = rotAxisX; p1_Y = rotAxisY - 1;
				p4_X = rotAxisX + 1; p4_Y = rotAxisY;
				p3_X = rotAxisX; p3_Y = rotAxisY + 1;
				++numRot;
			}
			else if (numRot % 4 == 3)
			{
				if (!(gameMap[rotAxisY][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX] < 2 &&
					gameMap[rotAxisY][rotAxisX + 1] < 2))
					break;
				p1_X = rotAxisX - 1; p1_Y = rotAxisY;
				p4_X = rotAxisX; p4_Y = rotAxisY - 1;
				p3_X = rotAxisX + 1; p3_Y = rotAxisY;
				++numRot;
			}
			break;
		case 1:
			if (numRot % 2 == 0)
			{
				if (!(gameMap[rotAxisY - 1][rotAxisX] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY][rotAxisX - 1] < 2))
					break;
				p1_X = rotAxisX; p1_Y = rotAxisY - 1;
				p4_X = rotAxisX - 1; p4_Y = rotAxisY + 1;
				p3_X = rotAxisX - 1; p3_Y = rotAxisY;
				++numRot;
			}
			else if (numRot % 2 == 1)
			{
				if (!(gameMap[rotAxisY][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX] < 2))
					break;
				p1_X = rotAxisX - 1; p1_Y = rotAxisY;
				p4_X = rotAxisX + 1; p4_Y = rotAxisY + 1;
				p3_X = rotAxisX; p3_Y = rotAxisY + 1;
				++numRot;
			}
			break;
		case 2:
			if (numRot % 2 == 0)
			{
				if (!(gameMap[rotAxisY - 1][rotAxisX] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY][rotAxisX + 1] < 2))
				{
					break;
				}
				p2_X = rotAxisX; p2_Y = rotAxisY - 1;
				p3_X = rotAxisX + 1; p3_Y = rotAxisY + 1;
				p4_X = rotAxisX + 1; p4_Y = rotAxisY;
				++numRot;
			}
			else if (numRot % 2 == 1)
			{
				if (!(gameMap[rotAxisY][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX] < 2))
					break;
				p2_X = rotAxisX + 1; p2_Y = rotAxisY;
				p3_X = rotAxisX - 1; p3_Y = rotAxisY + 1;
				p4_X = rotAxisX; p4_Y = rotAxisY + 1;
				++numRot;
			}
			break;
		case 3:
			if (numRot % 4 == 0)
			{
				if (!(gameMap[rotAxisY + 1][rotAxisX] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX + 1] < 2))
					break;
				p1_X = rotAxisX; p1_Y = rotAxisY + 1;
				p2_X = rotAxisX + 1; p2_Y = rotAxisY + 1;
				p3_X = rotAxisX + 1; p3_Y = rotAxisY;
				p4_X = rotAxisX + 1; p4_Y = rotAxisY - 1;
				++numRot;
			}
			else if (numRot % 4 == 1)
			{
				if (!(gameMap[rotAxisY][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX - 1] < 2))
					break;
				p1_X = rotAxisX + 1; p1_Y = rotAxisY;
				p2_X = rotAxisX + 1; p2_Y = rotAxisY - 1;
				p3_X = rotAxisX; p3_Y = rotAxisY - 1;
				p4_X = rotAxisX - 1; p4_Y = rotAxisY - 1;
				++numRot;
			}
			else if (numRot % 4 == 2)
			{
				if (!(gameMap[rotAxisY - 1][rotAxisX] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX - 1] < 2))
					break;
				p1_X = rotAxisX; p1_Y = rotAxisY - 1;
				p2_X = rotAxisX - 1; p2_Y = rotAxisY - 1;
				p3_X = rotAxisX - 1; p3_Y = rotAxisY;
				p4_X = rotAxisX - 1; p4_Y = rotAxisY + 1;
				++numRot;
			}
			else if (numRot % 4 == 3)
			{
				if (!(gameMap[rotAxisY][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX + 1] < 2))
					break;
				p1_X = rotAxisX - 1; p1_Y = rotAxisY;
				p2_X = rotAxisX - 1; p2_Y = rotAxisY + 1;
				p3_X = rotAxisX; p3_Y = rotAxisY + 1;
				p4_X = rotAxisX + 1; p4_Y = rotAxisY + 1;
				++numRot;
			}
			break;
		case 4:
			if (numRot % 4 == 0)
			{
				if (!(gameMap[rotAxisY + 1][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX] < 2))
					break;
				p1_X = rotAxisX + 1; p1_Y = rotAxisY + 1;
				p2_X = rotAxisX + 1; p2_Y = rotAxisY;
				p3_X = rotAxisX + 1; p3_Y = rotAxisY - 1;
				p4_X = rotAxisX; p4_Y = rotAxisY - 1;
				++numRot;
			}
			else if (numRot % 4 == 1)
			{
				if (!(gameMap[rotAxisY - 1][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY][rotAxisX - 1] < 2))
					break;
				p1_X = rotAxisX + 1; p1_Y = rotAxisY - 1;
				p2_X = rotAxisX; p2_Y = rotAxisY - 1;
				p3_X = rotAxisX - 1; p3_Y = rotAxisY - 1;
				p4_X = rotAxisX - 1; p4_Y = rotAxisY;
				++numRot;
			}
			else if (numRot % 4 == 2)
			{
				if (!(gameMap[rotAxisY - 1][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX] < 2))
					break;
				p1_X = rotAxisX - 1; p1_Y = rotAxisY - 1;
				p2_X = rotAxisX - 1; p2_Y = rotAxisY;
				p3_X = rotAxisX - 1; p3_Y = rotAxisY + 1;
				p4_X = rotAxisX; p4_Y = rotAxisY + 1;
				++numRot;
			}
			else if (numRot % 4 == 3)
			{
				if (!(gameMap[rotAxisY + 1][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY][rotAxisX + 1] < 2))
					break;
				p1_X = rotAxisX - 1; p1_Y = rotAxisY + 1;
				p2_X = rotAxisX; p2_Y = rotAxisY + 1;
				p3_X = rotAxisX + 1; p3_Y = rotAxisY + 1;
				p4_X = rotAxisX + 1; p4_Y = rotAxisY;
				++numRot;
			}
			break;
		case 5:
			if (numRot % 2 == 0)
			{
				if (!(gameMap[rotAxisY + 2][rotAxisX] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX] < 2))
					break;
				p1_X = rotAxisX; p1_Y = rotAxisY + 2;
				p2_X = rotAxisX; p2_Y = rotAxisY + 1;
				p4_X = rotAxisX; p4_Y = rotAxisY - 1;
				++numRot;
			}
			else if (numRot % 2 == 1)
			{
				if (!(gameMap[rotAxisY][rotAxisX - 2] < 2 &&
					gameMap[rotAxisY][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY][rotAxisX + 1] < 2))
					break;
				p1_X = rotAxisX - 2; p1_Y = rotAxisY;
				p2_X = rotAxisX - 1; p2_Y = rotAxisY;
				p4_X = rotAxisX + 1; p4_Y = rotAxisY;
				++numRot;
			}
			break;
		case 6:
			break;
		default:
			break;
		}
	}
	bool DropBlock(void)			
	{
		gameMap[p1_Y][p1_X] = 0;
		gameMap[p2_Y][p2_X] = 0;
		gameMap[p3_Y][p3_X] = 0;
		gameMap[p4_Y][p4_X] = 0;

		if (!(gameMap[p1_Y + 1][p1_X] < 2 &&
			gameMap[p2_Y + 1][p2_X] < 2 &&
			gameMap[p3_Y + 1][p3_X] < 2 &&
			gameMap[p4_Y + 1][p4_X] < 2))	
		{
			gameMap[p1_Y][p1_X] = 2;		
			gameMap[p2_Y][p2_X] = 2;
			gameMap[p3_Y][p3_X] = 2;
			gameMap[p4_Y][p4_X] = 2;
			return true;
		}
		++p1_Y;
		++p2_Y;
		++p3_Y;
		++p4_Y;
		++rotAxisY;
		gameMap[p1_Y][p1_X] = 3;		
		gameMap[p2_Y][p2_X] = 3;
		gameMap[p3_Y][p3_X] = 3;
		gameMap[p4_Y][p4_X] = 3;
		return false;
	}
};
struct Score
{
	int _score;
	int combo;
	bool comboON;
	void InIt(void)
	{
		_score = 0;
		combo = 0;
		comboON = false;
	}
};
Block block;
Score score;
void CursorView(char show)		
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
void gotoxy(int x, int y)	
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void ShowBoard(void)
{
	int i;
	gotoxy(0, 0);						
	printf("┏");
	for (i = 1; i < BOARD_X; i++)
	{
		gotoxy(2 * i, 0);
		printf("━");
	}
	gotoxy(2 * BOARD_X, 0);
	printf("┓");
	for (i = 1; i < BOARD_Y; i++)
	{
		gotoxy(2 * BOARD_X, i);
		printf("┃");
	}
	gotoxy(2 * BOARD_X, BOARD_Y);
	printf("┛");
	for (i = 1; i < BOARD_X; i++)
	{
		gotoxy(2 * i, BOARD_Y);
		printf("━");
	}
	gotoxy(0, BOARD_Y);
	printf("┗");
	for (i = 1; i < BOARD_Y; i++)
	{
		gotoxy(0, i);
		printf("┃");
	}									

	gotoxy(15, 7);
	printf("■■■  ■■■   ■■■  ■■■  ■■■  ■■■");
	gotoxy(15, 8);
	printf("■    ■         ■    ■  ■    ■    ■    ");
	gotoxy(15, 9);
	printf("■    ■■■     ■    ■■      ■    ■■■");
	gotoxy(15, 10);
	printf("■    ■         ■    ■  ■    ■        ■");
	gotoxy(15, 11);
	printf("■    ■■■     ■    ■  ■  ■■■  ■■■");

	while (!_kbhit())
	{
		gotoxy(30, 20);
		printf("- Press any button -");
		Sleep(400);
		gotoxy(30, 20);
		printf("                    ");
		Sleep(400);
	}
	_getch();	
}
void InIt(void)		
{
	for (int i = 0; i < MAP_Y; ++i)
		for (int j = 0; j < MAP_X; ++j)
			if (j == 0 || j == 11 || i == 21)
				gameMap[i][j] = 4;
			else
				gameMap[i][j] = 0;
	block.InIt();
	score.InIt();
	startTime = 0, pauseTime = 0;
	cntTime = 0;
	dropTime = 0, raiseTime = 0;
	dropTimeSet = 1000;
	raiseTimeSet = 2100000000;
	fallen = false;
}
void ShowMenu(void)
{
	int i;
	gotoxy(0, 0);						
	printf("┏");
	for (i = 1; i < BOARD_X; i++)
	{
		gotoxy(2 * i, 0);
		printf("━");
	}
	gotoxy(2 * BOARD_X, 0);
	printf("┓");
	for (i = 1; i < BOARD_Y; i++)
	{
		gotoxy(2 * BOARD_X, i);
		printf("┃");
	}
	gotoxy(2 * BOARD_X, BOARD_Y);
	printf("┛");
	for (i = 1; i < BOARD_X; i++)
	{
		gotoxy(2 * i, BOARD_Y);
		printf("━");
	}
	gotoxy(0, BOARD_Y);
	printf("┗");
	for (i = 1; i < BOARD_Y; i++)
	{
		gotoxy(0, i);
		printf("┃");
	}									

	gotoxy(32, 8);
	printf("Line score: 100");
	gotoxy(32, 9);
	printf("Combo score: 100");
	gotoxy(32, 11);
	printf("Speed : ←    →");
	gotoxy(55, 11);
	printf("Rising Line :");
	gotoxy(67, 10);
	printf("↑");
	gotoxy(67, 12);
	printf("↓");
	gotoxy(32, 12);
	printf("Start : SpaceBar");
	gotoxy(32, 13);
	printf("Pause : p");

}
void ShowMap(void)
{
	int i, j;							
	for (i = 0; i < MAP_Y; i++)
	{
		gotoxy(6, i + 3);
		for (j = 0; j < MAP_X; j++)
			if (gameMap[i][j] == 0)		
				printf("  ");
			else if (gameMap[i][j] == 1)		
				printf("▨ ");
			else if (gameMap[i][j] == 2)		
				printf("■ ");
			else if (gameMap[i][j] == 3)		
				printf("■ ");
			else if (gameMap[i][j] == 4)		
				printf("□ ");
	}
	gotoxy(32, 3);						
	printf("Time  :  %d:%02d", ((cntTime - startTime) / 1000) / 60, ((cntTime - startTime) / 1000) % 60);
	gotoxy(32, 5);						
	printf("Score :  %d", score._score);
	gotoxy(32, 6);
	printf("Combo :  %d", score.combo);
	gotoxy(42, 11);						
	printf("%2d", 11 - dropTimeSet / 100);
	gotoxy(67, 11);						
	printf("%2d", raiseTimeSet == 2100000000 ? 0 : 11 - raiseTimeSet / 1000);
}
void ClearLine(void)
{
	int i, j;
	int x, y;
	int check;
	score.comboON = false;			
	for (i = 1; i < 21; i++)
	{
		check = 0;						
		for (j = 1; j < 11; j++)
			if (gameMap[i][j] == 0)		
				break;
			else if (gameMap[i][j] == 2)
				check++;
		if (check == 10)				
		{
			for (y = i; y > 0; y--)
				for (x = 1; x < 11; x++)
					gameMap[y][x] = gameMap[y - 1][x];	
			for (x = 1; x < 11; x++)
				gameMap[0][x] = 0;					
			score._score += 100;	
			score.comboON = true;						
		}
	}
	if (!score.comboON)		
		score.combo = 0;		
	if (score.combo != 0)		
		score._score = score._score + (100 * score.combo);	
	if (score.comboON)		
		++score.combo;		
}
bool RaiseGround()	
{
	int i, j;
	bool crashCheck = false;
	srand(clock());
	int hole = (rand() % 10) + 1;

	for (i = 0; i < 20; i++)				//블록이랑 충돌체크
		for (j = 1; j < 11; j++)
			if (gameMap[i][j] == 3 && gameMap[i + 1][j] == 2)
				crashCheck = true;

	if (crashCheck)					//충돌시
	{
		for (i = 0; i < 20; i++)
			for (j = 1; j < 11; j++)
			{
				gameMap[i][j] = gameMap[i + 1][j];
				if (gameMap[i][j] == 3)
					gameMap[i][j] = 2;
			}
		for (j = 1; j < 11; j++)
			if (j == hole)
				gameMap[20][j] = 0;
			else
				gameMap[20][j] = 2;
		return true;
	}
	else
	{
		for (i = 0; i < 20; i++)
			for (j = 1; j < 11; j++)
				if (gameMap[i][j] == 3)
					gameMap[i][j] = 3;
				else if (gameMap[i + 1][j] == 3)
					gameMap[i][j] = 0;
				else
					gameMap[i][j] = gameMap[i + 1][j];
		for (j = 1; j < 11; j++)
			if (j == hole)
				gameMap[20][j] = 0;
			else
				gameMap[20][j] = 2;
	}
	return false;
}
int DropSpeed(void)			
{
	int input;							
	if (_kbhit())
	{
		input = _getch();
		if (input == 224)
		{
			input = _getch();
			switch (input)
			{
			case 72:	
				if (raiseTimeSet == 2100000000)
				{
					raiseTimeSet = 10000;
					return 2;
				}
				else if (raiseTimeSet > 1000)
				{
					raiseTimeSet = raiseTimeSet - 1000;
					return 2;
				}
				break;
			case 80:	
				if (raiseTimeSet == 10000)
				{
					raiseTimeSet = 2100000000;
					return 2;
				}
				else if (raiseTimeSet < 10000)
				{
					raiseTimeSet = raiseTimeSet + 1000;
					return 2;
				}
				break;
			case 75:	
				if (dropTimeSet < 1000)
				{
					dropTimeSet = dropTimeSet + 100;
					return 2;
				}
				break;
			case 77:	
				if (dropTimeSet > 100)
				{
					dropTimeSet = dropTimeSet - 100;
					return 2;
				}
				break;
			default:
				break;
			}
		}
		else if (input == 32)	
			return 1;
	}						
	return 0;
}
void GameOver(void)
{
	int i;
	gotoxy(11, 5);
	printf("  Game  Over");
	for (i = 0; i < 2; i++)
	{
		Sleep(400);
		gotoxy(11, 5);
		printf("            ");
		Sleep(400);
		gotoxy(11, 5);
		printf("  Game  Over");
	}
}
int main(void)
{
	CursorView(0);
	ShowBoard();
	while (true)
	{
		InIt();
		system("cls");			
		ShowMenu();
		ShowMap();
		while (true)	
		{
			bool breakLoop = false;
			switch (DropSpeed())
			{
			case 1:
				breakLoop = true;
				break;
			case 2:
				ShowMap();
				break;
			default:
				break;
			}
			if (breakLoop)
				break;
			Sleep(30);
		}
		startTime = clock();
		raiseTime = clock();
		while (true)
		{
			if (!block.MakeBlock())	
			{
				dropTime = clock() - pauseTime;
				while (true)
				{
					fallen = block.MoveBlock();
					cntTime = clock() - pauseTime;
					if (!fallen)
						block.MakeShadow();
					ShowMap();
					if (!fallen)
						block.EraseShadow();
					if (cntTime - dropTime > dropTimeSet)			
					{
						fallen = block.DropBlock();
						if (!fallen)
							block.MakeShadow();
						ShowMap();
						if (!fallen)
							block.EraseShadow();
						dropTime = clock() - pauseTime;
					}
					if (fallen)	
					{
						ClearLine();	
						break;	
					}
					if (cntTime - raiseTime > raiseTimeSet)			
					{
						fallen = RaiseGround();
						if (!fallen)
							block.MakeShadow();
						ShowMap();
						if (!fallen)
							block.EraseShadow();
						raiseTime = clock() - pauseTime;
					}
					if (fallen)	
					{
						ClearLine();	
						break;	
					}
					Sleep(30);
				}
			}
			else
				break;
		}
		GameOver();		
		system("pause>null");
	}
	return 0;
}
