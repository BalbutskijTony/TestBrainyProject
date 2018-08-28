#include "Scene.h"


Scene::Scene() : m_player(Point(100, 200), Vector2D(0, -1)), m_enemy(Point(300, 100), Vector2D(-1, 0)) 
{
	m_walls.emplace_back(Point(150, 280), Point(150, 150), Point(200, 150), Point(200, 280));
	m_walls.emplace_back(Point(50, 180), Point(50, 150), Point(100, 150), Point(100, 180));
	m_walls.emplace_back(Point(50, 80), Point(50, 60), Point(200, 60), Point(200, 80));
}

void Scene::m_executeAllCommands(Unit & who, queue<int> & commands) {
	int currentCommand;
	while (!commands.empty())
	{
		currentCommand = commands.front();
		commands.pop();
		m_executeCommand(who, currentCommand);
	}
}

void Scene::m_executeCommand(Unit & who, int command) {
	switch (command)
	{
	case STEP_RIGHT_COMMAND:
		m_changePos(who, createRotated(who.direction(), 90));
		break;
	case STEP_LEFT_COMMAND:
		m_changePos(who, createRotated(who.direction(), -90));
		break;
	case STEP_BACK_COMMAND:
		m_changePos(who, createRotated(who.direction(), 180));
		break;
	case STEP_FORWARD_COMMAND:
		m_changePos(who, createRotated(who.direction(), 0));
		break;
	case TURN_RIGHT_COMMAND:
		who.setDirection(createRotated(who.direction(), static_cast<float>(m_unitTurnSize)));
		break;
	case TURN_LEFT_COMMAND:
		who.setDirection(createRotated(who.direction(), static_cast<float>(-int(m_unitTurnSize))));
		break;
	case SHOTING_COMMAND: // TODO заименовать магическое число
		m_bullets.emplace_back(who.position() + 3 * who.direction() * static_cast<float>(m_unitRadius), who.direction());
		break;
	case ON_OFF_DEBUG:
		m_isPaintTrajectory = !m_isPaintTrajectory;
		break;
	default:
		break;
	}
}

void Scene::m_moveBullets() {
	for (size_t i = 0; i < m_bullets.size(); i++)
		m_changePos(m_bullets[i], m_bullets[i].direction() * static_cast<float>(m_bulletVelocity));
}

void Scene::m_changePos(Unit & who, const Vector2D & direction) {
	Point offsetPoint = who.position() + direction * static_cast<float>(m_unitStepSize);

	for (auto wall : m_walls)
	{
		// TODO ѕеренести услови€ в булевские переменные. ѕример: bool is... = wall.minX() - m_unitRadius <= offsetPoint.x();
		if (wall.minX() - m_unitRadius <= offsetPoint.x() && wall.maxX() + m_unitRadius >= offsetPoint.x() &&
			wall.minY() - m_unitRadius <= offsetPoint.y() && wall.maxY() + m_unitRadius >= offsetPoint.y())
			return;
	}
		
	who.setPosition(offsetPoint);
}

void Scene::m_changePos(Bullet & what, const Vector2D & path) {
	vector<std::pair<Point, Vector2D>> intersectionPoints;
	Point oldPos = what.position();
	Point offsetPoint = oldPos + path;
	Point currentIntersectPoint;
	float pathLenght = norm(path);

	for (auto wall : m_walls)
	{
		for (int i = 0; i < wall.amountVertices(); i++) 
		{
			if (isSegmentsIntersect(oldPos, offsetPoint, wall.vertex(i), wall.vertex(i + 1), currentIntersectPoint))
				intersectionPoints.emplace_back(currentIntersectPoint, wall.getGuide(i));
		}
	}

	if (!intersectionPoints.empty()) 
	{
		using std::sort; using std::pair;

		sort(
			intersectionPoints.begin(), 
			intersectionPoints.end(),
			[oldPos](const pair<Point, Vector2D> & p1, const pair<Point, Vector2D> & p2)
				{ return length(oldPos, p1.first) < length(oldPos, p2.first); }
			);
		

		float predStepSize = length(oldPos, intersectionPoints[0].first);
		Vector2D reflectedVector = what.direction() * (pathLenght - predStepSize);

		bool bulletIsHit = isIntersectCircle(m_player.position(), static_cast<float>(m_unitRadius), oldPos, intersectionPoints[0].first);
		if(bulletIsHit) m_playerDead = true;
			

		bulletIsHit = isIntersectCircle(m_enemy.position(), static_cast<float>(m_unitRadius), oldPos, intersectionPoints[0].first);
		if (bulletIsHit) m_enemyDead = true;
			
		// TODO magic digit
		what.setDirection(scalarProduct(intersectionPoints[0].second, reflectedVector) * 2 * intersectionPoints[0].second - reflectedVector);
		what.addPointTrajectory(intersectionPoints[0].first);
		what.reduceBounds();
		m_changePos(what, what.direction());
	}
	else {
		what.setPosition(offsetPoint);

		bool bulletIsHit = isIntersectCircle(m_player.position(), static_cast<float>(m_unitRadius), oldPos, offsetPoint);
		if (bulletIsHit) m_playerDead = true;


		bulletIsHit = isIntersectCircle(m_enemy.position(), static_cast<float>(m_unitRadius), oldPos, offsetPoint);
		if (bulletIsHit) m_enemyDead = true;
	}
}

void Scene::addPlayerCommand(int command) {
	m_playerCommands.push(command);
}

void Scene::addEnemyCommand(int command) {
	m_enemyCommands.push(command);
}

void Scene::gameTic() {

	m_executeAllCommands(m_player, m_playerCommands);
	m_executeAllCommands(m_enemy, m_enemyCommands);

	m_moveBullets();

	m_deleteIncorrectBullets();

	if (!isInside(m_player.position(), m_minScreen, m_maxScreen)) m_playerDead = true;
	if (!isInside(m_enemy.position(), m_minScreen, m_maxScreen)) m_enemyDead = true;

	sleep_for(milliseconds(50));
}

const Unit & Scene::player() const {
	return m_player;
}

const Unit & Scene::enemy() const {
	return m_enemy;
}

const list<Wall> & Scene::walls() const {
	return m_walls;
}

const vector<Bullet> & Scene::bullets() const {
	return m_bullets;
}

unsigned int Scene::unitsRadius() const {
	return m_unitRadius;
}

unsigned int Scene::bulletSize() const {
	return m_bulletSize;
}

bool Scene::isDrawTrajectory() const {
	return m_isPaintTrajectory;
}

void Scene::setMaxScreen(const Point & p) {
	m_maxScreen = p;
}

void Scene::m_deleteIncorrectBullets() {
	for (auto bullet : m_bullets)

		for (size_t i = 0; i < m_bullets.size(); i++)
			if (!isInside(m_bullets[i].position(), m_minScreen, m_maxScreen) || m_bullets[i].isReboundsImpossible())
				m_bullets.erase(m_bullets.begin() + i);
}

bool Scene::isPlayerDead() const {
	return m_playerDead;
}

bool Scene::isEnemyDead() const {
	return m_enemyDead;
}

int Scene::unitStepSize() const {
	return m_unitStepSize;
}

int Scene::bulletVelocity() const {
	return m_bulletVelocity;
}