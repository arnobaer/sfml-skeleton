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

#ifndef skeleton_core_ArgumentParser_hpp
#define skeleton_core_ArgumentParser_hpp

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace skeleton {
namespace core {

class ArgumentParser
{
public:
    ArgumentParser();
    ArgumentParser(int argc, char* argv[]);
    ArgumentParser(const std::vector<std::string>& args);
    virtual ~ArgumentParser();

    bool hasArgument(const std::string& flag) const;

    template<typename T>
    T getArgument(const std::string& flag) const;

    template<typename T>
    std::vector<T> getArguments(const std::string& flag, const size_t nArguments) const;

private:
    std::vector<std::string> m_args;
};

ArgumentParser::ArgumentParser() = default;

ArgumentParser::ArgumentParser(int argc, char* argv[])
: m_args(argv, argv + argc)
{
}

ArgumentParser::ArgumentParser(const std::vector<std::string>& args)
: m_args(args)
{
}

ArgumentParser::~ArgumentParser() = default;

bool ArgumentParser::hasArgument(const std::string& flag) const
{
    return m_args.end() != std::find(m_args.begin(), m_args.end(), flag);
}

template<typename T>
T ArgumentParser::getArgument(const std::string& flag) const
{
    return getArguments<T>(flag, 1).at(0);
}

template<typename T>
std::vector<T> ArgumentParser::getArguments(const std::string& flag, const size_t nArguments) const
{
    std::vector<T> args(nArguments);

    // TODO draft

    auto it = std::find(m_args.begin(), m_args.end(), flag);
    if (m_args.end() == it)
    {
        std::cerr << "no such argument: " << flag << std::endl;
    }
    else
    {
        ++it;
        for (size_t i = 0; i < nArguments; ++i, ++it)
        {
            if (m_args.end() == it or (it->size() and "-" == it->substr(0, 1)))
            {
                std::cerr << "not enough arguments for: " << flag << std::endl;
                break;
            }
            args[i] = *it;
        }
    }
    return args;
}

} // namespace core
} // namespace skeleton

#endif
