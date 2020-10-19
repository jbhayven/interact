#!/bin/bash
cd -P -- "$(dirname -- "${BASH_SOURCE[0]}")"

git clone git@github.com:scylladb/scylla-tools-java.git
cd scylla-tools-java
ant jar
cd ..

git clone git@github.com:scylladb/scylla-jmx.git
cd scylla-jmx
mvn --file scylla-jmx-parent/pom.xml package
