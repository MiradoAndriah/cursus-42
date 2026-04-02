*This project  has been created as part of program 42 curriculum by herinaan.*

## DESCRIPTION

ft_printf is a reimplementation of the standard C printf function.

The goal of this project is to reproduce the behavior of the original printf from the C standard library, handling formatted output and variadic arguments, while respecting the constraints and allowed functions of the 42 curriculum.


#### THIS PROJECT FOCUSES ON:

- Variadic functions handling (stdarg.h)

- Parsing and interpreting format strings

- Converting and printing different data types

- Memory management and modular code architecture

- Reproducing specific formatting behaviors



#### THE FUNCTION PROTOTYPE IS:
``` bash 
int ft_printf(const char *format, ...);
```
The function returns the total number of characters printed.

#### MANDATORY CONVERSIONS:

`%c` — Character

`%s` — String

`%p` — Pointer (hexadecimal with 0x prefix)

`%d` / `%i` — Signed integer

`%u` — Unsigned integer

`%x` — Hexadecimal (lowercase)

`%X` — Hexadecimal (uppercase)

`%%` — Percent sign

## INSTRUCTION
#### COMPILATION
#### To compile the project:
``` bash 
make 
```
#### This will generate:  
``` bash 
libftprintf.a
```
#### Clean object files  
``` bash 
make clean 
```
#### Full clean (*.o and the libftprintf.a)   
``` bash 
make fclean 
```
#### Recompile everything  
``` bash 
make re 
```
#### To run one file
- create main.c
``` bash
touch main.c
```
- exemple of main.c
``` bash
#include "ft_printf.h"

int	main(void)
{
	ft_printf("Hello %s!\n", "world");
    ft_printf("Number: %d\n", 42);
    ft_printf("Hex: %x\n", 255);
    return (0);
}

```
COMPILE WITH :
``` bash
cc -Wall -Wextra -Werror main.c -L. -lftprintf
```
- -L. -> Adds the current directory (.) to the list of directories where the linker searches for
- -lftprintf -> Tells the linker to search for a library named libftprintf.a

## RESOURCES
#### Documentation
- man 3 printf
- man 3 stdarg
- 42 Subject PDF

#### Articles & References
- Variadic functions in C
- Stack memory and calling conventions
- Number base conversion algorithms

#### AI Usage Disclosure
AI tools were used during this project for:
- Clarifying how variadic functions (va_list) work
- Understanding edge cases of the original printf

AI was not used to generate the final implementation code.
All architecture, debugging, and validation were performed manually to ensure full understanding.

## Technical Design & Algorithm Explanation
#### Overall Architecture

The project is built around a modular and structured architecture to ensure clarity, maintainability, and separation of responsibilities.

The main function ft_printf performs three core tasks:

- Parsing the format string

- Dispatching conversions

- Counting printed characters
The format string is parsed character by character.
When a regular character is encountered, it is written directly to the output using write().

When a % character is detected, the next character determines the conversion type.
#### This approach was chosen because:
- It reproduces the behavior of the original printf

- It avoids unnecessary memory allocation

- It keeps control over every printed character

- It simplifies debugging and validation

#### Variadic Arguments Handling

The project uses the standard <stdarg.h> library to handle variadic arguments.

The following macros are used:

- `va_start` — initializes the argument list

- `va_arg` — retrieves the next argument

- `va_end` — cleans up the argument list

Each time a conversion specifier is detected, the corresponding type is retrieved using `va_arg`.

Example logic:

- `%d` / `%i` → `va_arg(args, int)`

- `%u` → `va_arg(args, unsigned int)`

- `%s` → `va_arg(args, char *)`

- `%p` → `va_arg(args, void *)`

This mechanism ensures strict correspondence between format specifiers and argument types.

#### Conversion Dispatch System

A dispatcher function is used to separate concerns.

Instead of writing all conversion logic inside ft_printf, each conversion type is handled by a dedicated function:

- Character printing

- String printing

- Integer printing

- Unsigned integer printing

- Hexadecimal conversion

- Pointer conversion

This modular approach was chosen because:

- It improves readability

- It respects clean code principles

- It allows isolated testing of each conversion

- It reduces function complexity

### Number Conversion Algorithm
#### Integer Handling (%d / %i)

Signed integers are handled carefully:

- If the number is negative, a - sign is printed first.

- The value is converted to a positive equivalent.

- Edge case: INT_MIN is handled separately to avoid overflow.

#### Unsigned Integers (%u)

Unsigned integers are printed without sign management.

#### Hexadecimal Conversion (%x / %X)

Hexadecimal numbers are converted using base 16.

Two approaches are possible:

- Recursive conversion

- Iterative conversion

The chosen implementation uses (recursive/iterative — adapt if needed) conversion because:

- It simplifies base decomposition

- It mirrors mathematical base conversion logic

Lowercase and uppercase outputs are handled by selecting the correct base string:

- "0123456789abcdef"

- "0123456789ABCDEF"

#### Pointer Conversion (%p)

Pointers are:

- Cast to unsigned long

- Printed in hexadecimal

- Prefixed with 0x

This matches the behavior of the original printf.

#### Memory Management Strategy

No dynamic memory allocation (malloc) is used for conversions.

Instead:

- Characters are written directly using write()

- Numbers are converted and printed immediately

This design choice:

- Avoids memory leaks

- Respects 42 constraints

- Reduces memory overhead

- Improves performance

All functions return the number of printed characters, allowing ft_printf to compute and return the total count accurately.

#### Character Counting Strategy

Each printing function returns the number of characters it outputs.

ft_printf accumulates this count throughout execution.

This ensures:

- Correct return value

- Accurate reproduction of original printf behavior

- Proper handling of edge cases

#### Data Structures Used

This project does not require complex data structures.

It primarily relies on:

- va_list for variadic arguments

- Basic integer types

- Character arrays for base conversion

No advanced data structures were necessary because:

- The problem is linear

- The format string is parsed sequentially

- No state persistence is required

#### Design Justification

- The chosen implementation prioritizes:

- Simplicity

- Modularity

- Full control over output

- Zero unnecessary memory allocation

- Clear separation of responsibilities

This architecture ensures the function is:

- Easy to maintain

- Easy to debug

- Faithful to the original printf

- Fully compliant with 42 constraints

## AUTHOR
*This project was created by 42 student.*