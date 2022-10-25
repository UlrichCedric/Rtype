#pragma once

#include "../ClientError.hpp"

class WindowCreationError: public ClientError {
    public:
    WindowCreationError(std::string str = "Error creating the window") { _str = str; }
    const char *what(void) noexcept { return _str.c_str(); }
    ~WindowCreationError() {}
};
