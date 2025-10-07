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
#endif

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
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


    printf("\n--- Performance Test (sorting %d elements) ---\n", LARGE_ARRAY_SIZE);

    /* Создание и заполнение большого массива */
    arr_large = (int*)pIMem->pVTbl->Alloc(pIMem, LARGE_ARRAY_SIZE * sizeof(int));
    arr_large_copy = (int*)pIMem->pVTbl->Alloc(pIMem, LARGE_ARRAY_SIZE * sizeof(int));
    srand((unsigned int)time(NULL));
    for (i = 0; i < LARGE_ARRAY_SIZE; i++) {
        arr_large[i] = rand();
    }

    /* Замер времени для вашей реализации qsort */
    memcpy(arr_large_copy, arr_large, LARGE_ARRAY_SIZE * sizeof(int));
    start = clock();
    pIEcoLab1->pVTbl->qsort(pIEcoLab1, arr_large_copy, LARGE_ARRAY_SIZE, sizeof(int), comp_int);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000.0;
    printf("Custom qsort time: %f ms\n", cpu_time_used);

    /* Замер времени для стандартной qsort */
    memcpy(arr_large_copy, arr_large, LARGE_ARRAY_SIZE * sizeof(int));
    start = clock();
    qsort(arr_large_copy, LARGE_ARRAY_SIZE, sizeof(int), comp_int_std);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000.0;
    printf("Standard qsort time: %f ms\n", cpu_time_used);
	getchar();

    result = 0;

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
