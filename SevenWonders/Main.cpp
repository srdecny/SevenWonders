// Wonders.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <string>
#include "Engine.h"

using namespace std;

int main()
{
	
	
	for (int i = 0; i < 1000; i++)
	{
		GameEngine engine(3, 0);
		engine.PlayTheGame();
	}
	
	

	/*
	GameEngine engine(3, 1);
	engine.PlayTheGame();
	*/

	cout << "Finished!";
	getchar();
}

