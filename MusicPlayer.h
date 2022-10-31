#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "Note.h"
using namespace std;

class MusicPlayer {
private:
    double max_amplitude = 32760;  // "volume"
    int beatsPerMinute = 60;
    double hz = 44100;    // samples per second
    ofstream f;
    size_t data_chunk_pos;

    void makeHeader();
    int getNumSamples(double duration);
    vector<Note> getNotesFromFile(string fileName);
    void close();

public:
    MusicPlayer(string fileName);
    MusicPlayer(string fileName, int beatsPerMinute);
    ~MusicPlayer();

    void playNote(double frequency, double duration, double volume);
    void playNote(Note note);
    void playNotes(vector<Note> notes);

    void playFile(string playFile);
};