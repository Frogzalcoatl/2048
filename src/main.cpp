#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);
    const sf::Font font("./assets/fonts/DejaVuSans.ttf");
    string str = "Big Butts";
    sf::Text text(font, str, 50);
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        window.clear();
        window.draw(text);
        window.display();
    }
}
