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
 * @file      driver_ads1115_register_test.c
 * @brief     driver ads1115 register test source file
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
 
#include "driver_ads1115_register_test.h"
#include <stdlib.h>

static ads1115_handle_t gs_handle;        /**< ads1115 handle */

/**
 * @brief     register test
 * @param[in] addr is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t ads1115_register_test(ads1115_address_t addr)
{
    uint8_t res;
    int16_t high_threshold;
    int16_t low_threshold;
    int16_t high_threshold_before;
    int16_t low_threshold_before;
    int16_t reg;
    float f_reg;
    float f_reg_check;
    ads1115_info_t info;
    ads1115_channel_t channel;
    ads1115_range_t range;
    ads1115_pin_t pin;
    ads1115_compare_t compare;
    ads1115_rate_t rate;
    ads1115_comparator_queue_t comparator_queue;
    ads1115_address_t addr_pin;
    ads1115_bool_t enable;

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
    
    /* start register test */
    ads1115_interface_debug_print("ads1115: start register test.\n");
    
    /* ads1115_set_addr_pin/ads1115_get_addr_pin test */
    ads1115_interface_debug_print("ads1115: ads1115_set_addr_pin/ads1115_get_addr_pin test.\n");
    
    /* set ADDR_GND */
    res = ads1115_set_addr_pin(&gs_handle, ADS1115_ADDR_GND);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set addr pin failed.\n");
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set addr pin ground.\n");
    res = ads1115_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get addr pin failed.\n");
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check addr pin %s.\n", addr_pin == ADS1115_ADDR_GND ? "ok" : "error");
    
    /* set ADDR_VCC */
    res = ads1115_set_addr_pin(&gs_handle, ADS1115_ADDR_VCC);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set addr pin failed.\n");
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set addr pin vcc.\n");
    res = ads1115_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get addr pin failed.\n");
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check addr pin %s.\n", addr_pin == ADS1115_ADDR_VCC ? "ok" : "error");
    
    /* set ADDR_SDA */
    res = ads1115_set_addr_pin(&gs_handle, ADS1115_ADDR_SDA);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set addr pin failed.\n");
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set addr pin sda.\n");
    res = ads1115_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get addr pin failed.\n");
     
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check addr pin %s.\n", addr_pin == ADS1115_ADDR_SDA ? "ok" : "error");
    
    /* set ADDR_SCL */
    res = ads1115_set_addr_pin(&gs_handle, ADS1115_ADDR_SCL);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set addr pin failed.\n");
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set addr pin scl.\n");
    res = ads1115_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get addr pin failed.\n");
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check addr pin %s.\n", addr_pin == ADS1115_ADDR_SCL ? "ok" : "error");
    
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
    
    /* ads1115_set_channel/ads1115_get_channel test */
    ads1115_interface_debug_print("ads1115: ads1115_set_channel/ads1115_get_channel test.\n");
    
    /* AIN0 to GND */
    res = ads1115_set_channel(&gs_handle, ADS1115_CHANNEL_AIN0_GND);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set channel failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set channel ain0_ground.\n");
    res = ads1115_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get channel failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check channel %s.\n", channel == ADS1115_CHANNEL_AIN0_GND ? "ok" : "error");
    
    /* AIN1 to GND */
    res = ads1115_set_channel(&gs_handle, ADS1115_CHANNEL_AIN1_GND);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set channel failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set channel ain1_ground.\n");
    res = ads1115_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get channel failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check channel %s.\n", channel == ADS1115_CHANNEL_AIN1_GND ? "ok" : "error");
    
    /* AIN2 to GND */
    res = ads1115_set_channel(&gs_handle, ADS1115_CHANNEL_AIN2_GND);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set channel failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set channel ain2_ground.\n");
    res = ads1115_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get channel failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check channel %s.\n", channel == ADS1115_CHANNEL_AIN2_GND ? "ok" : "error");
    
    /* AIN3 to GND */
    res = ads1115_set_channel(&gs_handle, ADS1115_CHANNEL_AIN3_GND);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set channel failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set channel ain3_ground.\n");
    res = ads1115_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get channel failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check channel %s.\n", channel == ADS1115_CHANNEL_AIN3_GND ? "ok" : "error");
    
    /* AIN0 to AIN1 */
    res = ads1115_set_channel(&gs_handle, ADS1115_CHANNEL_AIN0_AIN1);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set channel failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set channel ain0_ain1.\n");
    res = ads1115_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get channel failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check channel %s.\n", channel == ADS1115_CHANNEL_AIN0_AIN1 ? "ok" : "error");
    
    /* AIN0 to AIN3 */
    res = ads1115_set_channel(&gs_handle, ADS1115_CHANNEL_AIN0_AIN3);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set channel failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set channel ain0_ain3.\n");
    res = ads1115_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get channel failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check channel %s.\n", channel == ADS1115_CHANNEL_AIN0_AIN3 ? "ok" : "error");
    
    /* AIN1 to AIN3 */
    res = ads1115_set_channel(&gs_handle, ADS1115_CHANNEL_AIN1_AIN3);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set channel failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set channel ain1_ain3.\n");
    res = ads1115_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get channel failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check channel %s.\n", channel == ADS1115_CHANNEL_AIN1_AIN3 ? "ok" : "error");
    
    /* AIN2 to AIN3 */
    res = ads1115_set_channel(&gs_handle, ADS1115_CHANNEL_AIN2_AIN3);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set channel failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set channel ain2_ain3.\n");
    res = ads1115_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get channel failed.\n");
        (void)ads1115_deinit(&gs_handle);
       
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check channel %s.\n", channel == ADS1115_CHANNEL_AIN2_AIN3 ? "ok" : "error");
    
    /* ads1115_set_range/ads1115_get_range test */
    ads1115_interface_debug_print("ads1115: ads1115_set_range/ads1115_get_range test.\n");
    
    /* set 6.144V */
    res = ads1115_set_range(&gs_handle, ADS1115_RANGE_6P144V);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set range 6.144V.\n");
    res = ads1115_get_range(&gs_handle, &range);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check range %s.\n", range == ADS1115_RANGE_6P144V ? "ok" : "error");
    
    /* set 4.096V */
    res = ads1115_set_range(&gs_handle, ADS1115_RANGE_4P096V);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set range 4.096V.\n");
    res = ads1115_get_range(&gs_handle, &range);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check range %s.\n", range == ADS1115_RANGE_4P096V ? "ok" : "error");
    
    /* set 2.048V */
    res = ads1115_set_range(&gs_handle, ADS1115_RANGE_2P048V);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set range 2.048V.\n");
    res = ads1115_get_range(&gs_handle, &range);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check range %s.\n", range == ADS1115_RANGE_2P048V ? "ok" : "error");
    
    /* set 1.024V */
    res = ads1115_set_range(&gs_handle, ADS1115_RANGE_1P024V);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set range 1.024V.\n");
    res = ads1115_get_range(&gs_handle, &range);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check range %s.\n", range == ADS1115_RANGE_1P024V ? "ok" : "error");
    
    /* set 0.512V */
    res = ads1115_set_range(&gs_handle, ADS1115_RANGE_0P512V);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set range 0.512V.\n");
    res = ads1115_get_range(&gs_handle, &range);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check range %s.\n", range == ADS1115_RANGE_0P512V ? "ok" : "error");
    
    /* set 0.256V */
    res = ads1115_set_range(&gs_handle, ADS1115_RANGE_0P256V);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set range 0.256V.\n");
    res = ads1115_get_range(&gs_handle, &range);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check range %s.\n", range == ADS1115_RANGE_0P256V ? "ok" : "error");
    
    /* ads1115_set_alert_pin/ads1115_get_alert_pin test */
    ads1115_interface_debug_print("ads1115: ads1115_set_alert_pin/ads1115_get_alert_pin test.\n");
    
    /* pin_low */
    res = ads1115_set_alert_pin(&gs_handle, ADS1115_PIN_LOW);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set alert pin failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set alert pin low.\n");
    res = ads1115_get_alert_pin(&gs_handle, &pin);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get alert pin failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check alert pin %s.\n", pin == ADS1115_PIN_LOW ? "ok" : "error");
    
    /* pin_high */
    res = ads1115_set_alert_pin(&gs_handle, ADS1115_PIN_HIGH);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set alert pin failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set alert pin high.\n");
    res = ads1115_get_alert_pin(&gs_handle, &pin);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get alert pin failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check alert pin %s.\n", pin == ADS1115_PIN_HIGH ? "ok" : "error");
    
    /* ads1115_set_compare_mode/ads1115_get_compare_mode test */
    ads1115_interface_debug_print("ads1115: ads1115_set_compare_mode/ads1115_get_compare_mode test.\n");
    
    /* set threshold */
    res = ads1115_set_compare_mode(&gs_handle, ADS1115_COMPARE_THRESHOLD);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set compare failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set compare threshold.\n");
    res = ads1115_get_compare_mode(&gs_handle, &compare);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get compare failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check compare %s.\n", compare == ADS1115_COMPARE_THRESHOLD ? "ok" : "error");
    
    /* set window */
    res = ads1115_set_compare_mode(&gs_handle, ADS1115_COMPARE_WINDOW);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set compare failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set compare window.\n");
    res = ads1115_get_compare_mode(&gs_handle, &compare);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get compare failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check compare %s.\n", compare == ADS1115_COMPARE_WINDOW ? "ok" : "error");
    
    /* ads1115_set_rate/ads1115_get_rate test */
    ads1115_interface_debug_print("ads1115: ads1115_set_rate/ads1115_get_rate test.\n");
    
    /* set 8SPS */
    res = ads1115_set_rate(&gs_handle, ADS1115_RATE_8SPS);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set rate 8 sps.\n");
    res = ads1115_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check rate %s.\n", rate == ADS1115_RATE_8SPS ? "ok" : "error");
    
    /* set 16SPS */
    res = ads1115_set_rate(&gs_handle, ADS1115_RATE_16SPS);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set rate 16 sps.\n");
    res = ads1115_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check rate %s.\n", rate == ADS1115_RATE_16SPS ? "ok" : "error");
    
    /* set 32SPS */
    res = ads1115_set_rate(&gs_handle, ADS1115_RATE_32SPS);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set rate 32 sps.\n");
    res = ads1115_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check rate %s.\n", rate == ADS1115_RATE_32SPS ? "ok" : "error");
    
    /* set 64SPS */
    res = ads1115_set_rate(&gs_handle, ADS1115_RATE_64SPS);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set rate 64 sps.\n");
    res = ads1115_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check rate %s.\n", rate == ADS1115_RATE_64SPS ? "ok" : "error");
    
    /* set 128SPS */
    res = ads1115_set_rate(&gs_handle, ADS1115_RATE_128SPS);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set rate 128 sps.\n");
    res = ads1115_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check rate %s.\n", rate == ADS1115_RATE_128SPS ? "ok" : "error");
    
    /* set 250SPS */
    res = ads1115_set_rate(&gs_handle, ADS1115_RATE_250SPS);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set rate 250 sps.\n");
    res = ads1115_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check rate %s.\n", rate == ADS1115_RATE_250SPS ? "ok" : "error");
    
    /* set 475SPS */
    res = ads1115_set_rate(&gs_handle, ADS1115_RATE_475SPS);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set rate 475 sps.\n");
    res = ads1115_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check rate %s.\n", rate == ADS1115_RATE_475SPS ? "ok" : "error");
    
    /* set 860SPS */
    res = ads1115_set_rate(&gs_handle, ADS1115_RATE_860SPS);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set rate 860 sps.\n");
    res = ads1115_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get rate failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check rate %s.\n", rate == ADS1115_RATE_860SPS ? "ok" : "error");
    
    /* ads1115_set_comparator_queue/ads1115_get_comparator_queue test */
    ads1115_interface_debug_print("ads1115: ads1115_set_comparator_queue/ads1115_get_comparator_queue test.\n");
    
    /* none conv */
    res = ads1115_set_comparator_queue(&gs_handle, ADS1115_COMPARATOR_QUEUE_NONE_CONV);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set comparator queue failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set comparator queue none.\n");
    res = ads1115_get_comparator_queue(&gs_handle, &comparator_queue);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get comparator queue failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check comparator queue %s.\n", comparator_queue == ADS1115_COMPARATOR_QUEUE_NONE_CONV ? "ok" : "error");
    
    /* 1 conv */
    res = ads1115_set_comparator_queue(&gs_handle, ADS1115_COMPARATOR_QUEUE_1_CONV);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set comparator queue failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set comparator queue 1 conv.\n");
    res = ads1115_get_comparator_queue(&gs_handle, &comparator_queue);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get comparator queue failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check comparator queue %s.\n", comparator_queue == ADS1115_COMPARATOR_QUEUE_1_CONV ? "ok" : "error");
    
    /* 2 conv */
    res = ads1115_set_comparator_queue(&gs_handle, ADS1115_COMPARATOR_QUEUE_2_CONV);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set comparator queue failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set comparator queue 2 conv.\n");
    res = ads1115_get_comparator_queue(&gs_handle, &comparator_queue);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get comparator queue failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check comparator queue %s.\n", comparator_queue == ADS1115_COMPARATOR_QUEUE_2_CONV ? "ok" : "error");
    
    /* 4 conv */
    res = ads1115_set_comparator_queue(&gs_handle, ADS1115_COMPARATOR_QUEUE_4_CONV);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set comparator queue failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set comparator queue 4 conv.\n");
    res = ads1115_get_comparator_queue(&gs_handle, &comparator_queue);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get comparator queue failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check comparator queue %s.\n", comparator_queue == ADS1115_COMPARATOR_QUEUE_4_CONV ? "ok" : "error");
    
    /* ads1115_set_compare_threshold/ads1115_get_compare_threshold test */
    ads1115_interface_debug_print("ads1115: ads1115_set_compare_threshold/ads1115_get_compare_threshold test.\n");
    high_threshold_before = rand()%8196;
    low_threshold_before = -rand()%8196;
    res = ads1115_set_compare_threshold(&gs_handle, high_threshold_before, low_threshold_before);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set compare threshold failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: set high threshold %d low threshold %d.\n", high_threshold_before, low_threshold_before);
    res = ads1115_get_compare_threshold(&gs_handle, (int16_t *)&high_threshold, (int16_t *)&low_threshold);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get compare threshold failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check high threshold %s.\n", high_threshold == high_threshold_before ? "ok" : "error");
    ads1115_interface_debug_print("ads1115: check low threshold %s.\n", low_threshold == low_threshold_before ? "ok" : "error");
    
    /* ads1115_set_compare/ads1115_get_compare test */
    ads1115_interface_debug_print("ads1115: ads1115_set_compare/ads1115_get_compare test.\n");
    
    /* enable compare */
    res = ads1115_set_compare(&gs_handle, ADS1115_BOOL_TRUE);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set compare failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: enable compare.\n");
    res = ads1115_get_compare(&gs_handle, (ads1115_bool_t *)&enable);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get compare failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check compare %s.\n", enable == ADS1115_BOOL_TRUE ? "ok" : "error");
    
    /* disable compare */
    res = ads1115_set_compare(&gs_handle, ADS1115_BOOL_FALSE);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set compare failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: disable compare.\n");
    res = ads1115_get_compare(&gs_handle, (ads1115_bool_t *)&enable);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: get compare failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check compare %s.\n", enable == ADS1115_BOOL_FALSE ? "ok" : "error");
    
    /* ads1115_convert_to_register test */
    ads1115_interface_debug_print("ads1115: ads1115_convert_to_register test.\n");
    
    /* set 6.144V */
    res = ads1115_set_range(&gs_handle, ADS1115_RANGE_6P144V);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    f_reg = -(rand()%6144)/1000.0f;
    ads1115_interface_debug_print("ads1115: convert to register %0.2fV.\n", f_reg);
    res = ads1115_convert_to_register(&gs_handle, f_reg, (int16_t *)&reg);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: convert to register failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check convert to register %s.\n", reg == (int16_t)(f_reg * 32768.0f / 6.144f) ? "ok" : "error");
    
    /* set 4.096V */
    res = ads1115_set_range(&gs_handle, ADS1115_RANGE_4P096V);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    f_reg = (rand()%4096)/1000.0f;
    ads1115_interface_debug_print("ads1115: convert to register %0.2fV.\n", f_reg);
    res = ads1115_convert_to_register(&gs_handle, f_reg, (int16_t *)&reg);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: convert to register failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check convert to register %s.\n", reg == (int16_t)(f_reg * 32768.0f / 4.096f) ? "ok" : "error");
    
    /* set 2.048V */
    res = ads1115_set_range(&gs_handle, ADS1115_RANGE_2P048V);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    f_reg = -(rand()%2048)/1000.0f;
    ads1115_interface_debug_print("ads1115: convert to register %0.2fV.\n", f_reg);
    res = ads1115_convert_to_register(&gs_handle, f_reg, (int16_t *)&reg);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: convert to register failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check convert to register %s.\n", reg == (int16_t)(f_reg * 32768.0f / 2.048f) ? "ok" : "error");
    
    /* set 1.024V */
    res = ads1115_set_range(&gs_handle, ADS1115_RANGE_1P024V);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    f_reg = (rand()%1024)/1000.0f;
    ads1115_interface_debug_print("ads1115: convert to register %0.2fV.\n", f_reg);
    res = ads1115_convert_to_register(&gs_handle, f_reg, (int16_t *)&reg);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: convert to register failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check convert to register %s.\n", reg == (int16_t)(f_reg * 32768.0f / 1.024f) ? "ok" : "error");
    
    /* set 0.512V */
    res = ads1115_set_range(&gs_handle, ADS1115_RANGE_0P512V);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    f_reg = -(rand()%512)/1000.0f;
    ads1115_interface_debug_print("ads1115: convert to register %0.2fV.\n", f_reg);
    res = ads1115_convert_to_register(&gs_handle, f_reg, (int16_t *)&reg);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: convert to register failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check convert to register %s.\n", reg == (int16_t)(f_reg * 32768.0f / 0.512f) ? "ok" : "error");
    
    /* set 0.256V */
    res = ads1115_set_range(&gs_handle, ADS1115_RANGE_0P256V);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: set range failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    f_reg = (rand()%256)/1000.0f;
    ads1115_interface_debug_print("ads1115: convert to register %0.2fV.\n", f_reg);
    res = ads1115_convert_to_register(&gs_handle, f_reg, (int16_t *)&reg);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: convert to register failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: check convert to register %d.\n", reg);
    res = ads1115_convert_to_data(&gs_handle, reg, (float *)&f_reg_check);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: convert to data failed.\n");
        (void)ads1115_deinit(&gs_handle);
        
        return 1;
    }
    ads1115_interface_debug_print("ads1115: convert to data %0.2fV.\n", f_reg_check);
    
    /* finish register */
    ads1115_interface_debug_print("ads1115: finish register test.\n");
    (void)ads1115_deinit(&gs_handle);
    
    return 0;
}
