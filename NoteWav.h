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
        return volume * sin((M_PI * noteN) / N);
    }

    double getSinValue(int n) {
        return sin( (2 * M_PI * n * frequency) / hz );
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