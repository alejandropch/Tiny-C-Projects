CC = gcc
CFLAGS = -Wall -Wextra

BUILD = build
SRC_DIRS = src database
INSTALL_PATH = /usr/bin
DATABASE_PATH = /usr/local/share/greetings

#including subfolders
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
CFLAGS += $(foreach d, $(INC_DIRS), -I$(d))


SRC = $(shell find $(SRC_DIRS) -name "*.c")

OBJ = $(patsubst %.c, $(BUILD)/%.o, $(SRC))

TARGET = greetings


$(BUILD)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(BUILD) $(TARGET)

$(BUILD):
	mkdir -p $(BUILD)/src $(BUILD)/database

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lsqlite3 -o $(TARGET)

.PHONY: clear
clear: 
	rm -r $(TARGET)
	rm -rf $(BUILD)

.PHONY: install
install: 
	$(CC) -o $(INSTALL_PATH)/$(TARGET) $(SRC) -lsqlite3
	mkdir -p $(DATABASE_PATH)
	
.PHONY: uninstall
uninstall:  
	rm -rf $(DATABASE_PATH)
	rm -f $(INSTALL_PATH)/$(TARGET)
