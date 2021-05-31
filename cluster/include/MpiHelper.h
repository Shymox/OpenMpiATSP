#pragma once
#include <mpi.h>
#include <string>
#include "List.h"
#include "Array.h"
#include <stddef.h>
#include "Matrix.h"

#define WORKTAG 1  
#define DIETAG 2
#define NUM_WORK_REQS 200

class MpiHelper
{
private:
	Matrix* matrix;

public:
    void master(char argv[]);

    void slave();

    void master2();

    void slave2();

    void load(std::string name);

    int **alloc_2d_int(int rows, int cols);

    MpiHelper(int argc, char *argv[]);

    ~MpiHelper();

};