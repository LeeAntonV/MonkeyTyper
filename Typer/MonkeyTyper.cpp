#include <iostream>
#include <fstream>
#include "MonkeyTyper.h"
#include "../StartMenu/Button.h"
#include "../StartMenu/StartMenu.h"

auto words = std::vector<Button>{};
auto file = std::ifstream("assets/scores.txt");

auto MonkeyTyper(int speed, std::string fontStr, int bestScore) -> void {
    using namespace sf;
    using namespace std;

    auto score = 0;
    Font font;
    font.loadFromFile(fontStr);
    vector<Vector2f> wordPositions = {
            Vector2f(300, 30),
            Vector2f(600, 80),
            Vector2f(800, 100),
            Vector2f(1000, 120),
            Vector2f(1200, 40),
    };

    for (auto i = 0; i < wordPositions.size(); i++) {
        auto word = Button("word", font, 24, wordPositions[i]);
        words.push_back(word);
    }
    auto line = VertexArray(Lines, 2);
    line[0] = Vector2f(0, 730);
    line[1] = Vector2f(1500, 730);
    line[0].color = Color::Red;
    line[1].color = Color::Red;
    auto run = true;
    auto reloadText = Button("F1 - Reload", font, 24, Vector2f(1200, 790));
    auto pauseText = Button("F2 - Pause/Unpause", font, 24, Vector2f(1200, 850));
    auto exitText = Button("Esc - Exit", font, 24, Vector2f(1200, 910));
    auto window = RenderWindow(
            VideoMode({1500, 1100}), "Monkey Typer",
            Style::Close, ContextSettings(0, 0, 8)
    );

    string userInput;
    while (window.isOpen()) {
        auto event = Event();
        auto input = Button(userInput, font, 24, Vector2f(100, 790));
        auto scoreString = "   " + to_string(score);
        auto scoreText = Button("Score:\n" + scoreString, font, 24, Vector2f(1000, 790));
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                if (score > bestScore){
                    bestScore = score;
                }
                auto scores = vector<int>{bestScore, score};
                remove("assets/scores.txt");
                auto file1 = ofstream("assets/scores.txt");
                for (auto s: scores) {
                    file1 << s << endl;
                }
                userInput.clear();
                words.clear();
                window.close();
                start();
            } else if (event.type == Event::KeyPressed) {
                auto keyPressed = event.key.code;
                if (keyPressed == Keyboard::Escape){
                    if (score > bestScore){
                        bestScore = score;
                    }
                    auto scores = vector<int>{bestScore, score};
                    remove("assets/scores.txt");
                    auto file1 = ofstream("assets/scores.txt");
                    for (auto s: scores) {
                        file1 << s << endl;
                    }
                    userInput.clear();
                    words.clear();
                    window.close();
                    start();
                } else if ( keyPressed == Keyboard::F1){
                        words.clear();
                        window.close();
                        MonkeyTyper(speed, fontStr, bestScore);
                }else if (keyPressed == Keyboard::F2){
                    if (run) {
                        run = false;
                    } else {
                        run = true;
                    }
                }
            }
            if(run) {
                if (event.type == Event::TextEntered) {
                    userInput += event.text.unicode;
                } else if (event.key.code == Keyboard::BackSpace) {
                    userInput.pop_back();
                } else if (event.key.code == Keyboard::Enter) {
                    for (auto i = 0; i < words.size(); i++){
                        if (userInput == words[i].getString()){
                            score += 1;
                            words.erase(words.begin() + i);
                        }
                        userInput.clear();
                    }
                }
            }
        }
        window.clear();
        window.draw(line);
        window.draw(scoreText);
        window.draw(reloadText);
        window.draw(pauseText);
        window.draw(exitText);
        window.draw(input);
        if (run) {
            for (auto i = 0; i < words.size(); i++) {
                auto currentPosition = words[i].getPosition();
                if (currentPosition.y < 700) {
                    words[i].setPosition(currentPosition.x, currentPosition.y + speed);
                    window.draw(words[i]);
                } else {
                    run = false;
                    words[i].setFillColor(Color::Red);
                    break;
                }
            }
        } else {
            for (auto i = 0; i < words.size(); i++) {
                window.draw(words[i]);
            }
        }
        window.display();
        sleep(seconds(0.1));
    }
}

auto configureTyper() -> void{
    auto bestScore = 0;
    auto speed = 10;
    auto fontStr = "assets/arial.ttf";
    auto letters = "2 letters.txt";
    auto settings = std::fstream("assets/settings.txt");
    std::string line;
    while (getline(settings, line)) {
        if (line == "Medium") {
            speed = 20;
        } else if (line == "Fast") {
            speed = 30;
        } else if (line == "Insane") {
            speed = 80;
        } else if (line == "InkFree") {
            fontStr = "assets/Inkfree.ttf";
        } else if (line == "Sans") {
            fontStr = "comic.ttf";
        } else if (line == "Harlowsi") {
            fontStr = "assets/HARLOWSI.TTF";
        } else if (line == "3 letters") {
            letters = "3 letters.txt";
        } else if (line == "4 letters") {
            letters = "4 letters.txt";
        } else {
            letters = "5 letters.txt";
        }
        file.close();
    }
    MonkeyTyper(speed, fontStr, bestScore);
}