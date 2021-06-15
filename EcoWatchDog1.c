/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoWatchDog1
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
#include "IdEcoWatchDog1.h"

/* Глобальная переменная */
volatile int g_Problem = -1;

/*
 *
 * <сводка>
 *   Функция AnalyzeProblemHandler
 * </сводка>
 *
 * <описание>
 *   Функция AnalyzeProblemHandler - функция анализа проблемы
 * </описание>
 *
 */
void AnalyzeProblemHandler() {
    // Псевдокод анализа проблемы
    
    // обнарудена ошибка при работе с контроллером  mcp2515 через spi интрерфейс
    // при проверке статусного регистра контроллер не отвечает что требудет сброса контроллера mcp2515

    /* Устранение общибки */
    if (g_Problem != 0) {
        g_Problem  = 0;
    }
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
    volatile int index = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoWatchDog1* pIEcoWatchDog1 = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoWatchDog1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_897EFA2C9A4D4D55B74E20422EE64D92);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif

    /* Получение тестируемого интерфейса */
    pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoWatchDog1, 0, &IID_IEcoWatchDog1, (void**) &pIEcoWatchDog1);
    if (result != 0 && pIEcoWatchDog1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Устанавливаеи обработчик анализа проблем*/
    pIEcoWatchDog1->pVTbl->set_Handler(pIEcoWatchDog1, AnalyzeProblemHandler);

    /* Разрешаем наблюдение с периодом в 1 сек и сдавим режим reset*/
    pIEcoWatchDog1->pVTbl->set_Mode(pIEcoWatchDog1, 1);
    pIEcoWatchDog1->pVTbl->Enable(pIEcoWatchDog1, 250);

    while (1) {
    index++;
        if (index > 100) {
            /* Имитируем сбой в системе - зависание */
            while (1) {
                index = g_Problem;
                if (index == 0) {
                    /* Ошибка была проаналиирована и исправлена */
                    break;
                }
            }
        }
        else {
            pIEcoWatchDog1->pVTbl->Reset(pIEcoWatchDog1);
        }
    }

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoWatchDog1 != 0) {
        pIEcoWatchDog1->pVTbl->Release(pIEcoWatchDog1);
    }

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

