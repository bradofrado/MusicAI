#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "Note.h"
#include "NoteWav.h"

using namespace std;

class MusicPlayer {
private:
    double max_amplitude = 32760;  // "volume"
    int beatsPerMinute = 60;
    double hz = 44100;    // samples per second
    ofstream f;
    size_t data_chunk_pos;

    NoteWavContainer noteWavs;

    void makeHeader();
    int getNumSamples(double duration);
    double getValueAtN(int n);
    vector<Note> getNotesFromFile(string fileName);
    vector<NoteWav> convertToNoteWavs(Song song);
    
    void close();

public:
    MusicPlayer(string fileName);
    MusicPlayer(string fileName, int beatsPerMinute);
    ~MusicPlayer();

    void playNote(double frequency, double duration, double volume);
    void playNote(Note note);
    void playNotes(vector<Note> notes);

    void playFile(string playFile);

    void writeSong(Song song);
};