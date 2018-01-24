#include <iostream>
#include <string>
#include "main.h"

int main() {

	constexpr int WORD_LENGTH = 5;

	Print_Starting_Text(WORD_LENGTH);

	Get_Players_Guess(WORD_LENGTH);

	return 0;
}

void Get_Players_Guess(const int &WORD_LENGTH)
{
	std::string guess = "";
	std::cout << "Type a " << WORD_LENGTH;
	std::cout << " letter word: ";
	std::getline(std::cin, guess);
	std::cout << "Your word was " << guess << std::endl;
	std::cout << std::endl;
}

void Print_Starting_Text(const int &WORD_LENGTH)
{
	std::cout << "Welcome to Bulls & Cows" << std::endl;
	std::cout << "Try to guess the " << WORD_LENGTH;
	std::cout << " letter word." << std::endl;
	std::cout << std::endl;
}
