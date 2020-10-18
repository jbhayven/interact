// Connecting to ScyllaDB with a simple C++ program
#include <cassandra.h>
#include <iostream>
#include <cstdlib>
#include <sstream>

void get_vector(CassSession* session, size_t vector_id, const char *table) {
    std::stringstream query;
    
    query << "SELECT * FROM " << table << " WHERE id=" << vector_id << " ORDER BY coord ALLOW FILTERING";
    
    CassStatement* statement = cass_statement_new(query.str().c_str(), 0); // the 2nd argument (zero) is be explained in section “Prepared Statements”
    cass_statement_set_consistency(statement, CASS_CONSISTENCY_QUORUM);

    CassFuture* result_future = cass_session_execute(session, statement);
    if (cass_future_error_code(result_future) == CASS_OK) {
      const CassResult* result = cass_future_get_result(result_future);
      std::cout << "OK" << std::endl;
      
      CassIterator* iterator = cass_iterator_from_result(result);
      while (cass_iterator_next(iterator)) {
        const CassRow* row = cass_iterator_get_row(iterator);
        
        int coord; 
        double coord_value;
        
        const CassValue* value = cass_row_get_column_by_name(row, "coord");
        cass_value_get_int32(value, &coord);
        
        value = cass_row_get_column_by_name(row, "value");
        cass_value_get_double(value, &coord_value);
        
        std::cout << coord << " " << coord_value << std::endl;
      }
      cass_iterator_free(iterator);
        
      cass_result_free(result);
    } else {
      std::cout << "ERROR!" << std::endl;
      exit(1);
    }
    cass_future_free(result_future);
    cass_statement_free(statement);
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] 
                    << " " << "table_name"
                    << " " << "vec_id"
                    << " " << "[address]"
                    << " " << "[port]"<< std::endl;
    exit(1);
  }
  
  int id = std::stoi(argv[2]);
  
  // Allocate the objects that represent cluster and session. 
  CassCluster* cluster = cass_cluster_new();
  CassSession* session = cass_session_new();

  if (argc >= 4) {
    cass_cluster_set_contact_points(cluster, argv[3]);
    if (argc >= 5) {
      cass_cluster_set_port(cluster, std::stoi(argv[4]));
    }
  }
  cass_cluster_set_protocol_version(cluster, CASS_PROTOCOL_VERSION_V4);
  
  CassFuture* connect_future = cass_session_connect(session, cluster);
  if (cass_future_error_code(connect_future) == CASS_OK) {
    std::cout << "Connected" << std::endl;
    get_vector(session, id, argv[1]);
  } else {
    std::cout << "Connection ERROR" << std::endl;
  }
 
  // Release the resources.
  cass_future_free(connect_future);
  cass_cluster_free(cluster);
  cass_session_free(session);
}

