#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// Both Bulls and Cows initialized to 0;
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus {
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Contains_Non_Letters,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EWordStatus CheckGuessValidity(FString) const;

	void Reset(); //TODO make a more rich return value.


	FBullCowCount SubmitGuess(FString);

private:
	int32 myCurrentTry;
	int32 myMaxTries;
	FString myHiddenWord;

};