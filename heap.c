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
#if HEAP_MODE == HEAP_TEST
typedef uint32_t Heap_Node_T;
#else
typedef void* Heap_Node_T;
#endif


/* TYPES */
typedef struct Heap_Tag
{
    Heap_Node_T * array;
    uint32_t length;
    uint32_t heap_size;

} Heap_T;


/* FUNCTIONS */
Heap_T Heap(Heap_Node_T* array, uint32_t length)
{
    Heap_T obj;
    obj.array = array;
    obj.length = length;
    obj.heap_size = 0;
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

uint32_t Heap_Pos_Parent(uint32_t pos)
{
    return pos / 2;
}

uint32_t Heap_Pos_Left(uint32_t pos)
{
    return 2 * pos;
}

uint32_t Heap_Pos_Right(uint32_t pos)
{
    return 2 * pos + 1;
}


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
