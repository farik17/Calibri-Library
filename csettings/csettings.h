#ifndef CSETTINGS_H
#define CSETTINGS_H

//! Std Includes
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

//! CUtils Includes
#include "cutils/cutils.h"

#if _MSC_VER
#pragma warning(disable:4503)
#endif

//! Typedefs
typedef std::map<std::string, std::string>                  csettings_properties;
typedef std::map<std::string, csettings_properties>         csettings_properties_tree;
typedef std::vector<csettings_properties>                   csettings_array;
typedef std::map<std::string, csettings_array>              csettings_arrays_tree;

class CSettings
{
public:
    CSettings(const std::string &fileName);
    
    void save();
    void load();

    template<typename T>
    bool value(const std::string &key, T &data, size_t index = 0)
    {
        if (!str_contains('/', key))
            return false;

        std::string section = str_left('/', key);

        bool array = isArray(section);
        bool group = isGroup(section);

        if (!group && !array)
            return false;

        if (group) {
            std::string name = str_right('/', key);
            if (!isPropertiesTreeContains(section, name))
                return false;

            return lexical_cast(m_propertiesTree[section][name], data);
        }

        if (array) {
            std::string name = str_right('/', key);
            if (!isArraysTreeContains(section, index, name))
                return false;

            return lexical_cast(m_arraysTree[section][index][name], data);
        }

        return false;
    }

    template<typename T>
    bool setValue(const std::string &key, const T &data, size_t index = 0)
    {
        if (!str_contains('/', key))
            return false;

        std::string section = str_left('/', key);

        bool array = isArray(section);
        bool group = isGroup(section);

        if (!array && !group)
            return false;

        if (group)
            return lexical_cast(data, m_propertiesTree[section][str_right('/', key)]);

        if (array) {
            if (index >= m_arraysTree[section].size())
                m_arraysTree[section].resize(index + 1);

            return lexical_cast(data, m_arraysTree[section][index][str_right('/', key)]);
        }

        return false;
    }

    size_t arraySize(const std::string &section);

private:
    C_DISABLE_COPY(CSettings)

    void eraseArray(const std::string &section);
    void eraseSection(const std::string &section);

    bool isGroup(const std::string &line);
    bool isArray(const std::string &line);
    bool isPropertiesTreeContains(const std::string &section, const std::string &name);
    bool isArraysTreeContains(const std::string &section, size_t index, const std::string &name);

    csettings_properties_tree m_propertiesTree;
    csettings_arrays_tree m_arraysTree;

    std::string m_fileName;
    std::fstream m_file;
};

#endif // CSETTINGS_H

