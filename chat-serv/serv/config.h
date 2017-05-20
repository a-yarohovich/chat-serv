#pragma once

namespace server
{

struct IServerConfig
{
	virtual ~IServerConfig() = default;
	virtual size_t listen_port() const = 0;
};

class ServerConfig : public IServerConfig
{
public:
	ServerConfig();
	virtual size_t listen_port() const override { return list_port; }

private:
	void read_config();
private:
	size_t list_port;
};

}