#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { EMP_FULLTIME = 0, EMP_CONTRACT = 1 } JobType;

typedef struct {
    char empName[25];
    int id;
    JobType jobType;
    union {
        float fixedSalary;
        struct {
            float ratePerHour;
            int totalHours;
        } contract;
    } income;
} Staff;

// Helper function to safely clear the input buffer
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void getStaffDetails(Staff *s, int index) {
    int choice;
    printf("\n--- Enter Details for Employee %d ---\n", index + 1);
    
    printf("Name: ");
    // Safely read spaces and limit input to 24 characters to prevent buffer overflow
    scanf(" %[^\n]24s", s->empName); 
    clearBuffer();

    printf("ID: ");
    scanf("%d", &s->id);
    
    printf("Job Type (0-FullTime, 1-Contract): ");
    scanf("%d", &choice);
    s->jobType = (JobType)choice;

    if (s->jobType == EMP_FULLTIME) {
        printf("Monthly Salary: ");
        scanf("%f", &s->income.fixedSalary);
    } else {
        printf("Hourly Rate: ");
        scanf("%f", &s->income.contract.ratePerHour);
        printf("Total Hours Worked: ");
        scanf("%d", &s->income.contract.totalHours);
    }
    clearBuffer(); // Clean trailing newline after reading numbers
}

float printStaffPayslip(Staff *s) {
    float amount = 0.0f;
    printf("\n---------------------------\n");
    printf("Name   : %s\n", s->empName);
    printf("ID     : %d\n", s->id);

    if (s->jobType == EMP_FULLTIME) {
        amount = s->income.fixedSalary;
        printf("Type   : FULL TIME\n");
        printf("Salary : %.2f\n", amount);
    } else {
        amount = s->income.contract.ratePerHour * s->income.contract.totalHours;
        printf("Type   : CONTRACT\n");
        printf("Hourly Rate : %.2f\n", s->income.contract.ratePerHour);
        printf("Hours       : %d\n", s->income.contract.totalHours);
        printf("Payable     : %.2f\n", amount);
    }
    return amount;
}

int main() {
    Staff *staffList;
    int empCount;
    float companyTotal = 0.0f;

    printf("How many employees? ");
    if (scanf("%d", &empCount) != 1 || empCount <= 0) {
        printf("Invalid count!\n");
        return 1;
    }
    clearBuffer();

    staffList = (Staff *)malloc(empCount * sizeof(Staff));
    if (!staffList) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < empCount; i++) {
        getStaffDetails(&staffList[i], i);
    }

    printf("\n\n======== COMPANY PAYSLIPS ========\n");
    for (int i = 0; i < empCount; i++) {
        companyTotal += printStaffPayslip(&staffList[i]);
    }

    printf("\n==================================\n");
    printf("Total Company Payout: %.2f\n", companyTotal);

    free(staffList);
    staffList = NULL;
    return 0;
}

