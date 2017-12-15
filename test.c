// TP Final - Prog. II
// Ignacio Seret

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "funciones.c"

void nuevoContactoTest(){
	int agendaSize = 0;
	Contacto * agenda = malloc(sizeof(Contacto));
	Contacto * temp = malloc(sizeof(Contacto));

	temp->nombre = malloc(sizeof(char)*6);
	temp->apellido = malloc(sizeof(char)*6);
	temp->domicilio = malloc(sizeof(char)*14);
	temp->telefono = malloc(sizeof(char)*10);

	strcpy(temp->nombre, "Nacho");
	strcpy(temp->apellido, "Seret");
	strcpy(temp->domicilio, "Necochea 1580");
	strcpy(temp->telefono, "153209825");
	temp->edad = 19;

	agendaSize = nuevoContacto(&agenda, agendaSize, (*temp));
	assert(agendaSize==1);

	strcpy(temp->nombre, "Jorge");
	strcpy(temp->apellido, "Monet");
	strcpy(temp->domicilio, "Montevideo 40");
	strcpy(temp->telefono, "123705825");
	temp->edad = 28;

	agendaSize = nuevoContacto(&agenda, agendaSize, (*temp));
	assert(agendaSize==2);

	assert(strcmp(agenda[0].nombre, "Nacho")==0);
	assert(strcmp(agenda[0].apellido,"Seret")==0);
	assert(strcmp(agenda[0].domicilio, "Necochea 1580")==0);
	assert(strcmp(agenda[0].telefono, "153209825")==0);
	assert(agenda[0].edad == 19);

	assert(strcmp(agenda[1].nombre, "Jorge")==0);
	assert(strcmp(agenda[1].apellido, "Monet")==0);
	assert(strcmp(agenda[1].domicilio, "Montevideo 40")==0);
	assert(strcmp(agenda[1].telefono, "123705825")==0);
	assert(agenda[1].edad == 28);

	printf("Los test de nuevoContacto pasaron.\n");
}

void buscarContactoTest(){
	int agendaSize = 0;
	Contacto * agenda = malloc(sizeof(Contacto));
	Contacto * temp = malloc(sizeof(Contacto));

	temp->nombre = malloc(sizeof(char)*6);
	temp->apellido = malloc(sizeof(char)*6);
	temp->domicilio = malloc(sizeof(char)*14);
	temp->telefono = malloc(sizeof(char)*10);

	strcpy(temp->nombre, "Nacho");
	strcpy(temp->apellido, "Seret");
	strcpy(temp->domicilio, "Necochea 1580");
	strcpy(temp->telefono, "153209825");
	temp->edad = 19;

	agendaSize = nuevoContacto(&agenda, agendaSize, (*temp));

	strcpy(temp->nombre, "Jorge");
	strcpy(temp->apellido, "Monet");
	strcpy(temp->domicilio, "Montevideo 40");
	strcpy(temp->telefono, "123705825");
	temp->edad = 28;

	agendaSize = nuevoContacto(&agenda, agendaSize, (*temp));

	assert(buscarContacto(agenda,agendaSize,"Nacho","Seret")==0);
	assert(buscarContacto(agenda,agendaSize,"Jorge","Monet")==1);
	assert(buscarContacto(agenda,agendaSize,"Giani","Cocino")==-1);

	printf("Los test de buscarContacto pasaron.\n");
}

void eliminarContactoTest(){
	int agendaSize = 0;
	Contacto * agenda = malloc(sizeof(Contacto));
	Contacto * temp = malloc(sizeof(Contacto));

	assert(eliminarContacto(&agenda, agendaSize, 2)==0);

	temp->nombre = malloc(sizeof(char)*6);
	temp->apellido = malloc(sizeof(char)*6);
	temp->domicilio = malloc(sizeof(char)*14);
	temp->telefono = malloc(sizeof(char)*10);

	strcpy(temp->nombre, "Nacho");
	strcpy(temp->apellido, "Seret");
	strcpy(temp->domicilio, "Necochea 1580");
	strcpy(temp->telefono, "153209825");
	temp->edad = 19;

	agendaSize = nuevoContacto(&agenda, agendaSize, (*temp));

	strcpy(temp->nombre, "Jorge");
	strcpy(temp->apellido, "Monet");
	strcpy(temp->domicilio, "Montevideo 40");
	strcpy(temp->telefono, "123705825");
	temp->edad = 28;

	agendaSize = nuevoContacto(&agenda, agendaSize, (*temp));

	agendaSize = eliminarContacto(&agenda, agendaSize, 0);
	assert(agendaSize==1);
	assert(strcmp(agenda[0].nombre, "Jorge")==0);
	assert(strcmp(agenda[0].apellido, "Monet")==0);
	assert(strcmp(agenda[0].domicilio, "Montevideo 40")==0);
	assert(strcmp(agenda[0].telefono, "123705825")==0);
	assert(agenda[0].edad == 28);

	agendaSize = eliminarContacto(&agenda, agendaSize, 0);
	assert(agendaSize==0);

	printf("Los test de eliminarContacto pasaron.\n");
}

void editarContactoTest(){
	int agendaSize = 0;
	Contacto * agenda = malloc(sizeof(Contacto));
	Contacto * temp = malloc(sizeof(Contacto));

	assert(eliminarContacto(&agenda, agendaSize, 2)==0);

	temp->nombre = malloc(sizeof(char)*6);
	temp->apellido = malloc(sizeof(char)*6);
	temp->domicilio = malloc(sizeof(char)*14);
	temp->telefono = malloc(sizeof(char)*10);

	strcpy(temp->nombre, "Nacho");
	strcpy(temp->apellido, "Seret");
	strcpy(temp->domicilio, "Necochea 1580");
	strcpy(temp->telefono, "153209825");
	temp->edad = 19;

	agendaSize = nuevoContacto(&agenda, agendaSize, (*temp));

	strcpy(temp->nombre, "Jorge");
	strcpy(temp->apellido, "Monet");
	strcpy(temp->domicilio, "Montevideo 40");
	strcpy(temp->telefono, "123705825");
	temp->edad = 28;

	agendaSize = nuevoContacto(&agenda, agendaSize, (*temp));
	
	strcpy(temp->nombre, "Rogelio Ladron");
	strcpy(temp->apellido, "Aguas");
	strcpy(temp->domicilio, "Marylebone Rd");
	strcpy(temp->telefono, "1746652649");
	temp->edad = 70;

	assert(strcmp(agenda[1].nombre, "Jorge")==0);
	assert(strcmp(agenda[1].apellido, "Monet")==0);
	assert(strcmp(agenda[1].domicilio, "Montevideo 40")==0);
	assert(strcmp(agenda[1].telefono, "123705825")==0);
	assert(agenda[1].edad == 28);

	editarContacto(agenda, agendaSize, 1, (*temp));

	assert(strcmp(agenda[1].nombre, "Rogelio Ladron")==0);
	assert(strcmp(agenda[1].apellido, "Aguas")==0);
	assert(strcmp(agenda[1].domicilio, "Marylebone Rd")==0);
	assert(strcmp(agenda[1].telefono, "1746652649")==0);
	assert(agenda[1].edad == 70);

	printf("Los test de editarContacto pasaron.\n");
}

int main(){
	nuevoContactoTest();
	buscarContactoTest();
	eliminarContactoTest();
	editarContactoTest();
	printf("Todos los test se pasaron con exito.\n");
}