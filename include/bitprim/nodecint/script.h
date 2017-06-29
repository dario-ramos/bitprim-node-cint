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
 * @file script.h
 * @brief Functions for manipulating a transaction script
 *
 */

#ifndef BITPRIM_NODE_CINT_SCRIPT_H_
#define BITPRIM_NODE_CINT_SCRIPT_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Release memory held by a script instance
 * @param script Handle to a script instance
 */
BITPRIM_EXPORT
void script_destruct(script_t script);

/**
 * @brief Determine if a script is valid
 * @param script Handle to a script instance
 * @return True (non zero) iif the script is valid
 */
BITPRIM_EXPORT
int script_is_valid(script_t script);

/**
 * @brief Determine if the script operations are valid
 * @param script Handle to a script instance
 * @return True (non zero) iif the script operations are valid
 */
BITPRIM_EXPORT
int script_is_valid_operations(script_t script);

/**
 * @brief Get the script Satoshi content size
 * @param script Handle to a script instance
 * @return Script Satoshi content size
 */
BITPRIM_EXPORT
size_t script_satoshi_content_size(script_t script);

/**
 * @brief Get script serialized size
 * @param script Handle to a script instance
 * @param prefix If true, add prefix size to total size
 * @return Script serialized size
 */
BITPRIM_EXPORT
size_t script_serialized_size(script_t script, bool prefix);

/**
 * @brief Get script string representation
 * @param script Handle to a script instance
 * @param active_forks Active forks count
 * @return Script string representation
 */
BITPRIM_EXPORT
char const* script_to_string(script_t script, uint32_t active_forks);

/**
 * @brief Get script signature operations (sigops) count
 * @param script Handle to a script instance
 * @param embedded Tells whether to consider embedded sigops in the count or not
 * @return Script sigops count
 */
BITPRIM_EXPORT
size_t script_sigops(script_t script, bool embedded);

/**
 * @brief Get script embedded signature operations (sigops) count
 * @param script Handle to a script instance
 * @param prevout_script Handle to previous script instance
 * @return Embedded signature operations count
 */
BITPRIM_EXPORT
size_t script_embedded_sigops(script_t script, script_t prevout_script);


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODE_CINT_SCRIPT_H_ */
