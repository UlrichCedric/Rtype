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
		_rectX(rect.first),
		_rectY(rect.second),
		_isHealth(health != -1),
		_isAlive(health > 0)
	{
		setPos(pos);
		setScale(scale);

		if (_rectX != -1.0 && _rectY != -1.0) {
			setRect(0, 0, static_cast<int>(rect.first), static_cast<int>(rect.second));
		}
		setTexture(path);
		_health = Health({ 60, 10 }, pos.first, pos.second, health);
	}

	void Image::setTexture(std::string path)
	{
		_path = path;

		try {
			if (!_texture.loadFromFile(_path)) {
				std::cerr << "Error creating the texture: " << _path << std::endl;
			}
			_sprite.setTexture(_texture);
		} catch (std::exception &e) {
			std::cerr << "SetTexture Error: " << e.what() << std::endl;
		}
	}
}