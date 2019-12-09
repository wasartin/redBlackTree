TARGET = project2Ex
ECHO = echo

HISTORY = .userInputLogHIstory.txt

SRCS  = $(shell find ./src     -type f -name *.cpp)
HEADS = $(shell find ./include -type f -name *.h)
OBJS = $(SRCS:.cpp=.o)
DEPS = Makefile.depend

INCLUDES = -I./include
# -g is for gdb, -ggdb has more debugging symbols.
# CXXFLAGS = -ggdb -Wall -Werror $(INCLUDES)
CXXFLAGS = -g -std=c++98 -Wall $(INCLUDES)
CPP = g++
LDFLAGS = -lm


all: $(TARGET)

$(TARGET): $(OBJS) $(HEADS)
	$(CPP) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

run: all
	@./$(TARGET)

.PHONY: depend clean
depend:
	$(CXXFLAGS) $(INCLUDES) -MM $(SRCS) > $(DEPS)
	@sed -i -E "s/^(.+?).o: ([^ ]+?)\1/\2\1.o: \2\1/g" $(DEPS)

clean:
	$(RM) $(OBJS) $(TARGET)

clobber: clean
	@$(ECHO) Removing auxillary files
	$(RM) $(HISTORY)

-include $(DEPS)
