#ifndef __brain__ofxMindflex__
#define __brain__ofxMindflex__

#include "ofMain.h"
#include "MindflexSample.h"

class ofxMindflex {
  
  ofSerial serial;
  int state;
  int buf[36];
  int plen;
  int pos;
  int checksum;
  int checkval;
  
  bool connected;
  bool firstReading;
  bool newData;
  
  vector<MindflexSample> samples;
  int maxSamples;
  
  int attention;
  int signal;
  int meditation;
  
  int maxValues[11];
  int minValues[11];
  
  void processPacket();
  int convert3ByteInt(int b1, int b2, int b3);
    
public:
  bool active;
  ofxMindflex(bool, string, int, int);
  void checkSerial();
  int getAttention();
  int getMeditation();
  int getSignalStrength();
  bool gotData() { return !firstReading; }
  bool gotNewData() {
    if (newData) {
      newData = false;
      return true;
    }
    return false;
  }
  float getValue(int);
  
  void drawChannel(int, float, float);
  
};

#endif 
