/*
 *  sfml-skeleton
 *  Copyright (C) 2016  Bernhard Arnold
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <skeleton/core/Application.hpp>

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace skeleton {
namespace core {

std::vector<std::string> Application::m_args;

Application::Application() = default;

Application::Application(int argc, char* argv[])
{
    m_args.clear();
    for (int i = 0; i < argc; ++i)
        m_args.emplace_back(argv[i]);
}

Application::~Application() = default;

const std::vector<std::string>& Application::getArgs() noexcept
{
  return m_args;
}

int Application::exec()
{
    // dump help
    if (std::find(m_args.begin(), m_args.end(), "-h") != m_args.end())
    {
        std::cout << "usage: " << m_args.at(0) << " [options]" << std::endl;
        std::cout << "options:" << std::endl;
        std::cout << "  -m    show available fullscreen modes and exit" << std::endl;
        std::cout << "  -h    show help and exit" << std::endl;
        return EXIT_SUCCESS;
    }

    // dump fullscrean modes
    if (std::find(m_args.begin(), m_args.end(), "-m") != m_args.end())
    {
        std::cout << "fullscreen modes:" << std::endl;
        for (const auto& mode : sf::VideoMode::getFullscreenModes())
        {
            std::cout << mode.width << "x" << mode.height << " ";
            std::cout << mode.bitsPerPixel << "bpp" << std::endl;
        }
        return EXIT_SUCCESS;
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "skeleton", sf::Style::Close);

    sf::Image icon;
    icon.loadFromFile("../assets/icons/sfml-icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Texture texture;
    texture.loadFromImage(icon);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(.5, .5);
    sprite.setOrigin(
        sprite.getLocalBounds().width / 2.,
        sprite.getLocalBounds().height / 2.
    );
    sprite.setPosition(
        window.getSize().x / 2.,
        window.getSize().y / 2. - 32.
    );

    sf::Font font;
    font.loadFromFile("../assets/fonts/Tuffy.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString("SFML Skeleton");
    text.setCharacterSize(24);
    text.setColor(sf::Color::White);
    text.setOrigin(
        text.getLocalBounds().width / 2.,
        text.getLocalBounds().height / 2.
    );
    text.setPosition(
        window.getSize().x / 2.,
        window.getSize().y / 2. + 128.
    );

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // draw stuff
        window.draw(sprite);
        window.draw(text);

        window.display();
    }


    return EXIT_SUCCESS;
}

} // namespace core
} // namespace skeleton
