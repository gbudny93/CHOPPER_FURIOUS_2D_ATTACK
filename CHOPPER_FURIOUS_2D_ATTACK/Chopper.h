#pragma once

#include "GameObject.h"

class Chopper : public GameObject
{
private:

	int lives;//CHOPPER PLAYER'S LIVES
	int score;//POINTS OBTAINED BY PLAYER
	int animationRow;
	
public:

	float petrol = 1000;//INITIAL AMOUNT OF PLAYER'S CHOPPER PETROL
	Chopper();//DEFAULT CONSTRUCTOR
	void Destroy();//METHOD THAT DESTROYS OBJECT

	void Init(ALLEGRO_BITMAP *image = NULL);//INITIALIZING METHOD THAT 
	void Update();//METHOD THAT UPDATES OBJECT COORDINATES
	void Render();//METHOD THAT RENDER GRAPHICS
	void MoveUp();//METHOD THAT MOVES UP PLAYER'S CHOPPER
	void MoveDown();//METHOD THAT MOVES DOWN PLAYER'S CHOPPER
	void MoveLeft();//METHOD THART MOVES LEFT PLAYER'S CHOPPER
	void MoveRight();//METHOD THAT MOVES RIGHT PLAYER'S CHEOPPER

	void ResetAnimation(int position);

	int GetLives() { return lives; }//METHOD THAT RETURNS NUMBER OF PLAYERS LIVES
	int GetScore() { return score; }//METHOD THAT RETURNS PLAYER'S SCORE
	float GetFuel() { return petrol; }//METHOD THAT RETURNS AMOUNT OF PLAYER'S FUEL

	void LoseLife() { lives--; }//METHOD THAT SUBSTRUCT PLAYER'S LIVES
	void GetLife(){ lives++; }//METHOD THAT ADD PLAYER LIVE
	void AddPoint() { score++; }//METHOD THAT ADD PLAYER SCORE
	void AddFuel() { petrol +=500; }//METHOD THAT ADDS PLAYER'S PETROL
	void LoseFuel(){ petrol -= 0.5; }//METHOD THAT REDUCE FUEL WITH RESPECT TO FLYING TIME
	
	void Collided(int objectID);//METHOD THAT MAKE COLLISION WITH OTHER OBJECTS
};