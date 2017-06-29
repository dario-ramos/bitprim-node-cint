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
 * @file block.h
 * @brief Functions for manipulating a block from the blockchain
 *
 */

#ifndef BITPRIM_NODE_CINT_BLOCK_H_
#define BITPRIM_NODE_CINT_BLOCK_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Release the memory held by a block object
 * @param block Handle to a block instance
 */
BITPRIM_EXPORT
void block_destruct(block_t block);

/**
 * @brief Determine if a block is valid
 * @param block Handle to a block instance
 * @return True (non zero) iif the block is valid
 */
BITPRIM_EXPORT
int block_is_valid(block_t block);

/**
 * @brief Get the block's header
 * @param block Handle to a block instance
 * @return Handle to the block's header. Must be released by calling header_destruct()
 */
BITPRIM_EXPORT
header_t block_header(block_t block);

/**
 * @brief Get the block's hash
 * @param block Handle to a block instance
 * @return Block hash as a byte array. Must be released by calling delete[]
 */
BITPRIM_EXPORT
hash_t block_hash(block_t block);

/**
 * @brief Get the block's transaction count
 * @param block Handle to a block instance
 * @return The amount of transactions that comprise the block
 */
BITPRIM_EXPORT
size_t block_transaction_count(block_t block);

/**
 * @brief Get the block's n-th transaction
 * @param block Handle to a block instance
 * @param n Index to the desired transaction. Starts at zero (0) for the first one
 * @return Handle to the selected transaction. Must be released by calling transaction_destruct()
 */
BITPRIM_EXPORT
transaction_t block_transaction_nth(block_t block, size_t n);

/**
 * @brief Get the block's serialized size
 * @param block Handle to a block instance
 * @param version The protocol version as a 32-bit integer
 * @return The block's serialized size
 */
BITPRIM_EXPORT
size_t block_serialized_size(block_t block, uint32_t version);

/**
 * @brief Get the block subsidy (miner_reward = block_subsidy + transaction_fees)
 * @param height The block's height
 * @return The block's subsidy
 */
BITPRIM_EXPORT
/*static*/
uint64_t block_subsidy(size_t height);

/**
 * @brief Get the block's total transaction fees (miner_reward = block_subsidy + transaction_fees)
 * @param block Handle to a block instance
 * @return The block's total transaction fees
 */
BITPRIM_EXPORT
uint64_t block_fees(block_t block);

/**
 * @brief Get the block's claim
 * @param block Handle to a block instance
 * @return The block's claim
 */
BITPRIM_EXPORT
uint64_t block_claim(block_t block);

/**
 * @brief Get the block's miner reward (miner_reward = block_subsidy + transaction_fees)
 * @param block Handle to a block instance
 * @param height The block's height
 * @return The block's miner reward
 */
BITPRIM_EXPORT
uint64_t block_reward(block_t block, size_t height);

/**
 * @brief Generate a Merkle root for a block
 * @param block Handle to a block instance
 * @return The new Merkle root's hash. Must be released by calling delete[]
 */
BITPRIM_EXPORT
hash_t block_generate_merkle_root(block_t block);

/**
 * @brief Get the block's signature operations count
 * @param block Handle to a block instance
 * @return Amount of block signature operations
 */
BITPRIM_EXPORT
size_t block_signature_operations(block_t block);

/**
 * @brief Get the block's BIP0016 signature operations count
 * @param block Handle to a block instance
 * @param bip16_active If true (non zero), don't consider inactive operations for the total count
 * @return Amount of BIP0016 block signature operations
 */
BITPRIM_EXPORT
size_t block_signature_operations_bip16_active(block_t block, int /*bool*/ bip16_active);

/**
 * @brief Get the block's input count
 * @param block Handle to a block instance
 * @param with_coinbase If true (non zero), count coinbase inputs
 * @return Amount of inputs owned by the transaction
 */
BITPRIM_EXPORT
size_t block_total_inputs(block_t block, int /*bool*/ with_coinbase /*= true*/);

/**
 * @brief Determine if a block has extra coinbases
 * @param block Handle to a block instance
 * @return True (non zero) iif the block has extra coinbases
 */
BITPRIM_EXPORT
int /*bool*/ block_is_extra_coinbases(block_t block);

/**
 * @brief Determine if a block is final
 * @param block Handle to a block instance
 * @param height Block height
 * @return True (non zero) iif the block is final
 */
BITPRIM_EXPORT
int /*bool*/ block_is_final(block_t block, size_t height);

/**
 * @brief Determine if a block contains a distinct transaction set
 * @param block Handle to a block instance
 * @return True (non zero) iif the block contains a distinct transaction set
 */
BITPRIM_EXPORT
int /*bool*/ block_is_distinct_transaction_set(block_t block);

/**
 * @brief Determine if a block contains a valid coinbase claim
 * @param block Handle to a block instance
 * @param height Block height
 * @return True (non zero) iif the block contains a valid coinbase claim
 */
BITPRIM_EXPORT
int /*bool*/ block_is_valid_coinbase_claim(block_t block, size_t height);

/**
 * @brief Determine if a block contains a valid coinbase script
 * @param block Handle to a block instance
 * @param height Block height
 * @return True (non zero) iif the block contains a valid coinbase script
 */
BITPRIM_EXPORT
int /*bool*/ block_is_valid_coinbase_script(block_t block, size_t height);

/**
 * @brief Determine if a block contains an internal double spend
 * @param block Handle to a block instance
 * @return True (non zero) iif the block contains an internal double spend
 */
BITPRIM_EXPORT
int /*bool*/ block_is_internal_double_spend(block_t block);

/**
 * @brief Determine if a block has a valid Merkle root
 * @param block Handle to a block instance
 * @return True (non zero) iif the block has a valid Merkle root
 */
BITPRIM_EXPORT
int /*bool*/ block_is_valid_merkle_root(block_t block);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODE_CINT_BLOCK_H_ */
