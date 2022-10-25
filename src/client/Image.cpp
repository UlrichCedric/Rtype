/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
** File description:
** Image
*/

#include "Image.hpp"

namespace Game {
	void Image::setTexture(std::string path)
	{
		_path = path;
		if (!_texture.loadFromFile(_path))
			std::cout << "Can't find the image: " << _path << std::endl;
		_sprite.setTexture(_texture);
	}
}
