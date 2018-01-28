#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int FBullCowGame::GetMaxTries() const {	return myMaxTries; }

int FBullCowGame::GetCurrentTry() const { return myCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return myHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameWon; }

void FBullCowGame::Reset() {

	bGameWon = false;

	constexpr int32 MAX_TRIES = 3;
	myMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	myHiddenWord = HIDDEN_WORD;

	myCurrentTry = 1;
	return;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString guess) const {
	
	if (!IsIsogram(guess)) { // if the guess isn't an isogram
		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowercase(guess)) { // if the guess isn't all lowercase
		return EWordStatus::Not_Lowercase; 
	}
	else if (GetHiddenWordLength() != guess.length()) { // if the guess length is wrong
		return EWordStatus::Wrong_Length;
	}
	else {
		return EWordStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString guess) {
	myCurrentTry++;
	FBullCowCount bullCowCount;

	//loop through all letters in the guess
	int32 WordLength = myHiddenWord.length();  // Assumes word length is the same as guess
	for (int32 i = 0; i < WordLength; ++i) {
		//compare letters against the hidden word
		for (int32 j = 0; j < WordLength; ++j) {
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

	// Player wins if all letters are bulls
	// Set bGameWon to true when that happens
	if (bullCowCount.Bulls == GetHiddenWordLength()) {
		bGameWon = true;
	}

	return bullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	// Treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) {
		return true;
	}

	TMap<char, bool> LetterSeen; // Setup Map
	for (auto Letter : Word) { // Loop through every letter in the guess and check if is in the table
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { // When that letter is not in the table add it
			return false; // When that letter is in the table return that the word is not an isogram
		} 
		LetterSeen[Letter] = true; // Newly added letter set to true
	}

	return true; // If the loop finished means there were no duplicates so return that the word is an isogram
}

bool FBullCowGame::IsLowercase(FString Word) const {
	// If word is zero length or \0 return true
	if (Word.length() == 0) {
		return true;
	}

	for (auto Letter : Word) { // Loop through all the letters in the word
		if (Letter == '\0') {
			return true;
		}
		if (!isalpha(Letter) || !islower(Letter)) {
			return false; // If an uppercase letter, space, or non-letter is found return false
		}
	}
	// If the loop goes through all the letters then word is all lowercase so return true
	return true;
}
