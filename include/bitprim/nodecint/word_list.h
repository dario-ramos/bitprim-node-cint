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
 * @file word_list.h
 * @brief Functions for manipulating a word list
 *
 */

#ifndef BITPRIM_NODE_CINT_WORD_LIST_H
#define BITPRIM_NODE_CINT_WORD_LIST_H

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create a new word list instance
 * @return Handle to new word list instance. Must be released by calling word_list_destruct()
 */
BITPRIM_EXPORT
word_list_t word_list_construct();

/**
 * Add a word to the word list
 * @param word_list Handle to a word list instance
 * @param word New word
 */
BITPRIM_EXPORT
void word_list_add_word(word_list_t word_list, const char* word);

/**
 * @brief Release memory held by word list object
 * @param word_list Handle to a word list instance
 */
BITPRIM_EXPORT
void word_list_destruct(word_list_t word_list);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //BITPRIM_NODE_CINT_WORD_LIST_H
