#include "GameMap.h"
#include "Being.h"
#include "Player.h"
#include"GameEvent.h"

void unlockDoor(GameEvent*, GameMap*, Player*);
bool hasItem(GameEvent*, int[2], Player*, sf::Event&);

GameMap::GameMap()
{
    //ctor
    for (int i = 0; i<MAP_SIZE; i++)
    {
        for (int j = 0; j<MAP_SIZE; j++)
        {
            layer1[i][j] = 0;
            layer2[i][j] = 0;
        }
    }
}

GameMap::GameMap(Tile _t[])
{
    for (int i = 0; i<20; i++)
    {
        tileList[i] = _t[i];
    }
}

GameMap::~GameMap()
{
    //dtor
}

void GameMap::setPos(sf::Vector2f _p)
{
    pos = _p;
}

void GameMap::setTileList(Tile t[])
{
    for (int i = 0; i<20; i++)
    {
        tileList[i] = t[i];
    }
}

bool checkMove(sf::Vector2f vec, GameMap* gamemap, Being* player)
{
    int x, y;
    x = (vec.x)/32;
    y = (vec.y)/32;//essentiall my function calculates the position of the furthers corner of its sprite and checks if that is about to bump into an unpassable tile
    if (x<0 || y<0 || x>MAP_SIZE || y>MAP_SIZE)
    {
        return false;
    }
    if (player->getDir()==0 || player->getDir()==2)//example if a player is going down or right, it checks the bottom right pixel and sees if its in an unpassable tile
    {

        if(!gamemap->tileList[gamemap->layer1[x][y]].getPass())
        {
            return false;
        }
    }
    x=(vec.x+25)/32;
    y=(vec.y)/32;
    if (x<0 || y<0 || x>MAP_SIZE || y>MAP_SIZE)
    {
        return false;
    }
    if (player->getDir()==0 || player->getDir()==3)
    {
        if (!gamemap->tileList[gamemap->layer1[x][y]].getPass())
        {
            return false;
        }
    }
    x=(vec.x)/32;
    y=(vec.y+25)/32;
    if (x<0 || y<0 || x>MAP_SIZE || y>MAP_SIZE)
    {
        return false;
    }
    if (player->getDir()==1 || player->getDir() == 2)
    {
        if (!gamemap->tileList[gamemap->layer1[x][y]].getPass())
        {
            return false;
        }
    }
    x=(vec.x+25)/32;
    y=(vec.y+25)/32;
    if (x<0 || y<0 || x>MAP_SIZE || y>MAP_SIZE)
    {
        return false;
    }
    if (player->getDir()==1 || player->getDir() == 3)
    {
        if (!gamemap->tileList[gamemap->layer1[x][y]].getPass())
        {
            return false;
        }
    }
    return true;//returns true if allowed
}

void GameMap::makeMapA()
{
    for (int i = 0; i<MAP_SIZE; i++)
    {
        for (int j = 0; j<MAP_SIZE; j++)
        {
            if (i == 0 || j == 0 || i == MAP_SIZE-1 || j == MAP_SIZE-1)
            {
                layer1[i][j] = 1;
            }
            else {layer1[i][j] = 0;}
            if ((i+j)%6 == 1)
            {
                layer1[i][j] = 1;
            }
        }
    }
}

void GameMap::makeMapMaze()//makes a maze, 2 is a lock
{
    Maze maze;
    maze.generateMaze();
    maze.giveMazeDoors();
    maze.makeMazeArr(layer1);
    for (int i = 0; i<MAP_SIZE; i++)
    {
        for (int j = 0; j<MAP_SIZE; j++)
        {
            if (layer1[i][j] == 2)
            {
                layer1[i][j] = 1;
                layer2[i][j] = 2;
            }
        }
    }
}

void GameMap::drawMap(sf::RenderWindow& window, sf::Event& event, sf::Shader* shader) //A tile is a 32x32 square
{
    sf::Texture* t;
    for (int i = 0; i<MAP_SIZE; i++)
    {
        for (int j = 0; j<MAP_SIZE; j++)
        {
            t = &tex[layer1[i][j]];
            tileList[layer1[i][j]].drawTile(32*i, 32*j, window, t, shader, pos);//draws tiles
            if (layer2[i][j] == 2)
            {
                sf::Sprite s;
                tex[7].loadFromFile("bin\\Release\\common\\Textures\\lock.png");//draws locks
                s.setTexture(tex[7]);
                s.setPosition(32*i,32*j);
                window.draw(s, shader);
            }
            if (i == MAP_SIZE-2 && j == MAP_SIZE-2)
            {
                tex[8].loadFromFile("bin\\Release\\common\\Textures\\exit.png");//draws exit
                exit.setTexture(tex[8]);
                exit.setPosition(32*i, 32*j);
                window.draw(exit, shader);
            }
        }
    }
}

void GameMap::loadGameEvents(GameEvent* gameEvent[NUM_EVENTS])
{
    int k[NUM_EVENTS]; for(int i = 0; i<NUM_EVENTS; i++){k[i]=-1;}
    int n;
    for (int i = 0; i<NUM_EVENTS; i++)
    {
        if (gameEvent[NUM_EVENTS] == nullptr)
        {
            k[n++] = i;
        }
    }
    n = 0;
    for (int i = 0; i<MAP_SIZE; i++)
    {
        for (int j = 0; j<MAP_SIZE;  j++)
        {
            if (layer2[i][j] == 2)
            {
                gameEvent[n++] = new GameEvent(&hasItem, &unlockDoor, sf::Vector2f(32*i,32*j), "bin\\Release\\common\\Textures\\lock.png", tex[7]);
            }
        }
    }
}

void GameMap::checkPlayerKey(Player* player)//if player has a key it changes the locked stone tiles to dirt tiles, allowing the player to pass
{
    if (player->getKey())
    {
        for (int i = 0; i<MAP_SIZE; i++)
        {
            for (int j = 0; j<MAP_SIZE; j++)
            {
                if (layer2[i][j]==2)
                {
                    layer1[i][j] = 0;
                }
            }
        }
    }
}

