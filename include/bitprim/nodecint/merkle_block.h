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
 * @file merkle_block.h
 * @brief Functions for manipulating Merkle blocks
 *
 */

#ifndef BITPRIM_NODE_CINT_MERKLE_BLOCK_H_
#define BITPRIM_NODE_CINT_MERKLE_BLOCK_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the block's n-th hash
 * @param block Handle to a Merkle block instance
 * @param n Index for selecting hash
 * @return Handle to Merkle block's n-th hash. Must be released by calling delete[]
 */
BITPRIM_EXPORT
hash_t merkle_block_hash_nth(merkle_block_t block, size_t n);

/**
 * @brief Get Merkle block header
 * @param block Handle to a Merkle block instance
 * @return Handle to Merkle block header. Must be released by calling header_destruct()
 */
BITPRIM_EXPORT
header_t merkle_block_header(merkle_block_t block);

/**
 * @brief Determine if a Merkle block is valid
 * @param block Handle to a Merkle block instance
 * @return True (non zero) iif the Merkle block is valid
 */
BITPRIM_EXPORT
int /* bool */ merkle_block_is_valid(merkle_block_t block);

/**
 * @brief Get Merkle block hash count
 * @param block Handle to a Merkle block instance
 * @return The Merkle block hash count
 */
BITPRIM_EXPORT
size_t merkle_block_hash_count(merkle_block_t block);

/**
 * @brief Get Merkle block serialized size
 * @param block Handle to a Merkle block instance
 * @param version Protocol version
 * @return The Merkle block serialized size
 */
BITPRIM_EXPORT
size_t merkle_block_serialized_size(merkle_block_t block, uint32_t version);

/**
 * @brief Get Merkle block transaction count
 * @param block Handle to a Merkle block instance
 * @return Merkle block transaction count
 */
BITPRIM_EXPORT
size_t merkle_block_total_transaction_count(merkle_block_t block);

/**
 * @brief Release memory held by Merkle block instance
 * @param block Handle to a Merkle block instance
 */
BITPRIM_EXPORT
void merkle_block_destruct(merkle_block_t block);

/**
 * @brief Reset Merkle block
 * @param block Handle to a Merkle block instance
 */
BITPRIM_EXPORT
void merkle_block_reset(merkle_block_t block);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODE_CINT_MERKLE_BLOCK_H_ */
