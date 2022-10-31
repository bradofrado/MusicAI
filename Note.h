#pragma once

#include <string>
#include <map>
#include <cmath>

using namespace std;

// map<string, double> frequencyMap1 = {
//         {"A", 220},
//         {"A#", 233.08},
//         {"B", 246.94},
//         {"C", 261.63},
//         {"C#", 277.18},
//         {"D", 293.66},
//         {"D#", 311.13},
//         {"E", 329.63},
//         {"F", 349.23},
//         {"F#", 369.99},
//         {"G", 392},
//         {"G#", 415.3},
//     };



struct Note {
    double volume;
    double duration;
    string note;
    int octave;

    Note(string note, double duration, double volume) : Note(note, 4, duration, volume) {}
    Note(string note, int octave, double duration, double volume) : note(note), octave(octave), duration(duration), volume(volume) {}
    double getFrequency();
};