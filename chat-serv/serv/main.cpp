#include "server_sm.h"
#include "config.h"

int main()
{
 	server::ServerListener listener;
 	listener.initiate();
 	listener.process_event(server::EvInitStart());
	return 0;
}