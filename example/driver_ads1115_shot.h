/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_ads1115_shot.h
 * @brief     driver ads1115 shot header file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-02-13
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/02/13  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/10/13  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_ADS1115_SHOT_H
#define DRIVER_ADS1115_SHOT_H

#include "driver_ads1115_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup ads1115_example_driver
 * @{
 */

/**
 * @brief ads1115 shot example default definition
 */
#define ADS1115_SHOT_DEFAULT_RANGE        ADS1115_RANGE_6P144V        /**< set range 6.144V */
#define ADS1115_SHOT_DEFAULT_RATE         ADS1115_RATE_128SPS         /**< set 128 SPS */

/**
 * @brief     shot example init
 * @param[in] addr iic device address
 * @param[in] channel adc channel
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t ads1115_shot_init(ads1115_address_t addr, ads1115_channel_t channel);

/**
 * @brief      shot example read
 * @param[out] *s pointer to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t ads1115_shot_read(float *s);

/**
 * @brief  shot example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ads1115_shot_deinit(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
