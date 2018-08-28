#pragma once
#include <queue>
using std::queue;
#include "Scene.h"
#include <conio.h>

class PlayerController
{
private:
	queue<int> command;
public:
	PlayerController() = default;
	~PlayerController() = default;
	void listenAndTransfer(Scene & S);
};

