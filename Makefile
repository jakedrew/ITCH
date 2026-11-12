CXXFLAGS = -std=c++20 -O2 -Wall -Wextra

build/itch: src/main.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf build
