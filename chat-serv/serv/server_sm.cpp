#include <iostream>
#include "server_sm.h"

#define LOG_FUNC std::cout << __FUNCTION__ << std::endl

namespace server
{

Stopped_State::Stopped_State()
{
	LOG_FUNC;
}
Stopped_State::~Stopped_State()
{
	LOG_FUNC;
}
statechart::result Stopped_State::react(const EvInitStart&)
{
	LOG_FUNC;
	return transit< Init_State >();
}

//////////////////////////////////////////////////////////////////////////

Init_State::Init_State()
{
	LOG_FUNC;
}

Init_State::~Init_State()
{
	LOG_FUNC;
}

statechart::result Init_State::react(const EvInitDone&)
{
	LOG_FUNC;
	return transit< Running_State >();
}

statechart::result Init_State::react(const EvStop &)
{
	LOG_FUNC;
	return transit< Stopped_State >();
}

//////////////////////////////////////////////////////////////////////////

Running_State::Running_State()
{
	LOG_FUNC;
}

Running_State::~Running_State()
{
	LOG_FUNC;
}

statechart::result Running_State::react(const EvInitStart &)
{
	LOG_FUNC;
	return transit< Init_State >();
}

statechart::result Running_State::react(const EvStop&)
{
	LOG_FUNC;
	return transit< Stopped_State >();
}

statechart::result Running_State::react(const EvMessage&)
{
	LOG_FUNC;
	return discard_event();
}

}

