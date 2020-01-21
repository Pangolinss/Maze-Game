#include "Menu.h"

Menu::Menu()
{
    //ctor
    if (!font.loadFromFile("bin\\Release\\common\\Fonts\\Latchboy.ttf"));
    {
        std::cout<<"Unable to load font"<<std::endl;
    }
}

Menu::~Menu()
{
    //dtor
}

int Menu::makeMenu()
{

    sf::Text title;
    sf::Text play;
    sf::Text autosolve;
    sf::Mouse mouse;
    title.setFont(font);
    title.setString("A Very Friendly Maze");
    title.setColor(sf::Color::Red);
    title.setCharacterSize(60);
    title.setPosition(80,240);

    play.setFont(font);
    play.setString("Play");
    play.setColor(sf::Color::White);
    play.setCharacterSize(30);
    play.setPosition(100,320);

    autosolve.setFont(font);
    autosolve.setString("Autosolve");
    autosolve.setColor(sf::Color::White);
    autosolve.setCharacterSize(30);
    autosolve.setPosition(300,320);

    window.draw(title);
    window.draw(play);
    window.draw(autosolve);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))//buttons to click stuff
    {
        sf::Vector2f vec = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (autosolve.getGlobalBounds().contains(vec))
        {
            return 2;
        }
        if (play.getGlobalBounds().contains(vec))
        {
            return 1;
        }
    }
    return 0;
}

void Menu::wonMenu(sf::View& view)
{
    view.setCenter(0,0);
    window.setView(view);
    window.clear();
    sf::Text text;
    text.setFont(font);
    text.setString("You Won");
    text.setColor(sf::Color::Yellow);
    text.setCharacterSize(60);
    text.setPosition(-100,0);
    window.draw(text);
}

void Menu::deathMenu(sf::View& view)
{
    view.setCenter(0,0);
    window.setView(view);
    window.clear();
    sf::Text text;
    text.setFont(font);
    text.setString("You Died");
    text.setColor(sf::Color::Red);
    text.setCharacterSize(60);
    text.setPosition(-100,0);
    window.draw(text);
}
