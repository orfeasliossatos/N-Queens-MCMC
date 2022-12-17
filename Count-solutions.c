#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <float.h>

// A csv for beta_stars from N = 4..27.
const char FILENAME_KNOWN_BETA_STARS[] = "knownbetastars.csv";
// A text file with known counts from N = 4..27
const char FILENAME_KNOWN_COUNTS[] = "knowncounts.txt";
// Number of known counts
const int NUM_KNOWN = 27 - 4 + 1;

/**
 * Returns log(n!).
 */
double logfact(int n) {
	double res = 0;
	for (int i = 1; i <= n; i++) {
		res += log((double) i);
	}
	return res;
}

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
 * Finds the largest element in an unsorted array.
 */
 double arr_max(double* z, int len) {
	 double largest_so_far = -DBL_MAX;
	 for (int i = 0; i < len; i++) {
		 if (largest_so_far < z[i]) {
			largest_so_far = z[i];
		 }
	 }
	 return largest_so_far;
}

/**
 * Returns the sum of all elements in the array.
 */
double sum(double* z, int len) {
	double s = 0;
	for (int i=0; i < len; i++) {
		s += z[i];
	}
	return s;
}

/**
 * Exponentiate each element of an array. Inplace.
 */
double* exp_arr(double* z, int len) {
	 for (int i=0; i < len; i++) {
		 z[i] = exp(z[i]);
	 }
	 return z;
}

/**
 * Multiply each element of z by a scalar. Inplace.
 */
double* scal_prod(double r, double* z, int len) {
	 for (int i=0; i < len; i++) {
		 z[i] *= r;
	 }
	 return z;
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
 * Prints an array of long long unsigned
 */
void print_llu_arr(long long unsigned* z, int length)
{
	printf("[ ");
	for (int i = 0; i < length; i++) {
		printf("%I64u ", z[i]);
	}
	printf("]\n");
}

/**
 * Prints an array of doubles
 */
void print_lf_arr(double* z, int length)
{
	printf("[ ");
	for (int i = 0; i < length; i++) {
		printf("%.3lf ", z[i]);
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
double max_lf(double a, double b) {
	return a*(a>b) + b*(a<=b);
}

/**
 * Returns the max of two long long unsigned integers.
 */
long long unsigned max_llu(long long unsigned a, long long unsigned b) {
	return a*(a>b) + b*(a<=b);
}

/**
 * Percentage difference between two long long unsigned integers.
 */
double percent_diff(long long unsigned x, long long unsigned y) {
	return (double) abs(x-y) / max_llu(x,y);
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

/**
 * Reads long long unsigned integer array from files with format
 * a1,a2,a3,a4,a5,...
 */
void load_llu_arr(char* filename, long long unsigned *dst, int len) {
	
	FILE *fp = fopen(filename, "r");
	if(fp == NULL) {
        printf("file can't be opened\n");
        exit(1);
    }
    
    for (int i = 0; i < len; i++) {
		fscanf(fp, "%I64u,", &dst[i]);
	}
}

/**
 * Reads long long unsigned integer array from files with format
 * a1,a2,a3,a4,a5,...
 */
void save_lf_arr(char* filename, double *src, int len) {
	
	FILE *fp = fopen(filename, "w");
	if(fp == NULL) {
        printf("file can't be opened\n");
        exit(1);
    }
    
    for (int i = 0; i < len; i++) {
		fprintf(fp, "%lf,", src[i]);
	}
}

/**
 * Procedure to find the beta_stars which best approximate known
 * solution counts.
 */
double* beta_stars(int M, double beta_del) {
	
	// Read and print out known solution counts.
	long long unsigned *Z_inf_known = malloc(NUM_KNOWN * sizeof(long long unsigned));
	load_llu_arr("knowncounts.txt", Z_inf_known, NUM_KNOWN);
	
	printf("Known solution counts for N=4..27:\n");
	print_llu_arr(Z_inf_known, NUM_KNOWN);
	printf("\n");
	
	// Map to log.
	double *log_Z_inf_known = malloc(NUM_KNOWN * sizeof(double));
    
    for (int i = 0; i < NUM_KNOWN; i++) {
		log_Z_inf_known[i] = log(Z_inf_known[i]);
	}
	
	// Approximated solution counts.
	long long unsigned *Z_inf_guess = malloc(NUM_KNOWN * sizeof(long long unsigned));	
	
	// Array of beta_star_known to fill in.
	double *beta_star_known = malloc(NUM_KNOWN * sizeof(double));
	int N = 4; 
	
	printf("Parameters: M = %d, beta_del = %.3lf\n\n", M, beta_del);
	
	// For every N for which the number of solutions is known
	for (int i = 0; i < NUM_KNOWN; i++, N++) {
		
		int C = N * (N-1) / 2;
		double log_Z_partial = 0; // Current estimate.
		int T = 0; // Discover T.
		
		// Approach the real number of solutions
		while(1) {
			// Starting position
			int *z = malloc(N * sizeof(int));
			arange(z, 1, N+1, 1);
		
			// Pairs of queen indices
			int *idx_pairs = malloc(2 * C * sizeof(int));
			pairs(idx_pairs, N);
			
			// Shuffle the starting position
			shuffle(z, 2 * N, idx_pairs, C);
			
			// Calculate current loss
			int l = loss(z, idx_pairs, C);
			
			double *losses = malloc(M * sizeof(double));
			
			// Draw M samples according to the Metropolis Algorithm.
			for (int k = 0; k < M; k++) {
				
				int r = (rand() % C);
				int m = idx_pairs[2*r]; 
				int n = idx_pairs[2*r+1];
				double diff = (double)loss_diff(z, m, n, N);
				double acc = (diff < 0) ? 1 : exp(-T*beta_del*diff);
				double u = ((double)rand() / (double)(RAND_MAX));
				if (u < acc) {
					swap(z, m, n);
					l += diff;
				}
				losses[k] = (double) l;
			}
			
			// Estimate ratio
			double log_Z_beta_t_ratio = 
				log(sum(exp_arr(scal_prod(
							-beta_del,losses,M),M),M)/M);
			
			// If the next partial sum undershoots the estimate, break.
			if (log_Z_partial + log_Z_beta_t_ratio + logfact(N) 
					< log_Z_inf_known[i]) {
				break;
			}
			
			// Otherwise, incorporate the next term.
			log_Z_partial += log_Z_beta_t_ratio;
			
			T++;
			
			free(z);
			free(losses);
			free(idx_pairs);
		}
		
		// Now T is known.
		beta_star_known[i] = T * beta_del;
		
		// Record approximation.
		Z_inf_guess[i] = (long long unsigned) exp(log_Z_partial+logfact(N));
	}
	
	// Calculate guess quality.
	double *guess_quality = malloc(NUM_KNOWN * sizeof(double));
	for (int i = 0; i < NUM_KNOWN; i++) {
		guess_quality[i] = percent_diff(Z_inf_guess[i], Z_inf_known[i]);
	}
	
	// Print guesses.
	printf("Solution count guesses\n");
	print_llu_arr(Z_inf_guess, NUM_KNOWN);
	printf("\n");
	
	// Print guess quality
	printf("Worst guess percent diff: ");
	printf("%.2lf%%\n\n", 100 * arr_max(guess_quality, NUM_KNOWN));
	
	// Print beta-stars.
	printf("Beta-stars\n");
	print_lf_arr(beta_star_known, NUM_KNOWN);
	printf("\n");
	
	// Print 
	free(Z_inf_known);
	free(Z_inf_guess);
	free(guess_quality);
	free(log_Z_inf_known);
	return beta_star_known;
}

int main()
{	
	// Timing start
	time_t then;
	time(&then);
	
	// Reproducibility
	srand(2022);
	
	// Find good beta_stars for known solutions N=[4...27]
	double* beta_stars_known = beta_stars(1000, 0.001);
	save_lf_arr("betastars.txt", beta_stars_known, NUM_KNOWN);
	
	// 
	
	// Timing end
	time_t now;
	time(&now);
	
	time_t diff = now - then;
	
	printf("Began: %s", ctime(&then));
	printf("Ended: %s", ctime(&now));
	printf("Diff: %d minutes, %d seconds", diff / 60, diff % 60);
	
	// Free
	free(beta_stars_known);
	
	// Finish
	return 0;
}
