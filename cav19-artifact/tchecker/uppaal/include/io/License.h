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
// Copyright (c) 1995 - 2003, Uppsala University and Aalborg University.
// All right reserved.
//
///////////////////////////////////////////////////////////////////

#ifndef INCLUDE_IO_LICENSE_H
#define INCLUDE_IO_LICENSE_H

#include <string>
#include <map>
#include <vector>
#include "base/platform.h"

namespace io
{

#ifdef ENABLE_LICENSE

    class License
    {
    public:
        /** Initialize the license:
         * - use the key if necessary and if key != NULL,
         * - check the license in licfile,
         * The entries are mapped internally afterwards.
         */
        License(const char* argv0, const char* key, const char* licfile, int defLease = -1);

        enum status_t
        {
            VALID,     // Obviously valid license.
            EXPIRED,   // Time is over.
            EXHAUSTED, // Too many other active users.
            NOT_FOUND, // Key, server, or license file not found.
            INVALID,
            CONNECTION_ERROR,
            NO_MAC,
            INVALID_MAC
        };

        /** Conversion from status to string.
         */
        static const char* status2str(status_t);

        /** Check the license and return its status.
         * If it is expired, try to renew the license file
         * with its key if it is a floating license.
         */
        status_t checkStatus();

        /** Return the associated value to a key
         * inside the license file.
         */
        std::string getValue(const char* key) { return values[key]; }

        /** Return true if the string is listed in
         * uppaal.features, false otherwise.
         */
        bool hasFeature(const char* key) { return status == VALID && features[key]; }

        /** Iterator on the key/values.
         */
        typedef std::map<std::string, std::string>::const_iterator const_iterator;
        const_iterator begin() const { return values.begin(); }
        const_iterator end()   const { return values.end(); }

        /** Iterator on the features.
         */
        typedef std::map<std::string, bool>::const_iterator feature_iterator;
        feature_iterator beginFeature() const { return features.begin(); }
        feature_iterator endFeature()   const { return features.end(); }

    private:
        // Get the license from the server.
        bool getLicense(const std::string&, std::string&);

        // Decrypt the license file.
        void decrypt(std::string&);

        // Map the key/values in the license file.
        void mapValues(const std::string&, char);

        // Map the features.
        void mapFeatures();

        // Test (time) validity.
        bool isValid(const char*);

        std::string licFilename, data, key;
        int defaultLease;
        status_t status;
        std::map<std::string, std::string> values;
        std::map<std::string, bool> features;
        maclist_t *macs;
    };

#else // Academic check.

    void checkAcademicLicense(const char* argv0, const char* filename);

#endif

}

// Default license filename (used for distributions).
#if defined(__APPLE__) && defined(__MACH__)
#define LICENSE_SERVER "../Resources/Java/license.txt"
#define LICENSE_VERIFIER "/Applications/UPPAAL.app/Contents/Resources/Java/license.txt"
#else
#define LICENSE_SERVER "../license.txt"
#define LICENSE_VERIFIER "../license.txt"
#endif

#endif // INCLUDE_IO_LICENSE_H
