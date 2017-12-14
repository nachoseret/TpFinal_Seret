#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Representamos a un contacto como una estructura Contacto
// que consta de cuatro punteros a char que representan
// nombre, apellido, domicilio y telefono respectivamente
// y una variable de tipo int que representa la edad.
typedef struct contacto{
	char * nombre;
	char * apellido;
	char * domicilio;
	char * telefono;
	int edad;
}Contacto;

void pause(){
	printf("Presione [Enter] para volver al menu . . .");
	getchar();
	getchar();
}

void nuevoContacto(Contacto ** agenda, int agendaSize){

	Contacto * nuevaAgenda = realloc((*agenda), (agendaSize+1)*sizeof(Contacto));

	if(nuevaAgenda==NULL){
		printf("Error realocando memoria.");
		return;
	}

	char * buffer = malloc(sizeof(char)*300);
	printf("Nombre: ");
	scanf("%s", buffer);
	nuevaAgenda[agendaSize].nombre = malloc(sizeof(char)*(strlen(buffer)+1));
	strcpy(nuevaAgenda[agendaSize].nombre, buffer);

	printf("Apellido: ");
	scanf("%s", buffer);
	nuevaAgenda[agendaSize].apellido = malloc(sizeof(char)*(strlen(buffer)+1));
	strcpy(nuevaAgenda[agendaSize].apellido, buffer);

	printf("Domicilio: ");
	scanf("%s", buffer);
	nuevaAgenda[agendaSize].domicilio = malloc(sizeof(char)*(strlen(buffer)+1));
	strcpy(nuevaAgenda[agendaSize].domicilio, buffer);

	printf("Telefono: ");
	scanf("%s", buffer);
	nuevaAgenda[agendaSize].telefono = malloc(sizeof(char)*(strlen(buffer)+1));
	strcpy(nuevaAgenda[agendaSize].telefono, buffer);

	printf("Edad: ");
	scanf("%d", &(nuevaAgenda[agendaSize].edad));

	(*agenda) = nuevaAgenda;
	//free(nuevaAgenda);
}

int cargarAgenda(Contacto ** agenda){

	char * buffer = malloc(sizeof(char)*300);
	printf("Nombre del archivo: ");
	scanf("%s",buffer);

	FILE *entrada;
    entrada = fopen(buffer, "r");

    if(entrada==NULL){
    	printf("El archivo no ha sido encontrado.\n");
    	pause();
    	return 0;
    }

    int agendaSize, i;
    fscanf(entrada, "%d", &agendaSize);

	Contacto * nuevaAgenda = realloc((*agenda), (agendaSize+1)*sizeof(Contacto));

	if(nuevaAgenda==NULL){
		printf("Error realocando memoria.");
		pause();
		return 0;
	}

	for(i=0; i<agendaSize; i++){
		fscanf(entrada, "%s", buffer);
		nuevaAgenda[i].nombre = malloc(sizeof(char)*(strlen(buffer)+1));
		strcpy(nuevaAgenda[i].nombre, buffer);
		printf("%s\n", nuevaAgenda[i].nombre );

		fscanf(entrada, "%s", buffer);
		nuevaAgenda[i].apellido = malloc(sizeof(char)*(strlen(buffer)+1));
		strcpy(nuevaAgenda[i].apellido, buffer);

		fscanf(entrada, "%s", buffer);
		nuevaAgenda[i].domicilio = malloc(sizeof(char)*(strlen(buffer)+1));
		strcpy(nuevaAgenda[i].domicilio, buffer);

		fscanf(entrada, "%s", buffer);
		nuevaAgenda[i].telefono = malloc(sizeof(char)*(strlen(buffer)+1));
		strcpy(nuevaAgenda[i].telefono, buffer);

		fscanf(entrada ,"%d", &(nuevaAgenda[i].edad));
	}

	free(buffer);
	fclose(entrada);
	(*agenda) = nuevaAgenda;
	free(nuevaAgenda);
	return agendaSize;
}

void buscarContacto(Contacto * agenda, int agendaSize){
	int i;
	char * nombre = malloc(sizeof(char)*300);
	char * apellido = malloc(sizeof(char)*300);
	printf("Nombre: ");
	scanf("%s",nombre);
	printf("Apellido: ");
	scanf("%s",apellido);
	for(i=0; i<agendaSize; i++){
		if(strcmp(agenda[i].nombre, nombre)==0){
			if(strcmp(agenda[i].apellido, apellido)==0){
				printf("%s %s - Dom: %s - Tel: %s - Edad: %d\n", agenda[i].nombre, agenda[i].apellido, agenda[i].domicilio, agenda[i].telefono, agenda[i].edad);
				return;
			}
		}
	}
	printf("%s %s no esta agendado.", nombre, apellido);
	free(nombre);
	free(apellido);
}

void mostrarAgenda(Contacto * agenda, int agendaSize){

	if(agenda==NULL){
		printf("No hay contactos para mostrar.");
		return;
	}

	int i;
	for(i=0;i<agendaSize;i++){
		printf("%s %s - Dom: %s - Tel: %s - Edad: %d\n",agenda[i].nombre, agenda[i].apellido, agenda[i].domicilio, agenda[i].telefono, agenda[i].edad);
	}
}






