#ifndef SETTINGS_H
#define SETTINGS_H

//! Std Includes
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

//! Project Includes
#include "defines.h"

//! Utils Includes
#include "utils.h"

#if _MSC_VER
#pragma warning(disable:4503)
#endif

//! Typedefs
typedef std::map<std::string, std::string>              settings_properties;
typedef std::map<std::string, settings_properties>      settings_properties_tree;
typedef std::vector<settings_properties>                settings_array;
typedef std::map<std::string, settings_array>           settings_arrays_tree;

class Settings
{
public:
    Settings(const std::string &fileName);
    
    void save();
    void load();

    settings_properties_tree &propertiesTree();
    settings_arrays_tree &arraysTree();
	
private:
    C_DISABLE_COPY(Settings)

	void eraseArray(const std::string &section);
	void eraseSection(const std::string &section);

    settings_properties_tree m_properties;
    settings_arrays_tree m_arrays;

    std::string m_fileName;
    std::fstream m_file;
};

inline bool is_settings_group(const std::string &line);
inline bool is_settings_array(const std::string &line);

size_t settings_array_size(Settings &settings, const std::string &section);

template<typename T>
inline bool settings_value(Settings &settings, const std::string &key, T &data, size_t index = 0)
{
    if (!str_contains('/', key))
        return false;
	
    std::string section = str_left('/', key);

    bool array = is_settings_array(section);
    bool group = is_settings_group(section);

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
inline bool set_settings_value(Settings &settings, const std::string &key, T data, size_t index = 0)
{
    if (!str_contains('/', key))
        return false;

    std::string section = str_left('/', key);

    bool array = is_settings_array(section);
    bool group = is_settings_group(section);

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

#endif // SETTINGS_H

