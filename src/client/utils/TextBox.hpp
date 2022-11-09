/*
** EPITECH PROJECT, 2022
** Rtype [WSL : Ubuntu]
** File description:
** InputField
*/

#ifndef INPUTFIELD_HPP_
#define INPUTFIELD_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Config.hpp"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class TextBox {
    public:
        TextBox() {};
        ~TextBox() {};

        void init(int size, sf::Color color, bool sel) {
            textbox.setCharacterSize(size);
            textbox.setColor(color);
            isSelected = sel;
            if (sel) {
                textbox.setString("_");
            } else {
                textbox.setString("");
            }
        }

        void setFont(std::string path) {
            _font.loadFromFile(Game::Config::ExecutablePath + path);
            textbox.setFont(_font);
            _data = sf::String("");
            textbox = sf::Text(_data, _font, 50);
        }

        void setPosition(sf::Vector2f pos) {
            textbox.setPosition(pos);
        }

        void setLimit(bool ToF) {
            hasLimit = ToF;
        }

        void setLimit(bool ToF, int lim) {
            hasLimit = ToF;
            limit = lim;
        }

        void setSelected(bool sel) {
            isSelected = sel;
            if (!sel) {
                std::string t = text.str();
                std::string newT = "";
                for (int i = 0; i < t.length(); i++) {
                    newT += t[i];
                }
                textbox.setString(newT);
            }
        }

        std::string getText() {
            return text.str();
        }

        void drawTo(sf::RenderWindow &window) {
            textbox.setString(text.str() + "");
            window.draw(textbox);
        }

        void typedOn(sf::Event input) {
            if (isSelected) {
                int charTyped = input.text.unicode;
                if (charTyped < 128) {
                    if (hasLimit) {
                        if (text.str().length() <= limit) {
                            inputLogic(charTyped);
                        } else if (text.str().length() > limit && charTyped == DELETE_KEY) {
                            deleteLastChar();
                        }
                    } else {
                        inputLogic(charTyped);
                    }
                }
            }
        }

    protected:
    private:
    sf::Text textbox;
    std::ostringstream text;
    bool isSelected = false;
    bool hasLimit = false;
    int limit;
    sf::Font _font;
    sf::String _data;


    void inputLogic(int charTyped) {
        if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
            text << static_cast<char>(charTyped);
        } else if (charTyped == DELETE_KEY) {
            if (text.str().length() > 0) {
                deleteLastChar();
            }
        }
    }

    void deleteLastChar() {
        std::string t = text.str();
        std::string newT = "";
        for (int i = 0; i < t.length() - 1; i++) {
            newT += t[i];
        }
        text.str("");
        text << newT;

        textbox.setString(text.str());
    }
};

#endif /* !INPUTFIELD_HPP_ */
