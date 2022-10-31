#include <cmath>
#include <fstream>
#include <iostream>
#include <time.h>
#include <map>
#include <vector>
#include "MusicPlayer.h"
#include "Note.h"

using namespace std;

int main()
{
    srand(time(0));
    int beatsPerMinute = 60;
    MusicPlayer player("example.wav", beatsPerMinute);
    
    player.playFile("marry-had-a-little-lamb.txt");
}