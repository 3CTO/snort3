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
// config_mpls_payload_type.cc author Josh Rosenbaum <jrosenba@cisco.com>

#include <sstream>
#include <vector>

#include "conversion_state.h"
#include "utils/converter.h"
#include "utils/snort2lua_util.h"

namespace config
{

namespace {


class MplsPayloadType : public ConversionState
{
public:
    MplsPayloadType(Converter* cv, LuaData* ld) : ConversionState(cv, ld) {};
    virtual ~MplsPayloadType() {};
    virtual bool convert(std::istringstream& data_stream);
};

} // namespace


bool MplsPayloadType::convert(std::istringstream& data_stream)
{
    std::string type;
    bool retval = true;

    if (!(data_stream >> type))
        return false;

    ld->open_table("cd_mpls");


    if (!type.compare("ethernet"))
    {
        ld->add_diff_option_comment("config mpls_payload_type: ethernet", "mpls_payload_type = eth");
        retval = ld->add_option_to_table("mpls_payload_type", "eth");
    }
    else if (!type.compare("ipv4"))
    {
        ld->add_diff_option_comment("config mpls_payload_type: ipv4", "mpls_payload_type = ip4");
        retval = ld->add_option_to_table("mpls_payload_type", "ip4");
    }

    else if (!type.compare("ipv6"))
    {
        ld->add_diff_option_comment("config mpls_payload_type: ipv6", "mpls_payload_type = ip6");
        retval = ld->add_option_to_table("mpls_payload_type", "ip6");
    }
    else
        return false;

    data_stream.setstate(std::ios::eofbit); // if additional options available, stop parsing.
    return retval;
}

/**************************
 *******  A P I ***********
 **************************/


static ConversionState* ctor(Converter* cv, LuaData* ld)
{
    return new MplsPayloadType(cv, ld);
}

static const ConvertMap mpls_payload_type_api =
{
    "mpls_payload_type",
    ctor,
};

const ConvertMap* mpls_payload_type_map = &mpls_payload_type_api;

} // namespace config