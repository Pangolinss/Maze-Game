#ifndef BEING_H
#define BEING_H
#include<iostream>
#include<cmath>
#include"GameMap.h"
#include<SFML/Graphics.hpp>

extern sf::Shader shader;

class Being
{
    public:
        Being();
        Being(sf::Texture&);
        virtual ~Being();

        //get and set methods
        sf::Vector2f getPos(){return pos;}
        int getDir(){return dir;}
        sf::Sprite& getSprite(){return sprite;}
        float getSpd(){return spd;}
        bool getAlive(){return isAlive;}

        void setPos(float a, float b){pos.x = a;pos.y = b;}
        void setAlive(bool _a){isAlive = _a;}

        virtual void renderMovement(sf::RenderWindow& window, sf::Shader* = &shader);//move input
        virtual void movement(float time, GameMap* gamemap);//actual moving
        virtual void kill();//kills the being

    protected:
        sf::Vector2f pos;//position
        sf::Sprite sprite;//sprite
        int dir;//this stores your movement input
        int move_dir; //this stores which way you are actually moving
        float spd;//speed
        bool isAlive;//are you alive?
};

#endif // BEING_H
