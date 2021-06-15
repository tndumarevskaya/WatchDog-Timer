/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoWatchDog1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoWatchDog1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECOWATCHDOG1_H__
#define __C_ECOWATCHDOG1_H__

#include "IEcoWatchDog1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoWatchDog1 {

    /* Таблица функций интерфейса IEcoWatchDog1 */
    IEcoWatchDog1VTbl* m_pVTblIEcoWatchDog1;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Вспомогательная функцуия */
    void (*Handler)(/* in */ void);

    /* Данные экземпляра */
    uint32_t m_Period;
	uint32_t m_Mode;
	bool_t m_flag;

} CEcoWatchDog1, *CEcoWatchDog1Ptr;

/* Инициализация экземпляра */
int16_t initCEcoWatchDog1(/*in*/ struct IEcoWatchDog1* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t createCEcoWatchDog1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoWatchDog1** ppIEcoWatchDog1);
/* Удаление */
void deleteCEcoWatchDog1(/* in */ IEcoWatchDog1* pIEcoWatchDog1);

#endif /* __C_ECOWATCHDOG1_H__ */
