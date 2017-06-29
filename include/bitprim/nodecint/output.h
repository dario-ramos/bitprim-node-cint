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
 * @file output.h
 * @brief Functions for manipulating a transaction output
 *
 */

#ifndef BITPRIM_NODE_CINT_OUTPUT_H_
#define BITPRIM_NODE_CINT_OUTPUT_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Release memory held by an output instance
 * @param output Handle to an output instance
 */
BITPRIM_EXPORT
void output_destruct(output_t output);

/**
 * @brief Determine if an output is valid
 * @param output Handle to an output instance
 * @return True (non zero) iif the output is valid
 */
BITPRIM_EXPORT
int output_is_valid(output_t output);

/**
 * @brief Get the output's serialized size
 * @param output Handle to an output instance
 * @param wire Deprecated; currently ignored
 * @return The output's serialized size
 */
BITPRIM_EXPORT
size_t output_serialized_size(output_t output, int /*bool*/ wire /*= true*/);

/**
 * @brief Get the output's value
 * @param output Handle to an output instance
 * @return The output's value
 */
BITPRIM_EXPORT
uint64_t output_value(output_t output);

/**
 * @brief Get the output signature operations count
 * @param output Handle to an output instance
 * @return Amount of signature operations in the output
 */
BITPRIM_EXPORT
size_t output_signature_operations(output_t output);

/**
 * @brief: Get the output's script
 * @param output Handle to an output instance
 * @return Handle to the output script instance. Must be released by calling script_destruct
 */
BITPRIM_EXPORT
script_t output_script(output_t output);

/**
 * @brief Get output hash
 * @param output Handle to an output instance
 * @return The output hash as a byte array. Must be released by calling delete[]
 */
BITPRIM_EXPORT
hash_t output_get_hash(output_t output);

/**
 * @brief Get the output's index
 * @param output Handle to an output instance
 * @return Output index
 */
BITPRIM_EXPORT
uint32_t output_get_index(output_t output);


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODE_CINT_OUTPUT_H_ */
