#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct strNode {
	Type key, value;
	struct strNode *next;
}*Node;

typedef struct strList {
	int size;
	Node first, last;
}*List;

struct strMap{
	int size;	//número de pares actualmente en la lista
	int m;	//capacidad del arreglo de listas enlazadas de pares (su “tamaño total”)
	List * table;	//arreglo (dinámico) de listas enlazadas de pares
	HashFunc hashFunc;	//apuntador a función hash: recibe una llave y m, produce un índice
	EqualsFunc equalsFunc;	//apuntador a función que recibe dos llaves y dice si son iguales
	DestroyFunc keyDestructor;	//destructor de elementos para las llaves
	DestroyFunc valueDestructor;	//destructor de elementos para los valores
};

Map map_create(int m, HashFunc hF, EqualsFunc eF, DestroyFunc keyDestructor, DestroyFunc valueDestructor){

	Map M = (Map) malloc (sizeof(struct strMap));	//crear instancia de Map  y asigna 0 y m a sus primeros dos atributos.
	M->size = 0;
	M->m = m;

	M->table = (List *) malloc (m * sizeof(List));	//construye un arreglo de m apuntadores a listas enlazadas, table
	for (int i = 0; i < m; i++)	//asigne NULL a cada posición/slot de table para dejar CLARO: NO ha sido inicializada ninguna lista.
		M->table[i] = NULL;

	M->hashFunc = hF;
	M->equalsFunc = eF;
	M->keyDestructor = keyDestructor;
	M->valueDestructor = valueDestructor;
	return M;
}

void map_destroy(Map M){
	if(M == NULL)	//si no hya mapa, no hay nada que hacer LOL
		return;

	for (int i = 0; i < (M->m); i++)	//para c lista elimina c nodo y su par llave-valor c los destructores
	{
		if (M->table[i] != NULL)	//si ese slot es null, no hay lista que destruir
		{
			Node aux1, aux2;
			aux1 = M->table[i]->first;
			while(aux1 != NULL)
			{
				aux2 = aux1->next;
				if(M->keyDestructor != NULL)
					M->keyDestructor(aux1->key);	//borra types con las funuciones destrucutoras especiales
				if(M->valueDestructor != NULL)
					M->valueDestructor(aux1->value);
				free (aux1);	//ahora liberamos este nodo
				aux1 = aux2;	//move on to next node
			}
			free(M->table[i]);	//elimina el slot que apunta a la lista
		}
	}
	free (M->table);	//libera la memoria asociada al arreglo de listas y
	free (M);	//libera la estructura principal del mapa.
}

int  map_size(Map M){
	if (M==NULL)
		return -1;
	return M->size;
}

void map_put(Map M, Type k, Type v){
	if(M == NULL) return;

	Node n = (Node) malloc(sizeof(struct strNode));	//crea nuevo nodo e inserta el par <k,v>
	n->key = k;
	n->value = v;
	n->next = NULL;

	int index = M->hashFunc(k, M->m);	//caulcula el índice (de la lista) en el arreglo donde ira el nuevo nodo

	if (M->table[index] == NULL)//Si ese índice de tabla almacena NULL, se crea la lista y se inserta el nuevo nodo (inicialización PE-RE-ZO-SA)
	{
		M->table[index] = (List) malloc (sizeof(struct strList));
		M->table[index]->size = 0;
		M->table[index]->last = M->table[index]->first = n;
	}
	else	//Si no, entonces la lista ya está creada y sólo agregamos el nuevo nodo
	{
		Node aux = M->table[index]->first;
		while(aux != NULL)
		{
			if (M->equalsFunc(k, aux->key)) return;	//si el elemento ya esta, no lo agregamos
			aux = aux->next;
		}
		M->table[index]->last->next = n;
	}
	M->table[index]->last = n;	//en cualquier caso se actualiza el last
	++(M->table[index]->size);	//y se incrementa size de la lista en 1
	++(M->size);	//y se incrementa del mapa size en 1
}

Type map_get(Map M, Type k){
	if(M == NULL) return NULL;

	int index = M->hashFunc (k, M->m);	//Usa hashFunc con k y m para calcular el índice de la lista respectiva.

	if (M->table[index] == NULL) return NULL;	//Si la lista es NULL, facil, devolvemos NULL.

	Node current = M->table[index]->first;	//Else, recorremos la lista en busqueda de un nodo cuyo atributo key sea == k.
	while(current != NULL)	//for (int i = 0; i < M->table[index]->size; i++)	//recorre toda la lista
	{
		if (M->equalsFunc(k, current->key)) return (current->value);	//si lo encontramos, devuelve el valor v asociado a la llave k y aqui acaba la cosa
		current = current->next;
	}
	return NULL;	//Si con ningún nodo de la lista equalsFunc devolvió true, la llave k no existe (ni un value asociado a ella)
}

Type map_remove(Map M, Type k){
	if(M == NULL) return NULL;

	int index = M->hashFunc (k, M->m);	//Usa hashFunc con k y m para calcular el índice de la lista respectiva.

	if (M->table[index] == NULL) return NULL;//Si la lista es NULL, facil, devolvemos NULL.

	Node current = M->table[index]->first;	//Else, recorremos la lista en busqueda de un nodo cuyo atributo key sea == k.
	Node previous = NULL;
	while(current != NULL)
	{
		if (M->equalsFunc(k, current->key))	//si lo encontramos, elimina y devuelve el value asociado con la llave k y Decrementa el tamaño en uno
		{
			if (current == M->table[index]->first)
				M->table[index]->first = current->next;	//el nodo siguiente será ahora el primero.
			else if (current == M->table[index]->last)
			{
				previous->next = NULL;
				M->table[index]->last = previous;
			}
			else
				previous->next = current->next; //borrar logicamente
			Type Value = current->value;
			free (current);
			--(M->table[index]->size);
			--(M->size);
			return Value;
		}
		previous = current;
		current = current->next;
	}
	return NULL;	//si no se encontro, tambien se devuelve null
}
