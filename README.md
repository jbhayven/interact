# interact

Przygotowaliśmy klaster składający się z 4 instancji, oraz programy do zapisywanie / odczytywanie wektorów z bazy. Instancej uruchamiane są w kontenerach, każda ze swoim ip. Ip z zakresu 172.19.0.0/16. Zalecane ustawienie:
- node1 172.19.0.2
- node2 172.19.0.3
- node3 172.19.0.4
- node4 172.19.0.5

Wszystkie skrypty zakładają taką konfigurację ip.

## Instrukcja użycia:

### Budowanie scylli:
`./build_scylla.sh`

### Budowanie narzędzi (cqlsh, nodetool, jmx proxy (potrzebne do nodetool)):
`./build_tools.sh`

### Uruchamianie Scylli
By uruchomić instancje używamy komend (w 4 osobnych terminalach):
- `./run_scylla.sh node1 172.19.0.2 172.19.0.2`
- `./run_scylla.sh node2 172.19.0.3 172.19.0.2`
- `./run_scylla.sh node3 172.19.0.4 172.19.0.2`
- `./run_scylla.sh node4 172.19.0.5 172.19.0.2`

### Przygotowywanie tabeli
`./prepare_tables.sh`

### Używanie narzędzi
- cqlsh: `./bin/cqlsh [Scylla host (e.g. 172.19.0.2)] [Scylla port (e.g. 9042)]`
- jmx proxy: `./scripts/scylla-jmx -jp [port to listen on (e.g. 9043)] -p [Scylla REST API port (e.g. 10000)] -a [Scylla host (e.g. 172.19.0.2)]`
- nodetool (wymaga uruchomionego jmx-proxy): `./bin/nodetool -h [ip jmx proxy listens on (e.g. 127.0.0.1)] -p [port jmx proxy listens on (e.g. 9043)] [command (e.g. status)]`
