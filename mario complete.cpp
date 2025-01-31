#include <stdio.h>  
#include <stdlib.h>  
#include <windows.h>  
#include <locale.h>
#include <codecvt>
#include <iostream>
#include <conio.h>    // For _kbhit(), _getch()
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <string.h>
#include <time.h>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define _CRT_SECURE_NO_WARNINGS

#define HEIGHT_LevelFirst 14  
#define WIDTH_LevelFirst 64 
#define HEIGHT_Level2 27
#define WIDTH_Level2 62
#define MAX_USERS 100
#define MAX_HISTORY 100

// Define the map using a 2D array of strings to accommodate multi-byte emojis
std::string map_LevelFirst[HEIGHT_LevelFirst][WIDTH_LevelFirst];
std::string map_LevelSecond[HEIGHT_Level2][WIDTH_Level2];
// Mario's position
int marioX = 3; // Starting X position (column)
int marioY = HEIGHT_LevelFirst - 2; // Starting Y position (row)

// Jump variables
bool isJumping_LevelFirst = false;
bool isJumping_LevelSecond = false;
// Define emojis
const std::string emoji = "\xF0\x9F\xA7\xB1";
const std::string yellowSquareEmoji = "\xF0\x9F\x9F\xA8";
const std::string orangeSquareEmoji = "\xF0\x9F\x9F\xA7";
const std::string greenSquareEmoji = "\xF0\x9F\x9F\xA9";
const std::string purplesquareemoji = "\xF0\x9F\x9F\xAA";
const std::string TrexSquareEmoji = "\xF0\x9F\xA6\x95";
const std::string mario = "\xF0\x9F\x98\xA1";
const std::string coinEmoji = "\xF0\x9F\xAA\x99";
const std::string parcham = "\xF0\x9F\x8F\x81";
const std::string okhtapus = "\xF0\x9F\x90\x99";
const std::string javane = "\xF0\x9F\x8C\xB1";
const std::string gharch = "\xF0\x9F\x8D\x84";

const std::string boundaryEmoji = "\xF0\x9F\xA7\xB1";
const std::string purpleSquareEmoji = "\xF0\x9F\x9F\xAA";
const std::string trexSquareEmoji = "\xF0\x9F\xA6\x95";
const std::string emptySpace = "  ";
const std::string limeSquareEmoji = "\xF0\x9F\x9F\xA6";
const std::string shild = "\xF0\x9F\x9B\xA1";

// Function to set up the console for UTF-8 output
int Level = 1;
int yellowcount_LevelFirst = 5;
int yellowcount1_LevelSecond = 5;
int yellowcount2_LevelSecond = 5;
int coinCount_LevelFirst = 0;
int coinCount_LevelSecond = 0;
bool bolIsJumped = false;
bool isdouble = false;
bool isGameOver = false;
int currenttime = 0;
int okhtapus1_location_LevelFirst = 26;
int okhtapus2_location_LevelFirst = 56;
bool okhtapus1_goright_LevelFirst = true;
bool okhtapus2_goright_LevelFirst = true;
bool okhtapus1_letitgo_LevelFirst = true;
bool okhtapus2_letitgo_LevelFirst = true;
bool isGameOverForOkhtapus_LevelFirst = false;
bool isGameOverFortrex_LevelFirst = false;
bool isGameOverFortrex_Levelsecond = false;
int okhtapus2_LevelFirst_Step = 0;
int okhtapus1_locationRow_LevelSecond = 14;
int okhtapus2_locationRow_LevelSecond = 31;
int okhtapus3_locationRow_LevelSecond = 41;
int okhtapus4_locationRow_LevelSecond = 45;
int okhtapus1_locationHeight_LevelSecond = 12;
int okhtapus2_locationHeight_LevelSecond = 25;
int okhtapus3_locationHeight_LevelSecond = 12;
int okhtapus4_locationHeight_LevelSecond = 10;


bool okhtapus1_letitgo_LevelSecond = true;
bool okhtapus2_letitgo_LevelSecond = true;
bool okhtapus3_letitgo_LevelSecond = true;
bool okhtapus4_letitgo_LevelSecond = true;


bool okhtapus1_goright_LevelSecond = true;
bool okhtapus2_goright_LevelSecond = true;
bool okhtapus3_goright_LevelSecond = true;
bool okhtapus4_goright_LevelSecond = true;
bool isGameOverForOkhtapus_LevelSecond = false;


typedef struct {
	char username[30];
	char email[50];
	char password[30];
} User;

// Structure for game history
typedef struct {
	char username[30];
	int score;
	int coins;
} History;

// Global variables
User users[MAX_USERS];
History histories[MAX_HISTORY];
int userCount = 0, historyCount = 0;
int currentUserIndex = -1; // Index of the logged-in user


void setupConsole();
void initializeMapArray();
void handleInput();
void renderMap();
void change_okhtapus_location();
void checkTeleport(int& marioX, int& marioY);
void showjavane();
void StartTheGame();
void loadData();
void saveData();
void loginSystem(); // Menu1: Register, Login, Forgot Password, Exit
void registerUser();
int loginUser();
void forgotPassword();
void userMenu(); // Menu2: Change Info, View History, Start Game, Logout
void changeUserInfo();
void viewHistory();
void startGame();
void addHistory(int score, int coins);



int main() {
	// Initialize random seed for game
	srand((unsigned int)time(NULL));

	loadData(); // Load user data and history

	// Start the login system
	loginSystem();

	// saveData(); // No longer needed here as data is saved immediately after changes
	return 0;
}

// Function to load user data and history from file
void loadData() {
	FILE* file;
	errno_t err = fopen_s(&file, "data.txt", "r");
	if (err != 0 || file == NULL) {
		printf("No existing user data found.\n");
		return;
	}

	// Load user data
	if (fscanf_s(file, "%d\n", &userCount) != 1) {
		userCount = 0;
	}
	for (int i = 0; i < userCount; i++) {
		if (fscanf_s(file, "%29s %49s %29s\n",
			users[i].username, (unsigned int)sizeof(users[i].username),
			users[i].email, (unsigned int)sizeof(users[i].email),
			users[i].password, (unsigned int)sizeof(users[i].password)) != 3) {
			printf("Error reading user data for user %d.\n", i + 1);
			// Handle error, possibly set userCount to i
			userCount = i;
			break;
		}
	}

	// Load history data
	if (fscanf_s(file, "%d\n", &historyCount) != 1) {
		historyCount = 0;
	}
	for (int i = 0; i < historyCount; i++) {
		if (fscanf_s(file, "%29s %d %d\n",
			histories[i].username, (unsigned int)sizeof(histories[i].username),
			&histories[i].score,
			&histories[i].coins) != 3) {
			printf("Error reading history data for entry %d.\n", i + 1);
			// Handle error, possibly set historyCount to i
			historyCount = i;
			break;
		}
	}

	fclose(file);
}

// Function to save user data and history to file
void saveData() {
	FILE* file;
	errno_t err = fopen_s(&file, "data.txt", "w");
	if (err != 0 || file == NULL) {
		printf("Error saving data.\n");
		return;
	}

	// Save user data
	fprintf(file, "%d\n", userCount);
	for (int i = 0; i < userCount; i++) {
		fprintf(file, "%s %s %s\n", users[i].username, users[i].email, users[i].password);
	}

	// Save history data
	fprintf(file, "%d\n", historyCount);
	for (int i = 0; i < historyCount; i++) {
		fprintf(file, "%s %d %d\n", histories[i].username, histories[i].score, histories[i].coins);
	}

	fclose(file);
}

// Function for Menu1: Register, Login, Forgot Password, Exit
void loginSystem() {
	int choice;

	while (1) {
		printf("\nWelcome to Mario Escape!\n");
		printf("1. Register\n");
		printf("2. Login\n");
		printf("3. Forgot Password\n");
		printf("4. Exit\n");
		printf("Choose an option: ");
		scanf_s("%d", &choice);
		getchar(); // Consume the newline after number input

		if (choice == 1) {
			registerUser();
		}
		else if (choice == 2) {
			if (loginUser()) {
				// If login successful, enter user menu
				userMenu();
			}
		}
		else if (choice == 3) {
			forgotPassword();
		}
		else if (choice == 4) {
			saveData();
			printf("Goodbye!\n");
			exit(0);
		}
		else {
			printf("Invalid option. Please try again.\n");
		}
	}
}

// Function to register a new user
void registerUser() {
	char username[30], email[50], password[30], confirmPassword[30];

	printf("Enter a username: ");
	scanf_s("%29s", username, (unsigned int)sizeof(username));

	// Check if username already exists
	for (int i = 0; i < userCount; i++) {
		if (strcmp(users[i].username, username) == 0) {
			printf("Username already exists. Please try again.\n");
			return;
		}
	}

	printf("Enter your email: ");
	scanf_s("%49s", email, (unsigned int)sizeof(email));

	while (1) {
		printf("Enter a password (at least 8 characters): ");
		scanf_s("%29s", password, (unsigned int)sizeof(password));

		if (strlen(password) < 8) {
			printf("Password must be at least 8 characters long. Try again.\n");
			continue;
		}

		printf("Confirm your password: ");
		scanf_s("%29s", confirmPassword, (unsigned int)sizeof(confirmPassword));

		if (strcmp(password, confirmPassword) != 0) {
			printf("Passwords do not match. Try again.\n");
		}
		else {
			break;
		}
	}

	if (userCount >= MAX_USERS) {
		printf("Maximum number of users reached. Cannot register more users.\n");
		return;
	}

	// Add new user
	strcpy_s(users[userCount].username, sizeof(users[userCount].username), username);
	strcpy_s(users[userCount].email, sizeof(users[userCount].email), email);
	strcpy_s(users[userCount].password, sizeof(users[userCount].password), password);
	userCount++;

	printf("Registration successful!\n");

	// Save data immediately after registration
	saveData();
}

// Function to handle user login
int loginUser() {
	char username[30], password[30];

	printf("Enter your username: ");
	scanf_s("%29s", username, (unsigned int)sizeof(username));
	printf("Enter your password: ");
	scanf_s("%29s", password, (unsigned int)sizeof(password));

	for (int i = 0; i < userCount; i++) {
		if (strcmp(users[i].username, username) == 0 &&
			strcmp(users[i].password, password) == 0) {
			printf("Login successful! Welcome, %s.\n", username);
			currentUserIndex = i; // Set the current user index
			return 1;
		}
	}

	printf("Invalid username or password. Please try again.\n");
	return 0;
}

// Function to handle forgot password
void forgotPassword() {
	char username[30];

	printf("Enter your username: ");
	scanf_s("%29s", username, (unsigned int)sizeof(username));

	for (int i = 0; i < userCount; i++) {
		if (strcmp(users[i].username, username) == 0) {
			printf("Your password is: %s\n", users[i].password);
			return;
		}
	}

	printf("Username not found. Please try again.\n");
}

// Function for Menu2: Change User Information, View History, Start Game, Logout
void userMenu() {
	int choice;

	while (currentUserIndex != -1) { // While user is logged in
		printf("\n--- User Menu ---\n");
		printf("1. Change User Information\n");
		printf("2. View History\n");
		printf("3. Start Game\n");
		printf("4. Logout\n");
		printf("Choose an option: ");
		scanf_s("%d", &choice);
		getchar(); // Consume newline

		switch (choice) {
		case 1:
			changeUserInfo();
			break;
		case 2:
			viewHistory();
			break;
		case 3:
			startGame();
			break;
		case 4:
			printf("Logging out...\n");
			currentUserIndex = -1;
			return; // Exit user menu back to login system
		default:
			printf("Invalid choice. Try again.\n");
		}
	}
}

// Function to change user information
void changeUserInfo() {
	char newEmail[50], newPassword[30], confirmPassword[30];

	printf("Enter new email (current: %s): ", users[currentUserIndex].email);
	scanf_s("%49s", newEmail, (unsigned int)sizeof(newEmail));

	while (1) {
		printf("Enter new password (leave '0' to keep current password): ");
		scanf_s("%29s", newPassword, (unsigned int)sizeof(newPassword));

		if (strcmp(newPassword, "0") == 0) { // Entering '0' skips changing password
			printf("Password unchanged.\n");
			strcpy_s(newPassword, sizeof(newPassword), users[currentUserIndex].password);
			break;
		}

		if (strlen(newPassword) < 8) {
			printf("Password must be at least 8 characters long. Try again.\n");
			continue;
		}

		printf("Confirm new password: ");
		scanf_s("%29s", confirmPassword, (unsigned int)sizeof(confirmPassword));

		if (strcmp(newPassword, confirmPassword) != 0) {
			printf("Passwords do not match. Try again.\n");
		}
		else {
			break;
		}
	}

	// Update user information
	strcpy_s(users[currentUserIndex].email, sizeof(users[currentUserIndex].email), newEmail);
	strcpy_s(users[currentUserIndex].password, sizeof(users[currentUserIndex].password), newPassword);
	printf("User information updated successfully.\n");

	// Save data immediately after changing user information
	saveData();
}

// Function to view game history
void viewHistory() {
	int found = 0;
	printf("\n--- Game History ---\n");
	for (int i = 0; i < historyCount; i++) {
		if (strcmp(histories[i].username, users[currentUserIndex].username) == 0) {
			printf("Score: %d, Coins: %d\n", histories[i].score, histories[i].coins);
			found = 1;
		}
	}
	if (!found) {
		printf("No game history found.\n");
	}
}

// Function to start the game (dummy implementation)
void startGame() {
	PlaySound(TEXT("game.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	StartTheGame();
}


// Function to add game history
void addHistory(int score, int coins) {
	if (historyCount >= MAX_HISTORY) {
		printf("Maximum history entries reached. Cannot save new history.\n");
		return;
	}

	strcpy_s(histories[historyCount].username, sizeof(histories[historyCount].username), users[currentUserIndex].username);
	histories[historyCount].score = score;
	histories[historyCount].coins = coins;
	historyCount++;

	printf("Game history saved.\n");

	// Save data immediately after adding game history
	saveData();
}




void setupConsole() {
	// Enable Unicode in console
	SetConsoleOutputCP(CP_UTF8);
	// Hide the cursor for better visuals
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

// Function to initialize the map array with objects
void initializeMapArray() {
	if (Level == 1) {
		// Initialize all cells to empty
		for (int i = 0; i < HEIGHT_LevelFirst; i++) {
			for (int j = 0; j < WIDTH_LevelFirst; j++) {
				map_LevelFirst[i][j] = "  "; // Two spaces for alignment
			}
		}



		// Set borders
		for (int i = 0; i < HEIGHT_LevelFirst; i++) {
			for (int j = 0; j < WIDTH_LevelFirst; j++) {
				if (i == 0 || i == HEIGHT_LevelFirst - 1 || j == 0 || j == WIDTH_LevelFirst - 1) {
					map_LevelFirst[i][j] = emoji;
				}
			}
		}

		// Platforms
		for (int j = 4; j <= 6; j++) {
			map_LevelFirst[8][j] = emoji;
		}
		for (int j = 7; j <= 8; j++) {
			map_LevelFirst[9][j] = emoji;
		}
		map_LevelFirst[9][10] = emoji;
		for (int j = 12; j <= 14; j++) {
			map_LevelFirst[10][j] = emoji;
		}
		for (int j = 19; j <= 21; j++) {
			map_LevelFirst[5][j] = emoji;
		}
		for (int j = 23; j <= 25; j++) {
			map_LevelFirst[6][j] = emoji;
		}
		for (int j = 27; j <= 29; j++) {
			map_LevelFirst[5][j] = emoji;
		}
		for (int i_row = 9; i_row <= 13; i_row++) {
			map_LevelFirst[i_row][49] = emoji;
		}
		for (int i_row = 9; i_row <= 11; i_row++) {
			map_LevelFirst[i_row][52] = emoji;
		}

		// Additional objects
		map_LevelFirst[9][9] = yellowSquareEmoji;
		for (int j = 50; j <= 51; j++) {
			map_LevelFirst[9][j] = orangeSquareEmoji;
		}
		for (int i_row = 1; i_row <= 2; i_row++) {
			for (int j = 24; j <= 25; j++) {
				map_LevelFirst[i_row][j] = greenSquareEmoji;
			}
		}
		for (int j = 23; j <= 26; j++) {
			map_LevelFirst[3][j] = greenSquareEmoji;
		}
		for (int j = 59; j <= 60; j++) {
			map_LevelFirst[12][j] = greenSquareEmoji;
		}
		for (int j = 58; j <= 61; j++) {
			map_LevelFirst[10][j] = greenSquareEmoji;
		}
		for (int j = 59; j <= 60; j++) {
			map_LevelFirst[11][j] = greenSquareEmoji;

		}
		map_LevelFirst[12][21] = yellowSquareEmoji;
		// Purple squares
		for (int j = 32; j <= 33; j++) {
			map_LevelFirst[12][j] = purplesquareemoji;
		}
		for (int j = 31; j <= 34; j++) {
			map_LevelFirst[11][j] = purplesquareemoji;
		}
		for (int j = 37; j <= 38; j++) {
			map_LevelFirst[12][j] = purplesquareemoji;
			map_LevelFirst[11][j] = purplesquareemoji;
			map_LevelFirst[10][j] = purplesquareemoji; map_LevelFirst[9][j] = purplesquareemoji;
		}
		map_LevelFirst[9][39] = purplesquareemoji;
		map_LevelFirst[9][36] = purplesquareemoji;
		for (int j = 41; j <= 42; j++) {
			for (int i_row = 6; i_row <= 12; i_row++) {
				map_LevelFirst[i_row][j] = purplesquareemoji;
			}
		}
		for (int j = 45; j <= 46; j++) {
			for (int i_row = 3; i_row <= 12; i_row++) {
				map_LevelFirst[i_row][j] = purplesquareemoji;
			}
		}
		for (int j = 44; j <= 47; j++) {
			map_LevelFirst[3][j] = purplesquareemoji;
		}
		map_LevelFirst[6][40] = purplesquareemoji;
		map_LevelFirst[6][43] = purplesquareemoji;
		// Trex squares
		map_LevelFirst[12][35] = TrexSquareEmoji;
		map_LevelFirst[12][39] = TrexSquareEmoji;
		map_LevelFirst[12][43] = TrexSquareEmoji;
		map_LevelFirst[12][47] = TrexSquareEmoji;

		// Mario's starting position (ensure it's empty initially)
		map_LevelFirst[marioY][marioX] = "  ";

		// Coins
		map_LevelFirst[8][8] = coinEmoji;
		map_LevelFirst[8][7] = coinEmoji;
		map_LevelFirst[12][17] = coinEmoji;
		map_LevelFirst[12][18] = coinEmoji;
		map_LevelFirst[4][27] = coinEmoji;
		map_LevelFirst[4][28] = coinEmoji;

		// Other objects
		map_LevelFirst[4][20] = parcham;
		map_LevelFirst[12][26] = okhtapus;
		map_LevelFirst[12][57] = okhtapus;
		map_LevelFirst[12][56] = okhtapus;


		map_LevelFirst[2][46] = javane;
		map_LevelFirst[8][37] = javane;
	}
	else if (Level == 2) {

		// Initialize all cells to empty
		for (int i = 0; i < HEIGHT_Level2; i++) {
			for (int j = 0; j < WIDTH_Level2; j++) {
				map_LevelSecond[i][j] = emptySpace;
			}
		}

		//left and right
		for (int i = 0; i < 13; i++) {
			map_LevelSecond[i][0] = boundaryEmoji;
			map_LevelSecond[i][WIDTH_Level2 - 1] = boundaryEmoji;
		}
		// down1, up
		for (int j = 0; j < WIDTH_Level2; j++) {
			map_LevelSecond[0][j] = boundaryEmoji;
			if (j == 44 || j == 22) {
				continue;
			}
			else {
				map_LevelSecond[13][j] = boundaryEmoji;
			}
		}
		// down2 
		for (int j = 0; j < WIDTH_Level2; j++) {
			if (j == 44 || j == 22) {
				continue;
			}
			else {
				map_LevelSecond[14][j] = boundaryEmoji;
			}
		}

		map_LevelSecond[12][22] = greenSquareEmoji;
		map_LevelSecond[12][23] = greenSquareEmoji;
		map_LevelSecond[11][22] = greenSquareEmoji;
		map_LevelSecond[11][23] = greenSquareEmoji;

		map_LevelSecond[5][23] = limeSquareEmoji;
		map_LevelSecond[5][22] = limeSquareEmoji;
		map_LevelSecond[6][22] = limeSquareEmoji;
		map_LevelSecond[6][23] = limeSquareEmoji;

		for (int i = 15; i < 26; i++) {
			map_LevelSecond[i][44] = greenSquareEmoji;
		}
		map_LevelSecond[25][43] = greenSquareEmoji;
		map_LevelSecond[24][43] = greenSquareEmoji;
		map_LevelSecond[21][42] = boundaryEmoji;
		map_LevelSecond[22][41] = boundaryEmoji;
		map_LevelSecond[22][40] = boundaryEmoji;
		map_LevelSecond[22][38] = boundaryEmoji;
		map_LevelSecond[22][37] = boundaryEmoji;
		map_LevelSecond[23][37] = boundaryEmoji;
		map_LevelSecond[23][36] = boundaryEmoji;
		map_LevelSecond[23][35] = boundaryEmoji;
		map_LevelSecond[24][34] = boundaryEmoji;
		map_LevelSecond[24][33] = boundaryEmoji;
		map_LevelSecond[25][32] = boundaryEmoji;
		map_LevelSecond[23][34] = trexSquareEmoji;
		map_LevelSecond[22][36] = trexSquareEmoji;
		map_LevelSecond[24][32] = coinEmoji;
		map_LevelSecond[21][41] = coinEmoji;
		map_LevelSecond[20][42] = coinEmoji;
		map_LevelSecond[25][42] = coinEmoji;



		// down v2
		for (int i = 15; i < HEIGHT_Level2 - 1; i++) {
			map_LevelSecond[i][21] = boundaryEmoji;
			map_LevelSecond[i][45] = boundaryEmoji;
		}
		for (int j = 21; j < 46; j++) {
			map_LevelSecond[HEIGHT_Level2 - 1][j] = boundaryEmoji;
		}



		//Other platforms and special blocks
		map_LevelSecond[10][3] = boundaryEmoji;
		for (int j = 4; j <= 6; j++) map_LevelSecond[8][j] = boundaryEmoji;
		map_LevelSecond[8][9] = boundaryEmoji;
		for (int j = 7; j <= 8; j++) map_LevelSecond[6][j] = boundaryEmoji;
		for (int j = 10; j <= 11; j++) map_LevelSecond[6][j] = boundaryEmoji;
		map_LevelSecond[6][9] = orangeSquareEmoji;
		for (int j = 21; j <= 25; j++) map_LevelSecond[7][j] = boundaryEmoji;
		map_LevelSecond[6][25] = boundaryEmoji;
		for (int j = 25; j <= 27; j++) map_LevelSecond[5][j] = boundaryEmoji;
		for (int j = 27; j <= 29; j++) map_LevelSecond[6][j] = boundaryEmoji;
		for (int j = 28; j <= 29; j++) map_LevelSecond[7][j] = boundaryEmoji;
		for (int j = 29; j <= 43; j++) map_LevelSecond[8][j] = boundaryEmoji;
		for (int j = 45; j <= 49; j++) map_LevelSecond[8][j] = boundaryEmoji;
		map_LevelSecond[8][44] = yellowSquareEmoji;
		map_LevelSecond[6][34] = boundaryEmoji;
		map_LevelSecond[6][36] = boundaryEmoji;
		map_LevelSecond[6][35] = yellowSquareEmoji;
		map_LevelSecond[12][7] = yellowSquareEmoji;
		map_LevelSecond[7][33] = trexSquareEmoji;
		map_LevelSecond[9][3] = coinEmoji;
		map_LevelSecond[12][17] = coinEmoji;
		map_LevelSecond[8][28] = coinEmoji;
		map_LevelSecond[12][49] = coinEmoji;
		map_LevelSecond[12][14] = okhtapus;
		map_LevelSecond[12][41] = okhtapus;
		map_LevelSecond[10][45] = okhtapus;
		map_LevelSecond[25][31] = okhtapus;

		map_LevelSecond[10][57] = shild;
		map_LevelSecond[5][58] = parcham;
		for (int j = 32; j <= 33; j++) map_LevelSecond[4][j] = boundaryEmoji;
		map_LevelSecond[9][40] = boundaryEmoji;
		map_LevelSecond[4][34] = orangeSquareEmoji;
		map_LevelSecond[9][28] = boundaryEmoji;
		for (int j = 27; j <= 28; j++) map_LevelSecond[10][j] = boundaryEmoji;
		for (int j = 26; j <= 27; j++) map_LevelSecond[11][j] = boundaryEmoji;
		for (int j = 33; j <= 47; j++) map_LevelSecond[11][j] = boundaryEmoji;
		map_LevelSecond[10][33] = boundaryEmoji;
		for (int j = 46; j <= 47; j++) map_LevelSecond[10][j] = boundaryEmoji;
		map_LevelSecond[12][46] = boundaryEmoji;
		for (int i = 9; i <= 11; i++) map_LevelSecond[i][49] = boundaryEmoji;
		map_LevelSecond[9][50] = boundaryEmoji;
		for (int j = 51; j <= 52; j++) map_LevelSecond[10][j] = boundaryEmoji;
		for (int j = 52; j <= 54; j++) map_LevelSecond[11][j] = boundaryEmoji;
		for (int j = 59; j <= 60; j++) map_LevelSecond[10][j] = boundaryEmoji;
		for (int j = 55; j <= 60; j++) map_LevelSecond[6][j] = boundaryEmoji;
		for (int i = 2; i <= 3; i++) map_LevelSecond[i][60] = limeSquareEmoji;
		for (int i = 1; i <= 5; i++) map_LevelSecond[i][55] = boundaryEmoji;
		for (int i = 1; i <= 4; i++) map_LevelSecond[i][59] = limeSquareEmoji;
	}
}

// Function to render the map with Mario's current position
void renderMap() {
	// Move the cursor to the top-left corner
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);

	if (Level == 1)
	{
		for (int h = 0; h < HEIGHT_LevelFirst; h++) {
			for (int w = 0; w < WIDTH_LevelFirst; w++) {
				if ((h == marioY && w == marioX) || (isdouble == true && h + 1 == marioY && w == marioX)) {
					std::cout << "\xF0\x9F\x98\xA1"; // Mario emoji with space for alignment
				}
				else {
					std::cout << map_LevelFirst[h][w];
				}
			}
			std::cout << "\n";
		}
		//std::cout << "\n";
		std::cout << "coin count Level First:" << coinCount_LevelFirst << "\n";

		/*std::cout << "Coin Count:" << coinCount;
		std::cout << "Grade:" << 0;
		std::cout << "\n";*/
		//if (currenttime > 20 && currenttime < 40 && isGameOver)
		//{
		//	//std::cout << "Game Over";
		//}
		//else if (isGameOver) {
		//	//std::cout << "         ";
		//	isGameOver = false;
		//	marioX = 3;
		//	marioY = HEIGHT_LevelFirst - 2;
		//	isdouble = false;
		//	//===============================
		//	map_LevelFirst[12][21] = yellowSquareEmoji;
		//	for (int j = 50; j <= 51; j++) {
		//		map_LevelFirst[9][j] = orangeSquareEmoji;
		//	}
		//}

		if (isGameOverForOkhtapus_LevelFirst)
		{
			//std::cout << "Game Over";
			isGameOverForOkhtapus_LevelFirst = false;
		}


		if (isGameOverFortrex_LevelFirst) {
			//std::cout << "Game Over";
			isGameOverFortrex_LevelFirst = false;
		}

	}
	else if (Level == 2)
	{
		system("cls");
		for (int h = 0; h < HEIGHT_Level2; h++) {
			for (int w = 0; w < WIDTH_Level2; w++) {
				if ((h == marioY && w == marioX) || (isdouble == true && h + 1 == marioY && w == marioX)) {
					std::cout << "\xF0\x9F\x98\xA1"; // Mario emoji with space for alignment
				}
				else {
					std::cout << map_LevelSecond[h][w];
				}
			}
			std::cout << "\n";
		}
		std::cout << "\n";
		if (isGameOverFortrex_Levelsecond) {
			isGameOverFortrex_Levelsecond = false;
		}
		std::cout << "coin count Level First:" << coinCount_LevelFirst << "\n";
		std::cout << "coin count Level Second:" << coinCount_LevelSecond << "\n";
	}
	else if (Level == 3) {
		system("cls");
		std::cout << "<< Congratulation >>" << "\n";
		std::cout << "coin count Level First:" << coinCount_LevelFirst << "\n";
		std::cout << "coin count Level Second:" << coinCount_LevelSecond << "\n";
	}
	/*

		for (int h = 0; h < HEIGHT_Level2; h++) {
			for (int w = 0; w < WIDTH_Level2; w++) {
				if ((h == marioY && w == marioX) || (isdouble == true && h + 1 == marioY && w == marioX)) {
					std::cout << "\xF0\x9F\x98\xA1"; // Mario emoji with space for alignment
				}
				else {
					std::cout << map_LevelSecond[h][w];
				}
			}
			std::cout << "\n";
		}
		std::cout << "\n";
		//for (int i = 0; i < HEIGHT_Level2; i++) {
		//	for (int j = 0; j < WIDTH_Level2; j++) {
		//		if (i == marioY && j == marioX) {
		//			std::cout << mario; // Mario's representation: two characters
		//		}
		//		else {
		//			std::cout << map_LevelSecond[i][j];
		//		}
		//	}
		//	std::cout << "\n";
		//}
	}
*/
}

bool isWalkable(int y, int x) {
	if (Level == 1)
	{
		if (y < 0 || y >= HEIGHT_LevelFirst || x < 0 || x >= WIDTH_LevelFirst)
			return false;

		if ((y == 8 && x == 8)
			|| (y == 8 && x == 7)
			|| (y == 12 && x == 17)
			|| (y == 12 && x == 18)
			|| (y == 4 && x == 27)
			|| (y == 4 && x == 28)
			)
		{

			return false;
		}

		if (y == 4 && x == 20)//flag
			return false;


		if (y == 4 && (x == 24 || x == 25))//end
			return false;
		if (y == 9 && (x == 59 || x == 60))//end
		{
			marioY = 4;
			marioX = 24;
			return true;
		}

		// Define collectible items
		const std::string coin = "\xF0\x9F\xAA\x99";

		// Allow walking on empty spaces or collectibles
		return (map_LevelFirst[y][x] == "  " || map_LevelFirst[y][x] == coin);
	}
	else if (Level == 2)
	{
		if (x < 0 || x >= WIDTH_Level2 || y < 0 || y >= HEIGHT_Level2)
			return false;

		if (y == 5 && x == 58)
			return false;

		// Treat any non-empty cell as non-walkable
		if (map_LevelSecond[y][x] != "  ")
			return false;



		return true;
	}

}

void GameOverForOkhtapus() {
	if (Level == 1)
	{
		isGameOverForOkhtapus_LevelFirst = true;
		marioX = 3;
		marioY = HEIGHT_LevelFirst - 2;
		isdouble = false;
		map_LevelFirst[12][21] = yellowSquareEmoji;
		for (int j = 50; j <= 51; j++) {
			map_LevelFirst[9][j] = orangeSquareEmoji;
		}
		map_LevelFirst[12][okhtapus1_location_LevelFirst] = "  ";
		map_LevelFirst[12][okhtapus2_location_LevelFirst] = "  ";
		map_LevelFirst[12][okhtapus2_location_LevelFirst + 1] = "  ";

		map_LevelFirst[12][26] = okhtapus;
		map_LevelFirst[12][57] = okhtapus;
		map_LevelFirst[12][56] = okhtapus;


		okhtapus1_location_LevelFirst = 26;
		okhtapus2_location_LevelFirst = 56;
	}
	else if (Level == 2)
	{
		isGameOverForOkhtapus_LevelSecond = true;
		marioX = 3;
		marioY = 12;
		isdouble = false;
		map_LevelSecond[8][44] = yellowSquareEmoji;
		map_LevelSecond[6][35] = yellowSquareEmoji;

		/*for (int j = 50; j <= 51; j++) {
			map_LevelFirst[9][j] = orangeSquareEmoji;
		}*/
		map_LevelSecond[12][okhtapus1_locationRow_LevelSecond] = "  ";
		map_LevelSecond[25][okhtapus2_locationRow_LevelSecond] = "  ";
		map_LevelSecond[12][okhtapus3_locationRow_LevelSecond] = "  ";
		map_LevelSecond[10][okhtapus4_locationRow_LevelSecond] = "  ";

		okhtapus1_locationRow_LevelSecond = 14;
		okhtapus2_locationRow_LevelSecond = 31;
		okhtapus3_locationRow_LevelSecond = 41;
		okhtapus4_locationRow_LevelSecond = 45;

		map_LevelSecond[12][okhtapus1_locationRow_LevelSecond] = okhtapus;
		map_LevelSecond[25][okhtapus2_locationRow_LevelSecond] = okhtapus;
		map_LevelSecond[12][okhtapus3_locationRow_LevelSecond] = okhtapus;
		map_LevelSecond[10][okhtapus4_locationRow_LevelSecond] = okhtapus;

		map_LevelSecond[12][7] = yellowSquareEmoji;

		map_LevelSecond[6][9] = orangeSquareEmoji;
		map_LevelSecond[4][34] = orangeSquareEmoji;

	}
}
void GameOverFortrex() {
	if (Level == 1)
	{
		isGameOverFortrex_LevelFirst = true;
		marioX = 3;
		marioY = HEIGHT_LevelFirst - 2;
		isdouble = false;

		map_LevelFirst[12][35] = TrexSquareEmoji;
		map_LevelFirst[12][39] = TrexSquareEmoji;
		map_LevelFirst[12][43] = TrexSquareEmoji;
		map_LevelFirst[12][47] = TrexSquareEmoji;
	}
	else if (Level == 2) {

		isGameOverFortrex_Levelsecond = true;
		marioX = 3;
		marioY = 12;
		isdouble = false;

		/*	map_LevelSecond[23][34] = TrexSquareEmoji;
			map_LevelSecond[22][34] = TrexSquareEmoji;
			map_LevelSecond[23][33] = TrexSquareEmoji;

			map_LevelSecond[22][36] = TrexSquareEmoji;
			map_LevelSecond[22][35] = TrexSquareEmoji;
			map_LevelSecond[21][36] = TrexSquareEmoji;


			map_LevelSecond[7][32] = TrexSquareEmoji;
			map_LevelSecond[6][33] = TrexSquareEmoji;
			map_LevelSecond[7][34] = TrexSquareEmoji;
			map_LevelSecond[7][33] = TrexSquareEmoji;*/

	}
}

void UpgradeLevel() {
	if (Level == 1) {
		Level = 2;
		initializeMapArray();
		marioX = 4;
		marioY = 12;
	}
	else if (Level == 2)
	{
		Level = 3;
	}
}
// Function to handle Mario's movement
void handleInput() {
	if (Level == 1)
	{
		if (_kbhit()) {
			char ch = _getch();
			bolIsJumped = false;
			if (ch == 'a' || ch == 'A')
			{ // Move left
				if (isWalkable(marioY, marioX - 1))
				{
					marioX -= 1;
				}
				else
				{
					//if (marioY == 9 && marioX == 60)//end
					//{
					//	marioY == 4;
					//	marioX == 24;
					//}
					//if (marioY == 9 && marioX == 59)//end
					//{
					//	marioY == 4;
					//	marioX == 25;
					//}
					if ((marioX - 1) == 21 && marioY == 12 && map_LevelFirst[12][21] == yellowSquareEmoji) {
						map_LevelFirst[12][21] = gharch;
					}
					else if ((marioX - 1) == 21 && marioY == 12 && map_LevelFirst[12][21] == gharch) {
						map_LevelFirst[12][21] = "  ";
						marioX -= 1;
						isdouble = true;
					}

					if ((marioX - 1) == 8 && marioY == 8)
					{
						coinCount_LevelFirst += 1;
						map_LevelFirst[8][8] = emptySpace;
					}
					if (marioY == 8 && (marioX - 1) == 7)
					{
						coinCount_LevelFirst += 1;
						map_LevelFirst[8][7] = emptySpace;
					}
					if (marioY == 12 && (marioX - 1) == 17)
					{
						coinCount_LevelFirst += 1;
						map_LevelFirst[12][17] = emptySpace;
					}
					if (marioY == 12 && (marioX - 1) == 18)
					{
						coinCount_LevelFirst += 1;
						map_LevelFirst[12][18] = emptySpace;
					}
					if (marioY == 4 && (marioX - 1) == 27)
					{
						coinCount_LevelFirst += 1;
						map_LevelFirst[4][27] = emptySpace;
					}
					if (marioY == 4 && (marioX - 1) == 28)
					{
						coinCount_LevelFirst += 1;
						map_LevelFirst[4][28] = emptySpace;
					}
					if (marioY == 4 && marioX - 1 == 20)
						UpgradeLevel();


				}
				if (marioY == 12 && (marioX == okhtapus1_location_LevelFirst - 1) && okhtapus1_goright_LevelFirst == true)
				{
					if (isdouble)
						isdouble = false;
					/*else
						GameOverForOkhtapus();*/
				}
			}
			else if (ch == 'd' || ch == 'D')
			{ // Move right
				if (isWalkable(marioY, marioX + 1))
				{
					marioX += 1;
				}
				else {

					//if (marioY == 9 && marioX == 60)//end
					//{
					//	marioY == 4;
					//	marioX == 24;
					//}
					//if (marioY == 9 && marioX == 59)//end
					//{
					//	marioY == 4;
					//	marioX == 25;
					//}

					if ((marioX + 1) == 21 && marioY == 12 && map_LevelFirst[12][21] == yellowSquareEmoji) {
						map_LevelFirst[12][21] = gharch;
					}
					else if ((marioX + 1) == 21 && marioY == 12 && map_LevelFirst[12][21] == gharch) {
						map_LevelFirst[12][21] = "  ";
						marioX += 1;
						isdouble = true;
					}
					if ((marioX + 1) == 8 && marioY == 8)
					{
						coinCount_LevelFirst += 1;
						map_LevelFirst[8][8] = emptySpace;
						marioX += 1;
					}
					if (marioY == 8 && (marioX + 1) == 7)
					{
						coinCount_LevelFirst += 1;
						map_LevelFirst[8][7] = emptySpace;
						marioX += 1;
					}
					if (marioY == 12 && (marioX + 1) == 17)
					{
						coinCount_LevelFirst += 1;
						map_LevelFirst[12][17] = emptySpace;
						marioX += 1;
					}
					if (marioY == 12 && (marioX + 1) == 18)
					{
						coinCount_LevelFirst += 1;
						map_LevelFirst[12][18] = emptySpace;
						marioX += 1;
					}
					if (marioY == 4 && (marioX + 1) == 27)
					{
						coinCount_LevelFirst += 1;
						map_LevelFirst[4][27] = emptySpace;
						marioX += 1;
					}
					if (marioY == 4 && (marioX + 1) == 28)
					{
						coinCount_LevelFirst += 1;
						map_LevelFirst[4][28] = emptySpace;
						marioX += 1;
					}
					if (marioY == 4 && marioX + 1 == 20)
						UpgradeLevel();
				}
				if (marioY == 12 && (marioX == okhtapus1_location_LevelFirst - 1) && okhtapus1_goright_LevelFirst == false)
				{
					if (isdouble)
						isdouble = false;
					/*else
						GameOverForOkhtapus();*/
				}

			}
			else if (ch == 'w' || ch == 'W') { // Jump
				if (map_LevelFirst[marioY + 1][marioX] != "  ")
				{
					if (map_LevelFirst[marioY - 1][marioX] == "  " && map_LevelFirst[marioY - 2][marioX] == "  " && map_LevelFirst[marioY - 3][marioX] == "  " && map_LevelFirst[marioY - 4][marioX] == "  ")
					{
						isJumping_LevelFirst = true;
						marioY -= 4;
						bolIsJumped = true;
					}
					else if (map_LevelFirst[marioY - 1][marioX] == "  " && map_LevelFirst[marioY - 2][marioX] == "  " && map_LevelFirst[marioY - 3][marioX] == "  ") {
						isJumping_LevelFirst = true;
						marioY -= 3;
						bolIsJumped = true;
					}
					else if (map_LevelFirst[marioY - 1][marioX] == "  " && map_LevelFirst[marioY - 2][marioX] == "  ") {
						isJumping_LevelFirst = true;
						marioY -= 2;
						bolIsJumped = true;
					}
					else if (map_LevelFirst[marioY - 1][marioX] == "  ") {
						isJumping_LevelFirst = true;
						marioY -= 1;
						bolIsJumped = true;
					}
					else {
						if ((marioY - 4 == 9 || marioY - 3 == 9 || marioY - 2 == 9 || marioY - 1 == 9) && marioX == 9 && yellowcount_LevelFirst > 1) {
							coinCount_LevelFirst += 1;
							yellowcount_LevelFirst -= 1;
						}
					}

				}

			}
			else if (ch == 'q' || ch == 'Q') { // Quit the game
				exit(0);
			}


		}
	}
	else if (Level == 2)
	{

		if (_kbhit()) {
			char ch = _getch();
			bolIsJumped = false;
			if (ch == 'a' || ch == 'A') { // Move left
				if (isWalkable(marioY, marioX - 1)) {
					marioX -= 1;
				}
				else {
					if ((marioX - 1) == 33 && marioY == 7) {
						GameOverFortrex();
					}

					if ((marioX - 1) == 32 && marioY == 24)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[24][32] = emptySpace;
					}

					if ((marioX - 1) == 41 && marioY == 21)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[21][41] = emptySpace;
					}
					if ((marioX - 1) == 42 && marioY == 20)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[20][42] = emptySpace;

					}
					if ((marioX - 1) == 42 && marioY == 25)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[25][42] = emptySpace;

					}
					if ((marioX - 1) == 3 && marioY == 9)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[9][3] = emptySpace;

					}
					if ((marioX - 1) == 17 && marioY == 12)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[12][17] = emptySpace;
					}
					if ((marioX - 1) == 28 && marioY == 8)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[8][28] = emptySpace;
					}
					if ((marioX - 1) == 49 && marioY == 12)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[12][49] = emptySpace;
					}
					if ((marioX - 1) == 7 && marioY == 12 && map_LevelSecond[12][7] == yellowSquareEmoji) {
						map_LevelSecond[12][7] = gharch;
					}
					else if ((marioX - 1) == 7 && marioY == 12 && map_LevelSecond[12][7] == gharch) {
						map_LevelSecond[12][7] = "  ";
						marioX -= 1;
						isdouble = true;
					}
					if (marioY == 5 && marioX - 1 == 58)
						UpgradeLevel();
				}
				//if (marioY == 12 && (marioX == okhtapus1_location_LevelFirst - 1) && okhtapus1_goright_LevelFirst == true)
				//{
				//	if (isdouble)
				//		isdouble = false;
				//	/*else
				//		GameOverForOkhtapus();*/
				//}
			}
			else if (ch == 'd' || ch == 'D') { // Move right
				if (isWalkable(marioY, marioX + 1)) {
					marioX += 1;
				}
				else {
					if (((marioX + 1) == 33 && marioY == 7) || ((marioX + 1) == 36 && marioY == 22) || ((marioX + 1) == 34 && marioY == 23)) {
						GameOverFortrex();
					}
					if ((marioX + 1) == 32 && marioY == 24)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[24][32] = emptySpace;
					}

					if ((marioX + 1) == 41 && marioY == 21)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[21][41] = emptySpace;
					}
					if ((marioX + 1) == 42 && marioY == 20)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[20][42] = emptySpace;

					}
					if ((marioX + 1) == 42 && marioY == 25)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[25][42] = emptySpace;

					}
					if ((marioX + 1) == 3 && marioY == 9)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[9][3] = emptySpace;

					}
					if ((marioX + 1) == 17 && marioY == 12)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[12][17] = emptySpace;
					}
					if ((marioX + 1) == 28 && marioY == 8)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[8][28] = emptySpace;
					}
					if ((marioX + 1) == 49 && marioY == 12)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[12][49] = emptySpace;
					}
					if ((marioX + 1) == 7 && marioY == 12 && map_LevelSecond[12][7] == yellowSquareEmoji) {
						map_LevelSecond[12][7] = gharch;
					}
					else if ((marioX + 1) == 7 && marioY == 12 && map_LevelSecond[12][7] == gharch) {
						map_LevelSecond[12][7] = "  ";
						marioX += 1;
						isdouble = true;
					}
					if (marioY == 5 && marioX + 1 == 58)
						UpgradeLevel();
					/*if ((marioX + 1) == 21 && marioY == 12 && map_LevelFirst[12][21] == yellowSquareEmoji) {
						map_LevelFirst[12][21] = gharch;
					}
					else if ((marioX + 1) == 21 && marioY == 12 && map_LevelFirst[12][21] == gharch) {
						map_LevelFirst[12][21] = "  ";
						marioX += 1;
						isdouble = true;
					}*/
				}
				//if (marioY == 12 && (marioX == okhtapus1_location_LevelFirst - 1) && okhtapus1_goright_LevelFirst == false)
				//{
				//	if (isdouble)
				//		isdouble = false;
				//	/*else
				//		GameOverForOkhtapus();*/
				//}
			}
			else if (ch == 'w' || ch == 'W') { // Jump
				if (map_LevelSecond[marioY + 1][marioX] != "  ")
				{
					if (map_LevelSecond[marioY - 1][marioX] == "  " && map_LevelSecond[marioY - 2][marioX] == "  " && map_LevelSecond[marioY - 3][marioX] == "  " && map_LevelSecond[marioY - 4][marioX] == "  ")
					{
						isJumping_LevelSecond = true;
						marioY -= 4;
						bolIsJumped = true;
					}
					else if (map_LevelSecond[marioY - 1][marioX] == "  " && map_LevelSecond[marioY - 2][marioX] == "  " && map_LevelSecond[marioY - 3][marioX] == "  ") {
						isJumping_LevelSecond = true;
						marioY -= 3;
						bolIsJumped = true;
					}
					else if (map_LevelSecond[marioY - 1][marioX] == "  " && map_LevelSecond[marioY - 2][marioX] == "  ") {
						isJumping_LevelSecond = true;
						marioY -= 2;
						bolIsJumped = true;
					}
					else if (map_LevelSecond[marioY - 1][marioX] == "  ") {
						isJumping_LevelSecond = true;
						marioY -= 1;
						bolIsJumped = true;
					}
					else {
						if ((marioY - 4 == 8 || marioY - 3 == 8 || marioY - 2 == 8 || marioY - 1 == 8) && marioX == 44 && yellowcount1_LevelSecond > 1) {
							coinCount_LevelSecond += 1;
							yellowcount1_LevelSecond -= 1;
						}
						else if ((marioY - 4 == 6 || marioY - 3 == 6 || marioY - 2 == 6 || marioY - 1 == 6) && marioX == 35 && yellowcount2_LevelSecond > 1) {
							coinCount_LevelSecond += 1;
							yellowcount2_LevelSecond -= 1;
						}
					}
				}

			}
			else if (ch == 'q' || ch == 'Q') { // Quit the game
				exit(0);
			}
		}
		//============================================
		//if (_kbhit()) {
		//	char input = _getch();
		//	switch (input) {
		//	case 'a': // Move left
		//		if (marioX > 0 && isWalkable(marioY, marioX - 1))
		//			marioX--;
		//		break;
		//	case 'd': // Move right
		//		if (marioX < WIDTH_Level2 - 1 && isWalkable(marioY, marioX + 1))
		//			marioX++;
		//		break;
		//	default:
		//		break;
		//	}
		//}

	}

}

// Function to handle jumping and gravity
//void handleJumpAndGravity() {
//
//	//if (isJumping) {
//	//	// Attempt to move up
//	//	if (jumpHeight < MAX_JUMP && isWalkable(marioY - 1, marioX)) {
//	//		marioY -= 1;
//	//		jumpHeight += 1;
//	//	}
//	//	else {
//	//		// Reached max jump height or blocked
//	//		isJumping = false;
//	//	}
//	//}
//	//else {
//	//	// Apply gravity: move down if possible
//	//	if (isWalkable(marioY + 1, marioX)) {
//	//		marioY += 1;
//	//	}
//	//}
//}

// Function to check if Mario is on a coin
void savecoins2file() {
	if (Level == 1)
	{
		if (map_LevelFirst[marioY][marioX] == "\xF0\x9F\xAA\x99") { // Coin emoji
			map_LevelFirst[marioY][marioX] = "  "; // Remove the coin
			// Save coin information to a file
			FILE* file;
			errno_t err = fopen_s(&file, "collected_coins.txt", "a");
			if (file != NULL) {
				fprintf(file, "Coin collected at position: (%d, %d)\n", marioX, marioY);
				fclose(file);
			}
			fclose(file);
		}
	}
	else if (Level == 2)
	{

	}
}

void checkTeleport(int& marioX, int& marioY) {
	if (Level == 1) {
		if ((marioY == 9 && marioX == 60) || (marioY == 9 && marioX == 59)) {
			marioX = 25;
			marioY = 4;
		}
	}
	else if (Level == 2) {
		if ((marioY == 10 && marioX == 22) || (marioY == 10 && marioX == 23)) {
			marioX = 22;
			marioY = 14;
		}
		else if ((marioY == 24 && marioX == 43) || (marioY == 25 && marioX == 42)) {
			marioX = 43;
			marioY = 12;
		}
		else if ((marioY == 4 && marioX == 23) || (marioY == 4 && marioX == 22)) {
			marioX = 58;
			marioY = 2;
		}
	}
}

void showjavane() {
	if (Level == 1)
	{
		if (currenttime < 20)
		{
			currenttime += 1;
			map_LevelFirst[2][46] = "  ";
			map_LevelFirst[8][37] = "  ";
		}
		else if (currenttime >= 20 && currenttime < 40) {
			map_LevelFirst[2][46] = javane;
			map_LevelFirst[8][37] = javane;
			currenttime += 1;

			if ((marioY == 2 && marioX == 46) || (marioY == 8 && marioX == 37)) {
				isGameOver = true;
			}
		}
		else
		{
			currenttime = 0;
		}
	}
	else if (Level == 2)
	{

	}
}

void change_okhtapus_location() {
	if (Level == 1)
	{
		if (okhtapus2_LevelFirst_Step > 20) {
			if (okhtapus1_letitgo_LevelFirst) {
				if (okhtapus1_goright_LevelFirst)
				{
					if (map_LevelFirst[12][okhtapus1_location_LevelFirst + 1] == "  ") {
						map_LevelFirst[12][okhtapus1_location_LevelFirst] = "  ";
						okhtapus1_location_LevelFirst += 1;
						map_LevelFirst[12][okhtapus1_location_LevelFirst] = okhtapus;

					}
					else
						okhtapus1_goright_LevelFirst = false;

				}
				else
				{
					if (map_LevelFirst[12][okhtapus1_location_LevelFirst - 1] == "  ") {
						map_LevelFirst[12][okhtapus1_location_LevelFirst] = "  ";
						okhtapus1_location_LevelFirst -= 1;
						map_LevelFirst[12][okhtapus1_location_LevelFirst] = okhtapus;
					}
					else {
						okhtapus1_goright_LevelFirst = true;
					}
				}

				if (marioY == 12 && marioX == okhtapus1_location_LevelFirst)
				{
					if (isdouble)
						isdouble = false;
					else
						GameOverForOkhtapus();
				}

			}
			okhtapus1_letitgo_LevelFirst = !okhtapus1_letitgo_LevelFirst;
			//==========================================
			if (okhtapus2_goright_LevelFirst)
			{
				if (map_LevelFirst[12][okhtapus2_location_LevelFirst + 2] == "  ") {
					map_LevelFirst[12][okhtapus2_location_LevelFirst] = "  ";
					map_LevelFirst[12][okhtapus2_location_LevelFirst + 1] = "  ";
					okhtapus2_location_LevelFirst += 1;
					map_LevelFirst[12][okhtapus2_location_LevelFirst] = okhtapus;
					map_LevelFirst[12][okhtapus2_location_LevelFirst + 1] = okhtapus;
				}
				else {
					okhtapus2_goright_LevelFirst = false;
				}
			}
			else
			{
				if (map_LevelFirst[12][okhtapus2_location_LevelFirst - 1] == "  ") {
					map_LevelFirst[12][okhtapus2_location_LevelFirst] = "  ";
					map_LevelFirst[12][okhtapus2_location_LevelFirst + 1] = "  ";
					okhtapus2_location_LevelFirst -= 1;
					map_LevelFirst[12][okhtapus2_location_LevelFirst] = okhtapus;
					map_LevelFirst[12][okhtapus2_location_LevelFirst + 1] = okhtapus;
				}
				else {
					okhtapus2_goright_LevelFirst = true;
				}

				if (marioY == 12 && (marioX == okhtapus2_location_LevelFirst || marioX == okhtapus2_location_LevelFirst + 1))
				{
					if (isdouble)
						isdouble = false;
					else
						GameOverForOkhtapus();
				}

			}

			okhtapus2_letitgo_LevelFirst = !okhtapus2_letitgo_LevelFirst;
			okhtapus2_LevelFirst_Step = 0;
		}
		else
			okhtapus2_LevelFirst_Step += 1;

	}
	else if (Level == 2)
	{
		if (okhtapus1_letitgo_LevelSecond) {
			if (okhtapus1_goright_LevelSecond)
			{
				if (map_LevelSecond[okhtapus1_locationHeight_LevelSecond][okhtapus1_locationRow_LevelSecond + 1] == "  ") {
					map_LevelSecond[okhtapus1_locationHeight_LevelSecond][okhtapus1_locationRow_LevelSecond] = "  ";
					okhtapus1_locationRow_LevelSecond += 1;
					map_LevelSecond[okhtapus1_locationHeight_LevelSecond][okhtapus1_locationRow_LevelSecond] = okhtapus;

				}
				else
					okhtapus1_goright_LevelSecond = false;

			}
			else
			{
				if (map_LevelSecond[okhtapus1_locationHeight_LevelSecond][okhtapus1_locationRow_LevelSecond - 1] == "  ") {
					map_LevelSecond[okhtapus1_locationHeight_LevelSecond][okhtapus1_locationRow_LevelSecond] = "  ";
					okhtapus1_locationRow_LevelSecond -= 1;
					map_LevelSecond[okhtapus1_locationHeight_LevelSecond][okhtapus1_locationRow_LevelSecond] = okhtapus;
				}
				else {
					okhtapus1_goright_LevelSecond = true;
				}
			}
		}
		okhtapus1_letitgo_LevelSecond = !okhtapus1_letitgo_LevelSecond;
		//==========================================
		if (okhtapus2_letitgo_LevelSecond) {
			if (okhtapus2_goright_LevelSecond)
			{
				if (map_LevelSecond[okhtapus2_locationHeight_LevelSecond][okhtapus2_locationRow_LevelSecond + 1] == "  ") {
					map_LevelSecond[okhtapus2_locationHeight_LevelSecond][okhtapus2_locationRow_LevelSecond] = "  ";
					okhtapus2_locationRow_LevelSecond += 1;
					map_LevelSecond[okhtapus2_locationHeight_LevelSecond][okhtapus2_locationRow_LevelSecond] = okhtapus;

				}
				else
					okhtapus2_goright_LevelSecond = false;

			}
			else
			{
				if (map_LevelSecond[okhtapus2_locationHeight_LevelSecond][okhtapus2_locationRow_LevelSecond - 1] == "  ") {
					map_LevelSecond[okhtapus2_locationHeight_LevelSecond][okhtapus2_locationRow_LevelSecond] = "  ";
					okhtapus2_locationRow_LevelSecond -= 1;
					map_LevelSecond[okhtapus2_locationHeight_LevelSecond][okhtapus2_locationRow_LevelSecond] = okhtapus;
				}
				else {
					okhtapus2_goright_LevelSecond = true;
				}
			}

			/*if (marioY == 12 && marioX == okhtapus2_location_LevelSecond)
			{
				if (isdouble)
					isdouble = false;
				else
					GameOverForOkhtapus();
			}*/

		}
		okhtapus2_letitgo_LevelSecond = !okhtapus2_letitgo_LevelSecond;
		//==========================================
		if (okhtapus3_letitgo_LevelSecond) {
			if (okhtapus3_goright_LevelSecond)
			{
				if (map_LevelSecond[okhtapus3_locationHeight_LevelSecond][okhtapus3_locationRow_LevelSecond + 1] == "  ") {
					map_LevelSecond[okhtapus3_locationHeight_LevelSecond][okhtapus3_locationRow_LevelSecond] = "  ";
					okhtapus3_locationRow_LevelSecond += 1;
					map_LevelSecond[okhtapus3_locationHeight_LevelSecond][okhtapus3_locationRow_LevelSecond] = okhtapus;

				}
				else
					okhtapus3_goright_LevelSecond = false;

			}
			else
			{
				if (map_LevelSecond[okhtapus3_locationHeight_LevelSecond][okhtapus3_locationRow_LevelSecond - 1] == "  ") {
					map_LevelSecond[okhtapus3_locationHeight_LevelSecond][okhtapus3_locationRow_LevelSecond] = "  ";
					okhtapus3_locationRow_LevelSecond -= 1;
					map_LevelSecond[okhtapus3_locationHeight_LevelSecond][okhtapus3_locationRow_LevelSecond] = okhtapus;
				}
				else {
					okhtapus3_goright_LevelSecond = true;
				}
			}
		}
		okhtapus3_letitgo_LevelSecond = !okhtapus3_letitgo_LevelSecond;
		//==========================================
		if (okhtapus4_letitgo_LevelSecond) {
			if (okhtapus4_goright_LevelSecond)
			{
				if (map_LevelSecond[okhtapus4_locationHeight_LevelSecond][okhtapus4_locationRow_LevelSecond + 1] == "  ") {
					map_LevelSecond[okhtapus4_locationHeight_LevelSecond][okhtapus4_locationRow_LevelSecond] = "  ";
					okhtapus4_locationRow_LevelSecond += 1;
					map_LevelSecond[okhtapus4_locationHeight_LevelSecond][okhtapus4_locationRow_LevelSecond] = okhtapus;

				}
				else
					okhtapus4_goright_LevelSecond = false;

			}
			else
			{
				if (map_LevelSecond[okhtapus4_locationHeight_LevelSecond][okhtapus4_locationRow_LevelSecond - 1] == "  ") {
					map_LevelSecond[okhtapus4_locationHeight_LevelSecond][okhtapus4_locationRow_LevelSecond] = "  ";
					okhtapus4_locationRow_LevelSecond -= 1;
					map_LevelSecond[okhtapus4_locationHeight_LevelSecond][okhtapus4_locationRow_LevelSecond] = okhtapus;
				}
				else {
					okhtapus4_goright_LevelSecond = true;
				}
			}

			/*if (marioY == 12 && marioX == okhtapus4_location_LevelSecond)
			{
				if (isdouble)
					isdouble = false;
				else
					GameOverForOkhtapus();
			}*/

		}
		okhtapus4_letitgo_LevelSecond = !okhtapus4_letitgo_LevelSecond;
		//==========================================
		if ((marioY == 12 && marioX == okhtapus1_locationRow_LevelSecond && okhtapus1_letitgo_LevelSecond == true) ||
			(marioY == 25 && marioX == okhtapus2_locationRow_LevelSecond && okhtapus2_letitgo_LevelSecond == true) ||
			(marioY == 12 && marioX == okhtapus3_locationRow_LevelSecond && okhtapus3_letitgo_LevelSecond == true) ||
			(marioY == 10 && marioX == okhtapus4_locationRow_LevelSecond && okhtapus4_letitgo_LevelSecond == true)
			)
		{
			if (isdouble)
				isdouble = false;
			else
				GameOverForOkhtapus();
		}
	}


}

void StartTheGame() {
	setupConsole();
	// Initial render
	system("cls");
	if (Level == 1) {
		initializeMapArray();

		renderMap();

		// Game loop
		/*marioX = 21;
		marioY = 3;*/
		while (true) {
			// Handle input
			showjavane();
			change_okhtapus_location();
			handleInput();
			savecoins2file();


			if (isJumping_LevelFirst)
			{
				isJumping_LevelFirst = false;
			}
			else
			{
				if (map_LevelFirst[marioY + 1][marioX] == "  ")
					marioY += 1;
				else {
					if (map_LevelFirst[marioY + 1][marioX] != "  " && isdouble == true && marioY == 8 && (marioX == 50 || marioX == 51)) {
						if ((rand() % 100) <= 20)
						{
							coinCount_LevelFirst += 1;
						}
						map_LevelFirst[marioY + 1][marioX] = "  ";
					}
					else if (map_LevelFirst[marioY + 1][marioX] != "  " && marioY + 1 == 12 && (marioX == okhtapus1_location_LevelFirst || marioX == okhtapus2_location_LevelFirst || marioX == okhtapus2_location_LevelFirst + 1)) {
						GameOverForOkhtapus();
					}
					else if (map_LevelFirst[marioY + 1][marioX] != "  " && marioY + 1 == 12 && (marioX == 35 || marioX == 39 || marioX == 43 || marioX == 47))
					{
						if (isdouble == true)
						{
							isdouble = false;
						}
						else
							GameOverFortrex();
					}
				}

			}

			renderMap();

			// Small delay to control game speed
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
	else if (Level == 2) {
		initializeMapArray();

		renderMap();
		// Game loop
		while (true) {
			// Handle input
			showjavane();
			change_okhtapus_location();
			handleInput();

			// Check for coin collision
			savecoins2file();


			if (isJumping_LevelSecond)
			{
				isJumping_LevelSecond = false;
			}
			else
			{
				if (map_LevelSecond[marioY + 1][marioX] == "  ")
					marioY += 1;
				else {

					if ((marioY == 10 && marioX == 22) || (marioY == 10 && marioX == 23)) {
						marioX = 22;
						marioY = 14;
					}
					else if ((marioY == 24 && marioX == 43) || (marioY == 25 && marioX == 42)) {
						marioX = 43;
						marioY = 12;
					}
					else if ((marioY == 4 && marioX == 23) || (marioY == 4 && marioX == 22)) {
						marioX = 58;
						marioY = 2;
					}
					else if ((marioY + 1 == 24 && marioX == 43)) {
						marioX = 43;
						marioY = 12;
					}
					//--------coins--------------
					if (marioX == 32 && (marioY + 1) == 24)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[24][32] = emptySpace;
					}

					if (marioX == 41 && (marioY + 1) == 21)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[21][41] = emptySpace;
					}
					if (marioX == 42 && (marioY + 1) == 20)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[20][42] = emptySpace;

					}
					if (marioX == 42 && (marioY + 1) == 25)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[25][42] = emptySpace;

					}
					if (marioX == 3 && (marioY + 1) == 9)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[9][3] = emptySpace;

					}
					if (marioX == 17 && (marioY + 1) == 12)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[12][17] = emptySpace;
					}
					if (marioX == 28 && (marioY + 1) == 8)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[8][28] = emptySpace;
					}
					if (marioX == 49 && (marioY + 1) == 12)
					{
						coinCount_LevelSecond += 1;
						map_LevelSecond[12][49] = emptySpace;
					}
					//---------------------
					if (map_LevelSecond[marioY + 1][marioX] != "  " && isdouble == true && ((marioX == 9 && (marioY + 1) == 6) || (marioX == 34 && (marioY + 1) == 4))) {
						if ((rand() % 100) <= 20)
						{
							coinCount_LevelSecond += 1;
						}
						map_LevelSecond[marioY + 1][marioX] = "  ";
					}

					if ((map_LevelSecond[marioY + 1][marioX] != "  " && (marioY + 1) == 7 && marioX == 33)
						|| (map_LevelSecond[marioY + 1][marioX] != "  " && (marioY + 1) == 22 && marioX == 36)
						|| (map_LevelSecond[marioY + 1][marioX] != "  " && (marioY + 1) == 23 && marioX == 34))
					{
						if (isdouble == true)
						{
							isdouble = false;
						}
						else
							GameOverFortrex();
					}
				}

			}
			renderMap();

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}


	}
}
