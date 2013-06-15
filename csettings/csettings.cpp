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

    auto sectionIt = m_propertiesTree.crbegin();
    auto sectionEnd = m_propertiesTree.crend();
    
    while(sectionIt != sectionEnd) {
        const std::string &section = (*sectionIt).first;

        if (!isGroup(section)) {
            eraseSection(section);
            ++sectionIt;
            continue;
        }

        m_file << section;
        m_file << std::endl;

        const csettings_properties &group = (*sectionIt).second;

        auto propertyIt = group.cbegin();
        auto propertyEnd = group.cend();

        while(propertyIt != propertyEnd) {
            m_file << (*propertyIt).first;
            m_file << "=";
            m_file << (*propertyIt).second;
            m_file << std::endl;

            ++propertyIt;
        }

        m_file << std::endl;

        ++sectionIt;
    }

    auto arrayIt = m_arraysTree.crbegin();
    auto arrayEnd = m_arraysTree.crend();
    while (arrayIt != arrayEnd) {
        const std::string &section = (*arrayIt).first;

        if (!isArray(section)) {
            eraseArray(section);
            ++arrayIt;
            continue;
        }

        m_file << section;
        m_file << std::endl;

        const csettings_array &array = (*arrayIt).second;

        for (size_t ix = 0; ix < array.size(); ++ix) {
            auto propertyIt = array[ix].cbegin();
            auto propertyEnd = array[ix].cend();
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

        ++arrayIt;
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

        if (isGroup(line)) {
            m_propertiesTree[line] = csettings_properties();
            currentSection = line;
            continue;
        }

        if (isArray(line)) {
            m_arraysTree[line] = std::vector<csettings_properties>();
            currentSection = line;
            continue;
        }

        if (!str_contains('=', line))
            continue;

        if (isGroup(currentSection)) {
            m_propertiesTree[currentSection][str_left('=', line)] = str_right('=', line);
            continue;
        }

        if (isArray(currentSection)) {
            if (!str_contains('=', line)) {
                eraseArray(currentSection);
                continue;
            }

ProcessArrayLine:
            if (isGroup(line)) {
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

            size_t index;
            if (lexical_cast(str_take_left('/', line), index)) {
                if (index >= m_arraysTree[currentSection].size())
                    m_arraysTree[currentSection].resize(index + 1);

                m_arraysTree[currentSection][index][str_left('=', line)] = str_right('=', line);
            }

            while (m_file.good()) {
                getline(m_file, line);
                if (line.empty())
                    continue;
                goto ProcessArrayLine;
            }
            continue;
        }
    }

    m_file.close();
}

size_t CSettings::arraySize(const std::string &section)
{
    auto it = m_arraysTree.find(section);
    if (it == m_arraysTree.cend())
        return 0;

    return (*it).second.size();
}

void CSettings::eraseArray(const std::string &section)
{
    auto it = m_arraysTree.find(section);
    if (it != m_arraysTree.cend())
        m_arraysTree.erase(it);
}

void CSettings::eraseSection(const std::string &section)
{
    auto it = m_propertiesTree.find(section);
    if (it != m_propertiesTree.cend())
        m_propertiesTree.erase(it);
}

bool CSettings::isGroup(const std::string &line)
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

bool CSettings::isPropertiesTreeContains(const std::string &section, const std::string &name)
{
    if (m_propertiesTree.find(section) == m_propertiesTree.cend())
        return false;

    const csettings_properties &properties = m_propertiesTree[section];
    if (properties.find(name) == properties.cend())
        return false;

    return true;
}

bool CSettings::isArraysTreeContains(const std::string &section, size_t index, const std::string &name)
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
