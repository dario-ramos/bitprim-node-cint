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
 * @file header.h
 * @brief Functions for manipulating a block header
 *
 */

#ifndef BITPRIM_NODE_CINT_HEADER_H_
#define BITPRIM_NODE_CINT_HEADER_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Releases memory held by the header object
 * @param header Handle to the header instance
 */
BITPRIM_EXPORT
void header_destruct(header_t header);

/**
 * @brief Determine if the header is valid
 * @param header Handle to a header instance
 * @return True (non zero) iif the header is valid
 */
BITPRIM_EXPORT
int header_is_valid(header_t header);

/**
 * @brief Get header version
 * @param header Handle to a header instance
 * @return Header version
 */
BITPRIM_EXPORT
uint32_t header_version(header_t header);

/**
 * @brief Set a header's version
 * @param header Handle to a header instance
 * @param version New version value
 */
BITPRIM_EXPORT
void header_set_version(header_t header, uint32_t version);

/**
 * @brief Get header timestamp
 * @param header Handle to a header instance
 * @return Header timestamp
 */
BITPRIM_EXPORT
uint32_t header_timestamp(header_t header);

/**
 * @brief Set header timestamp
 * @param header Handle to a header instance
 * @param timestamp New header timestamp value
 */
BITPRIM_EXPORT
void header_set_timestamp(header_t header, uint32_t timestamp);

/**
 * @brief Get header bits
 * @param header Handle to a header instance
 * @return Header bits
 */
BITPRIM_EXPORT
uint32_t header_bits(header_t header);

/**
 * @brief Set header bits
 * @param header Handle to a header instance
 * @param bits New header bits value
 */
BITPRIM_EXPORT
void header_set_bits(header_t header, uint32_t bits);

/**
 * @brief Get header nonce
 * @param header Handle to a header instance
 * @return Header nonce
 */
BITPRIM_EXPORT
uint32_t header_nonce(header_t header);

/**
 * Set header nonce
 * @param header Handle to a header instance
 * @param nonce New header nonce value
 */
BITPRIM_EXPORT
void header_set_nonce(header_t header, uint32_t nonce);

/**
 * @brief Get previous block hash
 * @param header Handle to a header instance
 * @return Previous block hash
 */
BITPRIM_EXPORT
hash_t header_previous_block_hash(header_t header);

/**
 * @brief Get header Merkle
 * @param header Handle to a header instance
 * @return Header Merkle
 */
BITPRIM_EXPORT
hash_t header_merkle(header_t header);

/**
 * @brief Get header hash
 * @param header Handle to a header instance
 * @return Header hash as byte array. Must be released by calling delete[]
 */
BITPRIM_EXPORT
hash_t header_hash(header_t header);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODE_CINT_HEADER_H_ */
