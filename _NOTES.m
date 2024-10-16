TODO:

- TEST deadlocks! (valgrind)
- TEST even more! (e.g.: why does visualizer say: Invalid log format: "2029 3 has taken fork")
- TEST for leaks!


? OPTIONAL ?

- NOTES TO WRITE thread (to battle write() delay)
- MAX 200 philos so on STACK
- (maybe static mutex)
- Change monitor to only checking the last given time of death! (instead of int array)
- TEST deadlocks!


- protect (eg.: gettimeofday())
- TEST!

VALGRIND CHECK!: [valgrind --tool=helgrind ./philo]
