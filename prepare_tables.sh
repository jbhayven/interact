#!/bin/bash
cd -P -- "$(dirname -- "${BASH_SOURCE[0]}")"

cd scylla-tools-java
./bin/cqlsh 172.19.0.2 9042 -f ../init_tables.cqlsh
