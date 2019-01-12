#pragma once

#include "GameObject.h"

class Fuel : public GameObject{

private:

public:
	Fuel(float x, float y, ALLEGRO_BITMAP *image);
	void Destroy();
	void Update();
	void Render();
	void Collided(int objectID);
};