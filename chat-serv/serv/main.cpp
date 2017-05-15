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

struct Active;
struct StopWatch : sc::state_machine< StopWatch, Active >
{
	double ElapsedTime() const
	{
		return state_cast<const IElapsedTime&>().ElapsedTime();
	}
};

struct Stopped;

struct Active : sc::simple_state<Active, StopWatch, Stopped >
{
public:
	using reactions = sc::transition< EvReset, Active >;
public:
	Active() : elapsedTime_(0.0) {}
	double ElapsedTime() const { return elapsedTime_; }
	double& ElapsedTime() { return elapsedTime_; }
private:
	double elapsedTime_;
};

struct Running : IElapsedTime, sc::simple_state< Running, Active >
{
public:
	using reactions = sc::transition< EvStartStop, Stopped >;

public:
	Running() : startTime_(std::time(0)) {}
	virtual ~Running() override
	{
		context<Active>().ElapsedTime() = ElapsedTime();
	}

	virtual double ElapsedTime() const override
	{
		return context< Active >().ElapsedTime() +
			std::difftime(std::time(0), startTime_);
	}

private:
	std::time_t startTime_;
};

struct Stopped : IElapsedTime, sc::simple_state< Stopped, Active >
{
	using reactions = sc::transition< EvStartStop, Running >;

	virtual double ElapsedTime() const override
	{
		return context< Active >().ElapsedTime();
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