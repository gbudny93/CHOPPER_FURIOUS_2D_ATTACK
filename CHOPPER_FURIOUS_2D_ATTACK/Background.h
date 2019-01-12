#pragma once

#include "GameObject.h"

//CLASS THAT CONSISTS ALL PARAMETRS OF BACKGROUND 
class Background : public GameObject
{
private:

public:

	Background(ALLEGRO_BITMAP *image, float velX);//CONSTRUCTOR THAT ALLOCATES BACKGROUND IMAGE AND ITS SPEED 
	void Destroy();//METHOD THAT DESTROYS OBJECT
	void Update();//METHOD THAT UPDATES OBJECT'S COORDINATES
	void Render();//METHOD THAT RENDER GRAPHICS
};