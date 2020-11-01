
NAME = DOOM
FLAGS = #-Wall -Werror -Wextra
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CFLAGS = -I SDL2/SDL.h -lSDL2 -lSDL2_ttf
endif
ifeq ($(UNAME_S),Darwin)
	CFLAGS = -I SDL/SDL.h -L lib -l SDL2-2.0.0
endif

SRCDIR	= ./src
INCDIR	= ./includes
OBJDIR	= ./obj

SRC		= main.c \
		  draw.c \
		  errors.c \
		  events.c \
		  init.c \
		  texture.c \
		  reader.c \
		  write.c \
		  map_events.c\
		  draw_utils.c\
		  draw_utils2.c\
		  neighbors.c\

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
CC		= gcc -g

# MLX		= ./minilibx/
# MLX_LNK	= -L $(MLX) -l mlx -lXext -lX11

# MLX_INC	= -I $(MLX)
# MLX_LIB	= $(addprefix $(MLX),mlx.a)

FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft -l pthread

all: obj $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(FLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	@make -C $(FT)

# $(MLX_LIB):
# 	@make -C $(MLX)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(FT_LNK) -lm $(CFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

re: fclean all