#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include<time.h>

#define UPWARD 72
#define DOWNWARD 80
#define LEFT 75
#define RIGHT 77

void invisible_cursor();
void gotoxy(int x, int y);
void random_seed();
void title_menu(void);
void game_screen(void);
void block_generator();
int key_input(int detection2);
void falling();
int detect_crash(int x, int y);
int detect_crash2(int x, int y);
void harden_block(int detection);
void new_block();
int one_line();
void delete_line(int k);

int block_form, next_block;
clock_t start_t, end_t;
int x = 4, y = 0;
int i, j;
int rotation = 0;
int score = 0;
int level = 1;



int map[18][12] = {
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
	    {1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1},
};

int tetrimino[7][4][4][4] = {
							{ //i자형 블록
								{
								  {0,0,1,0},
								  {0,0,1,0},
								  {0,0,1,0},
								  {0,0,1,0}
								},
								{
								  {0,0,0,0},
								  {0,0,0,0},
								  {0,0,0,0},
								  {1,1,1,1}
								},
							   {
								  {0,0,1,0},
								  {0,0,1,0},
								  {0,0,1,0},
								  {0,0,1,0}
								},
							   {
								  {0,0,0,0},
								  {0,0,0,0},
								  {0,0,0,0},
								  {1,1,1,1}
								}
										   },
							{ //o자형 블록
								{
								  {0,0,0,0},
								  {0,1,1,0},
								  {0,1,1,0},
								  {0,0,0,0}
								},
								{
								  {0,0,0,0},
								  {0,1,1,0},
								  {0,1,1,0},
								  {0,0,0,0}
								},
							   {
								  {0,0,0,0},
								  {0,1,1,0},
								  {0,1,1,0},
								  {0,0,0,0}
								},
							   {
								  {0,0,0,0},
								  {0,1,1,0},
								  {0,1,1,0},
								  {0,0,0,0}
								}
										   },
							{ //z형 블록
								{
								  {0,0,0,0},
								  {1,1,0,0},
								  {0,1,1,0},
								  {0,0,0,0}
								},
								{
								  {0,0,0,0},
								  {0,0,1,0},
								  {0,1,1,0},
								  {0,1,0,0}
								},
							   {
								  {0,0,0,0},
								  {1,1,0,0},
								  {0,1,1,0},
								  {0,0,0,0}
								},
							   {
								  {0,0,0,0},
								  {0,1,0,0},
								  {0,1,1,0},
								  {0,0,1,0}
								}
										   },
							{ //s자형 블록
								{
								  {0,0,0,0},
								  {0,1,1,0},
								  {1,1,0,0},
								  {0,0,0,0}
								},
								{
								  {0,0,0,0},
								  {0,1,0,0},
								  {0,1,1,0},
								  {0,0,1,0}
								},
							   {
								  {0,0,0,0},
								  {0,1,1,0},
								  {1,1,0,0},
								  {0,0,0,0}
								},
							   {
								  {0,0,0,0},
								  {0,1,0,0},
								  {0,1,1,0},
								  {0,0,1,0}
								}
										   },
							{ //j자형 블록
								{
								  {0,0,1,0},
								  {0,0,1,0},
								  {0,1,1,0},
								  {0,0,0,0}
								},
								{
								  {0,0,0,0},
								  {1,0,0,0},
								  {1,1,1,0},
								  {0,0,0,0}
								},
							   {
								  {0,1,1,0},
								  {0,1,0,0},
								  {0,1,0,0},
								  {0,0,0,0}
								},
							   {
								  {0,0,0,0},
								  {1,1,1,0},
								  {0,0,1,0},
								  {0,0,0,0}
								}
										   },
							{ //l자형 블록
								{
								  {0,1,0,0},
								  {0,1,0,0},
								  {0,1,1,0},
								  {0,0,0,0}
								},
								{
								  {0,0,0,0},
								  {1,1,1,0},
								  {1,0,0,0},
								  {0,0,0,0}
								},
							   {
								  {0,1,1,0},
								  {0,0,1,0},
								  {0,0,1,0},
								  {0,0,0,0}
								},
							   {
								  {0,0,0,0},
								  {0,0,1,0},
								  {1,1,1,0},
								  {0,0,0,0}
								}
										   },
							{ //t자형 블록
								{
								  {0,0,0,0},
								  {1,1,1,0},
								  {0,1,0,0},
								  {0,0,0,0}
								},
								{
								  {0,0,1,0},
								  {0,1,1,0},
								  {0,0,1,0},
								  {0,0,0,0}
								},
							   {
								  {0,0,0,0},
								  {0,1,0,0},
								  {1,1,1,0},
								  {0,0,0,0}
								},
							   {
								  {0,1,0,0},
								  {0,1,1,0},
								  {0,1,0,0},
								  {0,0,0,0}
								}
										   }
};

int main()
{
	int detection, detection2 = 0;
	int input;

	system("mode con cols=65 lines=26"); //화면 크기 조정

	invisible_cursor();
	title_menu();
	system("cls");
	random_seed();
	block_form = rand() % 7;
	next_block = rand() % 7;
	start_t = clock();
	while (1)
	{
		game_screen();
		block_generator();
		key_input(detection2);
		detection = detect_crash(x, y);
		detection2 = detect_crash2(x, y);
		harden_block(detection);
		one_line();
		falling();
			if (map[0][1] == 2|| map[0][2] == 2 || map[0][3] == 2 || map[0][4] == 2 || map[0][5] == 2 || map[0][6] == 2 || map[0][7] == 2 || map[0][8] == 2 || map[0][9] == 2 || map[0][10] == 2)
				break;
			if (score == 15)
				break;
	}
	if (score == 15)
	{
		system("cls");
		gotoxy(6, 1); printf("□□■□□□□■□□□■□□");
		gotoxy(6, 2); printf("□                        □");
		gotoxy(6, 3); printf("□      게임 클리어       ■");
		gotoxy(6, 4); printf("■                        □");
		gotoxy(6, 5); printf("□□□■□□□□□■□□□□");
		gotoxy(3, 8); printf(" 종료하시려면 아무키나 눌러주세요.");
		Sleep(1000);

		while (1)
		{
			if (_kbhit())
			{
				break;
			}
		}
	}
	else
	{
		system("cls");
		gotoxy(6, 1); printf("□□■□□□□■□□□■□□");
		gotoxy(6, 2); printf("□                        □");
		gotoxy(6, 3); printf("□       게임 오버        ■");
		gotoxy(6, 4); printf("■                        □");
		gotoxy(6, 5); printf("□□□■□□□□□■□□□□");
		gotoxy(3, 8); printf(" 종료하시려면 아무키나 눌러주세요.");
		Sleep(1000);
		while (1)
		{
			if (_kbhit())
			{
				break;
			}
		}
	}
    return 0;
}

void invisible_cursor() //커서 숨기는 함수
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void gotoxy(int x, int y) //좌표 이동 함수
{
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void random_seed() //랜덤 시드를 생성하는 함수
{
	srand(time(NULL));
}

void title_menu(void) //타이틀 메뉴 출력
{
	gotoxy(6, 1); printf("□□■□□□□■□□□■□□");
	gotoxy(6, 2); printf("□                        □");
	gotoxy(6, 3); printf("□                        ■");
	gotoxy(6, 4); printf("■                        □");
	gotoxy(6, 5); printf("□□□■□□□□□■□□□□");
	gotoxy(17, 3); printf("TETRIS");
	gotoxy(12, 12); printf("↑   : Shift");
	gotoxy(10, 13); printf("←  → : Left/Right");
	gotoxy(12, 14); printf("↓   : Drop Softly");
	gotoxy(9, 20); printf("Press Any Key to play...");

	while (1) //키 입력이 있는 경우 타이틀 메뉴를 벗어남
	{
		if (_kbhit())
		{
			break;
		}
	}

	while (_kbhit()) //버퍼 지우기
		_getch();
}

void game_screen(void) //게임 스크린 출력
{
	for (i = 0; i < 18; i++)   //게임 판 출력
		for (j = 0; j < 12; j++)
		{
			if (map[i][j] == 1)
			{
				gotoxy((j * 2), i);
				printf("□");
			}
			if (map[i][j] == 2)
			{
				gotoxy((j * 2), i);
				printf("■");
			}
		}

	gotoxy(42, 5); printf("Next");
	gotoxy(34, 5); printf("□□□□"); //다음에 나올 블록을 보여주는 칸과 점수와 현재 레벨 칸
	gotoxy(34, 6); printf("□");
	gotoxy(34, 7); printf("□");
	gotoxy(34, 8); printf("□");
	gotoxy(34, 9); printf("□");
	gotoxy(34, 10); printf("□");
	gotoxy(34, 11); printf("□□□□□□□□□□");
	gotoxy(46, 5); printf("□□□□");
	gotoxy(52, 6); printf("□");
	gotoxy(52, 7); printf("□");
	gotoxy(52, 8); printf("□");
	gotoxy(52, 9); printf("□");
	gotoxy(52, 10); printf("□");

	gotoxy(38, 13); printf("Score: %d", score);
	gotoxy(38, 15); printf("Level: %d/5", level);
	gotoxy(34, 12); printf("□");
	gotoxy(34, 13); printf("□");
	gotoxy(34, 14); printf("□");
	gotoxy(34, 15); printf("□");
	gotoxy(34, 16); printf("□");
	gotoxy(34, 17); printf("□□□□□□□□□□");
	gotoxy(52, 12); printf("□");
	gotoxy(52, 13); printf("□");
	gotoxy(52, 14); printf("□");
	gotoxy(52, 15); printf("□");
	gotoxy(52, 16); printf("□");

	for (i = 0; i < 4; i++)  //다음에 나올 블록 출력
		for (j = 0; j < 4; j++)
		{
			if (tetrimino[next_block][0][i][j] == 1)
			{
				gotoxy(40 + j * 2, 7 + i);
				printf("■");
			}
		}
}

void block_generator() //블록 생성
{
	if (rotation == 4)
	{
		rotation = 0;
	}

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			if (tetrimino[block_form][rotation][i][j] == 1)
			{
				gotoxy(x + j * 2, y + i);
				printf("■");
			}
		}
}

int key_input(int detection2) //사용자의 입력값을 받는 함수
{
	int input;

	if (_kbhit())
	{
		input = _getch();

		switch (input)
		{
		case UPWARD:
			if (block_form == 0&&detection2==0) //i자형이 회전할때 벽에 굳지 않기 위해서
			{
				if (rotation == 0 || rotation == 2) //i자형이 rotation 값 1 또는 3으로 회전할 때 x의 좌표가 16,-2,0 일 경우 회전하면 벽에 굳기 때문에 x의 값을 조정해주고 회전시킴
				{
					if (x == 16)
					{
						x -= 2;
						++rotation;
					}
					if (x == -2)
					{
						x += 4;
						++rotation;
					}
					if (x == 0)
					{
						x += 2;
						++rotation;
					}
					else
						++rotation;
				}
				else
					++rotation;
			}
			if ((block_form == 2 || block_form == 3 || block_form == 6) && detection2 == 0) //z, s, t자형이 회전할때 벽에 굳지 않기 위해서
			{
				if (rotation == 1 || rotation == 3)  //z, s, t자형이 rotation 값 2 또는 0으로 회전할 때 x의 좌표가 0 일 경우 회전하면 벽에 굳기 때문에 x의 값을 조정해주고 회전시킴
				{
					if (x == 0)
					{
						x += 2;
						++rotation;
					}
					else
						++rotation;
				}
				else
					++rotation;
			}
			if ((block_form == 4 || block_form == 5) && detection2 == 0) //j, l자형이 회전할때 벽에 굳지 않기 위해서
			{
				if (rotation == 0 || rotation == 2)  //j, l자형이 rotation 값 1 또는 3으로 회전할 때 x의 좌표가 0 일 경우 회전하면 벽에 굳기 때문에 x의 값을 조정해주고 회전시킴
				{
					if (x == 0)
					{
						x += 2;
						++rotation;
					}
					else
						++rotation;
				}
				else
					++rotation;
			}
			system("cls");
			break;

		case DOWNWARD:
			if (y!=16)
			{
				system("cls");
				y++;
				break;
			}

		case LEFT:
			if ((block_form == 2 || block_form == 3 || block_form == 6) && detection2 != 2)  //z, s, t자형이 왼쪽으로 이동할때 벽에 굳지 않기 위해서
			{
				if ((rotation == 0 || rotation == 2) && x != 2)  //rotation 값이 0 또는 2일 경우 x의 좌표값이 2이면 벽에 굳기 때문에 왼쪽으로 이동할 수 없음
					x -= 2;

				if ((rotation == 1 || rotation == 3) && x != 0)  //rotation 값이 1 또는 3일 경우 x의 좌표값이 0이면 벽에 굳기 때문에 왼쪽으로 이동할 수 없음
					x -= 2;
			}
			if ((block_form == 4 || block_form == 5) && detection2 != 2)  //j, l자형이 왼쪽으로 이동할때 벽에 굳지 않기 위해서
			{
				if ((rotation == 0 || rotation == 2) && x != 0)
					x -= 2;

				if ((rotation == 1 || rotation == 3) && x != 2)
					x -= 2;
			}
			if (block_form == 0 && detection2 != 2)  //i자형이 왼쪽으로 이동할때 벽에 굳지 않기 위해서
			{
				if ((rotation == 0 || rotation == 2) && x != -2)
					x -= 2;

				if ((rotation == 1 || rotation == 3) && x != 2)
					x -= 2;
			}

			if (block_form == 1 && x != 0 && detection2 != 2)  //o자형이 왼쪽으로 이동할때 벽에 굳지 않기 위해서
				x -= 2;

			system("cls");
			break;

		case RIGHT:
			if (block_form != 0 && x != 16 && detection2 != 1) //i자형을 제외한 블록들이 오른쪽으로 이동할때 벽에 굳지 않기 위해서 x의 좌표값이 16인 경우 오른쪽으로 이동 불가
				x += 2;

			if (block_form == 0 && x != 16 && detection2 != 1)
				if (rotation != 1 && rotation != 3)  //i자형이 rotation 값이 0 또는 2인 경우 x의 좌표값이 16인 경우 오른쪽으로 이동 불가
					x += 2;

			if (block_form == 0 && x != 14 && detection2 != 1)
				if (rotation == 1 || rotation == 3)  //i자형이 rotation 값이 1 또는 3인 경우 x의 좌표값이 14인 경우 오른쪽으로 이동 
					x += 2;

			system("cls");
			break;

		default:
			break;
		}
	}
}

void falling() //시간이 지나면 블록이 자동으로 아래로 떨어지는 함수
{
	end_t = clock();
	if ((float)(end_t - start_t) >= 1000 - level * 100) //레벨 1단계에서는 0.9초마다 아래로 떨어지며 레벨이 올라갈수록 더 빨리 떨어짐
	{
		if (detect_crash(x, y) != 1) //바로 밑에 바닥이 있을경우 내려가지 않음
		{
			y++;
			start_t = clock();
			system("cls");
		}
	}
}

int detect_crash(int x, int y)
{
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (tetrimino[block_form][rotation][i][j] == 1)
			{
				if (map[y + i + 1][x / 2 + j] == 1 || map[y + i + 1][x / 2 + j] == 2)
				{
					return 1; //바닥과 충돌하면 1을 return
				}
			}
	return 0; //바닥과 충돌하지 않으면 0을 return
}

int detect_crash2(int x, int y)
{
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (tetrimino[block_form][rotation][i][j] == 1)
			{
				if (map[y + i][x / 2 + j + 1] == 2)
				{
					return 1; //바닥과 충돌하면 1을 return
				}
				if (map[y + i][x / 2 + j - 1] == 2)
					return 2;
			}
	return 0; //바닥과 충돌하지 않으면 0을 return
}

void harden_block(int detection) //블록이 바닥과 충돌했을 경우 블록이 바닥에 굳고 새로운 블록을 생성하게 함
{

	if (detection == 1)
	{
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				if (tetrimino[block_form][rotation][i][j] == 1)
					map[y + i][x / 2 + j] = 2;
		new_block();
	}
}

void new_block() //새로운 블록을 생성하는 함수
{
	x = 4;
	y = 0;
	block_form = next_block;
	next_block = rand() % 7;
	rotation = 0;
}

int one_line() //i행의 모든 블록이 있는지 검사하는 함수
{
	for (i = 19; i >= 0; i--)
		if (map[i][1] == 2 && map[i][2] == 2 && map[i][3] == 2 && map[i][4] == 2 && map[i][5] == 2 && map[i][6] == 2 && map[i][7] == 2 && map[i][8] == 2 && map[i][9] == 2 && map[i][10] == 2)  //모든 i행에 블록이 있는경우
		{
			delete_line(i);
		}
}

void delete_line(int i)  //i행의 모든 블록이 채워진 경우 i행의 블록이 지워지고 i 위 행의 블록들이 한칸씩 내려가는 함수
{
	for (j = 1; j < 11; j++)
		map[i][j] = 0;     //모든 i행의 블록이 채워진 경우 i행의 블록이 지워짐

	for (; i >= 0; i--)
		for (j = 1; j < 11; j++)
			if (map[i - 1][j] == 2)
			{
				map[i][j] = 2;
				map[i - 1][j] = 0;   //모든 i행의 블록이 지워지고 i행 위의 블록이 한칸씩 내려감
			}
	score++;

	if (score == 2 || score == 4 || score == 7 || score == 10) //각각의 스코어의 달성시 레벨이 상승함
		level++;
}