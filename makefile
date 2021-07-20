all: make_mutex_test make_semaphore_test make_read_write_test

mutex_test: test_mutex.c mutex.h
	gcc -pthread test_mutex.c -o test_mutex

semaphore_test: test_semaphore.c counting_semaphore.h mutex.h
	gcc -pthread test_semaphore.c -o test_semaphore

read_write_test: test_read_write.c read_write_lock.h mutex.h
	gcc -pthread test_read_write.c -o test_read_write

clean:
	rm test_mutex test_semaphore test_read_write