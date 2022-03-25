# TFG
This is my final work project to obtain my degree in computer engineer.


In this project we will try to replicate, transform and redesign a Python code to C/C++ to try to increase its execution speed, because the problem that is being handled, the problem of inverse folding of the RNA, has to deal with a search space with an exponential size with respect to the length of the sequence that is inserted, necessary to carry out said execution. 

This leads to high execution times for very long sequences, which it is believed that can be reduced by transforming said code to a lower-level language, faster and with lower time in execution. 

The Python code that has been used is a reverse folding algorithm based on Monte Carlo search trees (MCTS), hence the name of the algorithm: MCTS-RNA, this algorithm has shown a good ability to find solutions and to control with precision the GC base pair content of RNA structures over other existing algorithms.

To carry out this objective, a new C/C++ project has to be carried out. In this project, a large part of the code must be redesigned and adapted due to the differences between the aforementioned languages, as well as carrying out the pertinent tests to ensure correct operation and, in the best scenario, to confirm the improvement in performance.





Original Code in Python can be found here: https://github.com/tsudalab/MCTS-RNA

For run Python code: 


How to use MCTS-RNA?
Once you downloaded the python script of MCTS-RNA and having installed all the requirements, you can execute MCTS-RNA from the shell. The inputs include the dot-bracket representation of target RNA secondary structure ,the target GC-content of the RNA sequence and GC-content error. The following are the examples and explanations of the inputs parameters.

This is an example of the command in the shell for nested RNA structures.

python MCTS-RNA.py -s "...(((((..........)))))........((((((((......))))))))(((((.......))))).............(((((..(((((..((..((.(((((.(((((.......))))).)))))...))....))))))))))))" -GC 0.75 -d 0.01 -pk 0

This is an example of the command in the shell for pseudoknot RNA structures.

python MCTS-RNA.py -s "....(((((.[[[[.))))).........]]]]..." -GC 0.4 -d 0.02 -pk 1

-s : The target RNA secondary structure.

-GC: The target GC-content of the RNA sequence, choose vaule from the range [0,1].

-d : The GC-content deviation of the solution, which is in range [0,0.02]. MCTS-RNA can output the sequence with more accurate GC-content with smaller GC-content devation setting, the default value of the GC-content devation is 0.01.

-pk: Design nested structure by setting -pk 0 and design pseudoknot structure by setting -pk 1 (currently MCTS-RNA only uses Pkiss) to predict pseudoknot structures.


