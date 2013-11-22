//
//  MindflexSample.h
//  brain
//
//  Created by Darren Mothersele on 22/11/2013.
//
//

#ifndef __brain__MindflexSample__
#define __brain__MindflexSample__

#define SAMPLE_SIGNAL 0
#define SAMPLE_ATTENTION 1
#define SAMPLE_MEDITATION 2

#define SAMPLE_DELTA 3
#define SAMPLE_THETA 4
#define SAMPLE_LOWALPHA 5
#define SAMPLE_HIGHALPHA 6
#define SAMPLE_LOWBETA 7
#define SAMPLE_HIGHBETA 8
#define SAMPLE_LOWGAMMA 9
#define SAMPLE_MIDGAMMA 10

class MindflexSample {
public:
  int signal;
  int attention;
  int meditation;
  int delta;
  int theta;
  int lowAlpha;
  int highAlpha;
  int lowBeta;
  int highBeta;
  int lowGamma;
  int midGamma;
  
  int getValue(int _t) {
    switch(_t) {
      case SAMPLE_ATTENTION:
        return attention;
      case SAMPLE_MEDITATION:
        return meditation;
      case SAMPLE_DELTA:
        return delta;
      case SAMPLE_THETA:
        return theta;
      case SAMPLE_LOWALPHA:
        return lowAlpha;
      case SAMPLE_HIGHALPHA:
        return highAlpha;
      case SAMPLE_LOWBETA:
        return lowBeta;
      case SAMPLE_HIGHBETA:
        return highBeta;
      case SAMPLE_LOWGAMMA:
        return lowGamma;
      case SAMPLE_MIDGAMMA:
        return midGamma;
    }
    return signal;
  }

  
};

#endif /* defined(__brain__MindflexSample__) */
