# Resizable-Deque

This is an implementation of a resizable deque using an array. A deque stores elements in an ordered list and allows insertions and deletions at both ends of the list in O(1) time. 

Capacity of array may be changed depending on number if elements currently stored in array, following the two rules:
1)  If an element is being inserted into a deque where the array is already full, the capacity of the array is doubled.
2) If, after removing an element from a deque the number of elements is 1/4 the capacity of the array or less, then the capacity of the array is halved. The capacity of the array may not be reduced below the initially specified capacity.

This is my code completed for ECE 250 Project 2. 
