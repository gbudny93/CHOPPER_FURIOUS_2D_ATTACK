#pragma once

#include "GameObject.h"

class Tank : public GameObject{

private:
	//void(*TakeLife)(void);

public:
	Tank(float x, float y, ALLEGRO_BITMAP *image);
	void Destroy();
	void Update();
	void Render();

	void Collided(int objectID);
};