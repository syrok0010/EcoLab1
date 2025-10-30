/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"

#define MAX_ARRAY_SIZE 5000000
#define LARGE_ARRAY_SIZE 100000

int16_t ECOCALLMETHOD comp_int(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int __cdecl comp_int_std(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void print_array(const char* msg, int* arr, size_t n) {
    size_t i;
    printf("%s: ", msg);
    for (i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;
    /* Указатель на интерфейс для работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    clock_t start, end;
    double cpu_time_used;
    int i;
    int sizes[] = {100000, 500000, 1000000, 2000000, 3000000, 5000000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int s_idx;
    IEcoCalculatorX* pIX = 0;
    IEcoCalculatorY* pIY = 0;
    int32_t comp_result = 0;
	IEcoLab1* temp_pIEcoLab1 = 0;
    IEcoCalculatorX* temp_pIX_Test = 0;
    IEcoCalculatorY* temp_pIY_Test = 0;
	int op_res;
    
	/* Тестовые наборы данных */
    int arr_random[] = { 5, 2, 8, 1, 9, 4 };
    int arr_sorted[] = { 1, 2, 4, 5, 8, 9 };
    int arr_reversed[] = { 9, 8, 5, 4, 2, 1 };
    int arr_same[] = { 5, 5, 5, 5, 5, 5 };
    int* arr_large = 0;
    int* arr_large_copy = 0;

    int arr_random_copy[6];
    int arr_sorted_copy[6];
    int arr_reversed_copy[6];
    int arr_same_copy[6];

    int expected_random[] = { 1, 2, 4, 5, 8, 9 };
    int expected_sorted[] = { 1, 2, 4, 5, 8, 9 };
    int expected_reversed[] = { 1, 2, 4, 5, 8, 9 };
    int expected_same[] = { 5, 5, 5, 5, 5, 5 };


    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void **)&pISys);
        if (result != 0 && pISys == 0) {
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        goto Release;
    }

    /* Получение интерфейса распределителя памяти */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);
    if (result != 0 || pIMem == 0) {
        goto Release;
    }

#ifdef ECO_LIB
    /* Регистрация статического компонента */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0 ) {
        goto Release;
    }
		result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorB, (IEcoUnknown*)GetIEcoComponentFactoryPtr_AE202E543CE54550899603BD70C62565);
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorA, (IEcoUnknown*)GetIEcoComponentFactoryPtr_4828F6552E4540E78121EBD220DC360E);
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorD, (IEcoUnknown*)GetIEcoComponentFactoryPtr_3A8E44677E82475CB4A3719ED8397E61);
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorE, (IEcoUnknown*)GetIEcoComponentFactoryPtr_872FEF1DE3314B87AD44D1E7C232C2F0);
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        goto Release;
    }
	
	result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIX);
    if (result != 0 || pIX == 0) {
        goto Release;
    }

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&pIY);
    if (result != 0 || pIY == 0) {
        goto Release;
    }

    printf("--- Functional Tests ---\n");

    /* --- Тест 1: Случайный массив --- */
    memcpy(arr_random_copy, arr_random, sizeof(arr_random));
    pIEcoLab1->pVTbl->qsort(pIEcoLab1, arr_random_copy, 6, sizeof(int), comp_int);
    printf("Random array test: %s\n", memcmp(arr_random_copy, expected_random, sizeof(expected_random)) == 0 ? "PASS" : "FAIL");

    /* --- Тест 2: Уже отсортированный массив --- */
    memcpy(arr_sorted_copy, arr_sorted, sizeof(arr_sorted));
    pIEcoLab1->pVTbl->qsort(pIEcoLab1, arr_sorted_copy, 6, sizeof(int), comp_int);
    printf("Sorted array test: %s\n", memcmp(arr_sorted_copy, expected_sorted, sizeof(expected_sorted)) == 0 ? "PASS" : "FAIL");

    /* --- Тест 3: Массив, отсортированный в обратном порядке --- */
    memcpy(arr_reversed_copy, arr_reversed, sizeof(arr_reversed));
    pIEcoLab1->pVTbl->qsort(pIEcoLab1, arr_reversed_copy, 6, sizeof(int), comp_int);
    printf("Reversed array test: %s\n", memcmp(arr_reversed_copy, expected_reversed, sizeof(expected_reversed)) == 0 ? "PASS" : "FAIL");

    /* --- Тест 4: Массив с одинаковыми элементами --- */
    memcpy(arr_same_copy, arr_same, sizeof(arr_same));
    pIEcoLab1->pVTbl->qsort(pIEcoLab1, arr_same_copy, 6, sizeof(int), comp_int);
    printf("Same elements array test: %s\n", memcmp(arr_same_copy, expected_same, sizeof(expected_same)) == 0 ? "PASS" : "FAIL");

    printf("\n--- Performance Tests ---\n");

    arr_large = (int*)pIMem->pVTbl->Alloc(pIMem, MAX_ARRAY_SIZE * sizeof(int));
    arr_large_copy = (int*)pIMem->pVTbl->Alloc(pIMem, MAX_ARRAY_SIZE * sizeof(int));
    if (!arr_large || !arr_large_copy) {
        printf("Memory allocation for large arrays failed!\n");
        goto Release;
    }

    srand((unsigned int)time(NULL));

    for (s_idx = 0; s_idx < num_sizes; ++s_idx) {
        int current_size = sizes[s_idx];
        printf("\nSorting %d elements:\n", current_size);

        // --- Random Array ---
        for (i = 0; i < current_size; i++) {
            arr_large[i] = rand();
        }
        printf("  Random array:\n");
        memcpy(arr_large_copy, arr_large, current_size * sizeof(int));
        start = clock();
        pIEcoLab1->pVTbl->qsort(pIEcoLab1, arr_large_copy, current_size, sizeof(int), comp_int);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000.0;
        printf("    Custom qsort time: %f ms\n", cpu_time_used);

        memcpy(arr_large_copy, arr_large, current_size * sizeof(int));
        start = clock();
        qsort(arr_large_copy, current_size, sizeof(int), comp_int_std);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000.0;
        printf("    Standard qsort time: %f ms\n", cpu_time_used);

        // --- Sorted Array ---
        for (i = 0; i < current_size; i++) {
            arr_large[i] = i; // Already sorted
        }
        printf("  Sorted array:\n");
        memcpy(arr_large_copy, arr_large, current_size * sizeof(int));
        start = clock();
        pIEcoLab1->pVTbl->qsort(pIEcoLab1, arr_large_copy, current_size, sizeof(int), comp_int);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000.0;
        printf("    Custom qsort time: %f ms\n", cpu_time_used);

        memcpy(arr_large_copy, arr_large, current_size * sizeof(int));
        start = clock();
        qsort(arr_large_copy, current_size, sizeof(int), comp_int_std);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000.0;
        printf("    Standard qsort time: %f ms\n", cpu_time_used);

        // --- Reversed Array ---
        for (i = 0; i < current_size; i++) {
            arr_large[i] = current_size - 1 - i; // Reversed sorted
        }
        printf("  Reversed array:\n");
        memcpy(arr_large_copy, arr_large, current_size * sizeof(int));
        start = clock();
        pIEcoLab1->pVTbl->qsort(pIEcoLab1, arr_large_copy, current_size, sizeof(int), comp_int);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000.0;
        printf("    Custom qsort time: %f ms\n", cpu_time_used);

        memcpy(arr_large_copy, arr_large, current_size * sizeof(int));
        start = clock();
        qsort(arr_large_copy, current_size, sizeof(int), comp_int_std);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000.0;
        printf("    Standard qsort time: %f ms\n", cpu_time_used);
    }

    result = 0;
    printf("\n===== Verification of Component Interfaces =====\n");
    printf("--- Part 1: Interface Accessibility Checks ---\n");

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&temp_pIX_Test);
    printf("Check [IEcoLab1 => IEcoCalculatorX]: %s\n", (result == 0) ? "Ok" : "Fail");
    if (temp_pIX_Test) temp_pIX_Test->pVTbl->Release(temp_pIX_Test);

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&temp_pIY_Test);
    printf("Check [IEcoLab1 => IEcoCalculatorY]: %s\n", (result == 0) ? "Ok" : "Fail");
    if (temp_pIY_Test) temp_pIY_Test->pVTbl->Release(temp_pIY_Test);

	result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&temp_pIEcoLab1);
    printf("Check [IEcoLab1 => IEcoCalculatorY]: %s\n", (result == 0) ? "Ok" : "Fail");
    if (temp_pIY_Test) temp_pIEcoLab1->pVTbl->Release(temp_pIEcoLab1);

    printf("\n--- Part 2: Cross-Interface QI Checks ---\n");

    result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoCalculatorY, (void**)&temp_pIY_Test);
    printf("Check [IEcoCalculatorX => IEcoCalculatorY]: %s\n", (result == 0) ? "Ok" : "Fail");
    if (temp_pIY_Test) temp_pIY_Test->pVTbl->Release(temp_pIY_Test);

    result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoLab1, (void**)&temp_pIEcoLab1);
    printf("Check [IEcoCalculatorX => IEcoLab1]: %s\n", (result == 0) ? "Ok" : "Fail");
    if (temp_pIEcoLab1) temp_pIEcoLab1->pVTbl->Release(temp_pIEcoLab1);

	result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoCalculatorX, (void**)&temp_pIX_Test);
    printf("Check [IEcoCalculatorX => IEcoCalculatorX]: %s\n", (result == 0) ? "Ok" : "Fail");
    if (temp_pIX_Test) temp_pIX_Test->pVTbl->Release(temp_pIX_Test);

    result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorX, (void**)&temp_pIX_Test);
    printf("Check [IEcoCalculatorY => IEcoCalculatorX]: %s\n", (result == 0) ? "Ok" : "Fail");
    if (temp_pIX_Test) temp_pIX_Test->pVTbl->Release(temp_pIX_Test);
    
    result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoLab1, (void**)&temp_pIEcoLab1);
    printf("Check [IEcoCalculatorY => IEcoLab1]: %s\n", (result == 0) ? "Ok" : "Fail");
    if (temp_pIEcoLab1) temp_pIEcoLab1->pVTbl->Release(temp_pIEcoLab1);

    result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorY, (void**)&temp_pIY_Test);
    printf("Check [IEcoCalculatorY => IEcoCalculatorY]: %s\n", (result == 0) ? "Ok" : "Fail");
    if (temp_pIY_Test) temp_pIY_Test->pVTbl->Release(temp_pIY_Test);

    printf("\n--- Part 3: Arithmetic Functionality Tests ---\n");
    
    op_res = pIX->pVTbl->Addition(pIX, 7, 8);
    if (op_res == 15) {
        printf("Operation [Addition 7+8]: Correct. Result = %d\n", op_res);
    } else {
        printf("Operation [Addition 7+8]: FAILED. Got %d, Expected 15\n", op_res);
    }
    
    op_res = pIX->pVTbl->Subtraction(pIX, 20, 5);
	if (op_res == 15) {
        printf("Operation [Subtraction 20-5]: Correct. Result = %d\n", op_res);
    } else {
        printf("Operation [Subtraction 20-5]: FAILED. Got %d, Expected 15\n", op_res);
    }

    op_res = pIY->pVTbl->Multiplication(pIY, 4, 6);
	if (op_res == 24) {
        printf("Operation [Multiplication 4*6]: Correct. Result = %d\n", op_res);
    } else {
        printf("Operation [Multiplication 4*6]: FAILED. Got %d, Expected 24\n", op_res);
    }

    op_res = pIY->pVTbl->Division(pIY, 50, 10);
	if (op_res == 5) {
        printf("Operation [Division 50/10]: Correct. Result = %d\n", op_res);
    } else {
        printf("Operation [Division 50/10]: FAILED. Got %d, Expected 5\n", op_res);
    }

    printf("\n===== Component Verification Finished =====\n\n");

	getchar();

Release:

    /* Освобождение памяти */
    if (pIMem != 0) {
        if (arr_large != 0) {
            pIMem->pVTbl->Free(pIMem, arr_large);
        }
        if (arr_large_copy != 0) {
            pIMem->pVTbl->Free(pIMem, arr_large_copy);
        }
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}
