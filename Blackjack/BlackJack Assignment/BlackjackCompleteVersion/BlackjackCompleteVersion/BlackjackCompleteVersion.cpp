#include "pch.h"
#include "Card.h"



Card::Card() {

}

Card::~Card() {

}

void Card::setCardValue(int p_value) {
	value = p_value;
}

int Card::getCardValue() {
	return value;
}

void Card::setCardName(std::string p_cardName) {
	cardName = p_cardName;
}

std::string Card::getCardName() {
	return cardName;
}

void Card::setCardType(std::string p_cardType) {
	cardType = p_cardType;
}

std::string Card::getCardType() {
	return cardType;
}

std::string Card::toString() {
	return cardName + " of " + cardType;
}




Card.h
#pragma once
#include<string>
class Card {
private:
	int value;
	std::string cardName;
	std::string cardType;
public:
	Card();
	~Card();
	void setCardValue(int p_value);
	int getCardValue();
	void setCardName(std::string p_cardName);
	std::string getCardName();
	void setCardType(std::string p_cardType);
	std::string getCardType();
	std::string toString();
};

Game.cpp

#include "pch.h"
#include "Card.h"
#include "Game.h"
#include<iostream>
#include<vector>
#include<random>
#include<time.h>
#include<stdlib.h>

std::random_device rd;
std::mt19937 gen(rd());

Game::Game() {

}

void Game::init() {
	for (int i = 0; i < 52; i++) {
		deck.push_back(Card());
	}

	std::string cardTypes[4] = { "CLUBS", "SPADES", "DIAMONDS", "HEARTS" };

	int cardTypeInd = 0;
	int currentValue = 2;
	for (int i = 0; i < 52; i++) {
		//std::cout << i << ", " << currentValue << std::endl;
		if (i == 13 || i == 26 || i == 39) {
			cardTypeInd++;
		}
		deck.at(i).setCardValue(currentValue);
		deck.at(i).setCardType(cardTypes[cardTypeInd]);
		if (i == 9 || i == 22 || i == 35 || i == 48) {
			deck.at(i).setCardName("JACK");
		}
		else if (i == 10 || i == 23 || i == 36 || i == 49) {
			deck.at(i).setCardName("QUEEN");
		}
		else if (i == 11 || i == 24 || i == 37 || i == 50) {
			deck.at(i).setCardName("KING");
		}
		else if (i == 12 || i == 25 || i == 38 || i == 51) {
			deck.at(i).setCardName("ACE");
		}
		else {
			deck.at(i).setCardName(std::to_string(currentValue));
		}
		if ((i - 10 >= -1 && i - 10 < 3) || (i - 10 > 10 && i - 10 <= 14) || (i - 10 >= 24 && i - 10 < 27) || (i - 10 > 37)) {
			currentValue = 10;
			deck.at(i).setCardValue(currentValue);
			if ((i - 10) == 2 || (i - 10) == 15 || (i - 10) == 28 || (i - 10) == 37) {
				currentValue = 2;
				deck.at(i).setCardValue(currentValue);
			}
		}
		else {
			currentValue++;
		}

		if ((i - 10) == 2 || (i - 10) == 15 || (i - 10) == 28 || (i - 10) == 41) {
			currentValue = 2;
			deck.at(i).setCardValue(currentValue);
			deck.at(i).setCardType(cardTypes[cardTypeInd]);
		}
		if (i == 12 || i == 25 || i == 38 || i == 51) {
			deck.at(i).setCardValue(11);
		}



	}
}

void Game::printDeck() {
	for (int i = 0; i < 52; i++) {
		std::cout << i << ": " << deck.at(i).getCardName() << ", " << deck.at(i).getCardValue() << ", " << deck.at(i).getCardType() << std::endl;
	}
}

void Game::displayMainMenu() {
	int value = -1;
	std::cout << "Welcome to the game of Pontoon lads..\n1. Start Game\n2. Help\n3. About\n";
	std::cin >> value;
	if (value == 1) {
		displayGameMenu();
	}
}

void Game::displayGameMenu() {
	int value = -1;
	std::cout << "Press the int value to select a menu option..\n1. New Game\n2. Help\n3. About\n4. Exit Game\n";
	std::cin >> value;
	if (value == 1) {
		startGame();
	}
	else if (value == 4) {
		displayMainMenu();
	}
}

int Game::chooseAceValue() {
	int value = -1;
	std::cout << "Choose 1 or 11 for the value of your Ace: " << std::endl;
	std::cin >> value;
	return value;
}

void Game::createNewDeck() {
	deck.clear();
	init();
	shuffle();
}

void Game::startGame() {

	std::cout << "Dealing the cards...\n";
	dealComputerPlayer();
	dealHumanPlayer();

	play();

	while (true) {
		bool again = playAgain();


		if (again) {
			system("CLS");
			createNewDeck();

			clearComputerHand();
			clearHumanHand();
			dealComputerPlayer();
			dealHumanPlayer();

			play();
		}
		else {
			break;
		}
	}


}

void Game::clearComputerHand() {
	computerHand.clear();
}

void Game::clearHumanHand() {
	humanHand.clear();
}


void Game::computerTwist() {
	int random = rand() % 1;

	for (int i = 0; i < random; i++) {
		computerHand.push_back(twist());
	}
}

void Game::play() {
	while (true) {
		displayHumanHand();
		std::cout << "Would you like to twist or stick? (twist/stick)\n" << std::endl;

		std::string tempResponse;
		std::cin >> tempResponse;

		if (tempResponse == "twist") {
			humanHand.push_back(twist());
			int humanHand = addHumanHand();
			if (humanHand > 21) {
				std::cout << "You have busted! Computer wins." << std::endl;
				break;
			}
		}
		else if (tempResponse == "stick") {

			computerTwist();

			displayComputerHand();
			displayHumanHand();

			for (int i = 0; i < humanHand.size(); i++) {
				if (humanHand[i].getCardName() == "ACE") {
					humanHand[i].setCardValue(chooseAceValue());
				}
			}

			int computerHandValue = addComputerHand();
			int humanHandValue = addHumanHand();

			int winner = chooseWinner(humanHandValue, computerHandValue);

			if (winner == 0) {
				std::cout << "Computer wins!" << std::endl;
			}
			else if (winner == 1) {
				std::cout << "You win!" << std::endl;
			}

			break;
		}
	}
}
int Game::chooseWinner(int humanHandValue, int computerHandValue) {
	bool humanPontoon = false, humanFiveCardTrick = false;
	bool computerPontoon = false, computerFiveCardTrick = false;
	bool humanThreeOrFour = false, computerThreeOrFour = false;

	//human decisions
	if (humanHandValue == 21 && humanHand.size() == 2) {
		humanPontoon = true;
	}
	else if (humanHandValue == 21 && humanHand.size() == 5) {
		humanFiveCardTrick = true;
	}

	//computer decisions
	if (computerHandValue == 21 && computerHand.size() == 2) {
		computerPontoon = true;
	}
	else if (computerHandValue == 21 && computerHand.size() == 5) {
		computerFiveCardTrick = true;
	}

	if ((humanHandValue == 21 && humanHand.size() == 3) || (humanHandValue == 21 && humanHand.size() == 4)) {
		humanThreeOrFour = true;
	}

	if ((computerHandValue == 21 && computerHand.size() == 3) || (computerHandValue == 21 && computerHand.size() == 4)) {
		computerThreeOrFour = true;
	}

	if (humanPontoon == true && computerPontoon == true) {
		return 0;
	}
	if (humanPontoon == true && computerPontoon == false) {
		return 1;
	}

	if (humanFiveCardTrick == true && computerFiveCardTrick == true) {
		return 0;
	}
	if (humanFiveCardTrick == true && computerFiveCardTrick == false) {
		return 1;
	}

	if (humanThreeOrFour == true && computerFiveCardTrick == true) {
		return 0;
	}
	if (humanFiveCardTrick == true && computerFiveCardTrick == false) {
		return 1;
	}

	if (humanHandValue <= 21 && humanHandValue > computerHandValue) {
		return 1;
	}
	else if (computerHandValue <= 21 && computerHandValue > humanHandValue) {
		return 0;
	}

	if (humanHandValue > 21) {
		return 0;
	}
	if (computerHandValue > 21) {
		return 1;
	}

	if (computerHandValue == humanHandValue) {
		return 0;
	}
}

int Game::addComputerHand() {
	int value = 0;
	for (int i = 0; i < computerHand.size(); i++) {
		value += computerHand[i].getCardValue();
	}
	return value;
}

int Game::addHumanHand() {
	int value = 0;
	for (int i = 0; i < humanHand.size(); i++) {
		value += humanHand[i].getCardValue();
	}
	return value;
}

void Game::dealHumanPlayer() {
	for (int i = 0; i < 2; i++) {
		humanHand.push_back(twist());
	}
}

void Game::dealComputerPlayer() {
	for (int i = 0; i < 2; i++) {
		computerHand.push_back(twist());
	}
}

void Game::displayComputerHand() {
	std::cout << "Computer hand: " << std::endl;
	for (int i = 0; i < computerHand.size(); i++) {
		std::cout << computerHand[i].toString() << std::endl;
	}
	std::cout << std::endl;
}

void Game::displayHumanHand() {
	std::cout << "Human hand: " << std::endl;
	for (int i = 0; i < humanHand.size(); i++) {
		std::cout << humanHand[i].toString() << std::endl;
	}
	std::cout << std::endl;
}

bool Game::playAgain() {
	bool playAgain = false;
	std::string response;
	std::cout << "Would you like to play again?(yes or no)\n";

	std::cin >> response;
	if (response == "yes") {
		playAgain = true;
	}
	return playAgain;
}
void Game::shuffle() {


	int random = -1;
	for (int i = 0; i < 52; i++) {
		//std::uniform_int_distribution<> dis(0, 51);
		//random = dis(gen);
		random = rand() % 51;
		Card temp = deck[i];
		deck[i] = deck[random];
		deck[random] = temp;
	}
}

Card Game::twist() {
	Card tmpCard = deck[0];
	deck.erase(deck.begin());
	return tmpCard;
}

void Game::stick() {

}

Game.h

#pragma once
#include "Card.h"
#include<vector>
#include<random>
class Game {
public:
	std::vector<Card> deck;
	std::vector<Card> humanHand;
	std::vector<Card> computerHand;

	Game();

	Card twist();

	bool playAgain();

	void init();
	void shuffle();
	void printDeck();
	void stick();
	void displayGameMenu();
	void displayMainMenu();
	void startGame();
	void dealHumanPlayer();
	void dealComputerPlayer();
	void displayHumanHand();
	void displayComputerHand();
	void play();
	void createNewDeck();
	void clearHumanHand();
	void clearComputerHand();
	void computerTwist();

	int chooseAceValue();
	int addHumanHand();
	int addComputerHand();
	int chooseWinner(int h, int  c);
};

Pontoon.cpp

// Pontoon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Card.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include <time.h>

int main()
{
	srand(time(NULL));
	Game game;
	game.init();
	game.shuffle();
	game.displayMainMenu();
}
