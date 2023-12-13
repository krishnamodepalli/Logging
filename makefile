# This is an AI generated makefile which is compaitable with the current project.
# Feel free to modify it to your liking and ignore any warnings or issues with it.

CXX := g++
SRCDIR := src
BUILDDIR := obj
BINDIR := bin
INCLUDEDIR := include
TARGET := app

# Source files
SRCEXT := cpp
SOURCES := $(wildcard $(SRCDIR)/*.$(SRCEXT))

# Object files
OBJECTS_TESTING := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/testing/%,$(SOURCES:.$(SRCEXT)=.o))
OBJECTS_RELEASE := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/release/%,$(SOURCES:.$(SRCEXT)=.o))

# Flags
CXXFLAGS := -std=c++11 -I$(INCLUDEDIR)

# Debug flags
TESTINGFLAGS := -g -DTESTING
CXXFLAGS_TESTING := $(CXXFLAGS) $(TESTINGFLAGS)

# Release flags
RELEASEFLAGS := -O3
CXXFLAGS_RELEASE := $(CXXFLAGS) $(RELEASEFLAGS)

# Final flags
LDFLAGS :=

# Targets
all: testing release

testing: $(BINDIR)/testing/$(TARGET)_testing $(BINDIR)/testing/

release: $(BINDIR)/release/$(TARGET)_release $(BINDIR)/release/

$(BINDIR)/testing/$(TARGET)_testing: $(OBJECTS_TESTING)
	@echo "Linking..."
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BINDIR)/release/$(TARGET)_release: $(OBJECTS_RELEASE)
	@echo "Linking..."
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILDDIR)/testing/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)/testing
	@echo "Compiling $< (Debug)"
	$(CXX) -c $(CXXFLAGS_TESTING) $< -o $@

$(BUILDDIR)/release/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)/release
	@echo "Compiling $< (Release)"
	$(CXX) -c $(CXXFLAGS_RELEASE) $< -o $@

$(BINDIR)/testing/:
	@mkdir -p $(BINDIR)/testing

$(BINDIR)/release/:
	@mkdir -p $(BINDIR)/release

.PHONY: clean

clean:
	@echo "Cleaning..."
	@$(RM) -r $(BUILDDIR) $(BINDIR)

.PHONY: run_testing

run_testing: $(BINDIR)/testing/$(TARGET)_testing
	@echo "Running in Debug mode..."
	./$<

.PHONY: run_release

run_release: $(BINDIR)/release/$(TARGET)_release
	@echo "Running in Release mode..."
	./$<
