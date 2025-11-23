/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab1.h"
#include "CEcoLab1EnumConnectionPoints.h"
#include "IEcoConnectionPointContainer.h"
#include "IEcoEnumConnections.h"
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"

const int RUN = 32;

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLab1
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_QueryInterface(/* in */ IEcoLab1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
	else if ( IsEqualUGUID(riid, &IID_IEcoConnectionPointContainer) ) {
		*ppv = &pCMe->m_pVTblICPC; 
		pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
	}
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        if (pCMe->m_pInnerUnknown != 0) {
            return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
        }
        else {
            *ppv = &pCMe->m_pVTblIX;
            pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
        }
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIY;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoUnknown)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoLab1_X_QueryInterface(/* in */ IEcoCalculatorXPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - 2 * sizeof(IEcoUnknownPtr_t));
    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }
    

    /* Проверка и получение запрошенного интерфейса */
    if (IsEqualUGUID(riid, &IID_IEcoLab1)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        if (pCMe->m_pInnerUnknown != 0) {
            return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
        }
        else {
            *ppv = &pCMe->m_pVTblIX;
            pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
        }
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIY;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoUnknown)) {
        if (pCMe->m_pInnerUnknown != 0) {
            return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
        }
        else {
            *ppv = &pCMe->m_pVTblIX;
            pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
        }
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoLab1_Y_QueryInterface(/* in */ IEcoCalculatorYPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - (uint64_t)3 * sizeof(IEcoUnknownPtr_t));
    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if (IsEqualUGUID(riid, &IID_IEcoLab1)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIY;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        if (pCMe->m_pInnerUnknown != 0) {
            return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
        }
        else {
            *ppv = &pCMe->m_pVTblIX;
            pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
        }
    }
    else if (IsEqualUGUID(riid, &IID_IEcoUnknown)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoLab1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1_AddRef(/* in */ IEcoLab1Ptr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CEcoLab1_X_AddRef(/* in */ IEcoCalculatorXPtr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - 2 * sizeof(IEcoUnknownPtr_t));

    /* Проверка указателя */
    if (me == 0) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CEcoLab1_Y_AddRef(/* in */ IEcoCalculatorYPtr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - (uint64_t)3 * sizeof(IEcoUnknownPtr_t));

    /* Проверка указателя */
    if (me == 0) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoLab1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1_Release(/* in */ IEcoLab1Ptr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab1((IEcoLab1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CEcoLab1_X_Release(/* in */ IEcoCalculatorXPtr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - 2 * sizeof(IEcoUnknownPtr_t));

    /* Проверка указателя */
    if (me == 0) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if (pCMe->m_cRef == 0) {
        deleteCEcoLab1((IEcoLab1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CEcoLab1_Y_Release(/* in */ IEcoCalculatorYPtr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - (uint64_t)3 * sizeof(IEcoUnknownPtr_t));

    /* Проверка указателя */
    if (me == 0) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if (pCMe->m_cRef == 0) {
        deleteCEcoLab1((IEcoLab1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

int16_t ECOCALLMETHOD CEcoLab1_Fire_OnProcessStart(CEcoLab1* pCMe, const void* start_ptr, uint32_t count) {
    int16_t result = 0;
    IEcoEnumConnections* pEnum = 0;
    IEcoLab1Events* pIEvents = 0;
    EcoConnectionData cd;

    if (pCMe == 0 || pCMe->m_pISinkCP == 0) return -1;

    result = ((IEcoConnectionPoint*)pCMe->m_pISinkCP)->pVTbl->EnumConnections((IEcoConnectionPoint*)pCMe->m_pISinkCP, &pEnum);
    
    if ((result == 0) && (pEnum != 0)) {
        while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0) {
            result = cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab1Events, (void**)&pIEvents);
            if ((result == 0) && (pIEvents != 0)) {
                pIEvents->pVTbl->OnProcessStart(pIEvents, start_ptr, count);
                pIEvents->pVTbl->Release(pIEvents);
            }
            cd.pUnk->pVTbl->Release(cd.pUnk);
        }
        pEnum->pVTbl->Release(pEnum);
    }
    return result;
}

int16_t ECOCALLMETHOD CEcoLab1_Fire_OnArrayChange(CEcoLab1* pCMe, uint32_t index, const void* val_ptr, const void* arr_ptr, uint32_t count) {
    int16_t result = 0;
    IEcoEnumConnections* pEnum = 0;
    IEcoLab1Events* pIEvents = 0;
    EcoConnectionData cd;

    if (pCMe == 0 || pCMe->m_pISinkCP == 0) return -1;

    result = ((IEcoConnectionPoint*)pCMe->m_pISinkCP)->pVTbl->EnumConnections((IEcoConnectionPoint*)pCMe->m_pISinkCP, &pEnum);
    
    if ((result == 0) && (pEnum != 0)) {
        while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0) {
            result = cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab1Events, (void**)&pIEvents);
            if ((result == 0) && (pIEvents != 0)) {
                pIEvents->pVTbl->OnArrayChange(pIEvents, index, val_ptr, arr_ptr, count);
                pIEvents->pVTbl->Release(pIEvents);
            }
            cd.pUnk->pVTbl->Release(cd.pUnk);
        }
        pEnum->pVTbl->Release(pEnum);
    }
    return result;
}

void insertionSort(CEcoLab1* pCMe, IEcoMemoryAllocator1* pIMem, char* base, size_t nitems, size_t size, int16_t (*compar)(const void*, const void*), char* global_base, size_t total_count) {
    size_t i;
    int j;
    size_t global_idx;
    char* key = (char*)pIMem->pVTbl->Alloc(pIMem, size);

    for (i = 1; i < nitems; i++) {
        pIMem->pVTbl->Copy(pIMem, key, base + i * size, size);
        
        j = (int)i - 1;
        
        while (j >= 0 && compar(base + j * size, key) > 0) {
            pIMem->pVTbl->Copy(pIMem, base + (j + 1) * size, base + j * size, size);
            
            global_idx = (size_t)((base + (j + 1) * size) - global_base) / size;
            CEcoLab1_Fire_OnArrayChange(pCMe, (uint32_t)global_idx, base + j * size, global_base, (uint32_t)total_count);

            j--;
        }
        pIMem->pVTbl->Copy(pIMem, base + (j + 1) * size, key, size);
        
        global_idx = (size_t)((base + (j + 1) * size) - global_base) / size;
        CEcoLab1_Fire_OnArrayChange(pCMe, (uint32_t)global_idx, key, global_base, (uint32_t)total_count);
    }
    pIMem->pVTbl->Free(pIMem, key);
}

void merge(CEcoLab1* pCMe, IEcoMemoryAllocator1* pIMem, char* base, char* left, size_t left_size, char* right, size_t right_size, size_t size, int16_t (*compar)(const void*, const void*), char* global_base, size_t total_count) {
    size_t i = 0, j = 0, k = 0;
    size_t global_idx;

    while (i < left_size && j < right_size) {
        global_idx = (size_t)((base + k * size) - global_base) / size;
        
        if (compar(left + i * size, right + j * size) <= 0) {
            pIMem->pVTbl->Copy(pIMem, base + k * size, left + i * size, size);
            CEcoLab1_Fire_OnArrayChange(pCMe, (uint32_t)global_idx, left + i * size, global_base, (uint32_t)total_count);
            i++;
        } else {
            pIMem->pVTbl->Copy(pIMem, base + k * size, right + j * size, size);
            CEcoLab1_Fire_OnArrayChange(pCMe, (uint32_t)global_idx, right + j * size, global_base, (uint32_t)total_count);
            j++;
        }
        k++;
    }
    while (i < left_size) {
        global_idx = (size_t)((base + k * size) - global_base) / size;
        pIMem->pVTbl->Copy(pIMem, base + k * size, left + i * size, size);
        CEcoLab1_Fire_OnArrayChange(pCMe, (uint32_t)global_idx, left + i * size, global_base, (uint32_t)total_count);
        i++;
        k++;
    }
    while (j < right_size) {
        global_idx = (size_t)((base + k * size) - global_base) / size;
        pIMem->pVTbl->Copy(pIMem, base + k * size, right + j * size, size);
        CEcoLab1_Fire_OnArrayChange(pCMe, (uint32_t)global_idx, right + j * size, global_base, (uint32_t)total_count);
        j++;
        k++;
    }
}


/*
 *
 * <сводка>
 *   Функция qsort
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_qsort(IEcoLab1Ptr_t me, void* base, size_t nitems, size_t size, int16_t (*compar)(const void*, const void*)) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    size_t i, len, mid, right_end;

    if (me == 0 || base == 0 || compar == 0) return -1;

    CEcoLab1_Fire_OnProcessStart(pCMe, base, (uint32_t)nitems);

    for (i = 0; i < nitems; i += RUN) {
        insertionSort(pCMe, pCMe->m_pIMem, (char*)base + i * size, (i + RUN < nitems) ? RUN : (nitems - i), size, compar, (char*)base, nitems);
    }

    for (len = RUN; len < nitems; len = 2 * len) {
        for (i = 0; i < nitems; i += 2 * len) {
            mid = i + len - 1;
            right_end = (i + 2 * len - 1 < nitems - 1) ? (i + 2 * len - 1) : (nitems - 1);

            if (mid < right_end) {
                size_t left_size = mid - i + 1;
                size_t right_size = right_end - mid;
                char* left = (char*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, left_size * size);
                char* right = (char*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, right_size * size);

                pCMe->m_pIMem->pVTbl->Copy(pCMe->m_pIMem, left, (char*)base + i * size, left_size * size);
                pCMe->m_pIMem->pVTbl->Copy(pCMe->m_pIMem, right, (char*)base + (mid + 1) * size, right_size * size);

                merge(pCMe, pCMe->m_pIMem, (char*)base + i * size, left, left_size, right, right_size, size, compar, (char*)base, nitems);

                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, left);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, right);
            }
        }
    }
    return 0;
}

static int32_t ECOCALLMETHOD CEcoLab1_X_Addition(/* in */ IEcoCalculatorXPtr_t me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - 2 * sizeof(IEcoUnknownPtr_t));
    int32_t result = 0;

    if (me == 0) return INT32_MIN;

    if (pCMe->m_pIX != 0) {
        result = pCMe->m_pIX->pVTbl->Addition(pCMe->m_pIX, a, b);
    }

    return result;
}

static int16_t ECOCALLMETHOD CEcoLab1_X_Subtraction(/* in */ IEcoCalculatorXPtr_t me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - 2 * sizeof(IEcoUnknownPtr_t));
    int16_t result = 0;

    if (me == 0) return INT32_MIN;

    if (pCMe->m_pIX != 0) {
        result = pCMe->m_pIX->pVTbl->Subtraction(pCMe->m_pIX, a, b);
    }

    return result;
}

static int32_t ECOCALLMETHOD CEcoLab1_Y_Multiplication(IEcoCalculatorYPtr_t me, int16_t a, int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - (uint64_t)3 * sizeof(IEcoUnknownPtr_t));
    int32_t result = 0;

    if (me == 0) return INT32_MIN;

    if (pCMe->m_pIY != 0) {
        result = pCMe->m_pIY->pVTbl->Multiplication(pCMe->m_pIY, a, b);
    }

    return result;
}

static int16_t ECOCALLMETHOD CEcoLab1_Y_Division(IEcoCalculatorYPtr_t me, int16_t a, int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - (uint64_t)3 * sizeof(IEcoUnknownPtr_t));
    int16_t result = 0;

    if (me == 0) return INT32_MIN;

    if (pCMe->m_pIY != 0) {
        result = pCMe->m_pIY->pVTbl->Division(pCMe->m_pIY, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD CEcoLab1_IEcoConnectionPointContainer_QueryInterface(struct IEcoConnectionPointContainer* me, const UGUID* riid, void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(IEcoLab1VTbl*));
    return pCMe->m_pVTblIEcoLab1->QueryInterface((IEcoLab1*)pCMe, riid, ppv);
}

uint32_t ECOCALLMETHOD CEcoLab1_IEcoConnectionPointContainer_AddRef(struct IEcoConnectionPointContainer* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(IEcoLab1VTbl*));
    return pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
}

uint32_t ECOCALLMETHOD CEcoLab1_IEcoConnectionPointContainer_Release(struct IEcoConnectionPointContainer* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(IEcoLab1VTbl*));
    return pCMe->m_pVTblIEcoLab1->Release((IEcoLab1*)pCMe);
}

int16_t ECOCALLMETHOD CEcoLab1_IEcoConnectionPointContainer_EnumConnectionPoints(struct IEcoConnectionPointContainer* me, struct IEcoEnumConnectionPoints **ppEnum) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(IEcoLab1VTbl*));
    int16_t result = 0;

    if (me == 0 || ppEnum == 0 ) return -1;

    result = createCEcoLab1EnumConnectionPoints((IEcoUnknown*)pCMe->m_pISys, (IEcoConnectionPoint*)&pCMe->m_pISinkCP->m_pVTblICP, ppEnum);
    return result;
}

int16_t ECOCALLMETHOD CEcoLab1_IEcoConnectionPointContainer_FindConnectionPoint(struct IEcoConnectionPointContainer* me, const UGUID* riid, struct IEcoConnectionPoint **ppCP) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(IEcoLab1VTbl*));

    if (me == 0 || ppCP == 0 ) return -1;

    if ( !IsEqualUGUID(riid, &IID_IEcoLab1Events ) ) {
        *ppCP = 0;
        return -1; /* CONNECT_E_NOCONNECTION */
    }

    if (pCMe->m_pISinkCP == 0) return -1;

    pCMe->m_pISinkCP->m_pVTblICP->AddRef((IEcoConnectionPoint*)&pCMe->m_pISinkCP->m_pVTblICP);
    *ppCP = (IEcoConnectionPoint*)&pCMe->m_pISinkCP->m_pVTblICP;

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoLab1(/*in*/ IEcoLab1Ptr_t me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result = -1;
	IEcoUnknown* pOuterUnknown = (IEcoUnknown*)me;
    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY, (void**)&pCMe->m_pIY);
    if (result != 0 || pCMe->m_pIY == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**)&pCMe->m_pIY);
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, pOuterUnknown, &IID_IEcoUnknown, (void**)&pCMe->m_pInnerUnknown);
    if (result != 0 || pCMe->m_pInnerUnknown == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**)&pCMe->m_pIX);
    }

	result = createCEcoLab1ConnectionPoint((IEcoUnknown*)pCMe->m_pISys, 
                                        (IEcoConnectionPointContainer*)&pCMe->m_pVTblICPC, 
                                        &IID_IEcoLab1Events, 
                                        (IEcoConnectionPoint**)&((pCMe)->m_pISinkCP));

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return result;
}

/* Create Virtual Table IEcoLab1 */
IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
    CEcoLab1_QueryInterface,
    CEcoLab1_AddRef,
    CEcoLab1_Release,
    CEcoLab1_qsort
};


IEcoCalculatorXVTbl g_X_x8A1ED3A6B4454B86B7C1D1E9F0A2B3C4VTbl = {
    CEcoLab1_X_QueryInterface,
    CEcoLab1_X_AddRef,
    CEcoLab1_X_Release,
    CEcoLab1_X_Addition,
    CEcoLab1_X_Subtraction
};

IEcoCalculatorYVTbl g_Y_x5F2B9C8D6E1A49479A8B6C5D4E3F2A1BVTbl = {
    CEcoLab1_Y_QueryInterface,
    CEcoLab1_Y_AddRef,
    CEcoLab1_Y_Release,
    CEcoLab1_Y_Multiplication,
    CEcoLab1_Y_Division
};

IEcoConnectionPointContainerVTbl g_x0000000500000000C000000000000046VTblCPC = {
    CEcoLab1_IEcoConnectionPointContainer_QueryInterface,
    CEcoLab1_IEcoConnectionPointContainer_AddRef,
    CEcoLab1_IEcoConnectionPointContainer_Release,
    CEcoLab1_IEcoConnectionPointContainer_EnumConnectionPoints,
    CEcoLab1_IEcoConnectionPointContainer_FindConnectionPoint
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoLab1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab1** ppIEcoLab1) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab1* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    /* Проверка указателей */
    if (ppIEcoLab1 == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem, (void **)&pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab1*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

       /* Создание таблицы функций интерфейса IEcoLab1 */
    pCMe->m_pVTblIEcoLab1 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;
	pCMe->m_pVTblICPC = &g_x0000000500000000C000000000000046VTblCPC;

    /* Создание таблицы функций интерфейса IEcoCalculatorX */
    pCMe->m_pVTblIX = &g_X_x8A1ED3A6B4454B86B7C1D1E9F0A2B3C4VTbl;

    /* Создание таблицы функций интерфейса IEcoCalculatorY */
    pCMe->m_pVTblIY = &g_Y_x5F2B9C8D6E1A49479A8B6C5D4E3F2A1BVTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;
    pCMe->m_pIX = 0;
    pCMe->m_pIY = 0;
	pCMe->m_pISinkCP = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoLab1 = (IEcoLab1*)pCMe;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoLab1(/* in */ IEcoLab1* pIEcoLab1) {
    CEcoLab1* pCMe = (CEcoLab1*)pIEcoLab1;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1 != 0 ) {
        pIMem = pCMe->m_pIMem;

		if (pCMe->m_pIX != 0) {
            pCMe->m_pIX->pVTbl->Release(pCMe->m_pIX);
        }
        if (pCMe->m_pIY != 0) {
            pCMe->m_pIY->pVTbl->Release(pCMe->m_pIY);
        }
		if (pCMe->m_pInnerUnknown != 0) {
            pCMe->m_pInnerUnknown->pVTbl->Release(pCMe->m_pInnerUnknown);
        }

        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
		if (pCMe->m_pISinkCP != 0) {
             deleteCEcoLab1ConnectionPoint((IEcoConnectionPoint*)pCMe->m_pISinkCP);
        }

        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}