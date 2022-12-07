#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "Note.h"
#include "NoteWav.h"
#include "MidiFile.h"
#include "Options.h"
#include "Binasc.h"
#include "MidiEvent.h"
#include "MidiEventList.h"
#include "MidiMessage.h"

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