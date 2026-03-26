*This project has been created as part of the 42 curriculum by brportos.*
# Libft
## Description
**Libft** is the first project in the 42 curriculum. The primary goal of this project is to create a custom static C library (`libft.a`) containing a collection of general-purpose functions. These functions are designed to be reused in future C projects throughout the curriculum.

The project involves **reimplementing standard C library functions** from headers such as `<string.h>`, `<stdlib.h>`, and `<ctype.h>`. By manually recreating these functions, I gained a deeper understanding of:
- Memory management
- Pointer arithmetic
- Data structures
- The internal behavior of the C standard library

---

### 1. **Libc Functions**
- `ft_isalpha` – Checks if a character is alphabetic  
- `ft_isdigit` – Checks if a character is a digit  
- `ft_isalnum` – Checks if a character is alphanumeric  
- `ft_isascii` – Checks if a character is an ASCII character  
- `ft_isprint` – Checks if a character is printable  
- `ft_strlen` – Calculates the length of a string  
- `ft_memset` – Fills a block of memory with a particular value  
- `ft_bzero` – Sets the first `n` bytes of a memory block to zero  
- `ft_memcpy` – Copies memory from one location to another  
- `ft_memmove` – Moves memory safely, even with overlapping regions  
- `ft_strlcpy` – Copies a string with guaranteed null-termination  
- `ft_strlcat` – Concatenates strings with size protection  
- `ft_toupper` – Converts a character to uppercase  
- `ft_tolower` – Converts a character to lowercase  
- `ft_strchr` – Finds the first occurrence of a character  
- `ft_strrchr` – Finds the last occurrence of a character  
- `ft_strncmp` – Compares two strings up to `n` characters  
- `ft_memchr` – Searches for a byte in memory  
- `ft_memcmp` – Compares two memory blocks  
- `ft_strnstr` – Locates a substring within a limited length  
- `ft_atoi` – Converts a string to an integer  
- `ft_calloc` – Allocates and zero-initializes memory  
- `ft_strdup` – Duplicates a string using dynamic memory  

---

### 2. **Additional Functions**
- `ft_substr` – Extracts a substring  
- `ft_strjoin` – Concatenates two strings  
- `ft_strtrim` – Trims leading and trailing whitespace  
- `ft_split` – Splits a string using a delimiter  
- `ft_itoa` – Converts an integer to a string  
- `ft_strmapi` – Applies a function to each character (new string)  
- `ft_striteri` – Applies a function to each character with index  
- `ft_putchar_fd` – Writes a character to a file descriptor  
- `ft_putstr_fd` – Writes a string to a file descriptor  
- `ft_putendl_fd` – Writes a string followed by a newline  
- `ft_putnbr_fd` – Writes an integer  

---

### 3. **Linked List Functions**
- `ft_lstnew` – Creates a new list element  
- `ft_lstadd_front` – Adds an element to the front  
- `ft_lstsize` – Returns the number of elements  
- `ft_lstlast` – Returns the last element  
- `ft_lstadd_back` – Adds an element to the back  
- `ft_lstdelone` – Deletes a single element  
- `ft_lstclear` – Clears and frees an entire list  
- `ft_lstiter` – Applies a function to each element  
- `ft_lstmap` – Creates a new list by mapping a function  

---
## Instructions
1. Compile the library using:
```
make
```
This will generate the libft.a file.
Available Makefile rules:
```
make clean   : removes object files
make fclean  : removes object files and libft.a
make re      : rebuilds the library
```
2. To use the library in your project, include the header:
```
#include "libft.h"
```
3. Compile your program with libft:
```
cc -Wall -Wextra -Werror main.c libft.a
```
## Resources
man

Google

Peer-to-peer discussions

AI

AI Usage:
AI tools were used only for explanations of concepts and function specifications. No code was copied directly from AI-generated output.
## Detailed library description
libft is a custom static C library (libft.a) that reimplements essential functions from the C standard library, along with additional utility functions.
The goal of this project is to build a solid foundation of reusable, well-tested functions that can be used in future C projects without relying on external libraries.
This library is organized into four main categories:
1. Character and Type Checking Functions
   These functions analyze or transform individual characters.

      `- Check character types`: alphabetic, digit, alphanumeric, ASCII, printable, Convert characters between uppercase and lowercase
2. String and Memory Manipulation Functions
   These functions handle low-level memory operations and string processing.

      `- Memory management`: Fill, zero, copy, move, search, and compare memory blocks

      `- String handling`: Measure string length, Copy and concatenate strings safely, and Search characters or substrings

      `- Compare strings`: Duplicate, join, trim, split, and extract substrings

3. Conversion and Allocation Functions
   These functions convert between data types and manage dynamic memory.
      - Convert strings to integers and integers to strings
      - Allocate memory dynamically and initialize it
      - Create new strings using allocated memory
4. Linked List Utility Functions
   These functions manage singly linked lists using a custom t_list structure.
      - Create new list nodes
      - Add elements to the front or back
      - Retrieve list size and last element
      - Delete elements and clear entire lists
      - Iterate over lists and apply functions
      - Map a list into a new list
