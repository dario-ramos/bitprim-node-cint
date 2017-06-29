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
 * @file node.h
 * @brief Functions for manipulating a node in the network
 *
 */

#ifndef BITPRIM_NODE_CINT_FULL_NODE_H_
#define BITPRIM_NODE_CINT_FULL_NODE_H_

#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct node* node_t;


/**
 * @brief Create a new node instance
 * @param path Points to node configuration file
 * @return Handle to new node instance. Must be released by calling node_destruct()
 */
BITPRIM_EXPORT
node_t node_construct(char const* path);

/**
 * @brief Release memory held by node
 * @param node Handle to a node instance
 */
BITPRIM_EXPORT
void node_destruct(node_t node);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODE_CINT_FULL_NODE_H_ */
