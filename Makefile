CXX = g++

CXXFLAGS = -std=c++17 -Iheaders
SRC_DIR = source
TEST_DIR = test
OBJ_DIR = obj

GTEST_INC_DIR = /usr/include
GTEST_LIB_DIR = /usr/lib
GTEST_LIBS = -lgtest -lgtest_main -pthread -ldl

MAIN_TARGET = my_program
TEST_TARGET = run_tests

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

TEST_SRC_FILES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/test_%.o,$(TEST_SRC_FILES))

MAIN_APP_OBJ = $(OBJ_DIR)/main.o

APP_OBJS_FOR_TEST = $(filter-out $(MAIN_APP_OBJ),$(OBJ_FILES))

.PHONY: all clean test run

all: dirs $(MAIN_TARGET) $(TEST_TARGET)

dirs:
	@mkdir -p $(OBJ_DIR)

$(MAIN_TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_TARGET): $(APP_OBJS_FOR_TEST) $(TEST_OBJ_FILES)
	$(CXX) $(APP_OBJS_FOR_TEST) $(TEST_OBJ_FILES) -o $@ $(GTEST_LIBS) -I$(GTEST_INC_DIR) -L$(GTEST_LIB_DIR)

$(OBJ_DIR)/test_%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(GTEST_INC_DIR) -c $< -o $@

run: $(MAIN_TARGET)
	./$(MAIN_TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
