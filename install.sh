#!/usr/bin/env bash

# bash best practices
# https://kvz.io/bash-best-practices.html

# exit when command fails
set -o errexit
set -o pipefail
set -o nounset

# trace (for debugging)
set -o xtrace

rm -Rf build || true

mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j2
sudo make install
cd ..
rm -Rf build || true
sudo cp x735-fancontrol.service /etc/systemd/system/
sudo systemctl daemon-reload
sudo systemctl enable x735-fancontrol.service
sudo systemctl start x735-fancontrol.service
