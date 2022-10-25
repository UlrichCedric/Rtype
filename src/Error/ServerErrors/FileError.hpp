#pragma once

#include "../ServerError.hpp"

class FileError: public ServerError {
    public:
    FileError(): _value("error opening file") {  }
    const char *what(void) const noexcept { return _value.c_str(); }
    ~FileError() {  }

    private:
    std::string _value;
};