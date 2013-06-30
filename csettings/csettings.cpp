/****************************************************************************
**
** Copyright (c) 2013 Calibri-Software <calibrisoftware@gmail.com>
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
** THE SOFTWARE.
**
****************************************************************************/

//! Self Includes
#include "csettings.h"

//! Std Includes
#include <iostream>
#include <ios>

CSettings::CSettings(const std::string &fileName)
    : m_fileName(fileName)
{

}

void CSettings::save()
{
    m_file.open(m_fileName.c_str(), std::ios::out | std::ios::trunc);
    if (!m_file.is_open()) {
        if (m_fileName.empty()) {
            std::cout << "CSettings::save error: invalid file name" << std::endl;
            return;
        }
        std::cout << "CSettings::save error: can not open file with name " << m_fileName << std::endl;
        return;
    }

    auto propertySectionIt = m_propertiesTree.crbegin();
    auto propertySectionEnd = m_propertiesTree.crend();
    while(propertySectionIt != propertySectionEnd) {
        const std::string &section = (*propertySectionIt).first;
        if (!isProperties(section)) {
            eraseProperties(section);
            ++propertySectionIt;
            continue;
        }

        m_file << section;
        m_file << std::endl;

        const csettings_properties &properties = (*propertySectionIt).second;

        auto propertyIt = properties.cbegin();
        auto propertyEnd = properties.cend();
        while(propertyIt != propertyEnd) {
            m_file << (*propertyIt).first;
            m_file << "=";
            m_file << (*propertyIt).second;
            m_file << std::endl;

            ++propertyIt;
        }

        m_file << std::endl;

        ++propertySectionIt;
    }

    auto arraySectionIt = m_arraysTree.crbegin();
    auto arraySectionEnd = m_arraysTree.crend();
    while (arraySectionIt != arraySectionEnd) {
        const std::string &section = (*arraySectionIt).first;
        if (!isArray(section)) {
            eraseArray(section);
            ++arraySectionIt;
            continue;
        }

        m_file << section;
        m_file << std::endl;

        const csettings_array &array = (*arraySectionIt).second;

        for (size_t ix = 0; ix < array.size(); ++ix) {
            const csettings_properties &properties = array[ix];

            auto propertyIt = properties.cbegin();
            auto propertyEnd = properties.cend();
            while(propertyIt != propertyEnd) {
                m_file << ix;
                m_file << '/';
                m_file << (*propertyIt).first;
                m_file << "=";
                m_file << (*propertyIt).second;
                m_file << std::endl;

                ++propertyIt;
            }
        }

        m_file << std::endl;

        ++arraySectionIt;
    }

    m_file.flush();
    m_file.close();
}

void CSettings::load()
{
    m_file.open(m_fileName.c_str(), std::ios::in);
    if (!m_file.is_open()) {
        if (m_fileName.empty()) {
            std::cout << "CSettings::load error: invalid file name" << std::endl;
            return;
        }
        std::cout << "CSettings::load error: can not open file with name " << m_fileName << std::endl;
        return;
    }

    std::string currentSection;

    while (m_file.good()) {
        std::string line;
        getline(m_file, line);

        if (line.empty())
            continue;

        if (isProperties(line)) {
            m_propertiesTree[line] = csettings_properties();
            currentSection = line;
            continue;
        }

        if (isArray(line)) {
            m_arraysTree[line] = csettings_array();
            currentSection = line;
            continue;
        }

        if (!str_contains('=', line))
            continue;

        if (isProperties(currentSection)) {
            m_propertiesTree[currentSection][str_left('=', line)] = str_right('=', line);
            continue;
        }

        if (isArray(currentSection)) {
            do {
                size_t index;
                if (lexical_cast(str_take_left('/', line), index)) {
                    if (index >= m_arraysTree[currentSection].size())
                        m_arraysTree[currentSection].resize(index + 1);

                    m_arraysTree[currentSection][index][str_left('=', line)] = str_right('=', line);
                }

                if (!m_file.good())
                    break;

                getline(m_file, line);
                if (line.empty())
                    break;

                if (isProperties(line)) {
                    if (m_arraysTree[currentSection].empty())
                        eraseArray(currentSection);

                    m_propertiesTree[line] = csettings_properties();
                    currentSection = line;
                    break;
                }

                if (isArray(line)) {
                    if (m_arraysTree[currentSection].empty())
                        eraseArray(currentSection);

                    m_arraysTree[line] = csettings_array();
                    currentSection = line;
                    break;
                }

                if (!str_contains('=', line))
                    break;
            } while(true);
            continue;
        }
    }

    m_file.close();
}

size_t CSettings::arraySize(const std::string &section)
{
    auto arraySectionIt = m_arraysTree.find(section);
    if (arraySectionIt == m_arraysTree.cend())
        return 0;

    return (*arraySectionIt).second.size();
}

void CSettings::eraseArray(const std::string &section)
{
    auto arraySectionIt = m_arraysTree.find(section);
    if (arraySectionIt != m_arraysTree.cend())
        m_arraysTree.erase(arraySectionIt);
}

void CSettings::eraseProperties(const std::string &section)
{
    auto propertiesSectionIt = m_propertiesTree.find(section);
    if (propertiesSectionIt != m_propertiesTree.cend())
        m_propertiesTree.erase(propertiesSectionIt);
}

bool CSettings::isPropertiesTreeContains(const std::string &section, const std::string &name)
{
    if (m_propertiesTree.find(section) == m_propertiesTree.cend())
        return false;

    const csettings_properties &properties = m_propertiesTree[section];
    if (properties.find(name) == properties.cend())
        return false;

    return true;
}

bool CSettings::isArrayTreeContains(const std::string &section, size_t index, const std::string &name)
{
    if (m_arraysTree.find(section) == m_arraysTree.cend())
        return false;

    const csettings_array &array = m_arraysTree[section];
    if (index >= array.size())
        return false;

    const csettings_properties &properties = array[index];
    if (properties.find(name) == properties.cend())
        return false;

    return true;
}

bool CSettings::isProperties(const std::string &line)
{
    if (line.size() == 0)
        return false;

    return line.at(0) == '[' && line.at(line.size() - 1) == ']';
}

bool CSettings::isArray(const std::string &line)
{
    if (line.size() == 0)
        return false;

    return line.at(0) == '<' && line.at(line.size() - 1) == '>';
}
