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

#include "multilang.h"
#include "util/serialize.h"
#include <sstream>

std::string serializeMultiLangString(const MultiLangString &plain)
{
	std::ostringstream os(std::ios::binary);
	writeU8(os, 0); // version
	writeU16(os, plain.values.size());
	for(std::map<std::string, std::string>::const_iterator
			i = plain.values.begin(); i != plain.values.end(); ++i)
	{
		os<<serializeString(i->first);
		os<<serializeLongString(i->second);
	}
	return os.str();
}

MultiLangString deSerializeMultiLangString(std::istream &is)
{
	MultiLangString result;
	readU8(is); // version
	size_t num = readU16(is);
	for(size_t i=0; i<num; i++){
		std::string lang = deSerializeString(is);
		std::string value = deSerializeLongString(is);
		result.set(lang, value);
	}
	return result;
}


