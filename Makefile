MINILIBC_DIR := minilibc
INCLUDE_DIR := include
LIB := $(MINILIBC_DIR)/libminilibc.a

.PHONY: all clean fclean re test demo debug coverage

all:
	$(MAKE) -C $(MINILIBC_DIR) all

clean:
	$(MAKE) -C $(MINILIBC_DIR) clean

fclean:
	$(MAKE) -C $(MINILIBC_DIR) fclean
	$(RM) -f tests/test_main
	$(RM) -f main
	$(RM) -f tests/test_runner_debug
	$(RM) -f tests/*.gcda tests/*.gcno
	$(RM) -f $(MINILIBC_DIR)/*.gcda $(MINILIBC_DIR)/*.gcno

re:
	$(MAKE) -C $(MINILIBC_DIR) re

test: all
	$(CC) -Wall -Wextra -Werror -I$(INCLUDE_DIR) tests/test_main.c $(LIB) -o tests/test_main
	./tests/test_main

demo: all
	$(CC) -Wall -Wextra -Werror -I$(INCLUDE_DIR) main.c $(LIB) -o main

debug:
	$(MAKE) -C $(MINILIBC_DIR) re CFLAGS="-g3 -fsanitize=address -Wall -Wextra -Werror"
	$(CC) -g3 -fsanitize=address -I$(INCLUDE_DIR) tests/test_main.c $(LIB) -o tests/test_runner_debug
	./tests/test_runner_debug

coverage:
	$(MAKE) -C $(MINILIBC_DIR) re CFLAGS="--coverage -Wall -Wextra -Werror"
	$(CC) --coverage -I$(INCLUDE_DIR) tests/test_main.c $(LIB) -o tests/test_main
	./tests/test_main
