
//-------------------------------------------------------------------

// instantiation.cpp

// file to link the templated .cpp files (doesn't work without it)

//-------------------------------------------------------------------

#include "Students.cpp"

#include "Lab5.cpp"

#include "Queue.cpp"
 

template class Queue<int>;

template class QueNode<int>;

 

template class Queue<Students*>;

template class QueNode<Students*>;
