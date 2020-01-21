#include<SFML/Graphics.hpp>
extern sf::RenderWindow window;

int menu()
{
    sf::Font font;
    font.loadFromFile("bin\\Release\\common\\Fonts\\Latchboy.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("A Very Friendly Maze");
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::Red);
    window.draw(text);
}
