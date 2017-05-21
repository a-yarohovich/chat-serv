#pragma once

namespace server
{

struct IServerConfig
{
	virtual ~IServerConfig() = default;
	virtual unsigned short listen_port() const = 0;
};

class ServerConfig : public IServerConfig
{
public:
	ServerConfig();
	virtual unsigned short listen_port() const override { return list_port; }

private:
	void read_config();
private:
	unsigned short list_port;
};

}