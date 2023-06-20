#include "functions.h"
using namespace std;

int main()
{

	ifstream Slot1_read("txt/Slot1.txt"), Slot2_read("txt/Slot2.txt"), Slot3_read("txt/Slot3.txt"); // reading streams for boards & Templates
	ifstream Template1_read("txt/Template1.txt"), Template2_read("txt/Template2.txt"), Template3_read("txt/Template3.txt");
	ifstream Solved1_read("txt/Solved1.txt"), Solved2_read("txt/Solved2.txt"), Solved3_read("txt/Solved3.txt");							// in case user asks for the solution
	ifstream Slot1_score_read("txt/Slot1_score.txt"), Slot2_score_read("txt/Slot2_score.txt"), Slot3_score_read("txt/Slot3_score.txt"); // to read scores of slots
	ifstream leaderboard_read("txt/SudokuLeaderBoard.txt"), leaderboard_score_read("txt/scores.txt");								// to read from leaderboard (containing top 7 player names)

	int solution1[row][column] = {// possible solutions of sudoku to get the template from
								4, 3, 5, 2, 6, 9, 7, 8, 1,
								6, 8, 2, 5, 7, 1, 4, 9, 3,
								1, 9, 7, 8, 3, 4, 5, 6, 2,
								8, 2, 6, 1, 9, 5, 3, 4, 7,
								3, 7, 4, 6, 8, 2, 9, 1, 5,
								9, 5, 1, 7, 4, 3, 6, 2, 8,
								5, 1, 9, 3, 2, 6, 8, 7, 4,
								2, 4, 8, 9, 5, 7, 1, 3, 6,
								7, 6, 3, 4, 1, 8, 2, 5, 9};
	int solution2[row][column] = {
								7, 3, 5, 6, 1, 4, 8, 9, 2,
								8, 4, 2, 9, 7, 3, 5, 6, 1,
								9, 6, 1, 2, 8, 5, 3, 7, 4,
								2, 8, 6, 3, 4, 9, 1, 5, 7,
								4, 1, 3, 8, 5, 7, 9, 2, 6,
								5, 7, 9, 1, 2, 6, 4, 3, 8,
								1, 5, 7, 4, 9, 2, 6, 8, 3,
								6, 9, 4, 7, 3, 8, 2, 1, 5,
								3, 2, 8, 5, 6, 1, 7, 4, 9};
	int solution3[row][column] = {
								1, 5, 2, 4, 8, 9, 3, 7, 6,
								7, 3, 9, 2, 5, 6, 8, 4, 1,
								4, 6, 8, 3, 7, 1, 2, 9, 5,
								3, 8, 7, 1, 2, 4, 6, 5, 9,
								5, 9, 1, 7, 6, 3, 4, 2, 8,
								2, 4, 6, 8, 9, 5, 7, 1, 3,
								9, 1, 4, 6, 3, 7, 5, 8, 2,
								6, 2, 5, 9, 4, 8, 1, 3, 7,
								8, 7, 3, 5, 1, 2, 9, 6, 4};

	int Template[row][column] = {0};											// template contains hints from solution and zeroes for all other indices
	int board[row][column] = {0};												// initiate the board with zeroes
	int solution_current[row][column] = {0};									// to store a solution of sudoku board in case user asks for it
	string leaderboard[leaderboard_size] = {"-", "-", "-", "-", "-", "-", "-"}; // contains names of top 7 players
	int leaderboard_score[leaderboard_size] = {0};								// contains scores of top 7 players
	int user_score = 0;
	int playersInLeaderboard = 7;

	if (leaderboard_read.is_open()) // if the are names in leaderboard then read into leaderboard[], scores in file into scores array
	{
		for (int i = 0; i < 7; i++) // reads scores
		{
			leaderboard_score_read >> leaderboard_score[i];
		}

		for (int i = 0; i < 7; i++) // reads names into leaderboard
		{
			char name_temp[25];							   // temp char to store the name as getline doesnt work for string[]
			leaderboard_read.getline(name_temp, 25, '\n'); // getline instead of >> so white spaces are not skipped
			string str_name(name_temp);					   // temp string to convert the char[] into a string type variable
			leaderboard[i] = str_name;					   // store the temp str to relevant leaderboard index
		}
		leaderboard_score_read.close();
		leaderboard_read.close();
	}

	string option_mainMenu, option_operationMenu, option_difficultyLevel, option_savingMenu; // variables for user choice of different menus
	do
	{ // main loop for main menu
		// PlaySound(TEXT("main_plus_pink"), NULL, SND_ASYNC);//play welcome to main mainu sound in english & urdu
		option_mainMenu = displayMainMenu(1); // returns user choice of main menu
		if (option_mainMenu == "c")			  // if user asks for credits
		{
			displayCredits(1);
			continue; // go back to main menu
		}

		else if (option_mainMenu == "l") // if user asks for instructions
		{
			showLeaderBoard(leaderboard_score, leaderboard);
			continue; // go back to main menu
		}

		else if (option_mainMenu == "p") // if user asks for playing game go to operation menu
		{
			do
			{
				option_operationMenu = displayOperationMenu(1); // show operation & return user choice

				if (option_operationMenu == "n")
				{
					user_score = 10000; // reset score to 10,000 points for every new game

					for (int i = 0; i < row; i++) // reinitialize with zeros to create a new empty array
					{
						for (int j = 0; j < column; j++)
						{
							Template[i][j] = 0;
							board[i][j] = 0;
						}
					}

					int hints_total = 0;								  // stores how many hints to print based on difficulty level
					option_difficultyLevel = displayModeSelectionMenu(1); // return user choice of difficulty level
					if (option_difficultyLevel == "e")
					{
						hints_total = 45;
					}
					else if (option_difficultyLevel == "m")
					{
						hints_total = 30;
					}
					else
					{
						hints_total = 15;
					}

					srand((unsigned int)time(0));	   // create a random number for choice of solution
					int choiceOfSolution = rand() % 3; // select one random solution to create Template from
					if (choiceOfSolution == 0)
						createTemplate(solution1, Template, board, solution_current, hints_total);
					if (choiceOfSolution == 1)
						createTemplate(solution2, Template, board, solution_current, hints_total);
					if (choiceOfSolution == 2)
						createTemplate(solution3, Template, board, solution_current, hints_total);
					option_savingMenu = displaySavingMenu(1); // get which slot to write in from user

					if (option_savingMenu == "1") // write new template&board into slot 1
					{
						ofstream Slot1_write("txt/Slot1.txt"), Template1_write("txt/Template1.txt"), Solved1_write("txt/Solved1.txt"), Slot1_score_write("txt/Slot1_score.txt");
						Slot1_score_write << user_score;
						for (int i = 0; i < row; i++)
						{
							for (int j = 0; j < column; j++)
							{
								Slot1_write << board[i][j] << " ";				// create board file
								Template1_write << Template[i][j] << " ";		// create template file
								Solved1_write << solution_current[i][j] << " "; // create solution file
							}
						}
						Slot1_write.close(); // closing all files
						Template1_write.close();
						Solved1_write.close();
						Slot1_score_write.close();
					}
					if (option_savingMenu == "2") // write new template&board into slot 2
					{
						ofstream Slot2_write("txt/Slot2.txt"), Template2_write("txt/Template2.txt"), Solved2_write("txt/Solved2.txt"), Slot2_score_write("txt/Slot2_score.txt");
						Slot2_score_write << user_score;
						for (int i = 0; i < row; i++)
						{
							for (int j = 0; j < column; j++)
							{
								Slot2_write << board[i][j] << " ";				// create board file
								Template2_write << Template[i][j] << " ";		// create template file
								Solved2_write << solution_current[i][j] << " "; // create solution file
							}
						}
						Slot2_write.close();
						Template2_write.close();
						Solved2_write.close();
						Slot2_score_write.close();
					}
					if (option_savingMenu == "3") // write new template & board into slot 3
					{
						ofstream Slot3_write("txt/Slot3.txt"), Template3_write("txt/Template3.txt"), Solved3_write("txt/Solved3.txt"), Slot3_score_write("txt/Slot3_score.txt");
						Slot3_score_write << user_score;

						for (int i = 0; i < row; i++)
						{
							for (int j = 0; j < column; j++)
							{
								Slot3_write << board[i][j] << " ";				// create board file
								Template3_write << Template[i][j] << " ";		// create template file
								Solved3_write << solution_current[i][j] << " "; // create solution file
							}
						}
						Slot3_write.close();
						Template3_write.close();
						Solved3_write.close();
						Slot3_score_write.close();
					}
				}

				else if (option_operationMenu == "s")
				{
					option_savingMenu = displaySavingMenu(1);
					if (option_savingMenu == "1") // reading Template & board from slot 1
					{
						if (!Slot1_read.is_open()) // if slot is empty, prompt user & go back to operation menu
						{
							cout << "**** OOPS SLOT 1 IS EMPTY, START NEW GAME or SELECT ANOTHER SLOT ****\n\n";
							system("pause");
							continue;
						}
						else // when slot 1 has a file
						{
							Slot1_score_read >> user_score; // gets the score from slot 1
							for (int i = 0; i < row; i++)	// read board and Template from slot 1
							{
								for (int j = 0; j < column; j++)
								{
									Slot1_read >> board[i][j];
									Template1_read >> Template[i][j];
									Solved1_read >> solution_current[i][j]; // reads the solution of the template
								}
							}
							Slot1_read.close();
							Template1_read.close();
							Solved1_read.close();
							Slot1_score_read.close();
						}
					}
					else if (option_savingMenu == "2") // reading Template & board from slot 2
					{
						if (!Slot2_read.is_open()) // if slot 2 is empty, prompt user & go back to operation menu
						{
							cout << "**** OOPS, SLOT 2 IS EMPTY, START NEW GAME or SELECT ANOTHER SLOT ****\n\n";
							system("pause");
							continue;
						}
						else // when slot 2 has a file
						{
							Slot2_score_read >> user_score; // gets the score from slot 2
							for (int i = 0; i < row; i++)	// read board and Template from slot 2
							{
								for (int j = 0; j < column; j++)
								{
									Slot2_read >> board[i][j];
									Template2_read >> Template[i][j];
									Solved2_read >> solution_current[i][j]; // reads the solution of the template
								}
							}
							Slot2_read.close();
							Template2_read.close();
							Solved2_read.close();
							Slot2_score_read.close();
						}
					}
					else if (option_savingMenu == "3") // reading Template & board from slot 3
					{
						if (!Slot3_read.is_open()) // if slot 3 is empty, prompt user & go back to operation menu
						{
							cout << "**** OOPS, SLOT 3 IS EMPTY, START NEW GAME or SELECT ANOTHER SLOT ****\n\n";
							system("pause");
							continue;
						}
						else // when slot 3 has a file
						{
							Slot3_score_read >> user_score; // gets the score from slot 3
							for (int i = 0; i < row; i++)	// read board and Template from slot 3
							{
								for (int j = 0; j < column; j++)
								{
									Slot3_read >> board[i][j];
									Template3_read >> Template[i][j];
									Solved3_read >> solution_current[i][j]; // reads the solution of the template
								}
							}
							Slot3_read.close();
							Template3_read.close();
							Solved3_read.close();
							Slot3_score_read.close();
						}
					}
				}

				else if (option_operationMenu == "m")
					continue;

				// PlaySound(TEXT("loading_screen.wav"), NULL, SND_ASYNC);//loading screen music
				showLoadingScreen(1); // just for extra absolutes

				do
				{ // actual game

					takeInput(Template, board, solution_current, option_savingMenu, user_score); // takes input, prompts for repeating values

					if (checkEnding(board)) // if board is completed then display ending
					{
						DisplayEndingScreen(1); // diplay the ending screen

						if (user_score >= leaderboard_score[leaderboard_size - 1]) // if user is among top 7 scorers
						{
							leaderboard_score[leaderboard_size - 1] = user_score; // add user_score to last index of top 7 score list
							string text = "\tCONGRATULATIONS, YOU ARE AMONG TOP 7 SCORERS OF ALL TIME\n\t\t\t\t        YOUR NAME WILL BE ADDED TO OUR LEADERBOARD";
							string name;
							createHeading(text, '~');
							do
							{
								cout << "Tell us your name (20 characters) : "; // ask user his name
								getline(cin, name);
								if (name.length() > 20) // when name is too long
								{
									cout << "input is too long. Please enter less than 20 characters.\n";
								}
							} while (name.length() > 20);								 // if name is greater than 24 characters then dont allow as it disturbs leaderboard
							leaderboard[leaderboard_size - 1] = name;					 // store name to last index of top 7 name list
							sortArray(leaderboard_score, leaderboard_size, leaderboard); // sort the leaderboard
							ofstream leaderboard_write("txt/SudokuLeaderBoard.txt"), leaderboard_score_write("txt/scores.txt");
							for (int i = 0; i < leaderboard_size; i++)
							{
								leaderboard_write << noskipws << leaderboard[i] << endl; // write name into leaderboard file
								leaderboard_score_write << leaderboard_score[i] << endl; // write score into score file
							}
							leaderboard_write.close();
							leaderboard_score_write.close();
						}
						showLeaderBoard(leaderboard_score, leaderboard);

						// after game is completed, delete that slot files from system
						if (option_savingMenu == "1")
						{
							remove("txt/Slot1.txt");
							remove("txt/Template1.txt");
							remove("txt/Solved1.txt");
							remove("txt/Slot1_score.txt");
						}
						else if (option_savingMenu == "2")
						{
							remove("txt/Slot2.txt");
							remove("txt/Template2.txt");
							remove("txt/Solved2.txt");
							remove("txt/Slot2_score.txt");
						}
						else if (option_savingMenu == "3")
						{
							remove("txt/Slot3.txt");
							remove("txt/Template3.txt");
							remove("txt/Solved3.txt");
							remove("txt/Slot1_score.txt");
						}
					}

				} while (!checkEnding(board)); // loop exits when board is completed with valid input values, goes back to operation menu

			} while (option_operationMenu != "m");
		}

	} while (1); // infinite loop for the main menu

	return 0;
}
