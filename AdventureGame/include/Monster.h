#ifndef MONSTER_H
#define MONSTER_H
#define NUM_CRAWLERS 20
#define NUM_GHOSTS 20

#include <Being.h>
#include "Projectile.h"
#include "GameEvent.h"
#include "GameMap.h"

const extern int SIZE;
const extern int MAX_PROJ;
extern sf::RenderWindow window;
extern sf::Shader shader;
extern Projectile* proj[MAX_PROJ];
extern sf::Texture tex[20];

class Player;
bool playerOnSprite(GameEvent*, int[2], Player*, sf::Event&);
bool hasItem();

//Effects
void giveKey(GameEvent*, GameMap*, Player*);

class Monster : public Being//a being!
{
    public:
        Monster();
        Monster(sf::Texture&, sf::Vector2f, int, std::string);
        virtual ~Monster();
        void chasePlayer(Being*, float, GameMap*);//chases player if it sees a player
        void chasePlayerSpooky(Being*, float, int);//spookily chases a player within a radius
        bool hitBoxDetection(Projectile*[MAX_PROJ]);//checks if shot
        void onDeathDrop(GameEvent* gameEvent[NUM_EVENTS]);//drops stuff on death

        friend void spawnGhosts(Monster* ghosts[NUM_GHOSTS]);//spawns ghosts
        friend void manageGhosts(Monster* ghosts[NUM_GHOSTS], Being*, float);
        friend void deleteGhosts(Monster* ghosts[NUM_GHOSTS], GameEvent* gameEvent[NUM_EVENTS]);
    private:
};

#endif // MONSTER_H
