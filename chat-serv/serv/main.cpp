#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <ctime>
#include <iostream>

struct IElapsedTime
{
	virtual ~IElapsedTime() = default;
	virtual double ElapsedTime() const = 0;
};

namespace sc = boost::statechart;

struct EvStartStop : sc::event< EvStartStop >
{
};

struct EvReset : sc::event< EvReset >
{
};

struct StateContext;
struct StopWatch : sc::state_machine< StopWatch, StateContext >
{
	double ElapsedTime() const
	{
		return state_cast<const IElapsedTime&>().ElapsedTime();
	}
};

struct Stopped;

struct StateContext : sc::simple_state<StateContext, StopWatch, Stopped >
{
public:
	using reactions = sc::transition< EvReset, StateContext >;
public:
	StateContext() : elapsedTime_(0.0) {}
	double ElapsedTime() const { return elapsedTime_; }
	double& ElapsedTime() { return elapsedTime_; }
private:
	double elapsedTime_;
};

struct Running : IElapsedTime, sc::simple_state< Running, StateContext >
{
public:
	using reactions = sc::transition< EvStartStop, Stopped >;

public:
	Running() : startTime_(std::time(0)) {}
	virtual ~Running() override
	{
		context<StateContext>().ElapsedTime() = ElapsedTime();
	}

	virtual double ElapsedTime() const override
	{
		return context< StateContext >().ElapsedTime() +
			std::difftime(std::time(0), startTime_);
	}

private:
	std::time_t startTime_;
};

struct Stopped : IElapsedTime, sc::simple_state< Stopped, StateContext >
{
	using reactions = sc::transition< EvStartStop, Running >;

	virtual double ElapsedTime() const override
	{
		return context< StateContext >().ElapsedTime();
	}
};

int main()
{
	StopWatch myWatch;
	myWatch.initiate();
	std::cout << myWatch.ElapsedTime() << "\n";
	myWatch.process_event(EvStartStop());
	std::cout << myWatch.ElapsedTime() << "\n";
	myWatch.process_event(EvStartStop());
	std::cout << myWatch.ElapsedTime() << "\n";
	myWatch.process_event(EvStartStop());
	std::cout << myWatch.ElapsedTime() << "\n";
	myWatch.process_event(EvReset());
	std::cout << myWatch.ElapsedTime() << "\n";
	return 0;
}