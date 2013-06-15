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

    auto sectionIt = m_properties.crbegin();
    auto sectionEnd = m_properties.crend();
    
    while(sectionIt != sectionEnd) {
        const std::string &section = (*sectionIt).first;

        if (!is_csettings_group(section)) {
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

    auto arrayIt = m_arrays.crbegin();
    auto arrayEnd = m_arrays.crend();
    while (arrayIt != arrayEnd) {
        const std::string &section = (*arrayIt).first;

        if (!is_csettings_array(section)) {
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

        if (is_csettings_group(line)) {
            m_properties[line] = csettings_properties();
            currentSection = line;
            continue;
        }

        if (is_csettings_array(line)) {
            m_arrays[line] = std::vector<csettings_properties>();
            currentSection = line;
            continue;
        }

        if (!str_contains('=', line))
            continue;

        if (is_csettings_group(currentSection)) {
            m_properties[currentSection][str_left('=', line)] = str_right('=', line);
            continue;
        }

        if (is_csettings_array(currentSection)) {
            if (!str_contains('=', line)) {
                eraseArray(currentSection);
                continue;
            }

ProcessArrayLine:
            if (is_csettings_group(line)) {
                if (m_arrays[currentSection].empty())
                    eraseArray(currentSection);

                m_properties[line] = csettings_properties();
                currentSection = line;
                break;
            }

            if (is_csettings_array(line)) {
                if (m_arrays[currentSection].empty())
                    eraseArray(currentSection);

                m_arrays[line] = csettings_array();
                currentSection = line;
                break;
            }

            size_t index = static_cast<size_t>(std::stoi(str_take_left('/', line)));

            if (index >= m_arrays[currentSection].size())
                m_arrays[currentSection].resize(index + 1);

            m_arrays[currentSection][index][str_left('=', line)] = str_right('=', line);

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

csettings_properties_tree &CSettings::propertiesTree()
{
    return m_properties;
}

csettings_arrays_tree &CSettings::arraysTree()
{
    return m_arrays;
}

void CSettings::eraseArray(const std::string &section)
{
    auto it = m_arrays.find(section);
    if (it != m_arrays.cend())
        m_arrays.erase(it);
}

void CSettings::eraseSection(const std::string &section)
{
    auto it = m_properties.find(section);
    if (it != m_properties.cend())
        m_properties.erase(it);
}

bool is_csettings_group(const std::string &line)
{
    if (line.size() == 0)
        return false;

    return line.at(0) == '[' && line.at(line.size() - 1) == ']';
}

bool is_csettings_array(const std::string &line)
{
    if (line.size() == 0)
        return false;

    return line.at(0) == '<' && line.at(line.size() - 1) == '>';
}

size_t csettings_array_size(CSettings &settings, const std::string &section)
{
    auto it = settings.arraysTree().find(section);
    if (it == settings.arraysTree().cend())
        return 0;

    return (*it).second.size();
}
