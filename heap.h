#ifndef HEAP_H
#define HEAP_H


#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

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

typedef uint32_t Heap_Pos_T;

/* TYPES */
typedef struct Heap_Tag
{
    Heap_Node_T * array;
    Heap_Pos_T    length;
    Heap_Pos_T    heap_size;

} Heap_T;


/* FUNCTION-LIKE MACROS */
#define Heap_Pos_Parent(pos)            (   ((pos) - 1) / 2   )
#define Heap_Pos_Left(pos)              (   (2 * (pos)) + 1   )
#define Heap_Pos_Right(pos)             (   (2 * (pos)) + 2   )
#define Heap_Level_Capacity(level)      (   1 << (level)      )

/* FUNCTIONS */
#define Heap_Empty(array, length)   ( Heap(array, length, 0)        )
#define Heap_Full(array, length)    ( Heap(array, length, length)   )
Heap_T Heap(Heap_Node_T* array, Heap_Pos_T length, Heap_Pos_T heap_size);

/* heplers */
int Heap_Arithmetic_Compare(Heap_T heap, Heap_Node_T el1, Heap_Node_T el2);
Heap_Pos_T Heap_Swap(Heap_T heap, Heap_Pos_T pos1, Heap_Pos_T pos2);
bool Heap_El_Exists(Heap_T heap, Heap_Pos_T pos);
Heap_Pos_T Heap_Max_Level(Heap_Pos_T max_pos);

/* core */
void Build_Max_Heap(Heap_T heap);
#define Max_Heapify_Root(heap) ( Max_Heapify((heap), 0) )
void Max_Heapify(Heap_T heap, Heap_Pos_T pos);
void Heap_Sort(Heap_T heap);
void Heap_Sort_Maxheap(Heap_T heap);
Heap_Node_T Heap_Maximum(Heap_T heap);
Heap_Node_T Heap_Extract_Max(Heap_T *heap_);
bool Heap_Insert(Heap_T *heap_, Heap_Node_T node);

#if HEAP_MODE == HEAP_TEST
/* PRINT FUNCTIONS */
void Heap_Print_Array(char* info_str, Heap_T heap);
void Heap_Print(char* info_str, Heap_T heap);
#endif


/* TEST */
#define TEST_HEAP_SIZE 64

int Heap_Test();

#endif // HEAP_H
