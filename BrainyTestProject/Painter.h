#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h> 
#include <windowsx.h>
#include <conio.h>

#include "Scene.h"

#include <string>
using std::string;

class Painter
{
private:
	HWND window;
	HDC holst;

	HBRUSH playerBrush;
	HPEN playerPen;

	HBRUSH enemyBrush;
	HPEN enemyPen;

	HBRUSH wallBrush;
	HPEN wallPen;

	HBRUSH bulletBrush;
	HPEN bulletPen;

	HPEN trajectoryPen;

	Point rightBottom = Point(1000,1000);

	void clearScreen();

	void drawUnit(const Scene & S, const Unit & U, const HBRUSH & B, const HPEN & P) const;
	void drawWall(const Wall & W) const;
	void drawBullet(const Scene & S, const Bullet & B) const;
	void drawTrajectory(const Scene & S, const Bullet & B) const;
	void drawCheck(const unsigned playerFrags, const unsigned enemyFrags) const;
public:
	void drawAll(const Scene & S, const unsigned playerFrags, const unsigned enemyFrags);

	Point getRightBottomPoint() const;
	Painter();
	~Painter();
};

