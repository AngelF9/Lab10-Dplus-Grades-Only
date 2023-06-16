# Lab 10: D+ Grades Only

In this lab, you will learn how to:
- use 2-dimensional arrays
- call functions from precompiled code

For this assignment, you will write a series of functions to implement a gradebook program, then test them using the GoogleTest framework.

## File structure

* `Makefile` - Configuration for `make`.
* `grades.cpp` - Your code goes here.
* `grades_test.cpp` - Your tests go here.
* `grades.h` - Header file for `grades.cpp`, already written for you.
* `main.cpp` - Contains main function if you want to run the functions in `grades.cpp`.
* `googletest/` - Contains code for the GoogleTest framework.
* `lib/` - Contains library files you may use.
    * `statistics.h` - Header file, already included for you in the starter code for `grades.cpp`
    * `statistics.o` - Already compiled implementation of those functions

**Do not change any files other than `grades.cpp` and `grades_test.cpp`!**

## Make commands

You have the same `make` commands as last time (format, test, build, all, clean). **Don't use g++**.

## Program specifications

In Lab 9, you wrote a small library with some helpful array functions.

Today, you will put them to use by writing a program that calculates students' grades in `grades.cpp`.

For Lab 10, you have been provided with a correct implementation of the Lab 9 functions. They are defined in `lib/statistics.h`.

You may freely call the functions in `lib/statistics.h`. Do not try to copy anything over from Lab 9 - everything has been taken care of for you.

**Important note:** For this lab, part of your grade is based on whether you are using functions effectively.
If there is a library function or another function that you already wrote that does a calculation you need, your code should call that function.
Reimplementing code that does those calculations is a waste of your time and will make you lose points.

As usual, you should read the specification below, then write test cases and implement the functions.

These are the 3 functions you will write (defined in grades.h):

* `int student_average(const int grades[MAX_S][MAX_HW], int n_students, int n_hws, int student_id);`
* `int top_score_student(const int grades[MAX_S][MAX_HW], int n_students, int n_hws);`
* `void hw_stats(const int grades[MAX_S][MAX_HW], int n_students, int n_hws, int hw_id, int& min, int& max, int& med, int& avg);`

The `MAX_S` and `MAX_HW` global constants are defined in `grades.h` and explained in the next section. You are allowed to use them.

### Gradebook specification

For this lab, a gradebook is represented using a 2-dimensional array:

* Each row corresponds to a student and each column corresponds to a homework assignment.
* Student and homework IDs are numbered starting from 0 and going up in order.
* `MAX_S` and `MAX_HW` are constants that represent the maximum size of the gradebook. `MAX_S` is the maximum number of students and `MAX_HWS` is the maximum number of homework assignments. Not all the rows and columns in a gradebook will contain data.
* The `n_students` and `n_hws` arguments to these functions will tell you how many different students and homework assignments actually exist.
* A value for `n_students` is valid if it is greater than zero and less than or equal to `MAX_S`. Similarly for `n_hws` with `MAX_HW`.
* A value for student ID is valid if it is greater than or equal to zero and less than the number of students (`n_students`). Similarly for homework IDs.
* The value of `grades[i][j]` corresponds to the score the ith student got on the jth homework

### Example gradebook

Suppose there are 3 students and 4 homework assignments. The students got these scores (in order of HW assignment):

* Student 0 got 90, 80, 95, 85
* Student 1 got 70, 100, 80, 80
* Student 2 got 0, 0, 0, 0 because they didn't turn in their homework :(

This would be represented with the following array:

```c++
int grades[MAX_S][MAX_HW] = { {90, 80, 95, 85},
                              {80, 100, 70, 80},
                              {0, 0, 0, 0} };
```

Homework assignments are numbered starting from 0.

* The score that Student 0 got on HW 0 is the value of `grades[0][0]` which is 90.
* The score that Student 1 got on HW 2 is the value of `grades[1][2]`, which is 70.
* The score that Student 2 got on HW 3 is the value of `grades[2][3]`, which is 0.

### student_average()

`int student_average(const int grades[MAX_S][MAX_HW], int n_students, int n_hws, int student_id)`

**Input:** A gradebook, the number of students and homeworks, and the id of the student to look up.

**Function behavior:** If any of the values for `n_students`, `n_hws`, or `student_id` are not valid, return -1. Otherwise return the average score the student with the ID number in `student_id` got on the first `n_hws` homework assignments, rounding down to an integer if necessary. 
Your function should not modify any of the values in `grades` or print anything out.

**Examples:** Using the gradebook in the example above, we call the function with `3` as the value for `n_students` and `4` as the value of `n_hws` since that's how many students and homeworks there are. Then:

* `student_average(grades, 3, 4, 0)` returns 87 because Student 0's scores on the 4 assignments are 90, 80, 95, and 85. 87 is the average of those rounded down.
* `student_average(grades, 3, 4, 1)` returns 82 because that's the average (rounded down) of Student 1's grades.
* `student_average(grades, 3, 4, 2)` returns 0 because the average of Student 2's grades is 0.
* `student_average(grades, 3, 4, 3)` returns -1 because the student id isn't valid

If we used different values for `n_students` and `n_hws`:

* `student_average(grades, 3, 2, 0)` returns 85 since this is Student 0's average scores on the first 2 assignments and they scored 90 and 80 on those assignments.
* `student_average(grades, -1, 4, 0)` returns -1 since the number of students is invalid


### top_score_student()

`int top_score_student(const int grades[MAX_S][MAX_HW], int n_students, int n_hws)`

**Input:** A gradebook and the number of students and homeworks

**Function behavior:** If at least one of the values for `n_students` or `n_hws` is not valid, return -1. Otherwise return the ID of the student out of the first `n_students` number of students that has the highest average score on the first `n_hws` homework assignments. If two or more students are tied for highest average score, your function can return the ID of any student with the highest average.
Your function should not modify any of the values in `grades` or print anything out.

**Example:** Using the gradebook in the example above, we call the function with `3` as the value for `n_students` and `4` as the value of `n_hws` since that's how many students and homeworks there are. Then `top_score_student(grades, 3, 4)` returns 0 because Student 0 had the highest average on the 4 assignments.

### hw_stats()

`void hw_stats(const int grades[MAX_S][MAX_HW], int n_students, int n_hws, int hw_id, int& min, int& max, int& med, int& avg)`

**Input:** A gradebook, the number of students and homeworks, a homework ID, and some reference variables to store the results in

**Function behavior:** If any of the values for `n_students`, `n_hws`, or `hw_id` are not valid, return immediately without doing anything else. Otherwise, when this function returns, the values of `min`, `max`, `med`, and `avg` should be set to the minimum, maximum, median, and average scores of the `n_students` students on the homework with the ID `hw_id`.
Your function should not modify any of the values in `grades` or print anything out.

**Example:** Using the gradebook in the example above, Student 0 got a score of 80 on HW 1. Student 1 got a 100 and Student 2 got a 0.

We can call `hw_stats(grades, 3, 4, 1, a, b, c, d);` to get the statistics for HW 1. After the function returns, the values of the following variables will be changed:

* The value of `a` will be 0 because 0 was the minimum score on HW 1
* The value of `b` will be 100 because 100 was the maximum score on HW 1
* The value of `c` will be 80 because 80 was the median score on HW 1
* The value of `d` will be 60 because 60 was the average score on HW 1

### Write test case

For this part, you only need to write one test case, but make it a good one!

The test case file looks like this:

```c++
class GradesTest : public ::testing::Test {
  protected:
    int grades[MAX_S][MAX_HW] = {0};
    int n_students = 0;
    int n_hws = 0;
    int expected_averages[MAX_S] = {0};
    int expected_top_students[MAX_S] = {0};
    int expected_hw_stats[MAX_HW][4] = {0};
};
```

Fill in these values and don't change anything else in the file:

* `grades` is a 2D array of the gradebook.
* `n_students` and `n_hws` are how many students and hws there are.
* For `expected_averages`, fill in an array of values corresponding to each student's average score on those assignments. The 0th element of the array should have Student 0's average score, and so on.
* For `expected_top_students`, fill in an array of all the student IDs, in ascending order, that are tied for highest average score because any of these numbers is an allowable answer. If there's only one student with the highest score, this should be an array with one thing in it.
* For `expected_hw_stats`, fill in a 2D array. Each row of the array should be an array with the minimum, maximum, median, and average score for that HW.

### Example test case

Using the same gradebook as the example in the function specifications, plus an additional Student (ID number 3) that got 87 on every assignment:

The gradebook would be represented by this array so we set the value of `grades` equal to it in the test case:

```c++ 
{ {90, 80, 95, 85},
  {80, 100, 70, 80},
  {0, 0, 0, 0},
  {87, 87, 87, 87} }
```

* `n_students` is 4 and `n_hws` is 4
* The average score for Student 0 was 87, the average for Student 1 was 82, the average for Student 2 was 0, and the average for Student 3 was 87. So the value in the test case for `expected_averages` is an array with those numbers in that order.
* Students 0 and 3 are tied for the highest average, so the value for `expected_top_students` is an array with the numbers 0 and 3 in that order. We have to do this when writing the test cases since the function spec says that the `top_score_student()` function could return either of those values.
* Now we have to fill out `expected_hw_stats`. An easy way to do it is to think about each assignment separately:
    * For HW 0, the student scores were 90, 80, 0, and 87. So the minimum is 0, maximum is 90, median is 83, and average is 64. If we put those numbers in that order in a 4-element array, we would get `{0, 90, 83, 64}`.
    * For HW 1, the scores were 80, 100, 0, 87. Minimum is 0, maximum is 100, median is 83, average is 66. This corresponds to this array: `{0, 100, 83, 66}`
    * For HW 2, the scores were 95, 70, 0, 87. Minimum is 0, maximum is 95, median is 78, average is 63. The array is `{0, 95, 78, 63}`
    * For HW 3, the scores were 85, 80, 0, 87. Minimum is 0, maximum is 87, median is 82, average is 63. The array is `{0, 87, 82, 63}`
    * Now use those arrays, in that order, as rows in the 2D array for `expected_hw_stats`

The resulting test case is below:

```c++
int grades[MAX_S][MAX_HW] = { {90, 80, 95, 85},
                               {80, 100, 70, 80},
                               {0, 0, 0, 0},
                               {87, 87, 87, 87} };
int n_students = 4;
int n_hws = 4;
int expected_averages[MAX_S] = {87, 82, 0, 87};
int expected_top_students[MAX_S] = {0, 3};
int expected_hw_stats[MAX_HW][4] = { {0, 90, 83, 64},
                                     {0, 100, 83, 66},
                                     {0, 95, 78, 63},
                                     {0, 87, 82, 63} };
```

### Implement the functions

You are allowed to use the library functions defined in `lib/statistics.h` and you are always allowed to write extra helper functions of your own.

You are **NOT** allowed to use any other external library functions.

Here are some hints for this part:

* You really should use the library functions. The header file has already been included in the starter code so you can just call them like normal. You may not need to use every library function, but if you complete this assignment without calling a single one of those functions, you're probably doing something wrong. Remember, part of your grade is based on using functions effectively.
* In a 2D int array, you can easily get an entire row of the array (which is a 1D array) by saying `a[i]` to get the ith row of array `a`. You can pass this to a function as an argument: `function_name(a[i])` calls a function named `function_name` with the ith row of `a` as an argument.
* Unlike rows, it's not so easy to get a column of a 2D array. There's no shortcut. You'll have to figure out how to do it.

### Running your code

Running `make test` should be enough to test your program, but if you want to run an interactive version of your program, run `make build` and then run `./gradebook`.
