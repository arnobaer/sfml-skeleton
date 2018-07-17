/*
 *  sfml-skeleton
 *  Copyright (C) 2018  Bernhard Arnold
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

#include <map>
#include <memory>
#include <string>
#include <iostream>
namespace skeleton {
namespace core {

template<class Key, class T>
class ResourceHandler
{
public:
    T& load(const Key& key);
    const T& get(const Key& key) const;

    void release(const Key& key);

private:
    std::map<Key, std::shared_ptr<T>> m_resources;
};

template<class Key, class T>
T& ResourceHandler<Key, T>::load(const Key& key)
{
    if (not m_resources.count(key))
        m_resources[key] = std::make_shared<T>();
    return *m_resources.at(key);
}

template<class Key, class T>
const T& ResourceHandler<Key, T>::get(const Key& key) const
{
    return *m_resources.at(key);
}

template<class Key, class T>
void ResourceHandler<Key, T>::release(const Key& key)
{
    auto it = m_resources.find(key);
    if (m_resources.end() != it)
        m_resources.erase(it);
}

} // namespace core
} // namespace skeleton

#endif
