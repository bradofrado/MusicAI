#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <queue>
#include <vector>


namespace Wav {

struct NoteWav {
    NoteWav(int start, int end, double frequency, double volume, double hz) {
        this->start = start;
        this->end = end;
        this->frequency = frequency;
        this->volume = volume;
        this->hz = hz;
    }

    int start;
    int end;
    double frequency;
    double volume;
    double hz;
    
    double getAmplitude(int n) {
        int N = end - start;
        int noteN = n - start;
        return volume ;//* sin((M_PI * noteN) / N);
    }

    double getSinValue(int n) {
        int noteN = n - start;
        double time = noteN / hz;
        double w = frequency; //+ sin(n);
        double val = sin( 2 * M_PI * time * w);

        val = doAffects(n, val);

        return val;
    }

    double doAffects(int n, double val) {
        int N = end - start;
        int noteN = n - start;
        double time = noteN / hz;
        val *= exp(-0.004 * 2 * M_PI * frequency * time);
        // val += sin(2 * 2 * M_PI * frequency * time) * exp(-0.004 * 2 * M_PI * frequency * time) / 2;
        // val += sin(3 * 2 * M_PI * frequency * time) * exp(-0.004 * 2 * M_PI * frequency * time) / 4;
        // val += sin(4 * 2 * M_PI * frequency * time) * exp(-0.004 * 2 * M_PI * frequency * time) / 8;
        // val += sin(5 * 2 * M_PI * frequency * time) * exp(-0.004 * 2 * M_PI * frequency * time) / 16;
        // val += sin(6 * 2 * M_PI * frequency * time) * exp(-0.004 * 2 * M_PI * frequency * time) / 32;

        //val += val * val * val;
        return val;
    }
};


class FutureNoteCompare {
public:
    bool operator() (NoteWav a, NoteWav b) {
        return a.start > b.start;
    }
};

class PastNoteCompare {
public: 
    bool operator() (NoteWav a, NoteWav b) {
        return a.end > b.end;
    }
};

class NoteWavContainer : private priority_queue<NoteWav, vector<NoteWav>, PastNoteCompare> {
private:
    priority_queue<NoteWav, vector<NoteWav>, FutureNoteCompare> future;
    void createQueue(vector<NoteWav> waves) {
        for (NoteWav wav : waves) {
            future.push(wav);
        }
    }
public:
    NoteWavContainer() {}
    NoteWavContainer(vector<NoteWav> waves) {
        createQueue(waves);
    }
    vector<NoteWav> getCurrentNotes(int n) {
        //Any wav that is not in the future anymore, add that to the current queue
        while (!future.empty() && future.top().start <= n) {
            push(future.top());
            future.pop();
        }

        //If anything in the current queue has ended, get rid of it
        while (!empty() && top().end <= n) {
            pop();
        }

        return this->c;
    }
};
};