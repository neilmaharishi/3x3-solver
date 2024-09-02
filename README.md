# 3x3 solver
 
This program uses an iteration of the A* algorithm, iterative deepening A*, to solve a 3x3 Rubik's cube. Due to the extremely large solution space of a 3x3 Rubik's cube (~43 quintillion), IDA* is a far more appropriate search algorithm due to less memory usage.

Run "make cube" to compile and ./cube to run this program. 

# References 
https://www.cs.princeton.edu/courses/archive/fall06/cos402/papers/korfrubik.pdf
https://medium.com/@benjamin.botto/implementing-an-optimal-rubiks-cube-solver-using-korf-s-algorithm-bf750b332cf9
https://stackoverflow.com/questions/36490073/heuristic-for-rubiks-cube#



# Future Additions
This is still an early version of the project, and requires improvements to be truly functional at scale. Due to the exponential increase in the solution space after a singular scramble, the performance of this application significantly drops off after 6 scrambles. To address this, I plan on implementing the pattern databases linked in the paper above. There are also other techniques, such as parallelization and bidirectional searching, which could also drastically improve performance. 
