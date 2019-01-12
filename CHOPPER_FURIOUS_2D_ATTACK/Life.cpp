#include "Life.h"


Life::Life(float x, float y, ALLEGRO_BITMAP *image){

	GameObject::Init(x, y, 2, 0, -1, 0, 0, 0);

	GameObject::image = image;
	SetID(LIFE);

}
void Life::Destroy(){

	GameObject::Destroy();

}
void Life::Update(){

	GameObject::Update();

	if (x <= 0)Collided(BORDER);


}
void Life::Render(){

	GameObject::Render();
	al_draw_bitmap(image, x, y, 0);
	al_convert_mask_to_alpha(image, al_map_rgb(255, 255, 255));

}
void Life::Collided(int objectID){

	if (objectID != LIFE){
		SetAlive(false);

	}
	if (objectID == PLAYER){
		SetAlive(false);

	}

}