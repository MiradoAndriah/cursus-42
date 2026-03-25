*This project has been created as part of the 42 curriculum by `brportos`.*
# ft_printf
## Description
**ft_printf** is a custom implementation of the standard C library function printf. The purpose of this project is to recreate the original printf function in order to deepen my understanding of:

Variadic functions (stdarg.h)

Format string parsing

Numeric base conversions

Low-level output handling

Rather than relying on simple functions like `ft_putnbr` or `ft_putstr`, this project challenges me to build a fully functional formatted output system from scratch.

The following format specifiers are implemented:

%c → `ft_putchar`: Prints a single character

%s → `ft_putstr`: Prints a null-terminated string

%d / %i → `ft_putnbr`: Prints a signed decimal (base 10) number and Prints an integer in base 10 respectively

%u → `ft_putunnbr` : Prints an unsigned decimal (base 10) number

%x → `ft_putlowhex` : Prints a hexadecimal number (lowercase)

%X → `ft_putuphex`: Prints a hexadecimal number (uppercase)

%p → `ft_putaddress` : Prints a void * pointer in hexadecimal format lowercase

%% → `ft_putchar('%')`: Prints a literal percent sign

---
## Instructions
1. Compile the library using:
```sh
make
```
This will generate the `libftprintf.a` file.
Available Makefile rules:
```sh
make clean   : removes object files
make fclean  : removes object files and libftprintf.a
make re      : rebuilds the library
```
2. To use the library in your project, include the header:
```c
#include "ft_printf.h"
```
3. To Compile your program with `libftprintf`:

Create your `main.c` and put `libftprintf` header (.h) above.
```c
#include "ft_printf.h"

int	main()
{
	int d = ft_printf(NULL);
	ft_printf("%d\n", d);

}
```
And then compile your programm with the command below
```sh
cc -Wall -Wextra -Werror main.c -IL libftprintf.a
```
## Resources
man

Google

Peer-to-peer discussions

Youtube
https://www.youtube.com/watch?v=byRw36Y3Hjs

AI

AI Usage:
AI tools were used only for explanations of concepts and function specifications. No code was copied directly from AI-generated output.

## Detailed ft_printf description

`ft_printf` is a custom reimplementation of the standard C printf function. The project is to understand and reproduce formatted output handling using variadic arguments, manual format parsing, and low-level writing functions — without relying on the original printf. Unlike a full implementation of printf, this version focuses on a controlled subset of conversions while strictly respecting the constraints of the 42 curriculum.

This library is organized into nine main functional components:

### ft_printf

Entry point of the program

Parses the format string

Detects `%` specifiers

Initializes and manages `va_list`

Returns the total number of printed characters

### ft_conversion

Acts as a dispatcher

Identifies the correct conversion type

Calls the appropriate output function

Updates the printed length counter

### ft_putchar

Prints a single character

Handles `%c` and `%%`

### ft_putstr

Prints a null-terminated string

Handles `%s`

Safely manages NULL strings

### ft_putnbr

Prints signed integers `(%d, %i)`

Handles negative numbers safely

### ft_putunnbr

Prints unsigned integers `(%u)`

### ft_putlowhex

Prints hexadecimal in lowercase `(%x)`

### ft_putuphex

Prints hexadecimal in uppercase `(%X)`

### ft_putaddress

Prints void * pointers `(%p)`

Adds `"0x"` prefix

Converts the address to hexadecimal

Handles NULL pointers safely

## A detailed explanation and justification algorithm and data structure

1_Iterate through the format string character by character.

2_If the current character is not `%`, print it directly.

3_If `%` is encountered:

	- Move to the next character.

	- Identify the conversion specifier.

	- Call the appropriate handler function.

4_Accumulate and return total printed character count.

Required Data Structure
```c
va_list ap;
va_start(ap, format);
va_arg(ap, type);
va_end(ap);
```
