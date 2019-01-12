#pragma once

#include "GameObject.h"

class Life : public GameObject{

private:

public:

	Life(float x, float y, ALLEGRO_BITMAP *image);
	void Destroy();
	void Update();
	void Render();
	void Collided(int objectID);
};