#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>
#include <Windows.h>
#include <time.h>

#define DEFAULT_X 0
#define DEFAULT_Y 0
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define MAP_SIZE 22
#define WALL 1
#define EMPTY 0
#define HEAD 2
#define TAIL 3
#define FRUIT 5
#define HIT 10
#define TRUE 1
#define FALSE 0

typedef int MData;

typedef struct _fruitxy {
	int x;
	int y;
	int numOfFruit;
} FruitPos;

typedef struct _snakexp {
	int x;
	int y;
} SnakePos;

typedef struct _mynode {
	SnakePos data;
	struct _mynode *next;
} Node;

typedef struct _myqueue {
	Node * rear;
	Node * front;
} MyQueue;
typedef MyQueue Queue;

void QueueInit(Queue * pq) {
	pq->rear = NULL;
	pq->front = NULL;
}
int isEmpty(Queue * pq) {
	if (pq->front == NULL)
		return TRUE;
	else
		return FALSE;
}

void Enqueue(Queue * pq, SnakePos data) {
	Node * newNode = (Node *)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	if (pq->front == NULL) {
		pq->rear = newNode;
		pq->front = newNode;
	}
	else {
		pq->rear->next = newNode;
		pq->rear = newNode;
	}
}

SnakePos Dequeue(Queue * pq) {
	Node * delNode;
	SnakePos delData = { 0,0 };
	if (isEmpty(pq)) {
		return delData;
	}
	delNode = pq->front;
	delData = delNode->data;
	pq->front = pq->front->next;
	free(delNode);
	return delData;
}

SnakePos Peek(Queue * pq) {
	return pq->front->data;
}

int getKeyDown() {		//keyboard input
	if (_kbhit()) return _getch();
	return -1;
}

void gotoxy(int x, int y) {		//move cursor 함수 선언
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void hidecursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

int drawStartMenu() {		//시작 메뉴
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, 11);
	gotoxy(DEFAULT_X, DEFAULT_Y);
	printf(
		"============================================\n"
		"============================================\n"
		"===      =  ===  =       =  ===  =       ===\n"
		"===  =====   ==  =  ===  =  ==  ==  ========\n"
		"===      =  = =  =       =     ===      ====\n"
		"=======  =  ==   =  ===  =  ==  ==  ========\n"
		"===      =  ===  =  ===  =  ===  =       ===\n"
		"============================================\n"
		"============================================\n");

	SetConsoleTextAttribute(hand, 15);
	gotoxy(DEFAULT_X, DEFAULT_Y + 11);
	printf("> Key  : ↑, ←, ↓, →");
	gotoxy(DEFAULT_X, DEFAULT_Y + 13);
	printf("> Exit : 't'");

	SetConsoleTextAttribute(hand, 14);
	while (1) {
		int keyDown = getKeyDown();
		if (keyDown == 's' || keyDown == 'S') {
			SetConsoleTextAttribute(hand, 7);
			return TRUE;
		}
		if (keyDown == 't' || keyDown == 'T') {
			SetConsoleTextAttribute(hand, 7);
			return FALSE;
		}
		gotoxy(DEFAULT_X + 5, DEFAULT_Y + 17);
		printf("-- Press 's' to start --");
	}

}

void stageClear(MData map[MAP_SIZE][MAP_SIZE]) {
	int i, j;
	for (i = 0; i <= MAP_SIZE; i++) {
		for (j = 0; i <= MAP_SIZE; j++) {
			map[i][j] = EMPTY;
		}
	}
}

void MainStage(MData map[MAP_SIZE][MAP_SIZE]) {		//맵세팅
	int i, j;
	for (i = 0; i<MAP_SIZE; i++) {
		if (i == 0 || i == MAP_SIZE - 1) {
			for (j = 0; j<MAP_SIZE; j++) {
				map[i][j] = WALL;
			}
		}
		else {
			for (j = 0; j<MAP_SIZE; j++) {
				if (j == 0 || j == MAP_SIZE - 1)
					map[i][j] = WALL;
				else
					map[i][j] = EMPTY;
			}
		}

	}
}

void drawMainMap(MData map[MAP_SIZE][MAP_SIZE]) {		//맵 그리기
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, 15);

	int i, j;
	for (i = 0; i<MAP_SIZE; i++) {
		for (j = 0; j<MAP_SIZE; j++) {
			if (map[i][j] == WALL) {
				gotoxy(i, j);
				printf("□");
			}
			else if (map[i][j] == EMPTY) {
				gotoxy(i, j);
				printf(" ");
			}
		}
	}
	SetConsoleTextAttribute(hand, 7);
}


void drawSubMap(int score) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, 15);

	gotoxy(DEFAULT_X, MAP_SIZE + 2);
	printf(" Your Score : %4d", score);
	gotoxy(DEFAULT_X + 8, MAP_SIZE + 5);
	printf("[Exit - 't' / Pause - 'p']\n");
	SetConsoleTextAttribute(hand, 7);


}

int setFruit(MData map[MAP_SIZE][MAP_SIZE], FruitPos * fp) {
	HANDLE  hand = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, j;
	srand((unsigned int)time(NULL));
	while (1) {
		i = rand() % (MAP_SIZE - 2) + 1;
		j = rand() % (MAP_SIZE - 2) + 1;
		if (map[i][j] == EMPTY) {
			map[i][j] = FRUIT;
			fp->x = i;
			fp->y = j;
			(fp->numOfFruit)++;
			SetConsoleTextAttribute(hand, 12);
			gotoxy(i, j);
			printf("♣");
			SetConsoleTextAttribute(hand, 7);

			return 1;
		}
	}
}

int setBonusFruit(MData map[MAP_SIZE][MAP_SIZE], FruitPos * fp) {
	int i, j, numOfFruit = 0;
	for (i = 0; i<MAP_SIZE - 1; i++) {
		for (j = 0; j<MAP_SIZE; j++) {
			if (map[i][j] == EMPTY) {
				map[i][j] = FRUIT;
				numOfFruit++;
			}
		}
	}
	return numOfFruit;
}

void setSnakeTail(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, 14);
	gotoxy(snake_x, snake_y);
	printf("◎");
	map[snake_x][snake_y] = TAIL;
	SetConsoleTextAttribute(hand, 7);

}

void setSnake(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(snake_x, snake_y);
	SetConsoleTextAttribute(hand, 10);
	printf("●");
	SetConsoleTextAttribute(hand, 7);
	map[snake_x][snake_y] = HEAD;
}

void removeSnake(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y) {
	gotoxy(snake_x, snake_y);
	printf(" ");
	map[snake_x][snake_y] = EMPTY;
}


int rotate(int xy, int way) {
	if (way == UP || way == LEFT) {
		if (xy - 1 == -1) {
			xy = MAP_SIZE - 1;
		}
		else {
			--(xy);
		}
		return xy;
	}
	if (way == DOWN || way == RIGHT) {
		if (xy + 1 == MAP_SIZE) {
			xy = 0;
		}
		else {
			++xy;
		}
		return xy;
	}
	return FALSE;
}



int HittheTail(MData map[MAP_SIZE][MAP_SIZE], SnakePos * sp, int way) {
	if (way == UP) {
		if (map[sp->x][rotate(sp->y, way)] == TAIL)
			return TRUE;
	}
	if (way == DOWN) {
		if (map[sp->x][rotate(sp->y, way)] == TAIL)
			return TRUE;
	}
	if (way == LEFT) {
		if (map[rotate(sp->x, way)][sp->y] == TAIL)
			return TRUE;
	}
	if (way == RIGHT) {
		if (map[rotate(sp->x, way)][sp->y] == TAIL)
			return TRUE;
	}
	return FALSE;
}

int HittheWall(MData map[MAP_SIZE][MAP_SIZE], SnakePos * sp, int way) {
	if (way == UP) {
		if (map[sp->x][rotate(sp->y, way)] == WALL)
			return TRUE;
	}
	if (way == DOWN) {
		if (map[sp->x][rotate(sp->y, way)] == WALL)
			return TRUE;
	}
	if (way == LEFT) {
		if (map[rotate(sp->x, way)][sp->y] == WALL)
			return TRUE;
	}
	if (way == RIGHT) {
		if (map[rotate(sp->x, way)][sp->y] == WALL)
			return TRUE;
	}
	return FALSE;
}

int moveSnakeHead(MData map[MAP_SIZE][MAP_SIZE], SnakePos * snake, int way) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	removeSnake(map, snake->x, snake->y);
	if (HittheWall(map, snake, way) == TRUE) {
		SetConsoleTextAttribute(hand, 12);
		gotoxy(1, 1);
		printf("> You hit the wall!");
		return HIT;
	}
	if (HittheTail(map, snake, way) == TRUE) {
		SetConsoleTextAttribute(hand, 12);
		gotoxy(1, 1);
		printf("> You hit your tail!");
		return HIT;
	}

	if (way == UP) {
		if (snake->y - 1 == -1) {
			snake->y = MAP_SIZE - 1;
		}
		else {
			--(snake->y);
		}
		setSnake(map, snake->x, (snake->y));
		return UP;
	}
	if (way == DOWN) {
		if (snake->y + 1 == MAP_SIZE) {
			snake->y = 0;
		}
		else {
			++(snake->y);
		}
		setSnake(map, snake->x, (snake->y));
		return DOWN;
	}
	if (way == LEFT) {
		if (snake->x - 1 == -1) {
			snake->x = MAP_SIZE - 1;
		}
		else {
			--(snake->x);
		}
		setSnake(map, (snake->x), snake->y);
		return LEFT;
	}
	if (way == RIGHT) {
		if (snake->x + 1 == MAP_SIZE) {
			snake->x = 0;
		}
		else {
			++(snake->x);
		}
		setSnake(map, snake->x, snake->y);
		return RIGHT;
	}
	return way;
}

int overlap(int savedKey, int key) {
	if (savedKey == UP && key == DOWN)
		return TRUE;
	if (savedKey == DOWN && key == UP)
		return TRUE;
	if (savedKey == LEFT && key == RIGHT)
		return TRUE;
	if (savedKey == RIGHT && key == LEFT)
		return TRUE;

	return FALSE;
}

int HittheFruit(SnakePos * sp, FruitPos * fp) {
	if ((sp->x == fp->x && sp->y == fp->y)) {
		return TRUE;
	}
	return FALSE;
}

int isCollision(int state) {
	if (state == HIT) return TRUE;
	return FALSE;
}
void GameOver(int score, Queue *pq) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleTextAttribute(hand, 12);
	gotoxy(MAP_SIZE / 2 - 4, MAP_SIZE / 2 - 5);
	printf("===<GAME OVER>===\n");
	gotoxy(MAP_SIZE / 2 - 3, MAP_SIZE / 2 - 3);
	printf("Your Score : %d\n", score);
	gotoxy(DEFAULT_X + 8, MAP_SIZE + 5);
	printf("\n");
	SetConsoleTextAttribute(hand, 7);

	while (!isEmpty(pq)) {
		Dequeue(pq);
	}
}

void GameStart(MData map[MAP_SIZE][MAP_SIZE]) {
	int score = 0;
	int key, savedKey = 0;
	Queue queue;
	QueueInit(&queue);
	SnakePos snake = { MAP_SIZE / 4 - 2, MAP_SIZE / 4 + 1 };
	SnakePos snakeSecond;
	SnakePos snakeTail;
	int time = FALSE;
	FruitPos fruit;
	fruit.numOfFruit = 0;

	MainStage(map);

	drawMainMap(map);
	setSnake(map, snake.x, snake.y);

	while (1) {

		Sleep(1000 / (DWORD)10);             // 뱀의 속도
		if (fruit.numOfFruit == 0) {          // "Fruit"
			setFruit(map, &fruit);
		}
		drawSubMap(score);

		if (HittheFruit(&snake, &fruit) == TRUE) {
			(fruit.numOfFruit)--;
			time = FALSE;
			score += 5;
		}

		if (_kbhit()) {
			key = _getch();
			if (key == 't' || key == 'T') {     //나가기
				return;
			}
			if (key == 'p' || key == 'P') {
				system("pause");				//멈춤
				gotoxy(DEFAULT_X, MAP_SIZE + 6);
				printf("                                            ");
				gotoxy(DEFAULT_X, DEFAULT_Y);
			}

			if (key == 224 || key == 0) {      //방향키에 대한 아스키코드가 224, 72~80 이므로
				key = _getch();
				if (overlap(savedKey, key) == TRUE) {
					key = savedKey;
				}
				snakeSecond = snake;
				savedKey = moveSnakeHead(map, &snake, key);
				Enqueue(&queue, snakeSecond);
				setSnakeTail(map, snakeSecond.x, snakeSecond.y);
				if (time == TRUE) {
					snakeTail = Dequeue(&queue);
					removeSnake(map, snakeTail.x, snakeTail.y);
				}
				else {
					time = TRUE;
				}
				if (isCollision(savedKey)) { GameOver(score, &queue); return; }
			}
		}
		else {
			snakeSecond = snake;
			savedKey = moveSnakeHead(map, &snake, savedKey);
			Enqueue(&queue, snakeSecond);
			setSnakeTail(map, snakeSecond.x, snakeSecond.y);
			if (time == TRUE) {
				snakeTail = Dequeue(&queue);
				removeSnake(map, snakeTail.x, snakeTail.y);
			}
			else {
				time = TRUE;
			}
			if (isCollision(savedKey)) { GameOver(score, &queue); return; }

		}
	}
}

int main() {
	MData map[MAP_SIZE][MAP_SIZE];
	system("color 7");
	hidecursor();
	while (1) {
		system("mode con: cols=44 lines=30");   //콘솔창 크기 설정
		if (drawStartMenu() == FALSE) break;
		system("cls");
		GameStart(map);
		system("pause");
	}
	return 0;
}