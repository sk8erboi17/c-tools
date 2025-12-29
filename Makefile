all:
	rm run_tests
	gcc tests/test_vector.c vector/vector.c utils/memory.c -o run_tests
	./run_tests
