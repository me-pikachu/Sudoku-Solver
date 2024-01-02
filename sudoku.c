#include <stdio.h>
#include <time.h>

#define squares 9

void assign_array(int arr1[squares], int arr2[squares]){
    int i;
    for (i=0; i<squares; i++){
        arr1[i] = arr2[i];
    }
}

void assign_array_2D(int arr1[squares][squares], int arr2[squares][squares]){
    int i,j;
    for (i=0; i<squares; i++){
        for (j=0; j<squares; j++){
            arr1[i][j] = arr2[i][j];
        }
    }
}

void print_1D(int array[squares+1]){
    for (int i=0; i<squares; i++){
        printf("%d ",array[i]);
    }
}

void print_2D(int array[squares][squares]){
    for (int i=0; i<squares; i++){
        for (int j=0; j<squares; j++){
            printf("%d ",array[i][j]);
        }
        printf("\n");
    }
}

void print_3D(int array[squares][squares][squares+1]){
    for (int i=0; i<squares; i++){
        for (int j=0; j<squares; j++){
            printf("%d ",array[i][j][0]);
        }
        printf("\n");
    }   
}

int in(int arr_x[squares], int arr_y[squares], int arr_z[squares], int element){
    int i;
    for (i=0; i<squares; i++){
        if (arr_x[i]==element){
            return 1;
        }
    }
    for (i=0; i<squares; i++){
        if (arr_y[i]==element){
            return 1;
        }
    }
    for (i=0; i<squares; i++){
        if (arr_z[i]==element){
            return 1;
        }
    }
    return 0;
}

int solved(int sudoku[squares][squares]){
    int i,j;
    for(i=0; i<9; i++){
        for (j=0; j<9; j++){
            if (sudoku[i][j] == 0){
                return 0;
            }
        }
    }
    return 1;
}

void available_numbers(int sudoku[squares][squares], int pos[2], int array[10]){
    if (sudoku[pos[0]][pos[1]]!=0){
        array[0] = -1;
    } else {
        int arr_x[9];
        assign_array(arr_x,sudoku[pos[0]]);
        int arr_y[9];
        int arr_z[9];
        int i,j,k;
        for (i=0; i<squares; i++){
            arr_y[i] = sudoku[i][pos[1]];
        }

        int count = 0;
        if (pos[0] >= 0 && pos[0] <= 2){
            if (pos[1] >= 0 && pos[1] <= 2){
                for (i=0; i<=2; i++){
                    for (j=0; j<=2; j++){
                        arr_z[count] = sudoku[i][j];
                        count ++;
                    }
                }
                goto re;
            } else if (pos[1] >= 3 && pos[1] <= 5){
                for (i=0; i<=2; i++){
                    for (j=3; j<=5; j++){
                        arr_z[count] = sudoku[i][j];
                        count ++;
                    }
                }
                goto re;
            } else {
                for (i=0; i<=2; i++){
                    for (j=6; j<=8; j++){
                        arr_z[count] = sudoku[i][j];
                        count ++;
                    }
                }
                goto re; 
            }           
        } else if (pos[0] >= 3 && pos[0] <= 5){
            if (pos[1] >= 0 && pos[1] <= 2){
                for (i=3; i<=5; i++){
                    for (j=0; j<=2; j++){
                        arr_z[count] = sudoku[i][j];
                        count ++;
                    }
                }
                goto re;
            } else if (pos[1] >= 3 && pos[1] <= 5){
                for (i=3; i<=5; i++){
                    for (j=3; j<=5; j++){
                        arr_z[count] = sudoku[i][j];
                        count ++;
                    }
                }
                goto re;
            } else {
                for (i=3; i<=5; i++){
                    for (j=6; j<=8; j++){
                        arr_z[count] = sudoku[i][j];
                        count ++;
                    }
                }
                goto re; 
            }
        } else {
            if (pos[1] >= 0 && pos[1] <= 2){
                for (i=6; i<=8; i++){
                    for (j=0; j<=2; j++){
                        arr_z[count] = sudoku[i][j];
                        count ++;
                    }
                }
                goto re; 
            } else if (pos[1] >= 3 && pos[1] <= 5){
                for (i=6; i<=8; i++){
                    for (j=3; j<=5; j++){
                        arr_z[count] = sudoku[i][j];
                        count ++;
                    }
                }
                goto re; 
            } else {
                for (i=6; i<=8; i++){
                    for (j=6; j<=8; j++){
                        arr_z[count] = sudoku[i][j];
                        count ++;
                    }
                }
                goto re; 
            }
        }
        
        re : count = 0;
            for (k=1; k<10; k++){
            if (in(arr_x,arr_y,arr_z,k)==0){
                array[count+1] = k;
                count ++;
            }
        }
        array[0] = count;
    }
}

int solver(int sudoku[squares][squares])
{
    if (solved(sudoku)==1){
        return 1;
    } else {
        int sq[squares][squares][squares+1];
        int i,j,k;
        for (i=0; i<squares; i++){
            for (j=0; j<squares; j++){
                int pos[2] = {i,j};
                available_numbers(sudoku,pos,sq[i][j]);
            }
        }
        int temp_sudoku[squares][squares];
        int min = 10;
        int sq1;
        int sq2;
        for (i=0; i<squares; i++){
            for (j=0; j<squares; j++){
                if (sq[i][j][0] == 0){
                    return 0;
                } else if (sq[i][j][0] == 1){
                    min = 1;
                    sudoku[i][j] = sq[i][j][1];
                    break;
                } else {
                    if (sq[i][j][0] > 0){
                        if (min > sq[i][j][0]){
                            sq1 = i;
                            sq2 = j;
                            min = sq[i][j][0];
                        }
                    }
                }
            }
        }
        if (min == 1){
            solver(sudoku);
        } else {
            for (i=1; i<=min; i++){
                assign_array_2D(temp_sudoku,sudoku);
                temp_sudoku[sq1][sq2] = sq[sq1][sq2][i];
                if (solver(temp_sudoku) == 1){
                    assign_array_2D(sudoku,temp_sudoku);
                    return 1;
                }
            }
            return 0;
        }
    }
}

void main()
{
    int sudoku[9][9];
    printf("Enter the sudoku.....\n");
    //= {{2,0,0,0,0,5,0,4,0},{0,9,0,0,0,4,6,0,0},{4,0,7,0,2,9,3,5,0},{5,0,0,4,0,2,8,6,7},{7,2,0,0,0,0,0,9,0},{3,0,0,9,0,0,5,0,4},{0,7,0,2,0,6,0,3,5},{9,4,0,0,8,1,0,7,0},{0,0,0,7,0,0,9,0,1}};
    for (int i=0; i<squares; i++ ){
        for (int j=0; j<squares; j++){
            scanf("%d",&sudoku[i][j]);
        }
    }
    printf("\n");
    printf("Unsolved Sudoku : \n");
    print_2D(sudoku);
    printf("\n");
    int res = solver(sudoku);
    printf("\nRes : %d\n",res);
    printf("Solved Sudoku : \n");
    print_2D(sudoku);
    printf("\n");
}
