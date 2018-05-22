// Wonders.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <string>
#include "Engine.h"

using namespace std;

int main()
{
	
	GameEngine engine(3, 0);
	engine.PlayTheGame();

	getchar();
}

