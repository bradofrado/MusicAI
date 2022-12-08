#include <cmath>
#include <fstream>
#include <iostream>
#include <time.h>
#include <map>
#include <vector>
#include <sstream>
#include <random>
#include "MusicPlayer.h"
#include "Note.h"
#include "MidiFile.h"
#include "Options.h"
#include "Binasc.h"
#include "MidiEvent.h"
#include "MidiEventList.h"
#include "MidiMessage.h"


using namespace std;
using namespace smf;

int main(int argv, char* argc[])
{
    string arg1 = argc[1];
    if (arg1 == "-m") {
        if (argv < 4) {
            cout << "Invalid arguments. Usage <-m> <inputfile> <outputfile>";
            exit(0);
        }
        MidiFile midifile;
        midifile.read(argc[2]);
		  random_device rd;
   mt19937 mt(rd());
   uniform_int_distribution<int> starttime(0, 200);
   uniform_int_distribution<int> duration(1, 8);
   uniform_int_distribution<int> pitch(36, 84);
   uniform_int_distribution<int> velocity(40, 100);

   //MidiFile midifile;
   int track   = 0;
   int channel = 0;
   int instr   = 1;
   midifile.addTimbre(track, 0, channel, instr);

   int tpq     = midifile.getTPQ();
   int count   = 640;
   for (int i=0; i<count; i++) {
      int starttick = int(starttime(mt) / 4.0 * tpq);
      int key       = pitch(mt);
      int endtick   = starttick + int(duration(mt) / 4.0 * tpq);
      midifile.addNoteOn (track, starttick, channel, key, velocity(mt));
      midifile.addNoteOff(track, endtick,   channel, key);
   }
   midifile.sortTracks();  // Need to sort tracks since added events are
                           // appended to track in random tick order.
   string filename = "out.midi";
      midifile.write(filename);
        if(midifile.status()) midifile.write(argc[3]);
        else cerr << "Problem reading MIDI file " << argc[2] << endl;
	}
	if (arg1 == "-n") {
		// if (argv < 2) {
		// 	cout << "Incorrect format. Usage <-n> <outputfile>." << endl;
		// 	exit(0);
		// }
		 MidiFile midifile;
        //midifile.read(argc[2]);
		random_device rd;
		mt19937 mt(rd());
		uniform_int_distribution<int> starttime(0, 120);
		uniform_int_distribution<int> duration(1, 16);
		uniform_int_distribution<int> pitch(24, 96);
		uniform_int_distribution<int> velocity(30, 100);

		//MidiFile midifile;
		int track   = 0;
		int channel = 0;
		int instr   = 1;
		midifile.addTimbre(track, 0, channel, instr);

		int tpq  = midifile.getTPQ();
		int count = 300;
		int keepcount = 0;
		for (int i=0; i<count; i++) {
			if (count % 1 == 0) {
                for (int j = 0; j < 8; j++) {
                    switch (j) {
                        case 0: {  //Note of C
                            int randint = rand() % 4 - 2;
                            int starttick = int(starttime(mt) / 4.0 * tpq);
                            int noo = pitch(mt);
                            int diff = noo % 12;
                            int key  = ((noo + (12 - diff)) * randint);
                            int endtick = starttick + int(duration(mt) / 4.0 * tpq);
                            midifile.addNoteOn (track, starttick, channel, key, velocity(mt));
                            midifile.addNoteOff(track, endtick,   channel, key);
                            i++;
                            break;
                        }
                        case 1: {  //Note of E
                            int randint = rand() % 4 - 2;
                            int starttick = int(starttime(mt) / 4.0 * tpq);
                            int noo = pitch(mt);
                            int diff = noo % 12;
                            int key  = ((noo + (12 - diff)) + 4) * randint;
                            int endtick = starttick + int(duration(mt) / 4.0 * tpq);
                            midifile.addNoteOn (track, starttick, channel, key, velocity(mt));
                            midifile.addNoteOff(track, endtick,   channel, key);
                            i++;
                            break;
                        }
                        case 2: {  //Note of G
                            int randint = rand() % 4 - 2;
                            int starttick = int(starttime(mt) / 4.0 * tpq);
                            int noo = pitch(mt);
                            int diff = noo % 12;
                            int key  = (noo + (12 - diff) + 7) * randint;
                            int endtick = starttick + int(duration(mt) / 4.0 * tpq);
                            midifile.addNoteOn (track, starttick, channel, key, velocity(mt));
                            midifile.addNoteOff(track, endtick,   channel, key);
                            i++;
                            break;
                        }
                        case 3: {  //Note of E
                            int randint = rand() % 4 - 2;
                            int starttick = int(starttime(mt) / 4.0 * tpq);
                            int noo = pitch(mt);
                            int diff = noo % 12;
                            int key  = (noo + (12 - diff) + 4) * randint;
                            int endtick = starttick + int(duration(mt) / 4.0 * tpq);
                            midifile.addNoteOn (track, starttick, channel, key, velocity(mt));
                            midifile.addNoteOff(track, endtick,   channel, key);
                            i++;
                            break;
                        }
                        case 4: { //Note of C
                            int randint = rand() % 4 - 2;
                            int starttick = int(starttime(mt) / 4.0 * tpq);
                            int noo = pitch(mt);
                            int diff = noo % 12;
                            int key  = ((noo + (12 - diff)) * randint);
                            int endtick = starttick + int(duration(mt) / 4.0 * tpq);
                            midifile.addNoteOn (track, starttick, channel, key, velocity(mt));
                            midifile.addNoteOff(track, endtick,   channel, key);
                            i++;
                            break;
                        }   
                        case 5: {//Note of E
                            int randint = rand() % 4 - 2;
                            int starttick = int(starttime(mt) / 4.0 * tpq);
                            int noo = pitch(mt);
                            int diff = noo % 12;
                            int key  = (noo + (12 - diff) + 4) * randint;
                            int endtick = starttick + int(duration(mt) / 4.0 * tpq);
                            midifile.addNoteOn (track, starttick, channel, key, velocity(mt));
                            midifile.addNoteOff(track, endtick,   channel, key);
                            i++;
                            break;
                        }   
                        case 6: {//Note of G
                           int randint = rand() % 4 - 2;
                            int starttick = int(starttime(mt) / 4.0 * tpq);
                            int noo = pitch(mt);
                            int diff = noo % 12;
                            int key  = (noo + (12 - diff) + 7) * randint;
                            int endtick = starttick + int(duration(mt) / 4.0 * tpq);
                            midifile.addNoteOn (track, starttick, channel, key, velocity(mt));
                            midifile.addNoteOff(track, endtick,   channel, key);
                            i++;
                            break;
                        }
                        case 7:  {//Note of E
                            int randint = rand() % 4 - 2;
                            int starttick = int(starttime(mt) / 4.0 * tpq);
                            int noo = pitch(mt);
                            int diff = noo % 12;
                            int key  = (noo + (12 - diff) + 4) * randint;
                            int endtick = starttick + int(duration(mt) / 4.0 * tpq);
                            midifile.addNoteOn (track, starttick, channel, key, velocity(mt));
                            midifile.addNoteOff(track, endtick,   channel, key);
                            i++;
                            break;
                        }
                    }
                }
				
			}
				int starttick = int(starttime(mt) / 4.0 * tpq);
				int noo = pitch(mt);
				int diff = noo % 4;
				int key  = noo + (12 - diff);
				int endtick = starttick + int(duration(mt) / 4.0 * tpq);
				midifile.addNoteOn (track, starttick, channel, key, velocity(mt));
				midifile.addNoteOff(track, endtick,   channel, key);
		}
		midifile.sortTracks();  // Need to sort tracks since added events are
						// appended to track in random tick order.
		string filename = "out.midi";
		midifile.write(filename);
		if(midifile.status()) midifile.write(filename);
		else cerr << "Problem reading MIDI file " << filename << endl;
		}
    else if (argv < 3) {
        cout << "Invalid arguments. Usage <musicfile> <beats per minute>";
        exit(0);
    stringstream ss;
	int beatsPerMinute = stoi(argc[2]);
	
    string inputFile = argc[1];
	cout << "Now opening: " << inputFile << endl;
	ss << inputFile << ".wav";

    MusicPlayer player(ss.str(), beatsPerMinute);
	
    MusicData song(vector<Measure> {
        Measure(vector<Note> {
            //Right hand
            Note("E", 4, 4, 0, 1),
            Note("D", 4, 4, .5, 1),
            Note("C", 4, 4, 1, 1),
            Note("D", 4, 4, 1.5, 1),
            Note("E", 4, 4, 2, 1),
            Note("E", 4, 4, 2.5, 1),
            Note("E", 4, 4, 3, 1),

            //Left hand
            Note("C", 3, 4, 0, 1),
            Note("E", 3, 4, .25, 1),
            Note("G", 3, 4, .5, 1),
            Note("E", 3, 4, .75, 1),
            Note("C", 3, 4, 1, 1),
            Note("E", 3, 4, 1.25, 1),
            Note("G", 3, 4, 1.5, 1),
            Note("E", 3, 4, 1.75, 1),
            Note("C", 3, 4, 2, 1),
            Note("E", 3, 4, 2.25, 1),
            Note("G", 3, 4, 2.5, 1),
            Note("E", 3, 4, 2.75, 1),
            Note("C", 3, 4, 3, 1),
            Note("E", 3, 4, 3.25, 1),
            Note("G", 3, 4, 3.5, 1),
            Note("E", 3, 4, 3.75, 1),
        }),
        Measure(vector<Note> {
            Note("D", 4, .5, 0, 1),
            Note("D", 4, .5, .5, 1),
            Note("D", 4, 1, 1, 1),
            Note("E", 4, .5, 2, 1),
            Note("G", 4, .5, 2.5, 1),
            Note("G", 4, 1, 3, 1),

            //Left hand
            Note("B", 2, .25, 0, 1),
            Note("D", 3, .25, .25, 1),
            Note("G", 3, .25, .5, 1),
            Note("D", 3, .25, .75, 1),
            Note("B", 2, .25, 1, 1),
            Note("D", 3, .25, 1.25, 1),
            Note("G", 3, .25, 1.5, 1),
            Note("D", 3, .25, 1.75, 1),
            Note("C", 3, .25, 2, 1),
            Note("E", 3, .25, 2.25, 1),
            Note("G", 3, .25, 2.5, 1),
            Note("E", 3, .25, 2.75, 1),
            Note("C", 3, .25, 3, 1),
            Note("E", 3, .25, 3.25, 1),
            Note("G", 3, .25, 3.5, 1),
            Note("E", 3, .25, 3.75, 1),
        }),
        Measure(vector<Note> {
            Note("E", 4, .5, 0, 1),
            Note("D", 4, .5, .5, 1),
            Note("C", 4, .5, 1, 1),
            Note("D", 4, .5, 1.5, 1),
            Note("E", 4, .5, 2, 1),
            Note("E", 4, .5, 2.5, 1),
            Note("E", 4, .5, 3, 1),
            Note("E", 4, .5, 3.5, 1),

            //Left hand
            Note("C", 3, .25, 0, 1),
            Note("E", 3, .25, .25, 1),
            Note("G", 3, .25, .5, 1),
            Note("E", 3, .25, .75, 1),
            Note("C", 3, .25, 1, 1),
            Note("E", 3, .25, 1.25, 1),
            Note("G", 3, .25, 1.5, 1),
            Note("E", 3, .25, 1.75, 1),
            Note("C", 3, .25, 2, 1),
            Note("E", 3, .25, 2.25, 1),
            Note("G", 3, .25, 2.5, 1),
            Note("E", 3, .25, 2.75, 1),
            Note("C", 3, .25, 3, 1),
            Note("E", 3, .25, 3.25, 1),
            Note("G", 3, .25, 3.5, 1),
            Note("E", 3, .25, 3.75, 1),
        }),
        Measure(vector<Note> {
            Note("D", 4, .5, 0, 1),
            Note("D", 4, .5, .5, 1),
            Note("E", 4, .5, 1, 1),
            Note("D", 4, .5, 1.5, 1),
            Note("C", 4, .5, 2, 1),

            //Left hand
            Note("B", 2, .25, 0, 1),
            Note("D", 3, .25, .25, 1),
            Note("G", 3, .25, .5, 1),
            Note("D", 3, .25, .75, 1),
            Note("B", 2, .25, 1, 1),
            Note("D", 3, .25, 1.25, 1),
            Note("G", 3, .25, 1.5, 1),
            Note("D", 3, .25, 1.75, 1),
            Note("C", 3, .25, 2, 1),
            Note("D", 3, .25, 2.25, 1),
            Note("E", 3, .25, 2.5, 1),
            Note("G", 3, .25, 2.75, 1),
            Note("C", 4, .5, 3, 1),
        }),
        Measure(vector<Note> {
            Note("C", 4, .25, 2, 1)
        })
    });

    //player.playData(song);
    player.playFile(inputFile + ".txt");
    }
}