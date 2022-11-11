/*
** EPITECH PROJECT, 2022
** Rtype [WSL : Ubuntu]
** File description:
** Initialisations
*/

#include "Menu.hpp"

void Menu::Menu::initMenu()
{
    _menu_select = MULTIPLAYER_SELECTION;
    _menu_title.setTexture(Game::Config::ExecutablePath + "assets/menu/sprites/R-TYPE_title.png");
    _menu_title.setPos(15, 430);
    // Load Fonts
    _menu_text_bottom_right = Game::Text("assets/menu/fonts/r-type.ttf");
    _menu_text_multiplayer = Game::Text("assets/menu/fonts/r-type.ttf");
    _menu_text_settings = Game::Text("assets/menu/fonts/r-type.ttf");
    _menu_text_top_right01 = Game::Text("assets/menu/fonts/r-type.ttf");
    _menu_text_top_right02 = Game::Text("assets/menu/fonts/r-type.ttf");
    _menu_text_quit = Game::Text("assets/menu/fonts/r-type.ttf");
    //_text_top_right01
    _menu_text_top_right01.SetText("BLAST OFF AND STRIKE");
    _menu_text_top_right01.setFontSize(20);
    _menu_text_top_right01.setPos(830, 15);
    //_text_top_right02
    _menu_text_top_right02.SetText("THE EVIL BYDO EMPIRE!");
    _menu_text_top_right02.setFontSize(20);
    _menu_text_top_right02.setPos(830, 45);
    //_text_multiplayer
    _menu_text_multiplayer.SetText("MULTIPLAYER");
    _menu_text_multiplayer.setFontSize(30);
    _menu_text_multiplayer.setFontColor(sf::Color::Black);
    _menu_text_multiplayer.setFontStyle(sf::Text::Bold);
    _menu_text_multiplayer.setPos(920, 180);
    //_text_settings
    _menu_text_settings.SetText("SETTINGS");
    _menu_text_settings.setFontSize(30);
    _menu_text_settings.setPos(995, 270);
    //_text_quit
    _menu_text_quit.SetText("QUIT");
    _menu_text_quit.setFontSize(30);
    _menu_text_quit.setPos(995, 360);
    //_text_bottom_right
    _menu_text_bottom_right.SetText("Epitech project 2022");
    _menu_text_bottom_right.setFontSize(20);
    _menu_text_bottom_right.setPos(835, 670);
    //_rect_selection
    _menu_rect_selection.setTexture(Game::Config::ExecutablePath + "assets/menu/sprites/white_rect.jpg");
    _menu_rect_selection.setRect(0, 0, 360, 56);
    _menu_rect_selection.setPos(910, 170);
}

void Menu::Menu::initLobby()
{
    _lobby_select = _selection_possibility_lobby::CREATE_A_LOBBY;

    // Load Fonts
    _lobby_title = Game::Text("assets/menu/fonts/r-type.ttf");
    _lobby_create = Game::Text("assets/menu/fonts/r-type.ttf");
    _game_name_title = Game::Text("assets/menu/fonts/r-type.ttf");
    //_lobby_title
    _lobby_title.SetText("Multiplayer");
    _lobby_title.setFontSize(50);
    _lobby_title.setFontStyle(sf::Text::Bold);
    _lobby_title.setPos(80, 60);
    //_lobby_create
    _lobby_create.SetText("Create a lobby");
    _lobby_create.setFontSize(25);
    _lobby_create.setFontColor(sf::Color::Black);
    _lobby_create.setFontStyle(sf::Text::Bold);
    _lobby_create.setPos(220, 155);
    //_lobby_refresh_icon
    _lobby_refresh_icon.setTexture(Game::Config::ExecutablePath + "assets/menu/sprites/refresh_icon.png");
    _lobby_refresh_icon.setPos(1020, 155);
    //_lobby_box_list
    _lobby_box_list.setSize(sf::Vector2f(850, 450));
    _lobby_box_list.setOutlineColor(sf::Color::White);
    _lobby_box_list.setOutlineThickness(2);
    _lobby_box_list.setFillColor(sf::Color(0, 0, 0, 150));
    _lobby_box_list.setPosition(210, 200);
    //_lobby_rect_selection
    _lobby_rect_selection.setTexture(Game::Config::ExecutablePath + "assets/menu/sprites/white_rect.jpg");
    _lobby_rect_selection.setRect(0, 0, 385, 45);
    _lobby_rect_selection.setPos(210, 145);
    //_lobby_box_selection
    _lobby_box_selection.setSize(sf::Vector2f(840, 80));
    _lobby_box_selection.setOutlineColor(sf::Color::White);
    _lobby_box_selection.setOutlineThickness(10);
    _lobby_box_selection.setFillColor(sf::Color::Transparent);
    _lobby_box_selection.setPosition(215, 205);
    //Create a lobby
    _create_lobby_modal_alpha.setSize(sf::Vector2f(1280, 720));
    _create_lobby_modal_alpha.setFillColor(sf::Color(0, 0, 0, 200));
    _create_lobby_modal.setSize(sf::Vector2f(680, 380));
    _create_lobby_modal.setFillColor(sf::Color(0, 0, 0, 255));
    _create_lobby_modal.setPosition(300, 170);
    _create_lobby_modal.setOutlineColor(sf::Color::White);
    _create_lobby_modal.setOutlineThickness(6);
    //_game_name_text_box
    _game_name_text_box.init(14, sf::Color::White, false);
    _game_name_text_box.setLimit(true, 32);
    _game_name_text_box.setFont("assets/menu/fonts/r-type.ttf");
    _game_name_text_box.setPosition(sf::Vector2f(400, 270));
    //_game_name_title
    _game_name_title.SetText("Give a name to your game lobby");
    _game_name_title.setFontSize(16);
    _game_name_title.setFontColor(sf::Color::White);
    _game_name_title.setPos(380, 220);
    //_validate_create_lobby_button
    _validate_create_lobby_button.setColorRect(Button::COLOR_CODE::BLACK, Button::COLOR_CODE::WHITE, 2.0f);
    _validate_create_lobby_button.setFont("assets/menu/fonts/r-type.ttf");
    _validate_create_lobby_button.setText("Create");
    _validate_create_lobby_button.setFontSize(16);
    _validate_create_lobby_button.setFontColor(sf::Color::White);
    _validate_create_lobby_button.setFontStyle(sf::Text::Bold);
    _validate_create_lobby_button.setPos(580, 405);
    // edit icon
    _edit_icon_game_name.setTexture(Game::Config::ExecutablePath + "assets/menu/sprites/editer.png");
    _edit_icon_game_name.setScale(0.6, 0.6);
    _edit_icon_game_name.setColor(sf::Color::Black);
    _edit_icon_game_name.setPos(905, 255);
    //_rect_select_create_lobby_modal
    _rect_select_create_lobby_modal.setSize(sf::Vector2f(48, 48));
    _rect_select_create_lobby_modal.setFillColor(sf::Color::White);
    _rect_select_create_lobby_modal.setPosition(900, 252);
    // init var selection
    _create_lobby_modal_select = _selection_possibility_create_lobby_modal::GAME_NAME;
}

void Menu::Menu::initSettings()
{
    _settings_select = MUSIC_VOLUME_TITLE;

    //_rect_selection
    _settings_rect_selection.setTexture(Game::Config::ExecutablePath + "assets/menu/sprites/white_rect.jpg");
    _settings_rect_selection.setRect(0, 0, 390, 45);
    _settings_rect_selection.setPos(130, 175);
    //fonts
    _settings_title = Game::Text("assets/menu/fonts/r-type.ttf");
    _settings_music_volume = Game::Text("assets/menu/fonts/r-type.ttf");
    _settings_sonds_volume = Game::Text("assets/menu/fonts/r-type.ttf");
    _settings_fps = Game::Text("assets/menu/fonts/r-type.ttf");
    //_settings_title
    _settings_title.SetText("Settings");
    _settings_title.setFontSize(50);
    _settings_title.setFontStyle(sf::Text::Bold);
    _settings_title.setPos(80, 60);
    //_settings_volume_music
    _settings_music_volume.SetText("Music Volume");
    _settings_music_volume.setFontSize(30);
    _settings_music_volume.setFontColor(sf::Color::Black);
    _settings_music_volume.setFontStyle(sf::Text::Bold);
    _settings_music_volume.setPos(140, 180);
    //_settings_sonds_volume
    _settings_sonds_volume.SetText("Sonds Volume");
    _settings_sonds_volume.setFontSize(30);
    _settings_sonds_volume.setPos(140, 320);

    //music volume bar
    _settings_music_volume_bar.setSize(sf::Vector2f(875, 50));
    _settings_music_volume_bar.setOutlineColor(sf::Color::White);
    _settings_music_volume_bar.setOutlineThickness(2);
    _settings_music_volume_bar.setFillColor(sf::Color::Black);
    _settings_music_volume_bar.setPosition(160, 230);
    _settings_music_volume_progression_bar.setSize(sf::Vector2f((869 * (_music_volume / 100)), 44));
    _settings_music_volume_progression_bar.setFillColor(sf::Color(236, 236, 236));
    _settings_music_volume_progression_bar.setPosition(163, 233);
    //sonds volume bar
    _settings_sounds_volume_bar.setSize(sf::Vector2f(875, 50));
    _settings_sounds_volume_bar.setOutlineColor(sf::Color::White);
    _settings_sounds_volume_bar.setOutlineThickness(2);
    _settings_sounds_volume_bar.setFillColor(sf::Color::Black);
    _settings_sounds_volume_bar.setPosition(160, 370);
    _settings_sounds_volume_progression_bar.setSize(sf::Vector2f((869 * (_sounds_volume / 100)), 44));
    _settings_sounds_volume_progression_bar.setFillColor(sf::Color(236, 236, 236));
    _settings_sounds_volume_progression_bar.setPosition(163, 373);

    //fps selector
    _settings_fps.setFontSize(30);
    _settings_fps.setFontColor(sf::Color::Black);
    _settings_fps.setFontStyle(sf::Text::Bold);
    _settings_fps.setPos(140, 460);
    _fps = {30, 60, 144};
    _fps_index = 1;
    _settings_fps.SetText("FPS set to " + std::to_string(_fps[_fps_index]));
}

