TEST_TARGET = hashmap_test
TEST_OBJS = hashmap_test.o
CXX    = g++

PREFIX?=/usr/local
INSTALL_DIR=$(PREFIX)/include/hashmap

test: $(TEST_TARGET)

$(TEST_TARGET): $(OBJS) $(TEST_OBJS)
	$(CXX) -pthread -o $@ $^
	./$(TEST_TARGET)

install:
	mkdir -p $(INSTALL_DIR)
	cp -pR hashmap.hpp $(INSTALL_DIR)
	cd cctest && make install

%.o: %.cc
	$(CXX) -c -o $@ $^

update_submodule:
	git submodule update --remote

c:
	rm -f $(TEST_TARGET) $(TEST_OBJS) $(OBJS) *.o
	rm -f $(INSTALL_DIR)/hashmap.hpp
