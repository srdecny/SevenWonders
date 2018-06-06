// Wonders.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <string>
#include "Engine.h"

using namespace std;

int main()
{

	string inputP, inputH;
	int players, humans;
	cout << "Welcome to the 7 Wonders game." << endl;
	cout << "Enter the total amount of players (between 3 and 7)" << endl;
	getline(cin, inputP);
	cout << "Enter the total amount of human players" << endl;
	getline(cin, inputH);

	try
	{
		players = stoi(inputP);
		humans = stoi(inputH);
		GameEngine engine(players, humans);
		engine.PlayTheGame();
	}
	catch (invalid_argument)
	{
		cout << "Invalid input!";
		return -1;
	}

	getchar();
	return 0;


	
	
}

