# CodeOptimization

This repository documents improvments of a code snippet allegedly written by another programmer and how to make code optimizations.
This project was the last assignment in Computer Structure course I took as part of Computer Science degree in Bar-Ilan university.

The scenario is as follows:
We are given a code snippet of another programmer and our goal is to optimize his runtime as much as possible using all the tools and principles we learned in the course. The goal is to get to a run time of the program fast As much as possible. This is a competition betwee students in which the students receive grades in relation to the performance achieved by their peers. The shorter the runtime of the code, the higher the student score (And of course the code should perform the same task performed by the original code).

Note: The only file we were allowed to modify is _c.myfunction_ only.

## Main Files

**myfunction_ORIGINAL.c** - This is the code file we received which was programmed by another programmer. This code gets an image and applies a filter to it successfully, but in an unlikely time.

* the suffix "\_ORIGINAL" added later to its name to differentiate  between the original and the improved one.

**myfunction.c** - This is the improved version of the code, which applies the same filter but does it more than 82% faster.


## Optimizations Methods

1. Loop unroll.
2. Complex calculations avoidance.
3. Code motion.
4. Use macro-functions.
5. Reduce functions calls.
6. Use pointers.


## IDE and Tools

- Visual Studio Code
- Notepad++
- Bash (for test-scriptss)
