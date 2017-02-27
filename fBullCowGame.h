/* The game logic (no view code or direct user interaction)
The game is a simple word guess game*/
#pragma once

#include <string>
#include <map>


// To make syntax Unreal friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

struct FBullCowCount	{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Incorrect_Length,
	Upper_Case
};

class FBullCowGame {
public:
	FBullCowGame();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; // Checks if the guess is valid and returns an status based on the results

	void SetRequestedWordLength(int32);
	void SetHiddenWord();
	void Reset();									// Sets the gamestate to a blank slate
	FBullCowCount SubmitValidGuess(FString);		// Counts the number of Bulls and Cows and checks if the game has been won

private:
	int32 MyCurrentTry;
	int32 RequestedWordLength;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};