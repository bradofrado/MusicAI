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
	
    MusicData song(vector<Measure> {
        Measure(vector<Note> {
            //Right hand
            Note("E", 4, .5, 0, 1),
            Note("D", 4, .5, .5, 1),
            Note("C", 4, .5, 1, 1),
            Note("D", 4, .5, 1.5, 1),
            Note("E", 4, .5, 2, 1),
            Note("E", 4, .5, 2.5, 1),
            Note("E", 4, 1, 3, 1),

            //Left hand
            Note("C", 3, 0, 0, 1),
            Note("E", 3, .25, .25, 1),
            Note("G", 3, .25, .5, 1),
            Note("E", 3, .25, .75, 1),
            Note("C", 3, .25, 1, 1),
            Note("E", 3, .25, 1.25, 1),
            Note("G", 3, .25, 1.5, 1),
            Note("E", 3, .25, 1.75, 1),
            Note("C", 3, .25, 2, 1),
            Note("E", 3, .25, 2.25, 1),
            Note("G", 3, .25, 2.5, 1),
            Note("E", 3, .25, 2.75, 1),
            Note("C", 3, .25, 3, 1),
            Note("E", 3, .25, 3.25, 1),
            Note("G", 3, .25, 3.5, 1),
            Note("E", 3, .25, 3.75, 1),
        }),
        Measure(vector<Note> {
            Note("D", 4, .5, 0, 1),
            Note("D", 4, .5, .5, 1),
            Note("D", 4, 1, 1, 1),
            Note("E", 4, .5, 2, 1),
            Note("G", 4, .5, 2.5, 1),
            Note("G", 4, 1, 3, 1),

            //Left hand
            Note("B", 2, .25, 0, 1),
            Note("D", 3, .25, .25, 1),
            Note("G", 3, .25, .5, 1),
            Note("D", 3, .25, .75, 1),
            Note("B", 2, .25, 1, 1),
            Note("D", 3, .25, 1.25, 1),
            Note("G", 3, .25, 1.5, 1),
            Note("D", 3, .25, 1.75, 1),
            Note("C", 3, .25, 2, 1),
            Note("E", 3, .25, 2.25, 1),
            Note("G", 3, .25, 2.5, 1),
            Note("E", 3, .25, 2.75, 1),
            Note("C", 3, .25, 3, 1),
            Note("E", 3, .25, 3.25, 1),
            Note("G", 3, .25, 3.5, 1),
            Note("E", 3, .25, 3.75, 1),
        }),
        Measure(vector<Note> {
            Note("E", 4, .5, 0, 1),
            Note("D", 4, .5, .5, 1),
            Note("C", 4, .5, 1, 1),
            Note("D", 4, .5, 1.5, 1),
            Note("E", 4, .5, 2, 1),
            Note("E", 4, .5, 2.5, 1),
            Note("E", 4, .5, 3, 1),
            Note("E", 4, .5, 3.5, 1),

            //Left hand
            Note("C", 3, .25, 0, 1),
            Note("E", 3, .25, .25, 1),
            Note("G", 3, .25, .5, 1),
            Note("E", 3, .25, .75, 1),
            Note("C", 3, .25, 1, 1),
            Note("E", 3, .25, 1.25, 1),
            Note("G", 3, .25, 1.5, 1),
            Note("E", 3, .25, 1.75, 1),
            Note("C", 3, .25, 2, 1),
            Note("E", 3, .25, 2.25, 1),
            Note("G", 3, .25, 2.5, 1),
            Note("E", 3, .25, 2.75, 1),
            Note("C", 3, .25, 3, 1),
            Note("E", 3, .25, 3.25, 1),
            Note("G", 3, .25, 3.5, 1),
            Note("E", 3, .25, 3.75, 1),
        }),
        Measure(vector<Note> {
            Note("D", 4, .5, 0, 1),
            Note("D", 4, .5, .5, 1),
            Note("E", 4, .5, 1, 1),
            Note("D", 4, .5, 1.5, 1),
            Note("C", 4, 2, 2, 1),

            //Left hand
            Note("B", 2, .25, 0, 1),
            Note("D", 3, .25, .25, 1),
            Note("G", 3, .25, .5, 1),
            Note("D", 3, .25, .75, 1),
            Note("B", 2, .25, 1, 1),
            Note("D", 3, .25, 1.25, 1),
            Note("G", 3, .25, 1.5, 1),
            Note("D", 3, .25, 1.75, 1),
            Note("C", 3, .25, 2, 1),
            Note("D", 3, .25, 2.25, 1),
            Note("E", 3, .25, 2.5, 1),
            Note("G", 3, .25, 2.75, 1),
            Note("C", 4, 1, 3, 1),
        })
    });

    player.playData(song);
    //player.playFile(inputFile + ".txt");
}