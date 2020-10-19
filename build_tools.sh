#!/bin/bash
cd -P -- "$(dirname -- "${BASH_SOURCE[0]}")"

git clone git@github.com:scylladb/scylla-tools-java.git
cd scylla-tools-java
ant jar
cd ..

git clone git@github.com:scylladb/scylla-jmx.git
cd scylla-jmx
mvn --file scylla-jmx-parent/pom.xml package


echo 'cqlsh usage:'
echo './bin/cqlsh [Scylla host (e.g. 172.19.0.2)] [Scylla port (e.g. 9042)]'
echo ''
echo 'Proxy usage:'
echo './scripts/scylla-jmx -jp [port to listen on (e.g. 9043)] -p [Scylla REST API port (e.g. 10000)] -a [Scylla host (e.g. 172.19.0.2)]'
echo ''
echo 'nodetool usage:'
echo './bin/nodetool -h [ip jmx proxy listens on (e.g. 127.0.0.1)] -p [port jmx proxy listens on (e.g. 9043)] [command (e.g. status)]'
