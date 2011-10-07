#ifndef PLAYER_H
#define PLAYER_H

#include "ofMain.h"
#include "vec3f.h"
#include "Entity.h"
#include <list>

class Entity;
class EntityManager;


class Player : public Entity
{
	public:
		Player(EntityManager *manager);
		~Player();
		
		void draw();
		void setKeyBindings(int keyUp, int keyRight, int keyDown, int keyLeft);
		
        int getKeyUp(){ return mKeyUp; };
        int getKeyRight(){ return mKeyRight; };
        int getKeyDown(){ return mKeyDown; };
        int getKeyLeft(){ return mKeyLeft; };
	    list<int> getKeyEvents(){ return mKeyEvents; };
	    
    private:
        void keyPressed(ofKeyEventArgs & args); 
        void keyReleased(ofKeyEventArgs & args); 
        
        int mKeyUp, mKeyRight, mKeyDown, mKeyLeft;
        list<int> mKeyEvents;
};


#endif