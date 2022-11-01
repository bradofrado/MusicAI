#include <cmath>
#include <fstream>
#include <iostream>
#include <time.h>
#include <map>
#include <vector>
#include <sstream>
#include "MusicPlayer.h"
#include "Note.h"

using namespace std;

int main(int argv, char* argc[])
{
    srand(time(0));
	 stringstream ss;
	// ss << argc[2];
	
	//int bpm = stoi(argc[2]);
	// for(int i = 0; i < argv; i++) {
	// 	cout << argc[i] << "  ";
	// }

    //int beatsPerMinute = stoi(argc[2]);
	//ss >> beatsPerMinute;
	string inputFile = argc[1];
	cout << "Now opening: " << inputFile << endl;
	ss << inputFile << ".wav";

    MusicPlayer player(ss.str(), 60);
	stringstream ww;
	ww << inputFile << ".txt";
    
    player.playFile(ww.str());
}