#include "Player.h"
#define SPEED 200
Player::Player()
{
    //ctor
    sprite.setPosition(64,64);
    pos.x = SPAWN_X; pos.y = SPAWN_Y;
}

Player::Player(sf::Texture& texture, Items* (*_itemList)[NUM_ITEMS])
{
    pos.x = SPAWN_X; pos.y = SPAWN_Y;
    texture.loadFromFile("bin//release//common//being//ladybug_sprite.png");
    sprite.setTexture(texture);
    //p_sprite.setSize(sf::Vector2f(32.f,32.f));
    sprite.setScale(1.f,1.f);
    pos.x = SPAWN_X; pos.y = SPAWN_Y;
    sprite.setPosition(pos.x,pos.y);
    spd = 200;
    inventroy = new Inventory(5, _itemList);
    isAlive = true;
    hasKey = false;
}

Player::~Player()
{
    //dtor
}


void Player::movement(sf::Event& event, float time, GameMap* gamemap)//sets movement based off keyboard inputs
{
    move_dir = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){move_dir = 0; dir = 0;}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){move_dir = 1; dir = 1;}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){move_dir = 2; dir = 2;}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){move_dir = 3; dir = 3;}
    Being::movement(time, gamemap);
}

void Player::renderMovement(sf::RenderWindow& window, sf::View& view)
{
    sprite.setPosition(pos);
    view.setCenter(pos);
    window.draw(sprite);
    window.setView(view);
}

void Player::fire(sf::Event& event, Projectile* proj[MAX_PROJ], sf::Texture& texture)//creates a new projectile if you press a key
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        for (int i = 0; i<MAX_PROJ; i++)
        {
            if (proj[i] == nullptr)
            {
                proj[i] = new Projectile("bin//release//common//being//ladybug_sprite.png", 300, dir, pos, 0, texture);
            }
        }
    }
}

void Player::monsterHitBox(Monster* monsterArray[], int s)//checks hitboxes of monsters
{
    for (int i = 0; i<s; i++)
    {
        if (monsterArray[i] != nullptr)
        {
            if (monsterArray[i]->getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds()))
            {
                kill();
            }
        }
    }
}

bool Player::endGame(GameMap* gamemap)//checks if you are touching the exit portal
{
    return (gamemap->getExitSprite().getGlobalBounds().intersects(sprite.getGlobalBounds()));
}

