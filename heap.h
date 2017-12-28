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
//#define Heap_Pos_Parent(pos)            ( (pos) / 2     ) //wrong
#define Heap_Pos_Left(pos)              ( 2* (pos) +1   )
#define Heap_Pos_Right(pos)             ( 2* (pos) +2   )
#define Heap_Level_Capacity(level)      ( 1 << (level)  )

/* FUNCTIONS */
#define Heap_Empty(array, length)   ( Heap(array, length, 0)        )
#define Heap_Full(array, length)    ( Heap(array, length, length)   )
Heap_T Heap(Heap_Node_T* array, Heap_Pos_T length, Heap_Pos_T heap_size);

//#define Heap_Left_Exists(heap, pos)     (  Heap_El_Exists( (heap), (Heap_Pos_Left(pos))  )  )
//#define Heap_Right_Exists(heap, pos)    (  Heap_El_Exists( (heap), (Heap_Pos_Right(pos)) )  )
bool Heap_El_Exists(Heap_T heap, Heap_Pos_T pos);

void Heap_Swap(Heap_T heap, Heap_Pos_T pos1, Heap_Pos_T pos2);
void Build_Max_Heap(Heap_T heap);
void Max_Heapify(Heap_T heap, Heap_Pos_T pos);
#if HEAP_MODE == HEAP_TEST
Heap_Pos_T Heap_Max_Level(Heap_Pos_T max_pos);
void Heap_Print_Array(char* info_str, Heap_T heap);
void Print_Level_Spaces(Heap_Pos_T level, Heap_Pos_T max_level, Heap_Pos_T last_number_digits, Heap_Pos_T times);
void Heap_Print(char* info_str, Heap_T heap);
#endif


/* TEST */
#define TEST_HEAP_SIZE 64

int Heap_Test();

#endif // HEAP_H
