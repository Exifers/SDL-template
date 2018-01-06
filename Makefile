srcdir := src/
bin    := vg

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic \
$(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image

debug : CFLAGS += -g

src := $(shell find $(srcdir) -name "*.c")
obj := $(src:%.c=%.o)

all: $(obj)
	$(CC) $(obj) -o $(bin) $(LDFLAGS)

debug : $(obj)
	$(CC) $(LDFLAGS) $^ -o $(bin)

clean:
	$(RM) $(obj) $(bin)

.PHONY: all debug clean
