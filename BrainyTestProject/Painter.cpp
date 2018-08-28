#include "Painter.h"



Painter::Painter()
{
	window = GetConsoleWindow();
	holst = GetDC(window); 

	playerBrush = CreateSolidBrush(RGB(0, 0, 0));
	playerPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));

	enemyBrush = CreateSolidBrush(RGB(0, 0, 0));
	enemyPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));

	wallBrush = CreateSolidBrush(RGB(0, 0, 0));
	wallPen = CreatePen(PS_SOLID, 3, RGB(255, 150, 150));

	bulletBrush = CreateSolidBrush(RGB(71, 74, 81));
	bulletPen = CreatePen(PS_SOLID, 1, RGB(71, 74, 81));

	trajectoryPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 255));

	SetBkColor(holst, RGB(0, 0, 0));
}

Painter::~Painter()
{
	DeletePen(playerPen);
	DeleteBrush(playerBrush);
	
	DeletePen(enemyPen);
	DeleteBrush(enemyBrush);

	DeletePen(wallPen);
	DeleteBrush(wallBrush);

	ReleaseDC(window, holst);
}

void Painter::drawAll(const Scene & S, const unsigned fragsPerPlayer, const unsigned fragsPerEnemy) {
	
	clearScreen();

	if(S.isDrawTrajectory())
		for (auto bullet : S.bullets())
			drawTrajectory(S, bullet);
	
	for (auto a : S.walls())
		drawWall(a);

	drawUnit(S, S.enemy(), enemyBrush, enemyPen);
	drawUnit(S, S.player(), playerBrush, playerPen);

	for (auto bullet : S.bullets())
		drawBullet(S, bullet);

	drawCheck(fragsPerPlayer, fragsPerEnemy);
}

void Painter::drawUnit(const Scene & mainScene, const Unit & unit, const HBRUSH & brush, const HPEN & pen) const {
	Point position = unit.position();
	Vector2D direction = unit.direction();
	Point extremePoint = createShiftedPoint(position, direction, static_cast<int>(1.5 * mainScene.unitsRadius()));
	POINT weapon[2] = { {int(position.x() + 0.5), int(position.y() + 0.5)}, {int(extremePoint.x() + 0.5), int(extremePoint.y() + 0.5)} };
	
	SelectPen(holst, pen);
	SelectBrush(holst, brush);
	Polyline(holst, weapon, 2);
	Ellipse(holst, position.x() - mainScene.unitsRadius(), position.y() - mainScene.unitsRadius(),
		position.x() + mainScene.unitsRadius(), position.y() + mainScene.unitsRadius());
}

void Painter::drawWall(const Wall & wall) const {
	POINT verticles[4];
	for (int i = 0; i < 4; i++)
		verticles[i] = { int(wall.vertex(i).x() + 0.5), int(wall.vertex(i).y() + 0.5) };

	SelectPen(holst, wallPen);
	SelectBrush(holst, wallBrush);
	Polygon(holst, verticles, 4);
}

void Painter::drawBullet(const Scene & mainScene, const Bullet & bullet) const {
	Point position = bullet.position();

	SelectPen(holst, bulletPen);
	SelectBrush(holst, bulletBrush);
	Ellipse(holst, position.x() - mainScene.bulletSize(), position.y() - mainScene.bulletSize(),
		position.x() + mainScene.bulletSize(), position.y() + mainScene.bulletSize());
}

void Painter::drawTrajectory(const Scene & mainScene, const Bullet & bullet) const {
	Point position = bullet.position();
	const int countPoints = bullet.trajectory().size() + 1;
	POINT * points = new POINT[countPoints];

	for (int i = 0; i < countPoints - 1; i++) {
		points[i].x = static_cast<LONG>(bullet.trajectory()[i].x());
		points[i].y = static_cast<LONG>(bullet.trajectory()[i].y());
	}

	points[countPoints - 1].x = static_cast<LONG>(bullet.position().x());
	points[countPoints - 1].y = static_cast<LONG>(bullet.position().y());

	SelectPen(holst, trajectoryPen);

	Polyline(holst, points, countPoints);

	delete[] points;
}

void Painter::clearScreen() {
	RECT winSize;
	GetClientRect(window, &winSize);

	HPEN pen = CreatePen(PS_SOLID, 1, GetBkColor(holst));
	HPEN oldPen = SelectPen(holst, pen);

	HBRUSH brush = CreateSolidBrush(GetBkColor(holst));
	HBRUSH oldBrush = SelectBrush(holst, brush);

	Rectangle(holst, 0, 0, winSize.right, winSize.bottom);

	rightBottom.setX(static_cast<float>(winSize.right));
	rightBottom.setY(static_cast<float>(winSize.bottom));

	SelectPen(holst, oldPen);
	SelectBrush(holst, oldBrush);
	DeletePen(pen);
	DeleteBrush(brush);
}

Point Painter::getRightBottomPoint() const {
	return rightBottom;
}

void Painter::drawCheck(const unsigned fragsPerPlayer, const unsigned fragsPerEnemy) const {
	string message = "Player " + std::to_string(fragsPerPlayer) + " : Enemy " + std::to_string(fragsPerEnemy);

	SetTextColor(holst, RGB(255,0,0));

	TextOut (holst, 500, 100, message.c_str(), message.size() + 1);
}