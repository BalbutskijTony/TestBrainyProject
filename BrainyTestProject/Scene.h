#pragma once
#pragma region include_standart_libs
#include <queue>
#include <list>
#include <chrono>
#include <thread>
using std::queue;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;
using std::list;
#pragma endregion

#pragma region include_our_libs
#include "Unit.h"
#include "Wall.h"
#include "Bullet.h"
#pragma endregion

#pragma region commands
#define STEP_RIGHT_COMMAND 100
#define STEP_LEFT_COMMAND 97
#define STEP_BACK_COMMAND 115
#define STEP_FORWARD_COMMAND 119

#define TURN_RIGHT_COMMAND 101
#define TURN_LEFT_COMMAND 113

#define SHOTING_COMMAND 32

#define ON_OFF_DEBUG 111
#pragma endregion

class Scene
{
public:
	Scene();
	~Scene() = default;

	void addPlayerCommand(int command);
	void addEnemyCommand(int command);

	void gameTic();

	const Unit & player() const;
	const Unit & enemy() const;
	const list<Wall> & walls() const;
	const vector<Bullet> & bullets() const;
	unsigned int unitsRadius() const;
	unsigned int bulletSize() const;

	void setMaxScreen(const Point & p);

	bool isDrawTrajectory() const;

	bool isPlayerDead() const;
	bool isEnemyDead() const;

	int bulletVelocity() const;
	int unitStepSize() const;
private:
	queue<int> m_playerCommands;
	queue<int> m_enemyCommands;

	Unit m_player;
	Unit m_enemy;

	bool m_playerDead = false;
	bool m_enemyDead = false;

	const unsigned int m_unitRadius = 10;
	const unsigned int m_unitStepSize = 9;
	const unsigned int m_unitTurnSize = 10;
	const unsigned int m_bulletVelocity = 20;
	const unsigned int m_bulletSize = 3;

	bool m_isPaintTrajectory = false;

	list<Wall> m_walls;
	vector<Bullet> m_bullets;

	Point m_minScreen = Point(0,0);
	Point m_maxScreen;

	void m_moveBullets();
	void m_executeAllCommands(Unit & who, queue<int> & commands);
	void m_executeCommand(Unit & who, int command);

	void m_changePos(Unit & who, const Vector2D & direction);
	void m_changePos(Bullet & what, const Vector2D & path);

	void m_deleteIncorrectBullets();
};

