NAME := scopaxx
SRCDIR := ./src/
GCC := g++
CXXFLAGS := -std=c++11 -pthread

SRC := $(addprefix $(SRCDIR), Card.cpp Game.cpp Deck.cpp State.cpp main.cpp)
OBJECTS := $(addsuffix .o, $(basename $(SRC)))

all: $(NAME)

$(NAME): $(OBJECTS)
	$(GCC) $^ -o $@ $(CXXFLAGS) 

%.o: %.cpp
	$(GCC) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)