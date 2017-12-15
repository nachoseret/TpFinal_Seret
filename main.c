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
	int agendaSize = 0;
	int op = 0;
	while(1){
		clear();
		printf("Acciones:\n1 - Cargar agenda de archivo\n2 - Nuevo contacto\n3 - Buscar contacto\n4 - Eliminar contacto\n5 - Editar contacto\n6 - Mostrar contactos\n7- Guardar agenda en archivo\n8 - Salir\n");
		scanf("%d",&op);
		switch(op){
			case 1:
				clear();
				agendaSize = cargarAgenda(&agenda);
				pause();
			break;
			case 2:
				clear();
				agendaSize = nuevoContacto(&agenda, agendaSize);
				pause();
			break;
			case 3:
				clear();
				buscarContacto(agenda, agendaSize);
				pause();
			break;
			case 4:
				clear();
				agendaSize = eliminarContacto(&agenda, agendaSize);
				pause();
			break;
			case 5:
				clear();
				editarContacto(agenda, agendaSize);
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

	return 0;
}