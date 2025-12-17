## minilibC (small C utility library)

This repository builds a small **C utility library** (a static archive) containing common string/memory helpers, simple output helpers, a linked-list module, and `get_next_line`.

It’s meant for:
- **Learning** how standard-ish library functions work
- **Reusing** a small, portable set of helpers across C projects

### What’s inside
The library is built in `minilibc/` and outputs:
- **`minilibc/libminilibc.a`**: the static library
- **`include/minilibc.h`**: the public header (API)

Included modules:
- **Character checks / case**: `ft_is*`, `ft_to*`
- **Strings**: `ft_strlen`, `ft_strdup`, `ft_strchr`, `ft_strrchr`, `ft_strncmp`, `ft_strnstr`, `ft_strlcpy`, `ft_strlcat`, `ft_strjoin`, `ft_substr`, `ft_strtrim`, `ft_split`
- **Memory**: `ft_mem*`, `ft_bzero`, `ft_calloc`
- **Numbers**: `ft_atoi`, `ft_itoa`
- **FD output**: `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`
- **Linked list**: `ft_lst*`
- **I/O**: `get_next_line`, `ft_printf`

### Build
From the repo root:

```bash
make
```

Clean:

```bash
make clean
make fclean
```

Debug & Coverage:

```bash
make debug      # bitcode with ASan
make coverage   # generate coverage report
```

### Use it in another project
Build the library, then link it:

```bash
cc main.c -Iinclude minilibc/libminilibc.a
```

In code:

```c
#include "minilibc.h"
```

### API notes (this project is allowed to be “different”)
- **`ft_split(const char *s, char *delims)`**: splits using *any character* from `delims` as a delimiter (multi-delimiter split).
- **`ft_strjoin(char *s1, char *s2)`**: returns a newly allocated string containing `s1 + s2`. It **does not** free inputs. Caller frees the result.
- **`get_next_line(int fd)`**:
  - Returns the next line (including the trailing `\n` if present).
  - Uses a per-file-descriptor stash (so you can interleave reads across FDs).
  - Caller must `free()` the returned line.
- **`ft_printf(const char *fmt, ...)`**:
  - Custom implementation of printf.
  - Supports: `%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X`, `%%`.

### Quick test run
If you have the `tests/` folder (provided by this repo), you can run:

```bash
make test
```
