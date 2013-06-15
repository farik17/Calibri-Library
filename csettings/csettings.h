#ifndef CSETTINGS_H
#define CSETTINGS_H

//! Std Includes
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

//! Project Includes
#include "cdefines.h"

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

    csettings_properties_tree &propertiesTree();
    csettings_arrays_tree &arraysTree();

private:
    C_DISABLE_COPY(CSettings)

    void eraseArray(const std::string &section);
    void eraseSection(const std::string &section);

    csettings_properties_tree m_properties;
    csettings_arrays_tree m_arrays;

    std::string m_fileName;
    std::fstream m_file;
};

inline bool is_csettings_group(const std::string &line);
inline bool is_csettings_array(const std::string &line);

size_t csettings_array_size(CSettings &settings, const std::string &section);

template<typename T>
inline bool csettings_value(CSettings &settings, const std::string &key, T &data, size_t index = 0)
{
    if (!str_contains('/', key))
        return false;

    std::string section = str_left('/', key);

    bool array = is_csettings_array(section);
    bool group = is_csettings_group(section);

    if (!group && !array)
        return false;
    
    if (group) {
        const std::string &value = settings.propertiesTree()[section][str_right('/', key)];

        std::stringstream stream;
        stream.str(value);
        stream >> data;
        return true;
    }

    if (array) {
        const std::string &value = settings.arraysTree()[section][index][str_right('/', key)];

        std::stringstream stream;
        stream.str(value);
        stream >> data;
        return true;
    }

    return false;
}

template<typename T>
inline bool set_csettings_value(CSettings &settings, const std::string &key, T data, size_t index = 0)
{
    if (!str_contains('/', key))
        return false;

    std::string section = str_left('/', key);

    bool array = is_csettings_array(section);
    bool group = is_csettings_group(section);

    if (!array && !group)
        return false;

    if (group) {
        std::stringstream stream;
        stream << data;

        settings.propertiesTree()[section][str_right('/', key)] = stream.str();
        return true;
    }

    if (array) {
        std::stringstream stream;
        stream << data;

        if (index >= settings.arraysTree()[section].size())
            settings.arraysTree()[section].resize(index + 1);

        settings.arraysTree()[section][index][str_right('/', key)] = stream.str();
        return true;
    }
    
    return false;
}

#endif // CSETTINGS_H

