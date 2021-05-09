/**
 * Copyright (C) LibDriver 2015-2021 All rights reserved
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
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-02-13
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/02/13  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_ads1115_compare_test.h"
#include "driver_ads1115_mutichannel_test.h"
#include "driver_ads1115_read_test.h"
#include "driver_ads1115_register_test.h"
#include "driver_ads1115_basic.h"
#include "driver_ads1115_interrupt.h"
#include "driver_ads1115_shot.h"
#include "iic.h"
#include "gpio.h"

/**
 * @brief global var definition
 */
uint8_t g_flag;            /**< interrupt flag */

/**
 * @brief     ads1115 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t ads1115(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            ads1115_info_t info;
            
            /* print ads1115 info */
            ads1115_info(&info);
            ads1115_interface_debug_print("ads1115: chip is %s.\n", info.chip_name);
            ads1115_interface_debug_print("ads1115: manufacturer is %s.\n", info.manufacturer_name);
            ads1115_interface_debug_print("ads1115: interface is %s.\n", info.interface);
            ads1115_interface_debug_print("ads1115: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            ads1115_interface_debug_print("ads1115: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            ads1115_interface_debug_print("ads1115: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            ads1115_interface_debug_print("ads1115: max current is %0.2fmA.\n", info.max_current_ma);
            ads1115_interface_debug_print("ads1115: max temperature is %0.1fC.\n", info.temperature_max);
            ads1115_interface_debug_print("ads1115: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            ads1115_interface_debug_print("ads1115: SCL connected to GPIO3(BCM).\n");
            ads1115_interface_debug_print("ads1115: SDA connected to GPIO2(BCM).\n");
            ads1115_interface_debug_print("ads1115: INT connected to GPIO17(BCM).\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show ads1115 help */
            
            help:
            
            ads1115_interface_debug_print("ads1115 -i\n\tshow ads1115 chip and driver information.\n");
            ads1115_interface_debug_print("ads1115 -h\n\tshow ads1115 help.\n");
            ads1115_interface_debug_print("ads1115 -p\n\tshow ads1115 pin connections of the current board.\n");
            ads1115_interface_debug_print("ads1115 -t reg -a (VCC | GND | SCL | SDA)\n\trun ads1115 register test.times means test times.\n");
            ads1115_interface_debug_print("ads1115 -t read <times> -a (VCC | GND | SCL | SDA)\n\trun ads1115 read test.times means test times.\n");
            ads1115_interface_debug_print("ads1115 -t muti <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 "
                                          "| AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND)\n\trun ads1115 mutichannel test."
                                          "times means test times.\n");
            ads1115_interface_debug_print("ads1115 -t int <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 "
                                          "| AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND) -th <low_threshold> <high_threshold>"
                                          "\n\trun ads1115 interrupt test.");
            ads1115_interface_debug_print("times means test times.low_threshold and high_threshold means interrupt threshold.\n");
            ads1115_interface_debug_print("ads1115 -c read <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 "
                                          "| AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND)\n\trun ads1115 read function.times means read times.\n");
            ads1115_interface_debug_print("ads1115 -c shot <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 "
                                          "| AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND)\n\trun ads1115 shot function.times means read times.\n");
            ads1115_interface_debug_print("ads1115 -c int <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 "
                                          "| AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND) -m (THRESHOLD | WINDOW) -th <low_threshold> <high_threshold>"
                                          "\n\trun ads1115 interrupt function.");
            ads1115_interface_debug_print("times means read times.low_threshold and high_threshold means interrupt threshold.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 5)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* reg test */
            if (strcmp("reg", argv[2]) == 0)
            {
                ads1115_address_t addr;
                
                /* check iic address */
                if (strcmp("-a", argv[3]) != 0)
                {
                    return 5;
                }
                if (strcmp("GND", argv[4]) == 0)
                {
                    addr = ADS1115_ADDR_GND;
                }
                else if (strcmp("VCC", argv[4]) == 0)
                {
                    addr = ADS1115_ADDR_VCC;
                }
                else if (strcmp("SDA", argv[4]) == 0)
                {
                    addr = ADS1115_ADDR_SDA;
                }
                else if (strcmp("SCL", argv[4]) == 0)
                {
                    addr = ADS1115_ADDR_SCL;
                }
                else
                {
                    return 5;
                }
                
                /* run reg test */
                if (ads1115_register_test(addr))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 6)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* read test */
            if (strcmp("read", argv[2]) == 0)
            {
                ads1115_address_t addr;
                
                /* check iic address */
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("GND", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_GND;
                }
                else if (strcmp("VCC", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_VCC;
                }
                else if (strcmp("SDA", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_SDA;
                }
                else if (strcmp("SCL", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_SCL;
                }
                else
                {
                    return 5;
                }
                if (ads1115_read_test(addr, atoi(argv[3])))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 8)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* muti test */
            if (strcmp("muti", argv[2]) == 0)
            {
                ads1115_address_t addr;
                ads1115_channel_t channel;
                
                /* check iic address */
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("GND", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_GND;
                }
                else if (strcmp("VCC", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_VCC;
                }
                else if (strcmp("SDA", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_SDA;
                }
                else if (strcmp("SCL", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_SCL;
                }
                else
                {
                    return 5;
                }
                
                /* check channel */
                if (strcmp("-ch", argv[6]) != 0)
                {
                    return 5;
                }
                if (strcmp("AIN0_AIN1", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_AIN1;
                }
                else if (strcmp("AIN0_AIN3", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_AIN3;
                }
                else if (strcmp("AIN1_AIN3", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN1_AIN3;
                }
                else if (strcmp("AIN2_AIN3", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN2_AIN3;
                }
                else if (strcmp("AIN0_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_GND;
                }
                else if (strcmp("AIN1_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN1_GND;
                }
                else if (strcmp("AIN2_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN2_GND;
                }
                else if (strcmp("AIN3_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN3_GND;
                }
                else
                {
                    return 5;
                }
                if (ads1115_multichannel_test(addr, channel, atoi(argv[3])))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
            /* read function */
            if (strcmp("read", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t i, times;
                volatile float s;
                ads1115_address_t addr;
                ads1115_channel_t channel;
                
                /* check iic address */
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("GND", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_GND;
                }
                else if (strcmp("VCC", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_VCC;
                }
                else if (strcmp("SDA", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_SDA;
                }
                else if (strcmp("SCL", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_SCL;
                }
                else
                {
                    return 5;
                }
                
                /* check channel */
                if (strcmp("-ch", argv[6]) != 0)
                {
                    return 5;
                }
                if (strcmp("AIN0_AIN1", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_AIN1;
                }
                else if (strcmp("AIN0_AIN3", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_AIN3;
                }
                else if (strcmp("AIN1_AIN3", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN1_AIN3;
                }
                else if (strcmp("AIN2_AIN3", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN2_AIN3;
                }
                else if (strcmp("AIN0_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_GND;
                }
                else if (strcmp("AIN1_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN1_GND;
                }
                else if (strcmp("AIN2_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN2_GND;
                }
                else if (strcmp("AIN3_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN3_GND;
                }
                else
                {
                    return 5;
                }
                times = atoi(argv[3]);
                res = ads1115_basic_init(addr, channel);
                if (res)
                {
                    ads1115_interface_debug_print("ads1115: basic init failed.\n");
                    
                    return 1;
                }
                for (i=0; i<times; i++)
                {
                    res = ads1115_basic_read((float *)&s);
                    if (res)
                    {
                        ads1115_interface_debug_print("ads1115: basic read failed.\n");
                        ads1115_basic_deinit();
                        
                        return 1;
                    }
                    ads1115_interface_debug_print("ads1115: %d/%d.\n", i+1, times);
                    ads1115_interface_debug_print("ads1115: adc is %0.4fV.\n", s);
                    ads1115_interface_delay_ms(1000);
                }
                ads1115_basic_deinit();
                
                return 0;
            }
            
            /* shot function */
            else if (strcmp("shot", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t i, times;
                volatile float s;
                ads1115_address_t addr;
                ads1115_channel_t channel;
                
                /* check iic address */
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("GND", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_GND;
                }
                else if (strcmp("VCC", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_VCC;
                }
                else if (strcmp("SDA", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_SDA;
                }
                else if (strcmp("SCL", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_SCL;
                }
                else
                {
                    return 5;
                }
                
                /* check channel */
                if (strcmp("-ch", argv[6]) != 0)
                {
                    return 5;
                }
                if (strcmp("AIN0_AIN1", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_AIN1;
                }
                else if (strcmp("AIN0_AIN3", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_AIN3;
                }
                else if (strcmp("AIN1_AIN3", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN1_AIN3;
                }
                else if (strcmp("AIN2_AIN3", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN2_AIN3;
                }
                else if (strcmp("AIN0_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_GND;
                }
                else if (strcmp("AIN1_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN1_GND;
                }
                else if (strcmp("AIN2_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN2_GND;
                }
                else if (strcmp("AIN3_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN3_GND;
                }
                else
                {
                    return 5;
                }
                times = atoi(argv[3]);
                res = ads1115_shot_init(addr, channel);
                if (res)
                {
                    ads1115_interface_debug_print("ads1115: basic init failed.\n");
                    
                    return 1;
                }
                for (i=0; i<times; i++)
                {
                    res = ads1115_shot_read((float *)&s);
                    if (res)
                    {
                        ads1115_interface_debug_print("ads1115: basic read failed.\n");
                        ads1115_shot_deinit();
                        
                        return 1;
                    }
                    ads1115_interface_debug_print("ads1115: %d/%d.\n", i+1, times);
                    ads1115_interface_debug_print("ads1115: adc is %0.4fV.\n", s);
                    ads1115_interface_delay_ms(1000);
                }
                ads1115_shot_deinit();
                
                return 0;
            }
            
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 13)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* int test */
            if (strcmp("int", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t i;
                volatile uint32_t times;
                ads1115_compare_t compare;
                ads1115_address_t addr;
                ads1115_channel_t channel;
                
                /* check iic address */
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("GND", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_GND;
                }
                else if (strcmp("VCC", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_VCC;
                }
                else if (strcmp("SDA", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_SDA;
                }
                else if (strcmp("SCL", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_SCL;
                }
                else
                {
                    return 5;
                }
                
                /* check channel */
                if (strcmp("-ch", argv[6]) != 0)
                {
                    return 5;
                }
                if (strcmp("AIN0_AIN1", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_AIN1;
                }
                else if (strcmp("AIN0_AIN3", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_AIN3;
                }
                else if (strcmp("AIN1_AIN3", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN1_AIN3;
                }
                else if (strcmp("AIN2_AIN3", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN2_AIN3;
                }
                else if (strcmp("AIN0_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_GND;
                }
                else if (strcmp("AIN1_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN1_GND;
                }
                else if (strcmp("AIN2_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN2_GND;
                }
                else if (strcmp("AIN3_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN3_GND;
                }
                else
                {
                    return 5;
                }
                
                /* check mode */
                if (strcmp("-m", argv[8]) != 0)
                {
                    return 5;
                }
                if (strcmp("WINDOW", argv[9]) != 0)
                {
                    compare = ADS1115_COMPARE_WINDOW;
                }
                else if (strcmp("THRESHOLD", argv[9]) != 0)
                {
                    compare = ADS1115_COMPARE_THRESHOLD;
                }
                else
                {
                    return 5;
                }
                
                /* check threshold */
                if (strcmp("-th", argv[10]) != 0)
                {
                    return 5;
                }
                times = atoi(argv[3]);
                res = gpio_interrupt_init();
                if (res)
                {
                    return 1;
                }
                res = ads1115_compare_test(addr, channel, compare, atof(argv[12]), atof(argv[11]), times);
                if (res)
                {
                    gpio_interrupt_deinit();
                    
                    return 1;
                }
                gpio_interrupt_deinit();
                
                return 0;
            }
            
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
             /* read function */
            if (strcmp("int", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t i;
                volatile uint32_t times;
                volatile float s;
                ads1115_compare_t compare;
                ads1115_address_t addr;
                ads1115_channel_t channel;
                
                /* check iic address */
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("GND", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_GND;
                }
                else if (strcmp("VCC", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_VCC;
                }
                else if (strcmp("SDA", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_SDA;
                }
                else if (strcmp("SCL", argv[5]) == 0)
                {
                    addr = ADS1115_ADDR_SCL;
                }
                else
                {
                    return 5;
                }
                
                /* check channel */
                if (strcmp("-ch", argv[6]) != 0)
                {
                    return 5;
                }
                if (strcmp("AIN0_AIN1", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_AIN1;
                }
                else if (strcmp("AIN0_AIN3", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_AIN3;
                }
                else if (strcmp("AIN1_AIN3", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN1_AIN3;
                }
                else if (strcmp("AIN2_AIN3", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN2_AIN3;
                }
                else if (strcmp("AIN0_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_GND;
                }
                else if (strcmp("AIN1_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN1_GND;
                }
                else if (strcmp("AIN2_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN2_GND;
                }
                else if (strcmp("AIN3_GND", argv[7]) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN3_GND;
                }
                else
                {
                    return 5;
                }
                
                /* check mode */
                if (strcmp("-m", argv[8]) != 0)
                {
                    return 5;
                }
                if (strcmp("WINDOW", argv[9]) != 0)
                {
                    compare = ADS1115_COMPARE_WINDOW;
                }
                else if (strcmp("THRESHOLD", argv[9]) != 0)
                {
                    compare = ADS1115_COMPARE_THRESHOLD;
                }
                else
                {
                    return 5;
                }
                
                /* check threshold */
                if (strcmp("-th", argv[10]) != 0)
                {
                    return 5;
                }
                times = atoi(argv[3]);
                res = ads1115_interrupt_init(addr, channel, compare, atof(argv[12]), atof(argv[11]), times);
                if (res)
                {
                    return 1;
                }
                res = gpio_interrupt_init();
                if (res)
                {
                    ads1115_interrupt_deinit();
                    
                    return 1;
                }
                g_flag = 0;
                for (i=0; i<times; i++)
                {
                    /* read data */
                    ads1115_interface_delay_ms(1000);
                    res = ads1115_interrupt_read((float *)&s);
                    if (res)
                    {
                        ads1115_interrupt_deinit();
                        gpio_interrupt_deinit();
                        
                        return 1;
                    }
                    ads1115_interface_debug_print("ads1115: %d/%d.\n", (uint32_t)(i+1), (uint32_t)times);
                    ads1115_interface_debug_print("ads1115: read is %0.4fV.\n", s);
                    
                    /* check interrupt */
                    if (g_flag)
                    {
                        ads1115_interface_debug_print("ads1115: find interrupt.\n");
                        
                        break;
                    }
                    
                }
                ads1115_interrupt_deinit();
                gpio_interrupt_deinit();
                
                return 0;
            }
            
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = ads1115(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        ads1115_interface_debug_print("ads1115: run failed.\n");
    }
    else if (res == 5)
    {
        ads1115_interface_debug_print("ads1115: param is invalid.\n");
    }
    else
    {
        ads1115_interface_debug_print("ads1115: unknow status code.\n");
    }

    return 0;
}