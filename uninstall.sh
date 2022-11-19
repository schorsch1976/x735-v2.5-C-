#!/usr/bin/env bash

# bash best practices
# https://kvz.io/bash-best-practices.html

# exit when command fails
set -o errexit
set -o pipefail
set -o nounset

# trace (for debugging)
set -o xtrace

sudo systemctl stop x735-fancontrol.service			|| true
sudo systemctl disable x735-fancontrol.service		|| true
sudo rm /etc/systemd/system/x735-fancontrol.service	|| true
sudo rm /usr/local/bin/x735-fancontrol				|| true
sudo rm /usr/local/bin/x735-fanspeed				|| true
