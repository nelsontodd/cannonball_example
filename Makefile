#
# == Paths ==
#
BIN_DIR   := bin
SRC_DIR   := src
BUILD_DIR := build

#
# == Files ==
#
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)
#TODO: Do this more intelligently
BUILD_OBJS = $(foreach obj,$(OBJS),$(BUILD_DIR)/$(notdir $(obj)))

#
# == CC Flags ==
#
CC      := c++
CXXFLAGS = --std=c++17

#
# == Targets ==
#

default: solve
objs: $(OBJS)


clean:
	$(RM) $(BUILD_DIR)/*.o $(BIN_DIR)/*

%.o: %.cpp
	$(CC) -o $(BUILD_DIR)/$(notdir $@) $(CXXFLAGS) -c $<

solve: $(OBJS) 
	$(CC) -o $(BIN_DIR)/solve $(BUILD_OBJS)
