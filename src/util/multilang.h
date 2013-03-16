/*
Minetest
Copyright (C) 2013 celeron55, Perttu Ahola <celeron55@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef MULTILANG_HEADER
#define MULTILANG_HEADER

#include <string>
#include <map>
#include <ostream>

#define MULTILANG_DEFAULT "en"

struct MultiLangString
{
	std::string default_value; // Cached for quicker access
	std::map<std::string, std::string> values;

	MultiLangString(const std::string &str="")
	{
		set(MULTILANG_DEFAULT, str);
	}

	const std::string& operator=(const std::string &str)
	{
		return set(MULTILANG_DEFAULT, str);
	}

	const std::string& set(const std::string &lang,
			const std::string &value)
	{
		values[lang] = value;
		if(lang == MULTILANG_DEFAULT)
			default_value = value;
		return default_value;
	}

	const std::string& get(const std::string &lang) const
	{
		std::map<std::string, std::string>::const_iterator
				i = values.find(lang);
		if(i == values.end())
			return default_value;
		return i->second;
	}

	const char* c_str() const
	{
		return default_value.c_str();
	}

	operator const std::string&() const
	{
		return default_value;
	}
};

inline std::ostream& operator<<(std::ostream& os, const MultiLangString &mls)
{
	os<<mls.default_value;
	return os;
}

std::string serializeMultiLangString(const MultiLangString &plain);

MultiLangString deSerializeMultiLangString(std::istream &is);

#endif

