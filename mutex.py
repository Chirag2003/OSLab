import threading
import time

# Initialize variables
read_count = 0
m = threading.Semaphore(1)  # Mutex
w = threading.Semaphore(1)  # Semaphore for writers
MAX_ITERATIONS = 2  # Define the maximum number of iterations for each thread

def writer(writer_id):
    for i in range(MAX_ITERATIONS):
        w.acquire()
        # Check if readers are currently reading
        if read_count > 0:
            print(f"Writer {writer_id} is being denied service because readers are reading...")
        else:
            # Perform the write operation
            print(f"Writer {writer_id} is writing...")
            time.sleep(1)  # Simulate some work
        w.release()

def reader(reader_id):
    global read_count
    for i in range(MAX_ITERATIONS):
        # Check if a writer is currently writing
        w.acquire()
        if read_count == 0:
            print(f"Reader {reader_id} is being denied service because a writer is writing...")
        w.release()
        m.acquire()
        read_count += 1
        if read_count == 1:
            w.acquire()  # Block writers if the first reader is entering
        m.release()
        # Perform the reading operation
        print(f"Reader {reader_id} is reading...")
        time.sleep(1)  # Simulate some work.
        m.acquire()
        read_count -= 1
        if read_count == 0:
            w.release()  # Allow a writer to access the resource if no readers are left
        m.release()

# Create multiple reader and writer threads
num_readers = 5
num_writers = 2
reader_threads = [threading.Thread(target=reader, args=(i,)) for i in range(num_readers)]
writer_threads = [threading.Thread(target=writer, args=(i,)) for i in range(num_writers)]

# Start the threads
for thread in reader_threads + writer_threads:
    thread.start()

# Join the threads (optional)
for thread in reader_threads + writer_threads:
    thread.join()
