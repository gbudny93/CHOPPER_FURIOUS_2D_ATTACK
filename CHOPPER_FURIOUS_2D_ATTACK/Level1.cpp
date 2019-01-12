#include "Level1.h"

Level1::Level1(ALLEGRO_BITMAP *image, float velX)
{
	GameObject::Init(x, y, velX, 0, -1, 0, 0, 0);

	SetID(ENEMY);
	

	Level1::image = image;
	frameWidth = al_get_bitmap_width(image);
}

void Level1::Destroy()
{
	GameObject::Destroy();
}

void Level1::Update()
{
	GameObject::Update();
	//if (x + frameWidth <= 0)
		//x = 0;
}

void Level1::Render()
{
	GameObject::Render();

	al_draw_bitmap(image, x, y, 0);

	if (x + frameWidth < 0)
		Collided(BORDER);
	//al_flip_display();

	//if (x + frameWidth < WIDTH)
		//al_draw_bitmap(image, x + frameWidth, y, 0);
}
void Level1::Collided(int objectID){

	if (objectID == PLAYER)std::cout << "haha";

}