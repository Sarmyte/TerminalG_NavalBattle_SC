#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>


using namespace std;


//Header Functions
void fMainMenu();
void fGameScreen();

//Terminal Colors
char cMainColor[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
char cWaterColor[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
char cBoatColor[] = { 0x1b, '[', '1', ';', '3', '3', 'm', 0 };


//Cleans the Terminal
void fScreenCleaner()
{
	system("CLS");
}

//Screen after game is Finished
void fEndGameScreen(int iScore)
{
	fScreenCleaner();
	int iOptions = 0;
	while (iOptions < 1 || iOptions > 3)
	{
		cout << "!!!!!GAME!!!!\n";
		cout << "!!!FINISHED!!\n\n";
		cout << "Your End Score was: " << iScore << "\n\n";
		cout << "Would you like to:\n";
		cout << "1 - Play Again\n";
		cout << "2 - Go Back to Main Menu\n";
		cout << "3 - Exit Game\n";
		cout << "Choose an Option and Press ENTER: ";
		cin >> iOptions;

		switch (iOptions)
		{
		case 1:
			fGameScreen();
			break;
		case 2:
			fMainMenu();
			break;
		case 3:
			break;
		}
	}
}


//Function to exit the terminal
void fExitGame()
{
	exit(0);
}
//About the game Screen
void fAboutScreen()
{
	fScreenCleaner();
	int iOption = 0;
	while (iOption == 0)
	{
		cout << "!!!!ABOUT!!\n";
		cout << "!!!!THE!!!!\n";
		cout << "!!!!GAME!!!\n\n";
		cout << "This is a Game of Naval Battle in which you have 10 chances to Strike precisely where the Boats are.\n";
		cout << "By Succesfully striking a boat, you are rewarded with Score points, which determines your performance.\n";
		cout << "This is a Game made for Studying purposes\n\n";
		cout << "Credits: Jefferson Souza aka Sarmyte";
		cout << "Input 1 to go Back to the Main Menu: \n";
		cin >> iOption;
	}
}


//Applies Score and sends a Feedback to the player
void fStrikeValidation(char cBoard[10][10], int iInputRow, int iInputColumn, int* iScore, string* sSystemFeedback)
{
	switch (cBoard[iInputRow][iInputColumn])
	{
	case 'S':
		*iScore = *iScore + 10;
		*sSystemFeedback = "You Struck a Small Boat, nice!";
		break;
		/*case 'M':
			*iScore = *iScore + 15;
			break;											//For Future Updates
		case 'B':
			*iScore = *iScore + 20;
			break;*/
	case 'W':
		*sSystemFeedback = "You Struck Water, try again!";
		break;
	}
}
//Places every aspect of the board on Screen
void fPrintingBoard(char cBoard[10][10], char cBoardMask[10][10])
{
	int cont;
	int cBoardRow, cBoardColumn;
	string sRows = "Rows";
	for (cont = 0; cont < 10; cont++)
	{
		if (cont == 0)
		{
			cout << "    C o l u m n s\n";
			cout << "    ";
		}
		cout << cont << " ";
	}
	cout << "\n";
	for (cBoardRow = 0; cBoardRow < 10; cBoardRow++)
	{
		if (cBoardRow < 4)
		{
			cout << sRows[cBoardRow] << " ";
		}
		else
		{
			cout << "  ";
		}
		cout << cBoardRow;
		for (cBoardColumn = 0; cBoardColumn < 10; cBoardColumn++)
		{

			switch (cBoardMask[cBoardRow][cBoardColumn])
			{
			case 'W':
				cout << cWaterColor;
				//cout << " " << cBoard[cBoardRow][cBoardColumn];				//Cheat Mode
				cout << " " << cBoardMask[cBoardRow][cBoardColumn];
				break;

			case 'S':
				cout << cBoatColor;
				//cout << " " << cBoard[cBoardRow][cBoardColumn];				//Cheat Mode
				cout << " " << cBoardMask[cBoardRow][cBoardColumn];
				break;


			default:
				cout << cMainColor;
				//cout << " " << cBoard[cBoardRow][cBoardColumn];				//Cheat Mode
				cout << " " << cBoardMask[cBoardRow][cBoardColumn];
				break;
			}
		}
		cout << "\n";
	}
}
//Places boats randomly on the board
void fGeneratingRandomBoatSpots(char cBoard[10][10])
{
	int iCont, iBoatAmount = 10, iBoatAmountPlaced = 0;

	while (iBoatAmountPlaced < iBoatAmount)
	{
		int iRandomBoatRow = rand() % 10;
		int	iRandomBoatColumn = rand() % 10;

		if (cBoard[iRandomBoatRow][iRandomBoatColumn] == 'W')
		{
			cBoard[iRandomBoatRow][iRandomBoatColumn] = 'S';
			iBoatAmountPlaced++;
		}
	}
}
//Creates both the actual board and masked board
void fCreatingBoard(char cBoard[10][10], char cBoardMask[10][10])
{
	int cBoardRow, cBoardColumn;
	for (cBoardRow = 0; cBoardRow < 10; cBoardRow++)
	{
		for (cBoardColumn = 0; cBoardColumn < 10; cBoardColumn++)
		{
			cBoard[cBoardRow][cBoardColumn] = 'W';
			cBoardMask[cBoardRow][cBoardColumn] = '*';
		}
	}
}
//Screen shown during play time
void fGameScreen()
{
	char cBoard[10][10], cBoardMask[10][10];
	int iInputRow, iInputColumn;
	int iGameState = 1;
	int iScore = 0;
	int iStrikes = 0, iMaximumStrikes = 10;
	string sSystemFeedback = "Time to Strike!";

	fCreatingBoard(cBoard, cBoardMask);
	fGeneratingRandomBoatSpots(cBoard);

	while (iStrikes < iMaximumStrikes)
	{
		fScreenCleaner();

		fPrintingBoard(cBoard, cBoardMask);

		cout << "\n";
		cout << sSystemFeedback << "\n\n";
		cout << "Strikes Remaining: " << iMaximumStrikes - iStrikes << "\n";
		cout << "Score: " << iScore << "\n";
		cout << "Input a Row you wish to Strike" << "\n";
		cin >> iInputRow;
		cout << "Input a Column you wish to Strike" << "\n";
		cin >> iInputColumn;

		//Checking if the Strike is in Range.
		while ((iInputRow < 0 || iInputColumn < 0) || (iInputRow > 9 || iInputColumn > 9))
		{
			fScreenCleaner();

			fPrintingBoard(cBoard, cBoardMask);

			cout << "\n";
			cout << sSystemFeedback << "\n\n";
			cout << "Strikes Remaining: " << iMaximumStrikes - iStrikes << "\n";
			cout << "Score: " << iScore << "\n\n";
			cout << "You struck in a Row or Column that is out of Range! Try again.\n\n";
			cout << "Input a Row you wish to Strike" << "\n";
			cin >> iInputRow;
			cout << "Input a Column you wish to Strike" << "\n";
			cin >> iInputColumn;
		}


		fStrikeValidation(cBoard, iInputRow, iInputColumn, &iScore, &sSystemFeedback);

		cBoardMask[iInputRow][iInputColumn] = cBoard[iInputRow][iInputColumn];
		iStrikes++;
	}

	fEndGameScreen(iScore);

}

//Starting options menu
void fMainMenu()
{
	fScreenCleaner();
	int iOptions = 0;
	while (iOptions < 1 || iOptions > 3)
	{
		cout << "!!!!!WELCOME!!!!\n";
		cout << "!!!!!!!TO!!!!!!!\n";
		cout << "!!NAVAL BATTLE!!\n\n";
		cout << "1 - Play Game\n";
		cout << "2 - About the Game\n";
		cout << "3 - Exit Game\n";
		cout << "Choose an Option and Press ENTER: ";
		cin >> iOptions;

		switch (iOptions)
		{
		case 1:
			fGameScreen();
			break;
		case 2:
			fAboutScreen();
			break;
		case 3:
			fExitGame();
			break;
		}
	}
}


int main()
{
	cout << cMainColor;
	srand((unsigned)time(NULL));


	fMainMenu();


	return 0;
}