#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
// Inicialización de variables globales
int alto, ancho;
char Dato1[60];
unsigned char header[54];
unsigned char gray;
// Programa para escala de grises
void Gray(){
    int i,j;
    char Dato2[60];
    unsigned char pixel[3];
    unsigned char A[54];

    FILE* entrada = fopen(Dato1,"rb");
    printf("Digite nombre del archivo a pasar a blanco y negro \n");
    scanf_s("%s", Dato2);
    FILE* salida = fopen(Dato2,"wb");

    fread(A, sizeof(unsigned char), 54, entrada);
    fwrite(A, sizeof(unsigned char), 54, salida);
    //Se hace el recorrido de los pixeles para poderlos pasas a escala de grises
    for(i = 0; i < alto; ++i){
        for(j = 0;j < ancho; ++j){
            fread(pixel, 3, 1, entrada);
            gray = pixel[0] * 0.3 + pixel[1] * 0.58 + pixel[2] * 0.11;
            memset(pixel, gray, sizeof(pixel));
            fwrite(&pixel, 3, 1, salida);
        }
    }
    fclose(entrada);
    fclose(salida);
}
// Programa para convolución
void Convolucion(){
    //Variables
    int i,j,k,l,h;
    char Dato2[60];
    char m[3][3],pixel[3];
    char matrixR[ancho][alto];
    char XY;
    unsigned char en[54];

    FILE* entrada = fopen(Dato1,"rb");
    printf("Digite nombre del archivo a hacer convolucion \n");
    scanf_s("%s", Dato2);
    FILE* salida = fopen(Dato2,"wb");
    fread(en, sizeof(unsigned char), 54, entrada);
    fwrite(en, sizeof(unsigned char), 54, salida);

    printf("digite la matriz:\n");
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
        printf("posicion %d %d \n",i,j);
        scanf_s("%d",&m[i][j]);
        }
    }
    printf("Matriz resultante: \n\n");//imprimo la matriz
    for (i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            printf("%d    ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for (i = 0; i < alto; ++i)
    {
        for (j = 0; j < ancho; ++j)
        {
            if (i==0 && j==0){
                fread(pixel, 3, 1, entrada);
                fwrite(&pixel, 3, 1, salida);
            }
            if (i==alto && j==alto){
                fread(pixel, 3, 1, entrada);
                fwrite(&pixel, 3, 1, salida);
            }

            fread(pixel, 3, 1, entrada);
            gray = pixel[0] * 0.3 + pixel[1] * 0.58 + pixel[2] * 0.11;
            matrixR[i][j]=gray;
            for(k = 0; k < 3; ++k)
            {
                for(l = 0; l < 3; ++l)
                {
                    XY=matrixR[i-1+k][j-1+l] * m[k][l];
                    h+=XY;
                 }
             }
            memset(pixel,h,sizeof(pixel));
            fwrite(&pixel, 3, 1, salida);
            h=0;
        }
    }
    fclose(entrada);
    fclose(salida);
}
// Programa principal
int main()
{
    unsigned char D1,D2,opcion;
    char rep;
    do{
    printf("Digite nombre del archivo a abrir en BMP \n");
    scanf_s("%s", Dato1);
    FILE* entrada = fopen(Dato1,"rb");

    if (entrada==NULL){
        printf("No encontrado\n");
        exit (-1);
    }
    D1 = fgetc(entrada);

    /*if((D1!='B') || (D2!='M')){
        printf("Lo sentimos, el archivo no es de tipo BMP");
        exit(-1);
    }*/
    printf("Genial, el archivo es BMP \n");
    fseek(entrada, 0, SEEK_SET); //devolvemos el apuntador
    fread(header, sizeof(unsigned char), 54, entrada);

    ancho = (int)&header[18];
    alto = abs((int)&header[22]);
    printf("alto: %d ; ancho: %d   \n", alto, ancho);

    printf("Por favor, seleccione la opcion a realizar:\n");
    printf("1: Imagen a escala de grises \n");
    printf("2: Convolucion \n");
    printf("3: Salir \n");
    scanf_s("%d",&opcion);

    switch(opcion){
        case 1:
        Gray();
        break;
        case 2:
        Convolucion();
        break;
        case 3:
        exit(-1);
        break;
        default:
        printf("opcion no valida \n");
    }
    printf("\nPara ingresar otra imagen pulse 1, de lo contrario pulse 2: ");
    scanf("%d",&rep);
	}while(rep==1);
    getch();
    return 0;
}