#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"
#include "time.h"

typedef struct
{
    int numLib;
    int paginas;
    char genero[100];
    char titulo[100];
    char autor[100];
} libro;

void crearArchivo();
void leerBaseDeDatos();
void vistaPorMatriz(libro librito);
int mostrarmatriz(libro [12][100],int,int);
int valGen(int);
void elegirorden();
void insertar(libro libros[], int i, libro dato);
void ordenamientoins(libro libros[], int numLibros);
void ordenamientoSeleccion (libro libros[], int numLibros);
int posicionMenor(libro libros[], int pos, int numLibros);
void ordenDeCarga();
int registrosCargadosBib();
int cargaBaseDatos();
libro cargaEstructuraLib(int*);
int libgenero(libro*);
int verificarLibro(int);
int recuperarArchivoEl();
int registrosCargadosEli();
void leerEliminados();
int recuperarArchivo(int);
void busquedaLibro();
libro filtrobusqueda(int);
void mostrarLibro(libro);
int similares(int,libro);
void eliminarArchivoB();
void eliminarArchivo(int);
void juego();
int arrayNumL(int arr[]);
void pilaNumL(Pila*,int[],int);
int juegoiniciado(Pila*,int);
void contadorSeg(int);
int puntos(int,int);
int librosCargados();

int main()
{
    crearArchivo();
    printf("=============================================\n");
    printf("%38s\n","BIENVENIDO LA BIBLIOTECA VIRTUAL");
    printf("=============================================\n");
    sleep(2);
    system("cls");
    int opc;
    int error;
    int recuperar=0;
    char menu='s';
    char caso='s';
    while(menu=='s' || menu=='S')
    {
        printf("Seleccione que desea realizar:\n 1) Ver Libros\n 2) Ingresar Libro\n 3) Buscar Libro\n 4) Jugar\n 5) Salir\nOPCION: ");
        fflush(stdin);
        scanf("%d", &opc);
        system("cls");
        switch(opc)
        {
        case 1:
            caso='s';
            while(caso=='s' || caso=='S')
            {
                leerBaseDeDatos();
                system("pause");
                system("cls");
                printf("Desea volver a ver los libros? S/N: ");
                fflush(stdin);
                scanf("%c", &caso);
                system("cls");
            }
            printf("Desea volver al menu? S/N: ");
            fflush(stdin);
            scanf("%c", &menu);
            system("cls");
            break;
        case 2:
             error=cargaBaseDatos();
            system("cls");
            if (error==0)
            {
                printf("Desea volver al menu? S/N: ");
                fflush(stdin);
                scanf("%c", &menu);
                system("cls");
            }
            else
            {
                menu='s';
            }
            break;
        case 3:
            busquedaLibro();
            system("cls");
            printf("Desea volver al menu? S/N: ");
            fflush(stdin);
            scanf("%c", &menu);
            system("cls");
            break;
        case 4:
            juego();
            printf("Desea volver al menu? S/N: ");
            fflush(stdin);
            scanf("%c", &menu);
            system("cls");
            break;
        case 5:
            printf("¡¡¡ADIOS!!!");
            sleep(2);
            return 0;

            break;
        default:
            printf("El numero ingresado es incorrecto, ingrese S si desea ingresar otro numero, N si desea salir\n");
            fflush(stdin);
            scanf("%c", &menu);
            system("cls");
            break;
        }
    }
    printf("ADIOS!!!");
    sleep(2);
    return 0;

}

void crearArchivo(){
 FILE *archi;
    archi = fopen("Base_De_Datos_Bib.bin", "rb");
    if (archi != NULL)
    {
    }
    else
    {
    archi = fopen("Base_De_Datos_Bib.bin", "wb");
    }
    fclose(archi);
}


void leerBaseDeDatos()
{
    char eleccion='s';
    int valor=0;
    valor=librosCargados();
    if(valor==0)
    {
        printf("ERROR, NO HAY LIBROS CARGADOS\n");
    }
    else
    {
        int i=0;
        libro librito;
        int opc=-1;
        while(opc!=1 && opc!=2 && opc!=3 && opc!=4&&i<3&&tolower(eleccion)=='s')
        {
            printf("Decide si quieres ver los libros por: \n 1) Orden de carga\n 2) Orden por su genero\n 3) Orden por su numero de libro\n 4) Orden por cantidad de paginas\n");
            printf("Ingrese la opcion: ");
            fflush(stdin);
            scanf("%d",&opc);
            if(opc!=1 && opc!=2 && opc!=3 && opc!=4)
            {
                i++;
                system("cls");
                printf("Porfavor ingrese un numero valido.\n");
                if(i<4){
                printf("Presione 'S' para volver a ingresar un numero, 'N' para salir.\n");
                fflush(stdin);
                scanf("%c",&eleccion);
                }
                system("cls");
                if(tolower(eleccion)=='s'&&i<4){
                printf("Intentos restantes: %d\n", 3-i);
                sleep(2);
                }
            }
            system("cls");
        }
        if(opc==2)
        {
            printf("Vista por genero: \n");
            vistaPorMatriz(librito);
        }
        else if(opc==3)
        {
            printf("Vista por Numero de Libro: \n");
            elegirorden(1);
        }
        else if(opc==4)
        {
            printf("Vista por Cantidad de Paginas: \n");
            elegirorden(0);
        }
        else if(opc==1)
        {
            printf("Vista por Orden de Carga: \n");
            ordenDeCarga();
        }
    }
}
void vistaPorMatriz(libro librito)
{

    libro matrizPorGen[12][100];
    libro generosin[12][100];
    int  j = 0,j1=0, j2 = 0, j3 = 0,j4 = 0,j5 = 0,j6 = 0,j7 = 0,j8 = 0,j9 = 0,j10 = 0,j11 = 0;
    int val1=0,val2=0,val3=0,val4=0,val5=0,val6=0,val7=0,val8=0,val9=0,val10=0,val11=0,val12=0;
    int i=0;
    int singenero;
    int singeneroarr[12][100];
    FILE *archi;
    archi = fopen("Base_De_Datos_Bib.bin", "rb");
    if (archi != NULL)
    {
        while (!feof(archi))
        {
            fread(&librito, sizeof(libro), 1, archi);
            if (!feof(archi))
            {
                if (strcmp("Autoayuda", librito.genero) == 0)
                {
                    matrizPorGen[0][j] = librito;
                    j++;
                    val1++;

                }
                else if(strcmp("Biografia", librito.genero) == 0)
                {
                    matrizPorGen[1][j1] = librito;
                    j1++;
                    val2++;
                }
                else if(strcmp("Ciencia ficcion", librito.genero) == 0)
                {
                    matrizPorGen[2][j2] = librito;
                    j2++;
                    val3++;
                }
                else if(strcmp("Cientifico", librito.genero) == 0)
                {
                    matrizPorGen[3][j3] = librito;
                    j3++;
                    val4++;
                }
                else if(strcmp("Historico", librito.genero) == 0)
                {
                    matrizPorGen[4][j4] = librito;
                    j4++;
                    val5++;
                }
                else if(strcmp("Infantil", librito.genero) == 0)
                {
                    matrizPorGen[5][j5] = librito;
                    j5++;
                    val6++;
                }
                else if(strcmp("Novela", librito.genero) == 0)
                {
                    matrizPorGen[6][j6] = librito;
                    j6++;
                    val7++;
                }
                else if(strcmp("Policial", librito.genero) == 0)
                {
                    matrizPorGen[7][j7] = librito;
                    j7++;
                    val8++;
                }
                else if(strcmp("Romance", librito.genero) == 0)
                {
                    matrizPorGen[8][j8] = librito;
                    j8++;
                    val9++;
                }
                else if(strcmp("Terror", librito.genero) == 0)
                {
                    matrizPorGen[9][j9] = librito;
                    j9++;
                    val10++;
                }
                else if(strcmp("Thriller", librito.genero) == 0)
                {
                    matrizPorGen[10][j10] = librito;
                    j10++;
                    val11++;
                }

                else
                {
                    matrizPorGen[11][j11] = librito;
                    j11++;
                    val12++;
                }
            }
        }
        fclose(archi);
    }
    else
    {
        printf("ERROR EN LA BASE DE DATOS");
    }
    int validos=0;

    singenero=mostrarmatriz(matrizPorGen,0,val1);
    if(singenero==0)
    {
        strcpy(singeneroarr[i], "Autoayuda");
        i++;
        validos++;
    }
    singenero=mostrarmatriz(matrizPorGen,1,val2);
    if(singenero==0)
    {
        strcpy(singeneroarr[i], "Biografia");
        i++;
        validos++;
    }
    singenero=mostrarmatriz(matrizPorGen,2,val3);
    if(singenero==0)
    {
        strcpy(singeneroarr[i], "Ciencia ficcion");
        i++;
        validos++;
    }
    singenero=mostrarmatriz(matrizPorGen,3,val4);
    if(singenero==0)
    {
        strcpy(singeneroarr[i], "Cientifico");
        i++;
        validos++;
    }
    singenero=mostrarmatriz(matrizPorGen,4,val5);
    if(singenero==0)
    {
        strcpy(singeneroarr[i], "Historico");
        i++;
        validos++;
    }
    singenero=mostrarmatriz(matrizPorGen,5,val6);
    if(singenero==0)
    {
        strcpy(singeneroarr[i], "Infantil");
        i++;
        validos++;
    }
    singenero=mostrarmatriz(matrizPorGen,6,val7);
    if(singenero==0)
    {
        strcpy(singeneroarr[i], "Novela");
        i++;
        validos++;
    }
    singenero=mostrarmatriz(matrizPorGen,7,val8);
    if(singenero==0)
    {
        strcpy(singeneroarr[i], "Policial");
        i++;
        validos++;
    }
    singenero=mostrarmatriz(matrizPorGen,8,val9);
    if(singenero==0)
    {
        strcpy(singeneroarr[i], "Romance");
        i++;
        validos++;
    }
    singenero=mostrarmatriz(matrizPorGen,9,val10);
    if(singenero==0)
    {
        strcpy(singeneroarr[i], "Terror");
        i++;
        validos++;
    }
    singenero=mostrarmatriz(matrizPorGen,10,val11);
    if(singenero==0)
    {
        strcpy(singeneroarr[i], "Thriller");
        i++;
        validos++;
    }
    singenero=mostrarmatriz(matrizPorGen,11,val12);
    if(singenero==0)
    {
        strcpy(singeneroarr[i], "'Otro'");
        i++;
        validos++;
    }
    if(validos>1)
    {
        printf("\nDe estos generos aun no hay libros cargados: ");

        for(i=0; i<validos; i++)
        {

            printf("%s ",singeneroarr[i]);
        }
    }
    printf("\nPorfavor, ");
}

int mostrarmatriz(libro matrizPorGen[12][100],int num,int val)
{
    int j=0;
    char genero[100];
    strcpy(genero, valGen(num));

    if(val!=0)
    {
        printf("\nEstos son los libros del genero: %s\n\n", genero);
        puts("===================");
        for ( j = 0; j < val; j++)
        {
            if(num!=11)
            {
                printf("Numero de libro: %d\n", matrizPorGen[num][j].numLib);
                printf("Numero de paginas: %d\n", matrizPorGen[num][j].paginas);
                printf("Autor: %s\n", matrizPorGen[num][j].autor);
                printf("Titulo: %s\n", matrizPorGen[num][j].titulo);
                puts("===================");
            }
            else
            {
                printf("Numero de libro: %d\n", matrizPorGen[num][j].numLib);
                printf("Numero de paginas: %d\n", matrizPorGen[num][j].paginas);
                printf("Genero: %s\n", matrizPorGen[num][j].genero);
                printf("Autor: %s\n", matrizPorGen[num][j].autor);
                printf("Titulo: %s\n", matrizPorGen[num][j].titulo);
                puts("===================");
            }
        }
    }
    else
    {
        return 0;
    }
    return 1;
}

int valGen(int num)
{
    switch(num)
    {
    case 0:
        return "Autoayuda";
        break;
    case 1:
        return "Biografia";
        break;
    case 2:
        return "Ciencia ficcion";
        break;
    case 3:
        return "Cientifico";
        break;
    case 4:
        return "Historico";
        break;
    case 5:
        return "Infantil";
        break;
    case 6:
        return "Novela";
        break;
    case 7:
        return "Policial";
        break;
    case 8:
        return "Romance";
        break;
    case 9:
        return "Terror";
        break;
    case 10:
        return "Thriller";
        break;
    case 11:
        return "'Otro'";
        break;
    }
    return 0;
}

void elegirorden(num)
{
    libro libros[100];
    int orden = num;
    int i=0;
    FILE *archi;
    archi = fopen("Base_De_Datos_Bib.bin", "rb+");
    if (archi != NULL)
    {
        int numLibros = 0;
        while (fread(&libros[numLibros], sizeof(libro), 1, archi) == 1)
        {
            numLibros++;
        }

        if (orden == 1)
        {
            ordenamientoSeleccion(libros, numLibros);
            for (i=0; i<numLibros; i++)
            {
                puts("========================");
                printf("El numero de libro es: %d\n", libros[i].numLib);
                printf("El numero de paginas es: %d\n", libros[i].paginas);
                printf("El genero del libro es: %s\n", libros[i].genero);
                printf("El autor del libro es: %s\n", libros[i].autor);
                printf("El titulo del libro es: %s\n", libros[i].titulo);
                puts("========================");
            }
        }
        else if (orden == 0)
        {
            ordenamientoins(libros, numLibros);
            for (i=0; i<numLibros; i++)
            {
                puts("========================");
                printf("El numero de paginas es: %d\n", libros[i].paginas);
                printf("El numero de libro es: %d\n", libros[i].numLib);
                printf("El genero del libro es: %s\n", libros[i].genero);
                printf("El autor del libro es: %s\n", libros[i].autor);
                printf("El titulo del libro es: %s\n", libros[i].titulo);
                puts("========================");
            }
        }
        fclose(archi);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
    return 0;
}

void insertar(libro libros[], int i, libro dato)
{
    while (i >= 0 && dato.paginas < libros[i].paginas)
    {
        libros[i + 1] = libros[i];
        i--;
    }
    libros[i + 1] = dato;
}

void ordenamientoins(libro libros[], int numLibros)
{
    int i = 0;
    while (i < numLibros - 1)
    {
        insertar(libros, i, libros[i + 1]);
        i++;
    }
}

void ordenamientoSeleccion(libro libros[], int numLibros)
{
    int posmenor;
    libro aux;
    int i = 0;
    while (i < numLibros - 1)
    {
        posmenor = posicionMenor(libros, i, numLibros);
        aux = libros[posmenor];
        libros[posmenor] = libros[i];
        libros[i] = aux;
        i++;
    }
}

int posicionMenor(libro libros[], int pos, int numLibros)
{
    int menor = libros[pos].numLib;
    int posmenor = pos;
    int i = pos + 1;
    while (i < numLibros)
    {
        if (menor > libros[i].numLib)
        {
            menor = libros[i].numLib;
            posmenor = i;
        }
        i++;
    }
    return posmenor;
}

void ordenDeCarga()
{
    libro librito;
    int i=1;
    FILE *archi;
    archi = fopen("Base_De_Datos_Bib.bin", "rb");
    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&librito, sizeof(libro),1,archi);
            if(!feof(archi))
            {
                puts("========================");
                printf("Libro: %i \n",i);
                printf("El numero de libro es: %i ",librito.numLib);
                printf("\nEl numero de paginas es: %i",librito.paginas);
                printf("\nEl genero del libro es: %s",librito.genero);
                printf("\nEl autor del libro es: %s",librito.autor);
                printf("\nEl titulo del libro es: %s\n",librito.titulo);
                puts("========================");
                i++;
            }
        }
        fclose(archi);
    }
}

int cargaBaseDatos()
{
     libro librito;
    char eleccion='s';
    char eleccionCarga='s';
    int error=0;
   while(tolower(eleccionCarga=='s')){
    FILE *archi;
    archi = fopen("Base_De_Datos_Bib.bin", "ab");
    int flag=1;
    if(archi!=NULL)
    {
        while(eleccion=='s' || eleccion=='S' && error==0)
        {
            librito=cargaEstructuraLib(&flag);
            if(flag==1)
            {
                printf("%d",flag);
                fwrite(&librito, sizeof(libro),1,archi);
                system("cls");
                printf("Datos guardados \n");
                error=0;
                eleccion='n';
                sleep(1);
                system("cls");
            }
            else
            {
                printf("Volvera al menu en breves...\n");
                error=1;
                eleccion='n';
                sleep(3);
            }
        }

        fclose(archi);
    }
    printf("Presione s para continuar cargando libros \n");
   fflush(stdin);
   scanf("%c", &eleccionCarga);
   if(eleccionCarga=='s'){
   eleccion='s';
   }
   system("cls");
   }
    return error;
}

libro cargaEstructuraLib(int*valorflagbase)
{
    libro librito;
    int num;
    int flag=0;
    int findeprograma=0;
    char eleccion='s';
    int errores=0;
    while(eleccion=='s')
    {
        while(flag==0 && eleccion=='s'||eleccion=='S')
        {
            printf("Ingrese el numero de libro: ");
            fflush(stdin);
            scanf("%d",&num);
            flag=verificarLibro(num);
            if(flag==0)
            {
                printf("Presione 's' si desea cargar nuevamente el numero de libro, 'n' si desea volver al menu ");
                fflush(stdin);
                scanf("%c", &eleccion);
                errores++;
                if(eleccion=='s'||eleccion=='S')
                {
                    printf("Le quedan %d intentos",4-errores);
                    sleep(2);
                    system("cls");
                }
                if(eleccion!='s'&&eleccion!='S'||errores==4)
                {
                    *valorflagbase=0;
                    return librito;
                }
            }
        }
        while(flag==1 && eleccion=='s'&& findeprograma==0)
        {
            librito.numLib=num;
            printf("\nIngrese el numero de paginas del libro: ");
            fflush(stdin);
            scanf("%d",&librito.paginas);
            findeprograma=libgenero(&librito.genero);
            if(findeprograma==0)
            {
                *valorflagbase=0;
                return librito;
            }
            else
            {
                system("cls");
                printf("Ingrese el numero de libro: %d",librito.numLib);
                printf("\nIngrese el numero de paginas del libro: %d",librito.paginas);
                printf("\nIngrese de que genero es el libro: %s",librito.genero);
                fflush(stdin);
                printf("\nIngrese el autor del libro: ");
                fflush(stdin);
                gets(librito.autor);
                printf("Ingrese el titulo del libro: ");
                fflush(stdin);
                gets(librito.titulo);
                eleccion='n';
                *valorflagbase=1;
                return librito;
            }
        }
    }

}

int libgenero(libro*librito)
{
    int opc;
    int flag=0;
    int cargaus=0;
    int i=0;
    char eleccion='s';
    while(flag==0&&i<4&&eleccion=='s'||eleccion=='S')
    {
        printf("\nIngrese de que genero es el libro:\n\n 1) Autoayuda\n\n 2) Biografia\n\n 3) Ciencia ficcion\n\n 4) Cientifico\n\n 5) Historico\n\n 6) Infantil\n\n 7) Novela\n\n 8) Policial\n\n 9) Romance\n\n 10) Terror\n\n 11) Thriller\n\n 12) Otro\n");
        printf("\nEscriba la opcion: ");
        fflush(stdin);
        scanf("%d",&opc);
        if(opc<1||opc>12)
        {
            system("cls");
            i++;
            printf("Ingreso '%d' que es un numero no valido. Porfavor ingrese un numero dentro del rango\nPresione S si desea seleccionar una opcion valida N para regresar al menu: ",opc);
            fflush(stdin);
            scanf("%c",&eleccion);
            system("cls");
            flag=0;
            if(eleccion=='s'||eleccion=='S'&&i<3)
            {
                printf("Intentos restantes: %d",4-i);
                sleep(2);
                system("cls");
            }
        }
        else
        {
            flag=1;
        }
    }
    if(flag==1)
    {
        switch(opc)
        {
        case 1:
            strcpy(librito, "Autoayuda");
            break;
        case 2:
            strcpy(librito, "Biografia");
            break;
        case 3:
            strcpy(librito, "Ciencia ficcion");
            break;
        case 4:

            strcpy(librito, "Cientifico");
            break;
        case 5:
            strcpy(librito, "Historico");
            break;
        case 6:
            strcpy(librito, "Infantil");
            break;
        case 7:
            strcpy(librito, "Novela");
            break;
        case 8:
            strcpy(librito, "Policial");
            break;
        case 9:
            strcpy(librito, "Romance");
            break;
        case 10:
            strcpy(librito, "Terror");
            break;
        case 11:
            strcpy(librito, "Thriller");
            break;
        case 12:
            printf("\nIngrese el genero manualmente: ");
            fflush(stdin);
            gets(librito);
            break;
        }
        return flag;
    }
    else
    {
        return flag;
    }
}

int verificarLibro(int num)
{
    libro librito;
    int flag=1;
    FILE *archi;
    archi = fopen("Base_De_Datos_Bib.bin", "rb");
    if(num>0)
    {
        if(archi!=NULL)
        {
            while(!feof(archi)&&flag==1)
            {
                fread(&librito, sizeof(libro),1,archi);
                if(!feof(archi))
                {

                    if (librito.numLib==num)
                    {
                        printf("El numero de libro pertenece a otro libro ya cargado.\n");
                        flag=0;
                    }
                }
            }
            fclose(archi);
        }
    }
    else
    {
        printf("El numero de libro no debe comenzar con 0.\n");
        flag=0;
    }
    return flag;
}

void busquedaLibro()
{
    int valor=0;
    valor=librosCargados();
    if(valor==0)
    {
        printf("ERROR, NO HAY LIBROS CARGADOS");
        sleep(2);
    }
    else
    {
        int j=0;
        libro librito;
        libro comparacion;
        int sim;
        int flag=0;
        int flagAux=0;
        int opc;
        int cargaUs;
        char eleccion='s';
        char elecF='n';
        int i=0;
        FILE *archi;
        while((elecF == 'n' || elecF == 'N') && j<3)
        {
            archi = fopen("Base_De_Datos_Bib.bin", "rb");
            printf("Seleccione sobre que desea realizar la busqueda:\n 1) Por numero de libro\n 2) Por cantidad de paginas\n 3) Por genero\nOPCION:");
            fflush(stdin);
            scanf("%d", &opc);
            if(opc != 1 && opc != 2 && opc != 3 && 3-j!=0)
            {
            printf("Ingreso un numero incorrecto\n");
            printf("Presione 'S' si desea volver a ingresar un numero, 'n' si desea volver al menu\n");
            fflush(stdin);
            scanf("%c", &elecF);
            if(elecF=='s' || elecF=='S'){
            j++;
            printf("Intentos restantes: %d\n",3-j);
            sleep(2);
            elecF = 'n';
            system("cls");
            }else{
            elecF = 'x';
            }
            }else{
            fflush(stdin);
            elecF = 's';
            }
            }
            if(j<3&&tolower(elecF)== 's'){
            comparacion=filtrobusqueda(opc);
            if(archi!=NULL)
            {
                flagAux=0;
                while(!feof(archi))
                {
                    fread(&librito, sizeof(libro),1,archi);

                    if(!feof(archi)&&flag==0)
                    {
                        switch(opc)
                        {

                        case 1:
                            if (librito.numLib==comparacion.numLib)
                            {
                                if(flagAux==0)
                                {
                                    printf("El libro esta cargado. \n");
                                    flagAux++;
                                }
                                mostrarLibro(librito);
                                sim=1;

                            }
                            else
                            {
                                flag=0;
                            }
                            break;
                        case 2:
                            if (librito.paginas==comparacion.paginas)
                            {
                                if(flagAux==0)
                                {
                                    printf("El libro esta cargado. \n");
                                    flagAux++;
                                }
                                mostrarLibro(librito);
                                sim=1;

                            }
                            else
                            {
                                flag=0;
                            }
                            break;
                        case 3:
                            if (strcasecmp(librito.genero,comparacion.genero)==0)
                            {
                                if(flagAux==0)
                                {
                                    printf("Los libros del genero %s son: \n",comparacion.genero);
                                    flagAux++;
                                }
                                mostrarLibro(librito);
                                sim=1;
                            }
                            else
                            {
                                flag=0;
                            }
                            break;
                        }

                    }
                }
                fclose(archi);
            }
            else
            {

                printf("ERROR EN LA BASE DE DATOS");
            }

            if(flagAux==0)
            {
                if(opc!=3)
                {
                    printf("No se ha podido encontrar ningun libro con la informacion proporcionada\nResultados similares (si es posible): \n");
                    sim=similares(opc,comparacion);
                }
                else
                {
                    do
                    {
                        printf("No se ha podido encontrar libros de ese genero. Indique porfavor si selecciono un genero de la lista (0) o si lo cargo ud (1).\n");
                        fflush(stdin);
                        scanf("%d",&cargaUs);
                        if (cargaUs != 0 && cargaUs != 1)
                        {
                            printf("Por favor, ingrese 0 si selecciono el genero o 1 si lo ingreso ud.\n");
                            fflush(stdin);
                            scanf("%d",&cargaUs);
                            i++;
                        }
                    }
                    while(cargaUs!=0 && cargaUs!=1 && i<1);

                    if(cargaUs==0)
                    {
                        printf("No hay libros cargados de ese genero.");
                        sim=1;
                    }
                    else if(cargaUs==1)
                    {
                        printf("Se buscaran resultados similares (si es posible): \n");
                        sim=similares(opc,comparacion);
                    }
                    else if(cargaUs!=0 && cargaUs!=1 )
                    {
                        printf("ERROR: NO SELECCIONO UNA OPCION VALIDA \n");
                        sim=1;
                    }
                }
            }
            if(sim==0)
            {
                printf("NO HAY ELEMENTOS SIMILARES \n");
            }
            printf("\nPresione 'S' si desea buscar otro libro. 'N' para volver al menu \n");
            fflush(stdin);
            scanf("%c", &eleccion);
            flag=0;
            sim=0;
            system("cls");
        }
    }

}

libro filtrobusqueda(int opc)
{
    libro filtro;
    switch(opc)
    {
    case 1:
        printf("Ingrese el numero de libro: \n");
        fflush(stdin);
        scanf("%d",&filtro.numLib);
        break;
    case 2:
        printf("Ingrese el numero de paginas: \n");
        fflush(stdin);
        scanf("%d",&filtro.paginas);
        break;
    case 3:
        libgenero(&filtro.genero);
        system("cls");
        printf("El genero es: %s\n", filtro.genero);
        sleep(3);
        system("cls");
        break;
    }
    return filtro;
}

void mostrarLibro(libro librito)
{
    puts("==========================================");
    printf("Numero de libro: %d\n", librito.numLib);
    printf("Cantidad de paginas: %d\n", librito.paginas);
    printf("Genero: %s\n", librito.genero);
    printf("Autor: %s\n", librito.autor);
    printf("Titulo: %s\n", librito.titulo);
    puts("==========================================");
}
int similares(int opc, libro comparacion)
{
    libro librito;
    int i = 0;
    FILE *archi;
    archi = fopen("Base_De_Datos_Bib.bin", "rb");
    int simil=0;
    if (archi != NULL)
    {
        while (!feof(archi) && i < 3)
        {
            fread(&librito, sizeof(libro), 1, archi);
            if (!feof(archi))
            {
                switch (opc)
                {
                case 1:
                    if (abs(librito.numLib - comparacion.numLib) <= 50)
                    {
                        mostrarLibro(librito);
                        i++;
                        simil=1;
                    }
                    break;
                case 2:
                    if (abs(librito.paginas - comparacion.paginas) <= 100)
                    {
                        mostrarLibro(librito);
                        i++;
                        simil=1;
                    }
                    break;
                case 3:
                    strlwr(librito.genero);
                    strlwr(comparacion.genero);
                    if (strstr(librito.genero, comparacion.genero) != NULL || strstr(comparacion.genero, librito.genero) != NULL)
                    {
                        mostrarLibro(librito);
                        i++;
                        simil = 1;
                    }
                    break;
                }
            }
        }
        fclose(archi);
    }
    else
    {
        printf("Error en la base de datos.\n");
    }
    return simil;
}

int librosCargados()
{
    int contador=0;
    FILE *archi;
    archi = fopen("Base_De_Datos_Bib.bin", "rb");
    if(archi==NULL)
    {
        printf("ERROR EN LA BASE DE DATOS\n");
    }
    else
    {
        fseek(archi,0,SEEK_END);
        contador = ftell(archi)/sizeof(libro);
        fseek(archi,0,SEEK_SET);
    }
    fclose(archi);
    return contador;
}

void juego()
{
    int valor=0;
    valor=librosCargados();
    int inicJ=0;
    char Elecjugar;
    if(valor<=0)
    {
        printf("No hay libros cargados, no es posible jugar. Porfavor ingrese mas libros \n");
        inicJ=0;
    }
    else if(valor==1)
    {
        printf("Hay un solo libro cargado, no es posible jugar. Porfavor ingrese mas libros \n");
        inicJ=0;
    }
    else if(valor>1 && valor<5)
    {
        printf("Hay pocos libros cargados, la experiencia de juego no sera la mejor. Porfavor presione 's' para jugar igual 'n' para ingresar libros \n");
        printf("%d",valor);
        fflush(stdin);
        scanf("%c",&Elecjugar);
        if(Elecjugar=='s')
        {
            inicJ=1;
        }
        else
        {
            inicJ=0;
        }
    }
    else
    {
        inicJ=1;
    }
    if(inicJ==1)
    {
        printf("Este juego le mostrara una pila de libros. Debera recordarla, para luego saber cual libro ha desaparecido.\n");
        system("pause");
        system("cls");
        printf("El sistema de puntos es: 100 puntos si aciertas, 50 si el numero se encuentra muy cerca, 15 si se encuentra cerca y 0 si se encuentra lejos\n");
        system("pause");
        system("cls");
        Pila numLib;
        inicpila(&numLib);
        int eliminado=0;
        int arrNumLib[100];
        int sumapuntos=0;
        int puntajetotal=0;
        int dif;
        char jugar='s';
        char cambdif='s';
        FILE *archi;
        archi = fopen("Base_De_Datos_Bib.bin", "rb");
        if (archi != NULL)
        {
            int validos=arrayNumL(arrNumLib);
            while(jugar=='s')
            {
                while(dif!=1&&dif!=2&&dif!=3)
                {
                    printf("Selecciona la dificultad:\n 1) Dificil\n 2) Medio\n 3) Facil\n");
                    fflush(stdin);
                    scanf("%d",&dif);
                    if(dif!=1&&dif!=2&&dif!=3)
                    {
                        printf("\nSeleccione una dificultad valida.");
                        sleep(2);
                    }
                    system("cls");
                    cambdif='n';
                }
                while(cambdif=='n'||cambdif=='N')
                {
                    pilaNumL(&numLib,arrNumLib,validos);
                    printf("RECUERDA ESTA PILA: \n");
                    mostrar(&numLib);
                    contadorSeg(dif);
                    srand(time(NULL));
                    if (validos>10)
                    {
                        eliminado = rand()%10+1;
                    }
                    else
                    {
                        eliminado=rand()%validos+1;
                    }
                    sumapuntos = juegoiniciado(&numLib,eliminado);
                    puntajetotal=puntajetotal+sumapuntos;
                    system("pause");
                    system("cls");
                    printf("Desea jugar otra ronda?: S/N\n");
                    fflush(stdin);
                    scanf("%c",&jugar);
                    if(jugar=='s'||jugar=='S')
                    {
                        printf("Desea cambiar la dificultad?: S/N\n");
                        fflush(stdin);
                        scanf("%c",&cambdif);
                        if(cambdif=='s'||cambdif=='S')
                        {
                            dif=0;
                        }
                        else
                        {
                            dif=dif;
                        }
                    }
                    else
                    {
                        jugar='n';
                        cambdif='s';
                    }
                    system("cls");
                }
            }

            printf("El puntaje final obtenido es... %d \n", puntajetotal);
        }
        else
        {
            printf("ERROR EN LA BASE DE DATOS. VERIFIQUE QUE EL SISTEMA TENGA LIBROS CARGADOS\n");
            return 0;
        }
    }
}

int arrayNumL(int arr[])
{
    libro librito;
    int i=0;
    FILE *archi;
    archi = fopen("Base_De_Datos_Bib.bin", "rb");
    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&librito, sizeof(libro),1,archi);
            if(!feof(archi))
            {

                arr[i]=librito.numLib;
                i++;

            }
        }
        fclose(archi);
    }

    return i;
}

void pilaNumL(Pila*pilita, int arr[],int validos)
{
    Pila descarte;
    inicpila(&descarte);
    while(!pilavacia(pilita))
    {
        apilar(&descarte,desapilar(pilita));
    }
    int aux[10];
    int aux2[validos];
    int maxnum=10;
    int numeroPila;
    int indice;
    int flag=0;
    srand(time(NULL));
    int i=0;
    int j=0;
    if(validos>=10)
    {
        while(i<10)
        {
            indice=rand()%validos;
            numeroPila=arr[indice];
            flag=0;
            for (j = 0; j < i; j++)
            {
                if (aux[j] == numeroPila)
                {
                    flag = 1;
                    break;
                }
            }

            if (flag == 0)
            {
                aux[i] = numeroPila;
                apilar(pilita, numeroPila);
                i++;
            }
        }
    }

    else
    {
        while(i<validos)
        {
            indice=rand()%validos;
            numeroPila=arr[indice];
            flag=0;
            for (j = 0; j < i; j++)
            {
                if (aux2[j] == numeroPila)
                {
                    flag = 1;
                    break;
                }
            }

            if (flag == 0)
            {
                aux2[i] = numeroPila;
                apilar(pilita, numeroPila);
                i++;
            }
        }

    }
}

int juegoiniciado(Pila*pilita,int eliminado)
{
    int i=0;
    int numLE;
    int numUs;
    Pila aux;
    inicpila(&aux);
    Pila aux2;
    inicpila(&aux2);
    printf("ELIMINADO %d\n",eliminado);
    while(i<eliminado)
    {
        numLE=tope(pilita);
        apilar(&aux,desapilar(pilita));
        i++;
    }
    apilar(&aux2,desapilar(&aux));

    while(!pilavacia(&aux))
    {
        apilar(pilita,desapilar(&aux));
    }
    printf("PILA NUEVA: \n");
    mostrar(pilita);
    printf("Que numero de libro se ha eliminado?\n");
    fflush(stdin);
    scanf("%d",&numUs);

    if(numLE==numUs)
    {
        printf("GANASTE\n");
    }
    else
    {
        printf("PERDISTE, EL NUMERO ERA: %d\n", numLE);
    }
    int puntaje=puntos(numLE,numUs);
    printf("Sumaste: %d puntos\n", puntaje);
    return puntaje;
}

void contadorSeg(int dif)
{
    int segundos;
    if(dif==1)
    {
        segundos=5;
    }
    else if(dif==2)
    {
        segundos=10;
    }
    else
    {
        segundos=20;
    }
    int i = segundos;
    for ( i; i >= 0; i--)
    {
        printf("%d...", i);
        sleep(1);
    }
    system("cls");
}

int puntos(int numM,int numUs)
{
    int diferencia = abs(numM - numUs);
    int puntos=0;

    if (diferencia == 0)
    {
        puntos += 100;
    }
    else if (diferencia <= 50)
    {
        puntos += 50;
    }
    else if (diferencia <= 100)
    {
        puntos += 15;
    }
    else
    {
        puntos +=0;
    }
    return puntos;
}

