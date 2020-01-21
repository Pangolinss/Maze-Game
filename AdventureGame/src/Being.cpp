#include "Being.h"

Being::Being()
{
    //ctor
    pos.x = 0; pos.y = 0;//default constructor
}

Being::~Being()
{
    //dtor
}

void Being::renderMovement(sf::RenderWindow& window, sf::Shader* shader)//draws where you are
{
    sprite.setPosition(pos);
    shader->setUniform("texture", sf::Shader::CurrentTexture);
    window.draw(sprite, shader);
}

void Being::movement(float time, GameMap* gamemap)//moves and then asks the gamemap if this is a valid move
{
    switch (move_dir)
    {
        case 0:
            pos.y +=(-spd)*time;
            if (!checkMove(pos, gamemap, this))
            {
                while (!checkMove(pos, gamemap, this))//if a move is invalid, it moves you to the closest position that is still allowed
                {
                    pos.y+=0.1;
                }
            }
            break;
        case 1:
            pos.y += (spd)*time;
            if (!checkMove(pos, gamemap, this))
            {
                while (!checkMove(pos, gamemap, this))
                {
                    pos.y-=0.1;
                }
            }
            break;
        case 2:
            pos.x +=(-spd)*time;
            if (!checkMove(pos, gamemap, this))
            {
                while (!checkMove(pos, gamemap, this))
                {
                    pos.x+=0.1;
                }
            }
            break;
        case 3:
            pos.x += (spd)*time;
            if (!checkMove(pos, gamemap, this))
            {
                while (!checkMove(pos, gamemap, this))
                {
                    pos.x-=0.1;
                }
            }
            break;
        default:
            break;
    }
}

void Being::kill()
{
    isAlive = false;
}
