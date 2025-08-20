# Step 1: Single-Node Storage Engine

- Implement a Write-Ahead Log (WAL) for durability.
  - All writes are first appended to the WAL before being applied.
- Use a B-tree for indexing and efficient data access.
  - Store key-value pairs in the B-tree.
  - On startup, replay the WAL to restore state.

# Step 2: Multi-Node Extension with Raft

- Integrate the Raft consensus algorithm:
  - Implement leader election.
  - Handle log replication across nodes.
  - Manage cluster membership changes.
- The Raft state machine will ensure all nodes agree on the log and state.
- On each node, apply committed log entries to the B-tree.


## Usage

Build the project:
```bash
make
```

Run the CLI:
```bash
./main
```

Example session:
```
engine> INSERT foo bar
Inserted: foo -> bar
engine> SELECT foo
bar
engine> EXIT
Bye!
```