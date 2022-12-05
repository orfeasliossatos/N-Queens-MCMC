#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

/**
 * Fills in z with integers from min to max by step inplace.
 */
void arange(int* z, int min, int max, int step) 
{	
	for (int i = 0; i < max-min; i += step) {
		z[i] = min + i;
	}
}

/**
 * Prints an array of integers
 */
void print_int_arr(int* z, int length)
{
	printf("[ ");
	for (int i = 0; i < length; i++) {
		printf("%d ", z[i]);
	}
	printf("]\n");
}

/**
 * Prints an array of doubles
 */
void print_dbl_arr(double* z, int length)
{
	printf("[ ");
	for (int i = 0; i < length; i++) {
		printf("%lf.3 ", z[i]);
	}
	printf("]\n");
}


/**
 * Swaps two array indices inplace.
 */
void swap(int* z, int i, int j) 
{
	int t = z[i];
	z[i] = z[j];
	z[j] = t;
}

/**
 * Calculates number of unique threats on board.
 */
int loss(int* z, int* idx_pairs, int C) 
{
	int sum = 0;
	for (int k = 0; k < 2 * C; k += 2) {
		int i = idx_pairs[k]; int j = idx_pairs[k+1];
		sum += (j - i == abs(z[j] - z[i]));
	}
	return sum;
}

/**
 * Calculates all pairwise combinations of indices less than N
 * and stores them contiguously in dst.
 */
void pairs(int* dst, int N) 
{
	int k = 0;
	for (int i = 0; i < N-1; i++) {
		for (int j = i+1; j < N; j++) {
			dst[k] = i;
			dst[k+1] = j;
			k += 2;
		}
	}
}

/**
 * Returns the minimum of two doubles.
 */
double min(double a, double b) {
	return a*(a<b) + b*(a>=b);
}

/**
 * Returns the max of two doubles.
 */
double max(double a, double b) {
	return a*(a>b) + b*(a<=b);
}

/**
 * Returns number of queens threatening queen i.
 */
int threats(int* z, int i, int N) {
	int sum = 0;
	for (int k = 0; k < N; k++) {
		sum += abs(k-i) == abs(z[k]-z[i]);
	}
	sum -= 1;
	return sum;
}

/**
 * One-step loss difference.
 */
int loss_diff(int* z, int i, int j, int N) {
	int old = threats(z, i, N) + threats(z, j, N);
	swap(z, i, j);
	int new = threats(z, i, N) + threats(z, j, N);
	swap(z, i, j); // Swap back.
	return new - old;
}

/**
 * Sample from the distribution p with support size X.
 */
int sample(double *p, int X) {
	
	double r = (double) rand() / RAND_MAX;
	double F = 0;
	int k = 0;
	for (; k < X; k++) {
		F += p[k];
		if (r <= F) { break; }
	}
	return k;
}

/**
 * Perform K random swaps on a list of integers.
 */
void shuffle(int* z, int K, int* idx_pairs, int nb_pairs) 
{
	for (int k = 0; k < K; k++) {
		int pair_idx = (rand() % nb_pairs) * 2;
		int i = idx_pairs[pair_idx];
		int j = idx_pairs[pair_idx+1];
		swap(z, i, j);
	}
}

/**
 * Assumes memory has been allocated. Copies len elements of 
 * src into dst.
 */
void arrcopy(int* src, int* dst, int len) 
{
	for (int i = 0; i < len; i++) {
		dst[i] = src[i];
	}
}

int main()
{	
	// Snapshot of time
	time_t then;
	time(&then);
	
	// Reproducibility
	srand(2022);
	
	// Variables
	int N = 1000;
	int C = N * (N-1) / 2;
	double b = 1;
	
	// Starting position
	int *z = malloc(N * sizeof(int));
	arange(z, 1, N+1, 1);
	
	// Pairs of queen indices
	int *idx_pairs = malloc(2 * C * sizeof(int));
	pairs(idx_pairs, N);
	
	// Shuffle the starting position
	shuffle(z, 2 * N, idx_pairs, C);
		
	// Search
	int t = 0;
	int MAX_ITERS = 10000000;
	
	// Calculate current loss
	int l = loss(z, idx_pairs, C);
	
	for (t = 1; t < MAX_ITERS; t++) {
		
		b = log(t*t/N);
		int k = (rand() % C);
		int i = idx_pairs[2*k]; 
		int j = idx_pairs[2*k+1];
		int diff = loss_diff(z, i, j, N);
		double acc = min(1, exp(-b*diff));	// Acceptance probability.
		double r = ((double)rand() / (double)(RAND_MAX));
		if (r < acc) {
			swap(z, i, j);
			l += diff;
		}
		
		if (l == 0) { break; }
	}
	
	// Results
	printf("\nFor the %d - queens problem\n----------------\n", N);
	
	if (loss(z, idx_pairs, C) == 0) {
		printf("Solution found in %d iterations:\n", t);
		print_int_arr(z, N);
	} else {
		printf("Solution not found in %d iterations\n", MAX_ITERS);
		print_int_arr(z, N);
	}
	
	// Timing information
	time_t now;
	time(&now);
	
	time_t diff = now - then;
	
	printf("Began: %s", ctime(&then));
	printf("Ended: %s", ctime(&now));
	printf("Diff: %d minutes, %d seconds", diff / 60, diff % 60);
	
	free(z);
	free(idx_pairs);
	return 0;
}
