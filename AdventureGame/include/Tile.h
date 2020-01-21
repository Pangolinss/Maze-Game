#ifndef TILE_H
#define TILE_H
#include<string>
#include"SFML/Graphics.hpp"

extern sf::Texture tex[20];

class GameMap;
class Tile //Each tile is 32x32 box
{
    public:
        Tile();
        Tile(bool, std::string, int);
        virtual ~Tile();
        //get and set methods
        bool getPass(){return pass;}
        std::string getSpriteName(){return sprite_name;}
        int GetTileId(){return tile_id;}
        sf::Sprite& getSprite(){return sprite;}

        //draws a tile
        void drawTile(float x, float y, sf::RenderWindow& window, sf::Texture* texture, sf::Shader*, sf::Vector2f);
        void operator=(Tile);

        //this creates arrays of tiles
        friend void createTileListA(Tile[]);
        friend void loadTextures(Tile[]);

    protected:

    private:
        bool pass;//can you walk through it
        std::string sprite_name;
        int tile_id;//numeric value of tile
        sf::Sprite sprite;//sprite
        friend class GameMap;
};

#endif // TILE_H
