#pragma once

#include "GameObject.h"

class Level1 : public GameObject
{
private:

public:
	Level1(ALLEGRO_BITMAP *image, float velX);
	void Destroy();
	void Update();
	void Render();
	void Collided(int objectID);

};