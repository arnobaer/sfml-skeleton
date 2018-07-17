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

#ifndef skeleton_core_ResourceHandler_hpp
#define skeleton_core_ResourceHandler_hpp

#include <string>
#include <map>
#include <memory>

namespace skeleton {
namespace core {

template<typename T>
class ResourceHandler
{
public:
    virtual ~ResourceHandler();

    void loadFromFile(const size_t id, const std::string& filename);
    const T& get(const size_t id) const;

private:
    std::map<size_t, std::shared_ptr<T>> m_resources;
};

template<typename T>
ResourceHandler<T>::~ResourceHandler() = default;

template<typename T>
void ResourceHandler<T>::loadFromFile(const size_t id, const std::string& filename)
{
    std::shared_ptr<T> resource = std::make_shared<T>();
    resource->loadFromFile(filename);
    m_resources.emplace(id, resource);
}

template<typename T>
const T& ResourceHandler<T>::get(const size_t id) const
{
    return *m_resources.at(id);
}

} // namespace core
} // namespace skeleton

#endif
