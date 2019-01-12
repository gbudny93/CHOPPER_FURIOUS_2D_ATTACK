#include "Rocket.h"

Rocket::Rocket(float x, float y, void(*ScorePoint)(void),int objectID,int direction,ALLEGRO_BITMAP *image)
{
	GameObject::Init(x, y, 10, 0, direction, 0, 0, 0);

	SetID(objectID);

	Rocket::ScorePoint = ScorePoint;
	GameObject::image = image;
}
Rocket::Rocket(float x, float y, void(*ScorePoint)(void), int objectID, int dirX, int dirY, ALLEGRO_BITMAP *image){

	GameObject::Init(x, y, 10, 10, -1, -1, 0, 0);

	SetID(objectID);

	Rocket::ScorePoint = ScorePoint;

	GameObject::image = image;

}
void Rocket::Destroy()
{
	GameObject::Destroy();
}

void Rocket::Update()
{
	GameObject::Update();

	if (x > WIDTH)
		Collided(BORDER);
}

void Rocket::Render()
{
	al_draw_bitmap(image, x, y, 0);
	al_convert_mask_to_alpha(image, al_map_rgb(255, 255, 255));

}

void Rocket::Collided(int objectID)
{
	if (objectID == ENEMY || objectID == BORDER)
		SetAlive(false);

	if (objectID == ENEMY)
		ScorePoint();

}