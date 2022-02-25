# Assignment 1
**Due by 11:59pm on Monday, 10/15/2018**

**Demo due by 11:59pm on Monday 10/29/2018**

This assignment is intended to give you practice writing C code (e.g. allocating and freeing memory, working with pointers, etc.) and also to have you start working with one of the most fundamental data structures we'll see in this course: the dynamic array.  There are several parts to the assignment, each described below.

For this assignment, you are provided with some starter code that defines the structures you'll be working with and prototypes the functions you'll be writing.  *It's important that you don't modify the function prototypes.*  To help grade your assignment, we will use a set of unit tests that assume these functions exist and have the same prototypes that are defined in the starter code.  If you change the prototypes, it will cause the unit tests to break, and your grade for the assignment will likely suffer.  Feel free, however, to write any additional functions you need to accomplish the tasks described below.

Within the provided starter code is a dynamic array implementation in `dynarray.h` and `dynarray.c`.  You should use this implementation to provide the dynamic array functionality needed by several of the functions you'll write for the assignment.  We will review this implementation in lecture.

Importantly, your work for this assignment will be limited to the file `students.c`, where you will implement the functions described below.  You should not modify any other file in this repository.  In addition to the descriptions below, there is thorough documentation in `students.c` describing how each function you'll write should behave.

## 1. Implement a function to allocate and initialize a single `struct student`

In `create_student()`, implement a function that initializes the values of a single newly-allocated student structure.  In particular, this function will be passed values for `name`, `id`, and `gpa`.  You should allocate memory on the heap to store a `struct student`.  You should also allocate memory on the heap to store a copy of `name` and copy `name` into that memory.  Then, you should assign the copy of `name`, `id`, and `gpa` to the corresponding fields in the student structure you allocated and return a pointer to that structure.

## 2. Implement a function to free the memory held by a single `struct student`

In `free_student()`, implement a function that frees any memory that was allocated by `create_student()` for a single student.  This function will be passed a pointer to the student whose held memory is to be freed.  You must free any memory allocated for the fields of that student structure as well as the memory allocated for the structure itself.  Importantly, this function must free all relevant memory and cannot result in a memory leak.

## 3. Implement a function to create a dynamic array of `struct student`s

In `create_student_array()`, implement a function to allocate and initialize a dynamic array (i.e. `struct dynarray`), store a collection of students in that newly-created dynamic array, and then return a pointer to the array.  This function will be provided with arrays specifying the names, IDs, and GPAs of the students to be stored in the array.  You should use your `create_student()` function to allocate and initialize a student structure for each set of provided values and store each allocated student structure in the new dynamic array.  In the returned array, the `i`th student should have the `i`th name, the `i`th ID, and the `i`th GPA.  Make sure to use the provided dynamic array functions (e.g. `dynarray_create()` and `dynarray_insert()`) to allocate and modify the dynamic array.

## 4. Implement a function to free the memory in a dynamic array of `struct student`s

In `free_student_array()`, implement a function that frees all of the memory allocated by `create_student_array()`.  In particular, you should use your `free_student()` function to free the memory held by each individual student in the array, and then you should free the memory held by the array itself.  Again, make sure to use the provided dynamic array functions to access elements in the dynamic array and to free the array itself.  Importantly, this function must free *all* of the memory associated with a dynamic array of student structures.  In other words, it may not result in memory leaks.

## 5. Implement a function to print a dynamic array of `struct student`s

In `print_students()`, implement a function that prints the name, ID, and GPA of each student in a dynamic array, one student per line.  As before, make sure to use the provided dynamic array functions to access elements in the dynamic array.

## 6. Implement functions to find the students in an array with the lowest and highest GPA

In `find_min_gpa()` and `find_max_gpa()`, implement functions to respectively find the student with the lowest GPA and the one with the highest GPA in an array.  These functions should return a pointer to these students.  Importantly, you should not make a copy of the student returned by these functions.  Instead, you should simply return the pointer to a student structure that's already stored in the array.

## 7. Implement a function to sort the students in a dynamic array by descending GPA

In `sort_by_gpa()`, implement a function to order the students in a dynamic array by descending GPA (i.e. with the highest GPAs at the beginning of the array).  You may use any sorting algorithm you like.  This function should abide by the following constraints:

  * It should sort the students *in place*.  In other words, you should not allocate memory for a new array in this function.
  * It should not use built-in functions like `qsort()`.  In other words, you have to implement the sorting yourself.  You may implement any in-place sorting algorithm you like.  Some possibilities are selection sort, insertion sort, bubble sort, and quicksort.

As with all of the other functions that work with dynamic arrays, make sure to use the provided dynamic array functions (e.g. `dynarray_get()`, `dynarray_set()`, etc.) to access and modify the contents of the dynamic array.

## A note on using void pointers

The dynamic array implementation in this assignment uses void pointers (i.e. `void*`) to store data.  You may not be familiar with the way void pointers work.  Simply put, void pointers are a mechanism that can be used to store *any* pointer type.  In other words, you can think of a void pointer as a generic pointer, capable of pointing to values of any type.  They are often used in C/C++ data structure implementations to allow those data structures to store data of many different types without needing to change the underlying source code of the data structure for each type.

In order to use a void pointer (e.g. one returned by a function), you'll likely want to cast or assign it back to its original type.  For example, below is some code that uses a void pointer to point to an integer and then prints that integer via the void pointer.  Note that we have to cast the void pointer as an integer pointer in order to dereference it and print the underlying integer value.
```C
int n = 16;
void* vptr = &n;  /* storing int* value in void* variable */
printf("%d\n", *(int*)vptr);
```
Alternatively, we could have assigned the address contained in `vptr` back into a variable of type `int*`, from which we could then print the underlying integer value:
```C
int* iptr = vptr;
printf("%d\n", *iptr);
```

Again, void pointers can hold a pointer to a value of any type.  For example, below is code that uses a void pointer to store the pointer to a `struct student` returned by `create_student()`.  This pointer is then assigned back into a variable of type `struct student*` in order to access the underlying values in the student structure.
```C
void* vptr = create_student(...);
struct student* sptr = vptr;
printf("%s\n", sptr->name);
```

Many of the functions from the dynamic array implementation you'll use in this assignment either take `void*` arguments or return `void*` values.  In general, it will work fine for you to pass `struct student*` values into `void*` arguments.  When working with `void*` return values, make sure to either cast back to `struct student*` or to assign to a variable of type `struct student*` if you want to access the underlying fields of the student structure.

## Testing your work

In addition to the dynamic array implementation and the skeleton code in `students.h` and `students.c`, you are also provided with some application code in `test.c` to help verify that your functions are behaving the way you want them to.  In particular, the code in `test.c` calls the functions from `students.c`, passing them appropriate arguments, and then prints the results.  You can use the provided `Makefile` to compile all of the code in the project together, and then you can run the testing code as follows:
```
make
./test
```

In order to verify that your memory freeing functions work correctly, it will be helpful to run the testing application through `valgrind`.

## Submission

As always, we'll be using GitHub Classroom for this assignment, and you will submit your assignment via GitHub. Just make sure your completed files are committed and pushed by the assignment's deadline to the master branch of the GitHub repo that was created for you by GitHub Classroom. A good way to check whether your files are safely submitted is to look at the master branch of your assignment repo on the github.com website (i.e. https://github.com/OSU-CS261-F18/assignment-1-YourGitHubUsername/). If your changes show up there, you can consider your files submitted.

## Grading criteria

Your program **MUST** compile and run on `flip.engr.oregonstate.edu`, so make sure you have tested your work there before you make your final submission, since a program that compiles and runs in one environment may not compile and run in another.  **Assignments that do not compile on flip will receive a grade of 0.**  If you do not have an ENGR account, you can create one at https://teach.engr.oregonstate.edu/.

The assignment is worth 100 total points, broken down as follows:

  * 10 points: `create_student()` allocates and initializes a `struct student` as described above
  * 10 points: `free_student()` frees the memory held by a `struct student` as described above (no memory leaks!)
  * 10 points: `create_student_array()` allocates and initializes a dynamic array of `struct student`s as described above
  * 10 points: `free_student_array()` frees the memory held by a dynamic array of `struct student`s as described above (no memory leaks!)
  * 10 points: `print_students()` prints a dynamic array of students as described above
  * 10 points: `find_min_gpa()` finds the student with the lowest GPA as described above
  * 10 points: `find_max_gpa()` finds the student with the highest GPA as described above
  * 20 points: `sort_by_gpa()` sorts a dynamic array of students by descending GPA, in place, as described above
  * 10 points: you can provide a satisfactory explanation of how your code works during your grading demo with the TA

Note that we will only consider changes to `students.c` when grading your work.  Changes to other files will be ignored.
