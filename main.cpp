#pragma once
/*This is the console executable, that makes use of the BullCow Class
This acts as the view in a MVC pattern, and is responsible for all user interaction
for game logic go to FBullCowGame
*/
#include <iostream>
#include <string>
#include "fBullCowGame.h"

// To make syntax Unreal friendly
using FText = std::string;	
using int32 = int;

void PrintIntro();
FText GetValidGuess();
void ShowGuess(FText&, FBullCowCount);
void PlayGame();
void EndGameCredits();
bool AskToPlayAgain();
FBullCowGame BCGame;			//Instantiate a new game, which we reuse across all plays

int main() {		//Entrypoint for the game	
	
	do {
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	//End program
	std::cout << std::endl;
	return 0;
}

void PrintIntro() {					//Game introduction
	std::cout << "Welcome to the bullshit" << std::endl;

	std::cout << std::endl;
	std::cout << "    ________{__}     __ " << std::endl;
	std::cout << "  /|########[oo]    [oo]" << std::endl;
	std::cout << " / |#######|(..)    (..)" << std::endl;
	std::cout << "*  ||     ||            ||" << std::endl;
	std::cout << "What lenght do you wish your word to be?()(4-6)";
	FString Request;
	getline(std::cin, Request);
	if (Request[0] == '4') {
		BCGame.SetRequestedWordLength(4);	
	} else if(Request[0] == '5'){
		BCGame.SetRequestedWordLength(5);
	} else {
		BCGame.SetRequestedWordLength(6);
	}
	BCGame.SetHiddenWord();
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking if?" << std::endl;
	return;
}

FText GetValidGuess() {	
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		std::cout << "Try " << BCGame.GetCurrentTry() << " out of " << BCGame.GetMaxTries() << ". Enter your guess: " << std::endl;
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Incorrect_Length:
			std::cout << "Your guess was not of incorrect length." << std::endl;
			std::cout << "It should be " << BCGame.GetHiddenWordLength() << " letters long.";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Your guess was not an isogram.";
			break;
		case EGuessStatus::Upper_Case:
			std::cout << "Your guess should be all lowercase.";
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void ShowGuess(FText &Guess, FBullCowCount BullCowCount) {		
	std::cout << "Your guess was: " << Guess << std::endl;
	std::cout << "It has " << BullCowCount.Bulls << " bulls, and " << BullCowCount.Cows << " cows." << std::endl << std::endl;
	return;
}

void PlayGame() {					//The game loop and logic
	do {
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		ShowGuess(Guess, BullCowCount); 
	} while (BCGame.GetCurrentTry() <= BCGame.GetMaxTries() && BCGame.IsGameWon() == false);
	EndGameCredits();
	return;
}

void EndGameCredits() {
	if (BCGame.IsGameWon()) {
		std::cout << "Well Done - You Win!" << std::endl;
	} else {
		std::cout << "Better luck next time." << std::endl;
	}
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again with the same hidden word? (y/n)" << std::endl;
	FText Answer;
	std::getline(std::cin, Answer);
	std::cout << std::endl;
	BCGame.Reset();
	return (Answer[0] == 'Y' || Answer[0] == 'y');
}