B-Tree Key-Value Storage EngineAn in-memory key-value database built on a B-Tree index (order $M = 16$), using a Write-Ahead Log (WAL) to ensure data durability across restarts.

Features 
* In-Memory B-Tree Index: Fast key-value lookups and mutations using a B-Tree structure with order $M = 16$.
* WAL Durability: Writes are appended to a disk-backed Write-Ahead Log (WAL) before updating the in-memory index.
* Crash Recovery: Replays the WAL during startup to reconstruct the B-Tree state.
* Interactive REPL: Simple command-line interface for reading and writing data.Architecture 

Overview                     
                      +-------------------+
                      |      CLI REPL     |
                      +-------------------+
                                |
                         Write Operation
                                |
            +-------------------+-------------------+
            |                                       |
            v                                       v
  +-------------------+                   +-------------------+
  |  Write-Ahead Log  |                   |  In-Memory B-Tree |
  |   (Disk Append)   | --- Startup ----> |     (M = 16)      |
  +-------------------+     Replay        +-------------------+



Prerequisites
C/C++ compiler toolchain (GCC or Clang)
make build system

Building
Clone the repository and build the project:
Bash "make"

Usage
Run the executable to open the CLI prompt:
Bash "./main"


Supported Commands
Command Syntax                Description
INSERT  INSERT <key> <value>  Appends to WAL and inserts/updates key in the B-Tree
SELECT  SELECT <key>          Looks up key in the in-memory B-Tree.
EXIT    EXIT                  Terminates the CLI session.


Example 

engine> INSERT foo bar
Inserted: foo -> bar

engine> SELECT foo
bar

engine> EXIT
Bye!