CC = gcc
CFLAGS = -Wall -Wextra -std=c11
BUILD_DIR = build

SRC = strgPtr.c cse_caesar.c
OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))

LOCAL_SRC = test.c
LOCAL_BIN = $(BUILD_DIR)/local_test

TEST_SRC = tests/test_strg.c tests/test_caesar.c
TEST_OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(TEST_SRC))
TEST_BIN = $(BUILD_DIR)/tests_runner

CRITERION_CFLAGS = $(shell pkg-config --cflags criterion 2>/dev/null)
CRITERION_LIBS = $(shell pkg-config --libs criterion 2>/dev/null)
HAVE_CRITERION = $(if $(CRITERION_LIBS),1,0)

.PHONY: all test local clean

all: $(LOCAL_BIN) $(if $(filter 1,$(HAVE_CRITERION)),$(TEST_BIN))

local: $(LOCAL_BIN)

ifeq ($(HAVE_CRITERION),1)
test: $(TEST_BIN)
	./$(TEST_BIN)
else
test:
	@echo "Criterion is not installed in this environment. Run ./build/local_test instead, or install Criterion to build the Criterion suite."
	@exit 1
endif

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CRITERION_CFLAGS) -c $< -o $@

$(LOCAL_BIN): $(OBJ) $(LOCAL_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LOCAL_SRC) $(SRC) -o $@

$(TEST_BIN): $(OBJ) $(TEST_OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CRITERION_CFLAGS) $(OBJ) $(TEST_OBJ) $(CRITERION_LIBS) -o $@

clean:
	rm -rf $(BUILD_DIR)