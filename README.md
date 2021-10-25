# binary_search_tree
### Node-based binary tree data structure, used to store and search for elements in an orderly manner. 

#### The left subtree of a node contains only nodes with keys smaller than the node's key, and on the right, larger ones.

**Tree used for the project:** https://i.imgur.com/GxlbvKK.png  

First, we insert the elements (50, 30, 90, 20, 40, 95, 10, 35, 45) in the tree in an orderly way, to form a binary search tree.

We calculate the following properties and tree paths:
* Pre-order transversal;
* Elements in descending order;
* Minimal element;
* Maximum element;
* Sum of the elements of the largest branch (largest sum).

We calculate, too, the cost / time of insertion and search of the BST algorithm for 32k elements (ordered ascending and then randomly).

The tests had the following results:
* Degenerate Tree (increasing inset): 1.70s;
* Non-degenerate tree (random insertion): 0.01s.

Finally, we give the user three options:
1. Insert an element of your choice;
2. Remove an element of your choice;
3. Find the lowest level common ancestor (LCA) of two nodes.
