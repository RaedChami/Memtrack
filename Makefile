CC = gcc
CLANG = clang
CFLAGS = -fPIC
LDFLAGS = -shared
CLANG_FLAGS = -Wl,-rpath,. -L.

TARGET_LIB = libmtrack.so
TARGET_EXEC = main
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests/
TRACKER = mtrack_05
UNITARY_TEST = utest_free
MAIN = $(TEST_DIR)$(UNITARY_TEST)

all: $(TARGET_LIB) $(TARGET_EXEC)

$(TARGET_LIB): $(TRACKER).o
	$(CC) $(LDFLAGS) $(TRACKER).o -o $(TARGET_LIB)

$(TRACKER).o: $(SRC_DIR)/$(TRACKER).c
	$(CC) -c $(SRC_DIR)/$(TRACKER).c $(CFLAGS) -o $(TRACKER).o

$(TARGET_EXEC): $(MAIN).o
	$(CLANG) $(CLANG_FLAGS) -lmtrack $(MAIN).o -o $(TARGET_EXEC)

$(MAIN).o: $(MAIN).c
	$(CC) -include $(INCLUDE_DIR)/$(TRACKER).h -c $(MAIN).c -o $(MAIN).o

clean:
	rm -f *.o $(TEST_DIR)*.o *.so $(TARGET_EXEC) $(TARGET_LIB)

.PHONY: all clean
