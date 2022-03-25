# TFG
This is my final work project to obtain my degree in computer engineer.


In this project we will try to replicate, transform and redesign a Python code to C/C++ to try to increase its execution speed, because the problem that is being handled, the problem of inverse folding of the RNA, has to deal with a search space with an exponential size with respect to the length of the sequence that is inserted, necessary to carry out said execution. 

This leads to high execution times for very long sequences, which it is believed that can be reduced by transforming said code to a lower-level language, faster and with lower time in execution. 

The Python code that has been used is a reverse folding algorithm based on Monte Carlo search trees (MCTS), hence the name of the algorithm: MCTS-RNA, this algorithm has shown a good ability to find solutions and to control with precision the GC base pair content of RNA structures over other existing algorithms.

To carry out this objective, a new C/C++ project has to be carried out. In this project, a large part of the code must be redesigned and adapted due to the differences between the aforementioned languages, as well as carrying out the pertinent tests to ensure correct operation and, in the best scenario, to confirm the improvement in performance.
