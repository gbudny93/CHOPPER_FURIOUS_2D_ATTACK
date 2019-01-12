#pragma once

#include "GameObject.h"

class Bomb : public GameObject
{

private:
	void(*ScorePoint)(void);


public:

	Bomb(float x, float y, void(*ScorePoint)(void), int objectID, int direction, ALLEGRO_BITMAP *image);//CONSTRUCTOR THAT INITIALIZE BOMB OBJECT ITS COORDINATES ID DIRECTION AND IMAGE
	void Destroy();//METHOD THAT DESTROYS OBJECTS
	void Update();//METHOD THAT UPDATES OBJECT'S COORDINATES
	void Render();//METHOD THAT RENDER GRAPHICS
	void Collided(int objectID);//METHOD THAT DEFINES COLLISION
};