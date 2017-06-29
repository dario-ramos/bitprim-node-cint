/**
 * Copyright (c) 2017 Bitprim developers (see AUTHORS)
 *
 * This file is part of Bitprim.
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
 * @file output_point.h
 * @brief Functions for manipulating a transaction's output's point
 *
 */

#ifndef BITPRIM_NODE_CINT_OUTPUT_POINT_H
#define BITPRIM_NODE_CINT_OUTPUT_POINT_H

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

/**
 * @brief Get the output point's hash
 * @param output Handle to an output point instance
 * @return Point hash as byte array. Must be released by calling delete[]
 */
BITPRIM_EXPORT
hash_t output_point_get_hash(output_point_t output);

/**
 * @brief Create an empty output point
 * @return Handle to new output point instance. Must be released by calling outpout_point_destruct()
 */
BITPRIM_EXPORT
output_point_t output_point_construct();

/**
 * @brief Get output point index inside the point. Starts at 0 (zero) with the first one
 * @param output Handle to an output point instance
 * @return Output point index
 */
BITPRIM_EXPORT
uint32_t output_point_get_index(output_point_t output);

/**
 * @brief Release memory held by output point
 * @param output Handle to an output point instance
 */
BITPRIM_EXPORT
void output_point_destruct(output_point_t output);

#endif //BITPRIM_NODE_CINT_OUTPUT_POINT_H
