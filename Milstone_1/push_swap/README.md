*This project has been created as part of the 42 curriculum by `herinaan` and `brportos`*
# push_swap
# Overview
The push_swap is a classic algorithmic project from the 42 curriculum that focuses on sorting data efficiently under strict constraints. 
The goal is not only to sort numbers, but to do so using a minimal number of operations and a very limited instruction set.
The challenge lies in optimizing both time and space complexity while working with two stacks and predefined moves. 
It encourages a deep understanding of sorting algorithms, problem-solving strategies, and performance trade-offs.
## Description
The `push_swap` project consists of writing a C program named `push_swap` that sorts a list of integers received as arguments.
The program must output, on the standard output, the smallest possible sequence of instructions that will sort the numbers in ascending order in stack a.

To achieve this, we must:

* Work with two stacks: `a` and `b`
* Use only a restricted set of operations
* Minimize the total number of operations performed

While sorting numbers is straightforward, doing so efficiently with these constraints makes the problem significantly more complex.
For example:

Sorting a random list differs greatly from sorting an already nearly sorted list
Different input sizes require different algorithmic strategies
### Available Operations
* sa (swap a): Swap the first two elements at the top of stack a.Do nothing if there is only one or no elements.
* sb (swap b): Swap the first two elements at the top of stack b. Do nothing if there is only one or no elements.
* ss : sa and sb at the same time.
* pa (push a): Take the first element at the top of b and put it at the top of a. Do nothing if b is empty.
* pb (push b): Take the first element at the top of a and put it at the top of b. Do nothing if a is empty.
* ra (rotate a): Shift up all elements of stack a by one. The first element becomes the last one.
* rb (rotate b): Shift up all elements of stack b by one. The first element becomes the last one.
* rr : ra and rb at the same time. 
* rra (reverse rotate a): Shift down all elements of stack a by one. The last element becomes the first one.
* rrb (reverse rotate b): Shift down all elements of stack b by one. The last element becomes the first one.
* rrr : rra and rrb at the same time.

### Goal

The ultimate goal of this project is to sort numbers in ascending order in stack A while using the fewest operations possible.

This project provides a practical introduction to:

* Algorithm design and optimization
* Complexity analysis (time and space)
* Choosing the right strategy depending on input characteristics
## Instructions 
### Compilation
To build (compile) this project, you need two tools installed on your system:

* make – a tool that automates the build process using instructions defined in a Makefile.
* clang – a C compiler that converts the source code into an executable program.
Steps to compile:
1. Open a terminal.
2. Navigate to the project directory (where the Makefile is located).
3. Run the following command:
```bash
Makefile
```
### Execution
After compiling the project, run push_swap with a list of integers. The program will output the operations needed to sort them.
1. Basic usage with a list of numbers:
```bash
./push_swap 5 4 3 2 1
```
2. You can use Simple flag test mode:
```bash
./push_swap --simple 5 4 3 2 1
```
3. You can use medium flag test mode:
```bash
./push_swap --medium 5 4 3 2 1
```
4. You can use --complex flag test mode:
```bash
./push_swap --complex 5 4 3 2 1
```
5. You can use --adaptive flag text mode
Automatically chooses the best algorithm depending on input size and disorder.
```bash
./push_swap --adaptive 5 4 3 2 1
```
6. You can addd --bench with one of those flags above
You can measure performance using --bench together with any mode:
```bash
./push_swap --simple --bench 5 4 3 2 1
```
7. Complex test with checker
To run it install checker_linux and run this:
```bash
ARG="4 67 3 87 23"; chmod +x checker_linux; ./push_swap --complex $ARG | ./checker_linux $ARG
```
## Resources
* Google
* Website

- https://share.google/eB16TUOvmwfQnqKhQ

* Peer-to-peer discussions

* Youtube

- http://www.youtube.com/@CodeVault

- https://youtu.be/OaG81sDEpVk?si=tqgv5WsdBM5n8LDV

* AI 
AI tools were used for explanations of concepts and function specifications.
### Algorithms
#### Selection sort

Always take the smallest number from stack a, move it to stack b. Repeat until a is empty, then push everything back to a.

Step-by-step:
* Find the smallest number in stack a
* Rotate stack a until the smallest number is on top
* Push it to stack b
* Repeat until stack a is empty
* Push everything back to a

Justifacation:
```bash
while stack a not empty
    find smallest in a
    rotate a until smallest on top
    pb (push to b)

while stack b not empty
    pa (push back to a)
```
#### Chunk sort

General Idea
The Chunk Sort algorithm divides the numbers in stack a into multiple groups (chunks), then pushes them progressively to stack b, and finally pushes them back to stack a in sorted order.
Instead of always searching for the smallest value, we process ranges of values.

- Chunk Size Selection:
The chunk size is based on the square root of the stack size:
```bash
chunk_size = sqrt(size_of_stack_a);
```
- Justification :

    -Too small → too many iterations ❌

    -Too large → inefficient sorting ❌

    -√n → good balance between operations and performance ✅

This heuristic is commonly used in push_swap to reduce the total number of operations.

- Step-by-Step Execution :
```bash
exemple:

stack a: 8 3 7 1 5 2 6 4
size = 8
chunk_size = sqrt(8) = 2
```

```bash
chunk :

chunk 1: 0 - 1
chunk 2: 2 - 3
chunk 3: 4 - 5
...
```
#### Radix sort

We sort numbers bit by bit starting from the right most bit.

we check each bit:
1. if bit equal 0 push to stack b 
2. if bit equal 1 rotate stack a

We repeat for every bit until sorted.

Justification:
```bash
max_bits = number of bits of biggest number

for bit = 0 to max_bits
    for each number in a
        if bit == 0
            pb
        else
            ra

    while b not empty
        pa
```