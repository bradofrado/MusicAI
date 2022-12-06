#pragma once

#include <string>
#include <map>
#include <cmath>
#include <vector>
#include "MidiFile.h"
#include "Options.h"
#include "Binasc.h"
#include "MidiEvent.h"
#include "MidiEventList.h"
#include "MidiMessage.h"

using namespace std;

struct Note {
    double volume;
    double duration;
    string note;
    int octave;
    double time;

    Note(string note, int octave, double duration, double time, double volume) : note(note), octave(octave), duration(duration), time(time), volume(volume) {}
    double getFrequency();
};

struct Measure {
    vector<Note> notes;
    Measure(vector<Note> notes) {
        this->notes = notes;
    }

    int getDuration() {
        return 4;
    }
};

struct MusicData {
    MusicData(vector<Measure> measures) {
        this->measures = measures;
    }
    vector<Measure> measures;
    int duration = 0;
    int getDuration() {
        if (duration > 0) {
            return duration;
        }

        for (Measure m : measures) {
            duration += m.getDuration();
        }

        return duration;
    }   
};