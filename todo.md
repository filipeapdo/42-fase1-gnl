# get_next_line
## Mandatory Part
- function name : get_next_line
  - [ ] char        *get_next_line(int fd)
- return value :
  - read line : correct behavior
  - NULL : nothing else to read or an error ocurred
- turn in files :
  - [ ] get_next_line.c
  - [ ] get_next_line_utils.c
  - [ ] get_next_line.h
- external functions :
  - read
  - malloc
  - free
- compilation:
  - gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c.

### notes
compile w/ ggdb (for debug)
`gcc -Wall -Wextra -Werror -ggdb3 get_next_line.h get_next_line_utils.c get_next_line.c test.c`


run programa with time check over valgrind saving the output on "a.log" and logs from valgrind into "valgrind.log"
`time valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --log-file="valgrind.log" ./a.out > a.log`

### tests
- [x] file: alternate new line in file (buffer_size ~line_size)
- **[ ] file: big line (buffer_size 1)**: TIMEOUT
- [x] stdin: alternate new line in file (buffer_size ~line_size)
- [ ] refatorar, nomes de funções e conseguir fazer a flp_get_line
talvez com join... talvez com strlcpy

### to-do
- [ ] check static variables
> basicly it saves the last value in its context
> .
> .
> .
- [ ] check read function
> ssize_t read(int fd, void *buf, size_t count);
> 
> to be tested:
> - if BUFFER_SIZE is the 'count from prototype'
> 
- [ ] check buffer definitions
> .
> .
> .
> 
- [ ] check file descriptor definitions
> .
> .
> .

* if BUFFER_SIZE = 4
* read 4 chars (bytes)
* save it on a buffer (static?)
* until '\n'

static char *buffer;
char        *line;
int         bytes_read = 0;
int         size = 0;
int         i = 0;

bytes_read = read(int fd, void *buf, size_t count);
1 . bytes_read = read(fd, buffer, BUFFER_SIZE);
bytes_read = 4
buffer = '1234'
size += bytes_read
size = 4

2 . bytes_read = read(fd, buffer, BUFFER_SIZE);
bytes_read = 4
buffer = '1234'+'5678'
size += bytes_read
size = 8

3 . bytes_read = read(fd, buffer, BUFFER_SIZE);
bytes_read = 3
buffer = '1234'+'5678'+'90\n'
size += bytes_read
size = 11

while (i < size)
{
  *(line + i) = *(buffer + i);
}

return (line);

como utilizar a variável estatica?
como "concatenar" o pequenos chunks até bater no '\n'?