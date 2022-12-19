# N-Queens-MCMC

Welcome to our github repo, you will find here our work on the N-queens problem as part of our project in Markov Chain & Algorithmic Applications (MCAA) course at EPFL, 2022. 

For the first part of the project, we apply the [Metropolis-Hastings algorithm](https://en.wikipedia.org/wiki/Metropolis%E2%80%93Hastings_algorithm) to a find solutions to the N-Queens problem for large values of N. We also investigate the impact of different schemes for the inverse temperature coefficient $\beta$ on the convergence times of the algorithm.

For the second part of the project, we use an extension of the Metropolis-Hastings algorithm to estimate the number of solutions to the N-Queens problem. For N greater than 27, the true number of solutions is unknown. 

Example command for compiling the C scripts : 
`gcc -std=c11 -o N-Queens.exe N-Queens.c -lm`

# Structure

## Part 1.

Main part :

`N-Queens.c` : C script implementing Metropolis-Hastings algorithm. Compile and run to produce two files, namely 
1. `N_Queens_solution.csv` : Two columns of integers from 1 to N representing row and column indices of a solution to the N-queens problem. The value of N is 1000, which is hardcoded.
2. `losses.csv` : Multiple rows of comma-separated integers representing the loss at every iteration of the Metropolis-Hastings algorithm. Each row corresponds to a new run of the algorithm (with `repeat` number of rows). The value of `repeat` is 10, which is hardcoded. The value of beta(t) is also hardcoded (and could be for ex. log(t), log(t*t) or t). You can find in the folder `beta(t)_data` the csv data and plots for the different values of beta(t) we tried.

Additional :
1. `N-Queens.ipynb` : Our python implementation of the Metropolis-Hastings algorithm. It is not used in the final report (as less efficient than our C implementation), but is kept for reference.
2. `Measure_time.ipynb` : Jupyter Notebook that measures the efficiency of different implementations of some of the function we can find in the Metropolis-Hastings algorithm implemented in `N-Queens.ipynb`.
3. `beta(t)_data` : Folder containing the data and plots for the different values of beta(t) we tried. The data is in csv format, and the plots are in png format. The data is a csv file with 10 rows, each row corresponding to a run of the Metropolis-Hastings algorithm. The columns are the losses at each iteration of the algorithm. The value of N is 1000, which is hardcoded.
4. `plots_solutions.ipynb` : Jupyter Notebook used to plot the figure in our LaTeX report.

## Part 2.

`KnownBetastars.c` : C script that finds values of $\beta^*$ such that the estimator of the number of solutions to the [4-27]-Queens problem is highly accurate (~0.1% difference between ground truth and estimate). It writes these values to a single row in `knownbetastars.csv`.

`FitBetastars.ipynb` : Jupyter Notebook that fits various curves to the values in `knownbetastars.csv` for N=[10-27], since they appear to be somewhat regular for N not too small. Using the exponential model, it predicts values for N=[100-1000] by increments of 100 and writes them to `fitbetastars.csv`.

`Count-solutions.c` : C script that estimates the number of solutions the the N-queens problem for N=[100-1000] by increments of 100 by reading `fitbetastars.csv`. The number of solutions is estimated iteratively, with the evolving estimates being appended to rows of `partialestimates[0-9].csv`. These are large files, so are omitted from the repository, but can be transfered upon request.

`ApproximateSolutions.ipynb` : Jupyter Notebook that graphs the evolution of estimates from `partialestimates[0-9].csv`, as well as their variance. This shows the quality of the estimator.


# Authors 

Michel Jean-Baptiste, Orfeas Liossatos and Gaiëtan Renault

# Project report

Currenty at : https://www.overleaf.com/read/ntrtspbrbjwx
