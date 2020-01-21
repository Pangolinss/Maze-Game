#include "Tile.h"

Tile::Tile()
{
    //ctor
    pass = true;
    sprite_name ="";
    tile_id = 0;
}

Tile::Tile(bool a, std::string b, int c)
{
    pass = a; sprite_name = b; tile_id = c;
}

Tile::~Tile()
{
    //dtor
}

void Tile::drawTile(float x, float y, sf::RenderWindow& window, sf::Texture* texture, sf::Shader* shader, sf::Vector2f vec)//draws a tile
{
    sprite.setTexture(*texture);
    sprite.setPosition(sf::Vector2f(x,y));
    sprite.setScale(1.f,1.f);
    shader->setUniform("texture", sf::Shader::CurrentTexture);
    window.draw(sprite, shader);
}

void Tile::operator=(Tile tile)//operator to make equality
{
    pass = tile.pass;
    sprite_name = tile.sprite_name;
    tile_id = tile.tile_id;
}

void createTileListA(Tile tileList[])
{
    Tile* tile = new Tile(true, "bin//release//common//Textures//dirt.png", 0);
    tileList[0] = *tile;
    delete tile;
    tile = new Tile(false, "bin//release//common//Textures//stone.png", 1);
    tileList[1] = *tile;
    delete tile;


}

void loadTextures(Tile tilelist[])
{
    for (int i = 0; i<20; i++)
    {
        if (tilelist[i].sprite_name != "")
        {
            tex[i].loadFromFile(tilelist[i].sprite_name);
        }
    }
}
