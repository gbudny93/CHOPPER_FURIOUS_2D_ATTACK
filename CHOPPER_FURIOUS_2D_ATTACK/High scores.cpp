#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace  std;

class HighScores
{
	std::vector<int> _scores;
public:
	void CreateVectorOfScores()
	{
		_scores.clear();
		_scores.shrink_to_fit();
		std::ifstream file;
		int score;

		file.open("C:/Users/Bartek/Desktop/High scores.txt");
		while (file.good())
		{
			file >> score;
			_scores.push_back(score);
		}
		file.close();
	}

	void PrintScores()
	{
		int counter = 1;
		for (vector<int>::iterator i = _scores.begin(); i != _scores.end(); ++i, counter++)
			cout << setw(4) << counter << ". " << *i << endl;
	}

	void SortAndReverceScoresVector()
	{
		sort(_scores.begin(), _scores.end());
		reverse(_scores.begin(), _scores.end());
	}
	
	void AddScore(int score)
	{
		ofstream file;
		file.open("C:/Users/Bartek/Desktop/High scores.txt", ios::app);
		file << endl;
		file << score;
		file.close();
	}
};

int main(){
	HighScores scores;
	scores.CreateVectorOfScores();
	scores.SortAndReverceScoresVector();
	scores.PrintScores();
	
	cout << endl << endl;
	
	scores.AddScore(17);				//jako argument trzeba mu wrzucić score ze skończonej rozgrywki
	scores.CreateVectorOfScores();
	scores.SortAndReverceScoresVector();
	scores.PrintScores();

	cout << endl << endl;
	system("pause");
	return 0;
}
