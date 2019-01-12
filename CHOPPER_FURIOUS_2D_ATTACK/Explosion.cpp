
#include "Explosion.h"

Explosion::Explosion(float x, float y, ALLEGRO_BITMAP *image)
{
	GameObject::Init(x, y, 0, 0, 0, 0, 0, 0);

	SetID(EXPLOSION);
	SetCollidable(false);

	maxFrame = 31;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 1;
	frameWidth = 128;
	frameHeight = 128;
	animationColumns = 8;
	animationDirection = 1;

	Explosion::image = image;
}

void Explosion::Destroy()
{
	GameObject::Destroy();
}

void Explosion::Update()
{
	GameObject::Update();

	if (++frameCount >= frameDelay)
	{
		curFrame += animationDirection;
		if (curFrame >= maxFrame)
			SetAlive(false);

		frameCount = 0;
	}
}

void Explosion::Render()
{
	GameObject::Render();

	//int fx = (curFrame % animationColumns) * frameWidth;
	//int fy = (curFrame / animationColumns) * frameHeight;

	//al_draw_bitmap_region(image, fx, fy, frameWidth,
	//frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
	al_draw_bitmap(image, x, y, 0);
	al_convert_mask_to_alpha(image, al_map_rgb(255, 255, 255));
}