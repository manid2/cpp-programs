# ============================================================================
# Default targets
# ============================================================================
all: tests check

# ============================================================================
# Variables & source file targets
# ============================================================================
CXX = /usr/bin/g++-13
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Werror

BUILD_DIR:=build

GIT_LS:=git ls-files --cached --others --exclude-standard

SRCS:=$(shell $(GIT_LS) -- '*.cpp')
BINS:=$(patsubst %.cpp,$(BUILD_DIR)/%,$(SRCS:.cpp=))

$(BINS): %: $(BUILD_DIR)/%.o
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$@ $(BUILD_DIR)/$*.o

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

BINS_CHECK:=$(addsuffix -check,$(BINS))
BINS_CLEAN:=$(addsuffix -clean,$(BINS))
SRCS_FORMAT:=$(addsuffix -format,$(BINS))
SRCS_LINT:=$(addsuffix -lint,$(BINS))

$(BINS_CHECK):
	@make -s $(@:-check=)
	@./$(BUILD_DIR)/$(@:-check=)

$(BINS_CLEAN):
	rm -f $(BUILD_DIR)/$(@:-clean=.o) $(BUILD_DIR)/$(@:-clean=)

$(SRCS_FORMAT):
	clang-format -i $(addsuffix .cpp,$(@:-format=))

$(SRCS_LINT):
	@echo "TODO lint $(addsuffix .cpp,$(@:-lint=))"

# ============================================================================
# Top level targets
# ============================================================================
tests: $(BINS)

check:
	@scripts/run_tests.py

clean:
	rm -rf $(BINS)

format: $(SRCS_FORMAT)

lint:

.PHONY: tests check clean format lint $(BINS_CHECK) $(BINS_CLEAN) \
	$(SRCS_FORMAT) $(SRCS_LINT)
