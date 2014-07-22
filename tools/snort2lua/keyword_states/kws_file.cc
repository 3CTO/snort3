/*
** Copyright (C) 2014 Cisco and/or its affiliates. All rights reserved.
 * Copyright (C) 2002-2013 Sourcefire, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License Version 2 as
 * published by the Free Software Foundation.  You may not use, modify or
 * distribute this program under any other version of the GNU General
 * Public License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
// kws_file.cc author Josh Rosenbaum <jrosenba@cisco.com>

#include <sstream>
#include <vector>

#include "conversion_state.h"
#include "utils/converter.h"
#include "utils/snort2lua_util.h"


namespace keywords
{

namespace {

class File : public ConversionState
{
public:
    File(Converter* cv, LuaData* ld) : ConversionState(cv, ld) {};
    virtual ~File() {};
    virtual bool convert(std::istringstream& data);
};

} // namespace


bool File::convert(std::istringstream& data_stream)
{
    // No changes have been made to file. This class literally
    // copies the entire buffer into a rule.


    ld->begin_rule();
    std::string data = data_stream.str();
    ld->add_hdr_data(data);
    data_stream.setstate(std::ios_base::eofbit);
    return true;
}

/**************************
 *******  A P I ***********
 **************************/

static ConversionState* ctor(Converter* cv, LuaData* ld)
{
    return new File(cv, ld);
}

static const ConvertMap keyword_file =
{
    "file",
    ctor,
};

const ConvertMap* file_map = &keyword_file;

} // namespace keywords