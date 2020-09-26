// Preprocessor directives
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// Constant that represents the dimension of arrays
#define LENGTH 3

// Prototype functions list
void CopyColumn(float [][LENGTH], float [], char Variable);
void CopyMatrix(float [][LENGTH], float [][LENGTH]);
void Set(float [][LENGTH], float []);
void Display(float [][LENGTH], float []);
void DisplayDeterminant(float N[][LENGTH], float D[][LENGTH], char Name, float X, float Det);
void DisplayDetSystem(float);
void DisplaySolution(float, float, float);
void ProcessVariable(float [][LENGTH], float [][LENGTH], float [], char);
void Reset(float [][LENGTH], float []);

// Function prototype
float GetDeterminants(float [][LENGTH]);

// Start point
int main()
{
    char Answer; // Answer to continue

    do{
        // bidimensional arrays
        float Matrix[LENGTH][LENGTH], MatrixTemp [LENGTH][LENGTH];

        // bidimensional array
        float Vector[LENGTH];

        // System variables and det
        float X, Y, Z, detSystem;

        // Resets all values to zero to calculate a new system 3x3
        Reset(Matrix, Vector);
        X = 0.0, Y = 0.0, Z = 0.0, detSystem = 0.0;

        // Welcome message from the program
        printf("\n\t-------------------------------------------------------------------------------------------------------------\n\t|>>>> NUMERICAL METHODS: Krammer's method to solve systems of linear equations with 3 variables <<<<|\n\t-------------------------------------------------------------------------------------------------------------\n");

        // Instructions for use
        printf("\n\t>>>> Enter first the 9 system coefficients and then the independent terms.\n\n");

        // Obtains and displays system values given by the user
        Set(Matrix, Vector);
        Display(Matrix, Vector);

        // Calculates and displays the system determinant
        detSystem = GetDeterminants(Matrix);
        DisplayDetSystem(detSystem);

        // Processes, obtains and displays the determinant and data for the unknown X
        ProcessVariable(Matrix, MatrixTemp, Vector, 'x');
        X = GetDeterminants(Matrix);
        DisplayDeterminant(Matrix, MatrixTemp, 'x', X, detSystem);

        // Processes, obtains and displays the determinant and data for the unknown Y
        ProcessVariable(Matrix, MatrixTemp, Vector, 'y');
        Y = GetDeterminants(MatrixTemp);
        DisplayDeterminant(MatrixTemp, Matrix, 'y', Y, detSystem);

        // Processes, obtains and displays the determinant and data for the unknown Z
        ProcessVariable(Matrix, MatrixTemp, Vector, 'z');
        Z = GetDeterminants(Matrix);
        DisplayDeterminant(Matrix, MatrixTemp, 'z', Z, detSystem);

        // Show the system solution
        DisplaySolution((X/detSystem) , (Y/detSystem), (Z/detSystem));

        // Notice to continue of the program
        printf("\n\n . . . Press 'y' to evaluate a new system, any key to exit . . .\n\n\t");
        scanf("%s", &Answer);
        system("cls");

    }while(toupper(Answer) == 'Y');

    // Output message
    printf("\n\n. . . Thanks . . .\n\n");

    return 0;
}

/*
    > CopyColumn

    Comment: Copies the array values (vector) to a given Matrix column
    conditioned by the incognita.

    Parameters: M[][LENGTH] -> Matrix whose column will be modified
                V[LENGTH]   -> Arrangement of the independent terms
                Variable    -> Character representing the column of the unknown to be copied

*/
void CopyColumn(float M[][LENGTH], float V[LENGTH], char Variable)
{
    int ValueVariable;
    Variable = toupper(Variable);

    switch(Variable)
    {
        case 'X': ValueVariable = 0; break;
        case 'Y': ValueVariable = 1; break;
        case 'Z': ValueVariable = 2; break;
        default : ValueVariable = 0; break;
    }

    printf("\n\n\t\t . . . Copying T.I to the column %c\n\n", Variable);
    for (int i = 0; i < LENGTH; i++)
    {
        M[i][ValueVariable] = V[i];
    }

    printf("\n\n");
    system("pause");
    system("cls");

    return;
}

/*
    > CopyMatrix

    Comment: Copies the values of the original Matrix or a temporary Matrix.

    Parameters: A[][LENGTH] -> Original Matrix
                B[][LENGTH] -> Temporary Matrix
*/
void CopyMatrix(float A[][LENGTH], float B[][LENGTH])
{
    for (int i = 0; i < LENGTH; i++)
    {
        for (int j = 0; j < LENGTH; j++)
        {
            A[i][j] = B[i][j];
        }
    }
    return;
}

/*
    > Set

    Comment: It asks the user for all the values of the whole system, both the unknowns
    as the one of the independent terms.

    Parameters: M[][LENGTH] -> Original Matrix to be filled
                V[]         -> Arrangement of the independent terms
*/
void Set(float M[][LENGTH], float V[])
{
    printf("\n\t\t\t_______________________________\n\n\t\t\t3x3 SYSTEM COEFFICIENT \n\t\t\t_______________________________\n\n");
    printf("\n\t\t|X|\t+\t|Y|\t+\t|Z|\t = \t|T.I|\n\n");
    for (int i = 0; i < LENGTH; i++)
    {
        printf("\t\t=================== EQUATI. # %d =====================\n", i+1);
        for (int j = 0; j < LENGTH; j++)
        {
            if (j == 0) printf("\t\t");
            if (j == 1) printf("\t\t\t\t");
            if (j == 2) printf("\t\t\t\t\t\t");
            scanf("%f", &M[i][j]);
        }
    }

    for (int i = 0; i < LENGTH; i++)
    {
        printf("\t\t\t\t\t\t====== T.I # %d ======\n", i+1);
        printf("\t\t\t\t\t\t\t   \t");
        scanf("%f", &V[i]);
    }

    printf("\n\n");
    system("pause");
    system("cls");

    return;
}

/*
    > Display

    Comment: Shows the current state of the system, both the Matrix and the vector

    Parameters: M[][LENGTH] -> Current System Matrix
                V[]         -> Current arrangement of independent terms

*/
void Display(float M[][LENGTH], float V[])
{
    printf("\n\t\t\t_____________________________________\n\n\t\t\tSYSTEM OF SIMULTANEOUS EQUATIONS 3x3\n\t\t\t_____________________________________\n\n");
    printf("\n\t\t|X|\t+\t|Y|\t+\t|Z|\t = \t|T.I|\n\n");
    for (int i = 0; i < LENGTH; i++)
    {
        printf("\n\t\t|%.1f|\t\t|%.1f|\t\t|%.1f|\t = \t|%.1f|\n\n",M[i][0], M[i][1], M[i][2], V[i]);
    }

    printf("\n\n");
    system("pause");
    system("cls");
    return;
}

/*
    > DisplayDeterminant

    Comment: Shows the value of the matrices in both the numerator and denominator
    in a format required by Krammer's method and shows the solution value.

    Parameters: N[][LENGTH] -> Matrix of the numerator
                N[][LENGTH] -> Matrix of the denominator
                Name        -> Name of the unknown
                Variable    -> Value of the unknown
                Det         -> System determinant value
*/
void DisplayDeterminant(float N[][LENGTH], float D[][LENGTH], char Names, float Variable, float Det)
{
    Names = toupper(Names);
    printf("\n\t_______________________\n\n\tVALUE OF VARIABLE %c \n\t_______________________\n\n\n", Names);
    printf("|\t%.1f\t%.1f\t%.1f\t|\n", N[0][0], N[0][1], N[0][2]);
    printf("|\t%.1f\t%.1f\t%.1f\t|\n", N[1][0], N[1][1], N[1][2]);
    printf("|\t%.1f\t%.1f\t%.1f\t|   %.1f\n", N[2][0], N[2][1], N[2][2], Variable);
    printf("\t----------------------  = ------- = %.1f\n", Variable/Det);
    printf("|\t%.1f\t%.1f\t%.1f\t|   %.1f\n", D[0][0], D[0][1], D[0][2], Det);
    printf("|\t%.1f\t%.1f\t%.1f\t|\n", D[1][0], D[1][1], D[1][2]);
    printf("|\t%.1f\t%.1f\t%.1f\t|\n\n", D[2][0], D[2][1], D[2][2]);
    printf("\n\n");
    system("pause");
    system("cls");
    return;
}

/*
    > DisplayDetSystem

    Comment: Displays the value of the system owner on the screen
    previously calculated.

    Parameters: det -> Real variable that represents the determinant of the system
*/
void DisplayDetSystem(float det)
{
    printf("\n\n\t\tSystem determinant is: %.1f\n\n", det);
    printf("\n\n");
    system("pause");
    system("cls");
    return;
}

/*
    > DisplaySolution

    Comment: Shows the system solution at the end of the program execution.

    Parameters: x -> Value of the unknown X
                y -> Value of the unknown Y
                z -> Value of the unknown Z

*/
void DisplaySolution(float x, float y, float z)
{
    system("cls");
    printf("\n\t____________________\n\n\tSYSTEM SOLUTION\n\t____________________\n\n");
    printf("\t/\n\t{ X = %.1f\n\t{ Y = %.1f\n\t{ Z = %.1f\n\t\\ \n\n", x, y, z);
    printf("\n\n");
    system("pause");
    return;
}

/*
    > ProcessVariable

    Comment: Depending on the unknown to be processed, it temporarily saves the values
    from the original Matrix, copies the independent arrangement of terms to the desired column
    and displays the result.

    Parameters: Mat[][LENGTH]       -> Original Matrix
                MatTem[][LENGTH]    -> Temporary Matrix
                Vec[]               -> Arrangement of the independent terms
                Nom                 -> Character representing the unknown to be processed

*/
void ProcessVariable(float Mat[][LENGTH], float MatTem[][LENGTH], float Vec[], char Nom)
{
    Nom = toupper(Nom);
    switch(Nom)
    {
        case 'X':
            CopyMatrix(MatTem, Mat);
            CopyColumn(Mat, Vec, 'x');
            Display(Mat, Vec);
            break;
        case 'Y':
            CopyMatrix(Mat, MatTem);
            CopyColumn(MatTem, Vec, 'y');
            Display(MatTem, Vec);
            break;
        case 'Z':
            CopyMatrix(MatTem, Mat);
            CopyColumn(Mat, Vec, 'z');
            Display(Mat, Vec);
            break;
        default :
            Display(Mat, Vec);
            break;
    }
    return;
}

/*
    > Reset

    Comment: Resets the Matrix and Vector values to zero to begin with
    a new execution of the program.

    Parameters: M[][LENGTH]     -> Original System Matrix
                V[]             -> One-dimensional arrangement of independent terms
*/
void Reset(float M[][LENGTH], float V[])
{
    for (int i = 0; i < LENGTH; i++)
    {
        V[i] = 0;
        for (int j = 0; j < LENGTH; j++)
        {
            M[i][j] = 0;
        }
    }
    return;
}

/*
    > GetDeterminants

    Comment: By directly implementing Sarrus' method of obtaining
    the numerical value of a Matrix trigger for a 3x3 system.

    Parameters: Matrix with values to be calculated

    Return: The real determinant of the given Matrix
*/
float GetDeterminants(float M[][LENGTH])
{
    float firstFactor = (M[0][0] * M[1][1] * M[2][2]) + (M[0][1] * M[1][2] * M[2][0]) + (M[1][0] * M[2][1] * M[0][2]);
    float secondFactor = (M[0][2] * M[1][1] * M[2][0]) + (M[0][1] * M[1][0] * M[2][2]) + (M[1][2] * M[2][1] * M[0][0]);
    return firstFactor - secondFactor;
}
