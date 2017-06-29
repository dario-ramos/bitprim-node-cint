/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
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
 * @file history_compact.h
 * @brief Functions for manipulating a transaction history entry
 */

#ifndef BITPRIM_NODE_CINT_HISTORY_COMPACT_H
#define BITPRIM_NODE_CINT_HISTORY_COMPACT_H

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the entry's point kind
 * @param history Handle to a history entry instance
 * @return Entry's point kind
 */
BITPRIM_EXPORT
point_kind_t history_compact_get_point_kind(history_compact_t history);

/**
 * @brief Get the entry's point
 * @param history Handle to a history entry instance
 * @return Entry's point
 */
BITPRIM_EXPORT
point_t history_compact_get_point(history_compact_t history);

/**
 * @brief Get the height of history entry in the blockchain
 * @param history Handle to a history entry instance
 * @return Entry height in the blockchain
 */
BITPRIM_EXPORT
uint32_t history_compact_get_height(history_compact_t history);

/**
 * @brief Get the entry's value
 * @param history Handle to a history entry instance
 * @return Entry value, which can be a Satoshi value if point kind is output, or the previous entry's checksum if point
 * kind is spend
 */
BITPRIM_EXPORT
uint64_t history_compact_get_value_or_previous_checksum(history_compact_t history);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //BITPRIM_NODE_CINT_HISTORY_COMPACT_H
