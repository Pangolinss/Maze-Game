#ifndef GAMEMAP_H
#define GAMEMAP_H
#define MAP_SIZE 31
#include"Tile.h"
#include<iostream>
#include<Maze.h>

class Being;
class Player;
class GameEvent;
extern sf::Texture tex[20];

class GameMap
{
    public:
        GameMap();
        GameMap(Tile[]);
        virtual ~GameMap();

        //get and set functions
        int getLayer1(int i, int j){return layer1[i][j];}
        int getLayer2(int i, int j){return layer2[i][j];}
        sf::Sprite& getExitSprite(){return exit;}

        void setLayer1(int i, int j, int k){layer1[i][j] = k;}
        void setLayer2(int i, int j, int k){layer2[i][j] = k;}

        void setPos(sf::Vector2f);
        void setTileList(Tile[]);

        friend bool checkMove(sf::Vector2f, GameMap*, Being*);//checks if a given move was valid

        void makeMapA();//a basic map for testing
        void makeMapMaze();//maze
        void drawMap(sf::RenderWindow&, sf::Event&, void (*createTileList)(Tile[]));//draws the map, but like weird, i don't use this one
        void drawMap(sf::RenderWindow&, sf::Event&, sf::Shader*);//draws the map
        void loadGameEvents(GameEvent*[]);//not used, supposed to load "map" based events
        void checkPlayerKey(Player*);//checks if the player has a key
    protected:

    private:
        int layer1[MAP_SIZE][MAP_SIZE];//layer 1, tiles and stuff
        int layer2[MAP_SIZE][MAP_SIZE];//layer 2, not tiles, but drawn on the map still
        Tile tileList[20];//list of tiles
        sf::Vector2f pos;//player pos
        sf::Sprite exit;//exit sprite
};

#endif // GAMEMAP_H
