CC = gcc
CFLAGS = -fPIC
LDFLAGS = -shared
CLANG = clang
CLANG_FLAGS = -Wl,-rpath,. -L.
TARGET_LIB = libmtrack.so
TARGET_EXEC = main

SRC_DIR = src/
INCLUDE_DIR = include/
LIB_DIR = lib/

MAIN = utest_free
TRACKER = mtrack_05

all: $(TARGET_LIB) $(TARGET_EXEC)

$(TRACKER).o: $(SRC_DIR)$(TRACKER).c
	$(CC) -c $(SRC_DIR)$(TRACKER).c $(CFLAGS) -o $@

$(LIB_DIR)$(TARGET_LIB): $(TRACKER).o
	$(CC) $(LDFLAGS) $(TRACKER).o -o $@

$(MAIN).o: $(INCLUDE_DIR)$(TRACKER).h $(MAIN).c
	$(CC) -include $(INCLUDE_DIR)$(TRACKER).h -c $(MAIN).c -o $@

$(TARGET_EXEC): $(MAIN).o
	$(CLANG) $(CLANG_FLAGS) -lmtrack $(MAIN).o -o $@

clean:
	rm -f $(TRACKER).o $(MAIN).o $(LIB_DIR)$(TARGET_LIB) $(TARGET_EXEC)

.PHONY: all clean
