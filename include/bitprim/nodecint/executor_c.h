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
 * @file executor_c.h
 * @brief Functions for manipulating a node in the Bitcoin network
 */

#ifndef BITPRIM_NODE_CINT_EXECUTOR_H_
#define BITPRIM_NODE_CINT_EXECUTOR_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Creates an executor instance, which controls a node in the network
 * @param path Points to node configuration file
 * @param sout FILE* to where standard output will be redirected
 * @param serr FILE* to which standard error output will be redirected
 * @return A new executor instance. Must be released manually by calling executor_destruct()
 */
BITPRIM_EXPORT
executor_t executor_construct(char const* path, FILE* sout, FILE* serr);

/**
 * @brief Creates an executor instance, which controls a node in the network
 * @param path Points to node configuration file
 * @param sout_fd File descriptor to where standard output will be redirected
 * @param serr_fd File descriptor to which standard error output will be redirected
 * @return A new executor instance. Must be released manually by calling executor_destruct()
 */
BITPRIM_EXPORT
executor_t executor_construct_fd(char const* path, int sout_fd, int serr_fd);


#if defined(_WIN32)

/**
 * @brief Creates an executor instance, which controls a node in the network. This version is for Windows systems
 * @param path Points to node configuration file
 * @param sout HANDLE to where standard output will be redirected
 * @param serr HANDLE to which standard error output will be redirected
 * @return A new executor instance. Must be released manually by calling executor_destruct()
 */
BITPRIM_EXPORT
executor_t executor_construct_handles(char const* path, void* sout, void* serr);

#endif /* defined(_WIN32) */



/**
 * @brief Destroys an executor instance (it only releases memory)
 * @param exec Handle to executor instance
 */
BITPRIM_EXPORT
void executor_destruct(executor_t exec);

/**
 * @brief After executor_initchain() has been called, the node can be started using this function.
 * This is an asynchronous function, hence the callback parameter.
 * @param exec Handle to executor instance
 * @param handler Callback which will be invoked when the node starts running. It must point to a C function
 * matching the signature defined by run_handler_t @sa run_handler_t
 */
BITPRIM_EXPORT
void executor_run(executor_t exec, run_handler_t handler);

/**
 * @brief After executor_initchain() has been called, the node can be started using this function.
 * This is a synchronous function, so it will block until node has started running
 * @param exec Handle to executor instance
 * @return Error code. Zero for success, non zero for error.
 */
BITPRIM_EXPORT
int executor_run_wait(executor_t exec);

/**
 * @brief Initializes the chain for this node. It only creates the structure; the blockchain won't be synced
 * @param exec Handle to executor instance
 * @return Error code. Zero for success, non zero for error.
 */
BITPRIM_EXPORT
int executor_initchain(executor_t exec);

/**
 * @brief Stops execution of the node
 * @param exec Handle to executor instance
 */
BITPRIM_EXPORT
void executor_stop(executor_t exec);

/**
 * @brief Get the current blockchain height
 * @param exec Handle to executor instance
 * @param handler Callback which will be invoked when the blockchain height is retrieved from the network, or retrieval
 * fails. This parameter must point to a C function matching the signature defined by last_height_fetch_handler_t
 * @sa last_height_fetch_handler_t
 */
BITPRIM_EXPORT
void fetch_last_height(executor_t exec, last_height_fetch_handler_t handler);

/**
 * @brief Get the current blockchain height. This is the synchronous version of fetch_last_height(),
 * so it will block until height is retrieved from the network, or an error occurs
 * @param exec Handle to executor instance
 * @param[out] height Current blockchain height
 * @return Error code. Zero for success, non zero for error
 */
BITPRIM_EXPORT
int get_last_height(executor_t exec, size_t* height);

/**
 * @brief Given a block, get its height in the blockchain
 * @param exec Handle to executor instance
 * @param hash Block hash, which univocally identifies a single block, as an array of bytes
 * @param handler Callback which will be invoked when the block height is retrieved from the network, or retrieval
 * fails. This parameter must point to a C function matching the signature defined by block_height_fetch_handler_t
 * @sa block_height_fetch_handler_t
 */
BITPRIM_EXPORT
void fetch_block_height(executor_t exec, hash_t hash, block_height_fetch_handler_t handler);

/**
 * @brief Given a block, get its height in the blockchain. This is the synchronous version of fetch_block_height(),
 * so it will block until height is retrieved from the network, or an error occurs
 * @param exec Handle to executor instance
 * @param hash Block hash, which univocally identifies a single block, as an array of bytes
 * @param[out] height Block height
 * @return Error code. Zero for success, non zero for error
 */
BITPRIM_EXPORT
int get_block_height(executor_t exec, hash_t hash, size_t* height);


// Block Header ---------------------------------------------------------------------

/**
 * @brief Given a height in the blockchain, retrieve its block's header
 * @param exec Handle to executor instance
 * @param height The height which identifies the desired block
 * @param handler Callback which will be invoked when the block header is retrieved from the network, or retrieval
 * fails. This parameter must point to a C function matching the signature defined by block_header_fetch_handler_t
 * @sa block_header_fetch_handler_t
 */
BITPRIM_EXPORT
void fetch_block_header_by_height(executor_t exec, size_t height, block_header_fetch_handler_t handler);

/**
 * @brief Given a height in the blockchain, retrieve its block's header.
 * This is the synchronous version of fetch_block_header_by_height(),
 * so it will block until the header is retrieved from the network, or an error occurs
 * @param exec Handle to executor instance
 * @param height The height which identifies the desired block
 * @param[out] header The block's header. It must be released by calling header_destruct()
 * @param[out] ret_height The block's height
 * @return Error code. Zero for success, non zero for error
 */
BITPRIM_EXPORT
int get_block_header_by_height(executor_t exec, size_t height, header_t* header, size_t* ret_height);

/**
 * @brief Given a block hash, retrieve its header
 * @param exec Handle to executor instance
 * @param hash The hash which identifies the desired block
 * @param handler Callback which will be invoked when the block header is retrieved from the network, or retrieval
 * fails. This parameter must point to a C function matching the signature defined by block_header_fetch_handler_t
 * @sa block_header_fetch_handler_t
 */
BITPRIM_EXPORT
void fetch_block_header_by_hash(executor_t exec, hash_t hash, block_header_fetch_handler_t handler);

/**
 * @brief Given a block hash, retrieve its header.
 * This is the synchronous version of fetch_block_header_by_height(),
 * so it will block until the header is retrieved from the network, or an error occurs
 * @param exec Handle to executor instance
 * @param hash The hash which identifies the desired block
 * @param[out] header Block header
 * @param[out] ret_height Block height
 * @return Error code. Zero for success, non zero for error
 */
BITPRIM_EXPORT
int get_block_header_by_hash(executor_t exec, hash_t hash, header_t* header, size_t* ret_height);


// Block ---------------------------------------------------------------------

/**
 * @brief Given a block's height, retrieve the block
 * @param exec Handle to executor instance
 * @param height The height which identifies the desired block
 * @param handler Callback which will be invoked when the block is retrieved from the network, or retrieval
 * fails. This parameter must point to a C function matching the signature defined by block_fetch_handler_t
 * @sa block_fetch_handler_t
 */
BITPRIM_EXPORT
void fetch_block_by_height(executor_t exec, size_t height, block_fetch_handler_t handler);

/**
 * @brief Given a block's height, retrieve the block.
 * This is the synchronous version of fetch_block_by_height(),
 * so it will block until the block is retrieved from the network, or an error occurs
 * @param exec Handle to executor instance
 * @param height The height which identifies the desired block
 * @param[out] block Block
 * @param[out] ret_height Block height
 * @return Error code. Zero for success, non zero for error
 */
BITPRIM_EXPORT
int get_block_by_height(executor_t exec, size_t height, block_t* block, size_t* ret_height);

/**
 * @brief Given a block's hash, retrieve the block
 * @param exec Handle to executor instance
 * @param hash The hash which identifies the desired block
 * @param handler Callback which will be invoked when the block is retrieved from the network, or retrieval
 * fails. This parameter must point to a C function matching the signature defined by block_fetch_handler_t
 * @sa block_fetch_handler_t
 */
BITPRIM_EXPORT
void fetch_block_by_hash(executor_t exec, hash_t hash, block_fetch_handler_t handler);

/**
 * @brief Given a block's hash, retrieve the block.
 * This is the synchronous version of fetch_block_by_height(),
 * so it will block until the block is retrieved from the network, or an error occurs
 * @param exec Handle to executor instance
 * @param hash The hash which identifies the desired block
 * @param[out] block Handle to block. Must be released by calling block_destruct()
 * @param[out] ret_height Block height
 * @return Error code. Zero for success, non zero for error
 */
BITPRIM_EXPORT
int get_block_by_hash(executor_t exec, hash_t hash, block_t* block, size_t* ret_height);


// Merkle Block ---------------------------------------------------------------------

/**
 * @brief Given a Merkle block's height, retrieve the block
 * @param exec Handle to executor instance
 * @param height The height which identifies the desired block
 * @param handler Callback which will be invoked when the block is retrieved from the network, or retrieval
 * fails. This parameter must point to a C function matching the signature defined by merkle_block_fetch_handler_t
 * @sa merkle_block_fetch_handler_t
 */
BITPRIM_EXPORT
void fetch_merkle_block_by_height(executor_t exec, size_t height, merkle_block_fetch_handler_t handler);

/**
 * @brief Given a Merkle block's hash, retrieve the block
 * @param exec Handle to executor instance
 * @param hash The hash which identifies the desired block
 * @param handler Callback which will be invoked when the block is retrieved from the network, or retrieval
 * fails. This parameter must point to a C function matching the signature defined by merkle_block_fetch_handler_t
 * @sa merkle_block_fetch_handler_t
 */
BITPRIM_EXPORT
void fetch_merkle_block_by_hash(executor_t exec, hash_t hash, merkle_block_fetch_handler_t handler);

// Compact Block ---------------------------------------------------------------------

/**
 * @brief Given a compact block's height, retrieve the block
 * @param exec Handle to executor instance
 * @param height The height which identifies the desired block
 * @param handler Callback which will be invoked when the block is retrieved from the network, or retrieval
 * fails. This parameter must point to a C function matching the signature defined by compact_block_fetch_handler_t
 * @sa compact_block_fetch_handler_t
 */
BITPRIM_EXPORT
void fetch_compact_block_by_height(executor_t exec, size_t height, compact_block_fetch_handler_t handler);

/**
 * @brief Given a compact block's hash, retrieve the block
 * @param exec Handle to executor instance
 * @param hash The hash which identifies the desired block
 * @param handler Callback which will be invoked when the block is retrieved from the network, or retrieval
 * fails. This parameter must point to a C function matching the signature defined by compact_block_fetch_handler_t
 * @sa compact_block_fetch_handler_t
 */
BITPRIM_EXPORT
void fetch_compact_block_by_hash(executor_t exec, hash_t hash, compact_block_fetch_handler_t handler);


// Transaction ---------------------------------------------------------------------

/**
 * @brief Given a transaction hash, retrieve it (optionally requiring it to be confirmed)
 * @param exec Handle to executor instance
 * @param hash The hash which identifies the desired transaction
 * @param require_confirmed If this is set to true (non zero), the transaction will only be fetched if it has
 * already been confirmed
 * @param handler Callback which will be invoked when the transaction is retrieved from the network, or retrieval
 * fails. This parameter must point to a C function matching the signature defined by transaction_fetch_handler_t
 * @sa transaction_fetch_handler_t
 */
BITPRIM_EXPORT
void fetch_transaction(executor_t exec, hash_t hash, int require_confirmed, transaction_fetch_handler_t handler);

/**
 * @brief Given a transaction's hash, retrieve it
 * This is the synchronous version of fetch_transaction(),
 * so it will block until the transaction is retrieved from the network, or an error occurs
 * @param exec Handle to executor instance
 * @param hash The hash which identifies the desired transaction
 * @param require_confirmed If this is set to true (non zero), the transaction will only be fetched if it has
 * already been confirmed
 * @param[out] transaction Block
 * @param[out] ret_height Block height
 * @return Error code. Zero for success, non zero for error
 */
BITPRIM_EXPORT
int get_transaction(executor_t exec, hash_t hash, int require_confirmed, transaction_t* transaction, size_t* ret_height, size_t* index);

/**
 * @brief Given a transaction hash, retrieve its position inside the block (optionally requiring it to be confirmed)
 * @param exec Handle to executor instance
 * @param hash The hash which identifies the desired transaction
 * @param require_confirmed If this is set to true (non zero), the transaction will only be fetched if it has
 * already been confirmed
 * @param handler Callback which will be invoked when the transaction position is retrieved from the network,
 * or retrieval fails. This parameter must point to a C function matching the signature defined by
 * transaction_index_fetch_handler_t
 * @sa transaction_index_fetch_handler_t
 */
BITPRIM_EXPORT
void fetch_transaction_position(executor_t exec, hash_t hash, int require_confirmed, transaction_index_fetch_handler_t handler);


// Output  ---------------------------------------------------------------------

/**
 * @brief Given an output hash, retrieve it (optionally requiring it to be confirmed)
 * @param exec Handle to executor instance
 * @param hash The hash which identifies the output's transaction
 * @param index The index which identifies the output among the transaction's other outputs
 * @param require_confirmed If this is set to true (non zero), the output will only be fetched if it has
 * already been confirmed
 * @param handler Callback which will be invoked when the output is retrieved from the network,
 * or retrieval fails. This parameter must point to a C function matching the signature defined by
 * output_fetch_handler_t
 * @sa output_fetch_handler_t
 */
BITPRIM_EXPORT
void fetch_output(executor_t exec, hash_t hash, uint32_t index, int require_confirmed, output_fetch_handler_t handler);

/**
 * @brief Given an output's hash, retrieve it
 * This is the synchronous version of fetch_output(),
 * so it will block until the output is retrieved from the network, or an error occurs
 * @param exec Handle to executor instance
 * @param hash The hash which identifies the desired output
 * @param index The index which identifies the output among the transaction's other outputs
 * @param require_confirmed If this is set to true (non zero), the output will only be fetched if it has
 * already been confirmed
 * @param[out] output Handle to output. Must be released by calling output_destruct()
 * @return Error code. Zero for success, non zero for error
 */
BITPRIM_EXPORT
int get_output(executor_t exec, hash_t hash, uint32_t index, int require_confirmed, output_t* output);

// Spend ---------------------------------------------------------------------

/**
 * @brief Given an output point, retrieve its spend
 * @param exec Handle to executor instance
 * @param outpoint The output point whose spend we wish to retrieve
 * @param handler Callback which will be invoked when the spend is retrieved from the network,
 * or retrieval fails. This parameter must point to a C function matching the signature defined by
 * spend_fetch_handler_t
 * @sa spend_fetch_handler_t
 */
BITPRIM_EXPORT
void fetch_spend(executor_t exec, output_point_t outpoint, spend_fetch_handler_t handler);

// History ---------------------------------------------------------------------

/**
 * @brief Given a payment address, a starting height and an entry limit, retrieve its transaction history
 * @param exec Handle to executor instance
 * @param address Payment address whose history we want to fetch
 * @param limit Maximum entries to fetch
 * @param from_height Starting blockchain height for the history
 * @param handler Callback which will be invoked when the history is retrieved from the network,
 * or retrieval fails. This parameter must point to a C function matching the signature defined by
 * history_fetch_handler_t
 * @sa history_fetch_handler_t
 */
BITPRIM_EXPORT
void fetch_history(executor_t exec, payment_address_t address, size_t limit, size_t from_height, history_fetch_handler_t handler);

/**
 * @brief Given a payment address, a starting height and an entry limit, retrieve its transaction history
 * This is the synchronous version of fetch_history(),
 * so it will block until the history is retrieved from the network, or an error occurs
 * @param exec Handle to executor instance
 * @param address Payment address whose history we want to fetch
 * @param limit Maximum entries to fetch
 * @param from_height Starting blockchain height for the history
 * @param[out] out_history Handle to history. Must be released by calling history_compact_list_destruct()
 * @return Error code. Zero for success, non zero for error
 */
BITPRIM_EXPORT
int get_history(executor_t exec, payment_address_t address, size_t limit, size_t from_height, history_compact_list_t* out_history);


//BITPRIM_EXPORT
//void fetch_stealth(const binary& filter, size_t from_height, stealth_fetch_handler handler);

// ------------------------------------------------

/**
 * @brief Converts a raw transaction hex string to a transaction object
 * @param tx_hex Raw transaction hex string
 * @return Handle to new transaction object built from the hex string. Must be released by calling
 * transaction_destruct()
 */
BITPRIM_EXPORT
transaction_t hex_to_tx(char const* tx_hex);

/**
 * @brief Validates a new transaction (has not been added to the blockchain yet)
 * @param exec Handle to executor instance
 * @param tx Transaction to validate
 * @param handler Callback which will be invoked when the history is retrieved from the network,
 * or retrieval fails. This parameter must point to a C function matching the signature defined by
 * validate_tx_handler_t
 * @sa validate_tx_handler_t
 */
BITPRIM_EXPORT
void validate_tx(executor_t exec, transaction_t tx, validate_tx_handler_t handler);

// ------------------------------------------------
// Wallet functions
// ------------------------------------------------
BITPRIM_EXPORT
/**
 * @brief Convert a set of keywords/mnemonics to an HD wallet seed
 * @param mnemonics List of keywords/mnemonics
 * @return Handle to long_hash object containing the seed. Must be released by calling long_hash_destroy()
 */
long_hash_t wallet_mnemonics_to_seed(word_list_t mnemonics);

BITPRIM_EXPORT
/**
 * @brief Release the memory held by a long hash object
 * @param ptr Handle to long hash object
 */
void long_hash_destroy(long_hash_t ptr);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODE_CINT_EXECUTOR_H_ */
