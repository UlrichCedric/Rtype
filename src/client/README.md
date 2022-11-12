<div align="center" id="top"> 
  <img src="./.github/app.gif" alt="B CPP 500 NCY 5 1 Rtype Marius Nowak" />

  &#xa0;

  <a href="https://bcpp500ncy51rtypemariusnowak.netlify.app">Demo</a>
</div>

<h1 align="center">B CPP 500 NCY 5 1 Rtype Marius Nowak</h1>

<p align="center">
  <img alt="Github top language" src="https://img.shields.io/github/languages/top/{{YOUR_GITHUB_USERNAME}}/b-cpp-500-ncy-5-1-rtype-marius-nowak?color=56BEB8">

  <img alt="Github language count" src="https://img.shields.io/github/languages/count/{{YOUR_GITHUB_USERNAME}}/b-cpp-500-ncy-5-1-rtype-marius-nowak?color=56BEB8">

  <img alt="Repository size" src="https://img.shields.io/github/repo-size/{{YOUR_GITHUB_USERNAME}}/b-cpp-500-ncy-5-1-rtype-marius-nowak?color=56BEB8">

  <img alt="License" src="https://img.shields.io/github/license/{{YOUR_GITHUB_USERNAME}}/b-cpp-500-ncy-5-1-rtype-marius-nowak?color=56BEB8">

  <img alt="Github issues" src="https://img.shields.io/github/issues/{{YOUR_GITHUB_USERNAME}}/b-cpp-500-ncy-5-1-rtype-marius-nowak?color=56BEB8" />

  <img alt="Github forks" src="https://img.shields.io/github/forks/{{YOUR_GITHUB_USERNAME}}/b-cpp-500-ncy-5-1-rtype-marius-nowak?color=56BEB8" />

  <img alt="Github stars" src="https://img.shields.io/github/stars/{{YOUR_GITHUB_USERNAME}}/b-cpp-500-ncy-5-1-rtype-marius-nowak?color=56BEB8" />
</p>

Status

<h4 align="center"> 
	🚧  B CPP 500 NCY 5 1 Rtype Marius Nowak 🚀 Under construction...  🚧
</h4> 

<hr>

<p align="center">
  <a href="#dart-about">About</a> &#xa0; | &#xa0; 
  <a href="#sparkles-features">Features</a> &#xa0; | &#xa0;
  <a href="#rocket-technologies">Technologies</a> &#xa0; | &#xa0;
  <a href="#white_check_mark-requirements">Requirements</a> &#xa0; | &#xa0;
  <a href="#checkered_flag-starting">Starting</a> &#xa0; | &#xa0;
  <a href="#memo-license">License</a> &#xa0; | &#xa0;
  <a href="https://github.com/{{YOUR_GITHUB_USERNAME}}" target="_blank">Author</a>
</p>

<br>

### The Player
An `Player` is an object who manage all player issuses.

Here is the prototype for an Player :
```c
  namespace Game {
    class Player {
        public:
            Player();
            ~Player();
            // set the player's position
            void setPos(float x, float y);

            // draw the player
            void draw(sf::RenderWindow &window);

            //update the life of the player
            void setLife(int life);

            //shoot a bullet
            void bullet_reset() { _shoot.setPos(_player.getPos().x + 33 , _player.getPos().y + 8);};

            //get the position of the player
            sf::Vector2f getPos() {_pos = _player.getPos(); return _pos;};

            //generate a sprite for the player
            Image _player;

            //Manage the health of the player
            Health _health;

            //the position of the player
            sf::Vector2f _pos;

            //is life
            int _life = 100;

            //the bullet
            Shoot _shoot;
    };
}
```
### The Config
An `config` is an object who check the path of the executable .

Here is the prototype for config :
```c
  namespace Config {
            //stock the path of the executable
            extern std::string  ExecutablePath;
            //get the path of the executable
            void initialize();
    };
```

### The Music
An `Music` is an object who manage the music .

Here is the prototype for Music :
```c
  class Music {
        public:
            Music();
            //play the music
            void play() { _music.play(); };
            //restart the music
            void replay() { _music.stop(); _music.play(); };
            //stop the music
            void stop() { _music.stop(); };
            //set to loop the music
            void isRepeatable(bool repeat) { _music.setLoop(repeat); };
            //set the volume of the music
            void setVolume(float volume) { _music.setVolume(volume); };
            ~Music() {};
        private:
            sf::Music _music;
            std::string path;
    };
```	
### The Image
An `Image` is an object who manage the texture for the sprite .

Here is the prototype for Image :
```c
  class Image {
        public:
            Image() {};
            //Set the texture of the sprite
            void setTexture(std::string  path);

            std::string &get_path() { return _path; }
            void set_path(std::string path) { _path = path; }
            //return the sprite
            sf::Sprite &get_sprite() { return _sprite; }
            //set the position of the sprite
            void setPos(float posX = 0, float posY = 0) { _sprite.setPosition(posX, posY); };
            //Set the scale of the sprite
            void setScale(float scaleX = 1, float scaleY = 1) { _sprite.setScale(scaleX, scaleY); };
            //return the position of the sprite
            sf::Vector2f getPos() { return _sprite.getPosition(); };
            //return the color of the sprite
            sf::Color getColor() { return _sprite.getColor(); };
            //set the color of the sprite
            void setColor(sf::Color color) { _sprite.setColor(color); };
            //set the rotation of the sprite
            void setRotation(float angle) { _sprite.setRotation(angle); };
            //set the rect of the sprite
            void setRect(int x, int y, int width, int height) { _sprite.setTextureRect(sf::IntRect(x, y, width, height)); };
            //Move the rect to animate the sprite
            void MoveRect(int x, int y, int width, int height) { _sprite.setTextureRect(sf::IntRect(x, y, width, height)); };
            ~Image() {};
```

### The Window
An `Window` is an object who run all the classes and communicate with the server .

Here is the prototype for Window :
```c
class Windows {
        public:
            Windows();
            //Do a loop to display the window
            void Loop(Client& client);
            //Draw the menu
            void Display_menu();
            //Draw the pause menu
            void Display_pause();
            //get the event of the menu
            void Events();
            //get the event of the game
            void Events_game();
            //get the event of the pause menu
            void Events_pause();
            //Check the input
            void handleKeyPressed(sf::Event& event);
            void handleKeyReleased(sf::Event& event);
            //init the window
            void init();
            ~Windows() {};
```

```c

## :memo: License ##

This project is under license from MIT. For more details, see the [LICENSE](LICENSE.md) file.


Made with :heart: by <a href="https://github.com/{{YOUR_GITHUB_USERNAME}}" target="_blank">{{YOUR_NAME}}</a>

&#xa0;

<a href="#top">Back to top</a>
