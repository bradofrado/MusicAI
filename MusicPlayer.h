#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "Note.h"
#include "NoteWav.h"
#include "include/MidiFile.h"
#include "include/Options.h"
#include "include/Binasc.h"
#include "include/MidiEvent.h"
#include "include/MidiEventList.h"
#include "include/MidiMessage.h"

using namespace std;
using namespace Wav;

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
    double getValueAtN(int n, double& maxVolume);
    
    vector<Note> getNotesFromFile(string fileName);
    vector<Measure> getMeasuresFromNotes(vector<Note> notes, int beatsInMeasure);
    vector<NoteWav*> convertToNoteWavs(MusicData data);

    void close();

public:
    MusicPlayer(string fileName);
    MusicPlayer(string fileName, int beatsPerMinute);
    ~MusicPlayer();

    void playFile(string playFile);

    void playData(MusicData data);
};