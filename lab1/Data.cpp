struct Data {
    int x, y, z;
};  

Data ** foo(Data ** v, int x) {
    for (int i = 0; i < x; i++)
        //if (v[i] != 0)
            v[i] = new Data;
    return v;
}

int main () {
    const int size = 5;
    Data ** v = new Data * [size];
    //foo(v, size);
    Data ** p = foo(v, size);
    delete [] p;
}

/**
==21913== Memcheck, a memory error detector
==21913== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==21913== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==21913== Command: ./Data.out
==21913== 
==21913== 
==21913== HEAP SUMMARY:
==21913==     in use at exit: 100 bytes in 6 blocks
==21913==   total heap usage: 6 allocs, 0 frees, 100 bytes allocated
==21913== 
==21913== 100 (40 direct, 60 indirect) bytes in 1 blocks are definitely lost in loss record 2 of 2
==21913==    at 0x4C2AC27: operator new[](unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==21913==    by 0x40060E: main (Data.cpp:14)
==21913== 
==21913== LEAK SUMMARY:
==21913==    definitely lost: 40 bytes in 1 blocks
==21913==    indirectly lost: 60 bytes in 5 blocks
==21913==      possibly lost: 0 bytes in 0 blocks
==21913==    still reachable: 0 bytes in 0 blocks
==21913==         suppressed: 0 bytes in 0 blocks
==21913== 
==21913== For counts of detected and suppressed errors, rerun with: -v
==21913== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 2 from 2)

*/
/**
==21983== Memcheck, a memory error detector
==21983== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==21983== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==21983== Command: ./Data.out
==21983== 
==21983== 
==21983== HEAP SUMMARY:
==21983==     in use at exit: 100 bytes in 6 blocks
==21983==   total heap usage: 6 allocs, 0 frees, 100 bytes allocated
==21983== 
==21983== 100 (40 direct, 60 indirect) bytes in 1 blocks are definitely lost in loss record 2 of 2r
==21983==    at 0x4C2AC27: operator new[](unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==21983==    by 0x40060E: main (Data.cpp:14)
==21983== 
==21983== LEAK SUMMARY:
==21983==    definitely lost: 40 bytes in 1 blocks
==21983==    indirectly lost: 60 bytes in 5 blocks
==21983==      possibly lost: 0 bytes in 0 blocks
==21983==    still reachable: 0 bytes in 0 blocks
==21983==         suppressed: 0 bytes in 0 blocks
==21983== 
==21983== For counts of detected and suppressed errors, rerun with: -v
==21983== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 2 from 2)

*/
/**
==21994== Memcheck, a memory error detector
==21994== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==21994== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==21994== Command: ./Data.out
==21994== 
==21994== 
==21994== HEAP SUMMARY:
==21994==     in use at exit: 60 bytes in 5 blocks
==21994==   total heap usage: 6 allocs, 1 frees, 100 bytes allocated
==21994== 
==21994== 60 bytes in 5 blocks are definitely lost in loss record 1 of 1
==21994==    at 0x4C2B1C7: operator new(unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==21994==    by 0x400626: foo(Data**, int) (Data.cpp:8)
==21994==    by 0x400673: main (Data.cpp:16)
==21994== 
==21994== LEAK SUMMARY:
==21994==    definitely lost: 60 bytes in 5 blocks
==21994==    indirectly lost: 0 bytes in 0 blocks
==21994==      possibly lost: 0 bytes in 0 blocks
==21994==    still reachable: 0 bytes in 0 blocks
==21994==         suppressed: 0 bytes in 0 blocks
==21994== 
==21994== For counts of detected and suppressed errors, rerun with: -v
==21994== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 2 from 2)

*/
