#include "ofxMindflex.h"

ofxMindflex::ofxMindflex(bool _active, string _port, int _baud, int _maxSaved) {
  newData = false;
  maxSamples = _maxSaved;
  connected = false;
  firstReading = true;
  serial.listDevices();
  active = _active;
  
  if (active) {
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    int serialDeviceID;
    for (vector<ofSerialDeviceInfo>::iterator i = deviceList.begin(); i != deviceList.end(); i++)
    {
      if (i->getDeviceName() == _port) {
        if (serial.setup(i->getDeviceID(), _baud)) {
          connected = true;
        }
        break;
      }
    }
  }
  state = 1;
  // so we don't have to reallocate as samples come in
  samples.reserve(50);
}

float ofxMindflex::getValue(int j) {
  if (minValues[j] == maxValues[j]) return 0;
  return ofMap(samples.back().getValue(j), minValues[j], maxValues[j], 0, 1);
}

void ofxMindflex::checkSerial() {
  int current;
  if (connected) {
    while (serial.available() > 0) {
      current = serial.readByte();
      switch (state) {
        case 1:
          if (current == 0xAA) state = 2;
          break;
        case 2:
          if (current == 0xAA) state = 3;
          else state = 1;
          break;
        case 3:
          if (current > 170) state = 1;
          else if (current < 170) {
            plen = current;
            state = 4;
          }
          break;
        case 4:
          buf[pos++] = current;
          checksum += current;
          if (pos >= plen) state = 5;
          break;
        case 5:
          checkval = current;
          checksum &= 0xFF;
          checksum = ~checksum & 0xFF;
          processPacket();
          state = 1;
          plen = 0;
          pos = 0;
          checksum = 0;
          checkval = 0;
      }
    }
  }
}
int ofxMindflex::getMeditation() {
  return meditation;
}
int ofxMindflex::getAttention() {
  return attention;
}
int ofxMindflex::getSignalStrength() {
  return signal;
}

int ofxMindflex::convert3ByteInt(int b1, int b2, int b3) {
  int temp = b1;
  temp = (temp << 8) + b2;
  temp = (temp << 8) + b3;
  return temp;
}

void ofxMindflex::processPacket() {
  if (checksum != checkval) {
    cout << "Checksum error" << endl;
  }
  else {
    newData = true;
    attention = buf[29];
    meditation = buf[31];
    signal = buf[1];
    
    MindflexSample s;
    s.attention = attention;
    s.meditation = meditation;
    s.signal = signal;
    
    s.delta = convert3ByteInt(buf[4],buf[5],buf[6]);
    s.theta = convert3ByteInt(buf[7],buf[8],buf[9]);
    s.lowAlpha = convert3ByteInt(buf[10],buf[11],buf[12]);
    s.highAlpha = convert3ByteInt(buf[13],buf[14],buf[15]);
    s.lowBeta = convert3ByteInt(buf[16],buf[17],buf[18]);
    s.highBeta = convert3ByteInt(buf[19],buf[20],buf[21]);
    s.lowGamma = convert3ByteInt(buf[22],buf[23],buf[24]);
    s.midGamma = convert3ByteInt(buf[25],buf[26],buf[27]);
    
    samples.push_back(s);
    if (samples.size() > maxSamples) {
      samples.erase(samples.begin());
    }
    if (samples.size()) {
      for (int j = SAMPLE_SIGNAL; j <= SAMPLE_MIDGAMMA; j++) {
        int minVal = samples.front().getValue(j);
        int maxVal = samples.front().getValue(j);
        for (vector<MindflexSample>::iterator i = samples.begin(); i != samples.end(); i++) {
          int tempVal = i->getValue(j);
          if (tempVal < minVal) minVal = tempVal;
          if (tempVal > maxVal) maxVal = tempVal;
        }
        minValues[j] = minVal;
        maxValues[j] = maxVal;
      }
    }
    firstReading = false;
  }
}

void ofxMindflex::drawChannel(int _c, float _w, float _h) {
  float width = _w / maxSamples;
  float x = 0;
  float h;
  int tempMax = maxValues[_c];
  if (tempMax == minValues[_c]) tempMax++;
  float prevH = ofMap(samples.begin()->getValue(_c), minValues[_c], tempMax, 0, _h);
  for(vector<MindflexSample>::iterator it = samples.begin() + 1; it != samples.end(); ++it){
    h = ofMap(it->getValue(_c), maxValues[_c], minValues[_c], 0, _h);
    ofLine(x, _h - prevH, x + width, _h - h);
    x += width;
    prevH = h;
  }
}
