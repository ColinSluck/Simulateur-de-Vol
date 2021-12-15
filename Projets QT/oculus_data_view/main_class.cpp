#include "oculus.h"
#include "stdio.h"

int main()
{
    Oculus data_oculus;
    data_oculus.initialisation();

    while(true)
    {
        data_oculus.refreshData();
        data_oculus.printData();
    }
    data_oculus.stop();
}
