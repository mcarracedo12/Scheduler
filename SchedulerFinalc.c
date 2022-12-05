#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct proceso
{
    int procesador;
    int id_proceso;
    int prioridad;
    char estado[10];
} proceso;

proceso *scheduling[10];

void asignarEstado(proceso *proc);        // Asigna siguiente Estado
void ingresaProceso();                    // Ingresa el proceso al scheduler en el primer espacio que encuentre
int terminaProceso(proceso *proc, int i); // Quita el proceso de la cola y retorna el lugar liberado
void recorreCola();                       // recorrre los procesos de la cola , haciendo el cambio de estado de los mismos
void mostrarScheduler();                  // Lista los procesos de la cola
int contadorProceso = 0;

// retorna 0 si es prioridad mas baja
//  retorno 1 si no lo es
int prioridad_baja(proceso *p)
{
    for (int x = 0; x < 10; x++)
    {
        if (scheduling[x] != NULL && strcmp(scheduling[x]->estado, "Listo") == 0)
        {
            if (p->estado > scheduling[x]->estado)
                return 1;
        }
    }
    return 0;
}

int p1 = 1; // procesadores
int p2 = 2;

int main()
{
    for (int i = 0; i < 10; i++)
    {
        scheduling[i] = NULL;
    }
    ingresaProceso();
    ingresaProceso();
    ingresaProceso();
    mostrarScheduler();
    recorreCola();
    recorreCola();
    mostrarScheduler();
    ingresaProceso();
    ingresaProceso();
    mostrarScheduler();
    recorreCola();
    mostrarScheduler();
    recorreCola();
    mostrarScheduler();
    return EXIT_SUCCESS;
}

void ingresaProceso()
{
    for (int i = 0; i < 10; i++)
    {
        if (scheduling[i] == NULL)
        {
            scheduling[i] = (proceso *)malloc(sizeof(proceso));
            scheduling[i]->id_proceso = rand() % 10;
            scheduling[i]->procesador = 0;
            scheduling[i]->prioridad = contadorProceso++;
            strcpy((*(scheduling + i))->estado, "Nuevo");
            return;
        }
    }
    printf("No hay espacio para otro proceso.. please wait...\n");
}

void mostrarScheduler()
{

    for (int i = 0; i < 10; i++)
    {
        if (scheduling[i] != NULL)
        {
            printf("%d %d %d %s \n", scheduling[i]->id_proceso, scheduling[i]->prioridad, scheduling[i]->procesador, scheduling[i]->estado);
        }
        else
        {
            printf("Aca no hay proceso en posicion %d\n", i);
        }
    }
    printf("\n");
}

void asignarEstado(proceso *proc)
{
    char *estado = proc->estado;
    if (strcmp(estado, "Nuevo") == 0)
    {
        strcpy(estado, "Listo");
        return;
    }

    if (strcmp(estado, "Listo") == 0)
    {

        if (p1 == 1)
        {
            strcpy(estado, "Corriendo");
            proc->procesador = 1;
            p1 = 0;
            return;
        }
        else if (p2 == 2)
        {
            strcpy(estado, "Corriendo");
            proc->procesador = 2;
            p2 = 0;
            return;
        }
        else
        {
            return;
        }
    }

    if (strcmp(estado, "Corriendo") == 0)
    {
        strcpy(estado, "Terminado");
        if (proc->procesador == 1)
        {
            p1 = 1;
        }
        else
        {
            p2 = 2;
        }
        return;
    }
    if (proc == NULL)
    {
        printf("Aca no hay proceso para asignarle estado");
    }
}

int terminaProceso(proceso *proc, int i)
{

    if (proc != NULL)
    {
        if (strcmp(proc->estado, "Terminado") == 0)
        {
            free(proc);
            scheduling[i] = NULL;
        }
    }
    return 0;
}

void recorreCola()
{
    for (int i = 0; i < 10; i++)
    {
        if (scheduling[i] != NULL)
        {
            if (strcmp(scheduling[i]->estado, "Terminado") == 0)
            {
                terminaProceso(scheduling[i], i);
            }
            else if (strcmp(scheduling[i]->estado, "Corriendo") == 0)
            {
                asignarEstado(scheduling[i]);
            }
            else if (strcmp(scheduling[i]->estado, "Listo") == 0)
            {
                int ubicacion;
                if (prioridad_baja(scheduling[i]) == 0)
                {
                    ubicacion = i;
                    asignarEstado(scheduling[ubicacion]);
                }
            }
            else if (strcmp(scheduling[i]->estado, "Nuevo") == 0)
            {
                asignarEstado(scheduling[i]);
            }
        }
    }
}
