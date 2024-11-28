# Compiler and flags 
CXX = g++-14.2.0
CXXFLAGS = -std=c++20 -Wall -g

# Source files in dependency order
OBJECTS = player.o observer.o subject.o link.o data.o virus.o square.o board.o textobserver.o gamecontroller.o main.o

TARGET = raiiNet

# Compile everything
all: $(TARGET)

# Define dependencies
player.o: player.cc player.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

observer.o: observer.cc observer.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

subject.o: subject.cc subject.h observer.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

link.o: link.cc link.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

data.o: data.cc data.h link.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

virus.o: virus.cc virus.h link.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

square.o: square.cc square.h link.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

board.o: board.cc board.h square.h subject.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

textobserver.o: textobserver.cc textobserver.h observer.h board.h square.h player.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

gamecontroller.o: gamecontroller.cc gamecontroller.h board.h player.h textobserver.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: main.cc gamecontroller.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link everything
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -rf gcm.cache/