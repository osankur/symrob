/* -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; -*-
 *
 * This file is part of the UPPAAL DBM library.
 *
 * The UPPAAL DBM library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 *
 * The UPPAAL DBM library is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with the UPPAAL DBM library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA.
 */

// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-
////////////////////////////////////////////////////////////////////
//
// This file is a part of the UPPAAL toolkit.
// Copyright (c) 1995 - 2006, Uppsala University and Aalborg University.
// All right reserved.
//
///////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBM_CLOCKACCESSOR_H
#define INCLUDE_DBM_CLOCKACCESSOR_H

#include <string>
#include "base/inttypes.h"
#include "base/Object.h"

namespace dbm
{

    // Class to access clock names in an abstract way.
    class ClockAccessor : public base::Object
    {
    public:
        virtual ~ClockAccessor() {}

        /// @return the name of a given clock (index).
        /// The reference clock corresponds to index 0.
        virtual const std::string getClockName(cindex_t index) const = 0;
    };

}

#endif // INCLUDE_DBM_CLOCKACCESSOR_H
