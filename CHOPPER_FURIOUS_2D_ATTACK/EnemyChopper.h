#pragma once

#include "GameObject.h"

class EnemyChopper : public GameObject
{
private:
	void(*TakeLife)(void);

public:
	EnemyChopper(float x, float y, ALLEGRO_BITMAP *image, void(*TakeLife)(void));//CONSTRUCTOR THAT CREATES CHOPPER ENEMIES
	void Destroy();
	void Update();
	void Render();
	void Collided(int objectID);
};