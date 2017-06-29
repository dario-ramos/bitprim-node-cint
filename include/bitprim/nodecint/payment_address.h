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
 * @file payment_address.h
 * @brief Functions for manipulating a payment address
 *
 */

#ifndef BITPRIM_NODE_CINT_PAYMENT_ADDRESS_H
#define BITPRIM_NODE_CINT_PAYMENT_ADDRESS_H

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Encode a payment address
 * @param payment_address Handle to a payment address instance
 * @return Encoded payment address
 */
BITPRIM_EXPORT
char const* payment_address_encoded(payment_address_t payment_address);

/**
 * @brief Create a payment address from a string
 * @param address String representing a payment address
 * @return Handle to encoded payment address. Must be released by calling payment_address_destruct()
 */
BITPRIM_EXPORT
payment_address_t payment_address_construct_from_string(char const* address);

/**
 * @brief Get payment address version
 * @param payment_address Handle to a payment address instance
 * @return Payment address version
 */
BITPRIM_EXPORT
uint8_t version(payment_address_t payment_address);

/**
 * @brief Release memory held by payment address instance
 * @param payment_address Handle to a payment address instance
 */
BITPRIM_EXPORT
void payment_address_destruct(payment_address_t payment_address);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //BITPRIM_NODE_CINT_PAYMENT_ADDRESS_H
