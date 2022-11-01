#define _USE_MATH_DEFINES

#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include "MusicPlayer.h"
#include "Note.h"

using namespace std;

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

void MusicPlayer::playNote(double frequency, double duration, double volume) {
    int N = getNumSamples(duration);

    for (int n = 0; n < N; n++)
    {
        //This gives the volume a sin wave so that it does not pop
        double amplitude = volume * max_amplitude * sin((M_PI * n) / N);
        
        double value = sin( (2 * M_PI * n * frequency) / hz );

        //C note harmony
        // double value2 = sin( (2 * M_PI * n * 261.63	) / hz );
        // value += value2;

        write_word(f,(int)(amplitude  * value), 2);
        write_word(f,(int)(amplitude  * value), 2);
    }
}

void MusicPlayer::playNote(Note note) {
    playNote(note.getFrequency(), note.duration, note.volume);
}

void MusicPlayer::playNotes(vector<Note> notes) {
    for (int j = 0; j < notes.size(); j++) {

        Note note = notes[j];
        playNote(note);
    }
}

void MusicPlayer::playFile(string fileName) {
    vector<Note> notes = getNotesFromFile(fileName);

    playNotes(notes);
}

vector<Note> MusicPlayer::getNotesFromFile(string fileName) {
    ifstream in(fileName);

    if (!in) {
        throw "File not found";
    }

    string word;
    vector<Note> notes;
    while(!in.eof()) {
		//cout << "In while loop" << " ";
        string note;
        int octave;
        double duration;

        in >> word;
        note = word;

        in >> word;
        octave = stoi(word);

        in >> word;
        duration = stod(word);

        notes.push_back(Note(note, octave, duration, .5));
    }

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