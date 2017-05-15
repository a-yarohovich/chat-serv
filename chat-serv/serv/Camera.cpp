#include "Camera.h"
#include "Configuring.h"
#include "Shooting.h"

sc::result NotShooting::react(const EvShutterHalf &)
{
	return transit< Shooting >();
}

sc::result Idle::react(const EvConfig &)
{
	return transit< Configuring >();
}