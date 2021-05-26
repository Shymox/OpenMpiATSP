// Project_PEA.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//


#include "MpiHelper.h"

void slave()
{
    std::cout<<"im slave\n";
    char a[12];
    MPI_Status status;
    MPI_Recv(&a,12,MPI_CHAR,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
    std::cout<<a<<"\n";
}

void slave2()
{
    std::cout<<"im slave\n";
    char a[12];
    MPI_Status status;
    MPI_Bcast(&a,12,MPI_CHAR,0,MPI_COMM_WORLD);
    std::cout<<a<<"\n";
}


void master()
{
    int ntasks;
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    char a[] = "Ala Ma Kota";
    std::cout<<"im master\n";
    for(int i = 1 ; i<=ntasks;i++)
    {
        MPI_Send(&a,12,MPI_CHAR,i,15,MPI_COMM_WORLD);
    }
    
}

void master2()
{
    char a[] = "Ala Ma Kota";
    std::cout<<"im master\n";
    MPI_Bcast(&a,12,MPI_CHAR,0,MPI_COMM_WORLD);
}

//funkcja main programu
int main(int argc, char *argv[])
{
    MpiHelper* mpi = new MpiHelper(argc,argv);
    return 0;
}


// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
