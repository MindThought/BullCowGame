#pragma once

#include "fBullCowGame.h"


FBullCowGame::FBullCowGame() { Reset(); }	//Default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {2,4}, {3,5}, {4,6}, {5,7}, {6,8}, {7,9}, {8,10} };
	return WordLengthToMaxTries[GetHiddenWordLength()]; 
}

bool FBullCowGame::IsIsogram(FString Guess) const {
	if (Guess.length() < 2) { return true; }
	TMap<char, bool> LettersSeen;
	for (auto Letter : Guess) {
		Letter = tolower(Letter);
		if (LettersSeen[Letter]) { return false; }
		else {
			LettersSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const {
	for (auto Letter : Guess) {
		if (!islower(Letter)) { return false; }
	}
	return true;
}

void FBullCowGame::SetRequestedWordLength(int32 Request){
	RequestedWordLength = Request;
	return;
}

void FBullCowGame::SetHiddenWord() { //TODO add randomization
	//These must all be isogram
	TMap<int32, FString> FourLetterWords{ { 0,"flow" },{ 1,"duck" },{ 2,"thor" } }; 
	TMap<int32, FString> FiveLetterWords{ { 0,"truck" },{ 1,"ducks" },{ 2,"plane" } };
	TMap<int32, FString> SixLetterWords{ { 0,"planet" },{ 1,"garlic" },{ 2,"forget" } };
	if (RequestedWordLength == 4) {
		MyHiddenWord = FourLetterWords[0];
	}
	else if (RequestedWordLength == 5) {
		MyHiddenWord = FiveLetterWords[0];
	}
	else {
		MyHiddenWord = SixLetterWords[0];
	}
}

void FBullCowGame::Reset() {
	MyCurrentTry = 1;
	SetHiddenWord();
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (Guess.length() != MyHiddenWord.length()) { return EGuessStatus::Incorrect_Length; }
	if (!IsIsogram(Guess)) { return EGuessStatus::Not_Isogram; }
	if (!IsLowercase(Guess)) { return EGuessStatus::Upper_Case; }
	return EGuessStatus::OK;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {//Recieves a valid Guess, increments try #, returns bulls ands cows
	MyCurrentTry++;
	FBullCowCount BullCowCount; 
	int32 WordLength = MyHiddenWord.length();	// Assuming Guess is the same length as MyHiddenWord
	for (int32 i = 0; i < WordLength; i++) {	//loop through all the letters in Guess and matching them against MyHiddenWord
		if (Guess[i] == MyHiddenWord[i]) { BullCowCount.Bulls++; }	// If Guess and MyHiddenWord has the same letter at index i, increment Bulls, otherwise,
		else if (MyHiddenWord.find(Guess[i]) != -1) { BullCowCount.Cows++; } // If the char in Guess at index i is found in MyHiddenWord, increment Cows
	}
	if (BullCowCount.Bulls == WordLength) { bGameIsWon = true; }
	return BullCowCount;
}
