# Ising
2D Ising Model Simulation on Matlab

## 2017-05-21
Basic code has been completed.  
Simulation code for square lattice ising model and triangle lattice ising model have both been checked and work well.
The next step is to add more code to calaulate more physics values, include wham graph.

## 2017-05-22
Code for Multiple Histogram Algorithm on Matlab is completed. But it's discovered that MATLAB doesn't support long double or other larger data type. So the current result of the simulation failed. NaN... All the results. So sad!  
I'm going to use C language instead. OpenMP will be used to achieve parallel computing.