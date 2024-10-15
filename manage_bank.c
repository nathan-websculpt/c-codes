#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//in progress.........

void checkbalance(char*);
void display(char*);
void person(char*);
void afterlogin(void);
void transfer(void);
void login(void);
void loginRedirect(void);
void logout(void);
void newAcct(void);
void accountCreated(void);

// for setting cursor position
void goToPos(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;

	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}

struct acct {
	char username[50];
	char phone[15];
	char fname[20];
	char lname[20];
	char address[50];
	int funds;
};

//for logs
struct tx {
	char to[50];
	char from[50];
	long int amt;
};

struct acctpassword {
	char pw[50];
};

int main()
{
	int i, a, b, sel, pwlen;

	goToPos(20, 3);

	//  main menu
	printf("ELLO GUBNA\n\n");
	goToPos(18, 5);

	printf("**********************************");
	goToPos(25, 7);

	goToPos(20, 10);
	printf("1:    CREATE AN ACCOUNT");
	goToPos(20, 12);
	printf("2:    SIGN IN");
	goToPos(20, 14);
	printf("3:    EXIT\n\n");

	printf("\n\nENTER SELECTION");

	scanf("%d", &sel);

	switch (sel) {
	case 1:
		system("cls");
		printf("\n\n USERNAME");
		printf("\n\n PASSWORD");
		newAcct();
		break;

	case 2:
		login();
		break;

	case 3:
		exit(0);
		break;

		getch();
	}
}

void seedfunds(char un[]) {
	FILE *fm;
	int toSend = 100;
	char from[50];
	strcpy(from, "FROM_BANK");

	//to, from, amt
	struct tx bankTransaction = { un, from, toSend };

	fm = fopen("funds.txt", "ab");
	fwrite(&bankTransaction, sizeof(bankTransaction),
		1, fm);
	fclose(fm);
}

void newAcct(void)
{
	char pw[20];
	int pwlen, i, seek = 0;
	char ch;
	FILE *fp, *fu;
	struct acct user;
	struct acctpassword p1;

	struct acctpassword p2;

	// Opening file to write user data
	fp = fopen("username.txt", "ab");

	//TODO: won't work right if you use spaces in any of these inputs
	// Inputs
	system("cls");
	printf("\n\n!!!!!CREATE ACCOUNT!!!!!");

	printf("\n\nFIRST NAME..");
	scanf("%s", &user.fname);

	printf("\n\nLAST NAME..");
	scanf("%s", &user.lname);

	printf("\n\nPHONE NUMBER..");
	scanf("%s", &user.phone);

	printf("\n\nADDRESS..");
	scanf("%s", &user.address);

	printf("\n\nUSERNAME..");
	scanf("%s", &user.username);

	printf("\n\nPASSWORD..");

	// Taking password (masked to *s)
	for (i = 0; i < 50; i++) {
		ch = getch();
		if (ch != 13) {
			pw[i] = ch;
			ch = '*';
			printf("%c", ch);
		}
		else
			break;
	}

	// writing to file
	fwrite(&user, sizeof(user),
		1, fp);

	// close file
	fclose(fp);

	//initial funds
	user.funds = 100;
	seedfunds(&user.username);

	// called on successful account creation
	accountCreated();
}

// Successful account creation
void accountCreated(void)
{
	int i;
	char ch;
	system("cls");
	printf("PLEASE WAIT....\n\nYOUR DATA IS PROCESSING....");	
	for (i = 0; i < 200000000; i++) { i++; }// pretend to do stuffs and things

	goToPos(30, 10);

	printf("ACCOUNT CREATED SUCCESSFULLY....");
	goToPos(0, 20);

	printf("Press enter to login");

	getch();
	login();
}

void login(void)
{
	system("cls");

	char username[50];
	char pw[50];

	int i, j, k;
	char ch;
	FILE *fp, *fu;
	struct acct user;
	struct acctpassword p;

	fp = fopen("username.txt", "rb");

	if (fp == NULL) {
		printf("ERROR OPENING FILE");
	}
	goToPos(34, 2);
	printf(" ACCOUNT LOGIN ");
	goToPos(7, 5);
	printf("***********************************************"
		"********************************");

	goToPos(35, 10);
	printf("==== LOG IN ====");

	// Take input
	goToPos(35, 12);
	printf("USERNAME.. ");
	scanf("%s", &username);

	goToPos(35, 14);
	printf("PASSWORD..");

	// Input the password
	for (i = 0; i < 50; i++) {
		ch = getch();
		if (ch != 13) {
			pw[i] = ch;
			ch = '*';
			printf("%c", ch);
		}
		else
			break;
	}

	// Checking if username
	// exists in the file or not
	while (fread(&user, sizeof(user),
		1, fp)) {
		if (strcmp(username,
			user.username)
			== 0) {
			//TODO: check password
			loginRedirect();
			display(username);
		}
	}

	fclose(fp);
}

void loginRedirect(void)
{
	int i;
	FILE* fp;
	struct acct user;
	system("cls");
	printf("Fetching account details.....\n");
	for (i = 0; i < 400000; i++) { i++; } // fake wait .... fate? ... Musch Weow

	goToPos(30, 10);
	printf("LOGIN SUCCESSFUL....");
	goToPos(0, 20);
	printf("Press enter to continue");

	getch();
}

// display user data
void display(char un[])
{
	system("cls");
	FILE* fp;
	int sel, i;
	fp = fopen("username.txt", "rb");
	struct acct user;

	if (fp == NULL) {
		printf("err opening file");
	}

	while (fread(&user, sizeof(user),
		1, fp)) {
		if (strcmp(un,
			user.username)
			== 0) {
			goToPos(30, 1);
			printf("WELCOME, %s %s",
				user.fname, user.lname);
			goToPos(28, 2);
			printf("..........................");
			goToPos(55, 6);
			printf("==== YOUR ACCOUNT INFO ====");
			goToPos(55, 8);
			printf("***************************");
			goToPos(55, 10);
			printf("NAME..%s %s", user.fname,
				user.lname);

			goToPos(55, 12);
			printf("MOBILE NUMBER..%s",
				user.phone);

			goToPos(55, 14);
			printf("ADDRESS..%s", user.address);
		}
	}

	fclose(fp);

	goToPos(0, 6);

	// Menu 
	printf(" HOME ");
	goToPos(0, 7);
	printf("******");
	goToPos(0, 9);
	printf(" 1....CHECK BALANCE");
	goToPos(0, 11);
	printf(" 2....TRANSFER MONEY");
	goToPos(0, 13);
	printf(" 3....LOG OUT\n\n");
	goToPos(0, 15);
	printf(" 4....EXIT\n\n");

	printf(" ENTER YOUR CHOICES..");
	scanf("%d", &sel);

	switch (sel) {
	case 1:
		checkbalance(un);
		break;

	case 2:
		transfer();
		break;

	case 3:
		logout();
		login();
		break;

	case 4:
		exit(0);
		break;
	}
}

// money transfer - tx
void transfer(void)
{
	int i, j;
	FILE *fm, *fp;
	struct acct user;
	struct tx transaction;
	char username[20]; //username sending funds to
	char userpass[20];
	system("cls");

	// read user's username
	fp = fopen("username.txt", "rb");

	// another file to write tx details
	fm = fopen("funds.txt", "ab");

	goToPos(33, 4);
	printf("---- TRANSFER MONEY ----");
	goToPos(33, 5);
	printf("========================");

	goToPos(33, 11);
	printf("FROM (your username).. ");
	scanf("%s", &username);

	goToPos(33, 13);
	printf(" TO (username of recipient)..");
	scanf("%s", &userpass);

	// Check if username in file
	while (fread(&user, sizeof(user),
		1, fp)) {
		if (strcmp(userpass,
			user.username)
			== 0) {
			strcpy(transaction.to,
				user.username);
			strcpy(transaction.from,
				username);
		}
	}
	goToPos(33, 16);

	printf("ENTER THE AMOUNT TO BE TRANSFERRED..");
	scanf("%d", &transaction.amt);

	fwrite(&transaction, sizeof(transaction),
		1, fm);

	goToPos(0, 26);
	printf(
		"--------------------------------------------------"
		"--------------------------------------------");

	goToPos(0, 28);
	printf(
		"--------------------------------------------------"
		"--------------------------------------------");

	goToPos(0, 29);
	printf("transferring amount, Please wait..");

	goToPos(10, 27);
	for (i = 0; i < 70; i++) {
		for (j = 0; j < 1200000; j++) {
			j++;
			j--;
		}
		printf("*");
	}

	goToPos(33, 40);
	printf("SUCCESSFULLY TRANSFERRED....");
	getch();

	fclose(fp);
	fclose(fm);

	// display home screen
	display(username);
}

void checkbalance(char un[])
{
	system("cls");
	FILE* fm;
	struct tx transaction;
	char ch;
	int i = 1, fundsTotal = 0;

	// amount file
	fm = fopen("funds.txt", "rb");

	int k = 5, l = 10;
	int m = 30, n = 10;
	int u = 60, v = 10;

	goToPos(30, 2);
	printf("==== BALANCE ====");
	goToPos(30, 3);
	printf("***************************");
	goToPos(k, l);
	printf("S no.");
	goToPos(m, n);
	printf("TRANSACTION ID");
	goToPos(u, v);
	printf("AMOUNT");

	// get correct record using username
	while (fread(&transaction, sizeof(transaction),
		1, fm)) {
		if (strcmp(un,
			transaction.to)
			== 0) {
			goToPos(k, ++l);
			printf("%d", i);
			i++;
			goToPos(m, ++n);
			printf("%s", transaction.from);

			goToPos(u, ++v);
			printf("%d", transaction.amt);
			
			//update sums
			fundsTotal = fundsTotal + transaction.amt; // TODO: +=
		}
	}

	goToPos(80, 10);
	printf("TOTAL AMOUNT");

	goToPos(80, 12);
	printf("%d", fundsTotal);

	getch();

	fclose(fm);
	display(un);
}

void logout(void)
{
	int i, j;
	system("cls");
	printf("please wait, logging out");

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 25000000; j++) {
			i++;
			i--;
		}
		printf(".");
	}

	goToPos(30, 10);
	printf("Sign out successfully..\n");

	goToPos(0, 20);
	printf("press any key to continue..");

	getch();
}
