#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(640,480,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
  
  string port = "tty.HC-06-DevB";
  int baudrate = 115200;
  bool active = true;
  ofxMindflex brain(active, port, baudrate, 30);
  
	ofRunApp(new testApp(brain));

}
