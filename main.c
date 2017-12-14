// TP Final - Prog. II
// Ignacio Seret

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.c"

void clear(){
	system("clear"); // Cambiar clear por cls si se quiere correrlo en Windows
}

int main()
{
	// Menu principal
	clear();
	Contacto * agenda = malloc(sizeof(Contacto));
	int agendaSize = 0;
	int op = 0;
	while(1){
		clear();
		printf("Acciones:\n1 - Cargar agenda de archivo\n2 - Nuevo contacto\n3 - Buscar contacto\n4 - Eliminar contacto\n5 - Editar contacto\n6 - Mostrar contactos\n7 - Salir\n");
		scanf("%d",&op);
		switch(op){
			case 1:
				agendaSize = cargarAgenda(&agenda);
			break;
			case 2:
				nuevoContacto(&agenda, agendaSize);
				agendaSize+=1;
			break;
			case 3:
				buscarContacto(agenda, agendaSize);
				pause();
			break;
			case 6:
				clear();
				mostrarAgenda(agenda, agendaSize);
				pause();
			break;
			case 7:
				exit(0);
			break;
		}
	}

	return 0;
}