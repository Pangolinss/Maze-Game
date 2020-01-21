#ifndef PROJECTILE_H
#define PROJECTILE_H
#include<Being.h>
#include<SFML/Graphics.hpp>
#include<string>
#include"GameMap.h"

const int MAX_PROJ = 20;

class Projectile : public Being//projectiles are just beings!
{
    public:
        Projectile();
        Projectile(std::string, int, int, sf::Vector2f, int, sf::Texture&);
        virtual ~Projectile();

        void movement(float, GameMap*);
        void destroyProjectile(GameMap*);
        void kill();

        friend void deleteProjectile(Projectile* proj[MAX_PROJ]);

    private:
        std::string sprite_name;
        int targetType;
};

#endif // PROJECTILE_H
