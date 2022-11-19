#include <gpiod.hpp>

#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>

class Worker
{
public:
	Worker();
	~Worker() = default;

	int64_t MeasureRPM();

private:
	gpiod::line m_fan_tacho;
};

Worker::Worker()
{
	// get the gpio lines
	gpiod::chip chip("gpiochip0");
	m_fan_tacho = chip.get_line(16);

	m_fan_tacho.request(
		{"FanTacho", gpiod::line_request::DIRECTION_INPUT |
						 gpiod::line_request::EVENT_FALLING_EDGE});
}

int64_t Worker::MeasureRPM()
{
	using namespace std::chrono;

	using Duration_t = duration<double>;
	using TimePoint_t = steady_clock::time_point;

	std::this_thread::sleep_for(milliseconds(10));

	size_t count = 0;
	const TimePoint_t start = steady_clock::now();
	TimePoint_t now = start;
	TimePoint_t first_tick;
	while (now - start < seconds(1))
	{
		if (m_fan_tacho.event_wait(milliseconds(100)) == true)
		{
			if (count == 0)
			{
				first_tick = steady_clock::now();
			}
			count++;
			m_fan_tacho.event_read();
		}

		now = steady_clock::now();
	}
	const TimePoint_t end = now;

	// no impulses => 0 RPM
	if (count <= 2)
	{
		return 0;
	}

	Duration_t total = end - first_tick;
	Duration_t avg = total / (count - 1); // fence problem ...
	double freq = 1.0 / avg.count();

	// double rpm = freq / PULSE(2) * 60;
	// so: RPM = freq *30;
	double rpm = freq * 30.0;

	return static_cast<int64_t>(rpm);
}

int main(int argc, char** argv)
{
	try
	{
		Worker w;
		int64_t rpm = w.MeasureRPM();
		std::cout << "RPM: " << rpm << std::endl;
		return EXIT_SUCCESS;
	}
	catch (const std::error_code& ec)
	{
		std::cerr << ec.message() << " - " << ec.value() << ":"
				  << ec.category().name() << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unknown exception" << std::endl;
	}
	return EXIT_FAILURE;
}
