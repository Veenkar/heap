/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include "heap.h"

#if HEAP_MODE == HEAP_TEST
#include <stdio.h>
#endif

/* DEFINES */
#if HEAP_MODE == HEAP_TEST
#ifndef RES_STR
    #define RES_STR(val) val? "successful": "failed"
#endif /* BOOL_STR */
#ifndef UNUSED
    #define UNUSED(val) ( (void) val )
#endif /* BOOL_STR */
#endif

/* PRIVATE FUNCTION DECLARATIONS */
void Print_Level_Spaces(Heap_Pos_T level, Heap_Pos_T max_level, Heap_Pos_T last_number_digits, Heap_Pos_T times);


/* FUNCTIONS */
/* constr */
Heap_T Heap(Heap_Node_T* array, Heap_Pos_T length, Heap_Pos_T heap_size)
{
    Heap_T obj;
    obj.array       = array;
    obj.length      = length;
    obj.heap_size   = heap_size;
    return obj;
}

/* heplers */
int Heap_Arithmetic_Compare(Heap_T heap, Heap_Node_T el1, Heap_Node_T el2)
{
    UNUSED(heap);
    return el1 - el2;
}
bool Heap_El_Exists(Heap_T heap, Heap_Pos_T pos)
{
    return pos < heap.heap_size && heap.array != NULL;
}
Heap_Pos_T Heap_Swap(Heap_T heap, Heap_Pos_T pos1, Heap_Pos_T pos2)
{

    Heap_Node_T temp = heap.array[pos1];
    heap.array[pos1] = heap.array[pos2];
    heap.array[pos2] = temp;
    return pos2;
}
Heap_Pos_T Heap_Max_Level(Heap_Pos_T max_pos)
{
    Heap_Pos_T level = 0;
    while (max_pos > 0)
    {
        max_pos = max_pos >> 1;
        ++level;
    }
    return level;
}

/* core */
void Build_Max_Heap(Heap_T heap)
{
    Heap_Pos_T pos = heap.heap_size / 2;
    do
    {
        Max_Heapify(heap, pos);

    } while (pos-- !=0);
}
void Max_Heapify(Heap_T heap, Heap_Pos_T pos)
{

    if (!Heap_El_Exists(heap, pos))
    {
        return;
    }
    else
    {   Heap_Pos_T max_el_pos;
        Heap_Node_T parent_val = heap.array[pos];
        Heap_Pos_T left_pos = Heap_Pos_Left(pos);
        Heap_Pos_T right_pos = Heap_Pos_Right(pos);

        if (Heap_El_Exists(heap, left_pos) && Heap_Arithmetic_Compare(heap, heap.array[left_pos], parent_val) > 0 )
        {
            max_el_pos = left_pos;
        }
        else
        {
            max_el_pos = pos;
        }

        if (Heap_El_Exists(heap, right_pos) && Heap_Arithmetic_Compare(heap, heap.array[right_pos], heap.array[max_el_pos]) > 0)
        {
            max_el_pos = right_pos;
        }

        if (max_el_pos != pos)
        {
            Heap_Swap(heap, pos, max_el_pos);
            Max_Heapify(heap, max_el_pos);
        }

    }

}
void Heap_Sort(Heap_T heap)
{
    Build_Max_Heap(heap);
    Heap_Sort_Maxheap(heap);
}
void Heap_Sort_Maxheap(Heap_T heap)
{
    for (Heap_Pos_T pos = heap.heap_size - 1; pos >0; --pos)
    {
        Heap_Swap(heap, 0, pos);
        --heap.heap_size;
        Max_Heapify_Root(heap);
    }
}
Heap_Node_T Heap_Maximum(Heap_T heap)
{
    Heap_Node_T res = {0};
    if (heap.heap_size > 0)
    {
        res = heap.array[0];
    }
    return res;
}

Heap_Node_T Heap_Extract_Max(Heap_T *heap_)
{
    Heap_Node_T maximum = Heap_Maximum(*heap_);
    if (heap_->heap_size > 0)
    {
        Heap_Swap(*heap_, 0, --heap_->heap_size);
        Max_Heapify_Root(*heap_);

        #if HEAP_MODE == HEAP_TEST
            printf("Heap_Extract successful -> %d\n\n", maximum);
        #endif
    }
    else
    {
        #if HEAP_MODE == HEAP_TEST
            printf("Heap_Extract failed -> %d\n\n", maximum);
        #endif
    }
    return maximum;
}
bool Heap_Insert(Heap_T *heap_, Heap_Node_T node)
{
    bool res;
    if (heap_==NULL && !Heap_El_Exists(*heap_, heap_->heap_size) )
    {
        res = false;
    }
    else
    {
        Heap_Pos_T pos, pos_parent;
        pos = heap_->heap_size;
        heap_->array[heap_->heap_size++] = node;

        while (pos > 0 && heap_->array[pos_parent = Heap_Pos_Parent(pos)] < heap_->array[pos])
        {
            pos = Heap_Swap(*heap_, pos, pos_parent);
        }
        res = true;
    }
    #if HEAP_MODE == HEAP_TEST
        printf("Heap_Insert %s <- %d\n\n", RES_STR(res), node);
    #endif
    return res;
}

#if HEAP_MODE == HEAP_TEST
/* PRINT FUNCTIONS */
void Print_Level_Spaces(Heap_Pos_T level, Heap_Pos_T max_level, Heap_Pos_T last_number_digits, Heap_Pos_T times)
{
    for (Heap_Pos_T repeat = 0; repeat<times; repeat++)
    {
        for (Heap_Pos_T level_it = 0; level_it < Heap_Level_Capacity(max_level - level)  - last_number_digits +1; ++level_it)
        {
            printf(" ");
        }
    }
}
void Heap_Print_Array(char* info_str, Heap_T heap)
{
    printf("%s[", info_str);
    for (Heap_Pos_T el_id = 0; el_id < heap.heap_size; ++el_id)
    {
        bool is_last = el_id == heap.heap_size - 1;
        printf(is_last? "%d": "%d, ", heap.array[el_id]);
    }
    printf("]\n");
}
void Heap_Print(char* info_str, Heap_T heap)
{
    Heap_Pos_T level = 0;
    Heap_Pos_T max_level = Heap_Max_Level(heap.heap_size);
    Heap_Pos_T level_capacity = Heap_Level_Capacity(level);
    Heap_Pos_T last_number_digits = 0;

    printf("%s\n", info_str);
    printf("capacity: %d\nheap_length: %d\n", heap.length, heap.heap_size);

    Print_Level_Spaces(level, max_level, last_number_digits, 1);

    for (Heap_Pos_T el_id = 0; el_id < heap.heap_size; ++el_id)
    {
        if (el_id >= level_capacity)
        {
            level_capacity += Heap_Level_Capacity(++level);
            last_number_digits = 0;
            printf("\n");
            Print_Level_Spaces(level, max_level, last_number_digits, 1);
        }

        last_number_digits = printf("%d ", heap.array[el_id]);
        Print_Level_Spaces(level, max_level, last_number_digits, 2);
    }
    printf("\n");
    Heap_Print_Array("array:", heap);
    printf("\n");
}

/* TEST */
#define TEST_HEAP_SIZE 64
int Heap_Test()
{
    Heap_Node_T heap_array [20] = {15, 4, 78, 1, 5};
    //memset(heap_array, 0, sizeof heap_array);
    Heap_T heap;
    heap = Heap(heap_array, N_ELEMS(heap_array), 5);

    Heap_Print("----heap----", heap);
    Build_Max_Heap(heap);
    Heap_Print("----heap----", heap);
    Heap_Insert(&heap, 100);
    Heap_Print("----heap----", heap);
    Heap_Insert(&heap, 2);
    Heap_Print("----heap----", heap);
    Heap_Extract_Max(&heap);
    Heap_Print("----heap----", heap);

    return 0;
}

#endif /*  HEAP_MODE == HEAP_TEST */


