#pragma once

#include "GameObject.h"

class Rocket : public GameObject
{
private:
	void(*ScorePoint)(void);
	

public:
	Rocket(float x, float y, void(*ScorePoint)(void),int objectID,int direction,ALLEGRO_BITMAP *image);
	Rocket(float x, float y, void(*ScorePoint)(void), int objectID, int dirX, int dirY, ALLEGRO_BITMAP *image);
	void Destroy();
	void Update();
	void Render();

	void Collided(int objectID);
};