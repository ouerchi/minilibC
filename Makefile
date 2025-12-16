MINILIBC_DIR := minilibc
INCLUDE_DIR := include
LIB := $(MINILIBC_DIR)/libminilibc.a

.PHONY: all clean fclean re test demo

all:
	$(MAKE) -C $(MINILIBC_DIR) all

clean:
	$(MAKE) -C $(MINILIBC_DIR) clean

fclean:
	$(MAKE) -C $(MINILIBC_DIR) fclean
	$(RM) -f tests/test_main
	$(RM) -f main

re:
	$(MAKE) -C $(MINILIBC_DIR) re

test: all
	$(CC) -Wall -Wextra -Werror -I$(INCLUDE_DIR) tests/test_main.c $(LIB) -o tests/test_main
	./tests/test_main

demo: all
	$(CC) -Wall -Wextra -Werror -I$(INCLUDE_DIR) main.c $(LIB) -o main

