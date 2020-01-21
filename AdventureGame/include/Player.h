#ifndef PLAYER_H
#define PLAYER_H

#include<cmath>
#include <Being.h>
#include"GameMap.h"
#include"Projectile.h"
#include"Monster.h"
#include"Inventory.h"
#define SPAWN_X 128
#define SPAWN_Y 128


extern sf::RenderWindow window;
extern sf::Texture tex[20];

class Player : public Being//a being
{
    public:
        Player();
        Player(sf::Texture&, Items*(*)[NUM_ITEMS]);
        virtual ~Player();
        Inventory* getInventory(){return inventroy;}
        bool getKey() {return hasKey;}
        void setKey(bool k){hasKey = k;}

        void movement(sf::Event& event, float, GameMap*);//moving with collision
        void renderMovement(sf::RenderWindow&, sf::View&);

        void fire(sf::Event& event, Projectile*[MAX_PROJ], sf::Texture&);//shooting
        void monsterHitBox(Monster*[], int);//check if been murdered by a monster

        bool endGame(GameMap*);//check if at end of map
    protected:

    private:
        Inventory* inventroy;//not used
        int fire_dir;//direction of shooting
        bool hasKey;//has key or not
};

#endif // PLAYER_H
