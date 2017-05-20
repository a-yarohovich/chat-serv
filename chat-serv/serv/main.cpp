#include <iostream>

#include "server_sm.h"
#include "config.h"

int main()
{
 	server::ServerListener listener;
 	listener.initiate();
 	listener.process_event(server::EvInitStart());
// 	std::cout << listener.Config()->ListPort() << std::endl;
// 	listener.process_event(server::EvStop());
// 	listener.process_event(server::EvStop());
// 	listener.process_event(server::EvInitStart());
// 	listener.process_event(server::EvInitDone());
// 	listener.process_event(server::EvMessage());
// 	listener.process_event(server::EvInitStart());
// 	listener.process_event(server::EvInitDone());
// 	listener.process_event(server::EvStop());
	return 0;
}