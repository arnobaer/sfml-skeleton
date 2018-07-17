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

#include <SFML/Graphics.hpp>
#include <pugixml.hpp>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace skeleton {
namespace core {

static const std::string ID_TEXTURE_ICON {"ID_TEXTURE_ICON"};
static const std::string ID_FONT_TUFFY {"ID_FONT_TUFFY"};

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

    loadTextures("../config/textures.xml");
    loadFonts("../config/fonts.xml");

    sf::RenderWindow window(videoMode, "skeleton", sf::Style::Close);

    {
        sf::Image icon = m_textureHandler.get(ID_TEXTURE_ICON).copyToImage();
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    sf::Sprite sprite;
    sprite.setTexture(m_textureHandler.get(ID_TEXTURE_ICON));
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
    text.setFont(m_fontHandler.get(ID_FONT_TUFFY));
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

void Application::loadTextures(const std::string& filename)
{
    pugi::xml_document doc;
    doc.load_file(filename.c_str());

    for (auto node: doc.child("textures"))
    {
        std::string id = node.attribute("id").value();
        std::string src = node.attribute("src").value();
        if (not m_textureHandler.load(id).loadFromFile(src))
            throw std::runtime_error(src);
    }
}

void Application::loadFonts(const std::string& filename)
{
  pugi::xml_document doc;
  doc.load_file(filename.c_str());

  for (auto node: doc.child("fonts"))
  {
    std::string id = node.attribute("id").value();
    std::string src = node.attribute("src").value();
    if (not m_fontHandler.load(id).loadFromFile(src))
        throw std::runtime_error(src);
  }
}

} // namespace core
} // namespace skeleton
