#include <iostream>
#include <chrono>

#define ROWS 10000
#define COLS 10000

int horizontal(int** matrix) {
  int sum = 0;

  for (size_t i = 0; i < ROWS; ++i) {
    for (size_t j = 0; j < COLS; ++j) {
      sum += matrix[i][j];
    }
  }

  return sum;
}

int vertical(int** matrix) {
  int sum = 0;

  for (size_t j = 0; j < COLS; ++j) {
    for (size_t i = 0; i < ROWS; ++i) {
      sum += matrix[i][j];
    }
  }

  return sum;
}

int main(int argc, char const *argv[]) {

  // Creating matrix
  int** arr = (int**)malloc(ROWS * sizeof(int*));
  for (int i = 0; i < ROWS; i++) {
    arr[i] = (int*)malloc(COLS * sizeof(int));
  }

  // Filling with 1s
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      arr[i][j] = 1;
    }
  }

  auto start = std::chrono::high_resolution_clock::now();

  // valgrind --tool=cachegrind ./test

  /* HORIZONTAL ONLY (EXECUTION TIME W Cachegrind ON: 2468 ms)
   I   refs:      2,707,447,818
   I1  misses:            2,155
   LLi misses:            2,079
   I1  miss rate:          0.00%
   LLi miss rate:          0.00%
   
   D   refs:      1,502,723,891  (1,401,807,176 rd   + 100,916,715 wr)
   D1  misses:       12,554,707  (    6,283,620 rd   +   6,271,087 wr)
   LLd misses:       12,548,940  (    6,278,870 rd   +   6,270,070 wr)
   D1  miss rate:           0.8% (          0.4%     +         6.2%  )
   LLd miss rate:           0.8% (          0.4%     +         6.2%  )
   
   LL refs:          12,556,862  (    6,285,775 rd   +   6,271,087 wr)
   LL misses:        12,551,019  (    6,280,949 rd   +   6,270,070 wr)
   LL miss rate:            0.3% (          0.2%     +         6.2%  )
  */
  horizontal(arr);
  
  /* VERTICAL ONLY (EXECUTION TIME W Cachegrind ON: 5459 ms)
   I   refs:      2,707,447,818
   I1  misses:            2,154
   LLi misses:            2,078
   I1  miss rate:          0.00%
   LLi miss rate:          0.00%
   
   D   refs:      1,502,723,891  (1,401,807,176 rd   + 100,916,715 wr)
   D1  misses:      118,810,955  (  112,539,868 rd   +   6,271,087 wr)
   LLd misses:       12,541,255  (    6,271,185 rd   +   6,270,070 wr)
   D1  miss rate:           7.9% (          8.0%     +         6.2%  )
   LLd miss rate:           0.8% (          0.4%     +         6.2%  )
   
   LL refs:         118,813,109  (  112,542,022 rd   +   6,271,087 wr)
   LL misses:        12,543,333  (    6,273,263 rd   +   6,270,070 wr)
   LL miss rate:            0.3% (          0.2%     +         6.2%  )
  */
  vertical(arr);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << duration.count() << std::endl;

  // Freeing memory
  for (int i = 0; i < ROWS; i++) {
    free(arr[i]);
  }
  free(arr);

  return 0;
}
