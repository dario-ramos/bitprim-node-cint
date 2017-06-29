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
 * @file transaction.h
 * @brief Functions for manipulating a Bitcoin transaction
 *
 */

#ifndef BITPRIM_NODE_CINT_TRANSACTION_H_
#define BITPRIM_NODE_CINT_TRANSACTION_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Release memory held by transaction instance
 * @param transaction Handle to transaction instance
 */
BITPRIM_EXPORT
void transaction_destruct(transaction_t transaction);

/**
 * @brief Determine if a transaction is valid
 * @param transaction Handle to transaction instance
 * @return True (non zero) iif a transaction is valid
 */
BITPRIM_EXPORT
int transaction_is_valid(transaction_t transaction);

/**
 * @brief Get transaction version
 * @param transaction Handle to transaction instance
 * @return Transaction version
 */
BITPRIM_EXPORT
uint32_t transaction_version(transaction_t transaction);

/**
 * @brief Set transaction version
 * @param transaction Handle to transaction instance
 * @param version New value for transaction version
 */
BITPRIM_EXPORT
void transaction_set_version(transaction_t transaction, uint32_t version);

/**
 * @brief Get transaction hash
 * @param transaction Handle to transaction instance
 * @return Transaction hash as byte array. Must be released by calling delete[]
 */
BITPRIM_EXPORT
hash_t transaction_hash(transaction_t transaction);

/**
 * @brief Get transaction sighash by type
 * @param transaction Handle to transaction instance
 * @param sighash_type Sighash type
 * @return Sighash as byte array. Must be released by calling delete[]
 */
BITPRIM_EXPORT
hash_t transaction_hash_sighash_type(transaction_t transaction, uint32_t sighash_type);

/**
 * @brief Get transaction locktime
 * @param transaction Handle to transaction instance
 * @return Transaction locktime
 */
BITPRIM_EXPORT
uint32_t transaction_locktime(transaction_t transaction);

/**
 * @brief Get transaction serialized size
 * @param transaction Handle to transaction instance
 * @param wire Deprecated; currently ignored
 * @return Transaction serialized size
 */
BITPRIM_EXPORT
size_t transaction_serialized_size(transaction_t transaction, int wire /*= true*/);

/**
 * @brief Get transaction fees
 * @param transaction Handle to transaction instance
 * @return Transaction fees
 */
BITPRIM_EXPORT
uint64_t transaction_fees(transaction_t transaction);

/**
 * @brief Get transaction signature operations count
 * @param transaction Handle to transaction instance
 * @return Transaction signature operations count
 */
BITPRIM_EXPORT
size_t transaction_signature_operations(transaction_t transaction);

/**
 * @brief Get transaction BIP0016 signature operations count
 * @param transaction Handle to transaction instance
 * @param bip16_active: If true, only consider active operations
 * @return Transaction BIP0016 signature operations count
 */
BITPRIM_EXPORT
size_t transaction_signature_operations_bip16_active(transaction_t transaction, int /*bool*/ bip16_active);

/**
 * @brief Get the sum of the transaction input values
 * @param transaction Handle to transaction instance
 * @return Sum of transaction input values
 */
BITPRIM_EXPORT
uint64_t transaction_total_input_value(transaction_t transaction);

/**
 * @brief Get the sum of the transaction output values
 * @param transaction Handle to transaction instance
 * @return Sum of transaction output values
 */
BITPRIM_EXPORT
uint64_t transaction_total_output_value(transaction_t transaction);

/**
 * @brief Determine if a transaction is coinbase
 * @param transaction Handle to transaction instance
 * @return True (non zero) iif transaction is coinbase
 */
BITPRIM_EXPORT
int /*bool*/ transaction_is_coinbase(transaction_t transaction);

/**
 * @brief Determine if a transaction is null and not coinnase
 * @param transaction Handle to transaction instance
 * @return True (non zero) iif the transaction is null and not coinbase
 */
BITPRIM_EXPORT
int /*bool*/ transaction_is_null_non_coinbase(transaction_t transaction);

/**
 * @brief Determine if a transaction is oversized coinbase
 * @param transaction Handle to transaction instance
 * @return True (non zero) iif the transaction is oversized coinbase
 */
BITPRIM_EXPORT
int /*bool*/ transaction_is_oversized_coinbase(transaction_t transaction);

/**
 * @brief Determine if a transaction is immature
 * @param transaction Handle to transaction instance
 * @param target_height Target height
 * @return True (non zero) iif the transaction is immature
 */
BITPRIM_EXPORT
int /*bool*/ transaction_is_immature(transaction_t transaction, size_t target_height);

/**
 * @brief Determine if a transaction is overspent
 * @param transaction Handle to transaction instance
 * @return True (non zero) iif the transaction is overspent
 */
BITPRIM_EXPORT
int /*bool*/ transaction_is_overspent(transaction_t transaction);

/**
 * @brief Determine if a transaction is double spent
 * @param transaction Handle to transaction instance
 * @param include_unconfirmed Tells whether to include unconfirmed outputs/inputs
 * @return True (non zero) iif transaction is double spent
 */
BITPRIM_EXPORT
int /*bool*/ transaction_is_double_spend(transaction_t transaction, int /*bool*/ include_unconfirmed);

/**
 * @brief Determine whether transaction is missing previous outputs
 * @param transaction Handle to transaction instance
 * @return True (non zero) iif transaction is missing previous outputs
 */
BITPRIM_EXPORT
int /*bool*/ transaction_is_missing_previous_outputs(transaction_t transaction);

/**
 * @brief Determine if a transaction is final
 * @param transaction Handle to transaction instance
 * @param block_height Transaction block height
 * @param block_time Transaction block time
 * @return True (non zero) iif the transaction is final
 */
BITPRIM_EXPORT
int /*bool*/ transaction_is_final(transaction_t transaction, size_t block_height, uint32_t block_time);

/**
 * @brief Determine if a transaction incurs in a locktime conflict
 * @param transaction Handle to transaction instance
 * @return True (non zero) iif the transaction incurs in a locktime conflict
 */
BITPRIM_EXPORT
int /*bool*/ transaction_is_locktime_conflict(transaction_t transaction);

/**
 * @brief Get transaction output count
 * @param transaction Handle to transaction instance
 * @return Transaction output count
 */
BITPRIM_EXPORT
size_t transaction_output_count(transaction_t transaction);

/**
 * @brief Get the transaction's n-th output
 * @param transaction Handle to transaction instance
 * @param n Index to select transaction output. Starts at 0 (zero) for the first one
 * @return Handle to n-th transaction output. Must be released by calling output_destruct()
 */
BITPRIM_EXPORT
output_t transaction_output_nth(transaction_t transaction, size_t n);

/**
 * @brief Get transaction input count
 * @param transaction Handle to transaction instance
 * @return Transaction input count
 */
BITPRIM_EXPORT
size_t transaction_input_count(transaction_t transaction);

/**
 * @brief Get n-th transaction input
 * @param transaction Handle to transaction instance
 * @param n Index to transaction input. Starts at 0 (zero) for the first one
 * @return Transaction's n-th input
 */
BITPRIM_EXPORT
input_t transaction_input_nth(transaction_t transaction, size_t n);



#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODE_CINT_TRANSACTION_H_ */
