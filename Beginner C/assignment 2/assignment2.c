#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
All variables in different functions named the same to increase the readibility of the code
*/

void aisle_placer(int i, int* aisles) // to place aisles to given points, int* aisles explaned below
{
    if (i + 1 == aisles[i]) {
        printf("| | ");
    }
}
int min(int a, int b) // given two numbers, returns the little one
{
    if (b < a) {
        return b;
    }
    return a;
}
int max(int a, int b) // given two numbers, returns the greater one
{
    if (b > a) {
        return b;
    }
    return a;
}
void print_reservation(int col_number, char* columns, int row_number, char** seats, int* aisle_place) // function to print reservations, variables explained below
{
    printf("  "); // before column names ( A B C... )
    for (int i = 0; i < col_number; i++) {  //prints out the column names
        printf("%c ", columns[i]);
        aisle_placer(i, aisle_place); //aisles between seats
    }
    for (int i = 0; i < row_number; i++) { // prints out the seats as a matrix
        printf("\n%d ", i + 1); // seat numbers (1,2,3)
        for (int j = 0; j < col_number; j++) {
            printf("%c ", seats[i][j]); // "-" or "+" or "X"
            aisle_placer(j, aisle_place);
        }
    }
    for (int i = 0; i < row_number; i++) {
        for (int j = 0; j < col_number; j++) {
            if (seats[i][j] == '+')  // To turn "+" sign into "X" sign
                seats[i][j] = 'X';
        }
    }
}
double** dist(int col_number, int row_number, int* aisle_place, char** seats) // function to calculate distances
{
    double** distances = (double**)malloc(row_number * sizeof(double*)); // dynamic array that stores the total distances of seats to the other ones
    for (int i = 0; i < row_number; i++) {
        *(distances + i) = (double*)malloc(sizeof(double) * (col_number)); // creating subarrays
    }
    double dist = 0; // to store two seats' basic distance
    double adjusted_dist = 0; // to store adjusted distances
    for (int i = 0; i < row_number; i++) {
        for (int j = 0; j < col_number; j++) {
            distances[i][j] = -10000; // -10000 because adjusted distance can be negative according to given formula
        }
    }
    for (int i = 0; i < row_number; i++) { // 4 for inside to compare seats with each other
        for (int j = 0; j < col_number; j++) {
            for (int k = 0; k < row_number; k++) {
                for (int l = 0; l < col_number; l++) {
                    dist = 0;
                    if (seats[i][j] == '-' && (seats[k][l] == 'X' || seats[k][l] == '+')) { 
					/*if the main seat is empty and the other one is filled,
					 calculate distance; otherwise dist variable already defined as 0*/
                        dist = abs(i - k) + (double)abs(j - l) / 2.0;
                        for (int t = min(j, l); t < max(j, l); t++) {
                            if (aisle_place[t] == t + 1) { // if there is an aisle, treat as equivalent to a seat
                                dist += 0.5;
                            }
                        }
                    }
                    if (dist == 0 || seats[i][j] == '+' || seats[i][j] == 'X') { 
                        adjusted_dist = -100000; 
						/* again, negative adjusted distance coming from was a trouble,
						 so I solved it by setting the default value of adjusted distance even smaller*/
                    }
                    else {
                        adjusted_dist = 100 - pow(100.0, 1.0 / dist); //given formula 
                    }
                    distances[i][j] += adjusted_dist;
                } //distance is turned into adjusted distance immediately as it is calculated, and adjusted distances summed in one loop
            }
        }
    }
    return distances;
}

void one_place_seat(int col_number, int row_number, char** seats, int* aisle_place, char* columns) 
// function to place one person, variables explained below
{
    int checker = 0; // To understand if there is an available seat
    for (int i = 0; i < row_number; i++) {
        for (int j = 0; j < col_number; j++) {
            if (seats[i][j] == '+' || seats[i][j] == 'X')
                checker++; //everytime a seat is filled, checker increases by one
        }
    }
    if (checker == row_number * col_number) { // if checker was increased at every element of matrix, there is no empty seat
        printf("No available seats for the requested reservation!");
        return; // the function is of type void, so return is used to terminate function
    }
    else {

        double** distances = dist(col_number, row_number, aisle_place, seats); //2d dynamic array defined and the distances are calculated
        double maks = -10000000; // again, negative value from adjusted distance formula was trouble so the value is set negative as default
        int x = 0, y = 0; //to store index
        for (int i = 0; i < row_number; i++) {
            for (int j = 0; j < col_number; j++) {
                if (maks < distances[i][j] && seats[i][j] == '-') { // if there is a greater value than max, assign it to the maks
                    maks = distances[i][j];
                    x = i; //store the indexes of the seat with the greatest score
                    y = j;
                }
            }
        }

        seats[x][y] = '+'; //fill the seat
        printf("Reserved seats: %d%c\n", x + 1, columns[y]); // print out reserved seats at the current step

        print_reservation(col_number, columns, row_number, seats, aisle_place); //print out the current state
    }
}
void family_seat(int col_number, int row_number, int person, char** seats, int* aisle_place, char* columns)
/*function to place more than 1 person, variables explained below*/
{
    int count = 0; //to understand if an available reservation can be made
    int** checker = (int**)malloc(sizeof(int*) * row_number); //2d array to check available consecutive seats
    for (int i = 0; i < row_number; i++) {
        *(checker + i) = (int*)malloc(sizeof(int) * col_number); //subarrays created
        for (int j = 0; j < col_number; j++) {
            checker[i][j] = 0; // set to zero, 
        }
    }
    for (int i = 0; i < row_number; i++) {
        for (int j = 0; j < col_number - person + 1; j++) {
            for (int k = j; k < j + person; k++) {
                if (seats[i][k] == '-') //if consecutive seats are equal to '-', +1 the value
                    checker[i][j]++;
            }
        }
    }
    /* The idea is to start from one seat, if next (int person)*seats are empty, increment by one for each seat.
	 so We can understand if there are consecutive empty (int person)*seats
    */
    for (int i = 0; i < row_number; i++) {
        for (int j = 0; j < col_number - person + 1; j++) {
            if (checker[i][j] < person) // if every consecutive block is less than the number of people to be reserved, increment count by one.
                count++;
        }
    }
    if (count == row_number * (col_number - person + 1)) { //if count is equal to that, it means there are no consecutive seats available
        printf("No available seats for the requested reservation!\n");
        return; // return is used to terminate function if necessary
    }
    else {
        double** distances = dist(col_number, row_number, aisle_place, seats); //2d dynamic array defined and the distances are calculated
        int x = 0, y = 0; //to store index
        double maks = -100000000; // negative so there won't be any problem
        for (int i = 0; i < person; i++) { // the assign first seats.
            maks += distances[0][i]; 
        }
        for (int i = 0; i < row_number; i++) {
            for (int j = 0; j < col_number - person + 1; j++) {
                double people_total = -100000000;
                for (int k = j; k < j + person; k++) { // the values of consecutive (int person)*seats are calculated
                    people_total += distances[i][k];
                }
                distances[i][j] = people_total;
            }
        }
        for (int i = 0; i < row_number; i++) {
            for (int j = 0; j < col_number - person + 1; j++) {
                if (maks < distances[i][j]) { //if there is a greater value than maks, assign it.
                    maks = distances[i][j];
                    x = i; //indexes of maks valued seats are stored in x,y
                    y = j;
                }
            }
        }
        for (int a = y; a < y + person; a++) {
            if (seats[x][a] == '-') { // to fill in consecutive empty seats
                seats[x][a] = '+';
            }
        }
        printf("Reserved seats:");
        for (int b = y; b < y + person; b++) { //to print out which seats are reserved
            printf(" %d%c", x + 1, columns[b]);
        }
        printf("\n");
        print_reservation(col_number, columns, row_number, seats, aisle_place);//to print reservation
    }
}

int main()
{
    int row_number = 0, col_number = 0, aisles = 0, game = 1; 
	//respectively, row and column numbers,number of aisles and loop variable to keep getting reservations
    char columns[] = "ABCDEFGHIJKLMNOPQRST"; // column names stored in an array
    int aisle_place[20]; //places of aisles are to be assigned in an array
    int k=0; //aisle place index variable
    printf("Number of rows: ");
    scanf("%d", &row_number);
    printf("Number of seats per row: "); //taking inputs for number of rows, columns and aisles 
    scanf("%d", &col_number);
    printf("Number of aisles: ");
    scanf("%d", &aisles);
    char** seats = (char**)malloc(sizeof(char*) * row_number); //2d dynamic array to store the situation of a seat
    for (int i = 0; i < row_number; i++) {
        seats[i] = (char*)malloc(sizeof(char) * col_number); //subarrays are created
    }
    for (int i = 0; i < row_number; i++) {
        for (int j = 0; j < col_number; j++) { //arrays are set empty as default
            seats[i][j] = '-';
        }
    }
    for (int i = 0; i < col_number; i++) {
        aisle_place[i] = 0; // means there is no aisle anywhere
    }
    for (int i = 0; i < aisles; i++) {

        printf("Add aisle %d after seat: ", i + 1);
        scanf("%d", &k); 
        aisle_place[k - 1] = k; // if an aisle is to be placed after seat number k, store it at (k-1)th index
    }
    print_reservation(col_number, columns, row_number, seats, aisle_place); //print for once
    while (game != -1) {
        int person = 0; //how many people to be reserved
        printf("\nThe number of people in the reservation\n (0: print current reservations, -1: exit):");
        scanf("%d", &person);
        if (person == -1) {
            game = -1; //if -1, terminates the loop and program
        }
        else if (person == 0) {
            print_reservation(col_number, columns, row_number, seats, aisle_place); //prints
        }
        else if (person == 1) {
            one_place_seat(col_number, row_number, seats, aisle_place, columns); //places one person and prints
        }
        else if (person > 1) {
            family_seat(col_number, row_number, person, seats, aisle_place, columns); //places more than one person and prints
        }
    }
    return 0;
}
