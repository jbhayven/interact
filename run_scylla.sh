#!/bin/bash
cd -P -- "$(dirname -- "${BASH_SOURCE[0]}")"

if [ "$#" -ne 3 ]; then
    echo "Usage: ./run_scylla.sh [name] [ip] [seed-ip]"
    exit 1
fi

NAME=$1
IP=$2
SEEDIP=$3

cd scylla

./tools/toolchain/dbuild --network scylla-cluster --ip $IP --name $NAME -v "$PWD/../cluster/$NAME:/scylla-data" -v "$PWD/../scylla-config:/scylla-home" -- ./build/release/scylla --developer-mode=yes --smp 2 -W /scylla-data --options-file /scylla-home/scylla.yaml --seed-provider-parameters seeds=$SEEDIP --listen-address $IP --rpc-address $IP --api-address $IP
