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
 * @file point_list.h
 * @brief Functions for manipulating a point list
 *
 */

#ifndef BITPRIM_NODE_CINT_POINT_LIST_H
#define BITPRIM_NODE_CINT_POINT_LIST_H

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the list's n-th point
 * @param point_list Handle to a point list instance
 * @param n Index for the selected point. Starts at 0 (zero) with the first one
 * @return Handle to selected point instance. Must be released with point_destruct()
 */
BITPRIM_EXPORT
point_t point_list_nth(point_list_t point_list, size_t n);

/**
 * @brief Get point list count
 * @param point_list Handle to a point list instance
 * @return Point list count
 */
BITPRIM_EXPORT
size_t point_list_count(point_list_t point_list);

/**
 * @brief Release memory held by point list instance
 * @param point_list Handle to a point list instance
 */
BITPRIM_EXPORT
void point_list_destruct(point_list_t point_list);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //BITPRIM_NODE_CINT_POINT_LIST_H
