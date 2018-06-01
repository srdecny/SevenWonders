// Wonders.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <string>
#include "Engine.h"

using namespace std;

int main()
{
	
	// stress test
	for (int i = 0; i < 1000; i++)
	{
		GameEngine engine(6, 0);
		engine.PlayTheGame();
	}
	
}

