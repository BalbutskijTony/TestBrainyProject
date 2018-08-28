#pragma once
#include "Scene.h"

class AIController
{
public:
	AIController();
	~AIController() = default;
	void listen(Scene & S);
private:
	bool m_areWallsInTheWay(const Scene & S) const;
	void m_moveToPlayer(Scene & S);
	void m_rotateToPlayer(Scene & S);
	void m_shotToPlayer(Scene & S);
	bool m_dodge(Scene & S);

	const int m_shotFrequency = 10;
	const int m_stepFrequency = 5;
	const int m_turnFrequency = 3;

	int m_ticsBeforeShot;
	int m_ticsBeforeTurn;
	int m_ticsBeforeStep;
};

