// TP Final - Prog. II
// Ignacio Seret

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.c"

// clear : None -> None
// Limpia la pantalla.
void clear(){
	system("clear"); // Cambiar clear por cls si se quiere correrlo en Windows
}

int main()
{
	// Menu principal
	clear();
	Contacto * agenda = malloc(sizeof(Contacto));
	int agendaSize = 0, op = 0;
	char * nombre = malloc(sizeof(char)*300);
	char * apellido = malloc(sizeof(char)*300);
	while(1){
		clear();
		printf("Acciones:\n1 - Cargar agenda de archivo\n2 - Nuevo contacto\n3 - Buscar contacto\n4 - Eliminar contacto\n5 - Editar contacto\n6 - Mostrar contactos\n7 - Guardar agenda en archivo\n8 - Salir\n");
		scanf("%d",&op);
		switch(op){
			case 1:
				clear();
				agendaSize = cargarAgenda(&agenda);
				pause();
			break;
			case 2:
				clear();
				Contacto * temp;
				temp = malloc(sizeof(Contacto));
				printf("Nuevo contacto\n");
				(*temp) = ingresoDatos();
				agendaSize = nuevoContacto(&agenda, agendaSize, (*temp));
				free(temp);
				pause();
			break;
			case 3:
				clear();
				printf("Buscar contacto\nNombre: ");
				scanf(" %[^\t\n]s",nombre);
				printf("Apellido: ");
				scanf(" %[^\t\n]s",apellido);
				op = buscarContacto(agenda, agendaSize, nombre, apellido);
				if(op>=0){
					mostrarContacto(agenda[op]);
					pause();
					break;
				}
				printf("%s %s no esta agendado.\n", nombre, apellido);
				pause();
			break;
			case 4:
				clear();
				printf("Eliminar contacto\nNombre: ");
				scanf(" %[^\t\n]s",nombre);
				printf("Apellido: ");
				scanf(" %[^\t\n]s",apellido);
				op = buscarContacto(agenda, agendaSize, nombre, apellido);
				if(op>=0){
					agendaSize = eliminarContacto(&agenda, agendaSize, op);
					printf("%s %s ha sido eliminado.\n", nombre, apellido);
					pause();
					break;
				}
				printf("%s %s no esta agendado.\n", nombre, apellido);
				pause();
			break;
			case 5:
				clear();
				printf("Editar contacto\nNombre: ");
				scanf(" %[^\t\n]s",nombre);
				printf("Apellido: ");
				scanf(" %[^\t\n]s",apellido);
				op = buscarContacto(agenda, agendaSize, nombre, apellido);
				if(op>=0){
					mostrarContacto(agenda[op]);
					printf("Ingrese '-' en nombre, apellido, domicilio y/o telefono\npara dejarlo sin modificar.\n");
					temp = malloc(sizeof(Contacto));
					(*temp) = ingresoDatos();
					editarContacto(agenda, agendaSize, op, (*temp));
					free(temp);
					pause();
					break;
				}
				printf("%s %s no esta agendado.\n", nombre, apellido);
				pause();
			break;
			case 6:
				clear();
				mostrarAgenda(agenda, agendaSize);
				pause();
			break;
			case 7:
				clear();
				guardarAgenda(agenda, agendaSize);
				pause();
			break;
			case 8:
				free(agenda);
				exit(0);
			break;
		}
	}
	free(nombre);
	free(apellido);
	return 0;
}