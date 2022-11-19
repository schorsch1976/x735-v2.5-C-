#include <gpiod.hpp>

#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

class Worker
{
public:
	Worker();
	~Worker();

	void Run();

private:
	gpiod::line m_fan_on;
};

Worker::Worker()
{
	// get the gpio lines
	gpiod::chip chip("gpiochip0");
	m_fan_on = chip.get_line(13);
	m_fan_on.request({"FanControl", gpiod::line_request::DIRECTION_OUTPUT});
}
Worker::~Worker() { m_fan_on.set_value(0); }

void Worker::Run()
{
	using namespace std::chrono;

	steady_clock::duration on_time = milliseconds(0);
	steady_clock::duration off_time = milliseconds(100);

	while (1)
	{
		std::ifstream ifs("/sys/class/thermal/thermal_zone0/temp");
		if (ifs.is_open())
		{
			int temp = 0.0;
			ifs >> temp;
			temp /= 1000;

			if (temp > 65)
			{
				on_time = milliseconds(100);
				off_time = milliseconds(0);
			}
			else if (temp > 60)
			{
				on_time = milliseconds(90);
				off_time = milliseconds(10);
			}
			else if (temp > 55)
			{
				on_time = milliseconds(75);
				off_time = milliseconds(25);
			}
			else if (temp > 50)
			{
				on_time = milliseconds(50);
				off_time = milliseconds(50);
			}
			else if (temp > 30)
			{
				on_time = milliseconds(40);
				off_time = milliseconds(60);
			}
			else
			{
				on_time = milliseconds(0);
				off_time = milliseconds(1000);
			}
		}

		m_fan_on.set_value(1);
		std::this_thread::sleep_for(on_time);

		m_fan_on.set_value(0);
		std::this_thread::sleep_for(off_time);
	}
}

int main(int argc, char** argv)
{
	try
	{
		Worker w;
		w.Run();

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
