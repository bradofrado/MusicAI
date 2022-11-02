#include <cmath>
#include "Note.h"

map<string, int> noteDistance = {
        {"C", -9},
        {"C#", -8},
        {"Db", -8},
        {"D", -7},
        {"D#", -6},
        {"Eb", -6},
        {"E", -5},
        {"F", -4},
        {"F#", -3},
        {"Gb", -3},
        {"G", -2},
        {"G#", -1},
        {"Ab", -1},
        {"A", 0},
        {"A#", 1},
        {"Bb", 1},
        {"B", 2},
};

const int OCTAVE_COUNT = 12;
const int BASE_OCTAVE = 4;
const int BASE_HZ = 440;

double Note::getFrequency() {
    int relativeDistance = noteDistance[note];

    int distance = relativeDistance + (octave - BASE_OCTAVE) * OCTAVE_COUNT;

    double frequency = BASE_HZ * pow(2.0, distance / 12.0);

    return frequency;
}