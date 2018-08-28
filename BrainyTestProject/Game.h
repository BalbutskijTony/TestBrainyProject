#pragma once
#include "Scene.h"
#include "Painter.h"
#include "PlayerController.h"
#include "AIController.h"

class Game
{
private:
	unsigned int m_playerFrags;
	unsigned int m_enemyFrags;

	AIController AI;
	Painter mainPainter;
	Scene * mainScene;
	PlayerController mainController;

	void gameCycle();
	void reset();
public:
	Game();
	void run();
	~Game();
};

