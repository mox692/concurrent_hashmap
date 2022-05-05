TEST_TARGET = hashmap_test
TEST_OBJS = hashmap_test.o
CXX    = g++

PREFIX?=/usr/local
INSTALL_DIR=$(PREFIX)/include/hashmap

install:
	mkdir -p $(INSTALL_DIR)
	cp -pR hashmap.hpp $(INSTALL_DIR)
	cd cctest && make install

test: $(TEST_TARGET)

$(TEST_TARGET): $(OBJS) $(TEST_OBJS)
	$(CXX) -o $@ $^
	./$(TEST_TARGET)

%.o: %.cc
	$(CXX) -c -o $@ $^

update_submodule:
	git submodule update --remote

clean:
	rm -f $(TEST_TARGET) $(TEST_OBJS) $(OBJS) *.o
	rm -f $(INSTALL_DIR)/hashmap.hpp