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
 * @file compact_block.h
 * @brief Functions for manipulating a compact block from the blockchain
 *
 */

#ifndef BITPRIM_NODE_CINT_COMPACT_BLOCK_H
#define BITPRIM_NODE_CINT_COMPACT_BLOCK_H

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

//TODO Dario check how to map compact_block::short_ids()

/**
 * @brief Get compact block header
 * @param block Handle to a compact block instance
 * @return Handle to the compact block's header. Must be released by calling header_destruct()
 */
BITPRIM_EXPORT
header_t compact_block_header(compact_block_t block);

/**
 * @brief Determine if a compact block is valid
 * @param block Handle to a compact block instance
 * @return True (non zero) iif the compact block is valid
 */
BITPRIM_EXPORT
int /*bool*/ compact_block_is_valid(compact_block_t block);

/**
 * @brief Get a compact block's serialized size
 * @param block Handle to a compact block instance
 * @param version Protocol version
 * @return The compact block's serialized size
 */
BITPRIM_EXPORT
size_t compact_block_serialized_size(compact_block_t block, uint32_t version);

/**
 * @brief Get the compact block's transaction count
 * @param block Handle to a compact block instance
 * @return Amount of transactions that comprise the compact block
 */
BITPRIM_EXPORT
size_t compact_block_transaction_count(compact_block_t block);

/**
 * @brief Get a compact block's n-th transaction
 * @param block Handle to a compact block instance
 * @param n Index to the transaction inside the block. Starts at 0 (zero) for the first one
 * @return Handle to the n-th transaction. Must be released by calling transaction_destruct()
 */
BITPRIM_EXPORT
transaction_t compact_block_transaction_nth(compact_block_t block, size_t n);

/**
 * @brief Get compact block's nonce
 * @param block Handle to a compact block instance
 * @return Compact block's nonce
 */
BITPRIM_EXPORT
uint64_t compact_block_nonce(compact_block_t block);

/**
 * @brief Release memory held by compact block instance
 * @param block Handle to a compact block instance
 */
BITPRIM_EXPORT
void compact_block_destruct(compact_block_t block);

/**
 * @brief Reset compact block
 * @param block Handle to a compact block instance
 */
BITPRIM_EXPORT
void compact_block_reset(compact_block_t block);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //BITPRIM_NODE_CINT_COMPACT_BLOCK_H
