#ifndef _SIMPLE_FSM_APP
#define _SIMPLE_FSM_APP


#include "ofMain.h"

#include "Player.h"
//#include "Monster.h"
#include "EntityManager.h"

class SimpleFSMApp : public ofBaseApp{

	public:

		SimpleFSMApp();
		void setup();
		void update();
		void draw();
		void exit();
        void keyReleased(int key);
		
	private:
	    //Player *mPlayer;
	    EntityManager *mManager;
        ofImage background;
        
        ofImage credits;
        ofImage help;


        ofSoundPlayer mSoundPlayer;
        int mLastUpdate;
};

#endif
