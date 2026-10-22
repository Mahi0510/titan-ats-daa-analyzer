# TITAN ATS — Candidate Ranking & DAA Analyzer

A responsive, browser-based candidate ranking prototype for a Design and Analysis of Algorithms (DAA) mini-project. The ranking engine is written in C++ and compiled to WebAssembly (WASM) for use in modern browsers.

## What it does

- Add candidates manually or import a CSV file.
- Work with sample candidate records for a safe demo.
- Rank candidates by a supplied match score using **C++ Bubble Sort** or **C++ Merge Sort**.
- Compare comparison counts, data movements, and measured runtime.
- Search for an exact score using **Binary Search** on a descending-sorted list.
- Export the ranked list to CSV.
- Responsive layout for mobile, tablet, and desktop browsers.
- Candidate records are processed in the browser; this prototype does not upload candidate data to a server.

## Important scope and privacy note

This is a **DAA educational prototype**, not a complete commercial ATS and not an AI resume-scoring product. It does not parse resumes, infer candidate suitability, provide authentication, or store data in a cloud database. Match scores are supplied by the user or demo data. Do not enter sensitive real applicant information into this prototype.

A publicly hosted static version can be accessed worldwide, but deployment requires publishing the built files. GitHub Pages can build the C++ WebAssembly module automatically from this repository.

## DAA algorithms

| Algorithm | Purpose | Time complexity | Auxiliary space |
|---|---|---|---|
| Bubble Sort (optimized) | Rank candidates by score, descending | Best O(n), average/worst O(n²) | O(1) |
| Merge Sort | Rank candidates by score, descending | O(n log n) in all cases | O(n) |
| Binary Search | Find an exact score in descending order | O(log n) | O(1) iterative |

The runtime display is empirical and varies with device, browser, and input size. Operation counts are usually more useful than tiny timing differences.

## Run locally

### Option A — build the real C++/WASM engine

Install [Emscripten](https://emscripten.org/docs/getting_started/downloads.html), then from this folder run:

```bash
em++ src/algorithms.cpp -O2 -std=c++17 \
  -s WASM=1 \
  -s MODULARIZE=1 \
  -s EXPORT_NAME=createTitanModule \
  -s ENVIRONMENT=web \
  -s EXPORTED_FUNCTIONS='["_bubbleSort","_mergeSort","_binarySearch","_getComparisons","_getMoves","_resetCounters","_malloc","_free"]' \
  -s EXPORTED_RUNTIME_METHODS='["cwrap"]' \
  -o web/titan.js
```

Then serve the `web` directory using a local web server (not `file://`):

```bash
python -m http.server 8000 --directory web
```

Open `http://localhost:8000`.

### Option B — use the GitHub Pages workflow

1. Create a new GitHub repository and upload the contents of this folder.
2. In the repository, open **Settings → Pages** and set the source to **GitHub Actions**.
3. Push to the `main` branch. The workflow compiles the C++ engine to WebAssembly and publishes the site.
4. Open the Pages URL shown in the repository's Pages settings.

The included workflow uses the official `emscripten/emsdk` GitHub Action and GitHub Pages deployment actions. Review and pin action versions to your organisation's security policy before commercial use.

## CSV format

Use a header row with these columns:

```csv
name,role,score
Aarav Shah,Python Developer,86
Mira Joshi,Data Analyst,92
Sam Lee,Security Intern,78
```

Scores must be numeric from 0 to 100. Avoid importing sensitive personal information. The application validates basic input and treats CSV content as text, not HTML.

## Suggested DAA experiment

Test input sizes such as 10, 100, 500, 1,000, and 5,000 candidates. For each size, compare Bubble Sort and Merge Sort on random, already sorted, and reverse-sorted score sets. Record comparisons and movements. Do not make claims based on one runtime sample; repeat runs and report the median if you need a formal experiment.

## Suggested report sections

1. Abstract and problem statement
2. Objectives and scope
3. System architecture
4. Algorithms and pseudocode
5. Complexity analysis
6. Implementation details (C++ compiled to WebAssembly)
7. Test cases and experimental results
8. Limitations, privacy, and future scope
9. Conclusion

## Before real-world/commercial use

Add a security review, accessibility testing, privacy/legal review, authentication and authorisation if server-side data is introduced, audit controls, retention/deletion policy, backups, monitoring, abuse protection, and a validated candidate-scoring process. Employment-related ranking can materially affect people; scores should be explainable, reviewed by humans, tested for disparate impact, and never treated as an automatic hiring decision.
