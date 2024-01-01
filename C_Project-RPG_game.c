#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>

//키보드 방향키 정의
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACEBAR 32

//캐릭터 점프를 위한 bool변수
bool isJumping = false;
bool isFlying = false;
bool isBottom = true;

//커서 안보이게 하기
void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

//캐릭터
typedef struct _character {
	char name[10];
	int HP;
	int money;
	int attack;
}character;

typedef struct _monster {
	int HP;
	int attack;
}monster;

void gotoxy(int x, int y);
void init();
void titleDraw();
void menuDraw();
int Choicemenu();
void GamestartDraw(character* user, int s);
void GamestockDraw(FILE* userinformation, character* user, int s);
void OptionDraw();
void OptionErase();
int Option(int* y);
void DrawCharacter(int* x, int* y);
void Character(int* x, int* y, int* a, character* user, monster* bug, int s, FILE* userinformation, FILE* space);
void DrawWeapon(int* x, int* y);
void Attack(int* x, int* y);
void DrawMonster(int* x, int* y, int* count, monster* bug);
void Monster(int* x, int* y, int* count, character* user, monster* bug, int s);
void StatusDraw();
void StatusRenew(character* user, int s);
bool Damaged(int* x, int* y, int* a);
bool Damaging(int* x, int* y, int* a);
void StoreDraw();
void StoreErase();
int Store(int* y, int s, character* user);

int stockcount; //저장 - 종료 : 동적할당 -1 X, 저장X - 종료 : 동적할당 -1 위한 변수
int userstock; //유저 저장 수 -> 매개변수 s 그냥 둠
int direction = 1; //무기 방향을 위한 변수 오른쪽 1, 왼쪽 -1
int characterdirection = 0; //캐릭터 방향을 위한 변수 평소 0, 오른 1, 왼 -1

int main() {
	//커서없애기
	CursorView();

	FILE* UserInformation = NULL; //유저 저장 위한 파일
	FILE* Space = NULL; //usersock 저장을 위한 파일

	character* User = (character*)malloc(sizeof(character));

	// 맨 처음 실행 시 파일 생성 
	if (userstock <= 1);
	else {
		Space = fopen("space.txt", "w");
		fclose(Space);
	}

	while (1)
	{

		//저장한 space 불러오기
		Space = fopen("space.txt", "r");
		fscanf(Space, "%d", &userstock);
		fclose(Space);

		//userstock이 프로그램 종료 후 다시 시작해도 초기화 되지 않도록 조건
		if (1 <= userstock);
		else
			userstock = 0;

		monster Bug;
		Bug.HP = 20, Bug.attack = 5; //몬스터 초기 설정

		init();
		titleDraw();
		menuDraw();

		switch (Choicemenu()) {
		case 1:
			system("cls");
			userstock += 1;
			User = (character*)realloc(User, sizeof(character) * userstock);
			GamestartDraw(User, userstock - 1); //닉네임 받기
			User[userstock - 1].HP = 100, User[userstock - 1].money = 0, User[userstock - 1].attack = 5; //캐릭터 초기 설정 !!HP = 100 받으면 UI에 이상하게 뜸.
			system("cls");


			stockcount = 0;
			int x = 45, y = 22, a = 100, b = 24, count = 1;
			gotoxy(0, 25);
			for (int i = 0; i <= 110; i++) {
				printf("-");
			}
			for (int i = 0; i < 25; i++) {
				gotoxy(110, i);
				printf("|");
			}
			StatusDraw();

			while (1) {
				Character(&x, &y, &a, User, &Bug, userstock - 1, UserInformation, Space);
				Monster(&a, &b, &count, User, &Bug, userstock - 1);
				StatusRenew(User, userstock - 1);
			}

			break;
		case 2:
			system("cls");
			gotoxy(0, 25);
			for (int i = 0; i <= 110; i++) {
				printf("-");
			}
			for (int i = 0; i < 25; i++) {
				gotoxy(110, i);
				printf("|");
			}
			GamestockDraw(UserInformation, User, userstock);
			if (userstock >= 1) {
				char c = _getch();
				if (c == 'y')
				{
					//userstock += 1;
					User = (character*)realloc(User, sizeof(character) * userstock);

					UserInformation = fopen("usertest1.txt", "r");
					fscanf(UserInformation, "%s %d %d %d", &User[userstock - 1].name, &User[userstock - 1].HP, &User[userstock - 1].money, &User[userstock - 1].attack);
					fclose(UserInformation);

					system("cls");

					stockcount = 0;
					int x = 45, y = 22, a = 100, b = 24, count = 1;
					gotoxy(0, 25);
					for (int i = 0; i <= 110; i++) {
						printf("-");
					}
					for (int i = 0; i < 25; i++) {
						gotoxy(110, i);
						printf("|");
					}
					StatusDraw();

					while (1) {
						Character(&x, &y, &a, User, &Bug, userstock - 1, UserInformation, Space);
						Monster(&a, &b, &count, User, &Bug, userstock - 1);
						StatusRenew(User, userstock - 1);
					}
				}
			}
			system("cls");
			break;
		case 3:
			system("cls");
			gotoxy(0, 25);
			for (int i = 0; i <= 110; i++) {
				printf("-");
			}
			for (int i = 0; i < 25; i++) {
				gotoxy(110, i);
				printf("|");
			}
			gotoxy(44, 12);
			printf("게임을 종료합니다.");
			exit(1);
			gotoxy(0, 26);
			break;
		}
	}

	free(User);
	return 0;
}

void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void init()
{
	system("mode con cols = 110 lines = 25 | title RPG게임");
}

void titleDraw()
{
	printf("\n\n\n\n\n\n");
	//40, 6에서 시작
	printf("\t\t\t\t   ######       #      #     #  #######     \n");
	printf("\t\t\t\t  #            # #     ##   ##  #           \n");
	printf("\t\t\t\t  #    ###    #####    # # # #  #######     \n");
	printf("\t\t\t\t  #     ##   #     #   #  #  #  #           \n");
	printf("\t\t\t\t   ##### #  #       #  #     #  #######     \n");
	gotoxy(0, 25);
	for (int i = 0; i <= 110; i++) {
		printf("-");
	}
	for (int i = 0; i < 25; i++) {
		gotoxy(110, i);
		printf("|");
	}
}

void menuDraw()
{
	gotoxy(87, 1);
	printf("방향키 ↑ / ↓ : 이동");
	gotoxy(87, 2);
	printf("스페이스바 : 선택");

	gotoxy(48, 15);
	printf("게 임 시 작");
	gotoxy(48, 16);
	printf("저장된 게임");
	gotoxy(48, 17);
	printf("   종 료   ");
	gotoxy(0, 25);

}

int Choicemenu()
{
	int y = 15, choice = 0;
	char c;
	gotoxy(46, y);
	printf(">");
	while (choice != 1)
	{
		if (_kbhit())
		{
			c = _getch();
			if (c == -32)
			{
				c = _getch();
				switch (c)
				{
				case UP:
					gotoxy(46, y);
					printf(" ");
					y--;
					if (y < 15) {
						y = 17;
					}
					break;
				case DOWN:
					gotoxy(46, y);
					printf(" ");
					y++;
					if (y > 17) {
						y = 15;
					}
					break;
				}
			}
			gotoxy(46, y);
			printf(">");
			if (c == 32) {
				choice = 1;
				if (y == 15)
					return 1;
				else if (y == 16)
					return 2;
				else
					return 3;
			}
		}
		gotoxy(0, 25);
	}
}

void GamestartDraw(character* user, int s)
{
	gotoxy(0, 25);
	for (int i = 0; i <= 110; i++) {
		printf("-");
	}
	for (int i = 0; i < 25; i++) {
		gotoxy(110, i);
		printf("|");
	}

	gotoxy(0, 0);
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t     닉네임을 정하세요\n");
	printf("\t\t\t\t\t┌────────────────────────┐\n");
	printf("\t\t\t\t\t│                        │\n");//컴퓨터마다 위치 다른 듯
	printf("\t\t\t\t\t└────────────────────────┘\n");
	gotoxy(42, 12);
	scanf("%s", (*(user + s)).name);
}

void OptionDraw()
{
	gotoxy(0, 0);
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t              메뉴\n");
	printf("\t\t\t\t\t┌────────────────────────────┐\n");
	printf("\t\t\t\t\t│          계 속 하 기       │\n");
	printf("\t\t\t\t\t│          저 장 하 기       │\n");
	printf("\t\t\t\t\t│            종   료         │\n");
	printf("\t\t\t\t\t└────────────────────────────┘");
}

void OptionErase()
{
	gotoxy(0, 10);
	printf("\t\t\t\t\t                                \n");
	printf("\t\t\t\t\t                                \n");
	printf("\t\t\t\t\t                                \n");
	printf("\t\t\t\t\t                                \n");
	printf("\t\t\t\t\t                                \n");
	printf("\t\t\t\t\t                                ");
}

int Option(int* y)
{
	char c;
	if (_kbhit())
	{
		c = _getch();
		if (c == -32)
		{
			c = _getch();
			switch (c)
			{
			case UP:
				gotoxy(50, *y);
				printf(" ");
				(*y)--;
				if (*y < 12) {
					*y = 14;
				}
				break;
			case DOWN:
				gotoxy(50, *y);
				printf(" ");
				(*y)++;
				if (*y > 14) {
					*y = 12;
				}
				break;
			}
			gotoxy(50, *y);
			printf(">");
		}
		if (c == 32) {
			if (*y == 12)
				return 1;
			else if (*y == 13)
				return 2;
			else
				return 3;
		}
	}
}


//DrawCharacter, Character 포인터 중요! -> 변하는 x, y값을 그때마다 저장해야할 필요 있음.

void DrawCharacter(int* x, int* y)
{
	gotoxy(*x, *y);
	printf(" @ ");
	if (characterdirection == 1)
	{
		gotoxy(*x, *y + 1);
		printf("/|o");
		gotoxy(*x, *y + 2);
		printf("/ )");
	}
	else if (characterdirection == -1)
	{
		gotoxy(*x, *y + 1);
		printf("o|\\");
		gotoxy(*x, *y + 2);
		printf("( \\");
	}
	else
	{
		gotoxy(*x, *y + 1);
		printf("(|)");
		gotoxy(*x, *y + 2);
		printf("/ \\");
	}
}

void Character(int* x, int* y, int* a, character* user, monster* bug, int s, FILE* userinformation, FILE* space)
{

	const int gravity = 1;
	char c;

	//점프 누른 뒤 점프 상태일 경우 -> 이렇게 하지 않을 경우 점프가 눌러야만 되거나 점프 진행할 동안 몬스터 등 다른 함수 코딩이 작동 안함.
	if (isFlying == true)
	{
		for (int i = 0; i < 3; i++) {
			gotoxy(*x, *y + i);
			printf("   ");
		}
		if (isJumping) {
			*y -= gravity;
		}
		else
			*y += gravity;
		if (direction == 1) {
			gotoxy(*x + 3, *y + 2);
			printf(" ");
			gotoxy(*x + 3, *y - 2);
			printf(" ");
		}
		else if (direction == -1) {
			gotoxy(*x - 1, *y + 2);
			printf(" ");
			gotoxy(*x - 1, *y - 2);
			printf(" ");
		}
		if (*y >= 22) {
			*y = 22;
			isBottom = true;
			isFlying = false;
		}
		if (*y <= 15)
			isJumping = false;
	}

	//점프를 누르지 않은 평소일 경우
	else
	{
		if (_kbhit())
		{
			c = _getch();
			if (c == -32)
			{
				c = _getch();
				switch (c)
				{
				case RIGHT:
					direction = 1;
					characterdirection = 1;
					if (*x == 106); //오른쪽 벽 확인
					else {
						for (int i = 0; i < 3; i++) {
							gotoxy(*x, *y + i);
							printf("   ");
						}
						(*x)++;
					}
					break;
				case LEFT:
					direction = -1;
					characterdirection = -1;
					if (*x == 1); //왼쪽 벽 확인
					else {
						for (int i = 0; i < 3; i++) {
							gotoxy(*x, *y + i);
							printf("   ");
						}
						(*x)--;
					}
					break;
				case UP:
					if (*y == 22) {
						isFlying = true;
						isJumping = true;
						isBottom = false;
					}
					break;
					//상점 구현
				case DOWN:
					StoreDraw();
					int y = 12, choice = 0;
					gotoxy(45, y);
					printf(">");
					while (choice != 1)
					{
						if (Store(&y, s, user) == 1) {
							choice = 1;
							StoreErase();
						}
						StatusRenew(user, s);
					}
					break;
				}
			}

			//공격
			else if (c == SPACEBAR)
			{
				Attack(x, y);
				if (Damaging(x, y, a)) {
					(*bug).HP -= (*(user + s)).attack;
				}
			}

			//중간 메뉴  ※※※키보드 상시 입력받는 곳이 character함수이기에 이 함수에서 키보드 입력을 주로 해야함. 만약 main while(1)에서 키보드 입력을 더 받는다면 character를 포함해 키보드 입력이 2개가 되어 게임 진행 코드가 꼬이게 됨.
			else if (c == 27)
			{
				OptionDraw();
				int y = 12, choice = 0;
				gotoxy(50, y);
				printf(">");
				while (choice != 1)
				{
					if (Option(&y) == 1) {
						choice = 1;
						OptionErase();
					}
					else if (Option(&y) == 2) {
						choice = 1;
						stockcount = 1;
						OptionErase();
						//space 저장
						space = fopen("space.txt", "w");
						fprintf(space, "%d", s + 1);
						fclose(space);
						//유저 저장
						userinformation = fopen("usertest1.txt", "w");
						fprintf(userinformation, "%s %d %d %d", user[s].name, user[s].HP, user[s].money, user[s].attack);
						fclose(userinformation);
						gotoxy(50, 15);
						printf("저장되었습니다.");
						Sleep(2000);
						gotoxy(50, 15);
						printf("               ");
					}
					else if (Option(&y) == 3) {
						choice = 1;
						if (stockcount == 0) { //게임 한 판 내 종료 전 저장을 했는지 안 했는지 여부
							free(user);
							// 0메모리 동적할당 해도 되나?
						}
						system("cls");
						gotoxy(0, 25);
						for (int i = 0; i <= 110; i++) {
							printf("-");
						}
						for (int i = 0; i < 25; i++) {
							gotoxy(110, i);
							printf("|");
						}
						gotoxy(44, 12);
						printf("게임을 종료합니다.");
						gotoxy(0, 26);
						exit(1);
					}
				}
			}
		}
	}

	//몬스터랑 닿았을 경우
	if (Damaged(x, y, a)) {
		(*(user + s)).HP = (*(user + s)).HP - (*bug).attack;
		Sleep(100); //수정 필요. 잠깐 무적 상태
	}
	//HP < 0 일 경우
	if ((*(user + s)).HP <= 0)
	{
		for (int i = 0; i < 4; i++)
		{
			gotoxy(*x - 1, *y - 1 + i);
			printf("     ");
		}
		(*(user + s)).money -= 50;
		gotoxy(50, 10);
		printf("< D E A T H >");
		Sleep(2000);
		gotoxy(50, 10);
		printf("             ");
		(*(user + s)).HP = 100;
		*x = 45, * y = 22;
	}

	DrawCharacter(x, y);
	DrawWeapon(x, y);
	characterdirection = 0;
}

void DrawMonster(int* x, int* y, int* count, monster* bug)
{
	if (*count == 1)
	{
		gotoxy(*x + 1, *y - 1);
		printf("%d", (*bug).HP);
		gotoxy(*x, *y);
		printf("@QQQ");
	}
	else if (*count == -1)
	{
		gotoxy(*x + 1, *y - 1);
		printf("%d", (*bug).HP);
		gotoxy(*x, *y);
		printf("QQQ@");
	}
}

void Monster(int* x, int* y, int* count, character* user, monster* bug, int s)
{
	if ((*bug).HP <= 0)
	{
		gotoxy(*x + 1, *y - 1);
		printf("  ");
		gotoxy(*x, *y);
		printf("    ");
		(*(user + s)).money += 10;
		Sleep(1000);
		(*bug).HP = 20;
		*x = 100, * y = 24;
	}
	else
	{
		gotoxy(*x + 1, *y - 1);
		printf("  ");
		gotoxy(*x, *y);
		printf("    ");
		*x -= *count;
		if (*x == 1 || *x == 106)
			*count *= -1;
		DrawMonster(x, y, count, bug);
		Sleep(50);
	}
}

void DrawWeapon(int* x, int* y)
{
	//오른쪽 방향
	if (direction == 1) {
		for (int i = 0; i < 3; i++) {
			gotoxy(*x - 2, *y - 1 + i);
			printf(" ");
		}
		gotoxy(*x + 2, *y - 1);
		printf(" ");

		gotoxy(*x + 3, *y - 1);
		printf("|");
		gotoxy(*x + 3, *y);
		printf("|");
		gotoxy(*x + 3, *y + 1);
		printf("T");
	}
	//왼쪽 방향
	else if (direction == -1) {
		for (int i = 0; i < 3; i++) {
			gotoxy(*x + 4, *y - 1 + i);
			printf(" ");
		}
		gotoxy(*x, *y - 1);
		printf(" ");

		gotoxy(*x - 1, *y - 1);
		printf("|");
		gotoxy(*x - 1, *y);
		printf("|");
		gotoxy(*x - 1, *y + 1);
		printf("T");
	}
}

void Attack(int* x, int* y)
{
	//오른쪽 공격
	if (direction == 1)
	{
		for (int i = 0; i < 3; i++) {
			gotoxy(*x + 4, *y + i);
			printf(">");
		}
		Sleep(30);
		for (int i = 0; i < 3; i++) {
			gotoxy(*x + 4, *y + i);
			printf(" ");
		}
	}
	//왼쪽 공격
	else if (direction == -1)
	{
		for (int i = 0; i < 3; i++) {
			gotoxy(*x - 2, *y + i);
			printf("<");
		}
		Sleep(30);
		for (int i = 0; i < 3; i++) {
			gotoxy(*x - 2, *y + i);
			printf(" ");
		}
	}
}

void StatusDraw()
{
	gotoxy(0, 0);
	printf("┌─────────────────┐\n");
	printf("│                 │\n");
	printf("│                 │\n");
	printf("│                 │\n");
	printf("│                 │\n");
	printf("└─────────────────┘");
	gotoxy(2, 1);
	printf("Name :");
	gotoxy(2, 2);
	printf("HP :");
	gotoxy(2, 3);
	printf("Money :");
	gotoxy(2, 4);
	printf("Attack :");

	gotoxy(87, 1);
	printf("방향키 ← / → : 이동");
	gotoxy(87, 2);
	printf("방향키 ↑ : 점프");
	gotoxy(87, 3);
	printf("방향키 ↓ : 상점");
	gotoxy(87, 4);
	printf("스페이스바 : 공격/선택");
	gotoxy(87, 5);
	printf("ESC : 메뉴");
}

void StatusRenew(character* user, int s)
{
	gotoxy(9, 1);
	printf("%s", (*(user + s)).name);
	gotoxy(7, 2);
	printf("%-3d", (*(user + s)).HP);
	gotoxy(10, 3);
	printf("%-3d", (*(user + s)).money);
	gotoxy(11, 4);
	printf("%-2d", (*(user + s)).attack);
}

bool Damaged(int* x, int* y, int* a)
{
	//그나마 제일 범위 오차 적은 코딩.
	for (int i = 0; i < 3; i++) {
		if (*a <= *x + i && *x + i <= *a + 3 && *y + 2 == 24)
			return true; //공격 받음.
		else
			return false;
	}
}

bool Damaging(int* x, int* y, int* a)
{
	//일단 몬스터가 1종류뿐이라 맞는 공간이 정해져 있어 간단히 코딩.
	if (direction == 1)
	{
		if (*a <= *x + 4 && *x + 4 <= *a + 3 && *y + 2 == 24)
			return true;
		else
			return false;
	}
	else if (direction == -1)
	{
		if (*a <= *x - 2 && *x - 2 <= *a + 3 && *y + 2 == 24)
			return true;
		else
			return false;
	}
}

void GamestockDraw(FILE* userinformation, character* user, int s)
{
	character print = { NULL, };
	gotoxy(45, 9);
	printf(" 최근 저장된 게임\n");
	gotoxy(42, 11);
	printf("지금까지 저장한 횟수 : %d", s);

	if (s >= 1) {
		userinformation = fopen("usertest1.txt", "r");
		fscanf(userinformation, "%s %d %d %d", &print.name, &print.HP, &print.money, &print.attack);
		fclose(userinformation);
	}

	gotoxy(48, 14);
	printf("NAME : %s", print.name);
	gotoxy(48, 15);
	printf("  HP : %-3d", print.HP);
	gotoxy(47, 16);
	printf("MONEY : %-3d", print.money);
	gotoxy(46, 17);
	printf("ATTACK : %-2d", print.attack);
	gotoxy(0, 26);

	gotoxy(80, 5);
	printf("이어서 하기 : y");
	gotoxy(80, 6);
	printf("뒤로가기 : 아무키");
}

void StoreDraw()
{
	gotoxy(0, 0);
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t              상점\n");
	printf("\t\t\t\t\t┌────────────────────────────┐\n");
	printf("\t\t\t\t\t│         계 속 하 기        │\n");
	printf("\t\t\t\t\t│      $10 - HP 5 상승       │\n");
	printf("\t\t\t\t\t│      $20 - Attack 1 상승   │\n");
	printf("\t\t\t\t\t│                            │\n");
	printf("\t\t\t\t\t└────────────────────────────┘");
}

void StoreErase()
{
	gotoxy(0, 10);
	printf("\t\t\t\t\t                                \n");
	printf("\t\t\t\t\t                                \n");
	printf("\t\t\t\t\t                                \n");
	printf("\t\t\t\t\t                                \n");
	printf("\t\t\t\t\t                                \n");
	printf("\t\t\t\t\t                                \n");
	printf("\t\t\t\t\t                                ");
}

int Store(int* y, int s, character* user)
{
	char c;
	if (_kbhit())
	{
		c = _getch();
		if (c == -32)
		{
			c = _getch();
			switch (c)
			{
			case UP:
				gotoxy(45, *y);
				printf(" ");
				(*y)--;
				if (*y < 12) {
					*y = 14;
				}
				break;
			case DOWN:
				gotoxy(45, *y);
				printf(" ");
				(*y)++;
				if (*y > 14) {
					*y = 12;
				}
				break;
			}
			gotoxy(45, *y);
			printf(">");
		}
		if (c == 32) {
			if (*y == 12)
				return 1;
			else if (*y == 13) {
				if ((*(user + s)).money >= 10) {
					(*(user + s)).money -= 10;
					(*(user + s)).HP += 5;
					gotoxy(52, 15);
					printf("HP + 5 !");
					Sleep(1000);
					gotoxy(52, 15);
					printf("        ");
				}
				else {
					gotoxy(48, 15);
					printf("돈이 부족합니다.");
					Sleep(1000);
					gotoxy(48, 15);
					printf("                ");
				}
			}
			else {
				if ((*(user + s)).money >= 20) {
					(*(user + s)).money -= 20;
					(*(user + s)).attack += 1;
					gotoxy(50, 15);
					printf("Attack + 1 !");
					Sleep(1000);
					gotoxy(50, 15);
					printf("            ");
				}
				else {
					gotoxy(48, 15);
					printf("돈이 부족합니다.");
					Sleep(1000);
					gotoxy(48, 15);
					printf("                ");
				}
			}
		}
	}
}
