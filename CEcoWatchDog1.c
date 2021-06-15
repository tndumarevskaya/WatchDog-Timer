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
 *   Данный исходный код описывает реализацию интерфейсов CEcoWatchDog1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "CEcoWatchDog1.h"

void enable(int msec);

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoWatchDog1
 * </описание>
 *
 */
int16_t CEcoWatchDog1_QueryInterface(/* in */ struct IEcoWatchDog1* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoWatchDog1* pCMe = (CEcoWatchDog1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return result;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoWatchDog1) ) {
        *ppv = &pCMe->m_pVTblIEcoWatchDog1;
        pCMe->m_pVTblIEcoWatchDog1->AddRef((IEcoWatchDog1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoWatchDog1;
        pCMe->m_pVTblIEcoWatchDog1->AddRef((IEcoWatchDog1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoWatchDog1
 * </описание>
 *
 */
uint32_t CEcoWatchDog1_AddRef(/* in */ struct IEcoWatchDog1* me) {
    CEcoWatchDog1* pCMe = (CEcoWatchDog1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
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
 *   Функция Release для интерфейса IEcoWatchDog1
 * </описание>
 *
 */
uint32_t CEcoWatchDog1_Release(/* in */ struct IEcoWatchDog1* me) {
    CEcoWatchDog1* pCMe = (CEcoWatchDog1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoWatchDog1((IEcoWatchDog1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Enable
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
int16_t CEcoWatchDog1_Enable(/* in */ struct IEcoWatchDog1* me, /* in */ uint32_t msec) {
    CEcoWatchDog1* pCMe = (CEcoWatchDog1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Сохраняем период */
    pCMe->m_Period = msec;

    /* Два варианта настройки */
    /* Вариант первый - закоментирован */
    // enable(msec);
    /* ИЛИ */
    /* Вариант второй - альтернативный. Если еспользовать вавриан 1, то код ниже нужно закоментировать */
    //WDTCSR |= (1<<WDCE) | (1<<WDE);
    (*(volatile uint8_t *)(0x60)) |= (1<<4) | (0<<3);

    if (msec == 16)
        //WDTCSR = (1<<WDIE) | (1<<WDE) | (0<<WDP0) | (0<<WDP1) | (0<<WDP2) | (0<<WDP3);
        (*(volatile uint8_t *)(0x60)) |= (0<<4) | (0<<3) | (0<<0) | (0<<1) | (0<<2) | (0<<5);
    else if (msec == 32)
        //WDTCSR = (1<<WDIE) | (1<<WDE) | (1<<WDP0) | (0<<WDP1) | (0<<WDP2) | (0<<WDP3);
        (*(volatile uint8_t *)(0x60)) |= (0<<4) | (0<<3) | (1<<0) | (0<<1) | (0<<2) | (0<<5);
    else if (msec == 64)
        //WDTCSR = (1<<WDIE) | (1<<WDE) | (0<<WDP0) | (1<<WDP1) | (0<<WDP2) | (0<<WDP3);
        (*(volatile uint8_t *)(0x60)) |= (0<<4) | (0<<3) | (0<<0) | (1<<1) | (0<<2) | (0<<5);
    else if (msec == 125)
        //WDTCSR = (1<<WDIE) | (1<<WDE) | (1<<WDP0) | (1<<WDP1) | (0<<WDP2) | (0<<WDP3);
        (*(volatile uint8_t *)(0x60)) |= (0<<4) | (0<<3) | (1<<0) | (1<<1) | (0<<2) | (0<<5);
    else if (msec == 250)
        //WDTCSR = (1<<WDIE) | (1<<WDE) | (0<<WDP0) | (0<<WDP1) | (1<<WDP2) | (0<<WDP3);
        (*(volatile uint8_t *)(0x60)) |= (0<<4) | (0<<3) | (0<<0) | (0<<1) | (1<<2) | (0<<5);
    else if (msec == 500)
        //WDTCSR = (1<<WDIE) | (1<<WDE) | (1<<WDP0) | (0<<WDP1) | (1<<WDP2) | (0<<WDP3);
        (*(volatile uint8_t *)(0x60)) |= (0<<4) | (0<<3) | (1<<0) | (0<<1) | (1<<2) | (0<<5);
    else if (msec == 1000)
        //WDTCSR = (1<<WDIE) | (1<<WDE) | (0<<WDP0) | (1<<WDP1) | (1<<WDP2) | (0<<WDP3);
        (*(volatile uint8_t *)(0x60)) |= (0<<4) | (0<<3) | (0<<0) | (1<<1) | (1<<2) | (0<<5);
    else if (msec == 2000)
        //WDTCSR = (1<<WDIE) | (1<<WDE) | (1<<WDP0) | (1<<WDP1) | (1<<WDP2) | (0<<WDP3);
        (*(volatile uint8_t *)(0x60)) |= (0<<4) | (0<<3) | (1<<0) | (1<<1) | (1<<2) | (0<<5);
    else if (msec == 4000)
        //WDTCSR = (1<<WDIE) | (1<<WDE) | (0<<WDP0) | (0<<WDP1) | (0<<WDP2) | (1<<WDP3);
        (*(volatile uint8_t *)(0x60)) |= (0<<4) | (0<<3) | (0<<0) | (0<<1) | (0<<2) | (1<<5);
    else if (msec == 8000)
        //WDTCSR = (1<<WDIE) | (1<<WDE) | (1<<WDP0) | (0<<WDP1) | (0<<WDP2) | (1<<WDP3);
        (*(volatile uint8_t *)(0x60)) |= (0<<4) | (0<<3) | (1<<0) | (0<<1) | (0<<2) | (1<<5);

    __asm__ __volatile__ ("sei" ::: "memory");

    return 0;
}

/*
 *
 * <сводка>
 *   Функция set_Mode
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 * 1 - interrupt, 2 - reset, 3 - interrupt and reset
 */
int16_t CEcoWatchDog1_set_Mode(/* in */ struct IEcoWatchDog1* me, /* in */ uint32_t mode) {
    CEcoWatchDog1* pCMe = (CEcoWatchDog1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Сохраняем период */
    pCMe->m_Mode = mode;

    (*(volatile uint8_t *)(0x60)) |= (1<<4) | (0<<3);

    if (mode == 1)
        //WDTCSR = (1<<WDIE) | (0<<WDE);
        (*(volatile uint8_t *)(0x60)) = (1<<6) | (0<<3);
    else if (mode == 2)
        //WDTCSR = (0<<WDIE) | (1<<WDE);
        (*(volatile uint8_t *)(0x60)) = (0<<6) | (1<<3);
    else if (mode == 3)
        //WDTCSR = (1<<WDIE) | (1<<WDE);
        (*(volatile uint8_t *)(0x60)) = (1<<6) | (1<<3);
		
    return 0;
}
/*
 *
 * <сводка>
 *   Функция Disable
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
int16_t CEcoWatchDog1_Disable(/* in */ struct IEcoWatchDog1* me) {
    CEcoWatchDog1* pCMe = (CEcoWatchDog1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Disable
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
int16_t CEcoWatchDog1_set_Handler(/* in */ struct IEcoWatchDog1* me, /* in */ void* funcHandler) {
    CEcoWatchDog1* pCMe = (CEcoWatchDog1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }
    /* Устанавливаем новый обработчик */
    pCMe->Handler = funcHandler;

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Handler
 * </сводка>
 *
 * <описание>
 *   Функция Handler - функция заглушка
 * </описание>
 *
 */
void CEcoWatchDog1_Handler() {
    return;
}

/*
 *
 * <сводка>
 *   Функция reset
 * </сводка>
 *
 * <описание>
 *   Функция reset
 * </описание>
 *
 */
int16_t CEcoWatchDog1_Reset(/* in */ struct IEcoWatchDog1* me) {
	CEcoWatchDog1* pCMe = (CEcoWatchDog1*)me;

	/* Проверка указателя */
	if (me == 0 ) {
		return -1;
	}
	
    __asm__ __volatile__ ("wdr");

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
int16_t initCEcoWatchDog1(/*in*/ struct IEcoWatchDog1* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoWatchDog1* pCMe = (CEcoWatchDog1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    return result;
}

/* Create Virtual Table */
IEcoWatchDog1VTbl g_xE42A4F19797C41CB82EC0263DDD2C0F4VTbl = {
    CEcoWatchDog1_QueryInterface,
    CEcoWatchDog1_AddRef,
    CEcoWatchDog1_Release,
    CEcoWatchDog1_Enable,
    CEcoWatchDog1_set_Mode,
    CEcoWatchDog1_Reset,
    CEcoWatchDog1_Disable,
    CEcoWatchDog1_set_Handler
};

/* Выделяем память под один экземпляр */
CEcoWatchDog1 g_xE42A4F19797C41CB82EC0263DDD2C0F4VTblWatchDog1 = {
    &g_xE42A4F19797C41CB82EC0263DDD2C0F4VTbl,
    0,
    CEcoWatchDog1_Handler,
    0
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
int16_t createCEcoWatchDog1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoWatchDog1** ppIEcoWatchDog1) {
    int16_t result = -1;
    CEcoWatchDog1* pCMe = 0;

    /* Проверка указателей */
    if (ppIEcoWatchDog1 == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение указателя на структуру компонента расположенной в области инициализированных данных */
    pCMe = &g_xE42A4F19797C41CB82EC0263DDD2C0F4VTblWatchDog1;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Инициализация данных */
    pCMe->m_Period = 1000;

    /* Возврат указателя на интерфейс */
    *ppIEcoWatchDog1 = (IEcoWatchDog1*)pCMe;

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
void deleteCEcoWatchDog1(/* in */ IEcoWatchDog1* pIEcoWatchDog1) {
    CEcoWatchDog1* pCMe = (CEcoWatchDog1*)pIEcoWatchDog1;
    if (pIEcoWatchDog1 != 0 ) {
    }
}

// Разрешение конфликта 
#define int8_t  no_int8_t
#define int16_t  no_int16_t
#define uint16_t  no_uint16_t
#define int32_t  no_int32_t
#define uint32_t  no_uint32_t
#define wchar_t no_wchar_t
#define int64_t no_int64_t

#include <avr/interrupt.h>
#include <avr/wdt.h>

ISR (WDT_vect) {
    g_xE42A4F19797C41CB82EC0263DDD2C0F4VTblWatchDog1.Handler();
}
