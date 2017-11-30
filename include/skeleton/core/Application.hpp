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

#include <string>
#include <vector>

namespace skeleton {
namespace core {

class Application
{
public:
    Application();
    Application(int argc, char* argv[]);
    virtual ~Application();

    static const std::vector<std::string>& getArgs() noexcept;
    int exec();

private:
    static std::vector<std::string> m_args;
};

} // namespace core
} // namespace skeleton

#endif
