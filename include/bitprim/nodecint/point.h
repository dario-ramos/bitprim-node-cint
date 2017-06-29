/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @file point.h
 * @brief Functions for manipulating a generic point
 *
 */

#ifndef BITPRIM_NODE_CINT_POINT_H
#define BITPRIM_NODE_CINT_POINT_H

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get point hash
 * @param point Handle to point instance
 * @return Point hash as byte array. Must be released by calling delete[]
 */
BITPRIM_EXPORT
hash_t point_get_hash(point_t point);

/**
 * @brief Determine if point is valid
 * @param point Handle to point instance
 * @return True (non zero) iif point is valid
 */
BITPRIM_EXPORT
int /*bool*/ point_is_valid(point_t point);

/**
 * @brief Get point index
 * @param point Handle to point instance
 * @return Point index
 */
BITPRIM_EXPORT
uint32_t point_get_index(point_t point);

/**
 * @brief Get point checksum
 * @param point Handle to point instance
 * @return Point checksum
 */
BITPRIM_EXPORT
uint64_t point_get_checksum(point_t point);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //BITPRIM_NODE_CINT_POINT_H
