# TITAN ATS: Candidate Ranking & Algorithm Analytics

## Abstract
This project demonstrates how sorting and searching algorithms can support candidate-score ranking workflows. A responsive browser interface invokes a C++ algorithm engine compiled to WebAssembly. Bubble Sort and Merge Sort rank candidates by a user-provided score, while Binary Search locates an exact score in descending-sorted results.

## Problem statement
Recruitment workflows may need to order candidates by an existing score. The project compares alternative sorting algorithms and measures their operation counts and execution time on different input sizes.

## Objectives
- Implement Bubble Sort and Merge Sort in C++.
- Implement Binary Search on descending-sorted scores.
- Count comparisons and index movements.
- Measure runtime and compare theoretical complexity with empirical results.
- Present results through a responsive browser UI.

## Scope and limitations
The prototype does not parse resumes or generate AI scores. All scores are user-supplied or fictional demo values. Results are not a recommendation to hire or reject a person.

## Methodology
1. Create or import candidate records containing a name, role, and score.
2. Create an index array so algorithms can reorder records without moving the full records.
3. Execute the selected C++ sorting algorithm.
4. Record comparisons, movements, and elapsed time.
5. Compare outcomes across datasets and input sizes.
6. Use Binary Search on descending-sorted scores.

## Pseudocode

### Bubble Sort (descending)
```text
for end from n-1 down to 1:
    swapped = false
    for i from 0 to end-1:
        comparisons++
        if score[index[i]] < score[index[i+1]]:
            swap(index[i], index[i+1])
            movements += 3
            swapped = true
    if not swapped:
        stop
```

### Merge Sort (descending)
```text
mergeSort(left, right):
    if range has 0 or 1 elements: return
    split range into two halves
    mergeSort(left half)
    mergeSort(right half)
    merge halves in descending score order
```

### Binary Search (descending)
```text
left = 0; right = n-1
while left <= right:
    mid = left + (right-left)/2
    if score[mid] == target: return mid
    if score[mid] < target: right = mid-1
    else: left = mid+1
return not found
```

## Complexity analysis
| Algorithm | Best | Average | Worst | Auxiliary space |
|---|---|---|---|---|
| Optimized Bubble Sort | O(n) | O(n²) | O(n²) | O(1) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) |
| Iterative Binary Search | O(1) | O(log n) | O(log n) | O(1) |

## Experimental results
Run multiple tests and fill this table with actual results from your own browser. Do not invent timing data.

| Input size | Input order | Algorithm | Comparisons | Movements | Time (ms) |
|---:|---|---|---:|---:|---:|
| 100 | Random | Bubble Sort | | | |
| 100 | Random | Merge Sort | | | |
| 1,000 | Random | Bubble Sort | | | |
| 1,000 | Random | Merge Sort | | | |
| 5,000 | Random | Merge Sort | | | |

## Test cases
- Empty data set
- One candidate
- All scores equal
- Already sorted scores
- Reverse-sorted scores
- Duplicate scores
- CSV with valid data
- CSV with missing columns or invalid scores
- Binary Search: score found and score not found

## Conclusion
Summarise the measured results and explain when Merge Sort is preferable to Bubble Sort. State that runtime varies by device and that operation counts support the comparison.

## Future scope
- Integrate a validated resume-parsing and scoring pipeline.
- Add authenticated server-side accounts only after security and privacy review.
- Add larger-scale experiments and visualisations.
- Add human-review workflows and fairness evaluation before any real hiring use.
