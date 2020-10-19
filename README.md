# interact

## Instrukcja użycia:

### Budowanie scylli:
`./build_scylla.sh`

### Budowanie narzędzi (cqlsh, nodetool, jmx proxy (potrzebne do nodetool)):
`./build_tools.sh`

### Uruchamianie scylli

Przygotowany jest klaster składający się z 4 instancji. Odpalane są w dockerze, każda ze swoim ip. Ip z zakresu 172.19.0.0/16. Zalecane ustawienie:
- node1 172.19.0.2
- node1 172.19.0.3
- node1 172.19.0.4
- node1 172.19.0.5

Wszystkie skrypty zakładają taką konfigurację ip.

By uruchomić instancje używamy komend (w 4 osobnych terminalach):
- `./run_scylla.sh node1 172.19.0.2 172.19.0.2`
- `./run_scylla.sh node2 172.19.0.3 172.19.0.2`
- `./run_scylla.sh node3 172.19.0.4 172.19.0.2`
- `./run_scylla.sh node4 172.19.0.5 172.19.0.2`

### Przygotowywanie tabeli
`./prepare_tables.sh`
