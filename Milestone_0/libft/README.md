*This project was created as part of program 42 curriculum by herinaan.*

## DESCRIPTION

Libft is the first project in the study program at School 42 (UNIT Factory).
The purpose of this project is to introduce students to standard C functions that will be used in future projects.
To gain a deeper understanding of these functions, we had to create our own implementations of standard C library functions.



## INSTRUCTIONS

#### installation
``` bash 
git clone git@vogsphere.42antananarivo.mg:vogsphere/intra-uuid-0abe359f-7c6b-4067-9560-d09adfc92633-7248611-herinaan lbft 
```
   
#### generate all the object file
``` bash 
make 
```
#### delete all the object file   
``` bash 
make clean 
```
#### delete all the object file and the libft.a   
``` bash 
make fclean 
```
#### delete the object file and the libft and rebuild it   
``` bash 
make re 
```
#### To run one file
``` bash
cc -Wall -Wextra -Werror main.c -L. -lft
```
- create main.c
``` bash
touch main.c
```
- exemple of main.c
``` bash
#include "libft.h"

int	main(void)
{
	//your code
}

```

- -L. -> Adds the current directory (.) to the list of directories where the linker searches for
- -lft -> Tells the linker to search for a library named libft.a

## RESOURCES

For this project, I consulted several resources:
- YouTube to watch tutorials and better understand various concepts through practical examples.
link : https://www.youtube.com/watch?v=DGwdAQauEV4
- Grok is used to provide additional explanations and clarifications on specific topics, including the behavior and usage of the split and lstmap functions.
link : https://grok.com/
- W3Schools to follow tutorials and review fundamental concepts of the C programming language.
link : https://www.w3schools.com/c/index.php
- Additionally, I carried out personal research using Google to deepen my understanding and resolve specific issues encountered during the project.


## libft
### Short description of each function

|name			|description									|
|:--------------|:----------------------------------------------|
|`ft_atoi`		|transform string to integer
|`ft_bzero`		|set /0 all of the memory
|`ft_calloc`		|set zero all of the memory allocated by malloc(3)
|`ft_isalnum`	|test if the number in input is alpha and numeric
|`ft_isalpha`		|test if the caractere is alphabetic
|`ft_isascii`		|test id the caractere is an ascii
|`ft_isdigit`		|test if the caractere in input is numeric
|`ft_isprint`		|test if the caractere	in input is printable
|`ft_itoa`		|transform integer to string
|`ft_lstadd_back`	|add the new element to the end of the list
|`ft_lstadd_front`|add the new element to the beginin of the list
|`ft_lstclear`	|delete all element in the list
|`ft_lstdelone`	|delete element in the list
|`ft_lstiter`		|Iterates through the list ’lst’ and applies the function ’f’ to the content of each node.
|`ft_lstlast`		|return the last node in the list
|`ft_lstmap`		|Iterates through the list ’lst’, applies the function ’f’ to each node’s content, and creates a new list resulting of the successive applications of the function ’f’.
|`ft_lstnew`		|Allocates memory (using malloc(3)) and returns a new node. The ’content’ member variable is initialized with the given parameter ’content’. The variable ’next’ is initialized to NULL.
|`ft_lstsize`		|return the number of the element in the list
|`ft_memchr`		|return a pointer to the matching element with c
|`ft_memcpy`		|copies n bytes from memory src to dest
|`ft_memmove`		|copies memory n bytes src to dest but take care about overlap
|`ft_memset`		|set c all the n bytes value in the memories
|`ft_putchar_fd`	|write character in file open with fd
|`ft_putendl_fd`	|write c in the file with \n at the end
|`ft_putnbr_fd`	|write number in the file open with fd
|`ft_putstr_fd`	|write a string in the file open with fd
|`ft_split`		|returns an array of strings obtained by splitting ’s’ using the character ’c’ as a delimiter
|`ft_strchr`		|search the charactere c in the string and return  a pointer to  the first occurence find
|`ft_strdup`		|return a substring result of copying of the s
|`ft_striteri`	|Applies the function ’f’ to each character of the string passed as argument, passing its index as the first argument. Each character is passed by address to ’f’ so it can be modified if necessary
|`ft_strjoin`		|Allocates memory (using malloc(3)) and returns a new string, which is the result of concatenating ’s1’ and ’s2
|`ft_strlcat`		|concatenate src to n to dest and make sure that the result of the string are terminated by \0 and return the length of src plus the lenght of dest
|`ft_strlcpy`		|copy the src to n to the dest and make sur that the string created are terminated to \0
|`ft_strlen`		|return the lenght of the string
|`ft_strmapi`		|apply all of the element of string into the parametre of f and store the result into a new string
|`ft_strncmp`		|compare the s1 and the s2 and return the difference between if the s1 and s2 is different else return 0
|`ft_strrchr`		|unction returns a pointer to the  last  occurrence  of the character c in the string s
|`ft_strtrim`		|Allocates memory (using malloc(3)) and returns a copy of ’s1’ with characters from ’set’ removed from the beginning and the end
|`ft_substr`		|Allocates memory (using malloc(3)) and returns a substring from the string ’s’. The substring starts at index ’start’ and has a maximum length of ’le
|`ft_tolower`		|transform to lowercase the charactere
|`ft_toupper	`	|transform in uppercase the caractere
|`ft_strnstr`		|The strnstr() function locates the first occurrence of the null terminated string little in the string big, where not more than len characters are searched.

## AUTHOR
*This project was created by 42 student.*
