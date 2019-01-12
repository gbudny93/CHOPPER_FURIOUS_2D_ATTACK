#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

class HighScores
{

public:
	std::vector<int> _scores;
	void CreateVectorOfScores();
	void PrintScores();
	void SortAndReverceScoresVector();
	void AddScore(int score);
	
	
};


