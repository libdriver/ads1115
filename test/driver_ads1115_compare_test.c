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
 * @file      driver_ads1115_compare_test.c
 * @brief     driver ads1115 compare test source file
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

#include "driver_ads1115_compare_test.h"

static ads1115_handle_t gs_handle;

/**
 * @brief     compare test
 * @param[in] addr is the iic device address
 * @param[in] channel is the adc channel
 * @param[in] compare is the interrupt compare mode
 * @param[in] f_high_threshold is the interrupt high threshold
 * @param[in] f_low_threshold is the interrupt low threshold
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t ads1115_compare_test(ads1115_address_t addr, ads1115_channel_t channel, ads1115_compare_t compare, 
                             float f_high_threshold, float f_low_threshold, uint32_t times)
{
    uint8_t res;
    int16_t high_threshold;
    int16_t low_threshold;
    uint32_t i;
    ads1115_info_t info;
    
    /* link interface function */
    DRIVER_ADS1115_LINK_INIT(&gs_handle, ads1115_handle_t); 
    DRIVER_ADS1115_LINK_IIC_INIT(&gs_handle, ads1115_interface_iic_init);
    DRIVER_ADS1115_LINK_IIC_DEINIT(&gs_handle, ads1115_interface_iic_deinit);
    DRIVER_ADS1115_LINK_IIC_READ(&gs_handle, ads1115_interface_iic_read);
    DRIVER_ADS1115_LINK_IIC_WRITE(&gs_handle, ads1115_interface_iic_write);
    DRIVER_ADS1115_LINK_DELAY_MS(&gs_handle, ads1115_interface_delay_ms);
    DRIVER_ADS1115_LINK_DEBUG_PRINT(&gs_handle, ads1115_interface_debug_print);
    
    /* get information */
    res = ads1115_info(&info);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip info */
        ads1115_interface_debug_print("ads1115: chip is %s.\n", info.chip_name);
        ads1115_interface_debug_print("ads1115: manufacturer is %s.\n", info.manufacturer_name);
        ads1115_interface_debug_print("ads1115: interface is %s.\n", info.interface);
        ads1115_interface_debug_print("ads1115: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ads1115_interface_debug_print("ads1115: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ads1115_interface_debug_print("ads1115: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ads1115_interface_debug_print("ads1115: max current is %0.2fmA.\n", info.max_current_ma);
        ads1115_interface_debug_print("ads1115: max temperature is %0.1fC.\n", info.temperature_max);
        ads1115_interface_debug_print("ads1115: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
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
    
    /* set range 6.144V */
    res = ads1115_set_range(&gs_handle, ADS1115_RANGE_6P144V);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set alert pin low */
    res = ads1115_set_alert_pin(&gs_handle, ADS1115_PIN_LOW);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set alert pin failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set compare mode */
    res = ads1115_set_compare_mode(&gs_handle, compare);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set compare mode failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set rate 128SPS */
    res = ads1115_set_rate(&gs_handle, ADS1115_RATE_128SPS);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set comparator queue 2 conv */
    res = ads1115_set_comparator_queue(&gs_handle, ADS1115_COMPARATOR_QUEUE_2_CONV);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set comparator queue failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable compare */
    res = ads1115_set_compare(&gs_handle, ADS1115_BOOL_TRUE);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set compare failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    
    /* convert to register */
    res = ads1115_convert_to_register(&gs_handle, f_high_threshold, (int16_t *)&high_threshold);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: convert to high threshold register failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    
    /* convert to register */
    res = ads1115_convert_to_register(&gs_handle, f_low_threshold, (int16_t *)&low_threshold);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: convert to low threshold register failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set compare threshold */
    res = ads1115_set_compare_threshold(&gs_handle, high_threshold, low_threshold);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set compare threshold failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    
    /* start compare mode test */
    ads1115_interface_debug_print("ads1115: start compare mode test.\n");
    for (i=0; i<times; i++)
    {
        int16_t raw;
        float s;
        
        ads1115_interface_debug_print("ads1115: run %d times.\n", i+1);
    
        /* single read */
        res = ads1115_single_read(&gs_handle, (int16_t *)&raw, (float *)&s);
        if (res != 0)
        {
            ads1115_interface_debug_print("ads1115: read failed.\n");
            (void)ads1115_deinit(&gs_handle);
            
            return 1;
        }
        if (s > f_high_threshold)
        {
            ads1115_interface_debug_print("ads1115: voltage is over high threshold, please see alert pin.\n");
        }
        if (s < f_low_threshold)
        {
            ads1115_interface_debug_print("ads1115: voltage is below low threshold, please see alert pin.\n");
        }
        ads1115_interface_delay_ms(1000);
    }

    /* finish compare mode test */
    ads1115_interface_debug_print("ads1115: finish compare mode test.\n");
    (void)ads1115_deinit(&gs_handle);
    
    return 0;
}
