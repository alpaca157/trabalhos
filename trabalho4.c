#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int difficulty;
    int profit;
} Job;

void merge_sort(Job* job, int left, int right);
void merge(Job* job, int left, int mid, int right);

int maxProfitAssignment(int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize) {
    Job* job = (Job*)malloc(difficultySize * sizeof(Job));
    int max_profit = 0;

    for (int i = 0; i < difficultySize; i++) {
        job[i].difficulty = difficulty[i];
        job[i].profit = profit[i];
    }

    merge_sort(job, 0, difficultySize - 1);

    
    for (int i = 0; i < workerSize; i++) {
        int j = 0, best_profit = 0;

        while (j < difficultySize) {
            if (job[j].difficulty <= worker[i]) {
                if (job[j].profit > best_profit) {
                    best_profit = job[j].profit;
                }
            } else {
                break;
            }
            j++;
        }
        max_profit += best_profit;
    }

    free(job);
    return max_profit;
}

void merge_sort(Job* job, int left, int right) {  
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(job, left, mid);
        merge_sort(job, mid + 1, right);

        merge(job, left, mid, right);
    }
}

void merge(Job* job, int left, int mid, int right) {
    int i, j, k;
    int left_length = mid - left + 1;
    int right_length = right - mid;
    
    Job *left_array = (Job*)malloc(sizeof(Job) * left_length);
    Job *right_array = (Job*)malloc(sizeof(Job) * right_length);
    
    for (int i = 0; i < left_length; i++) left_array[i] = job[left + i];
    for (int i = 0; i < right_length; i++) right_array[i] = job[mid + 1 + i];

    for (i = 0, j = 0, k = left; k <= right; k++) {
        if ((i < left_length) && 
        (j >= right_length || left_array[i].difficulty <= right_array[j].difficulty)) {
            job[k] = left_array[i];
            i++;
        } else {
            job[k] = right_array[j];
            j++;
        }
    }

    free(left_array);
    free(right_array);
}

int main() {
    int difficulty[] = {2, 4, 6, 8, 10};
    int profit[] = {10, 20, 30, 40, 50};
    int worker[] = {4, 5, 6, 7};

    int result = maxProfitAssignment(difficulty, 5, profit, 5, worker, 4);
    printf("Lucro máximo: %d\n", result);

    return 0;
}
