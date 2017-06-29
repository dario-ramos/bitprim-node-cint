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
 * @file primitives.h
 * @brief Common type definitions
 */

#ifndef BITPRIM_NODE_CINT_PRIMITIVES_H_
#define BITPRIM_NODE_CINT_PRIMITIVES_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef enum point_kind {output = 0, spend = 1} point_kind_t;

/**
 * @brief Wraps a pointer to an executor object
 */
typedef struct executor* executor_t;

/**
 * @brief Wraps a pointer to a block object
 */
typedef void* block_t;

/**
 * @brief Wraps a pointer to a compact_block object
 */
typedef void* compact_block_t;

/**
 * @brief Wraps a pointer to a header object
 */
typedef void* header_t;

/**
 * @brief Wraps a pointer to a history_compact object
 */
typedef void* history_compact_t;

/**
 * @brief Wraps a pointer to a history_compact_list object
 */
typedef void* history_compact_list_t;

/**
 * @brief Wraps a pointer to an input object
 */
typedef void* input_t;

/**
 * @brief Wraps a pointer to a merkle_block object
 */
typedef void* merkle_block_t;

/**
 * @brief Wraps a pointer to a script object
 */
typedef void* script_t;

/**
 * @brief Wraps a pointer to an output_point object
 */
typedef void* output_point_t;

/**
 * @brief Wraps a pointer to an output object
 */
typedef void* output_t;

/**
 * @brief Wraps a pointer to a point object
 */
typedef void* point_t;

/**
 * @brief Wraps a pointer to a point_list object
 */
typedef void* point_list_t;

/**
 * @brief Wraps a pointer to a transaction object
 */
typedef void* transaction_t;

/**
 * @brief Wraps a pointer to a payment_address object
 */
typedef void* payment_address_t;

/**
 * @brief Wraps a byte array
 */
typedef uint8_t const* hash_t;

/**
 * @brief Wraps a byte array
 */
typedef uint8_t* long_hash_t;

/**
 * @brief Wraps a word_list object
 */
typedef void* word_list_t;

/**
 * @brief Defines the signature for the fetch_block callback
 * @param error Error code returned by the callback. Zero for success, non zero for error
 * @param header Handle to block returned by the callback. Must be released by calling block_destruct()
 * @param h Block height
 */
typedef void (*block_fetch_handler_t)(int error, block_t block, size_t h);

/**
 * @brief Defines the signature for the fetch_block_height callback
 * @param error Error code returned by the callback. Zero for success, non zero for error
 * @param h Block height returned by the callback
 */
typedef void (*block_height_fetch_handler_t)(int error, size_t h);

/**
 * @brief Defines the signature for the fetch_block_header callback
 * @param error Error code returned by the callback. Zero for success, non zero for error
 * @param header Handle to header instance returned by the callback. Must be released by calling header_destruct()
 * @param h Block height
 */
typedef void (*block_header_fetch_handler_t)(int error, header_t header, size_t h);

/**
 * @brief Defines the signature for the fetch_compact_block callback
 * @param error Error code returned by the callback. Zero for success, non zero for error
 * @param block Handle to Compact block instance returned by the callback. Must be released by calling
 * compact_block_destruct
 * @param h Block height
 */
typedef void (*compact_block_fetch_handler_t)(int error, compact_block_t block, size_t h);

/**
 * @brief Defines the signature for the fetch_history callback
 * @param error Error code returned by the callback. Zero for success, non zero for error
 * @param history Handle to History object returned by the callback. Must be released by calling
 * history_compact_list_destruct()
 */
typedef void (*history_fetch_handler_t)(int error, history_compact_list_t history);

/**
 * @brief Defines the signature for the fetch_last_height callback
 * @param error Error code returned by the callback. Zero for success, non zero for error
 * @param h Current block chain height returned by the callback
 */
typedef void (*last_height_fetch_handler_t)(int error, size_t h);

/**
 * @brief Defines the signature for the fetch_merkle_block_header callback
 * @param error Error code returned by the callback. Zero for success, non zero for error
 * @param block Handle to Merkle Block instance returned by the callback. Must be released by calling
 * merkle_block_destruct()
 * @param h Block height
 */
typedef void (*merkle_block_fetch_handler_t)(int error, merkle_block_t block, size_t h);

/**
 * @brief Defines the signature for the fetch_output callback
 * @param error Error code returned by the callback. Zero for success, non zero for error
 * @param output Handle to the output returned by the callback. Must be released by calling output_destruct()
 */
typedef void (*output_fetch_handler_t)(int error, output_t output);

/**
 * @brief Defines the signature for the executor_run callback
 * @param error Error code returned by the callback. Zero for success, non zero for error
 */
typedef void (*run_handler_t)(int error);

/**
 * @brief Defines the signature for the fetch_spend callback
 * @param error Error code returned by the callback. Zero for success, non zero for error
 * @param input Handle to the input returned by the callback. Must be released by calling input_destruct()
 */
typedef void (*spend_fetch_handler_t)(int error, input_t input);

/**
 * @brief Defines the signature for the fetch_transaction callback
 * @param error Error code returned by the callback. Zero for success, non zero for error
 * @param transaction Handle to the transaction returned by the callback. Must be released by calling
 * transaction_destruct()
 */
typedef void (*transaction_fetch_handler_t)(int error, transaction_t transaction, size_t h, size_t i);

/**
 * @brief Defines the signature for the fetch_transaction_index callback
 * @param error Error code returned by the callback. Zero for success, non zero for error
 * @param position Transaction position returned by the callback
 * @param height Transaction block height returned by the callback
 */
typedef void (*transaction_index_fetch_handler_t)(int error, size_t position, size_t height);

/**
 * @brief Defines the signature for the validate_tx callback
 * @param error Error code returned by the callback. Zero for success, non zero for error
 * @param message Validation message returned by the callback
 */
typedef void (*validate_tx_handler_t)(int error, char* message);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODE_CINT_PRIMITIVES_H_ */
