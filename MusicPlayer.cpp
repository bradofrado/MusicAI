#define _USE_MATH_DEFINES

#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
#include "MusicPlayer.h"
#include "Note.h"
#include "NoteWav.h"


using namespace std;
using namespace Wav;

namespace little_endian_io
{
    template <typename Word>
    std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof( Word ) )
    {
    for (; size; --size, value >>= 8)
        outs.put( static_cast <char> (value & 0xFF) );
    return outs;
    }
}
using namespace little_endian_io;

MusicPlayer::MusicPlayer(string fileName) : MusicPlayer(fileName, 60) {}

MusicPlayer::MusicPlayer(string fileName, int beatsPerMinute) {
    f = ofstream(fileName, ios::binary );
    makeHeader();
    this->beatsPerMinute = beatsPerMinute;
}

MusicPlayer::~MusicPlayer(){
    close();
}

void MusicPlayer::playData(MusicData song) {
    int songDuration = song.getDuration();
    int N = getNumSamples(songDuration);

    vector<NoteWav*> noteWavs = convertToNoteWavs(song);
    this->noteWavs = NoteWavContainer(noteWavs);

    double* vals = new double[N];
    double maxVolume = 0;

    for (int n = 0; n < N; n++) {
        double val = getValueAtN(n, maxVolume);

        vals[n] = val;

        // write_word(f,(int)(val), 2);
        // write_word(f,(int)(val), 2);
    }

    double compression = maxVolume > max_amplitude ? max_amplitude / maxVolume : 1;

    for (int n = 0; n < N; n++) {
        double val = vals[n] * compression;

        write_word(f, (int)(val), 2);
        write_word(f, (int)(val), 2);
    }

    for (NoteWav* wav : noteWavs) {
        delete wav;
    }
}


double MusicPlayer::getValueAtN(int n, double& maxVolume) {
    vector<NoteWav*> notes = noteWavs.getCurrentNotes(n);
    
    double value = 0;
    double volume = 0;
    
    //We need to compress the wavs so that the amplitude does not exceed +-1
    //This figures out what to compress it to
    // for (NoteWav note: notes) {
    //     volume += note.getVolume(n);
    // }
    
    volume = volume == 0 ? 1 : volume;

    for (NoteWav* note: notes) {
        double sinVal = note->getSinValue(n);
        double amplitude = note->getAmplitude(n);
        double compression = amplitude / volume;

        value += compression * max_amplitude * sinVal;
    }

    if (value > maxVolume) {
        maxVolume = value;
    }

    return value;
}

vector<NoteWav*> MusicPlayer::convertToNoteWavs(MusicData song) {
    vector<NoteWav*> wavs;
    int N = 0;
    for (Measure measure : song.measures) {
        for (Note note : measure.notes) {
            int numNoteSamples = getNumSamples(note.duration);
            int timeSamples = getNumSamples(note.time);
            int start = N + timeSamples;

            NoteWav* wav = new PianoWav(start, start + numNoteSamples, note.getFrequency(), note.volume, hz);
            wavs.push_back(wav);
        }

        N += getNumSamples(measure.getDuration());
    }

    return wavs;
}

void MusicPlayer::playFile(string fileName) {
    vector<Note> notes = getNotesFromFile(fileName);

    vector<Measure> measures = getMeasuresFromNotes(notes, 4);
    MusicData song(measures);
    
    playData(song);
}

vector<Measure> MusicPlayer::getMeasuresFromNotes(vector<Note> notes, int beatsInMeasure) {
    vector<Measure> measures;

    double currBeat;
    vector<Note> currentMeasureNotes;
    for (Note note: notes) {
        currBeat += note.duration;

        currentMeasureNotes.push_back(note);
        if (currBeat >= beatsInMeasure) {
            measures.push_back(Measure(currentMeasureNotes));
            currentMeasureNotes = vector<Note>();
            currBeat = 0;
        }
    }

    if (!currentMeasureNotes.empty()) {
        measures.push_back(Measure(currentMeasureNotes));
    }

    return measures;
}

vector<Note> MusicPlayer::getNotesFromFile(string fileName) {
    ifstream in(fileName);

    if (!in) {
        throw "File not found";
    }

    string word;
    vector<Note> notes;
    double currTime = 0;
    while(!in.eof()) {
		string note;
        int octave;
        double duration;

        in >> word;
        note = word;

        in >> word;
        octave = stoi(word);

        in >> word;
        duration = stod(word);

        notes.push_back(Note(note, octave, duration, currTime, 1));

        currTime += duration;

        if (currTime >= 4) {
            currTime -= 4;
        }
    }

    in.close();

    return notes;
}

int MusicPlayer::getNumSamples(double duration) {
    double beatsPerSecond = 60.0 / beatsPerMinute;
    return hz * beatsPerSecond * duration;
}

void MusicPlayer::makeHeader() {
    f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
    write_word( f,     16, 4 );  // no extension data
    write_word( f,      1, 2 );  // PCM - integer samples
    write_word( f,      2, 2 );  // two channels (stereo file)
    write_word( f,  (int)hz, 4 );  // samples per second (Hz)
    write_word( f, 176400, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8
    write_word( f,      4, 2 );  // data block size (size of two integer samples, one for each channel, in bytes)
    write_word( f,     16, 2 );  // number of bits per sample (use a multiple of 8)

    // Write the data chunk header
    data_chunk_pos = f.tellp();
    f << "data----";  // (chunk size to be filled in later)
}

void MusicPlayer::close() {
    // (We'll need the final file size to fix the chunk sizes above)
    size_t file_length = f.tellp();

    // Fix the data chunk header to contain the data size
    f.seekp( data_chunk_pos + 4 );
    write_word( f, file_length - data_chunk_pos + 8 );

    // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
    f.seekp( 0 + 4 );
    write_word( f, file_length - 8, 4 ); 
}