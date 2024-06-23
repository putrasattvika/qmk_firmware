/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 * Copyright (c) 2023 sekigon-gonnoc
 * Copyright (c) 2024 QMK
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */

#pragma once

// Note: we must undefine GPIO_IN and GPIO_OUT before including ChibiOS as those
// have been defined by pico-sdk. This header file is included by TinyUSB, which
// includes Pico-PIO-USB, which in turn includes pico-sdk.
//
// I'm not sure whether we should re-defined them afterwards, but this setup
// seems to work fine.
#ifdef GPIO_IN
#undef GPIO_IN
#endif

#ifdef GPIO_OUT
#undef GPIO_OUT
#endif

#include "ch.h"

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------+
// TASK API
//--------------------------------------------------------------------+
static inline void osal_task_delay(uint32_t msec) {
    chThdSleepMilliseconds(msec);
}

//--------------------------------------------------------------------+
// MUTEX API
//--------------------------------------------------------------------+

typedef mutex_t osal_mutex_def_t;
typedef osal_mutex_def_t* osal_mutex_t;

static inline osal_mutex_t osal_mutex_create(osal_mutex_def_t* mdef) {
    chMtxObjectInit(mdef);
    return mdef;
}

static inline bool osal_mutex_lock(osal_mutex_t mutex_hdl, uint32_t msec) {
    chMtxLock(mutex_hdl);
    return true;
}

static inline bool osal_mutex_unlock(osal_mutex_t mutex_hdl) {
    chMtxUnlock(mutex_hdl);
    return true;
}

//--------------------------------------------------------------------+
// QUEUE API
//--------------------------------------------------------------------+

// Must be included after osal_mutex_t is defined
#include "common/tusb_fifo.h"

typedef struct {
    tu_fifo_t ff;
    mutex_t mutex;
} osal_queue_def_t;

typedef osal_queue_def_t* osal_queue_t;

#define OSAL_QUEUE_DEF(_int_set, _name, _depth, _type)        \
    uint8_t _name##_buf[_depth*sizeof(_type)];                \
    osal_queue_def_t _name = {                                \
        .ff = TU_FIFO_INIT(_name##_buf, _depth, _type, false) \
    }

static inline osal_queue_t osal_queue_create(osal_queue_def_t* qdef) {
    chMtxObjectInit(&qdef->mutex);
    tu_fifo_clear(&qdef->ff);

    return (osal_queue_t) qdef;
}

static inline bool osal_queue_receive(osal_queue_t qhdl, void* data, uint32_t msec) {
    (void)msec;

    chMtxLock(&qhdl->mutex);
    bool success = tu_fifo_read(&qhdl->ff, data);
    chMtxUnlock(&qhdl->mutex);

    return success;
}

static inline bool osal_queue_send(osal_queue_t qhdl, void const * data, bool in_isr) {
    (void) in_isr;

    chMtxLock(&qhdl->mutex);
    bool success = tu_fifo_write(&qhdl->ff, data);
    chMtxUnlock(&qhdl->mutex);

    TU_ASSERT(success);

    return success;
}

static inline bool osal_queue_empty(osal_queue_t qhdl) {
    return tu_fifo_empty(&qhdl->ff);
}

#ifdef __cplusplus
}
#endif
