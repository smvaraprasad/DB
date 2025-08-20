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

# Learning Outcomes

- Understand durability via WAL.
- Learn efficient indexing with B-trees.
- Gain experience with distributed consensus and fault tolerance using Raft.




storage_engine/
├── README.md
├── Makefile
├── src/
│   ├── wal.c         # Write-Ahead Log implementation
│   ├── wal.h
│   ├── btree.c       # B-tree implementation
│   ├── btree.h
│   ├── engine.c      # Main engine logic (ties WAL and B-tree)
│   ├── engine.h
│   ├── raft.c        # Raft consensus (add later)
│   ├── raft.h
│   └── node.c        # Node abstraction (single/multi-node)
│   └── node.h
├── test/
│   ├── test_wal.ca
│   ├── test_btree.c
│   ├── test_engine.c
│   └── test_raft.c
└── data/             # WAL and B-tree persistent files (for local dev)




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