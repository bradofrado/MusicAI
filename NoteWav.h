#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <queue>
#include <vector>

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

    double getValue(int n) {
        int N = end - start;
        int noteN = n - start;

        double val = 0;

        double amplitude = volume * sin((M_PI * noteN) / N);
        double value = sin( (2 * M_PI * noteN * frequency) / hz );

        return value * amplitude * 2000;
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

class NoteWavContainer : public priority_queue<NoteWav, vector<NoteWav>, PastNoteCompare> {
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
        while (!future.empty() && future.top().start <= n) {
            push(future.top());
            future.pop();
        }

        while (top().end <= n) {
            pop();
        }

        return this->c;
    }
};