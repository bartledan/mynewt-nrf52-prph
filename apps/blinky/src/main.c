/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <assert.h>
#include <string.h>

#include "sysinit/sysinit.h"
#include "os/os.h"
#include "bsp/bsp.h"
#include "hal/hal_gpio.h"
#ifdef ARCH_sim
#include "mcu/mcu_sim.h"
#endif
#include "nrf_gpio.h"

static volatile int g_task1_loops;

/* For LED toggling */
int g_led_pin;

/**
 * main
 *
 * The main task for the project. This function initializes packages,
 * and then blinks the BSP LED in a loop.
 *
 * @return int NOTE: this function should never return!
 */
int
main(int argc, char **argv)
{
    int rc;
#ifdef ARCH_sim
    mcu_sim_parse_args(argc, argv);
#endif

    sysinit();

    g_led_pin = LED_BLINK_PIN;

    /*
     * A better method is to use hal_gpio_init_out, but
     * this example is to show how one can use the nordic's API
     * from the SDK.
     */
    nrf_gpio_pin_dir_set(g_led_pin, NRF_GPIO_PIN_DIR_OUTPUT);

    while (1) {
        ++g_task1_loops;

        /* Wait one second.
         *
         * XXX: This is not a bare metal application (refer the target config),
         * we need to use a OS specific method for generating delay, so that
         * the WDT does not get fired. In other words, nrf_delay_ms will
         * __not__ work.
         */
        os_time_delay(OS_TICKS_PER_SEC);

        /* Toggle the LED
         * using Nordic's SDK api instead of hal_gpio_toggle
         */
        nrf_gpio_pin_toggle(g_led_pin);
    }
    assert(0);

    return rc;
}

