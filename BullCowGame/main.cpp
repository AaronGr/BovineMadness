/* This is the console executable, that makes use of the BullCow class
	This acts as the view in a MVC pattern, and is responsible for all
	user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void GetValidGuess(FText&);
void PlayGame();
void PrintGameSummary();
void PrintIntro();
void PrintGuess(FText);
bool AskToPlayAgain();

FBullCowGame BCGame;

int main() {
	
	do {
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
	
	return 0;
}

void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	FText current_guess = "";

	//loop for the number of turns asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		for (int32 i = 0; i < MaxTries; i++) {
			GetValidGuess(current_guess);  // Makes current_guess a valid guess.  TODO change this to what was done in lecture

		   //Submit valid guess to the game
			FBullCowCount bullCowCount = BCGame.SubmitValidGuess(current_guess);

			std::cout << "Bulls = " << bullCowCount.Bulls;
			std::cout << ". Cows = " << bullCowCount.Cows;
			std::cout << "." << std::endl;

			if (BCGame.IsGameWon()) {
				std::cout << std::endl;
				break;
			}

			PrintGuess(current_guess);
		}
	}

	PrintGameSummary();

	return;
}

// Loop continually until user inputs a valid guess
void GetValidGuess(FText &validGuess) {	
	EWordStatus Status = EWordStatus::Invalid;
	do {
		int32 current_try = BCGame.GetCurrentTry();
		FText current_guess = "";
		std::cout << "Try " << current_try << ". Type in your guess:  ";
		std::getline(std::cin, current_guess);
		EWordStatus Status = BCGame.CheckGuessValidity(current_guess);
		switch (Status) {
		case EWordStatus::Contains_Non_Letters:
			std::cout << "Please use only lowercase letters.\n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please use only lowercase letters.\n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		default:
			validGuess = current_guess;
			return;
		}
		std::cout << std::endl;
	} while (Status != EWordStatus::OK); // Keep looping until get no errors

}

bool AskToPlayAgain() {

	std::cout << "Do you want to play again? (y/n) ";
	std::string response = "";
	getline(std::cin, response);
	std::cout << std::endl;

	if (response[0] == 'Y' || response[0] == 'y') {
		return true;
	}

	return false;
}

void PrintIntro() {

	std::cout << "Welcome to Bulls & Cows" << std::endl;
	std::cout << "Try to guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter word." << std::endl;
	std::cout << std::endl;

	return;
}

void PrintGuess(std::string guess) {
	std::cout << "Your word was " << guess << std::endl;
	std::cout << std::endl;
	return;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "CONGRATULATIONS! YOU WON!" << std::endl;
	}
	else {
		std::cout << "Sorry, you ran out tries." << std::endl;
	}
}