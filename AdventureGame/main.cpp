#include<SFML/Graphics.hpp>
#define FRAMERATE_LIMIT 60
#include<fstream>
#include"Player.h"
#include"Projectile.h"
#include"Monster.h"
#include"GameMap.h"
#include"GameEvent.h"
#include"Menu.h"
#include"MazeSolver.h"

bool checkMove(sf::Vector2f, GameMap*, Player*);
std::string getShaderFile(std::string);

sf::Texture tex[20];//texutres are costly, so they are global, also each texture is for a specific sprite
Projectile* proj[MAX_PROJ];//don't want to pass this all the time
sf::RenderWindow window(sf::VideoMode(1600,1600), "Adventure Maze Game");//window is costly
sf::Shader shader;//

int main()
{
    srand(time(NULL));
    int inGame = 0;//variable for menu
    bool won = false;

    Menu menu;

    Items* itemList[NUM_ITEMS];//a list of items, which i dont actually use
    createItemList(itemList);//makes all of the items
    Player player(tex[9], &itemList);

    Monster* ghosts[NUM_GHOSTS];                            for (int i = 0; i<NUM_GHOSTS; i++){ghosts[i] = nullptr;}//sets ghost to null
                                                            for (int i = 0; i<MAX_PROJ; i++) {proj[i] = nullptr;}//sets projectiles to null

    GameMap* gamemap;
    Tile tilelist[100];
    GameEvent* gameEvent[NUM_EVENTS];                       for (int i = 0; i<NUM_EVENTS; i++){gameEvent[i]=nullptr;}//sets events to null

    sf::Clock clock;
    sf::Event event;
    sf::View view(sf::Vector2f(0.f,0.f), sf::Vector2f(600.f,360.f));
    gamemap = new GameMap;

    view.setViewport(sf::FloatRect(0, 0, 1, 0.6f));//basically setting the view for the game
    view.setCenter(240.f,240.f);
    view.zoom(0.75f);

    window.setView(view);
    window.setFramerateLimit(FRAMERATE_LIMIT);

    if (!shader.loadFromMemory(getShaderFile("shader.frag"), sf::Shader::Fragment))//loads the shader
    {
        std::cout<<"Computer does not support Fragment shader"<<std::endl;
        return 1;
    }

    gamemap->makeMapMaze();//makes the maze
    createTileListA(tilelist);
    loadTextures(tilelist);


    while (window.isOpen()) //game loop
    {
        gamemap->setPos(player.getPos());
        while (window.pollEvent(event))//checks inputs
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }
        if (inGame == 0)//basic menu
        {
            window.clear();
            inGame = menu.makeMenu();
        }
        if (inGame == 1)//in the actual game
        {
            if (player.endGame(gamemap) || won == true)//win screen
            {
                menu.wonMenu(view);
                won = true;
            }
            else if(!player.getAlive())//death screen
            {
                menu.deathMenu(view);
            }
            else
            {
                //Check Events
                manageEvents(gameEvent, gamemap, &player, event);//goes through each event and checks them
                gamemap->checkPlayerKey(&player);//checks if the player has a key
                //drawing the window and movement
                float time = clock.restart().asSeconds();//clock for movement
                player.movement(event, time, gamemap);//moving
                player.fire(event, proj, tex[2]);//shooting
                player.monsterHitBox(ghosts, NUM_GHOSTS);

                spawnGhosts(ghosts);//spawns the spooky ghosts

                window.clear();
                gamemap->setTileList(tilelist);//sets the tilelist for the map, in the loop cause in a better game, you would change tiles sometimes
                gamemap->drawMap(window, event, &shader);//draws the map
                drawEvents(gameEvent);//draws the events
                player.renderMovement(window, view);//actually draw movement
                manageGhosts(ghosts, &player, time);//moves ghosts
                for (int i = 0; i<MAX_PROJ; i++)
                {
                    if (proj[i] != nullptr)
                    {
                        proj[i]->movement(time, gamemap);//shoots stuff
                        proj[i]->renderMovement(window);//draws shooting
                        proj[i]->destroyProjectile(gamemap);//checks if the projectile hit something
                    }
                }
                deleteProjectile(proj);//deletes destroyed projectiles
                deleteGhosts(ghosts, gameEvent);//deletes killed ghosts
                deleteEvents(gameEvent);//deletes activated events
            }
        }
        window.display();
        if (inGame == 2)
        {
            window.close();//autosolver
            Maze maze;
            maze.generateMaze();
            maze.makeMazeInteresting();
            MazeSolver m(&maze);
            m.solveMazeWrapper();
        }
    }
    return 0;
}


std::string getShaderFile(std::string fileName)//shader requires to be a string, so i open the file and turn it into a string
{
    std::ifstream inFile;
    inFile.open(fileName);
    std::string buffer;
    std::string s = "";
    while (getline(inFile, buffer))
    {
        s +=buffer;
        s+="\n";
    }
    return s;
}
