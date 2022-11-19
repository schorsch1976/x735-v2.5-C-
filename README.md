# FanControl x735-v2.5-C++

C++ implementation of the x735 fan control software for the raspberry pi to
control and read the installed fan speed.

## First things first: How can I get it?

> git clone https://github.com/schorsch1976/x735-v2.5-C++.

This is my public (but not main repository). It is used to publish released versions and
for bug/issue tracking.

## Why rewritten?

My goal was to use a "vanilla" debian bullyeye on the raspberry pi4 but still have the
fan not running on maximum speed. The python3 libraries used at the [original](https://wiki.geekworm.com/X735_V2.5_Software) and the
forked version from [thorkseng](https://github.com/thorkseng/x735-v2.5) dont work on a
vanilla debian system.

So: One of the most fundamental and widespread programming languages is C/C++.

---

## Used libraries

``x735-v2.5-C++`` uses the following third-party libraries (in ``3rdparty/``):
- [libgpiod](https://libgpiod.readthedocs.io/en/latest/index.html) to read and control the GPIOs [upstream](https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git)


## Used tools

- cmake 3.13
- gcc >= 8.2 or clang >=6

---

### OK, but how can I compile ``x735-v2.5-C++`` first?

It's not hard to compile ``x735-v2.5-C++`` yourself though:

~~~
sudo apt install cmake g++ build-essential libgpiod-dev
git clone https://github.com/schorsch1976/x735-v2.5-C++
cd x735-v2.5-C++
./install.sh
~~~

Now the binaries are installed in ``/usr/local/bin``. Also the service file is installed.
To enable it:
~~~
sudo systemctl enable x735-fancontrol.service
~~~

To start it immediatly:
~~~
sudo systemctl start x735-fancontrol.service
~~~
