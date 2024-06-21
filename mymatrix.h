/*mymatrix.h*/

/// My Matrix
/// System: VSCode on MacOS
/// Author: Nuha Abougoash 
/// Assignment details and starter code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

template<typename T>
class mymatrix {

  private:
    struct ROW {
      T*  Cols;     // dynamic array of column elements
      int NumCols;  // total # of columns (0..NumCols-1)
    };

    ROW* Rows;     // dynamic array of ROWs
    int  NumRows;  // total # of rows (0..NumRows-1) 

  public:

    // default constructor
    // Called automatically by C++ to construct a 4x4 matrix. 
    mymatrix() {
      Rows = new ROW[4]; // an arrxay with 4 ROW structs:
      NumRows = 4;

      // initialize each row to have 4 columns:
      for (int r = 0; r < NumRows; ++r) {
        Rows[r].Cols = new T[4];  // an array with 4 elements of type T:
        Rows[r].NumCols = 4;

        // initialize the elements to their default value:
        for (int c = 0; c < Rows[r].NumCols; ++c) {
          Rows[r].Cols[c] = T();  // default value for type T:
        }
      }           
    }

    // parameterized constructor:
    // Called automatically by C++ to construct a matrix with R rows, where each row has C columns.
    mymatrix(int R, int C) {

      if (R < 1)
        throw invalid_argument("mymatrix::constructor: # of rows");
      if (C < 1)
        throw invalid_argument("mymatrix::constructor: # of cols");

      Rows = new ROW[R]; //declare new instance of struct
      NumRows = R; 

      for (int r = 0; r < NumRows; r++) { // loop thru each row
        Rows[r].Cols = new T[C]; 
        Rows[r].NumCols = C; 
 
        for (int c = 0; c < Rows[r].NumCols; c++) { 
          Rows[r].Cols[c] = T(); 
        } 
      }           
    }

    // copy constructor:
    // Called automatically by C++ to construct a matrix that contains a copy of an existing matrix.
    mymatrix(const mymatrix<T>& other) {
      NumRows = other.NumRows;
      Rows = new ROW[NumRows];

      for (int r = 0; r < NumRows; r++) { // loop thru each row
        Rows[r].NumCols = other.Rows[r].NumCols;
        Rows[r].Cols = new T[Rows[r].NumCols];

        for (int c = 0; c < Rows[r].NumCols; c++) {
          Rows[r].Cols[c] = other.Rows[r].Cols[c];
        }
      }
    }

    // Returns the # of rows in the matrix.
    int numrows() const {
      return NumRows;
    }
    
    // Returns the # of columns in row r.
    int numcols(int r) const {
      if (r < 0 || r >= NumRows)
        throw invalid_argument("mymatrix::numcols: row");
      
      int num_cols = 0;
      ROW &a_row = Rows[r];
      //T *a_cols = new T[a_ro]
      // loop thru struct of rows to count num of cols
      for ( int i = 0; i < a_row.NumCols; i++){
        num_cols++;
      }
      return num_cols;
    }
    
    // Grows the # of columns in row r to at least C. 
    void growcols(int r, int C) {
      // check if numbers are valid
      if (r < 0 || r >= NumRows)
          throw invalid_argument("mymatrix::growcols: row");
      
      if (C < 1)
        throw invalid_argument("mymatrix::growcols: columns");

      int currNumCols = numcols(r);

      if (currNumCols < C) {
        ROW& aRow = Rows[r]; 
        T* newCols = new T[C+aRow.NumCols]; // create new array of size "C + aRow.NumCols"

        // copy the value of existing cols into new array
        for (int i = 0; i < aRow.NumCols; ++i) {
            newCols[i] = aRow.Cols[i];
        }

        for (int j = aRow.NumCols; j < C; ++j) {
            newCols[j] = T(); // new cols are intialized to defualt value 
        }

        delete[] aRow.Cols; // delete old array
        aRow.Cols = newCols;
        aRow.NumCols = C;
      }
    }

    // Grows the size of the matrix so that it contains at least R rows, and every row contains at least C columns.
    void grow(int R, int C) {
      // check if rows and col are positive values
      if (R < 1)
        throw invalid_argument("mymatrix::grow: # of rows");
      if (C < 1)
        throw invalid_argument("mymatrix::grow: # of cols");


      if (R > NumRows) {
        ROW* newRows = new ROW[R]; // create new array with specified num of rows

        // copy existing array into new array
        for (int i = 0; i < NumRows; i++) {
          newRows[i] = Rows[i];
        }

        for (int i = NumRows; i < R; i++) {
          newRows[i].Cols = new T[C];
          for (int j = 0; j < C; j++) {
            newRows[i].Cols[j] = T(); 
          }
          newRows[i].NumCols = C;
        }

        delete[] Rows;
        Rows = newRows;
        NumRows = R;
      }

      for (int i = 0; i < NumRows; i++) {
       // if inputted C is greater than current num of cols 
       if (C > Rows[i].NumCols) {
          T* newCols = new T[C]; // create new array of cols with specified number

          // copy existing elements into new array
          for (int j = 0; j < Rows[i].NumCols; j++) {
            newCols[j] = Rows[i].Cols[j];
          }

          for (int j = Rows[i].NumCols; j < C; j++) {
            newCols[j] = T();
          }

          delete[] Rows[i].Cols;
          Rows[i].Cols = newCols;
          Rows[i].NumCols = C;
        }
      }
    }

    // Returns the total # of elements in the matrix.
    int size() const {
      int count = 0;
        for (int r = 0; r < NumRows; ++r) {
          count += Rows[r].NumCols;
        }
        return count;
    }

    // at
    //Returns a reference to the element at location (r, c)
    T& at(int r, int c) const {
      if (r < 0 || r >= NumRows)
        throw invalid_argument("mymatrix::at: row");
      if (c < 0 || c >= Rows[r].NumCols)
        throw invalid_argument("mymatrix::at: col");

      return Rows[r].Cols[c];

    }

    // Returns a reference to the element at location (r, c)
    T& operator()(int r, int c) const {
      if (r < 0 || r >= NumRows)
        throw invalid_argument("mymatrix::(): row");
      if (c < 0 || c >= Rows[r].NumCols)
        throw invalid_argument("mymatrix::(): col");
      
      return Rows[r].Cols[c];

    }

    // scalar multiplication
    // Multiplies every element of this matrix by the given scalar value, producing a new matrix that is returned.
    // Example:  M2 = M1 * 2;
    mymatrix<T> operator*(T scalar) {
      mymatrix<T> result;

      // intialize result matrix with same cols and rows as input matrix
      result.NumRows = NumRows;
      result.Rows = new ROW[NumRows];

      for (int r = 0; r < NumRows; r++) {
        result.Rows[r].NumCols = Rows[r].NumCols;
        result.Rows[r].Cols = new T[Rows[r].NumCols];

        for (int c = 0; c < Rows[r].NumCols; c++) {
          result.Rows[r].Cols[c] = Rows[r].Cols[c] * scalar; 
        }
      }

      // return new matrix
      return result;
    }

    // Performs matrix multiplication
    // Example:  M3 = M1 * M2;
    mymatrix<T> operator*(const mymatrix<T>& other) {
      mymatrix<T> result;

      // check if both matrices are rectangle
      for (int i = 0; i < NumRows; i++) {
        if (numcols(i) != numcols(0)) 
          throw runtime_error("mymatrix::*: this not rectangular");
      }
      for (int i = 0; i < other.NumRows; i++) {
        if (other.numcols(i) != other.numcols(0))
          throw runtime_error("mymatrix::*: other not rectangular");
        
      }
      if (NumRows <= 0 || Rows[0].NumCols <= 0 || other.NumRows <= 0 || other.Rows[0].NumCols <= 0 || Rows[0].NumCols != other.NumRows)
        throw runtime_error("mymatrix::*: size mismatch");

      // initialize with correct size
      result.NumRows = NumRows;
      result.Rows = new ROW[result.NumRows];
      result.Rows[0].NumCols = other.Rows[0].NumCols;

      // iterate over every element in result matrix and change valaue based on the corresponding element
      for (int r = 0; r < result.NumRows; r++) {

          result.Rows[r].NumCols = result.Rows[0].NumCols;
          result.Rows[r].Cols = new T[result.Rows[r].NumCols];

          for (int c = 0; c < result.Rows[r].NumCols; c++) {
              result.Rows[r].Cols[c] = 0;

              for (int i = 0; i < Rows[r].NumCols; i++) {
                  result.Rows[r].Cols[c] += Rows[r].Cols[i] * other.Rows[i].Cols[c];
              }
          }
      }
      return result;
    }

    // _output
    // Outputs the contents of the matrix; for debugging purposes.
    void _output() {
      for (int r = 0; r < this->NumRows; ++r) {
        for (int c = 0; c < this->Rows[r].NumCols; ++c) {
          cout << this->Rows[r].Cols[c] << " ";
        }
        cout << endl;
      }
    }

};