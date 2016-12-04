//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Tue Jan  8 10:08:15 PST 2002
// Last Modified: Mon Feb  9 21:24:41 PST 2015 Updated for C++11.
// Filename:      ...sig/doc/examples/all/createmidifile/createmidifile.cpp
// Syntax:        C++
//
// Description:   Demonstration of how to create a Multi-track MIDI file.
//

#include "MidiFile.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

typedef unsigned char uchar;

///////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {

   string line;
   string seq_start ("s");
   string parallel_track("||");

   queue <string> string_sequences;
   string st_seq = "";
   queue <vector<int>> int_sequences;
   vector<int> pitch_dur_arr;


   int f_melody[50];
   int f_rhythm[50];

   // int bass_in[50];
   // int bass_rhythm[50];


   ifstream myfile;
   myfile.open("file_example.txt");
   if (myfile.is_open()){
      int l = 0;

      while( getline(myfile,line)){
         if(seq_start.compare(line) != 0 && parallel_track.compare(line) != 0){
            cout << "new line "<< '\n';
            st_seq = line;
            string_sequences.push(st_seq);

            char * dup = strdup(line.c_str());
            char *token = strtok(dup, ",");
            int token_num = 0;

            while(token != NULL){
               token_num = atoi(token);

               pitch_dur_arr.push_back(token_num);

               //cout << token << '\n';
               token = strtok(NULL, ",");
               }
            free(dup);
            int_sequences.push(pitch_dur_arr);
            pitch_dur_arr.clear();
         }

         l = l + 1;
      // cout << line << '\n';
      }
      myfile.close();
   }
   else cout << "Can't Open file" << '\n';

   // checking lines read
   cout << "lines in the stack" << '\n';
   while(!string_sequences.empty()){
      cout << string_sequences.front() << '\n';
      string_sequences.pop();
   }


   MidiFile outputfile;        // create an empty MIDI file with one track
   outputfile.absoluteTicks();  // time information stored as absolute time
                               // (will be coverted to delta time when written)
   outputfile.addTrack(2);     // Add another two tracks to the MIDI file
   vector<uchar> midievent;     // temporary storage for MIDI events
   midievent.resize(3);        // set the size of the array to 3 bytes
   int tpq = 120;              // default value in MIDI file is 48
   outputfile.setTicksPerQuarterNote(tpq);

   int track_num = 1;
   int queue_size = int_sequences.size();

   while(!int_sequences.empty()){

      cout << "queue size: ";
      cout << to_string(queue_size) << '\n';
      cout << "ints in the " << to_string(track_num) << " track melody" << '\n';
      vector<int> f_melody_vector = int_sequences.front();
      int k = 0;
      string test = "";
      int n = f_melody_vector.size();
      for ( k = 0; k < n; k++){
         f_melody[k] = f_melody_vector[k];
         test = to_string(f_melody[k]);
         cout << test << '\n';
      }
      int_sequences.pop();

      cout << "ints in the " << to_string(track_num) << " track duration" << '\n';
      vector<int> rhythm_vector = int_sequences.front();
      n = rhythm_vector.size();
      for ( k = 0; k < n; k++){
         f_rhythm[k] = rhythm_vector[k];
         test = to_string(f_rhythm[k]);
         cout << test << '\n';
      }
      int_sequences.pop();

      int i=0;
      int actiontime = 0;      // temporary storage for MIDI event time
      midievent[2] = 64;       // store attack/release velocity for note command
      while (f_melody[i] >= 0) {
         midievent[0] = 0x90;     // store a note on command (MIDI channel 1)
         midievent[1] = f_melody[i];
         outputfile.addEvent(track_num, actiontime, midievent);
         actiontime += tpq * f_rhythm[i];
         midievent[0] = 0x80;     // store a note off command (MIDI channel 1)
         outputfile.addEvent(track_num, actiontime, midievent);
         i++;
      }

      track_num++;
      queue_size = int_sequences.size();
   }

   outputfile.sortTracks();         // make sure data is in correct order
   outputfile.write("twinkle.mid"); // write Standard MIDI File twinkle.mid
   return 0;
}

   // Original Doc -------------------------------------------------------

   ///////////////////////////////////////////////////////////////////////////

   //int main(int argc, char** argv) {

   // MidiFile outputfile;        // create an empty MIDI file with one track
   // outputfile.absoluteTicks();  // time information stored as absolute time
   //                             // (will be coverted to delta time when written)
   // outputfile.addTrack(2);     // Add another two tracks to the MIDI file
   // vector<uchar> midievent;     // temporary storage for MIDI events
   // midievent.resize(3);        // set the size of the array to 3 bytes
   // int tpq = 120;              // default value in MIDI file is 48
   // outputfile.setTicksPerQuarterNote(tpq);

   // data to write to MIDI file: (60 = middle C)
   // C5 C  G G A A G-  F F  E  E  D D C-

   //int melody[50]  = {72,72,79,79,81,81,79,77,77,76,76,74,74,72,81,-1};
   //int mrhythm[50] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1,-1};

   // C3 C4 E C F C E C D B3 C4 A3 F G C-
   // int bass[50] =   {48,60,64,60,65,60,64,60,62,59,60,57,53,55,48,65,-1};
   // int brhythm[50]= { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1,-1};


   // store a melody line in track 1 (track 0 left empty for conductor info)
   // int i=0;
   // int actiontime = 0;      // temporary storage for MIDI event time
   // midievent[2] = 64;       // store attack/release velocity for note command
   // while (melody[i] >= 0) {
   //    midievent[0] = 0x90;     // store a note on command (MIDI channel 1)
   //    midievent[1] = melody[i];
   //    outputfile.addEvent(1, actiontime, midievent);
   //    actiontime += tpq * mrhythm[i];
   //    midievent[0] = 0x80;     // store a note off command (MIDI channel 1)
   //    outputfile.addEvent(1, actiontime, midievent);
   //    i++;
   // }

   // store a base line in track 2
   // i=0;
   // actiontime = 0;          // reset time for beginning of file
   // midievent[2] = 64;
   // while (bass[i] >= 0) {
   //    midievent[0] = 0x90;
   //    midievent[1] = bass[i];
   //    outputfile.addEvent(2, actiontime, midievent);
   //    actiontime += tpq * brhythm[i];
   //    midievent[0] = 0x80;
   //    outputfile.addEvent(2, actiontime, midievent);
   //    i++;
   // }

//    outputfile.sortTracks();         // make sure data is in correct order
//    outputfile.write("twinkle.mid"); // write Standard MIDI File twinkle.mid
//    return 0;
// }


/*  FUNCTIONS available in the MidiFile class:

void absoluteTime(void);
   Set the time information to absolute time.
int addEvent(int aTrack, int aTime, vector<uchar>& midiData);
   Add an event to the end of a MIDI track.
int addTrack(void);
   Add an empty track to the MIDI file.
int addTrack(int count);
   Add a number of empty tracks to the MIDI file.
void deltaTime(void);
   Set the time information to delta time.
void deleteTrack(int aTrack);
   remove a track from the MIDI file.
void erase(void);
   Empty the contents of the MIDI file, leaving one track with no data.
MFEvent& getEvent(int aTrack, int anIndex);
   Return a MIDI event from the Track.
int getTimeState(void);
   Indicates if the timestate is TIME_STATE_ABSOLUTE or TIME_STATE_DELTA.
int getTrackState(void);
   Indicates if the tracks are being processed as multiple tracks or
   as a single track.
int getTicksPerQuarterNote(void);
   Returns the ticks per quarter note value from the MIDI file.
int getTrackCount(void);
   Returns the number of tracks in the MIDI file.
int getNumTracks(void);
   Alias for getTrackCount();
int getNumEvents(int aTrack);
   Return the number of events present in the given track.
void joinTracks(void);
   Merge all tracks together into one track.  This function is reversable,
   unlike mergeTracks().
void mergeTracks(int aTrack1, int aTrack2);
   Combine the two tracks into a single track stored in Track1.  Track2
   is deleted.
int read(char* aFile);
   Read the contents of a MIDI file into the MidiFile class data structure
void setTicksPerQuarterNote    (int ticks);
   Set the MIDI file's ticks per quarter note information
void sortTrack(vector<MFEvent>& trackData);
   If in absolute time, sort particular track into correct time order.
void sortTracks(void);
   If in absolute time, sort tracks into correct time order.

*/



