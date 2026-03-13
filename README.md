Super simple directed percolation program written in C++ because directed percolation was mentioned in a talk on turbulence, and I became somewhat obsessed.

Requires SDL2.

A few examples of the results with varying probabilities of propagation below:

![](https://github.com/IlexCrow/directed_percolation_test/blob/main/samples/0f7dc608-aa3b-430d-b278-9d33c13b94cc.jpeg)
![](https://github.com/IlexCrow/directed_percolation_test/blob/main/samples/7f67a1d5-576e-4171-ba49-1b2a624ea232.jpeg)
![](https://github.com/IlexCrow/directed_percolation_test/blob/main/samples/91512d54-80fa-4927-956c-61d4e2e0ba4b.jpeg)

Process:
1. The top left pixel of the screen has a value of true; all other pixels have a value of false. 
2. That pixel then has a random chance of setting the pixels to the right and/or down from it to true.
3. If either or both of these pixels is set to true, the same process is repeated for them, and so on.

The probability of this propagation can be varied, to create the various scenarios in the above screenshots.
