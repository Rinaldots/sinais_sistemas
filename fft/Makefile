CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = fft
SOURCE = fft.cpp

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
