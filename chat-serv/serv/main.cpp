#include "server_sm.h"

int main()
{
	server::ServerListener listener;
	listener.initiate();
	listener.process_event(server::EvInitStart());

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