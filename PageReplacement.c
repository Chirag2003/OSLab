#include <stdio.h>
#include <stdlib.h>

int findPageIndex(int page, int page_frames[], int num_frames) {
    for (int i = 0; i < num_frames; i++) {
        if (page_frames[i] == page) {
            return i;
        }
    }
    return -1;
}

int fifo(int page_references[], int num_references, int num_frames) {
    int page_frames[num_frames];
    int page_faults = 0;
    int frame_index = 0;

    for (int i = 0; i < num_references; i++) {
        int page = page_references[i];
        if (findPageIndex(page, page_frames, num_frames) == -1) {
            if (frame_index < num_frames) {
                page_frames[frame_index++] = page;
            } else {
                page_frames[frame_index] = page;
                frame_index = (frame_index + 1) % num_frames;
            }
            page_faults++;
        }
    }

    return page_faults;
}

int lru(int page_references[], int num_references, int num_frames) {
    int page_frames[num_frames];
    int page_faults = 0;

    for (int i = 0; i < num_references; i++) {
        int page = page_references[i];
        int page_index = findPageIndex(page, page_frames, num_frames);

        if (page_index == -1) {
            if (page_faults < num_frames) {
                page_frames[page_faults] = page;
            } else {
                int min_index = 0;
                for (int j = 1; j < num_frames; j++) {
                    if (page_references[i - 1 - j] == page_frames[min_index]) {
                        min_index = j;
                    }
                }
                page_frames[min_index] = page;
            }
            page_faults++;
        }
    }

    return page_faults;
}

// Function to simulate Optimal page replacement algorithm
int optimal(int page_references[], int num_references, int num_frames) {
    int page_frames[num_frames];
    int page_faults = 0;

    for (int i = 0; i < num_references; i++) {
        int page = page_references[i];
        int page_index = findPageIndex(page, page_frames, num_frames);

        if (page_index == -1) {
            if (page_faults < num_frames) {
                page_frames[page_faults] = page;
            } else {
                // Find the page that will not be used for the longest time
                int farthest_use = -1;
                int replace_index = -1;
                for (int j = 0; j < num_frames; j++) {
                    int page_to_find = page_frames[j];
                    int k;
                    for (k = i + 1; k < num_references; k++) {
                        if (page_references[k] == page_to_find) {
                            if (k > farthest_use) {
                                farthest_use = k;
                                replace_index = j;
                            }
                            break;
                        }
                    }
                    if (k == num_references) {
                        replace_index = j;
                        break;
                    }
                }
                page_frames[replace_index] = page;
            }
            page_faults++;
        }
    }

    return page_faults;
}

int main() {
    int num_references, num_frames;
    printf("Enter the size: ");
    scanf("%d", &num_references);

    int page_references[num_references];
    printf("Enter the string of page: ");
    for (int i = 0; i < num_references; i++) {
        scanf("%d", &page_references[i]);
    }

    printf("Enter the number of page frames: ");
    scanf("%d", &num_frames);

    int fifo_faults = fifo(page_references, num_references, num_frames);
    int lru_faults = lru(page_references, num_references, num_frames);
    int optimal_faults = optimal(page_references, num_references, num_frames);

    printf("FIFO Page Faults: %d\n", fifo_faults);
    printf("LRU Page Faults: %d\n", lru_faults);
    printf("Optimal Page Faults: %d\n", optimal_faults);

    return 0;
}