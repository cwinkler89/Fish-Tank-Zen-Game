#pragma once

#include "ofMain.h"
#include "Entity.h"

class Entity;
class EntityManager;


class Monster : public Entity
{
    public:
        Monster(EntityManager *manager);
        ~Monster();
};