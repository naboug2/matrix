
Description:

In C++, std::vector<T> is one of the most commonly used data structures. It’s efficient, and grows dynamically as needed. 
However, it’s a one-dimensional data structure. While it’s possible to use vector<T> to define two-dimensional structures
it’s awkward because each row is initially empty, requiring you to add columns on a row-by-row basis. 

The goal of this project is to define a class mymatrix<T> explicitly designed to support a 2D data structure. Like vector<T>,
it can grow dynamically in terms of rows and columns. Unlike vector<T>, the use of push_back is not required to add elements.
Instead, a matrix is defined to have a given number of rows and columns, and the resulting elements are initialized to C++’s
natural default value. 