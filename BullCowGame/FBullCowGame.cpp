#include "FBullCowGame.h"

using FString = std::string;
using int32 = int;

void FBullCowGame::Reset() {

	constexpr int32 MAX_TRIES = 8;
	myMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	myHiddenWord = HIDDEN_WORD;

	myCurrentTry = 1;
	return;
}

FBullCowGame::FBullCowGame() {
	Reset();
}

int FBullCowGame::GetMaxTries() const {
	return myMaxTries;
}

int FBullCowGame::GetCurrentTry() const {
	return myCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const {
	return myHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const {
	return false;
}


EWordStatus FBullCowGame::CheckGuessValidity(FString guess) const {
	
	if (false) { // if the guess isn't an isogram
		return EWordStatus::Not_Isogram;
	}
	else if (false) { // if the guess isn't all lowercase
		return EWordStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != guess.length()) { // if the guess length is wrong
		return EWordStatus::Wrong_Length;
	}
	else {
		return EWordStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitGuess(FString guess) {
	//increment the turn number
	myCurrentTry++;

	//setup a return variable
	FBullCowCount bullCowCount;

	//loop through all letters in the guess
	int32 hiddenWordLength = myHiddenWord.length();
	for (int32 i = 0; i < hiddenWordLength; ++i) {
		//compare letters against the hidden word
		for (int32 j = 0; j < hiddenWordLength; ++j) {
			if (guess[i] == myHiddenWord[j]) {
				if (i == j) {
					++bullCowCount.Bulls;
				}
				else {
					++bullCowCount.Cows;
				}
			}
		}

	}
		

	return bullCowCount;
}
