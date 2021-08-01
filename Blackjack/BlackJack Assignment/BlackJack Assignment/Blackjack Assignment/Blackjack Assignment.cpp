#include "pch.h"
#include <iostream>
#include <cstdlib> //drand function
#include <ctime> // time function
#include <Windows.h> //Sleep function
using namespace std;

int main()
{
	int num = 0;
	char menuinput = 'a';
	int p1Total = 0;
	char choice = 'a';
	bool start_game = FALSE; // this will be false until the user presses ‘h’
	char s = 'a';
	char h = 'a';
	char a = 'a';



	Sleep(2000);
	//seed random number ganerator using the system clock
	srand(static_cast<unsigned int> (time(0)));
	//generate a random number between 1 and 13
	num = rand() % 13 + 1;

	// Welcoming user and main menu
	cout << " Welcome to Blackjack!\n\n\n";
	cout << " Press 's' to Start a new game\n";
	cout << " Press 'h' for instructions on the game\n";
	cout << " Press 'a' for information about the game\n";
	cout << " Press 'e' to exit the game\n";

	// Menu Choice
	cin >> menuinput;

	// Menu code

	while (start_game = FALSE) { //Keep the user inside this loop until they exit or start game 

		switch (menuinput) {
		case 's':
			start_game = TRUE;
			break;
		case 'h':
			cout << " You are playing against the dealer (AI). You must aim to get the total of both your cards as close to 21 as possible. You can press 'hit' to receive another card, or you can settle with your current cards by selecting 'stick'. Whichever of you are closest to 21 will be crowned the victor!Keep in mind... If you both have the same value of cards,the dealer wins.So he has the slight advantage!Good luck. ";
			break;
		case 'a':
			cout << " Blackjack, also known as 'Pontoon' or '21', is a popular card game played around the world. It is a comparing card game between the Players and the Dealer.The aim of the game is to beat the dealer by getting your cards to total as close to 21 as possible.Each player and the dealer receives two cards at the beginning of the game.Competing in turns, the players can choose to either 'stick' with what they have, or 'hit' and receive an extra card, however if their cards equal a total higher than 21, they lose!";
			break;
		case 'e':
			system("Pause");
			return 0;
		default:
			cout << "Invalid option. Please try again.";
		}
	}

	// If the code gets to this point the user has pressed play.

	{ char choice;
	// random number generator inside loop
	num = rand() % 13 + 1;

	// Add card to the total and print
	p1Total += num;
	cout << " You got " << p1Total << endl;

	// Ask them if they want to stick or hit
	cout << "Do you want to hit ('h') or stick ('s')? ";
	cin >> choice;

	} while (choice == 's');
	{
		do
		{
			char choice;
			// random number generator inside loop
			num = rand() % 13 + 1;

			// Add card to the total and print
			p1Total += num;
			cout << " You got " << p1Total << endl;

			// Ask them if they want to stick or hit
			cout << "Do you want to hit ('h') or stick ('s')? ";
			cin >> choice;

		} while (choice == 'h');

	}

}
// Remember: After each round, i'll have to set the total to 0 again.
