#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <math.h>
#include <queue>
#include <vector>
#include "MidiFile.h"
#include "Options.h"
#include "Binasc.h"
#include "MidiEvent.h"
#include "MidiEventList.h"
#include "MidiMessage.h"


namespace Wav {

class NoteWav {
protected:
    double getTime(int n) {
        int noteN = n - start;
        double time = noteN / hz;

        return time;
    }
public:
    NoteWav(int start, int end, double frequency, double volume, double hz) {
        this->start = start;
        this->realEnd = end;
        this->end = end + 8000;
        this->frequency = frequency;
        this->volume = volume;
        this->amplitutde = volume;
        this->hz = hz;
    }

    int start;
    int end;
    int realEnd;
    double frequency;
    double volume;
    double hz;
    double amplitutde;

    double getAmplitude(int n) {
        return volume;
    }

    virtual double getSinValue(int n) {
        double w = frequency; //+ sin(n);
        double time = getTime(n);
        double val = sin( 2 * M_PI * time * w);

        if (n > realEnd) {
            volume *= 0.9996;
        }

        return val;
    }
};

class PianoWav : public NoteWav {
public:
    PianoWav(int start, int end, double frequency, double volume, double hz) : NoteWav(start, end, frequency, volume, hz) 
    {}

    double getSinValue(int n) override {
        double val = NoteWav::getSinValue(n);
        double time = getTime(n);
        val *= 
        //1
        exp(-0.001 * 2 * M_PI * frequency * time)
        ;
        val += sin(2 * 2 * M_PI * frequency * time) * exp(-0.004 * 2 * M_PI * frequency * time) / 2;
        val += sin(3 * 2 * M_PI * frequency * time) * exp(-0.004 * 2 * M_PI * frequency * time) / 4;
        val += sin(4 * 2 * M_PI * frequency * time) * exp(-0.004 * 2 * M_PI * frequency * time) / 8;
        val += sin(5 * 2 * M_PI * frequency * time) * exp(-0.004 * 2 * M_PI * frequency * time) / 16;
        val += sin(6 * 2 * M_PI * frequency * time) * exp(-0.004 * 2 * M_PI * frequency * time) / 32;

        //val += val * val * val;
        

        return val * amplitutde;
    }
};


class FutureNoteCompare {
public:
    bool operator() (NoteWav* a, NoteWav* b) {
        return a->start > b->start;
    }
};

class PastNoteCompare {
public: 
    bool operator() (NoteWav* a, NoteWav* b) {
        return a->end > b->end;
    }
};

class NoteWavContainer : private priority_queue<NoteWav*, vector<NoteWav*>, PastNoteCompare> {
private:
    priority_queue<NoteWav*, vector<NoteWav*>, FutureNoteCompare> future;
    void createQueue(vector<NoteWav*> waves) {
        for (NoteWav* wav : waves) {
            future.push(wav);
        }
    }
public:
    NoteWavContainer() {}
    NoteWavContainer(vector<NoteWav*> waves) {
        createQueue(waves);
    }
    vector<NoteWav*> getCurrentNotes(int n) {
        //Any wav that is not in the future anymore, add that to the current queue
        while (!future.empty() && future.top()->start <= n) {
            push(future.top());
            future.pop();
        }

        //If anything in the current queue has ended, get rid of it
        while (!empty() && top()->end <= n) {
            pop();
        }

        return this->c;
    }
};
};