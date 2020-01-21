#include "GameEvent.h"

GameEvent::GameEvent()
{
    //ctor
    trigger = nullptr;
    effect = nullptr;
    activeEvent = true;
}

GameEvent::GameEvent(bool (*_t)(GameEvent*, int[2], Player*, sf::Event&), void (*_e)(GameEvent*, GameMap*, Player*), sf::Vector2f _vec, std::string str, sf::Texture& tex)
{
    trigger = _t;
    effect = _e;
    pos_vec = _vec;
    tex.loadFromFile(str);
    sprite.setTexture(tex);
    sprite.setScale(0.5,0.5);
    activeEvent = true;
}

GameEvent::~GameEvent()
{
    //dtor
}

void GameEvent::drawEvent(sf::RenderWindow&, sf::Shader& s)
{
    sprite.setPosition(pos_vec);
    shader.setUniform("texture", sf::Shader::CurrentTexture);
    window.draw(sprite, &shader);
}

void GameEvent::checkEvent(GameMap* gameMap, Player* player, sf::Event& event)//checks event
{
    if (!trigger(this, pos, player, event))
    {
        return;
    }
    effect(this, gameMap, player);
    return;
}
//triggers
bool playerOnSprite(GameEvent* gameEvent, int pos[2], Player* player, sf::Event& event)//checks if a player is on a sprite
{

    if (gameEvent->sprite.getGlobalBounds().intersects(player->getSprite().getGlobalBounds()))
    {
        return true;
    }
    return false;
}

bool hasItem(GameEvent* gameEvent, int pos[2], Player* player, sf::Event& event)//checks if the player has an item, not used
{
    return player->getKey();
}
//effects
void giveKey(GameEvent* gameEvent, GameMap* gameMap, Player* player)//gives the player an item
{
    player->getInventory()->addItem(0);
    player->setKey(true);
    gameEvent->activeEvent = false;
}

void unlockDoor(GameEvent* gameEvent, GameMap* gameMap, Player* player)//not used
{
    for (int i = 0; i<MAP_SIZE; i++)
    {
        for (int j = 0; j<MAP_SIZE; j++)
        {
            if (gameMap->getLayer2(i,j)==2)
            {
                gameMap->setLayer1(i,j,0);
            }
        }
    }
}
//-----------------------------------------------------------------------------------------------
void manageEvents(GameEvent* gameEvents[NUM_EVENTS], GameMap* gameMap, Player* player, sf::Event& event)//just deals with an array of objects
{
    for (int i = 0; i<NUM_EVENTS; i++)
    {
        if (gameEvents[i] != nullptr)
        {
            gameEvents[i]->checkEvent(gameMap, player, event);
        }
    }
}

void drawEvents(GameEvent* gameEvent[NUM_EVENTS])
{
    for (int i = 0; i<NUM_EVENTS; i++)
    {
        if (gameEvent[i] != nullptr)
        {
            gameEvent[i]->drawEvent();
        }
    }
}

void deleteEvents(GameEvent* gameEvent[NUM_EVENTS])
{
    for (int i = 0; i<NUM_EVENTS; i++)
    {
        if (gameEvent[i] != nullptr)
        {
            if (!gameEvent[i]->activeEvent)
            {
                delete gameEvent[i];
                gameEvent[i] = nullptr;
            }
        }
    }
}
