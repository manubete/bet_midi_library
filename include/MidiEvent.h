//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sat Feb 14 21:47:39 PST 2015
// Last Modified: Sat Feb 14 21:54:52 PST 2015
// Filename:      midifile/include/MidiEvent.h
// Website:       http://midifile.sapp.org
// Syntax:        C++11
// vim:           ts=3 expandtab
//
// Description:   A class which stores a MidiMessage and a timestamp
//                for the MidiFile class.
//

#ifndef _MIDIEVENT_H_INCLUDED
#define _MIDIEVENT_H_INCLUDED

#include "MidiMessage.h"
#include <vector>

using namespace std;

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned long  ulong;

class MidiEvent : public MidiMessage {
   public:
                 MidiEvent    (void);
                 MidiEvent    (int command);
                 MidiEvent    (int command, int param1);
                 MidiEvent    (int command, int param1, int param2);
                 MidiEvent    (int aTime, int aTrack, vector<uchar>& message);
                 MidiEvent    (const MidiMessage& message);
                 MidiEvent    (const MidiEvent& mfevent);

                ~MidiEvent    ();

      MidiEvent& operator=    (MidiEvent& mfevent);
      MidiEvent& operator=    (MidiMessage& message);
      MidiEvent& operator=    (vector<uchar>& bytes);
      MidiEvent& operator=    (vector<char>& bytes);
      MidiEvent& operator=    (vector<int>& bytes);

      int       time;
      int       track;
};


#endif /* _MIDIEVENT_H_INCLUDED */


