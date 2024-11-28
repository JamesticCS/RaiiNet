# Compiler and flags 
CXX = g++-14.2.0
CXXFLAGS = -std=c++20 -fmodules-ts -Wall -g
CXXHFLAGS = -std=c++20 -fmodules-ts -c -x c++-system-header

# System headers (these are just included by the compiler, no need to compile them)
SYSTEM_HEADERS = iostream vector string memory sstream algorithm

# Compile system headers first
system_headers: 
	$(CXX) $(CXXHFLAGS) -c $(SYSTEM_HEADERS)

# All source files in proper order
INTERFACES = player.o observer.o subject.o link.o data.o virus.o square.o board.o textobserver.o gamecontroller.o main.o
IMPLEMENTATIONS = player-impl.o observer-impl.o subject-impl.o link-impl.o data-impl.o virus-impl.o square-impl.o board-impl.o textobserver-impl.o gamecontroller-impl.o
OBJECTS = $(SYSTEM_HEADERS:.h=.o) $(INTERFACES) $(IMPLEMENTATIONS)

TARGET = raiiNet

# Compile everything
all: system_headers $(TARGET)


# Define interface dependencies
player.o: player.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

observer.o: observer.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

subject.o: subject.cc observer.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

link.o: link.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

data.o: data.cc link.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

virus.o: virus.cc link.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

square.o: square.cc link.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

board.o: board.cc square.o subject.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

textobserver.o: textobserver.cc observer.o board.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

gamecontroller.o: gamecontroller.cc board.o player.o textobserver.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: main.cc gamecontroller.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Implementation files
player-impl.o: player-impl.cc player.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

observer-impl.o: observer-impl.cc observer.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

subject-impl.o: subject-impl.cc subject.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

link-impl.o: link-impl.cc link.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

data-impl.o: data-impl.cc data.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

virus-impl.o: virus-impl.cc virus.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

square-impl.o: square-impl.cc square.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

board-impl.o: board-impl.cc board.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

textobserver-impl.o: textobserver-impl.cc textobserver.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

gamecontroller-impl.o: gamecontroller-impl.cc gamecontroller.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link everything
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -rf gcm.cache/
