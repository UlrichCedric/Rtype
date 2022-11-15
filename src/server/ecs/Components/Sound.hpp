#pragma once

#include "../IComponent.hpp"
#include "../constants.hpp"


/** Sound
 *@path of the sound file
 */
class Sound: public IComponent {
    public:

    Sound(std::string path = "NONE"): _path(path) {  }
    Sound(Sound &s): _path(s._path) {  }

    void setSound(std::string path = "NONE") { _path = path == "NONE" ? _path : path; }
    std::string getPath(void) { return _path; }
    std::string getName(void) override { return "sound"; }
    components getEnum(void) override { return SOUND; }

    ~Sound() override = default;

    private:
    std::string _path;
};