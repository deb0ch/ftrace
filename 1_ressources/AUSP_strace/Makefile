##
## Makefile for nibbler in /home/ubuntu/rendu/cpp_nibbler
##
## Made by chauvo_t
## Login   <chauvo_t@epitech.net>
##
## Started on  Tue Apr  1 10:16:12 2014 chauvo_t
## Last update Sat May 17 00:39:00 2014 chauvo_t
##

CXX			:= gcc

RM			:= rm -f

DEBUG			:= debug

SRCDIR			:= src

OBJDIR			:= build

HDRDIR			:= include

SRCS			:=	main.c			\
				handle_exit.c		\
				launch_child.c		\
				print_syscalls.c	\
				print_types.c		\
				print_types2.c		\
				syscalls.c		\
				trace.c			\
				types.c

OBJS			:= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
SRCS			:= $(addprefix $(SRCDIR)/, $(SRCS))

DEPS			:= $(OBJS:.o=.d)

CFLAGS			+= -Wextra -Wall -W
CFLAGS			+= $(addprefix -I./, $(HDRDIR))
CFLAGS			+= -O0 -MD
$(DEBUG): CFLAGS	+= -g3 -ggdb

LDFLAGS			+= 
$(DEBUG): LDFLAGS	+= -g3 -ggdb

TMPS			:=	$(OBJS)			\
				$(OBJS:.o=.d)		\
				$(SRCS:.c=.c~)	\
				Makefile~

NAME			:= strace


all:		$(NAME)

$(DEBUG):	fclean $(NAME)

-include $(DEPS)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c
		$(COMPILE.c) $(OUTPUT_OPTION) $<

$(NAME):	$(OBJS)
		$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJS):	| $(OBJDIR)

$(OBJDIR):
		mkdir -p $(OBJDIR)

clean:
	@$(RM) $(TMPS)
	@echo "Object files cleaned"

fclean:	clean
	@$(RM) $(NAME)
	@echo "Executable cleaned"

re:	fclean all

.PHONY:	all clean fclean re
