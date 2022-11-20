/*
Se hizo uso de las siguientes referencias:
https://levelup.gitconnected.com/solving-2d-heat-equation-numerically-using-python-3334004aa01a
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

pthread_mutex_t lock;
#define m 6
#define n 6
int i;
int k;
int j;
int l;
int p;
int pi;
int pj;
float matrixTemp[n][m]={{-2,-2,-2,-2,-2,-2},
                     {-2,-2,-2,-2,-2,-2},
                     {-2,-2,-2,-2,-2,-2},
                     {-2,-2,-2,-2,-2,-2},
                     {-2,-2,-2,-2,-2,-2},
                     {-2,-2,-2,-2,-2,-2}};
                
char matrix[n][m]={{'F','F','F','F','F','F'},
                {'F','F','F','F','F','F'},
                {'F','F','C','C','C','F'},
                {'F','C','C','C','F','F'},
                {'F','F','C','C','C','F'},
                {'F','F','F','F','F','F'}};


//Funcion para llenar la matriz de temperatura
void *temp(void *a){
    pthread_mutex_lock(&lock);
    for(i=0; i<n;i++){
        for (j=0;j<m;j++){
                if(matrix[i][j]=='F'){
                    matrixTemp[i][j]=(rand( ) % 610 ) / 10.0f ;
                }
                else if(matrix[i][j]=='C'){
                    matrixTemp[i][j]=((rand()%410)+600)/10.0f;
            }
        }
    } 
    pthread_mutex_unlock(&lock); 
}
        
    


int main(int argc, char** argv){
    srand(time(NULL));
    
  //impresion de la matriz original
    printf("\n\t Matriz original\n\n");
    for(i=0; i<n;i++){
        printf("\t  ");
        for (j=0;j<m;j++){
            printf("%c ",matrix[i][j]);
        }
        printf("\n");
    }
  
  
  //declaracion de threads y cores
    int thread_num;
     /* Para convertir el numero dado por el usuario en el número de thread para paralelizar el proceso */
    if (argc > 1) {
        thread_num = atoi(argv[1]);
    }
    pthread_t threads[thread_num]; //Arreglo de threads

    for(l=0; l<thread_num; l++){
        pthread_create(&threads[i], NULL, temp, NULL); //Creamos cada thread con los valores necesarios
    }


    temp(matrixTemp);

  //impresion de la matriz de temperaturas
    printf("\n\t Matriz de temperaturas\n\n");
    for(i=0; i<n;i++){
        for (j=0;j<m;j++){
            printf(" %1.1f ",matrixTemp[i][j]);
        }
        printf("\n");
    }
  
  //Ecuacion de temperatura
    int max_time = 80;
    int a = 2;
    int dx = 1;
    float dt = (pow(dx, 2))/(4 * a);
    float g = (a * dt) / (dx*dx);
  
    int u[max_time][n][m];
    omp_set_num_threads(thread_num);
    #pragma omp parallel for private(k, i, j) shared (u, matrixTemp)
    for(int k = 0; k < max_time; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                u[k][i][j] = matrixTemp[i][j];
            }
        }
    }
    for(int k = 0; k < max_time - 1; k++){
        for(int i = 1; i < n - 1; i+= dx){
            for(int j = 1; j < m - 1; j+= dx){
                u[k + 1][i][j] = g * (u[k][i+1][j] + u[k][i-1][j] + u[k][i][j+1] + u[k][i][j-1] - 4*u[k][i][j]) + u[k][i][j];
            }
        }
    }
  
  //Resultado
    printf("\n |------------------------------------------------------|");
    printf("\n |                      ADMINISTRADOR                   |");         
    printf("\n |             La ecuacion de calor requerida:          |");
    printf("\n |            y = %d *[ %f / (%d^2)]                |", a, dt, dx);
    printf("\n |------------------------------------------------------|");

    return 0;

}
