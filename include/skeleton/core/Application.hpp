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

#ifndef skeleton_core_Application_hpp
#define skeleton_core_Application_hpp

#include <skeleton/core/ResourceHandler.hpp>

#include <string>
#include <vector>

namespace sf {
    class Texture;
    class Font;
}

namespace skeleton {
namespace core {

class Application
{
public:
    Application();
    Application(int argc, char* argv[]);
    Application(const std::vector<std::string>& args);
    virtual ~Application();

    const std::vector<std::string>& getArgs() const noexcept;
    int exec();

private:
    void loadTextures(const std::string& filename);
    void loadFonts(const std::string& filename);

private:
    const std::vector<std::string> m_args;
    ResourceHandler<std::string, sf::Texture> m_textureHandler;
    ResourceHandler<std::string, sf::Font> m_fontHandler;
};

} // namespace core
} // namespace skeleton

#endif
