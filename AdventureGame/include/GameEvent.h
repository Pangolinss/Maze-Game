#ifndef GAMEEVENT_H
#define GAMEEVENT_H
#define NUM_EVENTS 50
#include"SFML/Graphics.hpp"
#include"Player.h"
#include"GameMap.h"
#include<iostream>

extern sf::RenderWindow window;
extern sf::Shader shader;

class Player;
class GameEvent//a game event does something if a condition is met
{
    public:
        GameEvent(bool (*_t)(GameEvent*, int[2], Player*, sf::Event&), void (*_e)(GameEvent*, GameMap*, Player*), sf::Vector2f _vec, std::string str, sf::Texture& tex);
        GameEvent();
        virtual ~GameEvent();

        void drawEvent(sf::RenderWindow& w = window, sf::Shader& s = shader);
        void checkEvent(GameMap*, Player*, sf::Event&);//checks the condition and trigger


        //triggers
        friend bool playerOnSprite(GameEvent*, int[2], Player*, sf::Event&);
        friend bool hasItem(GameEvent*, int[2], Player*, sf::Event&);

        //Effects
        friend void giveKey(GameEvent*, GameMap*, Player*);
        friend void unlockDoor(GameEvent*, GameMap*, Player*);//not actually used

        //Manage Events
        friend void manageEvents(GameEvent*[NUM_EVENTS], GameMap*, Player*, sf::Event&);//manages your events for you
        friend void drawEvents(GameEvent*[NUM_EVENTS]);//draws events
        friend void deleteEvents(GameEvent*[NUM_EVENTS]);//kills used events

        //Events actually act a lot like beings, maybe should have made it a child class
    private:
        bool (*trigger)(GameEvent*, int[2], Player*, sf::Event&);//a function that returns true if a condition is met
        void (*effect)(GameEvent*, GameMap*, Player*);//a function that does something
        int pos[2];//position of event
        sf::Vector2f pos_vec;//vector position of event
        sf::Sprite sprite;//sprite
        bool activeEvent;//checks if the event fired or not
};


#endif // GAMEEVENT_H
