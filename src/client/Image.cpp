/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
** File description:
** Image
*/

#include "Image.hpp"

namespace Game {
	Image::Image(
		std::size_t id,
		std::string path,
		std::pair<float, float> pos,
		std::pair<float, float> scale,
		std::pair<float, float> rect,
		int health
	):
		_id(id),
		_path(path),
		_isHealth(health != -1),
		_isAlive(health > 0)
	{
		setTexture(path);
		setPos(pos);
		setScale(scale);
		_rectX = rect.first;
		_rectY = rect.second;
		setRect(0, 0, rect.first, rect.second);
		_health = Health({ 60, 10 }, pos.first, pos.second, health);
	}

	void Image::setTexture(std::string path)
	{
		_path = path;
		if (!_texture.loadFromFile(_path))
			std::cout << "Can't find the image: " << _path << std::endl;
		_sprite.setTexture(_texture);
	}
}
