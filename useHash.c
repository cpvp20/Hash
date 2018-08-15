#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash.h"

int main(){

	//--------------------------------------------SPECS------------------------------------------------------------

	setbuf(stdout, 0);
	int m = 10;	//tamano del arreglo de la tabla hash

	typedef struct{		//para las llaves
		char * placa;
	}PlacaAuto;

	typedef struct{		//los valores.
		char * modelo;
		char * color;
	}Auto;

	int hashFunc (Type key, int m){
		PlacaAuto * p = (PlacaAuto*) key;
		char minValues[] = "AAA-00-000";
		int pesos[] = { 26, 26, 10, 10, 10, 10} ;

		int index = (p->placa[0] - minValues[0]) % m;
		for(int i = 1; i < 7; i++)
		{
			index = index * pesos[i-1];
			index = (index) % m;
			index += (p->placa[i] - minValues[i]) % m;
			index = (index) % m;
		}
		return index;
	}

	bool equalsFunc (Type key1, Type key2){
		PlacaAuto * k1 = (PlacaAuto*) key1;
		PlacaAuto * k2 = (PlacaAuto*) key2;
		return (strcmp(k1->placa, k2->placa) == 0);	//si son iguales, devuelve true, si no, devuelve false
	}

	void keyDestructor(Type key){
		PlacaAuto * k = (PlacaAuto*) key;
		free(k->placa);
	}

	void valueDestructor(Type value){
		Auto * v = (Auto*) value;
		free (v->modelo);
		free (v->color);
	}

	//--------------------------------------------NOW LETS TEST IT--------------------------------------------------

	Map myMap = map_create(m, hashFunc, equalsFunc, keyDestructor, valueDestructor);

	PlacaAuto p1; Auto a1;
	p1.placa = malloc(11);
	strcpy(p1.placa, "JJL-12-445");
	a1.modelo = malloc (8);
	strcpy(a1.modelo, "Beettle");
	a1.color = malloc(5);
	strcpy(a1.color, "azul");
	map_put(myMap, &p1, &a1);

	PlacaAuto p2; Auto a2;
	p2.placa = malloc(11);
	strcpy(p2.placa, "BBL-12-445");
	a2.modelo = malloc (16);
	strcpy(a2.modelo, "Beettle vintage");
	a2.color = malloc(6);
	strcpy(a2.color, "negro");
	map_put(myMap, &p2, &a2);

	PlacaAuto p3; Auto a3;
	p3.placa = malloc(11);
	strcpy(p3.placa, "BBL-18-445");
	a3.modelo = malloc (8);
	strcpy(a3.modelo, "Beettle");
	a3.color = malloc(13);
	strcpy(a3.color, "negro y azul");
	map_put(myMap, &p3, &a3);

	PlacaAuto p4; Auto a4;
	p4.placa = malloc(11);
	strcpy(p4.placa, "BBL-12-755");
	a4.modelo = malloc (8);
	strcpy(a4.modelo, "Beettle");
	a4.color = malloc(6);
	strcpy(a4.color, "baby blue");
	map_put(myMap, &p4, &a4);

	PlacaAuto p5; Auto a5;
	p5.placa = malloc(11);
	strcpy(p5.placa, "JAL-11-111");
	a5.modelo = malloc (7);
	strcpy(a5.modelo, "pickup");
	a5.color = malloc(6);
	strcpy(a5.color, "fiusha");
	map_put(myMap, &p5, &a5);

	PlacaAuto p6; Auto a6;
	p6.placa = malloc(11);
	strcpy(p6.placa, "BBL-12-777");
	a6.modelo = malloc (20);
	strcpy(a6.modelo, "Chevrolet Traverse");
	a6.color = malloc(6);
	strcpy(a6.color, "negro");
	map_put(myMap, &p6, &a6);

	int sizeAux = map_size(myMap);	//ve el tamano del mapa para checar que hasta ahora si se han agregado todos
	printf("%d\n", sizeAux);

	PlacaAuto p7; Auto a7;
	p7.placa = malloc(11);
	strcpy(p7.placa, "ZAC-11-111");
	a7.modelo = malloc (7);
	strcpy(a7.modelo, "pickup");
	a7.color = malloc(6);
	strcpy(a7.color, "verde");
	map_put(myMap, &p7, &a7);

	PlacaAuto p8; Auto a8;
	p8.placa = malloc(11);
	strcpy(p8.placa, "BBL-00-727");
	a8.modelo = malloc (4);
	strcpy(a8.modelo, "BMW");
	a8.color = malloc(5);
	strcpy(a8.color, "rojo");
	map_put(myMap, &p8, &a8);

	PlacaAuto p9; Auto a9;
	p9.placa = malloc(11);
	strcpy(p9.placa, "JAL-00-000");
	a9.modelo = malloc (4);
	strcpy(a9.modelo, "BMW");
	a9.color = malloc(5);
	strcpy(a9.color, "rosa");
	map_put(myMap, &p9, &a9);

	PlacaAuto p10; Auto a10;
	p10.placa = malloc(11);
	strcpy(p10.placa, "SON-00-727");
	a10.modelo = malloc (4);
	strcpy(a10.modelo, "BMW");
	a10.color = malloc(7);
	strcpy(a10.color, "morado");
	map_put(myMap, &p10, &a10);

	sizeAux = map_size(myMap);	//ve el tamano del mapa para checar que hasta ahora si se han agregado todos
	printf("%d\n", sizeAux);

	PlacaAuto p11; Auto a11;
	p11.placa = malloc(11);
	strcpy(p11.placa, "SON-01-727");
	a11.modelo = malloc (4);
	strcpy(a11.modelo, "BMW");
	a11.color = malloc(7);
	strcpy(a11.color, "fiusha");
	map_put(myMap, &p11, &a11);

	PlacaAuto p12; Auto a12;
	p12.placa = malloc(11);
	strcpy(p12.placa, "SON-02-727");
	a12.modelo = malloc(7);
	strcpy(a12.modelo, "Toyota");
	a12.color = malloc(7);
	strcpy(a12.color, "morado");
	map_put(myMap, &p12, &a12);

	PlacaAuto p13; Auto a13;
	p13.placa = malloc(11);
	strcpy(p13.placa, "SON-03-725");
	a13.modelo = malloc(4);
	strcpy(a13.modelo, "BMW");
	a13.color = malloc(7);
	strcpy(a13.color, "blanco");
	map_put(myMap, &p13, &a13);

	PlacaAuto p14; Auto a14;
	p14.placa = malloc(11);
	strcpy(p14.placa, "SON-04-727");
	a14.modelo = malloc(7);
	strcpy(a14.modelo, "Toyota");
	a14.color = malloc(6);
	strcpy(a14.color, "beish");
	map_put(myMap, &p14, &a14);

	PlacaAuto p15; Auto a15;
	p15.placa = malloc(11);
	strcpy(p15.placa, "SON-06-724");
	a15.modelo = malloc (4);
	strcpy(a15.modelo, "BMW");
	a15.color = malloc(10);
	strcpy(a15.color, "baby blue");
	map_put(myMap, &p15, &a15);

	sizeAux = map_size(myMap);	//ve el tamano del mapa para checar que hasta ahora si se han agregado todos
	printf("%d\n", sizeAux);

	Auto * aux = (Auto*) map_get(myMap, &p1);	//vemos que el primer auto si es un Beetle azul wuuuuu
	if (aux != NULL)
	{
		puts (aux->modelo);
		puts (aux->color);
	}

	aux = (Auto*) map_get(myMap, &p5);	//vemos que el pen-ultimo auto si es un toyota besihs
	if (aux != NULL)
	{
		puts (aux->modelo);
		puts (aux->color);
	}

	aux = map_remove(myMap, &p2);	//eliminamos el segundo auto
	if (aux != NULL) puts (aux->modelo);

	sizeAux = map_size(myMap);	//ve el tamano del mapa para checar que si lo borro
	printf("%d\n", sizeAux);

	map_destroy(myMap);	//bye bye
	return 0;
}

