#include <algorithm>
#include <cstddef>
#include <vector>

// C++ algorithm engine compiled to WebAssembly.
// `scores` is the source score array; `indices` is reordered so the UI can
// retain candidate records. Scores are ranked descending (highest first).

static long long comparisons = 0;
static long long moves = 0;

extern "C" {

void resetCounters() {
    comparisons = 0;
    moves = 0;
}

long long getComparisons() {
    return comparisons;
}

long long getMoves() {
    return moves;
}

void bubbleSort(const double* scores, int* indices, int n) {
    resetCounters();
    if (!scores || !indices || n <= 1) return;

    for (int end = n - 1; end > 0; --end) {
        bool swapped = false;
        for (int i = 0; i < end; ++i) {
            ++comparisons;
            // Descending order: larger score should come first.
            if (scores[indices[i]] < scores[indices[i + 1]]) {
                std::swap(indices[i], indices[i + 1]);
                moves += 3;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

static void mergeRange(const double* scores, int* indices,
                       int* scratch, int left, int mid, int right) {
    int i = left;
    int j = mid;
    int k = left;

    while (i < mid && j < right) {
        ++comparisons;
        if (scores[indices[i]] >= scores[indices[j]]) {
            scratch[k++] = indices[i++];
        } else {
            scratch[k++] = indices[j++];
        }
        ++moves;
    }

    while (i < mid) {
        scratch[k++] = indices[i++];
        ++moves;
    }
    while (j < right) {
        scratch[k++] = indices[j++];
        ++moves;
    }
    for (int p = left; p < right; ++p) {
        indices[p] = scratch[p];
        ++moves;
    }
}

static void mergeSortRange(const double* scores, int* indices,
                           int* scratch, int left, int right) {
    if (right - left <= 1) return;
    const int mid = left + (right - left) / 2;
    mergeSortRange(scores, indices, scratch, left, mid);
    mergeSortRange(scores, indices, scratch, mid, right);
    mergeRange(scores, indices, scratch, left, mid, right);
}

void mergeSort(const double* scores, int* indices, int n) {
    if (!scores || !indices || n <= 1) {
        resetCounters();
        return;
    }
    resetCounters();
    std::vector<int> scratch(static_cast<std::size_t>(n));
    mergeSortRange(scores, indices, scratch.data(), 0, n);
}

// Returns the first matching index in a score array sorted descending,
// or -1 if the exact score is not found.
int binarySearch(const double* scores, const int* indices, int n, double target) {
    if (!scores || !indices || n <= 0) return -1;
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        const int mid = left + (right - left) / 2;
        ++comparisons;
        const double value = scores[indices[mid]];
        if (value == target) return mid;
        if (value < target) right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}

} // extern "C"
