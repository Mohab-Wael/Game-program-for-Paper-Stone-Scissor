#include<iostream>

using namespace std;

enum enGameChoices { Stone = 1, Paper = 2, Scissors = 3 };

enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoices PlayerChoice;
	enGameChoices ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameResults
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string GameWinnerName="";
};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

enGameChoices GetComputerChoise()
{
	return (enGameChoices)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.PlayerChoice)
	{
	case enGameChoices::Stone:
		return (RoundInfo.ComputerChoice == enGameChoices::Paper) ? enWinner::Computer : enWinner::Player;
	case enGameChoices::Paper:
		return (RoundInfo.ComputerChoice == enGameChoices::Scissors) ? enWinner::Computer : enWinner::Player;
	case enGameChoices::Scissors:
		return (RoundInfo.ComputerChoice == enGameChoices::Stone) ? enWinner::Computer : enWinner::Player;
	}
}
enWinner WhoWonTheGame(short PlayerWinTimes,short ComputerWinTimes)
{
	if (PlayerWinTimes > ComputerWinTimes)
		return enWinner::Player;
	else if (ComputerWinTimes > PlayerWinTimes)
		return enWinner::Computer;
	else  return enWinner::Draw;
}
string ChoiceName(enGameChoices Choise)
{
	string arrGameChoise[3] = { "Stone","Paper","Scissors" };
	return arrGameChoise[Choise - 1];
}
string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player","Computer","No Winner (Draw)" };
	return arrWinnerName[Winner - 1];
}
enGameChoices ReadPlayerChoice()
{
	short Choise;
	do
	{
		cout << "\nYour Choice: [1]:Stone,[2]:Paper, [3]:Scissors ? ";
		cin >> Choise;
	} while (Choise < 1 || Choise >10);

	return (enGameChoices)Choise;
}
void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Computer:
		system("Color 4F");
		break;
	case enWinner::Player:
		system("Color 2F");
		cout << "\a";
		break;
	default:
		system("Color 6F");
		break;
	}
}
void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n______________________ Round [" << RoundInfo.RoundNumber << "]______________\n\n";
	cout << "Player 1 choice: " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner: [" << RoundInfo.WinnerName << "]" << endl;
	cout << "_____________________________________________\n";

	SetWinnerScreenColor(RoundInfo.Winner);
}
stGameResults FillGameResults(short GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;
	GameResults.GameRounds = GameRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResults.GameWinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;
}
stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	for (int GameRound = 1;GameRound <= HowManyRounds;GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoise();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else if (RoundInfo.Winner == enWinner::Player)
			PlayerWinTimes++;
		else DrawTimes++;

	   PrintRoundResults(RoundInfo);
	}
	return FillGameResults( HowManyRounds,PlayerWinTimes,ComputerWinTimes,DrawTimes);
}

short ReadHowManyRounds()
{
	short Rounds=0;
	cout << "How many rounds do you want to play ? ";
	cin >> Rounds;

	return Rounds;
}
string Taps(short NumberofTaps)
{
	string t = "";

	for (int i = 1;i < NumberofTaps;i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}

void ShowGameOverScreen()
{
	cout << Taps(2) << "__________________________________________________\n\n";
	cout << Taps(2) << "              +++ G a m e  O v e r +++\n";
	cout << Taps(2) << "__________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{
	cout << Taps(3) << "________________________ [Game Results] _________________________\n\n";
	cout << Taps(3) << "Game Rounds       : " << GameResults.GameRounds << endl;
	cout << Taps(3) << "Player 1 Win Times: " << GameResults.Player1WinTimes << endl;
	cout << Taps(3) << "Computer Win Times: " << GameResults.ComputerWinTimes << endl;
	cout << Taps(3) << "Draw Times        : " << GameResults.DrawTimes << endl;
	cout << Taps(3) << "Final Winner      : " << GameResults.GameWinnerName << endl;
	cout << Taps(3) << "_________________________________________________________________\n\n";

	SetWinnerScreenColor(GameResults.GameWinner);
}
void ResetGame()
{
	system("Color 0F");
	system("cls");

}
void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetGame();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << endl << Taps(3) << "Do you want to play again ? Y/N ? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();

	return 0;
}