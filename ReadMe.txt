Included:
main.cpp
main.o
makefile

Tree order of 5:
1). All leaf nodes are on the same level
2). All non leaf nodes except the root has at least two children and a maximum of 5
3). The number of keys is one less than the number of children for non leaf nodes
4). The number of keys for leaf nodes is at most 4 children and at least 2 for leaf nodes
5). Root may hae as few as 2 children unless the tree root is alone

To grader:
The program does not work in a manner of how the assignemnt was sought out to be.
Some erros include:
After input program ends instead of returning to menu
Display of b tree
User input to search in the range rather than printing the numbers between n to 2n
Segmentation Fault

The proper use of this program would have the user input Generate a sequence of N random integers (keys), in the range [0,...,3*N],
with N >= 400.
The program would build a 5-way B-tree using the randomly generated keys, in the sequence order.
Then the program would search for/return any keys in the range [N, 2*N]

Program can be run using ./a.out