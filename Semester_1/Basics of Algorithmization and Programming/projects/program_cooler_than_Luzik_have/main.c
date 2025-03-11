#include <stdio.h>

int main()
{
    double number = 0;
    double ceil=1; double floor=1000;
    int flg = 0;
    int amountSymbol;
    do {
        {
            amountSymbol = 0;
            if(flg++>0) printf("Try again\n");
            scanf("%lf", &number);
            scanf("%*[^\n]%n", &amountSymbol);
        }
    }while(amountSymbol > 0 || number < ceil || number> floor);
    return 0;
}