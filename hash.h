//contenedor Map utilizando estructuras hash
//resolución de colisiones con encadenamiento lineal

#ifndef HASH_H_
#define HASH_H_

typedef void * Type;
#include <stdbool.h>
typedef struct strMap * Map;

typedef int (*HashFunc) (Type, int);
typedef bool (*EqualsFunc) (Type, Type);
typedef void (*DestroyFunc) (Type);

Map map_create(int m, HashFunc hF, EqualsFunc eF, DestroyFunc keyDestructor, DestroyFunc valueDestructor);
void map_destroy(Map);
int  map_size(Map);
void map_put(Map m, Type k, Type v);
Type map_get(Map m, Type k);
Type map_remove(Map m, Type k);

#endif /* HASH_H_ */
