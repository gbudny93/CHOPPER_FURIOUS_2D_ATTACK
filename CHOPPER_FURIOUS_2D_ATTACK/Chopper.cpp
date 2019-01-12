#include "Chopper.h"

Chopper::Chopper()
{}

void Chopper::Destroy()
{
	GameObject::Destroy();
}

void Chopper::Init(ALLEGRO_BITMAP *image)
{
	GameObject::Init(20, 200, 6, 6, 0, 0, 10, 12);
	

	SetID(PLAYER);
	SetAlive(true);

	lives = 3;
	score = 0;

	maxFrame = 3;
	curFrame = 0;
	frameWidth = 46;
	frameHeight = 41;
	animationColumns = 3;
	animationDirection = 1;

	animationRow = 1;

	if (image != NULL)
		Chopper::image = image;
}


void Chopper::Update()
{
	GameObject::Update();
	if (x < 0)
		x = 0;
	else if (x > WIDTH)
		x = WIDTH;

	if (y < 0)
		y = 0;
	else if (y > 424)
		y = 424;
}

void Chopper::Render()
{
	GameObject::Render();

	//int fx = (curFrame % animationColumns) * frameWidth;
	//int fy = animationRow * frameHeight;

	//al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight,
	//x - frameWidth / 2, y - frameHeight / 2, 0);
	al_draw_bitmap(image, x, y, 0);
}

void Chopper::MoveUp()
{
	animationRow = 0;
	dirY = -1;
}
void Chopper::MoveDown()
{
	animationRow = 2;
	dirY = 1;
}
void Chopper::MoveLeft()
{
	curFrame = 2;
	dirX = -1;
}
void Chopper::MoveRight()
{
	curFrame = 1;
	dirX = 1;
}

void Chopper::ResetAnimation(int position)
{
	if (position == 1)
	{
		animationRow = 1;
		dirY = 0;
	}
	else
	{
		curFrame = 0;
		dirX = 0;
	}
}

void Chopper::Collided(int objectID)
{
	if (objectID == ENEMY)
		lives--;
	
}