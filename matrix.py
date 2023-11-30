import threading
import numpy as np

MATRIX_SIZE = 3

result_matrix = np.zeros((MATRIX_SIZE, MATRIX_SIZE))

lock = threading.Lock()
matrix_a = np.random.randint(1, 10, (MATRIX_SIZE, MATRIX_SIZE))
matrix_b = np.random.randint(1, 10, (MATRIX_SIZE, MATRIX_SIZE))

def multiply_rows(row_index):
    global result_matrix
    for col_index in range(MATRIX_SIZE):
        result = 0
        for i in range(MATRIX_SIZE):
            result += matrix_a[row_index][i] * matrix_b[i][col_index]

        with lock:
            result_matrix[row_index][col_index] = result

def multiply_matrices():
    threads = []
    for i in range(MATRIX_SIZE):
        thread = threading.Thread(target=multiply_rows, args=(i,))
        threads.append(thread)
    for thread in threads:
        thread.start()

    for thread in threads:
        thread.join()

if __name__ == "__main__":
    print("Matrix A:")
    print(matrix_a)
    print("\nMatrix B:")
    print(matrix_b)

    multiply_matrices()

    print("\nResult Matrix:")
    print(result_matrix)
