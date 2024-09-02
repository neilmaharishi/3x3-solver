# 3x3 solver
 
This program uses an iteration of the A* algorithm, iterative deepening A*, to solve a 3x3 Rubik's cube. Due to the extremely large solution space of a 3x3 Rubik's cube (~43 quintillion), IDA* is a far more appropriate search algorithm due to lighter memory usage.

Run "make cube" to compile and ./cube to run this program. 

The program reads in a 2D cube in the following format:
```
    R R R 
    G W B 
    O O O 
O O R Y Y Y G R B Y Y Y 
W O Y G G O W R Y B B R 
R O O W W W B R G W W W 
    G G G 
    B Y G 
    B B B 
```

And will return a list of the faces that need to be rotated, along with the direction of each necessary rotation. For the example above, the program will return: 
```
Green CCW
Blue CCW
Orange CW
Red CW
White CCW
```

# Future Additions
This is still an early version of the project, and requires improvements to be truly functional at scale. Due to the exponential increase in the solution space after a singular scramble, the performance of this application significantly drops off after 6 scrambles. To address this, I plan on implementing the pattern databases linked in the paper above. There are also other techniques, such as parallelization and bidirectional searching, which could also drastically improve performance. 

# References 
https://www.cs.princeton.edu/courses/archive/fall06/cos402/papers/korfrubik.pdf 

https://medium.com/@benjamin.botto/implementing-an-optimal-rubiks-cube-solver-using-korf-s-algorithm-bf750b332cf9

https://stackoverflow.com/questions/36490073/heuristic-for-rubiks-cube#

