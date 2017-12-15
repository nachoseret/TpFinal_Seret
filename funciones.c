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

// pause : None -> None
// Muestra el mensaje "Presione [Enter] para volver al menu . . ." y espera a que el usuario lo haga
void pause(){
	printf("Presione [Enter] para volver al menu . . .");
	getchar();
	getchar();
}

// mostrarContacto : Contacto -> none
// Toma una estructura de tipo contacto e imprime por pantalla sus datos.
void mostrarContacto(Contacto x){
	printf("%s %s - Dom: %s - Tel: %s - Edad: %d\n",x.nombre, x.apellido, x.domicilio, x.telefono, x.edad);
}

// mostrarAgenda : Contacto * , int -> None
// Recibe un puntero a Contacto y la cantidad de los mismos en el espacio que apunta.
// Muestra todos los datos de los mismos, uno debajo del otro.
void mostrarAgenda(Contacto * agenda, int agendaSize){

	if(agenda==NULL||agendaSize==0){
		printf("No hay contactos para mostrar.\n");
		return;
	}

	int i;
	for(i=0;i<agendaSize;i++){
		mostrarContacto(agenda[i]);
	}
}

// ingresoDatos : None -> Contacto
// Pide al usuario por teclado el ingreso de los datos de un contacto y devuelve
// una estructura de tipo Contacto con esos datos.
Contacto ingresoDatos(){
	Contacto ingreso;

	char * buffer = malloc(sizeof(char)*300);
	printf("Nombre: ");
	scanf(" %[^\t\n]s",buffer);
	ingreso.nombre = malloc(sizeof(char)*(strlen(buffer)+1));
	strcpy(ingreso.nombre, buffer);

	printf("Apellido: ");
	scanf(" %[^\t\n]s",buffer);
	ingreso.apellido = malloc(sizeof(char)*(strlen(buffer)+1));
	strcpy(ingreso.apellido, buffer);

	printf("Domicilio: ");
	scanf(" %[^\t\n]s",buffer);
	ingreso.domicilio = malloc(sizeof(char)*(strlen(buffer)+1));
	strcpy(ingreso.domicilio, buffer);

	printf("Telefono: ");
	scanf(" %[^\t\n]s",buffer);
	ingreso.telefono = malloc(sizeof(char)*(strlen(buffer)+1));
	strcpy(ingreso.telefono, buffer);

	printf("Edad: ");
	scanf("%d", &(ingreso.edad));

	return ingreso;
}

// nuevoContacto : Contacto ** , int, Contacto -> int
// Toma un puntero a puntero Contacto, la cantidad de Contactos en ese espacio y el Contacto a agregar.
// Realoca la memoria para poder guardar el nuevo Contacto y lo guarda en la ultima posicion.
// En caso que realloc devuelva NULL, se muestra el mensaje "Error realocando memoria." y la funcion
// devuelve el tamano que la agenda tenia cuando se hizo el llamado. En caso exitoso, devuelve el tamano + 1.
int nuevoContacto(Contacto ** agenda, int agendaSize, Contacto ingreso){

	Contacto * nuevaAgenda = realloc((*agenda), (agendaSize+1)*sizeof(Contacto));

	if(nuevaAgenda==NULL){
		printf("Error realocando memoria.\n");
		return agendaSize;
	}

	nuevaAgenda[agendaSize].nombre = malloc(sizeof(char)*(strlen(ingreso.nombre)+1));
	strcpy(nuevaAgenda[agendaSize].nombre, ingreso.nombre);

	nuevaAgenda[agendaSize].apellido = malloc(sizeof(char)*(strlen(ingreso.apellido)+1));
	strcpy(nuevaAgenda[agendaSize].apellido, ingreso.apellido);

	nuevaAgenda[agendaSize].domicilio = malloc(sizeof(char)*(strlen(ingreso.domicilio)+1));
	strcpy(nuevaAgenda[agendaSize].domicilio, ingreso.domicilio);

	nuevaAgenda[agendaSize].telefono = malloc(sizeof(char)*(strlen(ingreso.telefono)+1));
	strcpy(nuevaAgenda[agendaSize].telefono, ingreso.telefono);

	nuevaAgenda[agendaSize].edad = ingreso.edad;

	(*agenda) = nuevaAgenda;
	return agendaSize+1;
}

// guardarAgenda : Contacto * , int -> None
// Toma un puntero a Contacto y el tamano de la agenda (cantidad de contactos). Pide por teclado
// el nombre del archivo a crear o editar y luego guarda los contactos en el mismo. La primera
// linea del archivo es el entero que corresponde a la cantidad de contactos (segundo argumento).
void guardarAgenda(Contacto * agenda, int agendaSize){

	if(agenda==NULL||agendaSize==0){
		printf("No hay contactos en la agenda.\n");
		return;
	}

	char * buffer = malloc(sizeof(char)*300);
	printf("Nombre del archivo: ");
	scanf("%s", buffer);

	FILE *salida = fopen(buffer, "wb");
	fprintf(salida, "%d\n", agendaSize);
	int i;
	for(i=0;i<agendaSize;i++){
		fprintf(salida,"%s\n%s\n%s\n%s\n%d\n",agenda[i].nombre, agenda[i].apellido, agenda[i].domicilio, agenda[i].telefono, agenda[i].edad);
	}

	printf("Se ha guardado la agenda en el archivo %s.\n",buffer);
	free(buffer);
	fclose(salida);

}

// cargarAgenda : Contacto ** -> int
// Recibe un puntero a puntero Contacto y pide por teclado el nombre del archivo a leer. Finalmente,
// aloca la memoria necesaria y guarda los contactos del archivo en el espacio alocado. Devuelve un
// entero que corresponte a la cantidad de contactos (el cual lee de la primera linea del archivo).
int cargarAgenda(Contacto ** agenda){

	char * buffer = malloc(sizeof(char)*300);
	printf("Nombre del archivo: ");
	scanf("%s", buffer);

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
		printf("Error realocando memoria.\n");
		pause();
		return 0;
	}

	for(i=0; i<agendaSize; i++){
		fscanf(entrada, " %[^\t\n]s", buffer);
		nuevaAgenda[i].nombre = malloc(sizeof(char)*(strlen(buffer)+1));
		strcpy(nuevaAgenda[i].nombre, buffer);

		fscanf(entrada, " %[^\t\n]s", buffer);
		nuevaAgenda[i].apellido = malloc(sizeof(char)*(strlen(buffer)+1));
		strcpy(nuevaAgenda[i].apellido, buffer);

		fscanf(entrada, " %[^\t\n]s", buffer);
		nuevaAgenda[i].domicilio = malloc(sizeof(char)*(strlen(buffer)+1));
		strcpy(nuevaAgenda[i].domicilio, buffer);

		fscanf(entrada, " %[^\t\n]s", buffer);
		nuevaAgenda[i].telefono = malloc(sizeof(char)*(strlen(buffer)+1));
		strcpy(nuevaAgenda[i].telefono, buffer);

		fscanf(entrada ,"%d", &(nuevaAgenda[i].edad));
	}

	free(buffer);
	fclose(entrada);
	(*agenda) = nuevaAgenda;
	printf("La carga ha sido realizada con exito.\n");
	return agendaSize;
}

// buscarContacto : Contacto * , int, char *, char * -> None
// Recibe un puntero a Contacto, la cantidad de Contactos que hay en ese espacio y el
// nombre y apellido a buscar, itera sobre los contactos hasta encontrar el nombre y
// apellido deseados. En caso de encontrarlo, devuelve la posicion. Caso contrario,
// devuelve -1.
int buscarContacto(Contacto * agenda, int agendaSize, char * nombre, char * apellido){
	int i;
	for(i=0; i<agendaSize; i++){
		if(strcmp(agenda[i].nombre, nombre)==0){
			if(strcmp(agenda[i].apellido, apellido)==0){
				return i;
			}
		}
	}
	return -1;
}

// eliminarContacto : Contacto ** , int, int -> int
// Toma un puntero a puntero Contacto, la cantidad de Contactos en ese espacio y la posicion del contacto
// a eliminar. Copia el contacto de la ultima posicion al lugar del que se quiere eliminar, luego realoca
// el espacio al tamano original - 1 y devuelve ese valor. En caso de error al realocar memoria, devuelve
// tamano original e imprime un mensaje informando al usuario.
int eliminarContacto(Contacto ** agenda, int agendaSize, int pos){
	if((*agenda)!=NULL&&agendaSize!=0){

		free((*agenda)[pos].nombre);
		free((*agenda)[pos].apellido);
		free((*agenda)[pos].domicilio);
		free((*agenda)[pos].telefono);

		if(agendaSize!=1 && (agendaSize-1)!=pos){
			(*agenda)[pos].nombre = malloc(sizeof(char)*(strlen((*agenda)[agendaSize-1].nombre)+1));
			(*agenda)[pos].apellido = malloc(sizeof(char)*(strlen((*agenda)[agendaSize-1].apellido)+1));
			(*agenda)[pos].domicilio = malloc(sizeof(char)*(strlen((*agenda)[agendaSize-1].domicilio)+1));
			(*agenda)[pos].telefono = malloc(sizeof(char)*(strlen((*agenda)[agendaSize-1].telefono)+1));
			strcpy((*agenda)[pos].nombre, (*agenda)[agendaSize-1].nombre);
			strcpy((*agenda)[pos].apellido, (*agenda)[agendaSize-1].apellido);
			strcpy((*agenda)[pos].domicilio, (*agenda)[agendaSize-1].domicilio);
			strcpy((*agenda)[pos].telefono, (*agenda)[agendaSize-1].telefono);
			(*agenda)[pos].edad = (*agenda)[agendaSize-1].edad;
		}	

		Contacto * nuevaAgenda = realloc((*agenda), (agendaSize-1)*sizeof(Contacto));

		if(nuevaAgenda==NULL){
			printf("Error realocando memoria.\n");
			pause();
			return agendaSize;
		}

		(*agenda) = nuevaAgenda;
		return agendaSize-1;
	}

	return agendaSize;
}


// editarContacto : Contacto * , int, int, Contacto -> int
// Toma un puntero a Contacto, la cantidad de Contactos en ese espacio, la posicion del contacto
// a editar y una estructura Contacto con los datos nuevos. Si el campo nuevo (menos la edad) tiene un
// "-", conserva el dato original. Sino, reemplaza el original por el campo nuevo.
void editarContacto(Contacto * agenda, int agendaSize, int pos, Contacto nuevo){

	if(strcmp(nuevo.nombre,"-")!=0){
		free(agenda[pos].nombre);
		agenda[pos].nombre = malloc(sizeof(char)*(strlen(nuevo.nombre)+1));
		strcpy(agenda[pos].nombre, nuevo.nombre);
	}

	if(strcmp(nuevo.apellido,"-")!=0){
		free(agenda[pos].apellido);
		agenda[pos].apellido = malloc(sizeof(char)*(strlen(nuevo.apellido)+1));
		strcpy(agenda[pos].apellido, nuevo.apellido);
	}

	if(strcmp(nuevo.domicilio,"-")!=0){
		free(agenda[pos].domicilio);
		agenda[pos].domicilio = malloc(sizeof(char)*(strlen(nuevo.domicilio)+1));
		strcpy(agenda[pos].domicilio, nuevo.domicilio);
	}

	if(strcmp(nuevo.telefono,"-")!=0){
		free(agenda[pos].telefono);
		agenda[pos].telefono = malloc(sizeof(char)*(strlen(nuevo.telefono)+1));
		strcpy(agenda[pos].telefono, nuevo.telefono);
	}

	agenda[pos].edad = nuevo.edad;
	
	return;
}