#include <fstream>
#include "SFML/Graphics.hpp"
#include "StartMenu.h"
#include "Button.h"
#include "../Typer/MonkeyTyper.h"

auto start() -> void{
    using namespace std;
    using namespace sf;

    vector<Vector2f> buttonPositions = {
            Vector2f(50, 100),
            Vector2f(50, 200),
            Vector2f(50, 300),
            Vector2f(50, 400),
            Vector2f(350, 100),
            Vector2f(350, 200),
            Vector2f(350, 300),
            Vector2f(350, 400),
            Vector2f(600, 100),
            Vector2f(600, 200),
            Vector2f(600, 300),
            Vector2f(600, 400)
    };

    vector<string> buttonTexts = {
            "Slow",
            "Medium",
            "Fast",
            "Insane",
            "Arial",
            "Sans",
            "Harlowsi",
            "InkFree",
            "2 letters",
            "3 letters",
            "4 letters",
            "5 letters"
    };

    Font font;
    if (!font.loadFromFile("assets/ebrima.ttf")) {
        return;
    }

    vector<Button> buttonText;
    for (size_t i = 0; i < buttonPositions.size(); ++i) {
        auto text = Button(buttonTexts[i], font, 24, buttonPositions[i]);
        buttonText.push_back(text);
    }

    auto window = RenderWindow(
            VideoMode({800, 600}), "Start Menu",
            Style::Close, ContextSettings(0, 0, 8)
    );

    auto startButtonText = Button("Start", font, 24, Vector2f(350,500));
    buttonText.push_back(startButtonText);
    auto modeText = Button("Mode", font, 24, Vector2f(50, 10));
    auto fontText = Button("Font", font, 24, Vector2f(350, 10));
    auto lettersText = Button("Letters", font, 24, Vector2f(600, 10));
    auto modes = vector<Button>{modeText, fontText, lettersText};
    auto settings = vector<string>{"Slow", "Arial", "2 letters"};
    auto file = fstream("assets/settings.txt");
    auto scoreFile = fstream("assets/scores.txt");
    auto bestScore = 0;
    scoreFile >> bestScore;
    auto bestScoreText = Button("Best Score: " + to_string(bestScore), font, 24, Vector2f(50, 500));
    while (window.isOpen()) {
        auto mousePosition = Mouse::getPosition(window);
        auto event = Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            for (auto i = 0; i < buttonText.size(); i++){
                auto isHovered = buttonText[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y);
                if(isHovered){
                    buttonText[i].setFillColor(Color::Green);
                    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left){
                        auto buttonName = buttonText[i].getString();
                        auto mode = buttonName == "Slow"|| buttonName == "Medium" || buttonName == "Fast" || buttonName == "Insane";
                        auto fontM = buttonName == "Arial" || buttonName == "Harlowsi" || buttonName == "Sans" || buttonName == "InkFree";
                        auto letters = buttonName == "2 letters" || buttonName == "3 letters" || buttonName == "4 letters" || buttonName == "5 letters";
                        if (buttonName == "Start"){
                            for (auto s : settings) {
                                file << s << endl;
                            }
                            window.close();
                            configureTyper();
                        }
                        if (mode){
                            cout << std::string(buttonName) + "\n" ;
                            settings[0] = buttonName;
                        }
                        if(fontM){
                            cout << std::string(buttonName) + "\n" ;
                            settings[1] = buttonName;
                        }
                        if(letters){
                            cout << std::string(buttonName) + "\n" ;
                            settings[2] = buttonName;
                        }
                    }
                }
                if(!isHovered){
                    buttonText[i].setFillColor(Color::White);
                }
            };
        }
        window.clear();
        for (auto b: buttonText){
            window.draw(b);
        }
        for (auto m: modes){
            window.draw(m);
        }
        window.draw(bestScoreText);
        window.display();
    }
    window.close();
}
