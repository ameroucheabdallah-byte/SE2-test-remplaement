# SE2-mini-project-AMROUCHE-Abdallah

OS2 mini project - L3 IS 2025/2026

## Exercise 1

16 threads created in parallel, each simulates a player waiting and playing on the PlayStation.
Used a struct to pass both the game name and player number to a single thread function.

- 8 Football threads
- 4 SuperMario threads  
- 4 NFS threads

Compile and run:
gcc exercise1/main.c -o ex1 -lpthread
./ex1

## Exercise 2

Same setup but with synchronization using semaphores.

Rules:
- Only one game type at a time on the console
- Football: max 4 simultaneous players
- SuperMario: max 2 simultaneous players
- NFS: max 1 player at a time
- Equal priority, no starvation

Each game has its own enter/release functions that handle blocking and waking up waiting players.

Compile and run:
gcc exercise2/main.c -o ex2 -lpthread
./ex2
