#include <iostream>
#include "SFML/Graphics.hpp"

 class Button : public sf::Text {
    public:
        Button(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position)
                : sf::Text(text, font, characterSize) {
            setPosition(position);
        }
    };



