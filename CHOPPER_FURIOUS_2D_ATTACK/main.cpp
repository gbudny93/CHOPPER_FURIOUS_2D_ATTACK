/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@Budny Grzegorz & Bartosz Szafarz@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@CP III Project@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
//LIBRARIES
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include <list>
#define FPS 60
//HEADER FILES
#include "Globals.h" //GLOBAL VARIABLES
#include "GameObject.h" //GAME ENGINE ALL FUNCTIONALITY IS HIDDEN HERE
#include "Chopper.h"	//PLAYER CHOPPER 
#include "Rocket.h"		//ROCKET
#include "EnemyChopper.h"	//ENEMY CHOPPERS
#include "Explosion.h"		//EXPLOSION
#include "Background.h"		//BACKGROUND
#include "Level1.h"			//LEVEL1
#include "Fuel.h"			//FUEL
#include "Life.h"			//LIFE
#include "Tank.h"			//ENEMY TANKS
#include "Bomb.h"			//BOMB
#include "HighScores.cpp"	//HIGHSCORES TABLE

//KEYBOARD
bool keys[] = { false, false, false, false, false, false, false,false };
enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE, ENTER, CTRL,P };

//GLOBALS
Chopper *chopper;
EnemyChopper *enemyChopper;
Fuel *fuel;
Life *life;
Tank *tank;
Level1 *level1;
HighScores scores;
//LIST OF OBJECTS
std::list<GameObject *> objects;
std::list<GameObject *>::iterator iter;
std::list<GameObject *>::iterator iter2;
//ALLEGRO GLOBALS
ALLEGRO_SAMPLE_INSTANCE *mainsong;
ALLEGRO_SAMPLE *song = NULL;
ALLEGRO_FONT *font;
ALLEGRO_FONT *font24;
ALLEGRO_FONT *font36;

int count1 = 0;
int count2 = 0;
bool done = false;
//PROTOTYPES
void __cdecl TakeLife();
void __cdecl ScorePoint();
void ChangeState(int &state, int newState);

int main(int argc, char **argv)
{
	bool render = false;
	int frames = 0;
	
	//project variables
	chopper = new Chopper();
	int state = -1;

	//ALLEGRO VARIABLES
	ALLEGRO_BITMAP *chopperImg = NULL;
	ALLEGRO_BITMAP *enemyChopperImg = NULL;
	ALLEGRO_BITMAP *expImg = NULL;
	ALLEGRO_BITMAP *bgImg = NULL;
	ALLEGRO_BITMAP *mgImg = NULL;
	ALLEGRO_BITMAP *fgImg = NULL;
	ALLEGRO_BITMAP *titleImage = NULL;
	ALLEGRO_BITMAP *lostImage = NULL;
	ALLEGRO_BITMAP *fuelImg = NULL;
	ALLEGRO_BITMAP *rocketImg = NULL;
	ALLEGRO_BITMAP *enemyRocketImg = NULL;
	ALLEGRO_BITMAP *lifeImg = NULL;
	ALLEGRO_BITMAP *tankImg = NULL;
	ALLEGRO_BITMAP *tankRocketImg = NULL;
	ALLEGRO_BITMAP *bombImg = NULL;
	ALLEGRO_BITMAP *how1 = NULL;
	ALLEGRO_BITMAP *how2 = NULL;
	ALLEGRO_BITMAP *how3 = NULL;
	ALLEGRO_SAMPLE *shoot = NULL;
	ALLEGRO_SAMPLE *exp = NULL;
	ALLEGRO_SAMPLE *pick = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	
	al_init();	//PROJECT INITIALIZATION
	display = al_create_display(WIDTH, HEIGHT);//CREATE DISPLAY
	al_set_window_title(display, "CHOPPER FURIOUS 2D ATTACK BY GRZEGORZ BUDNY AND BARTOSZ SZAFARZ");
	//THROWING EXCEPTIONS
	try{
		if (!al_init())throw "Initialization error occured! Try to turn off and on application";
		if (!display) throw "Display error occured! Try to turn off and on application!";
	}
	catch(char const *message ){
		al_show_native_message_box(al_get_current_display(), "ERROR!", "Oh no! an error occured", message, NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	//ADDONS INITIALIZATION
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();

	//project inti
	//FONTS
	font = al_load_font("PressStart2P.ttf", 12, 0);
	font24 = al_load_font("PressStart2P.ttf", 24, 0);
	font36 = al_load_font("PressStart2P.ttf", 36, 0);
	
	al_reserve_samples(15);
	//LOADING IMAGES
	bgImg = al_load_bitmap("Textures/mg.png");
	mgImg = al_load_bitmap("Textures/Level.png");
	fuelImg = al_load_bitmap("Textures/fuel.png");
	chopperImg = al_load_bitmap("Textures/chopper1.gif");
	al_convert_mask_to_alpha(chopperImg, al_map_rgb(255, 0, 255));
	enemyChopperImg = al_load_bitmap("Textures/enemy.gif");
	expImg = al_load_bitmap("Textures/explosion.png");
	rocketImg = al_load_bitmap("Textures/shell.gif");
	enemyRocketImg = al_load_bitmap("Textures/shell_enemy.gif");
	lifeImg = al_load_bitmap("Textures/live.gif");
	tankImg = al_load_bitmap("Textures/Tank.png");
	tankRocketImg = al_load_bitmap("Textures/Tank_shell.png");
	bombImg = al_load_bitmap("Textures/shell_bomb.png");
	how1 = al_load_bitmap("Textures/HowTo_1.png");
	how2 = al_load_bitmap("Textures/HowTo_2.png");
	how3 = al_load_bitmap("Textures/HowTo_3.png");
	//SOUNDS
	shoot = al_load_sample("Sounds/Shoot1.wav");
	exp = al_load_sample("Sounds/Explosion.wav");
	pick = al_load_sample("Sounds/Pickup.wav");
	song = al_load_sample("Sounds/song.wav");
	mainsong = al_create_sample_instance(song);
	al_set_sample_instance_playmode(mainsong, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(mainsong, al_get_default_mixer());
	
	//BACKGROUND OBJECTS
	Background *bg = new Background(bgImg, 1);
	objects.push_back(bg);
	Background *mg = new Background(mgImg, 1);
	objects.push_back(mg);

	chopper->Init(chopperImg);//PLAYER'S CHOPPER INITIALIZATION
	objects.push_back(chopper);

	ChangeState(state, TITLE);//SET DEFAULT STATE AS MAIN MENU
	
	srand(time(NULL));
	
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_start_timer(timer);
	
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		//MAIN MENU
		if (state == TITLE){

			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(font24, al_map_rgb(255, 10, 10), WIDTH/10, 50, 0, "CHOPPER FURIOUS 2D ATTACK !");
			switch (count1){
			case 0:{
				al_draw_text(font36, al_map_rgb(255, 0, 0), 300, 200, 0, "PLAY!");
				al_draw_text(font36, al_map_rgb(255, 255, 255), 180, 250, 0, "HOW TO PLAY?");
				al_draw_text(font36, al_map_rgb(255, 255, 255), 200, 300, 0, "HIGH SCORES");
				al_draw_text(font36, al_map_rgb(255, 255, 255), 310, 350, 0, "EXIT");
				break;
			}
			case 1:{
				al_draw_text(font36, al_map_rgb(255, 255, 255), 300, 200, 0, "PLAY!");
				al_draw_text(font36, al_map_rgb(255, 0, 0), 180, 250, 0, "HOW TO PLAY?");
				al_draw_text(font36, al_map_rgb(255, 255, 255), 200, 300, 0, "HIGH SCORES");
				al_draw_text(font36, al_map_rgb(255, 255, 255), 310, 350, 0, "EXIT");
				break;
			}
			case 2:{
				al_draw_text(font36, al_map_rgb(255, 255, 255), 300, 200, 0, "PLAY!");
				al_draw_text(font36, al_map_rgb(255, 255, 255), 180, 250, 0, "HOW TO PLAY?");
				al_draw_text(font36, al_map_rgb(255, 0, 0), 200, 300, 0, "HIGH SCORES");
				al_draw_text(font36, al_map_rgb(255, 255, 255), 310, 350, 0, "EXIT");
				break;
			}
			case 3:{
				al_draw_text(font36, al_map_rgb(255, 255, 255), 300, 200, 0, "PLAY!");
				al_draw_text(font36, al_map_rgb(255, 255, 255), 180, 250, 0, "HOW TO PLAY?");
				al_draw_text(font36, al_map_rgb(255, 255, 255), 200, 300, 0, "HIGH SCORES");
				al_draw_text(font36, al_map_rgb(255, 0, 0), 310, 350, 0, "EXIT");
				break;
			}
			default:{
				al_show_native_message_box(al_get_current_display(), "ERROR!", "Oh no! An error occured!", "Try to restart the game!", NULL, ALLEGRO_MESSAGEBOX_WARN);
				break;
			}
			}
		}
		//HOW TO PLAY SECTION
		else if (state == HOWTO){

			switch (count2){
			case 0:{

				al_draw_bitmap(how1, 0, 0, 0);
				break;
			}
			case 1:{

				al_draw_bitmap(how2, 0, 0, 0);
				break;
			}
			case 2:{
				al_draw_bitmap(how3, 0, 0, 0);
				break;
			}

			}
		}
		//GAME PAUSE
		else if (state == PAUSE)al_stop_timer(timer);
		//GAME PLAY STATE
		else if (state == PLAYING)al_start_timer(timer);
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				ChangeState(state, TITLE);
				al_stop_sample_instance(mainsong);
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				if (count2 == 0)break;
				count2--;
				if (state == HOWTO)al_play_sample(pick, 0.5, 1, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				if (count2 == 2)break;
				count2++;
				if (state == HOWTO)al_play_sample(pick, 0.5, 1, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				if (count1 == 0)break;
				count1--;
				if(state==TITLE)al_play_sample(pick, 0.5, 1, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				if (count1 == 3)break;
				count1++;
				if (state == TITLE)al_play_sample(pick, 0.5, 1, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				break;
			case ALLEGRO_KEY_P:
				keys[P] = true;
				if (state == PLAYING)ChangeState(state, PAUSE);
				if (state == PAUSE)ChangeState(state, PLAYING);
				break;
			case ALLEGRO_KEY_ENTER:
				keys[ENTER] = true;
				if (state == TITLE && count1 == 0)
					ChangeState(state, PLAYING);
				if (state == TITLE && count1 == 2)
					ChangeState(state, SCORES);
				if (state == TITLE && count1 == 3)
					ChangeState(state, EXIT);
				if (state == TITLE && count1 == 1)
					ChangeState(state, HOWTO);
				break;
			case ALLEGRO_KEY_LCTRL:
				keys[CTRL] = true;
				if (state == PLAYING){
					Bomb *bomb = new Bomb(chopper->GetX() + 17, chopper->GetY() + 15, &ScorePoint, ROCKET, 1, bombImg);
					objects.push_back(bomb);
					al_play_sample(shoot, 0.5, 1, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				 if (state == PLAYING)
				{
					Rocket *rocket = new Rocket(chopper->GetX() + 17, chopper->GetY()+15, &ScorePoint,ROCKET,1,rocketImg);
					objects.push_back(rocket);
					al_play_sample(shoot, 0.5, 1, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				else if (state == LOST)
					ChangeState(state, TITLE);
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_P:
				keys[P] = false;
				break;
			case ALLEGRO_KEY_ENTER:
				keys[ENTER] = false;
				break;
			case ALLEGRO_KEY_LCTRL:
				keys[CTRL] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}
		//GAME UPDATE UNDER TIMER
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;
			chopper->LoseFuel();
			if (state == PLAYING)
			{
				if (keys[UP])
					chopper->MoveUp();
				else if (keys[DOWN])
					chopper->MoveDown();
				else
					chopper->ResetAnimation(1);

				if (keys[LEFT])
					chopper->MoveLeft();
				else if (keys[RIGHT])
					chopper->MoveRight();
				else
					chopper->ResetAnimation(0);
				//RANDOM GENERATION OF ENEMIES CHOPPERS
				if (rand() % 50 == 0)
				{
					enemyChopper = new EnemyChopper(WIDTH, 30 + rand() % (HEIGHT - 250), enemyChopperImg, &TakeLife);
					objects.push_back(enemyChopper);
				}
				//RANDOM GENERATION OF ENEMIES ROCKETS
				if (enemyChopper){
					if (rand() % 200 == 0){
						Rocket *enemyRocket = new Rocket(enemyChopper->GetX() + 17, enemyChopper->GetY() + 15, &ScorePoint, ENEMY, -1, enemyRocketImg);
						objects.push_back(enemyRocket);
						al_play_sample(shoot, 0.5, 1, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
				}
				//RANDOM GEBERATION OF FUEL BONUS
				if (rand() % 300 == 0){
					fuel = new Fuel(WIDTH, 30 + rand() % (HEIGHT - 250), fuelImg);
					objects.push_back(fuel);
				}
				//RANDOM GEBERATION OF ENEMIES TANKS
				if (rand() % 300 == 0){
						tank = new Tank(WIDTH, 424, tankImg);
						objects.push_back(tank);
				}
				//RANDOM GENERATION OF TANKS ROCKETS
				if (tank){
					if (rand() %  300== 0){
						Rocket *tankRocket = new Rocket(tank->GetX(), tank->GetY(), &ScorePoint, ENEMY, -1, -1, tankRocketImg);
						objects.push_back(tankRocket);
					}
				}
				//RANDOM GENERATION OF BONUS LIFE
				if (rand() % 600 == 0){
					life = new Life(WIDTH, 30 + rand() % (HEIGHT - 250), lifeImg);
					objects.push_back(life);
				}
				//GAME OVER CONDITION
				if (chopper->GetFuel() <= 0)ChangeState(state,LOST);
				//UPDATING ALL OBJECTS IN A LIST
				for (iter = objects.begin(); iter != objects.end(); ++iter)
					(*iter)->Update();
				//COLLISION DETECTION AND EXECUTION
				for (iter = objects.begin(); iter != objects.end(); ++iter)
				{
					if (!(*iter)->Collidable()) continue;
					for (iter2 = iter; iter2 != objects.end(); ++iter2)
					{
						if (!(*iter2)->Collidable()) continue;
						if ((*iter)->GetID() == (*iter2)->GetID()) continue;
						if ((*iter)->CheckCollisions((*iter2)))
						{
							(*iter)->Collided((*iter2)->GetID());
							(*iter2)->Collided((*iter)->GetID());
							if ((*iter)->GetID() == ENEMY || (*iter2)->GetID()==ENEMY){
								Explosion *explosion = new Explosion(((*iter)->GetX() + (*iter2)->GetX()) / 2,
									((*iter)->GetY() + (*iter2)->GetY()) / 2, expImg);
									objects.push_back(explosion);
									al_play_sample(exp, 0.5, 1, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
							}
							else if ((*iter)->GetID() == FUEL || (*iter2)->GetID() == FUEL){
								chopper->AddFuel();
								al_play_sample(pick, 0.5, 1, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
							}
							else if ((*iter)->GetID() == LIFE || (*iter2)->GetID() == LIFE){
								chopper->GetLife();
								al_play_sample(pick, 0.5, 1, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
							}
						}
					}
				}
				if (chopper->GetLives() <= 0)
					ChangeState(state, LOST);
			}
			//DESTROYING OBJECTS IN A LIST
			for (iter = objects.begin(); iter != objects.end();)
			{
				if (!(*iter)->GetAlive())
				{
					delete (*iter);
					iter = objects.erase(iter);
				}
				else
					iter++;
			}
		}
		//GRAPHICS RENDERING
		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;
			if (state == PLAYING)
			{
				al_draw_textf(font, al_map_rgb(0, 0, 0), 5, 5, 0, "Lives: %i Score: %i  Fuel:%1.f ",
					chopper->GetLives(), chopper->GetScore(),chopper->GetFuel());
				for (iter = objects.begin(); iter != objects.end(); ++iter)
					(*iter)->Render();
			}
			else if (state == SCORES){
				scores.CreateVectorOfScores();
				scores.SortAndReverceScoresVector();
				scores.PrintScores(font);
			}
			else if (state == LOST)
			{
				al_draw_text(font36, al_map_rgb(0, 0, 0), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "GAME OVER");	
			}
			al_flip_display();
			al_clear_to_color(al_map_rgb(153, 255, 255));
		}
	}
	//REMOVING ALL OBJECTS IN THE LIST
	for (iter = objects.begin(); iter != objects.end();)
	{
		(*iter)->Destroy();
		delete (*iter);
		iter = objects.erase(iter);
	}
	//DESTROYING ALLEGRO VARIABLES
	al_destroy_bitmap(enemyChopperImg);
	al_destroy_bitmap(chopperImg);
	al_destroy_bitmap(expImg);
	al_destroy_bitmap(bgImg);
	al_destroy_bitmap(mgImg);
	al_destroy_bitmap(fgImg);
	al_destroy_bitmap(rocketImg);
	al_destroy_bitmap(enemyRocketImg);
	al_destroy_bitmap(titleImage);
	al_destroy_bitmap(lostImage);
	al_destroy_sample(shoot);
	al_destroy_sample(exp);
	al_destroy_sample(pick);
	al_destroy_sample_instance(mainsong);
	al_destroy_font(font);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;
}
void __cdecl TakeLife()
{
	chopper->LoseLife();
}

void __cdecl ScorePoint()
{
	chopper->AddPoint();
}
//CHANGE STATE FUNCTION - PERFORM PROPER ACTIONS AFTER CHANGE STATE
void ChangeState(int &state, int newState)
{
	if (state == TITLE)
	{
	}
	else if (state == PLAYING)
	{
		for (iter = objects.begin(); iter != objects.end(); ++iter)
		{
			if ((*iter)->GetID() != PLAYER && (*iter)->GetID() != MISC)
				(*iter)->SetAlive(false);
		}
	}
	else if (state == HOWTO){
	}
	else if (state == PAUSE){
	}
	else if (state == SCORES){
	
	}
	else if (state == LOST)
	{
	}
	else if (state == EXIT){
	}
	state = newState;
	if (state == TITLE)
	{
	}
	else if (state == PLAYING)
	{
		chopper->petrol = 1000;
		chopper->Init();
		chopper->AddFuel();
		al_play_sample_instance(mainsong);
	}
	else if (state == LOST)
	{
		scores.AddScore(chopper->GetScore());
		al_stop_sample_instance(mainsong);
	}
	else if (state == PAUSE){
	}
	else if (state == HOWTO){
	}
	else if (state == SCORES){
	}
	else if(state == EXIT){
		done = true;
	}
}