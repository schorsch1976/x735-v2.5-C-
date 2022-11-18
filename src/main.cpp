#include <gpiod.hpp>

#include <boost/asio.hpp>
#include <fstream>
#include <iostream>

class Worker
{
public:
	explicit Worker(boost::asio::io_context& io);
	~Worker();

private:
	void ScheduleMeasure();
	void ExecuteMeasure();

	void SchedulePWM();
	void ExecutePWM();

	boost::asio::io_context& m_io;
	boost::asio::steady_timer m_timer_measure;
	boost::asio::steady_timer m_timer_pwm;

	gpiod::line m_fan_on;
	int m_pwm_duty_ratio = 0;
	int m_pwm_state = 0;
};

Worker::Worker(boost::asio::io_context& io)
	: m_io(io), m_timer_measure(m_io, boost::asio::chrono::seconds(5)),
	  m_timer_pwm(m_io, boost::asio::chrono::milliseconds(10))
{
	// get the gpio lines
	gpiod::chip chip("gpiochip0");
	m_fan_on = chip.get_line(13);
	m_fan_on.request({"FanControl", gpiod::line_request::DIRECTION_OUTPUT});

	ScheduleMeasure();
	SchedulePWM();
}
Worker::~Worker() { m_fan_on.set_value(0); }

void Worker::ScheduleMeasure()
{
	m_timer_measure.async_wait([this](const boost::system::error_code& ec) {
		this->ExecuteMeasure();
	});
}

void Worker::ExecuteMeasure()
{
	std::ifstream ifs("/sys/class/thermal/thermal_zone0/temp");
	if (ifs.is_open())
	{
		double temp = 0.0;
		ifs >> temp;
		temp /= 1000.0;

		if (temp > 30.0)
		{
			m_pwm_duty_ratio = 40;
		}
		if (temp > 50.0)
		{
			m_pwm_duty_ratio = 50;
		}
		if (temp > 55.0)
		{
			m_pwm_duty_ratio = 75;
		}
		if (temp > 60.0)
		{
			m_pwm_duty_ratio = 90;
		}
		if (temp > 65.0)
		{
			m_pwm_duty_ratio = 100;
		}
		if (temp <= 30.0)
		{
			m_pwm_duty_ratio = 0;
		}
	}

	ScheduleMeasure();
}

void Worker::SchedulePWM()
{
	m_timer_measure.async_wait(
		[this](const boost::system::error_code& ec) { this->ExecutePWM(); });
}
void Worker::ExecutePWM()
{
	if (++m_pwm_state >= 100)
	{
		m_pwm_state = 0;
	}

	if (m_pwm_state <= m_pwm_duty_ratio)
	{
		m_fan_on.set_value(1);
	}
	else
	{
		m_fan_on.set_value(0);
	}

	SchedulePWM();
}

int main(int argc, char** argv)
{
	try
	{
		boost::asio::io_context io;

		Worker worker(io);

		io.run();

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
