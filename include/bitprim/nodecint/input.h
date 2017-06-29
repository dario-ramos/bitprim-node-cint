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
 * @file input.h
 * @brief Functions for manipulating a transaction's input
 *
 */

#ifndef BITPRIM_NODE_CINT_INPUT_H_
#define BITPRIM_NODE_CINT_INPUT_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Release the memory held by an input instance
 * @param input Handle to an input instance
 */
BITPRIM_EXPORT
void input_destruct(input_t input);

/**
 * @brief Determine if an input is valid
 * @param input Handle to an input instance
 * @return True (non zero) iif the input is valid
 */
BITPRIM_EXPORT
int input_is_valid(input_t input);

/**
 * @brief Determine if an input is final
 * @param input Handle to an input instance
 * @return True (non zero) iif the input is final
 */
BITPRIM_EXPORT
int /*bool*/ input_is_final(input_t input);

/**
 * @brief Get the input's serialized size
 * @param input Handle to an input instance
 * @param wire Deprecated; currently ignored
 * @return Input's serialized size
 */
BITPRIM_EXPORT
size_t input_serialized_size(input_t input, int wire /* = true*/);

/**
 * @brief Get the input's sequence number
 * @param input Handle to an input instance
 * @return The input's sequence number
 */
BITPRIM_EXPORT
uint32_t input_sequence(input_t input);

/**
 * @brief Get the input's signature operations count
 * @param input Handle to an input instance
 * @param bip16_active If true (non zero), consider only active operations
 * @return Signature operations count
 */
BITPRIM_EXPORT
size_t input_signature_operations(input_t input, int /*bool*/ bip16_active);

/**
 * @brief Get input script
 * @param input Handle to an input instance
 * @return Handle to input script. Must be released by calling script_destruct()
 */
BITPRIM_EXPORT
script_t input_script(input_t input);

/**
 * @brief Get the input's previous output
 * @param input Handle to an input instance
 * @return Handle to input's previous output. Must be released by calling output_point_destruct
 */
BITPRIM_EXPORT
output_point_t input_previous_output(input_t input);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODE_CINT_INPUT_H_ */
