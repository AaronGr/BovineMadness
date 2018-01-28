/* This is the console executable, that makes use of the BullCow class
	This acts as the view in a MVC pattern, and is responsible for all
	user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

FText Get_Valid_Guess();
void Play_Game();
void Print_Intro();
void Print_Guess(FText);
bool Ask_To_Play_Again();

FBullCowGame BCGame;

int main() {

	Print_Intro();
	do {
		Play_Game();
	} while (Ask_To_Play_Again());
	
	return 0;
}

void Play_Game() {
	BCGame.Reset();
	constexpr int32 NUM_GUESSES = 8;
	FText current_guess = "";

	//loop for the number of turns asking for guesses
	for (int32 i = 0; i < NUM_GUESSES; i++) { //TODO change from FOR to WHILE loop once we are validating tries
		current_guess = Get_Valid_Guess(); 

		//Submit valid guess to the game
		FBullCowCount bullCowCount =  BCGame.SubmitGuess(current_guess);

		std::cout << "Bulls = " << bullCowCount.Bulls;
		std::cout << ". Cows = " << bullCowCount.Cows;
		std::cout << "." << std::endl;

		Print_Guess(current_guess);
	}
}

// Loop continually until user inputs a valid guess
std::string Get_Valid_Guess() {	
	EWordStatus Status = EWordStatus::Invalid;
	do {
		int32 current_try = BCGame.GetCurrentTry();
		std::string guess = "";
		std::cout << "Try " << current_try << ". Type in your guess:  ";
		std::getline(std::cin, guess);
		EWordStatus Status = BCGame.CheckGuessValidity(guess);
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
			return guess;
		}
		std::cout << std::endl;
	} while (Status != EWordStatus::OK); // Keep looping until get no errors
}

void Print_Intro() {

	std::cout << "Welcome to Bulls & Cows" << std::endl;
	std::cout << "Try to guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter word." << std::endl;
	std::cout << std::endl;

	return;
}

void Print_Guess(std::string guess) {
	std::cout << "Your word was " << guess << std::endl;
	std::cout << std::endl;
	return;
}

bool Ask_To_Play_Again() {

	std::cout << "Do you want to play again? (y/n) ";
	std::string response = "";
	getline(std::cin, response);
	std::cout << std::endl;

	if (response[0] == 'Y' || response[0] == 'y') {
		return true;
	}

	return false;
}

