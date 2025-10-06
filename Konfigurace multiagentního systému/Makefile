CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2
TARGET = main
SRCS = main.cpp
DATADIR = datapub
PUBIN = $(wildcard $(DATADIR)/*.in)

# Default rule: build the program
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Run all tests
test: $(TARGET)
	@for infile in $(PUBIN); do \
		outfile=$${infile%.in}.out; \
		tmpout=$${infile%.in}.myout; \
		echo "Running test with $$infile..."; \
		./$(TARGET) < $$infile > $$tmpout; \
		if diff -q $$outfile $$tmpout > /dev/null; then \
			echo "  [OK] $$infile"; \
		else \
			echo "  [FAIL] $$infile"; \
			diff -u $$outfile $$tmpout || true; \
		fi; \
	done

# Run a single test with e.g. make run PUB=pub01
run: $(TARGET)
	@if [ -z "$(PUB)" ]; then \
		echo "Usage: make run PUB=pub01"; \
	else \
		infile=$(DATADIR)/$(PUB).in; \
		outfile=$(DATADIR)/$(PUB).out; \
		tmpout=$(DATADIR)/$(PUB).myout; \
		echo "Running test $(PUB)..."; \
		./$(TARGET) < $$infile > $$tmpout; \
		if diff -q $$outfile $$tmpout > /dev/null; then \
			echo "  [OK] $(PUB)"; \
		else \
			echo "  [FAIL] $(PUB)"; \
			diff -u $$outfile $$tmpout || true; \
		fi; \
	fi

# Clean build and outputs
clean:
	rm -f $(TARGET) $(DATADIR)/*.myout