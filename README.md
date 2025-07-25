# CPP09 - STL Module

## Overview

This project consists of three exercises, each focusing on the use of C++ Standard Template Library (STL) containers and algorithms, as required by Module 09 of the 42 C++ curriculum.

- **ex00: Bitcoin Exchange**  
  Calculate the value of bitcoin on specific dates using a historical price database.
- **ex01: Reverse Polish Notation (RPN)**  
  Evaluate mathematical expressions written in Reverse Polish Notation.
- **ex02: PmergeMe**  
  Sort a sequence of positive integers using the Ford-Johnson (merge-insert) algorithm, comparing performance between two STL containers.

---

## General Rules

- Compile with: `c++ -Wall -Wextra -Werror -std=c++98`
- No use of C++11 or later features, Boost, or forbidden functions (`*printf()`, `*alloc()`, `free()`)
- No `using namespace` or `friend` keywords
- Each exercise must use at least one STL container (two for ex02)
- Each exercise has its own `Makefile` with standard rules (`all`, `clean`, `fclean`, `re`)
- Output must end with a newline and be printed to standard output

---

## Build Instructions

Each exercise is in its own directory (`ex00`, `ex01`, `ex02`).  
To build all programs, run `make` in each directory:

```sh
cd ex00 && make
cd ../ex01 && make
cd ../ex02 && make
```

---

## Exercise Details & Usage

### ex00: Bitcoin Exchange

**Description:**  
Given a CSV database of bitcoin prices (`database.csv`) and an input file with lines of the form `date | value`, this program outputs the value of the specified amount of bitcoin on the given date.

**Build:**
```sh
cd ex00
make
```

**Run:**
```sh
./btc <input_file>
```

**Example:**
```sh
./btc inputs/input.txt
```

**Input file format:**
```
date | value
2011-01-03 | 3
2011-01-03 | 2
2011-01-03 | 1.2
2012-01-11 | -1
2001-42-42
2012-01-11 | 2147483648
```

**Output example:**
```
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-03 => 1.2 = 0.36
Error: not a positive number.
Error: bad input => 2001-42-42
Error: too large a number.
```

**Notes:**
- If the date is not in the database, the closest lower date is used.
- Handles errors for invalid dates, negative or too large values, and malformed lines.

---

### ex01: Reverse Polish Notation (RPN)

**Description:**  
Evaluates a mathematical expression in Reverse Polish Notation (RPN) passed as a single command-line argument.

**Build:**
```sh
cd ex01
make
```

**Run:**
```sh
./rpn "<expression>"
```

**Example:**
```sh
./rpn "8 9 * 9 - 9 - 9 - 4 - 1 +"
# Output: 42

./rpn "1 2 * 2 / 2 * 2 4 - +"
# Output: 0

./rpn "(1 + 1)"
# Output: Error
```

**Notes:**
- Only supports integer numbers < 10 and operators `+ - * /`.
- Prints result to standard output, errors to standard error.

---

### ex02: PmergeMe

**Description:**  
Sorts a sequence of positive integers using the Ford-Johnson (merge-insert) algorithm, implemented for both `std::vector` and `std::deque`. Reports the time taken for each container.

**Build:**
```sh
cd ex02
make
```

**Run:**
```sh
./pmergeMe <int1> <int2> <int3> ...
```

**Example:**
```sh
./pmergeMe 3 5 9 7 4
# Output:
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::vector : 0.00031 us
Time to process a range of 5 elements with std::deque  : 0.00014 us

# For large input (e.g., 3000 numbers):
./pmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
```

**Notes:**
- Only positive integers are accepted.
- Handles at least 3000 integers.
- Prints error and exits on invalid input.

---

## File Structure

- `ex00/` - Bitcoin Exchange
- `ex01/` - Reverse Polish Notation
- `ex02/` - PmergeMe (Ford-Johnson sort)
- Each directory contains its own `Makefile`, source files, and (for ex00) test input files.

---

## Author

- rmakoni