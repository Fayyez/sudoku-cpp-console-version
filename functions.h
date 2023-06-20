
#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
using namespace std;
//global variables
const int row = 9, column = 9;//coordinates of the sudoku board
const int leaderboard_size = 7;

int main();
string displayMainMenu(int);//displays main menu on console
/*Main Menu allows user to 1)play(continue to operation menu), 2)see credits, 3)see instructions*/
string displayOperationMenu(int);//to display operation menu on console
/*Main Menu allows user to 1)start new game(creates a new template from a solution), 2)open an existing game,
 3)go back to main menu*/
string displayModeSelectionMenu(int);//displays mode selection menu
/*Main Menu allows user to select a mode from easy, medium or hard which correspond to different numbers of #
 hints given in the template*/
string displaySavingMenu(int);//displays saving menu
/*allows usr to save his progress in any one of three slots*/
void createTemplate(int solution[][column], int Template[][column], int board[][column], int solution_current[][column], int);//creats a new sudoku template
void validateOption(string&, string, string, string);//validate choice of user from all the menus
void displayCredits(int);//show credits
void displayInstructions(int);//show instructions on console
bool validateNumber(string);//take inout between 1 and 9 only
void setCord(int, int);//to set coordinate of cursor on console
void printSudoku(int board[][column], int Template[][column],int);//print the sudoku board on console
void printSudoku(int board[][column], int Template[][column]);//print sudoku board for get solution (without score)
void takeInput(int Template[][column], int board[][column], int solution_current[][column], string slot,int&score);//function prototypes
bool checkRowColumnBox(int arr[][column], int i, int j, int valueToInsert);//validates user input into board
void createHeading(string, char);
void setColor(int);//change text color
void shuffle(int arr[][column]);//shuffles a 2D-array to make new solution
void showLoadingScreen(int);//shows a loading screen just like graphics which might give us extra absolutes
void sideMenu(string,string, int Template[][column], int board[][column],int user_score);//for side options of playing screen, i.e., save & quit from playing
void getSolution(string, int Template[][column], int solution_current[][column]);//to print solved sudoku board in case user asks for it in playing screen (takeInput)
bool checkEnding(int baord[][column]);//returns true when board is complete
void DisplayEndingScreen(int go);//displays kamaal kism ki ending screen FOR EXTRA ABSOLUTES 
void showLeaderBoard(int score[], string name[]);//leader board contain top 7 players with their scores
void sortArray(int arr[], int size, string name[]);//to sort leaderboard list
