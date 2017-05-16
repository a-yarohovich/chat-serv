#pragma once
#include <boost/statechart/event.hpp>

namespace server
{

namespace statechart = boost::statechart;

struct EvInitStart : statechart::event< EvInitStart > {};
struct EvInitDone : statechart::event< EvInitDone > {};
struct EvStop : statechart::event< EvStop > {};
struct EvMessage : statechart::event< EvMessage > {};

}
