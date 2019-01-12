#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <allegro5\allegro_font.h>

using namespace  std;

class HighScores
{
	std::vector<int> _scores;
public:

	HighScores(){
	
	}
	void CreateVectorOfScores()
	{
		_scores.clear();
		_scores.shrink_to_fit();
		std::ifstream file;
		int score;

		file.open("HighScores.txt");
		while (file.good())
		{
			file >> score;
			_scores.push_back(score);
		}
		file.close();
	}

	void PrintScores(ALLEGRO_FONT *font)
	{
		al_clear_to_color(al_map_rgb(0,0,0));
		al_draw_text(font, al_map_rgb(255, 0, 0), 300, 20, 0, "HIGH SCORES TABLE");
		int counter = 1;
		int y = 100;
		for (vector<int>::iterator i = _scores.begin(); counter <11; ++i, counter++, y+=50){
			//cout << setw(4) << counter << ". " << *i << endl;
			al_draw_textf(font, al_map_rgb(255, 0, 0), 370, y, 0, "%2d. %d", counter, *i);

		}
	}

	void SortAndReverceScoresVector()
	{
		sort(_scores.begin(), _scores.end());
		reverse(_scores.begin(), _scores.end());
	}

	void AddScore(int score)
	{
		ofstream file;
		file.open("HighScores.txt", ios::app);
		file << endl;
		file << score;
		file.close();
	}
};

