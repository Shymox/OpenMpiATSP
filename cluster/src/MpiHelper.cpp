#include "MpiHelper.h"
#include <iostream>
#include <unistd.h>
#include <curses.h>
#include <fstream>
#include <stdio.h>
#include <limits.h>
#include <cmath>

#define WORKTAG 1  
#define DIETAG 2
#define NUM_WORK_REQS 200


void MpiHelper::slave()
{
    int ntasks;
    int myrank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    int** cities;
    int size;
    int optimum=1;
    MPI_Status status;
    //odbiór rozmiaru macierzy
    MPI_Bcast(&size,1,MPI_INT,0,MPI_COMM_WORLD);
    //odbiór macierzy
    cities = alloc_2d_int(size,size);
    MPI_Bcast(&(cities[0][0]),size*size,MPI_INT,0,MPI_COMM_WORLD);

    int answers[size];
    answers[0]=INT_MAX;
    if(ntasks-1<size)
    {
        this->matrix = new Matrix();
        this->matrix->init(size);
        this->matrix->setOptimum(optimum);
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<size;j++)
            {
                matrix->matrix[i][j]=cities[i][j];
            }
        }
        int j=(myrank-1)*(size-1)/(ntasks-1);
        if(myrank==ntasks-1)
        {
            while(j<size-1)
            {
                this->matrix->reset();
                this->matrix->bruteForce(j);
                if(answers[0]>this->matrix->answer())
                {
                    answers[0]=this->matrix->answer();
                    int* temp = this->matrix->returnSequence();
                    for(int i=0;i<size;i++)
                    {
                        answers[i+1]=temp[i];
                    }
                }
                j++;
            }
        }
        else
        {
            while(j<myrank*(size-1)/(ntasks-1) && j<size)
            {
                this->matrix->reset();
                this->matrix->bruteForce(j);
                if(answers[0]>this->matrix->answer())
                {
                    answers[0]=this->matrix->answer();
                    int* temp = this->matrix->returnSequence();
                    for(int i=0;i<size;i++)
                    {
                        answers[i+1]=temp[i];
                    }
                }
                j++;
            }
        }
    }
    else if(myrank<size)
    {
        this->matrix = new Matrix();
        this->matrix->init(size);
        this->matrix->setOptimum(optimum);
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<size;j++)
            {
                matrix->matrix[i][j]=cities[i][j];
            }
        }

        this->matrix->bruteForce(myrank-1);
        if(answers[0]>this->matrix->answer())
        {
            answers[0]=this->matrix->answer();
            int* temp = this->matrix->returnSequence();
            for(int i=0;i<size;i++)
            {
                answers[i+1]=temp[i];
            }
        }

    }
    else
    {
        for(int i=0;i<size;i++)
            {
                answers[i+1]=0;
            }
    }
    MPI_Send(&answers,size,MPI_INT,0,15,MPI_COMM_WORLD);
}

void MpiHelper::master(char argv[])
{
    int ntasks;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    std::string b=argv;
    this->matrix = new Matrix();
	this->load(b);
    int size = this->matrix->returnSize();
    int** cities; 
    cities = alloc_2d_int(size,size);
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            cities[i][j]=matrix->matrix[i][j];
        }
    }

    int optimal[size];
    optimal[0]=INT_MAX;
    int a[size];

  //wiadomość z rozmiarem macierzy
    MPI_Bcast(&size,1,MPI_INT,0,MPI_COMM_WORLD);
  //wiadomość z macierzą
    MPI_Bcast(&(cities[0][0]),size*size,MPI_INT,0,MPI_COMM_WORLD);
    free(cities);
    for(int i = 1;i<ntasks;i++)
    {
        MPI_Recv(&a,size,MPI_INT,i,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
        if(a[0]<optimal[0])
        {
            for(int j=0;j<size;j++)
            {
                optimal[j]=a[j];
            }
        }
    }
    std::cout<<optimal[0]<<" 0";

    for(int i=1; i<size;i++)
    {
        std::cout<<" "<<optimal[i];
    }
}

void MpiHelper::load(std::string name)
{	
	size_t size;
	size_t number;
	std::fstream file;
	file.open(name, std::ios::in | std::ios::out);
	if (file.good() == true)
	{
//		std::cout << "Uzyskano dostep do pliku!" << std::endl;
		std::string data;
		getline(file, data);
		getline(file, data);
		try 
		{
			size = static_cast<size_t>(std::stoi(data));
			matrix->init(size);
		}
		catch (std::exception)
		{
			std::cerr << "Blad odczytu: std::exception 2" << '\n';
		}
		for (int i = 0; i < size; i++)
		{
			try
			{
				getline(file, data);
				size_t pos = data.find(' ');
				size_t initialPos = 0;
				int count = 0;
				while (count<size)
				{
					if (initialPos!=pos)
					{
						this->matrix->push(static_cast<int>(std::stoi(data.substr(initialPos, pos - initialPos))), i, count);
						count++;
					}
					initialPos = pos + 1;
					pos = data.find(' ', initialPos);
				}

			}
			catch (std::exception)
			{
				std::cerr << "Blad odczytu: std::exception "<<i<< '\n';
				_Exit(0);
			}
		}
		getline(file, data);
		try
		{
			this->matrix->setOptimum(static_cast<long>(std::stoi(data)));
		}
		catch (std::exception)
		{
			std::cerr << "Blad odczytu: std::exception 2" << '\n';
			_Exit(0);
		}

		file.close();
	}
	else
	{
	std::cerr << "Dostep do pliku zostal zabroniony!" << std::endl;
	_Exit(0);
	}
}

int ** MpiHelper::alloc_2d_int(int rows, int cols) {
    int *data = (int *)malloc(rows*cols*sizeof(int));
    int **array= (int **)malloc(rows*sizeof(int*));
    for (int i=0; i<rows; i++)
        array[i] = &(data[cols*i]);

    return array;
}

MpiHelper::MpiHelper(int argc, char *argv[])
{
    int myrank;

    if(argc>=1)
    {
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    if (myrank==0)
    {
        master(argv[1]);
    } else {
        slave();
    }
    MPI_Finalize();
    }
}

MpiHelper::~MpiHelper()
{

}

void MpiHelper::slave2()
{
    double result;
    int work;
    MPI_Status status;

    for (;;) 
    {
        MPI_Recv(&work, 1 , MPI_INT, 0 , MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        if(status.MPI_TAG == DIETAG) 
        {
            return;
        }
        sleep(6);
        result = 6.0;

        MPI_Send(&result, 1, MPI_DOUBLE_INT, 0,0,MPI_COMM_WORLD);
    }
}

void MpiHelper::master2()
{
    int ntasks, rank, work;
    double      result;
    MPI_Status  status;

    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

    work = NUM_WORK_REQS; /* liczba zadań */

    for (rank = 1; rank < ntasks; ++rank)
    {
        MPI_Send(&work,     /* bufor */
            1,                  /* wyślij 1 */
            MPI_INT,            /* int */
            rank,               /* do tego odbiorcy */
            WORKTAG,            /* tag - zadanie */
            MPI_COMM_WORLD);
        work--;
    }

    while (work > 0) {

        MPI_Recv(&result,   /* bufor na komunikat */
            1,                  /* odbierz 1 */
            MPI_DOUBLE,         /* double */
            MPI_ANY_SOURCE,     /* od kogokolwiek */
            MPI_ANY_TAG,        /* jakikolwiek typ */
            MPI_COMM_WORLD,
            &status);           /* info od kogo, jaki typ */

        MPI_Send(&work, 1, MPI_INT, status.MPI_SOURCE, WORKTAG, MPI_COMM_WORLD);
        work--;
    }

    // koniec zadań - zbierz ostatnie wyniki
    for (rank = 1; rank < ntasks; ++rank)
    {
        MPI_Recv(&result, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    }

    // zakończ slave'y
    for (rank = 1; rank < ntasks; ++rank)
    {
        MPI_Send(0, 0, MPI_INT, rank, DIETAG, MPI_COMM_WORLD);
    }
}