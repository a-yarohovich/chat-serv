#pragma once

#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>

namespace sc = boost::statechart;

struct EvShutterHalf : sc::event< EvShutterHalf > {};
struct EvShutterFull : sc::event< EvShutterFull > {};
struct EvShutterRelease : sc::event< EvShutterRelease > {};
struct EvConfig : sc::event< EvConfig > {};

struct NotShooting;
struct Camera : sc::state_machine< Camera, NotShooting >
{
	bool IsMemoryAvailable() const { return true; }
	bool IsBatteryLow() const { return false; }
};

struct Idle;
struct NotShooting : sc::simple_state<
	NotShooting, Camera, Idle >
{
	using reactions = sc::custom_reaction< EvShutterHalf >;
	sc::result react(const EvShutterHalf &);
};

struct Idle : sc::simple_state< Idle, NotShooting >
{
	using reactions = sc::custom_reaction< EvConfig >;
	sc::result react(const EvConfig &);
};
