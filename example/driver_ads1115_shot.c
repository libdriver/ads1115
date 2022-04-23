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
 * @file      driver_ads1115_shot.c
 * @brief     driver ads1115 shot source file
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

#include "driver_ads1115_shot.h"

static ads1115_handle_t gs_handle;        /**< ads1115 handle */

/**
 * @brief     shot example init
 * @param[in] addr is the iic device address
 * @param[in] channel is the adc channel
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t ads1115_shot_init(ads1115_address_t addr, ads1115_channel_t channel)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_ADS1115_LINK_INIT(&gs_handle, ads1115_handle_t); 
    DRIVER_ADS1115_LINK_IIC_INIT(&gs_handle, ads1115_interface_iic_init);
    DRIVER_ADS1115_LINK_IIC_DEINIT(&gs_handle, ads1115_interface_iic_deinit);
    DRIVER_ADS1115_LINK_IIC_READ(&gs_handle, ads1115_interface_iic_read);
    DRIVER_ADS1115_LINK_IIC_WRITE(&gs_handle, ads1115_interface_iic_write);
    DRIVER_ADS1115_LINK_DELAY_MS(&gs_handle, ads1115_interface_delay_ms);
    DRIVER_ADS1115_LINK_DEBUG_PRINT(&gs_handle, ads1115_interface_debug_print);
    
    /* set addr pin */
    res = ads1115_set_addr_pin(&gs_handle, addr);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set addr failed.\n");
        
        return 1;
    }
    
    /* ads1115 init */
    res = ads1115_init(&gs_handle);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: init failed.\n");
        
        return 1;
    }
    
    /* set channel */
    res = ads1115_set_channel(&gs_handle, channel);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set channel failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default range */
    res = ads1115_set_range(&gs_handle, ADS1115_SHOT_DEFAULT_RANGE);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default rate */
    res = ads1115_set_rate(&gs_handle, ADS1115_SHOT_DEFAULT_RATE);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable compare */
    res = ads1115_set_compare(&gs_handle, ADS1115_BOOL_FALSE);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set compare failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }

    return 0;
}

/**
 * @brief      shot example read
 * @param[out] *s points to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t ads1115_shot_read(float *s)
{
    int16_t raw;
  
    /* read data */
    if (ads1115_single_read(&gs_handle, (int16_t *)&raw, s) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  shot example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ads1115_shot_deinit(void)
{
    uint8_t res;
    
    /* deinit ads1115 */
    res = ads1115_deinit(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}
