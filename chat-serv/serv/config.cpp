#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>

#include "config.h"

namespace server
{

ServerConfig::ServerConfig()
{
	read_config();
}

void ServerConfig::read_config()
{
	namespace fs = boost::filesystem;

	fs::path conf_path(fs::current_path().string() + R"(\Config\conf.ini)");
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(conf_path.generic_string(), pt);

	list_port = pt.get<int>("Connection.listen_port");
}

}