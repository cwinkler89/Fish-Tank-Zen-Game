#pragma once

#include "FSM.h"
#include "vec3f.h"
#include <vector>

#include "EntityManager.h"

class EntityManager;

class Entity
{
    public:
        
        Entity(EntityManager *manager);
        ~Entity();
        
        void update();
        void draw();
        
        void eat(Entity *other);
        bool isEaten();
        
        void setColor(float r, float g, float b);
        void setImage(ofImage *image);
        
        void setPosition(vec3f position);
        vec3f getPosition(){return mPosition;};

        void decreasePower(float amount);
        void increasePower(float amount);
        float getPower(){return mPower;};

        void setSightRadius(float radius);
        float getSightRadius(){return mSightRadius;};

        void setSize(float size);
        float getSize(){return mSize;};
        
        void setVelocity(vec3f velocity);
        vec3f getVelocity(){return mVelocity;};
        
        float getMaxSpeed(){return mMaxSpeed;};
        vec3f getHeading(){return mHeading;};
        
        bool addSteeringSeek(vec3f targetPosition);
        bool addSteeringFollowPath();
        bool addSteeringFlee(vec3f targetPosition);
        bool addSteeringPersuit(Entity *evader);
        bool addSteeringArrive(vec3f targetPosition, unsigned int deceleration);
        
        EntityManager *mManager;

        bool isSmaller;
        
    protected:
        FSM mFSM;
        
        vector<vec3f> mPath;
        unsigned int mCurrentWaypoint;

        vec3f mPosition;
        vec3f mVelocity;
        vec3f mSteeringForce;
        vec3f mHeading;
        float mSize;
        float mSightRadius;
        float mMaxSpeed;
        float mMaxForce;
        float mPower;
        
        bool mIsEaten;
        
        ofColor mColor;
        ofImage *mImage;
        
        bool accumulateForce(vec3f forceToAdd);
};