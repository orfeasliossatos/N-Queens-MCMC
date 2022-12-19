# N-Queens-MCMC

Welcome to our github repo, you will find here our work on the N-queens problem as part of our project in Markov Chain & Algorithmic Applications (MCAA) course at EPFL, 2022. 

For the first part of the project, we apply the [Metropolis-Hastings algorithm](https://en.wikipedia.org/wiki/Metropolis%E2%80%93Hastings_algorithm) to a find solutions to the N-Queens problem for large values of N. We also investigate the impact of different schemes for the inverse temperature coefficient $\beta$ on the convergence times of the algorithm.

For the second part of the project, we use an extension of the Metropolis-Hastings algorithm to estimate the number of solutions to the N-Queens problem. For N greater than 27, the true number of solutions is unknown. 

Example command for compiling the C scripts : 
`gcc -std=c11 -o N-Queens.exe N-Queens.c -lm`

# Structure

## Part 1.

Main part :

1. `N-Queens.c` : C script implementing Metropolis-Hastings algorithm. Produces `N_Queens_solution.csv`, which contains two columns of integers from 1 to N representing row and column indices of a solution to the N-queens problem. The value of N is 1000, which is hardcoded.

2. `Fixed.c` & `Annealing.c`: C scripts implementing Metropolis-Hastings algorithm. Produces `losses_beta_[7,8,9,10,100,1000].csv` and `losses_beta_[exp,identity,log,log_square,square].csv` in `data_beta_t` which record the loss value for different schemes of $\beta$ at every iteration of the Metropolis-Hastings algorithm. Each row corresponds to a new run of the algorithm (with `repeat` number of rows). The value of `repeat` is 50, which is hardcoded. 


Additional :
1. `N-Queens.ipynb` : Our python implementation of the Metropolis-Hastings algorithm. It is not used in the final report (as less efficient than our C implementation), but is kept for reference.
2. `Measure_time.ipynb` : Jupyter Notebook that measures the efficiency of different implementations of some of the function we can find in the Metropolis-Hastings algorithm implemented in `N-Queens.ipynb`.
3. `data_beta_t` : Folder containing the data and plots for the different values of beta(t) we tried. The data is in csv format, and the plots are in png format. The data is a csv file with 10 rows, each row corresponding to a run of the Metropolis-Hastings algorithm. The columns are the losses at each iteration of the algorithm. The value of N is 1000, which is hardcoded.
4. `plots_solutions.ipynb` : Jupyter Notebook used to plot the figures for the first part of our LaTeX report.

## Part 2.

1. `KnownBetastars.c` : C script that finds values of $\beta^*$ such that the estimator of the number of solutions to the [4-27]-Queens problem is highly accurate (~0.1% difference between ground truth and estimate). It writes these values to a single row in `knownbetastars.csv`.

2. `FitBetastars.ipynb` : Jupyter Notebook that fits various curves to the values in `knownbetastars.csv` for N=[10-27], since they appear to be somewhat regular for N not too small. Using the exponential model, it predicts values for N=[100-1000] by increments of 100 and writes them to `fitbetastars.csv`.

3. `Count-solutions.c` : C script that estimates the number of solutions the the N-queens problem for N=[100-1000] by increments of 100 by reading `fitbetastars.csv`. The number of solutions is estimated iteratively, with the evolving estimates being appended to rows of `partialestimates[0-9].csv`. These are large files, so are omitted from the repository, but can be transfered upon request.

4. `ApproximateSolutions.ipynb` : Jupyter Notebook that graphs the evolution of estimates from `partialestimates[0-9].csv`, as well as their variance. This shows the quality of the estimator.


# Authors 

Michel Jean-Baptiste, Orfeas Liossatos and Gaiëtan Renault

# Project statement

In `report/MCAA_Project_Problem.pdf`

# Project report

In `report/MCAA_Project_Report.pdf`

And currenty online at : https://www.overleaf.com/read/ntrtspbrbjwx
