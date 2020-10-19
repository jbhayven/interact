CXX=g++
CPPFLAGS=-Iinclude
LDFLAGS=-Llib -lcassandra -Wl,-Rlib
RM=rm -f

SRCS=query_vector.cpp gen_vectors.cpp
OBJS=$(subst .cpp,.o,$(SRCS)) $(subst .cpp,,$(SRCS))

all: query_vector gen_vectors

.PHONY: all

query_vector: query_vector.o
	$(CXX) -o query_vector query_vector.o $(LDFLAGS)

query_vector.o: query_vector.cpp
	$(CXX) -o query_vector.o -c $(CPPFLAGS) query_vector.cpp

gen_vectors: gen_vectors.o
	$(CXX) -o gen_vectors gen_vectors.o $(LDFLAGS)

gen_vectors.o: gen_vectors.cpp
	$(CXX) -o gen_vectors.o -c $(CPPFLAGS) gen_vectors.cpp

clean:
	$(RM) $(OBJS)


