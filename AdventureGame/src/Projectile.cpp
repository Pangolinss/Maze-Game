#include "Projectile.h"

Projectile::Projectile()
{
    //ctor

}

Projectile::Projectile(std::string s, int _s, int d, sf::Vector2f vec, int _t, sf::Texture& texture)
{
    sprite_name = s;
    spd = _s;
    dir = d;
    pos = vec;
    targetType = _t;
    sprite.setPosition(vec);
    texture.loadFromFile(s);
    sprite.setTexture(texture);
}

Projectile::~Projectile()
{
    //dtor
}

void Projectile::movement(float time, GameMap* gamemap)//moves the projectile
{
    if (isAlive = true)
    {
        switch (dir)
        {
            case 0:
                pos.y +=(-spd)*time;
                break;
            case 1:
                pos.y += (spd)*time;
                break;
            case 2:
                pos.x +=(-spd)*time;
                break;
            case 3:
                pos.x += (spd)*time;
                break;
            default:
                break;
        }
    }
    destroyProjectile(gamemap);
}

void Projectile::destroyProjectile(GameMap* gamemap)//destroys the projectile if it touches a wall
//no need to have pixel perfect collision as the projectile just dies
{
    if (!checkMove(pos, gamemap, this))
    {
        kill();
    }
}

void Projectile::kill()
{
    Being::kill();
}

void deleteProjectile(Projectile* proj[MAX_PROJ])//deletes a projectile and makes its pointer available for usage
{
    for (int i = 0; i<MAX_PROJ; i++)
    {
        if (proj[i] != nullptr)
        {
            if (!proj[i]->isAlive)
            {
                delete proj[i];
                proj[i] = nullptr;
            }
        }
    }
}
