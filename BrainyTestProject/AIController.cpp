#include "AIController.h"


AIController::AIController()
{
	m_ticsBeforeShot = m_shotFrequency;
	m_ticsBeforeTurn = m_turnFrequency;
	m_ticsBeforeStep = m_stepFrequency;
}


void AIController::listen(Scene & S) {
	if (!m_dodge(S))
		if (m_areWallsInTheWay(S)) {
			m_moveToPlayer(S);
		} 
		else {
			m_rotateToPlayer(S);
			m_shotToPlayer(S);
		} 

	m_ticsBeforeTurn--;
	m_ticsBeforeStep--;
	m_ticsBeforeShot--;
}

bool AIController::m_areWallsInTheWay(const Scene & S) const {
	Point ourPosition = S.enemy().position();
	Point playerPosition = S.player().position();
	for (auto wall : S.walls())
		for (int i = 0; i < wall.amountVertices(); i++)
		{
			if (isSegmentsIntersect(ourPosition, playerPosition, wall.vertex(i), wall.vertex(i + 1), ourPosition))
				return true;
		}
	return false;
}

void AIController::m_moveToPlayer(Scene & S) {
	if (m_ticsBeforeStep > 0)
		return;
	else 
		m_ticsBeforeStep = m_stepFrequency;
		

	Vector2D relative(S.player().position() - S.enemy().position());
	Vector2D forward = S.enemy().direction() * static_cast<float>(S.unitStepSize());
	Vector2D backward = createRotated(S.enemy().direction(), 180) * static_cast<float>(S.unitStepSize());
	Vector2D left = createRotated(S.enemy().direction(), -90) * static_cast<float>(S.unitStepSize());
	Vector2D right = createRotated(S.enemy().direction(), 90) * static_cast<float>(S.unitStepSize());
	Point tmp;

	vector<std::pair<int, Vector2D>> directions = { { STEP_FORWARD_COMMAND, forward }, { STEP_BACK_COMMAND, backward },
													{ STEP_LEFT_COMMAND, left }, { STEP_RIGHT_COMMAND, right } };
	std::sort(directions.begin(), directions.end(),
		[relative](std::pair<int, Vector2D> & p1, std::pair<int, Vector2D> & p2)
		{ return scalarProduct(relative, p1.second) > scalarProduct(relative, p2.second); } );

	for (auto wall : S.walls())
	{
		if (wall.minX() - S.unitsRadius() <= directions[0].second.x() && wall.maxX() + S.unitsRadius() >= directions[0].second.x() &&
			wall.minY() - S.unitsRadius() <= directions[0].second.y() && wall.maxY() + S.unitsRadius() >= directions[0].second.y())
		{
			S.addEnemyCommand(directions[1].first);
			return;
		}
	}

	S.addEnemyCommand(directions[0].first);
}

void AIController::m_rotateToPlayer(Scene & S) {
	if (m_ticsBeforeTurn > 0)
		return;
	else
		m_ticsBeforeTurn = m_turnFrequency;

	Vector2D relative(S.player().position() - S.enemy().position());
	Vector2D left = createRotated(S.enemy().direction(), -90) * static_cast<float>(S.unitStepSize());
	Vector2D right = createRotated(S.enemy().direction(), 90) * static_cast<float>(S.unitStepSize());

	vector<std::pair<int, Vector2D>> directions = { { TURN_LEFT_COMMAND, left },{ TURN_RIGHT_COMMAND, right } };
	std::sort(directions.begin(), directions.end(),
		[relative](std::pair<int, Vector2D> & p1, std::pair<int, Vector2D> & p2)
	{ return scalarProduct(relative, p1.second) > scalarProduct(relative, p2.second); });

	S.addEnemyCommand(directions[0].first);
}

void AIController::m_shotToPlayer(Scene & S) {
	if (m_ticsBeforeShot <= 0) {
		S.addEnemyCommand(SHOTING_COMMAND);
		m_ticsBeforeShot = m_shotFrequency;
	}	
}

bool AIController::m_dodge(Scene & S) {
	if (m_ticsBeforeStep > 0)
		return false;
		

	Vector2D newDirection(-1,-1);

	for (auto bullet : S.bullets())
	{
		if (isIntersectCircle(S.enemy().position(), static_cast<float>(S.unitsRadius()), bullet.position(),
			bullet.position() + 10 * bullet.direction() * static_cast<float>(S.bulletVelocity())))
			newDirection = createRotated(bullet.direction(), 90);
	}

	if (newDirection == Vector2D(-1, -1))
		return false;

	Vector2D forward = S.enemy().direction() * static_cast<float>(S.unitStepSize());
	Vector2D backward = createRotated(S.enemy().direction(), 180) * static_cast<float>(S.unitStepSize());
	Vector2D left = createRotated(S.enemy().direction(), -90) * static_cast<float>(S.unitStepSize());
	Vector2D right = createRotated(S.enemy().direction(), 90) * static_cast<float>(S.unitStepSize());
	Point tmp;

	vector<std::pair<int, Vector2D>> directions = { { STEP_FORWARD_COMMAND, forward },{ STEP_BACK_COMMAND, backward },
	{ STEP_LEFT_COMMAND, left },{ STEP_RIGHT_COMMAND, right } };
	std::sort(directions.begin(), directions.end(),
		[newDirection](std::pair<int, Vector2D> & p1, std::pair<int, Vector2D> & p2)
	{ return scalarProduct(newDirection, p1.second) > scalarProduct(newDirection, p2.second); });
	
	S.addEnemyCommand(directions[0].first);
	m_ticsBeforeStep = m_stepFrequency;
	return true;
}