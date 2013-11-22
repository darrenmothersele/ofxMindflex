#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  
}

//--------------------------------------------------------------
void testApp::update(){
  if (brain.active) {
    brain.checkSerial();
  }
}

//--------------------------------------------------------------
void testApp::draw(){
  if (brain.active) {
    if (brain.gotData()) {
      // Draw graphs
      ofTranslate(ofGetWidth() - 70, ofGetHeight() - 10);
      for (int i = SAMPLE_ATTENTION; i <= SAMPLE_MIDGAMMA; i++) {
        ofTranslate(0, -20);
        ofSetColor(255, 125);
        brain.drawChannel(i, 50, 10);
      }
    }
  }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
