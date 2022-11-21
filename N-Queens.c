#include <stdio.h>
#include <stdlib.h>
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

int main()
{
	// Variables
	int N = 100;
	int C = N * (N-1) / 2;
	
	int *z = malloc(N * sizeof(int));
	arange(z, 1, N+1, 1);
	
	int *idx_pairs = malloc(2 * C * sizeof(int));
	pairs(idx_pairs, N);
	
	double *p = malloc((C+1) * sizeof(double));
	p[C] = 1;
	
	// Search
	
	
	srand(time(NULL));
	int MAX_ITERS = 10000;
	for (int t = 1; t < MAX_ITERS; t++) {
		
		// Calculate loss.
		int l = loss(z, idx_pairs, C);
		if (l == 0) { break; }
		
		if (t % 100 == 0) {
			printf("%d / %d - Loss=%d\n", t, MAX_ITERS, l);
		}
		
		// Outgoing arrows
		for (int k = 0; k < 2 * C; k+=2) {
			int i = idx_pairs[k]; int j = idx_pairs[k+1];
			p[k/2] = min(1, exp(-log(t*t/N)*loss_diff(z, i, j, N))) / C;
			p[C] -= p[k/2];
		}
		
		// Self-loop.
		p[C] = max(0, p[C]);
		
		// Choose a swap.
		int k = sample(p, C+1);
		if (k < C) {
			swap(z, idx_pairs[2*k], idx_pairs[2*k+1]);
		}
	}
	
	if (loss(z, idx_pairs, C) == 0) {
		printf("Solution : ");
		print_int_arr(z, N);
	} else {
		printf("Solution not found in %d iterations", MAX_ITERS);
	}
	
	free(z);
	free(idx_pairs);
	return 0;
}
