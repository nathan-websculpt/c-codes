#include <conio.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define PACMAN 'C' 
#define BOUNDARY '*' 
#define EMPTYSPACE ' ' 
#define FOOD '.' 
#define SOMUCHFOOD '$' 
#define EXTRALIFE '@' 
#define NOPER 'X'
#define W 80 
#define H 20  

char screen[H][W];
int pacman_isat_x, pacman_isat_y;
int total_lives = 3;
int food_avail = 0;
int food_eaten = 0;
int score = 0;
int rslt = 0;

void init()
{
	// place outer boundaries as walls 
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (i == 0 || j == W - 1 || j == 0
				|| i == H - 1) {
				screen[i][j] = BOUNDARY;
			}
			else
				screen[i][j] = EMPTYSPACE;
		}
	}

	//random boundaries as obstacles
	int c = 40;
	while (c != 0) {
		int i = (rand() % (H + 1));
		int j = (rand() % (W + 1));

		if (screen[i][j] != BOUNDARY && screen[i][j] != PACMAN) {
			screen[i][j] = BOUNDARY;
			c--;
		}
	}

	//horizontal walls (boundaries)
	//generate X number of random rows, then iterate over a range of columns(excluding the first and last 3) in each row.
	//edit: boundaries now occur ~80% of the time
	int val = 5;
	while (val--) {
		int row = (rand() % (H + 1));
		for (int j = 3; j < W - 3; j++) {
			if (screen[row][j] != BOUNDARY
				&& screen[row][j] != PACMAN
				&& (rand() % 100) < 80) {
				screen[row][j] = BOUNDARY;
			}
		}
	}

	// place extra lives
	c = 8;
	while (c != 0) {
		int i = (rand() % (H + 1));
		int j = (rand() % (W + 1));

		if (screen[i][j] != BOUNDARY && screen[i][j] != PACMAN) {
			screen[i][j] = EXTRALIFE;
			c--;
		}
	}

	// place food bonuses
	c = 25;
	while (c != 0) {
		int i = (rand() % (H + 1));
		int j = (rand() % (W + 1));

		if (screen[i][j] != BOUNDARY && screen[i][j] != PACMAN && screen[i][j] != EXTRALIFE) {
			screen[i][j] = SOMUCHFOOD;
			c--;
		}
	}

	// place Nopers
	c = 12;
	while (c != 0) {
		int i = (rand() % (H + 1));
		int j = (rand() % (W + 1));

		if (screen[i][j] != BOUNDARY && screen[i][j] != PACMAN && screen[i][j] != EXTRALIFE && screen[i][j] != SOMUCHFOOD) {
			screen[i][j] = NOPER;
			c--;
		}
	}

	// center pacman 
	pacman_isat_x = W / 2;
	pacman_isat_y = H / 2;
	screen[pacman_isat_y][pacman_isat_x] = PACMAN;

	// points 
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (i % 2 == 0 && j % 2 == 0
				&& screen[i][j] != BOUNDARY
				&& screen[i][j] != NOPER
				&& screen[i][j] != PACMAN) {

				screen[i][j] = FOOD;
				food_avail++;
			}
		}
	}
}

void draw()
{
	system("cls");

	// draw elements
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			printf("%c", screen[i][j]);
		}
		printf("\n");
	}
	printf("Score: %d\n\n", score);
}
 
void move(int move_x, int move_y)
{
	int x = pacman_isat_x + move_x;
	int y = pacman_isat_y + move_y;

	if (screen[y][x] != BOUNDARY) {
		if (screen[y][x] == FOOD) {
			score++;
			food_avail--;
			food_eaten++;
			if (food_avail == 0) {
				rslt = 2;
				return;
			}
		}
		else if (screen[y][x] == NOPER) {
			total_lives--;
			if(total_lives == 0)
				rslt = 1;
		}
		else if (screen[y][x] == EXTRALIFE) {
			total_lives++;
		}
		else if (screen[y][x] == SOMUCHFOOD) {
			//add 3 to food, but ~25% of the time add 100
			if ((rand() % 100) < 25)
				score += 100;
			else 
				score += 3;
		}

		screen[pacman_isat_y][pacman_isat_x] = EMPTYSPACE;
		pacman_isat_x = x;
		pacman_isat_y = y;
		screen[pacman_isat_y][pacman_isat_x] = PACMAN;
	}
}
 
int main()
{
	init();
	char usersInput;
	food_avail -= 50;
	int totalFood = food_avail;
	
	printf(" Y to Play Game \n Q to Quit Game \n WASD to move\n");

	usersInput = _getch();
	if (usersInput != 'Y' && usersInput != 'y') {
		printf("Exit!!! ");
		return 1;
	}

	while (1) {
		draw();
		printf("Total Food: %d\n", totalFood);
		printf("Food Remaining: %d\n", food_avail);
		printf("Wuchu Munched: %d\n\n", food_eaten);
		printf("Total Lives: %d\n", total_lives);
		if (rslt == 1) {
			system("cls");
			printf("Game Over!\n Score: "
				"%d\n",
				score);
			return 1;
		}

		if (rslt == 2) {
			system("cls");
			printf("You won, but does that really matter? \n Your (utterly meaningless) Score: %d\n", score);
			return 1;
		}

		// User's Input
		usersInput = _getch();

		// Move
		switch (usersInput) {
		case 'w':
			move(0, -1);
			break;
		case 's':
			move(0, 1);
			break;
		case 'a':
			move(-1, 0);
			break;
		case 'd':
			move(1, 0);
			break;
		case 'q':
			printf("Game Over! Score: %d\n", score);
			return 0;
		}
	}

	return 0;
}
