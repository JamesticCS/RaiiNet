# Compiler and flags
CXX = g++-14.2.0
CXXFLAGS = -std=c++20 -fmodules-ts -Wall -g
CXXHFLAGS = -std=c++20 -fmodules-ts -c -x c++-system-header

# Target executable
TARGET = displayBoard

# Source files with implementations
INTERFACES = square.o observer.o subject.o board.o textobserver.o main.o
IMPLEMENTATIONS = square-impl.o observer-impl.o subject-impl.o board-impl.o textobserver-impl.o
OBJECTS = $(INTERFACES) $(IMPLEMENTATIONS)

# System headers
SYSTEM_HEADERS = iostream vector string

# Rules
all: $(TARGET)

# Compile system headers
headers:
	$(foreach header,$(SYSTEM_HEADERS),$(CXX) $(CXXHFLAGS) $(header);)

# Interface files in dependency order
square.o: square.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

observer.o: observer.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

subject.o: subject.cc observer.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

board.o: board.cc square.o subject.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

textobserver.o: textobserver.cc observer.o board.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: main.cc board.o textobserver.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Implementation files
square-impl.o: square-impl.cc square.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

observer-impl.o: observer-impl.cc observer.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

subject-impl.o: subject-impl.cc subject.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

board-impl.o: board-impl.cc board.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

textobserver-impl.o: textobserver-impl.cc textobserver.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link
$(TARGET): headers $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

.PHONY: clean headers

clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -rf gcm.cache/