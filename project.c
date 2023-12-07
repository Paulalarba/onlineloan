#include <stdio.h>
#ifdef _WIN32
#define clear() system("cls")
#else
#define clear() printf("\033[H\033[J")
#endif

#define gotoxy(x, y) printf("\033[%d;%dH", (y), (x))
/* Program File Name: SFP_MLAS.c
           Description: A C program that will generate a Loan Amortization Payment Schedule
           Author: Paul N. Alarba
           Date Started: December 1, 2021
           Date Finished: December 9, 2021
	      Submitted to: Rey Cal */
int mode_D(double);
int mode_W(double);
int mode_M(double);
// main functionn that input the user information.
int main(){
  char name[50], address[50], com_name[50], mode_Pay, again;
  double salary, loan;
  do {
    clear();
    gotoxy(26,2);
    printf("SFP-MLAS (Modified Loan Amortization Schedule)");
    gotoxy(8,5);
    printf("Borrower's Name: ");
    gotoxy(8,6);
    printf("Business/Company Name: ");
    gotoxy(8,8);
    printf("Mode of Payment:");
    gotoxy(8,9);
    printf("D-daily");
    gotoxy(8,10);
    printf("W- weakly");
    gotoxy(8,11);
    printf("M- monday");
    gotoxy(23,12);
    printf(">> ");
    gotoxy(58,5);
    printf("Address: ");
    gotoxy(58,6);
    printf("Monthly Income/Salary: ");
    gotoxy(58,8);
    printf("Loan Amount: P ");
    gotoxy(58,9);
    printf("Interest Rate: ");
    gotoxy(58,10);
    printf("Terms of Payment: ");
    gotoxy(25,5);
    scanf(" %[^\n]", name);
    gotoxy(67,5);
    scanf(" %[^\n]", address);
    gotoxy(31,6);
    scanf(" %[^\n]", com_name);
    gotoxy(81,6);
    scanf("%lf", &salary);
    gotoxy(26,12);
    scanf(" %c", &mode_Pay);
    gotoxy(73,8);
    scanf("%lf", &loan);
    // check what mode of payment choice the user.
   if (mode_Pay == 'D' || mode_Pay =='d'){
        gotoxy(75,9);
        printf("20");
        gotoxy(76,10);
        printf("30 days");
   }
   else if( mode_Pay == 'W' || mode_Pay == 'w'){
        printf("15");
        gotoxy(76,10);
        printf("5 Weeks");
   }
   else if(mode_Pay == 'M' || mode_Pay == 'm'){
     printf("10");
      gotoxy(76,10);
      printf("1 Month");
   }
   gotoxy(20,13);
   printf("\n\n\n\t\t\t\t\t\tSchedule of Payments\n\n\t\t");
    printf("+------------------------------------------------------------------------------+\n\t\t");
    printf("| No. of  | Payment  | Beginning | Principal | Interest | D / W / M | Ending   |\n\t\t");
    printf("|Payments |   Date   |  Balance  |  Payment  |  Amount  |  Payment  | Balance  |\n\t\t");
    printf("+------------------------------------------------------------------------------+\n\t\t");
// call the functions
    if(mode_Pay == 'M' || mode_Pay == 'm'){
        mode_D(loan);
    }
    else if(mode_Pay == 'D' || mode_Pay == 'd'){
        mode_D(loan);
    }
    else if(mode_Pay == 'M' || mode_Pay == 'm'){
        mode_M(loan);
    }
    printf("\n\n\t\t\t\t\tAnother borrower? (Y/N): ");
    scanf("%c" , again);
}while (again == 'y' || again == 'Y');
return 0;
}
// validate if the user is elegibe to make a loan.
int validateLoan(double *value, double minValue, double maxValue, double *lastValidValue) {
    int errorRow = 14;

    do {
        scanf("%lf", value);

        if (*value < minValue || *value > maxValue) {
            gotoxy(1, errorRow);
            printf("Error: Input must be between %.0lf and %.0lf.                 ", minValue, maxValue);
            gotoxy(1, errorRow + 1);
            printf("Please enter a valid value: ");
        }
        else{
            *lastValidValue = *value;
        }
    } while (*value < minValue || *value > maxValue);
    gotoxy(1, errorRow);
    printf("                                                               ");
    gotoxy(1, errorRow + 1);
    printf("                                                                           ");
    gotoxy(73,8);
    printf("%.0lf", *lastValidValue);
    return 0;
}
// check if the user input the corect mode of payment.
int validateMode(char *mode) {
    do {
        gotoxy(26, 11);
        scanf(" %c", mode);

        if (*mode != 'D' && *mode != 'd' && *mode != 'W' && *mode != 'w' && *mode != 'M' && *mode != 'm') {
            printf("Error: Invalid mode. Please enter D, W, or M.\n");
        }
    } while (*mode != 'D' && *mode != 'd' && *mode != 'W' && *mode != 'w' && *mode != 'M' && *mode != 'm');
    gotoxy(0,12);
    printf("                                                               ");
    return 0;
}
// calculate the amount need to pay in daily mode of payment.
int mode_D(double loan){
    int i;
    double term = 30, prin_Pay, int_Amount, payment, end_Bal, tot_Prin, tot_Int,tot_Pay = 0;
    tot_Prin = loan;
    prin_Pay = loan / term;
    tot_Int = loan * 0.20;
    for (int i = 1; i <= 30; i++) {
        if (i == 1) {
            int_Amount = loan * (0.20 / 16);
        } else if (i >= 2 && i <= 10) {
            int_Amount = loan * (0.20 / 16);
        } else if (i >= 11 && i <= 25) {
            int_Amount = loan * (0.20 / 15);
        } else if (i >= 26 && i <= 30) {
            int_Amount = loan * (0.20 / 14);
        }
        end_Bal = loan - prin_Pay;
        payment = prin_Pay + int_Amount;

        printf("| %-8d| 11/%02d/21 | %-10.2lf| %-10.2lf| %-9.2lf| %-10.2lf| %-9.2lf|\n\t\t", i, i, loan, prin_Pay, int_Amount, payment, end_Bal);
        printf("+---------+----------+-----------+-----------+----------+-----------+----------+\n\t\t");
        tot_Pay += payment;
        loan = end_Bal;
    }
    gotoxy(52,113);
    printf("%.0lf", tot_Prin);
    gotoxy(64,113);
    printf("%.0lf", tot_Int);
    gotoxy(75,113);
    printf("%.0lf", tot_Pay);
    gotoxy(20,113);
    printf("Total");
}
//calculate the amount need to pay in weakly mode of payment.
int mode_W(double loan) {
    int i, d = 1;
    double term = 5, prin_Pay, int_Amount, payment, end_Bal, tot_Int, tot_Prin = loan, tot_Pay = 0;

    prin_Pay = loan / term;
    tot_Int = loan * 0.15;
    for (int i = 1; i <= 5; i++) {
        int_Amount = loan * (0.15 / 3);
        end_Bal = loan - prin_Pay;
        payment = prin_Pay + int_Amount;
        printf("| %-8d| 11/%02d/21 | %-10.2lf| %-10.2lf| %-9.2lf| %-10.2lf| %-9.2lf|\n\t\t", i, d, loan, prin_Pay, int_Amount, payment, end_Bal);
        printf("+---------+----------+-----------+-----------+----------+-----------+----------+\n\t\t");
        tot_Pay += payment;
        loan = end_Bal;
        d += 7;
    }
    gotoxy(52,113);
    printf("%.0lf", tot_Prin);
    gotoxy(64,113);
    printf("%.0lf", tot_Int);
    gotoxy(75,113);
    printf("%.0lf", tot_Pay);
    gotoxy(20,113);
    printf("Total");
}

//calculate the amunt need to pay in monthly mode of payment.
int mode_M(double loan) {
    int i;
    double prin_Pay = 0, int_Amount = 0, payment = 0, end_Bal = 0;

    for (int i = 1; i <= 2; i++) {

        printf("| %-8d| 1%01d/1/21  | %-10.2lf| %-10.2lf| %-9.2lf| %-10.2lf| %-9.2lf|\n\t\t", i, i, loan, prin_Pay, int_Amount, payment, end_Bal);
        printf("+---------+----------+-----------+-----------+----------+-----------+----------+\n\t\t");
	
        int_Amount = loan * 0.10;
        end_Bal = 0.00;
        prin_Pay = loan;
        payment = prin_Pay + int_Amount;
    }
}

