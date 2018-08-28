#include "Game.h"

Game::Game() {
	mainScene = new Scene;
}

Game::~Game() {
	delete mainScene;
}

void Game::gameCycle() {
	mainScene->setMaxScreen(mainPainter.getRightBottomPoint());
	while (!(mainScene->isPlayerDead()) && !mainScene->isEnemyDead()) 
	{
		mainScene->setMaxScreen(mainPainter.getRightBottomPoint());
		mainController.listenAndTransfer(*mainScene);
		mainScene->gameTic();
		AI.listen(*mainScene);
		mainPainter.drawAll(*mainScene, m_playerFrags, m_enemyFrags);
	}
	if (mainScene->isPlayerDead()) m_enemyFrags++;
	if (mainScene->isEnemyDead()) m_playerFrags++;
}

void Game::reset() {
	delete mainScene;
	mainScene = new Scene;
}

void Game::run() {
	while (true) {
		gameCycle();
		reset();
	}
}