#ifndef MENU_H
#define MENU_H
#include<SFML/Graphics.hpp>
#include<iostream>

extern sf::RenderWindow window;

class Menu
{
    public:
        Menu();
        virtual ~Menu();
        int makeMenu();//main menu
        void wonMenu(sf::View&);
        void deathMenu(sf::View&);

    private:
        sf::Font font;

};

#endif // MENU_H
