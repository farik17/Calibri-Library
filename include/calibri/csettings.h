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

#ifndef CSETTINGS_H
#define CSETTINGS_H

//! Std Includes
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>

//! CUtils Includes
#include "cutils.h"

#if _MSC_VER
#pragma warning(disable:4503)
#endif

//! Typedefs
typedef std::unordered_map<std::string, std::string>                    csettings_properties;
typedef std::unordered_map<std::string, csettings_properties>           csettings_properties_tree;
typedef std::vector<csettings_properties>                               csettings_array;
typedef std::unordered_map<std::string, csettings_array>                csettings_arrays_tree;

class CSettings
{
public:
    CSettings(const std::string &fileName);
    
    const bool save();
    const bool load();

    template<typename T>
    const bool value(const std::string &key, T &data, const size_t index = 0)
    {
        if (!str_contains('/', key))
            return false;

        std::string section = str_left('/', key);

        bool array = isArray(section);
        bool properties = isProperties(section);

        if (!properties && !array)
            return false;

        if (properties) {
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
    const bool setValue(const std::string &key, const T &data, const size_t index = 0)
    {
        if (!str_contains('/', key))
            return false;

        std::string section = str_left('/', key);

        bool array = isArray(section);
        bool properties = isProperties(section);

        if (!array && !properties)
            return false;

        if (properties)
            return lexical_cast(data, m_propertiesTree[section][str_right('/', key)]);

        if (array) {
            if (index >= m_arraysTree[section].size())
                m_arraysTree[section].resize(index + 1);

            return lexical_cast(data, m_arraysTree[section][index][str_right('/', key)]);
        }

        return false;
    }

    const size_t arraySize(const std::string &section);

private:
    C_DISABLE_COPY(CSettings)

    void eraseArray(const std::string &section);
    void eraseProperties(const std::string &section);

    const bool isPropertiesTreeContains(const std::string &section, const std::string &name);
    const bool isArraysTreeContains(const std::string &section, const size_t index, const std::string &name);

    static const bool isProperties(const std::string &line);
    static const bool isArray(const std::string &line);

    csettings_properties_tree m_propertiesTree;
    csettings_arrays_tree m_arraysTree;

    std::string m_fileName;
    std::fstream m_file;
};

#endif // CSETTINGS_H

