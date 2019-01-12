#pragma once

#include "GameObject.h"

class Explosion : public GameObject
{
private:

public:
	Explosion(float x, float y, ALLEGRO_BITMAP *image);
	void Destroy();
	void Update();
	void Render();
};