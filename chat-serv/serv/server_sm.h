#pragma once

#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>
#include <boost/shared_ptr.hpp>

#include "events.h"

namespace server
{

namespace mpl = boost::mpl;

struct IServerConfig;
using IServerConfigPtr = boost::shared_ptr<IServerConfig>;

class Stopped_State;

class ServerListener : public statechart::state_machine < ServerListener, Stopped_State >
{
public:
	IServerConfigPtr& Config();
	void Config(const IServerConfigPtr& spConf);
private:
	IServerConfigPtr spServConfig;
};

class Stopped_State : public statechart::simple_state < Stopped_State, ServerListener >
{
public:
	using reactions = statechart::custom_reaction< EvInitStart >;
public:
	Stopped_State();
	~Stopped_State();
	statechart::result react(const EvInitStart&);
};

class Init_State : public statechart::state < Init_State, ServerListener >
{
public:
	using reactions = mpl::list <
		statechart::custom_reaction< EvInitDone >,
		statechart::custom_reaction< EvStop > >;
public:
	Init_State(my_context ctx);
	~Init_State();
	statechart::result react(const EvInitDone&);
	statechart::result react(const EvStop&);
};

class Running_State : public statechart::simple_state < Running_State, ServerListener >
{
public:
	using reactions = mpl::list <
		statechart::custom_reaction< EvInitStart >,
		statechart::custom_reaction< EvStop >,
		statechart::custom_reaction< EvMessage > >;
public:
	Running_State();
	~Running_State();
	statechart::result react(const EvInitStart&);
	statechart::result react(const EvStop&);
	statechart::result react(const EvMessage&);
};

}

