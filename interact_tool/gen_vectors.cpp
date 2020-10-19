// Connecting to ScyllaDB with a simple C++ program
#include <cassandra.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <random>

double get_rand() {
    return ((double)rand()/(double)RAND_MAX);
}

void generate_vector(CassSession* session, size_t vector_id, size_t vector_length, const char *table) {
    srand(time(NULL));
    
    std::stringstream query;
    
    query << "BEGIN BATCH " << std::endl;
    for (size_t i = 0; i < vector_length; i++) {
      double random_number = get_rand();
      query << "INSERT INTO " << table << " " << " (id, coord, value) VALUES (" 
            << vector_id << ", " << i << ", " << get_rand() << ");" << std::endl;
    }
    query << "APPLY BATCH";
    
    std::cout << query.str() << std::endl;
    
    CassStatement* statement = cass_statement_new(query.str().c_str(), 0);
    cass_statement_set_consistency(statement, CASS_CONSISTENCY_QUORUM);

    CassFuture* result_future = cass_session_execute(session, statement);
    if (cass_future_error_code(result_future) == CASS_OK) {
      const CassResult* result = cass_future_get_result(result_future);
      
      std::cout << "OK" << std::endl;
      cass_result_free(result);
    } else {
      std::cout << "ERROR!" << std::endl;
      exit(1);
    }
    cass_future_free(result_future);
    cass_statement_free(statement);
}

int main(int argc, char* argv[]) {
  if (argc < 5) {
    std::cerr << "Usage: " << argv[0] 
                    << " " << "table_name"
                    << " " << "init_vect_num"
                    << " " << "vec_cnt" 
                    << " " << "vec_len" 
                    << " " << "[address]"
                    << " " << "[port]"<< std::endl;
    exit(1);
  }
  
  int initial = std::stoi(argv[2]);
  int cnt = std::stoi(argv[3]);
  int vec_length = std::stoi(argv[4]);
  
  // Allocate the objects that represent cluster and session. 
  CassCluster* cluster = cass_cluster_new();
  CassSession* session = cass_session_new();

  if (argc >= 6) {
    cass_cluster_set_contact_points(cluster, argv[5]);
    if (argc >= 7) {
      cass_cluster_set_port(cluster, std::stoi(argv[6]));
    }
  }
  cass_cluster_set_protocol_version(cluster, CASS_PROTOCOL_VERSION_V4);
  
  CassFuture* connect_future = cass_session_connect(session, cluster);
  if (cass_future_error_code(connect_future) == CASS_OK) {
    std::cout << "Connected" << std::endl;
    for (int i = initial; i < initial + cnt; i++) {
      generate_vector(session, i, vec_length, argv[1]);
    }
  } else {
    std::cout << "Connection ERROR" << std::endl;
  }
 
  // Release the resources.
  cass_future_free(connect_future);
  cass_cluster_free(cluster);
  cass_session_free(session);
}
