#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>

//Ű���� ����Ű ����
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACEBAR 32

//ĳ���� ������ ���� bool����
bool isJumping = false;
bool isFlying = false;
bool isBottom = true;

//Ŀ�� �Ⱥ��̰� �ϱ�
void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

//ĳ����
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

int stockcount; //���� - ���� : �����Ҵ� -1 X, ����X - ���� : �����Ҵ� -1 ���� ����
int userstock; //���� ���� �� -> �Ű����� s �׳� ��
int direction = 1; //���� ������ ���� ���� ������ 1, ���� -1
int characterdirection = 0; //ĳ���� ������ ���� ���� ��� 0, ���� 1, �� -1

int main() {
	//Ŀ�����ֱ�
	CursorView();

	FILE* UserInformation = NULL; //���� ���� ���� ����
	FILE* Space = NULL; //usersock ������ ���� ����

	character* User = (character*)malloc(sizeof(character));

	// �� ó�� ���� �� ���� ���� 
	if (userstock <= 1);
	else {
		Space = fopen("space.txt", "w");
		fclose(Space);
	}

	while (1)
	{

		//������ space �ҷ�����
		Space = fopen("space.txt", "r");
		fscanf(Space, "%d", &userstock);
		fclose(Space);

		//userstock�� ���α׷� ���� �� �ٽ� �����ص� �ʱ�ȭ ���� �ʵ��� ����
		if (1 <= userstock);
		else
			userstock = 0;

		monster Bug;
		Bug.HP = 20, Bug.attack = 5; //���� �ʱ� ����

		init();
		titleDraw();
		menuDraw();

		switch (Choicemenu()) {
		case 1:
			system("cls");
			userstock += 1;
			User = (character*)realloc(User, sizeof(character) * userstock);
			GamestartDraw(User, userstock - 1); //�г��� �ޱ�
			User[userstock - 1].HP = 100, User[userstock - 1].money = 0, User[userstock - 1].attack = 5; //ĳ���� �ʱ� ���� !!HP = 100 ������ UI�� �̻��ϰ� ��.
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
			printf("������ �����մϴ�.");
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
	system("mode con cols = 110 lines = 25 | title RPG����");
}

void titleDraw()
{
	printf("\n\n\n\n\n\n");
	//40, 6���� ����
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
	printf("����Ű �� / �� : �̵�");
	gotoxy(87, 2);
	printf("�����̽��� : ����");

	gotoxy(48, 15);
	printf("�� �� �� ��");
	gotoxy(48, 16);
	printf("����� ����");
	gotoxy(48, 17);
	printf("   �� ��   ");
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
	printf("\t\t\t\t\t     �г����� ���ϼ���\n");
	printf("\t\t\t\t\t����������������������������������������������������\n");
	printf("\t\t\t\t\t��                        ��\n");//��ǻ�͸��� ��ġ �ٸ� ��
	printf("\t\t\t\t\t����������������������������������������������������\n");
	gotoxy(42, 12);
	scanf("%s", (*(user + s)).name);
}

void OptionDraw()
{
	gotoxy(0, 0);
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t              �޴�\n");
	printf("\t\t\t\t\t������������������������������������������������������������\n");
	printf("\t\t\t\t\t��          �� �� �� ��       ��\n");
	printf("\t\t\t\t\t��          �� �� �� ��       ��\n");
	printf("\t\t\t\t\t��            ��   ��         ��\n");
	printf("\t\t\t\t\t������������������������������������������������������������");
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


//DrawCharacter, Character ������ �߿�! -> ���ϴ� x, y���� �׶����� �����ؾ��� �ʿ� ����.

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

	//���� ���� �� ���� ������ ��� -> �̷��� ���� ���� ��� ������ �����߸� �ǰų� ���� ������ ���� ���� �� �ٸ� �Լ� �ڵ��� �۵� ����.
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

	//������ ������ ���� ����� ���
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
					if (*x == 106); //������ �� Ȯ��
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
					if (*x == 1); //���� �� Ȯ��
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
					//���� ����
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

			//����
			else if (c == SPACEBAR)
			{
				Attack(x, y);
				if (Damaging(x, y, a)) {
					(*bug).HP -= (*(user + s)).attack;
				}
			}

			//�߰� �޴�  �ءء�Ű���� ��� �Է¹޴� ���� character�Լ��̱⿡ �� �Լ����� Ű���� �Է��� �ַ� �ؾ���. ���� main while(1)���� Ű���� �Է��� �� �޴´ٸ� character�� ������ Ű���� �Է��� 2���� �Ǿ� ���� ���� �ڵ尡 ���̰� ��.
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
						//space ����
						space = fopen("space.txt", "w");
						fprintf(space, "%d", s + 1);
						fclose(space);
						//���� ����
						userinformation = fopen("usertest1.txt", "w");
						fprintf(userinformation, "%s %d %d %d", user[s].name, user[s].HP, user[s].money, user[s].attack);
						fclose(userinformation);
						gotoxy(50, 15);
						printf("����Ǿ����ϴ�.");
						Sleep(2000);
						gotoxy(50, 15);
						printf("               ");
					}
					else if (Option(&y) == 3) {
						choice = 1;
						if (stockcount == 0) { //���� �� �� �� ���� �� ������ �ߴ��� �� �ߴ��� ����
							free(user);
							// 0�޸� �����Ҵ� �ص� �ǳ�?
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
						printf("������ �����մϴ�.");
						gotoxy(0, 26);
						exit(1);
					}
				}
			}
		}
	}

	//���Ͷ� ����� ���
	if (Damaged(x, y, a)) {
		(*(user + s)).HP = (*(user + s)).HP - (*bug).attack;
		Sleep(100); //���� �ʿ�. ��� ���� ����
	}
	//HP < 0 �� ���
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
	//������ ����
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
	//���� ����
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
	//������ ����
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
	//���� ����
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
	printf("��������������������������������������\n");
	printf("��                 ��\n");
	printf("��                 ��\n");
	printf("��                 ��\n");
	printf("��                 ��\n");
	printf("��������������������������������������");
	gotoxy(2, 1);
	printf("Name :");
	gotoxy(2, 2);
	printf("HP :");
	gotoxy(2, 3);
	printf("Money :");
	gotoxy(2, 4);
	printf("Attack :");

	gotoxy(87, 1);
	printf("����Ű �� / �� : �̵�");
	gotoxy(87, 2);
	printf("����Ű �� : ����");
	gotoxy(87, 3);
	printf("����Ű �� : ����");
	gotoxy(87, 4);
	printf("�����̽��� : ����/����");
	gotoxy(87, 5);
	printf("ESC : �޴�");
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
	//�׳��� ���� ���� ���� ���� �ڵ�.
	for (int i = 0; i < 3; i++) {
		if (*a <= *x + i && *x + i <= *a + 3 && *y + 2 == 24)
			return true; //���� ����.
		else
			return false;
	}
}

bool Damaging(int* x, int* y, int* a)
{
	//�ϴ� ���Ͱ� 1�������̶� �´� ������ ������ �־� ������ �ڵ�.
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
	printf(" �ֱ� ����� ����\n");
	gotoxy(42, 11);
	printf("���ݱ��� ������ Ƚ�� : %d", s);

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
	printf("�̾ �ϱ� : y");
	gotoxy(80, 6);
	printf("�ڷΰ��� : �ƹ�Ű");
}

void StoreDraw()
{
	gotoxy(0, 0);
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t              ����\n");
	printf("\t\t\t\t\t������������������������������������������������������������\n");
	printf("\t\t\t\t\t��         �� �� �� ��        ��\n");
	printf("\t\t\t\t\t��      $10 - HP 5 ���       ��\n");
	printf("\t\t\t\t\t��      $20 - Attack 1 ���   ��\n");
	printf("\t\t\t\t\t��                            ��\n");
	printf("\t\t\t\t\t������������������������������������������������������������");
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
					printf("���� �����մϴ�.");
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
					printf("���� �����մϴ�.");
					Sleep(1000);
					gotoxy(48, 15);
					printf("                ");
				}
			}
		}
	}
}
