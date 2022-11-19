# FanControl x735-v2.5-C++

C++ implementation of the x735 fan control software for the raspberry pi to
control and read the installed fan speed.

## First things first: How can I get it?

> git clone https://github.com/schorsch1976/x735-v2.5-C-.git.

This is my public (but not main repository). It is used to publish released versions and
for bug/issue tracking.

## Why rewritten?

My goal was to use a "vanilla" debian bullyeye on the raspberry pi4 but still have the
fan not running on maximum speed. The python3 libraries used at the [original](https://wiki.geekworm.com/X735_V2.5_Software) and the forked version from [thorkseng](https://github.com/thorkseng/x735-v2.5) dont work on a vanilla debian system.

So: One of the most fundamental and widespread programming languages is C/C++ was used.

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
git clone https://github.com/schorsch1976/x735-v2.5-C-.git
cd x735-v2.5-C-
bash install.sh
~~~

Now the binaries are installed in ``/usr/local/bin``. Also the service file is installed
and the fan should already be running.

### OK, How to read the fan speed?

~~~
georg@rpi4-rt:~$ x735-fanspeed
RPM: 2007
~~~

### Does it use much CPU power? My Pi4 is already sweating heavily ...

![cpuusage](https://github.com/schorsch1976/x735-v2.5-C/blob/master/images/cpuusage.png?raw=true)


### OK, but how can i get rid of it again?

~~~
...
cd x735-v2.5-C++
bash uninstall.sh
~~~
