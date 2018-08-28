#include "PlayerController.h"


void PlayerController::listenAndTransfer(Scene & scene) {
	while (_kbhit())
	{
		scene.addPlayerCommand(_getch());
	}
}

