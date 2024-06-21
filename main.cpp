#include <iostream>
#include "mymatrix.h"

using namespace std;

bool test1() {  // test parameterized constructor
   mymatrix<int>M(5,7); // cols bigger
   if (M.size() == 35) {
      return true;
   }
   return false;
}

bool test2() {  // test parameterized constructor
   mymatrix<int>M(1,1); // square & onyl 1
   if (M.size() == 1) {
      return true;
   }
   return false;
}

bool test3() {  // test parameterized constructor
   mymatrix<int>M(10,8); // row bigger
   if (M.size() == 80) {
      return true;
   }
   return false;
}

bool test4() {  // test copy constructor
   mymatrix<int> M1(4,6);
   mymatrix<int> M2(M1);
   if (M2.size() == 24) {
      return true;
   }
   return false;
}

bool test5() {  // test copy constructor
   mymatrix<int> M1(10,10);
   M1(4,4) = 12345;
   mymatrix<int> M2(M1);
   if (M2(4,4) == 12345) {
      return true;
   }
   return false;

}

bool test6() {  // test numrows function
   mymatrix<int> M(3,3);
   if (M.numrows() == 3) {
      return true;
   }
   return false;
}

bool test7() {  // test numcols function
   mymatrix<int> M(4,9);
   if (M.numcols(2) == 9) { // at row 2 there should be 9 cols
      return true;
   }
   return false;
}

bool test8() {  // test growcols function
   mymatrix<int> M; // default
   M.growcols(1, 8);
   if (M.size() == 20) { 
      return true;
   }
   return false;
}

bool test9() {  // test growcols function
   mymatrix<int> M;  
   M.growcols(2,2); // should NOT grow
    if (M.size() == 16) { 
      return true;
   }
   return false;
}

bool test10() {  // test growcols function 
   mymatrix<int> M(2,8);  //rectangle
   M.growcols(1, 10);
   if (M.size() == 18) { 
      return true;
   }
   return false;
}

bool test11() {  // test grow function
   mymatrix<int> M;
   M.grow(5, 8);
   if (M.size() == 40) { 
      return true;
   }
   return false;
}

bool test12() {  // test grow function 
   mymatrix<int> M;
   M.grow(2,2);
   if (M.size() == 16) {  // should NOT grow
      return true;
   }
   return false;
}

bool test13() {  // test grow function 
   mymatrix<int> M(3,3);
   M.grow(4,4);
   if (M.size() == 16) { 
      return true;
   }
   return false;
}

bool test14() {  // test size function & others
   mymatrix<int> M(2,2);
   M.grow(5,5);
   M.at(2,3) = 25;
   mymatrix<int> N(M);
   if (N.size() == 25) {
      return true;
   }
   return false;
}

bool test15() { // test at reference
   mymatrix<int> M; // edge case
   M.at(3,3) = 12345;
   if (M.at(3,3) == 12345) { 
      return true;
   }
   return false;
}

bool test16() { // test operator refeerence
   mymatrix<int>M;
   M(3,3) = -99;
   if (M(3,3) == -99) {
      return true;
   }
   return false;
}

bool test17() {  // test scalar mulitplication
   mymatrix<int> M;
   M(0,0) = 5;
   mymatrix<int> N;
   N = M * 5;
   if ( N.at(0,0) == 25) {
      return true;
   }
   return false;
}

bool test18() {  // test scalar multiplication
   mymatrix<int> M(6,5);
   M.at(5,4) = 10; // edge case
   mymatrix<int> N;
   N = M * 50;
   if (N.at(5,4) == 500) {
      return true;
   }
   return false;
}

bool test19() {  // test matrix multiplication
   mymatrix<int>M1;
   mymatrix<int>M2;
   mymatrix<int>M3;
   
   M1(0,0) = 10;
   M2(0,0) = 10;
   M3 = M1 * M2;
    if (M3.at(0,0) == 100) {
      return true;
   }
   return false;
}

bool test20() {  // test matrix multiplication
   mymatrix<int>M1;
   mymatrix<int>M2;
   mymatrix<int>M3;
   
   M1(3,3) = 5;
   M2(3,3) = 5;
   M3 = M1 * M2;
   if (M3.at(3,3) == 25) {
      return true;
   }
   return false;
}

bool test21() {  // test different data type
   mymatrix<string> M;
   M(2,2) = "testing";
   if (M(2,2) == "testing") {
      return true;
   }
   return false;
}

////// test all exceptions /////

bool exception_test1() { // # size of cols & rows
   try {
      mymatrix<int>M(0,0);
   }
   catch (exception) {
      return true;
   }
   return false;
}

bool exception_test2() {  // size mismatch
   try {
      mymatrix<int>M1(5,5);
      mymatrix<int>M2(6,5);
      mymatrix<int>M3(5,6);
      M1(3,3) = 10;
      M2(3,3) = 10;
      M3 = M1 * M2;
   }
   catch (exception) {
      return true;
   }
   return false;
}

bool exception_test3() { // not rectangle matrix
   try {
      mymatrix<int>M1;
      mymatrix<int>M2;
      mymatrix<int>M3;
      M2.growcols(1,9);
      M3 = M1 * M2;
   }
   catch (exception) {
      return true;
   }
   return false;
}

bool exception_test4() { // numcols
   try {
      mymatrix<int>M;
      M.numcols(-1);
   }
   catch (exception) {
      return true;
   }
   return false;
}

bool exception_test5() { // # of rows & cols
   try {
      mymatrix<int>M;
      M(4,4) = 5;
   }
   catch (exception) {
      return true;
   }
   return false;
}



int main() {
   int passed = 0;
   int failed = 0;

   (test1()) ? passed++ : failed++;
   (test2()) ? passed++ : failed++;
   (test3()) ? passed++ : failed++;
   (test4()) ? passed++ : failed++;
   (test5()) ? passed++ : failed++;
   (test6()) ? passed++ : failed++;
   (test7()) ? passed++ : failed++;
   (test8()) ? passed++ : failed++;
   (test9()) ? passed++ : failed++;
   (test10()) ? passed++ : failed++;
   (test11()) ? passed++ : failed++;
   (test12()) ? passed++ : failed++;
   (test13()) ? passed++ : failed++;
   (test14()) ? passed++ : failed++;
   (test15()) ? passed++ : failed++;
   (test16()) ? passed++ : failed++;
   (test17()) ? passed++ : failed++;
   (test18()) ? passed++ : failed++;
   (test19()) ? passed++ : failed++;
   (test20()) ? passed++ : failed++;
   (test21()) ? passed++ : failed++;
   (exception_test1()) ? passed++ : failed++;
   (exception_test2()) ? passed++ : failed++;  
   (exception_test3()) ? passed++ : failed++; 
   (exception_test4()) ? passed++ : failed++; 
   (exception_test5()) ? passed++ : failed++;  

   cout << "Tests passed: " << passed << endl;
   cout << "Tests failed: " << failed << endl;

   return 0;
}