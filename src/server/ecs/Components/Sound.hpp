#pragma once

#include "../IComponent.hpp"
#include "../constants.hpp"


/** Sound
 *@path of the sound file
 */
class Sound: public IComponent {
    public:
    Sound(std::string path = "NONE"): _path(path) {  }
    void setSound(std::string path = "NONE") { _path = path == "NONE" ? _path : path; }
    std::string getPath(void) { return _path; }
    std::string getName(void) { return "sound"; }
    int getEnum(void) { return SOUND; }
    ~Sound() {  };

    private:
    std::string _path;
};