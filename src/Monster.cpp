#include "Monster.h"

#include "StateNormalMonster.h"
#include "StateSleepMonster.h"

Monster::Monster(EntityManager *manager)
:   Entity(manager)
{
    mFSM.addState(new StateNormalMonster(this));
    mFSM.addState(new StateSleepMonster(this));
    
    float width = (float)ofGetWidth();
    float height = (float)ofGetHeight();
    
    mPath.push_back(vec3f(ofRandom(0, width), ofRandom(0, height)));
    mPath.push_back(vec3f(ofRandom(0, width), ofRandom(0, height)));
    mPath.push_back(vec3f(ofRandom(0, width), ofRandom(0, height)));
    mPath.push_back(vec3f(ofRandom(0, width), ofRandom(0, height)));
    mPath.push_back(vec3f(ofRandom(0, width), ofRandom(0, height)));
    
    
    mFSM.setInitState(State::eNormalMonster);
}

Monster::~Monster()
{

}