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
 */

#include <bitprim/nodecint/transaction.h>
#include <bitcoin/bitcoin/message/transaction.hpp>
//#include <memory>
//#include <boost/iostreams/device/file_descriptor.hpp>
//#include <bitprim/nodecint/executor.hpp>
//#include <inttypes.h>   //TODO: Remove, it is for the printf (printing pointer addresses)

extern "C" {

void transaction_destruct(transaction_t transaction) {
    auto transaction_cpp = static_cast<libbitcoin::message::transaction*>(transaction);
    delete transaction_cpp;
}

int transaction_is_valid(transaction_t transaction) {
    return static_cast<libbitcoin::message::transaction const*>(transaction)->is_valid();
}

uint32_t transaction_version(transaction_t transaction) {
    return static_cast<libbitcoin::message::transaction const*>(transaction)->version();
}

void transaction_set_version(transaction_t transaction, uint32_t version) {
    return static_cast<libbitcoin::message::transaction*>(transaction)->set_version(version);
}

hash_t transaction_hash(transaction_t transaction) {
    auto hash_cpp = static_cast<libbitcoin::message::transaction const*>(transaction)->hash();
    return hash_cpp.data();
}


//
//// Serialization.
////-----------------------------------------------------------------------------
//
//data_chunk to_data(bool wire=true) const;
//void to_data(std::ostream& stream, bool wire=true) const;
//void to_data(writer& sink, bool wire=true) const;
//
//// Properties (size, accessors, cache).
////-----------------------------------------------------------------------------
//
//size_t serialized_size(bool wire=true) const;
//
//uint32_t locktime() const;
//void set_locktime(uint32_t value);
//
//// Deprecated (unsafe).
//ins& inputs();
//
//const input::list& inputs() const;
//void set_inputs(const ins& value);
//void set_inputs(ins&& value);
//
//// Deprecated (unsafe).
//outs& outputs();
//
//const outs& outputs() const;
//void set_outputs(const outs& value);
//void set_outputs(outs&& value);
//
//hash_digest hash(uint32_t sighash_type) const;
//
//void recompute_hash();
//
//// Validation.
////-----------------------------------------------------------------------------
//
//uint64_t fees() const;
//output_point::list missing_previous_outputs() const;
//hash_list missing_previous_transactions() const;
//uint64_t total_input_value() const;
//uint64_t total_output_value() const;
//size_t signature_operations() const;
//size_t signature_operations(bool bip16_active) const;
//
//bool is_coinbase() const;
//bool is_null_non_coinbase() const;
//bool is_oversized_coinbase() const;
//bool is_immature(size_t target_height) const;
//bool is_overspent() const;
//bool is_double_spend(bool include_unconfirmed) const;
//bool is_missing_previous_outputs() const;
//bool is_final(size_t block_height, uint32_t block_time) const;
//bool is_locktime_conflict() const;
//
//code check(bool transaction_pool=true) const;
//code accept(bool transaction_pool=true) const;
//code accept(const chain_state& state, bool transaction_pool=true) const;
//code connect() const;
//code connect(const chain_state& state) const;
//code connect_input(const chain_state& state, size_t input_index) const;


} /* extern "C" */