#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define N_ELEMS(x) (  (sizeof(x))  /  (sizeof(x[0]))  )

/* OPTIONS */
#define HEAP_TEST       0
#define HEAP_GENERIC    1
#define HEAP_MODE       HEAP_TEST
/* END OPTIONS */

/* PROCESS OPTIONS */
#if     HEAP_MODE == HEAP_TEST
typedef uint32_t Heap_Node_T;
#else   /* HEAP_MODE == HEAP_TEST */
typedef void* Heap_Node_T;
#endif  /* HEAP_MODE == HEAP_TEST */


/* TYPES */
typedef struct Heap_Tag
{
    Heap_Node_T * array;
    uint32_t    length;
    uint32_t    heap_size;

} Heap_T;


/* FUNCTION-LIKE MACROS */
#define Heap_Pos_Parent(pos)    ( (pos) / 2     )
#define Heap_Pos_Left(pos)      ( 2* (pos)      )
#define Heap_Pos_Right(pos)     ( 2* (pos) +1   )

/* FUNCTIONS */
Heap_T Heap(Heap_Node_T* array, uint32_t length)
{
    Heap_T obj;
    obj.array       = array;
    obj.length      = length;
    obj.heap_size   = 0;
    return obj;
}

#if HEAP_MODE == HEAP_TEST
void Heap_Print(char* info_str, Heap_T heap)
{
    printf("%s[", info_str);
    for (uint32_t el_id = 0; el_id < heap.length; ++el_id)
    {
        printf("%d, ", heap.array[el_id]);
    }
    printf("]\n");
}
#endif


/* TEST */
#define TEST_HEAP_SIZE 64

int main()
{
    Heap_Node_T heap_array [TEST_HEAP_SIZE];
    memset(heap_array, 0, sizeof heap_array);
    Heap_T heap;
    heap = Heap(heap_array, N_ELEMS(heap_array));
    Heap_Print("heap:", heap);

    return 0;
}
