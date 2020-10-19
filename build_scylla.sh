#!/bin/bash

# We want to be in scripts dir
cd -P -- "$(dirname -- "${BASH_SOURCE[0]}")"

git clone https://github.com/scylladb/scylla.git
cd scylla
# Clone dependencies
git submodule update --init --recursive
./tools/toolchain/dbuild ./configure.py
# -j 2 because otherwise build requires more RAM than we have
./tools/toolchain/dbuild ninja -j 2 build/release/scylla
# We don't want to run Scylla in docker host network mode, but rather in bridge mode, to run whole cluster locally
sed -i '168s/.*/       #--network host \\/' ./tools/toolchain/dbuild

# Create folders for instances data
mkdir -p ../cluster/node1
mkdir -p ../cluster/node2
mkdir -p ../cluster/node3
mkdir -p ../cluster/node4
chmod 777 -R ../cluster

# Create docker network that clusters will use
docker network create --driver bridge --subnet 172.19.0.0/16 scylla-cluster
