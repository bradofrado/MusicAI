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
    if (argv < 3) {
        cout << "Invalid arguments. Usage <musicfile> <beats per minute>";
        exit(0);
    }

    stringstream ss;
	int beatsPerMinute = stoi(argc[2]);
	
    string inputFile = argc[1];
	cout << "Now opening: " << inputFile << endl;
	ss << inputFile << ".wav";

    MusicPlayer player(ss.str(), beatsPerMinute);
	stringstream ww;
	ww << inputFile << ".txt";
    
    try {
        player.playFile(ww.str());
    } catch(char const* c) {
        cout << "Error:" << c;
        exit(0);
    }
}