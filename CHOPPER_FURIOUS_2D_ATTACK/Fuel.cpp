#include "Fuel.h"


Fuel::Fuel(float x, float y, ALLEGRO_BITMAP *image){

	GameObject::Init(x, y, 2, 0, -1, 0, 0, 0);

	GameObject::image = image;
	SetID(FUEL);

}
void Fuel::Destroy(){

	GameObject::Destroy();

}
void Fuel::Update(){

	GameObject::Update();

	if (x <= 0)Collided(BORDER);


}
void Fuel::Render(){

	GameObject::Render();
	al_draw_bitmap(image, x, y, 0);
	al_convert_mask_to_alpha(image, al_map_rgb(255, 255, 255));

}
void Fuel::Collided(int objectID){

	if (objectID != FUEL){
		SetAlive(false);
		
	}
	if (objectID == PLAYER){
		SetAlive(false);
		
	}

}