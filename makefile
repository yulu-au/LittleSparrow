CC = gcc

SOURCES_DIR =./src
INCLUDES_DIR =
LIBS_DIR = 
OBJS_DIR = ./obj
BIN_DIR = ./bin


#CFLAGS = -I$(INCLUDES_DIR) -c -Wall -std=c99

CFLAGS = -c -Wall -std=gnu99

#LDFLAGS = -lpthread -L$(LIBS_DIR)

LDFLAGS = 

SOURCES=$(wildcard $(SOURCES_DIR)/*.c)
NOTDIR=$(notdir $(SOURCES))
SUBST=$(patsubst %.c,%.o,$(NOTDIR))
OBJS=$(addprefix $(OBJS_DIR)/,$(SUBST))

BIN=$(BIN_DIR)/main
all:$(BIN)

$(BIN):$(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJS_DIR)/%.o:$(SOURCES_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean run
clean:
	rm -f ./obj/*.o $(BIN)
run:
	$(BIN)
