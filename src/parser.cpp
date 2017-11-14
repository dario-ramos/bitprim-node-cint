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

#include <bitprim/nodecint/parser.hpp>

#include <cstdint>
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <bitcoin/blockchain.hpp>
#include <bitcoin/network.hpp>
#include <bitcoin/node/full_node.hpp>
#include <bitcoin/node/settings.hpp>

//BC_DECLARE_CONFIG_DEFAULT_PATH("libbitcoin" / "bn.cfg")

// TODO(libbitcoin): localize descriptions.

namespace bitprim { namespace nodecint {

using boost::filesystem::path;
using boost::program_options::value;
using boost::program_options::reading_file;

// Initialize configuration by copying the given instance.
parser::parser(libbitcoin::node::configuration const& defaults)
  : configured(defaults)
{}

// Initialize configuration using defaults of the given context.
parser::parser(libbitcoin::config::settings const& context)
  : configured(context)
{
    // A node doesn't require history, and history is expensive.
//    configured.database.index_start_height = libbitcoin::max_uint32;

#if WITH_NODE_REQUESTER
    // Default endpoint for blockchain replier.
    configured.chain.replier = { "tcp://localhost:5502" };
#endif

    // A node allows 8 inbound connections by default.
    configured.network.inbound_connections = 8;

    // A node allows 1000 host names by default.
    configured.network.host_pool_capacity = 1000;

    // A node requests transaction relay by default.
    configured.network.relay_transactions = true;

    // A node exposes full node (1) network services by default.
    configured.network.services = libbitcoin::message::version::service::node_network;
}

libbitcoin::options_metadata parser::load_options() {
    return libbitcoin::options_metadata("options");
}

libbitcoin::arguments_metadata parser::load_arguments() {
    libbitcoin::arguments_metadata description;
    return description;
}

libbitcoin::options_metadata parser::load_environment() {
    libbitcoin::options_metadata description("environment");
    return description;
}

libbitcoin::options_metadata parser::load_settings() {
    libbitcoin::options_metadata description("settings");
    description.add_options()
    /* [log] */
    (
        "log.debug_file",
        value<path>(&configured.network.debug_file),
        "The debug log file path, defaults to 'debug.log'."
    )
    (
        "log.error_file",
        value<path>(&configured.network.error_file),
        "The error log file path, defaults to 'error.log'."
    )
    (
        "log.archive_directory",
        value<path>(&configured.network.archive_directory),
        "The log archive directory, defaults to 'archive'."
    )
    (
        "log.rotation_size",
        value<size_t>(&configured.network.rotation_size),
        "The size at which a log is archived, defaults to 0 (disabled)."
    )
    (
        "log.minimum_free_space",
        value<size_t>(&configured.network.minimum_free_space),
        "The minimum free space required in the archive directory, defaults to 0."
    )
    (
        "log.maximum_archive_size",
        value<size_t>(&configured.network.maximum_archive_size),
        "The maximum combined size of archived logs, defaults to 0 (maximum)."
    )
    (
        "log.maximum_archive_files",
        value<size_t>(&configured.network.maximum_archive_files),
        "The maximum number of logs to archive, defaults to 0 (maximum)."
    )
    (
        "log.statistics_server",
        value<libbitcoin::config::authority>(&configured.network.statistics_server),
        "The address of the statistics collection server, defaults to none."
    )
    (
        "log.verbose",
        value<bool>(&configured.network.verbose),
        "Enable verbose logging, defaults to false."
    )
    /* [network] */
    (
        "network.threads",
        value<uint32_t>(&configured.network.threads),
        "The minimum number of threads in the network threadpool, defaults to 0 (physical cores)."
    )
    (
        "network.protocol_maximum",
        value<uint32_t>(&configured.network.protocol_maximum),
        "The maximum network protocol version, defaults to 70013."
    )
    (
        "network.protocol_minimum",
        value<uint32_t>(&configured.network.protocol_minimum),
        "The minimum network protocol version, defaults to 31402."
    )
    (
        "network.services",
        value<uint64_t>(&configured.network.services),
        "The services exposed by network connections, defaults to 1 (full node)."
    )
    (
        "network.validate_checksum",
        value<bool>(&configured.network.validate_checksum),
        "Validate the checksum of network messages, defaults to false."
    )
    (
        "network.identifier",
        value<uint32_t>(&configured.network.identifier),
        "The magic number for message headers, defaults to 3652501241."
    )
    (
        "network.inbound_port",
        value<uint16_t>(&configured.network.inbound_port),
        "The port for incoming connections, defaults to 8333."
    )
    (
        "network.inbound_connections",
        value<uint32_t>(&configured.network.inbound_connections),
        "The target number of incoming network connections, defaults to 8."
    )
    (
        "network.outbound_connections",
        value<uint32_t>(&configured.network.outbound_connections),
        "The target number of outgoing network connections, defaults to 8."
    )
    (
        "network.manual_attempt_limit",
        value<uint32_t>(&configured.network.manual_attempt_limit),
        "The attempt limit for manual connection establishment, defaults to 0 (forever)."
    )
    (
        "network.connect_batch_size",
        value<uint32_t>(&configured.network.connect_batch_size),
        "The number of concurrent attempts to establish one connection, defaults to 5."
    )
    (
        "network.connect_timeout_seconds",
        value<uint32_t>(&configured.network.connect_timeout_seconds),
        "The time limit for connection establishment, defaults to 5."
    )
    (
        "network.channel_handshake_seconds",
        value<uint32_t>(&configured.network.channel_handshake_seconds),
        "The time limit to complete the connection handshake, defaults to 30."
    )
    (
        "network.channel_heartbeat_minutes",
        value<uint32_t>(&configured.network.channel_heartbeat_minutes),
        "The time between ping messages, defaults to 5."
    )
    (
        "network.channel_inactivity_minutes",
        value<uint32_t>(&configured.network.channel_inactivity_minutes),
        "The inactivity time limit for any connection, defaults to 30."
    )
    (
        "network.channel_expiration_minutes",
        value<uint32_t>(&configured.network.channel_expiration_minutes),
        "The age limit for any connection, defaults to 1440."
    )
    (
        "network.channel_germination_seconds",
        value<uint32_t>(&configured.network.channel_germination_seconds),
        "The time limit for obtaining seed addresses, defaults to 30."
    )
    (
        "network.host_pool_capacity",
        value<uint32_t>(&configured.network.host_pool_capacity),
        "The maximum number of peer hosts in the pool, defaults to 1000."
    )
    (
        "network.hosts_file",
        value<path>(&configured.network.hosts_file),
        "The peer hosts cache file path, defaults to 'hosts.cache'."
    )
    (
        "network.self",
        value<libbitcoin::config::authority>(&configured.network.self),
        "The advertised public address of this node, defaults to none."
    )
    (
        "network.blacklist",
        value<libbitcoin::config::authority::list>(&configured.network.blacklists),
        "IP address to disallow as a peer, multiple entries allowed."
    )
    (
        "network.peer",
        value<libbitcoin::config::endpoint::list>(&configured.network.peers),
        "A persistent peer node, multiple entries allowed."
    )
    (
        "network.seed",
        value<libbitcoin::config::endpoint::list>(&configured.network.seeds),
        "A seed node for initializing the host pool, multiple entries allowed."
    )

    /* [database] */
    (
        "database.directory",
        value<path>(&configured.database.directory),
        "The blockchain database directory, defaults to 'blockchain'."
    )
    (
        "database.flush_writes",
        value<bool>(&configured.database.flush_writes),
        "Flush each write to disk, defaults to false."
    )
    (
        "database.file_growth_rate",
        value<uint16_t>(&configured.database.file_growth_rate),
        "Full database files increase by this percentage, defaults to 50."
    )
    (
        "database.block_table_buckets",
        value<uint32_t>(&configured.database.block_table_buckets),
        "Block hash table size, defaults to 650000."
    )
    (
        "database.transaction_table_buckets",
        value<uint32_t>(&configured.database.transaction_table_buckets),
        "Transaction hash table size, defaults to 110000000."
    )
    (
        "database.transaction_unconfirmed_table_buckets",
        value<uint32_t>(&configured.database.transaction_unconfirmed_table_buckets),
        "Unconfirmed Transaction hash table size, defaults to 10000."
    )
    (
        "database.cache_capacity",
        value<uint32_t>(&configured.database.cache_capacity),
        "The maximum number of entries in the unspent outputs cache, defaults to 0."
    )
#if defined(WITH_REMOTE_DATABASE)    
    (
        "database.replier",
        value<config::endpoint>(&configured.database.replier),
        "Database-blockchain connection, defaults to 127.0.0.1:5568."
    )    
#endif //defined(WITH_REMOTE_DATABASE)    

    /* [blockchain] */
    (
        "blockchain.cores",
        value<uint32_t>(&configured.chain.cores),
        "The number of cores dedicated to block validation, defaults to 0 (physical cores)."
    )
    (
        "blockchain.priority",
        value<bool>(&configured.chain.priority),
        "Use high thread priority for block validation, defaults to true."
    )
    (
        "blockchain.use_libconsensus",
        value<bool>(&configured.chain.use_libconsensus),
        "Use libconsensus for script validation if integrated, defaults to false."
    )
    (
        "blockchain.reorganization_limit",
        value<uint32_t>(&configured.chain.reorganization_limit),
        "The maximum reorganization depth, defaults to 256 (0 for unlimited)."
    )
    (
        "blockchain.checkpoint",
        value<libbitcoin::config::checkpoint::list>(&configured.chain.checkpoints),
        "A hash:height checkpoint, multiple entries allowed."
    )

    /* [fork] */
    (
        "fork.easy_blocks",
        value<bool>(&configured.chain.easy_blocks),
        "Allow minimum difficulty blocks, defaults to false."
    )
    (
        "fork.bip16",
        value<bool>(&configured.chain.bip16),
        "Add pay-to-script-hash processing, defaults to true (soft fork)."
    )
    (
        "fork.bip30",
        value<bool>(&configured.chain.bip30),
        "Disallow collision of unspent transaction hashes, defaults to true (hard fork)."
    )
    (
        "fork.bip34",
        value<bool>(&configured.chain.bip34),
        "Require coinbase input includes block height, defaults to true (soft fork)."
    )
    (
        "fork.bip66",
        value<bool>(&configured.chain.bip66),
        "Require strict signature encoding, defaults to true (soft fork)."
    )
    (
        "fork.bip65",
        value<bool>(&configured.chain.bip65),
        "Add check-locktime-verify op code, defaults to true (soft fork)."
    )
    (
        "fork.bip90",
        value<bool>(&configured.chain.bip90),
        "Assume bip34, bip65, and bip66 activation if enabled, defaults to true (hard fork)."
    )
#if defined(WITH_REMOTE_BLOCKCHAIN)
    (
        "blockchain.replier",
        value<config::endpoint>(&configured.chain.replier),
        "Blockchain Replier connect() endpoint."
    )
#endif // defined(WITH_REMOTE_BLOCKCHAIN)

    (
        "fork.bip68",
        value<bool>(&configured.chain.bip68),
        "Add relative locktime enforcement, defaults to true (soft fork)."
    )
    (
        "fork.bip112",
        value<bool>(&configured.chain.bip112),
        "Add check-sequence-verify op code, defaults to true (soft fork)."
    )
    (
        "fork.bip113",
        value<bool>(&configured.chain.bip113),
        "Use median time past for locktime, defaults to true (soft fork)."
    )

    /* [node] */
    ////(
    ////    "node.sync_peers",
    ////    value<uint32_t>(&configured.node.sync_peers),
    ////    "The maximum number of initial block download peers, defaults to 0 (physical cores)."
    ////)
    ////(
    ////    "node.sync_timeout_seconds",
    ////    value<uint32_t>(&configured.node.sync_timeout_seconds),
    ////    "The time limit for block response during initial block download, defaults to 5."
    ////)
    (
        "node.block_latency_seconds",
        value<uint32_t>(&configured.node.block_latency_seconds),
        "The time to wait for a requested block, defaults to 60."
    )
    (
        /* Internally this is blockchain, but it is conceptually a node setting. */
        "node.notify_limit_hours",
        value<uint32_t>(&configured.chain.notify_limit_hours),
        "Disable relay when top block age exceeds, defaults to 24 (0 disables)."
    )
    (
        /* Internally this is blockchain, but it is conceptually a node setting. */
        "node.byte_fee_satoshis",
        value<float>(&configured.chain.byte_fee_satoshis),
        "The minimum fee per byte, cumulative for conflicts, defaults to 1."
    )
    (
        /* Internally this is blockchain, but it is conceptually a node setting. */
        "node.sigop_fee_satoshis",
        value<float>(&configured.chain.sigop_fee_satoshis),
        "The minimum fee per sigop, additional to byte fee, defaults to 100."
    )
    (
        /* Internally this is blockchain, but it is conceptually a node setting. */
        "node.minimum_output_satoshis",
        value<uint64_t>(&configured.chain.minimum_output_satoshis),
        "The minimum output value, defaults to 500."
    )
    (
        /* Internally this is network, but it is conceptually a node setting. */
        "node.relay_transactions",
        value<bool>(&configured.network.relay_transactions),
        "Request that peers relay transactions, defaults to false."
    )
    (
        "node.refresh_transactions",
        value<bool>(&configured.node.refresh_transactions),
        "Request transactions on each channel start, defaults to true."
    )
    // TODO(bitprim): ver como implementamos esto para diferenciar server y node
    (
        /* Internally this database, but it applies to server.*/
        "node.index_start_height",
        value<uint32_t>(&configured.database.index_start_height),
        "The lower limit of address and spend indexing, defaults to 0."
    )
    ;

    return description;
}

// bool parser::load_configuration_variables(variables_map& variables, std::string const& option_name) {
bool parser::load_configuration_variables(variables_map& variables, boost::filesystem::path const& config_path) {

    auto const config_settings = load_settings();
    //auto const config_path = get_config_option(variables, option_name);

    // If the existence test errors out we pretend there's no file :/.
    boost::system::error_code code;
    if ( ! config_path.empty() && exists(config_path, code))
    {
        auto const& path = config_path.string();
        bc::ifstream file(path);

        if ( ! file.good())
        {
            BOOST_THROW_EXCEPTION(reading_file(path.c_str()));
        }

        auto const config = parse_config_file(file, config_settings);
        store(config, variables);
        return true;
    }

    // Loading from an empty stream causes the defaults to populate.
    std::stringstream stream;
    auto const config = parse_config_file(stream, config_settings);
    store(config, variables);
    return false;
}

// bool parser::parse(int argc, char const* argv[], std::ostream& error) {
bool parser::parse(boost::filesystem::path const& config_path, std::ostream& error) {
    try {
        variables_map variables;

        configured.file = config_path;
        auto file = load_configuration_variables(variables, config_path);

        // Update bound variables in metadata.settings.
        notify(variables);

        // Clear the config file path if it wasn't used.
        if ( ! file) {
            configured.file.clear();
        }

    } catch (boost::program_options::error const& e) {
        // This is obtained from boost, which circumvents our localization.
        error << format_invalid_parameter(e.what()) << std::endl;
        return false;
    }

    return true;
}

} // namespace nodecint
} // namespace bitprim
