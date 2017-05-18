#pragma once

namespace server
{

struct IServerConfig
{
	virtual ~IServerConfig() = default;
	
	virtual size_t ListPort() const = 0;
	virtual void ListPort( const size_t l_port ) = 0;
};

class ServerConfig : public IServerConfig
{
public:
	virtual size_t ListPort() const override { return list_port; }
	virtual void ListPort( const size_t l_port) override { list_port = l_port; }

private:
	size_t list_port;
};

}