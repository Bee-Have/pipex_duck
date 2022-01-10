NAME = pipex
NAME_BONUS = pipex_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror

DEBUG =
ifdef DEBUG
CFLAGS += -fsanitize=address -g -g3 -O0
endif

SRCS_DIR = $(shell find Srcs -type d)
OBJS_DIR = Objs
INC_DIR = ./Includes/
LIBFT_DIR = ./Libs/libft_duck
LIBGNL_DIR = ./Libs/Lib_get_file

LIBS = -L$(LIBFT_DIR) -lft -L$(LIBGNL_DIR) -lgetfile
INCLUDES = -I$(LIBFT_DIR)/Includes -I$(LIBGNL_DIR)/Includes -I$(INC_DIR)

vpath %.c $(foreach dir, $(SRCS_DIR), $(dir):)

SRCS = 

# SRCS = main_test.c

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

all: $(LIBFT_DIR)/libft.a $(LIBGNL_DIR)/libgetfile.a $(NAME)

bonus: $(LIBFT_DIR)/libft.a $(LIBGNL_DIR)/libgetfile.a $(NAME_BONUS)

both: $(LIBFT_DIR)/libft.a $(LIBGNL_DIR)/libgetfile.a $(NAME) $(NAME_BONUS)

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR) all

$(LIBGNL_DIR)/libgetfile.a:
	make -C $(LIBGNL_DIR) all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(NAME_BONUS): $(OBJS)
	$(CC) $(CFLAGS) -D BONUS=1 $^ -o $@ $(LIBS)

$(OBJS_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

re: fclean all

allre: cleanall all

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

cleanall: fclean
	make -C $(LIBFT_DIR) fclean
	make -C $(LIBGNL_DIR) fclean

.PHONY : fclean clean re all