#include "Bomb.h"

Bomb::Bomb(float x, float y, void(*ScorePoint)(void), int objectID, int direction, ALLEGRO_BITMAP *image)
{
	GameObject::Init(x, y, 0, 8, 0, direction, 0, 0);

	SetID(objectID);

	Bomb::ScorePoint = ScorePoint;
	GameObject::image = image;
}
void Bomb::Destroy()
{
	GameObject::Destroy();
}

void Bomb::Update()
{
	GameObject::Update();

	if (y > 454)
		Collided(BORDER);
}

void Bomb::Render()
{
	al_draw_bitmap(image, x, y, 0);
	al_convert_mask_to_alpha(image, al_map_rgb(255, 255, 255));

}

void Bomb::Collided(int objectID)
{
	if (objectID == ENEMY || objectID == BORDER)
		SetAlive(false);

	if (objectID == ENEMY)
		ScorePoint();

}