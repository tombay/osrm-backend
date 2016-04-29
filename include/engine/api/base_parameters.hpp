/*

Copyright (c) 2016, Project OSRM contributors
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list
of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this
list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef ENGINE_API_BASE_PARAMETERS_HPP
#define ENGINE_API_BASE_PARAMETERS_HPP

#include "engine/hint.hpp"
#include "engine/bearing.hpp"
#include "util/coordinate.hpp"

#include <boost/optional.hpp>

#include <vector>
#include <algorithm>

namespace osrm
{
namespace engine
{
namespace api
{

/**
 * General parameters for OSRM service queries.
 *
 * Holds member attributes:
 *  - coordinates: for specifying location(s) to services
 *  - hints: hint for the service to derive the position(s) in the road network more efficiently,
 *           optional per coordinate
 *  - radiuses: limits the search for segments in the road network to given radius(es) in meter,
 *              optional per coordinate
 *  - bearings: limits the search for segments in the road network to given bearing(s) in degree
 *              towards true north in clockwise direction, optional per coordinate
 *
 * \see OSRM, Coordinate, Hint, Bearing, RouteParame, RouteParameters, TableParameters,
 *      NearestParameters, TripParameters, MatchParameters and TileParameters
 */
struct BaseParameters
{
    std::vector<util::Coordinate> coordinates;
    std::vector<boost::optional<Hint>> hints;
    std::vector<boost::optional<double>> radiuses;
    std::vector<boost::optional<Bearing>> bearings;

    // FIXME add validation for invalid bearing values
    bool IsValid() const
    {
        return (hints.empty() || hints.size() == coordinates.size()) &&
               (bearings.empty() || bearings.size() == coordinates.size()) &&
               (radiuses.empty() || radiuses.size() == coordinates.size()) &&
               std::all_of(bearings.begin(), bearings.end(),
                           [](const boost::optional<Bearing> bearing_and_range)
                           {
                               if (bearing_and_range)
                               {
                                   return bearing_and_range->IsValid();
                               }
                               return true;
                           });
    }
};
}
}
}

#endif // ROUTE_PARAMETERS_HPP