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

#include <skeleton/core/ArgumentParser.hpp>
#include <skeleton/core/ResourceHandler.hpp>

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace skeleton {
namespace core {

static const size_t ID_TEXTURE_ICON {1000};
static const size_t ID_FONT_TUFFY {1000};

Application::Application() = default;

Application::Application(int argc, char* argv[])
: m_args(argv, argv + argc)
{
}

Application::Application(const std::vector<std::string>& args)
: m_args(args)
{
}

Application::~Application() = default;

const std::vector<std::string>& Application::getArgs() const noexcept
{
    return m_args;
}

int Application::exec()
{
    ArgumentParser parser(m_args);

    // dump help
    if (parser.hasArgument("-h"))
    {
        std::cout << "usage: " << m_args.at(0) << " [options]" << std::endl;
        std::cout << "options:" << std::endl;
        std::cout << "  -s <mode>  set fullscreen mode (default 800x600)" << std::endl;
        std::cout << "  -m         show available fullscreen modes and exit" << std::endl;
        std::cout << "  -h         show help and exit" << std::endl;
        return EXIT_SUCCESS;
    }

    // dump fullscrean modes
    if (parser.hasArgument("-m"))
    {
        std::cout << "fullscreen modes:" << std::endl;
        for (const auto& mode : sf::VideoMode::getFullscreenModes())
        {
            std::cout << mode.width << "x" << mode.height << " ";
            std::cout << mode.bitsPerPixel << "bpp" << std::endl;
        }
        return EXIT_SUCCESS;
    }

    sf::VideoMode videoMode(800, 600);

    // set fullscrean mode
    if (parser.hasArgument("-s"))
    {
        std::stringstream ss;
        ss << parser.getArgument<std::string>("-s");
        char x;
        ss >> videoMode.width >> x >> videoMode.height;
        const auto it = std::find(
            sf::VideoMode::getFullscreenModes().begin(),
            sf::VideoMode::getFullscreenModes().end(),
            videoMode
        );
        if (sf::VideoMode::getFullscreenModes().end() == it)
        {
            std::cerr << "ERROR: no such video mode... " << ss.str() << std::endl;
            return EXIT_FAILURE;
        }
    }

    ResourceHandler<sf::Texture> textureHandler;
    textureHandler.loadFromFile(ID_TEXTURE_ICON, "../assets/icons/sfml-icon.png");

    ResourceHandler<sf::Font> fontHandler;
    fontHandler.loadFromFile(ID_FONT_TUFFY, "../assets/fonts/Tuffy.ttf");

    sf::RenderWindow window(videoMode, "skeleton", sf::Style::Close);

    {
        sf::Image icon = textureHandler.get(ID_TEXTURE_ICON).copyToImage();
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    sf::Sprite sprite;
    sprite.setTexture(textureHandler.get(ID_TEXTURE_ICON));
    sprite.setScale(.5, .5);
    sprite.setOrigin(
        sprite.getLocalBounds().width / 2.,
        sprite.getLocalBounds().height / 2.
    );
    sprite.setPosition(
        window.getSize().x / 2.,
        window.getSize().y / 2. - 32.
    );

    sf::Text text;
    text.setFont(fontHandler.get(ID_FONT_TUFFY));
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
