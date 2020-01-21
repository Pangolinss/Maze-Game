#include "Monster.h"

Monster::Monster()
{
    //ctor
}

Monster::Monster(sf::Texture& texture, sf::Vector2f vec, int _spd, std::string fileName)
{
    pos.x = vec.x;
    pos.y = vec.y;
    sprite.setPosition(pos);
    texture.loadFromFile(fileName);
    sprite.setTexture(texture);
    sprite.setScale(1.f,1.f);
    dir = -1;
    move_dir = -1;
    spd = _spd;
    isAlive = true;
}

Monster::~Monster()
{
    //dtor
}

void Monster::chasePlayer(Being* player, float time, GameMap* gamemap)//this algorithm draws a rectangle and checks if this intersects with a player
//if yes, it chases the player
{
    sf::RectangleShape sight;
    sight.setSize(sf::Vector2f(25.f,25.f));
    sight.setPosition(pos);
    bool playerFound = false;
    move_dir = -1;
    sight.move(0.f, -12);
    while(checkMove(sight.getPosition(), gamemap, this))
    {
        sight.move(0.f, (-1.0)*1.f);
        if (sight.getGlobalBounds().intersects(player->getSprite().getGlobalBounds()))
        {
            move_dir = 0; dir = 0;
            playerFound = true;
            break;
        }
    }
    if (!playerFound)
    {
        sight.setPosition(pos);
        sight.move(0.f, 12);
        while(checkMove(sight.getPosition(), gamemap, this))
        {
            sight.move(0.f, 1.f);
            if (sight.getGlobalBounds().intersects(player->getSprite().getGlobalBounds()))
            {
                move_dir = 1; dir = 1;
                playerFound = true;
                break;
            }
        }
    }
    if (!playerFound)
    {
        sight.setPosition(pos);
        sight.move(-12, 0.f);
        while(checkMove(sight.getPosition(), gamemap, this))
        {
            sight.move((-1.0)*1.f, 0.f);
            if (sight.getGlobalBounds().intersects(player->getSprite().getGlobalBounds()))
            {
                move_dir = 2; dir = 2;
                playerFound = true;
                break;
            }
        }
    }
    if (!playerFound)
    {
        sight.setPosition(pos);
        sight.move(12, 0.f);
        while(checkMove(sight.getPosition(), gamemap, this))
        {
            sight.move(1.f, 0.f);
            if (sight.getGlobalBounds().intersects(player->getSprite().getGlobalBounds()))
            {
                move_dir = 3; dir = 3;
                playerFound = true;
                break;
            }
        }
    }
    if (!playerFound)
    {
        move_dir = dir;
    }//some glitchiness, the center of the sprite has all rectangle touching so it gets confusing what direction it should go
    Being::movement(time, gamemap);
}

void Monster::chasePlayerSpooky(Being* player, float time, int magicPlayerDetectionRadius)
{
    sf::Vector2f p_pos = player->getPos();//chases player if in range
    if ((p_pos.x-pos.x)*(p_pos.x-pos.x) + (p_pos.y-pos.y)*(p_pos.y-pos.y) < magicPlayerDetectionRadius*magicPlayerDetectionRadius)
    {
        move_dir = -1;
        if (pos.y>p_pos.y)
        {
            pos.y-=spd*time;
        }
        if (pos.y<p_pos.y)
        {
            pos.y+=spd*time;
        }
        if (pos.x<p_pos.x)
        {
            pos.x+=spd*time;
        }
        if (pos.x>p_pos.x)
        {
            pos.x-=spd*time;
        }
    }
    else if (rand()%1000 == 43)//idle movement, checks if it randoms to an exact number to change direction
    {
        move_dir = rand()%4;
        if (move_dir == 0)
        {
            pos.y-=spd*time;
        }
        if (move_dir == 1)
        {
            pos.y+=spd*time;
        }
        if (move_dir == 2)
        {
            pos.x+=spd*time;
        }
        if (move_dir == 3)
        {
            pos.x-=spd*time;
        }
    }

}

bool Monster::hitBoxDetection(Projectile* proj[MAX_PROJ])//checks if been shot by looking at sprite bounds
{
    for (int i = 0; i<MAX_PROJ; i++)
    {
        if (proj[i] != nullptr)
        {
            if (sprite.getGlobalBounds().intersects(proj[i]->getSprite().getGlobalBounds()))
            {
                isAlive = false;
                proj[i]->kill();
                delete proj[i];
                proj[i] = nullptr;
                return true;
            }
        }
    }
    return false;
}

void Monster::onDeathDrop(GameEvent* gameEvent[NUM_EVENTS])
{
    for (int i = 0; i<NUM_EVENTS; i++)
    {
        if (gameEvent[i]==nullptr)
        {
            gameEvent[i] = new GameEvent(&playerOnSprite, &giveKey, pos, "bin//release//common//Items//key.png", tex[6]);
            return;
        }
    }
    return;
}

void spawnGhosts(Monster* ghosts[NUM_GHOSTS])//spawns ghost somewhere
{
    int s;
    for (int i = 0; i<NUM_GHOSTS; i++)
    {
        s = rand()%1500;
        if (s == 232)
        {
            if (ghosts[i] == nullptr)
            {
                sf::Vector2f vec;
                vec.x = rand()%900;
                vec.y = rand()%900;
                ghosts[i] = new Monster(tex[4], vec, 75+(rand()%10), "bin//release//common//being//ghost_sprite.png");
            }
        }
    }
}

void manageGhosts(Monster* ghosts[NUM_GHOSTS], Being* player, float time)
{
    for (int i = 0; i<NUM_GHOSTS; i++)
    {
        if (ghosts[i] != nullptr)
        {
            ghosts[i]->hitBoxDetection(proj);
            ghosts[i]->chasePlayerSpooky(player, time,200);
            ghosts[i]->renderMovement(window, &shader);
        }
    }
}

void deleteGhosts(Monster* ghosts[NUM_GHOSTS], GameEvent* gameEvent[NUM_EVENTS])//kills ghosts
{
    for (int i = 0; i<NUM_GHOSTS; i++)
    {
        if (ghosts[i] != nullptr)
        {
            if (!ghosts[i]->isAlive)
            {
                ghosts[i]->onDeathDrop(gameEvent);
                delete ghosts[i];
                ghosts[i] = nullptr;
            }
        }
    }
}

