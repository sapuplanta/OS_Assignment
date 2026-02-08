Glass Bridge Game
==================

1. Project Overview
-------------------
This project is a multiplayer game insipired by the "Glass Bridge"
challenge from Squid Game. It is developed to demostrate core 
Opertaing System concepts such as:

- Process creation using fork()
- Inter-Process Communication (IPC)
- Shared memory using nmap()
- Turn-based synchronization
- Logging and persistent storage

The game runs locally on a single machine using POSIX system calls.


2. Games Rules Summary
----------------------
- Number of players: 3
- All players share ONE glass bridge path.
- The bridge has a fixed number of steps.
- At each step, only one tile is safe:
    -Left (L)
    -Right (R)
- Players take turns choosing L or R.
- Choosing the wrong tile eliminates theb player.
- Eliminated players skip future turns.
- The first player to reach the end of the bridge wins.
- The game continues to another round upon client confirmation.


3. Modes Supported
------------------
- Local multiplayer mode which turn-based.
- Text-based interaction via terminal.
- IPC-based execution using shared memory.
- No networking or online mode supported.


4. System Architecture
----------------------
- The server process initializes the game and shared memory.
- Each player is represented by a child using fork().
- All processes share the same game state using nmap().
- A turn variable ensures only one player moves at a time.
- A logger module records gameplay events and stores winners.


5. File Structure
-----------------
server.c : Core server and game logic (IPC, fork, turns)
logger.c : Logging and persistence implementation
logger.h : Logger interface
Makefile : Build instructions


6. How to Compile
-----------------
Ensure all source files are in the same directory.

Run the following command:
    make 

This will compile the program and generate the executable:
    server 


7. How to Run
-------------
After sucessful compilation, run:

    ./server


8. Output Files
---------------
After execution, the following files may be generated:

- game.log
  Records all gameplay events such as player moves,
  eliminations, and game start/end.

- scores.txt 
  Stores the winner of each completed game session.


9. Task Distribution
--------------------
Member 1 (Abid):
- fork() players processes
- shared memory setup
- process-shared mutexes
- signal handling

Member 2 (Jevaan):
- game design and rules
- game state Structure
- round-robin scheduler thread
- turn synchronization
- elimination & win logic

Member 3 (Faris):
- IPC
- logger thread
- input handling
- scores.txt persistence


10. Conclusion
--------------
This project demonstrates practical usage of 
Operating Systems concepts such as IPC, process management,
synchronization, and persistent logging through a simple interactive game.