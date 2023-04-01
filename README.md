# 42Philosophers
### Threads synchronization in C

<img src="https://user-images.githubusercontent.com/107865727/229291834-0e9ac08d-f765-4729-a192-b7cb719a07e5.png" width="400" height="400">

In this project, you will learn the basics of threading a process.
You will see how to create threads and you will discover mutexes.

In computer science, [the dining philosophers](https://en.wikipedia.org/wiki/Dining_philosophers_problem) problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

It was originally formulated in 1965 by Edsger Dijkstra as a student exam exercise, presented in terms of computers competing for access to tape drive peripherals. Soon after, Tony Hoare gave the problem its present form.

# Data Races


Data races are a common problem in multithreaded programming. Data races occur when multiple tasks or threads access a shared resource without sufficient protections, leading to undefined or unpredictable behavior.
A mutual exclusion (mutex) is used cooperatively between threads to ensure that only one of the cooperating threads is allowed to access the data or run certain application code at a time.
You can check date races via a Valgrind tool called [Helgrind](https://valgrind.org/docs/manual/hg-manual.html) with the command :
```
valgrind --tool=helgrind
```
