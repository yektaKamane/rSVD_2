CXX = g++
CXXFLAGS = -Wall -std=c++11

SRCS = main.cpp QR.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = QR.hpp

TARGET = my_program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
