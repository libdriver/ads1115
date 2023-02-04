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
#include "gpio.h"
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
volatile uint8_t g_flag;            /**< interrupt flag */

/**
 * @brief     ads1115 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t ads1115(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"channel", required_argument, NULL, 2},
        {"high-threshold", required_argument, NULL, 3},
        {"low-threshold", required_argument, NULL, 4},
        {"mode", required_argument, NULL, 5},
        {"times", required_argument, NULL, 6},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    ads1115_address_t addr = ADS1115_ADDR_GND;
    ads1115_channel_t channel = ADS1115_CHANNEL_AIN0_GND;
    ads1115_compare_t compare = ADS1115_COMPARE_THRESHOLD;
    float high_threshold = 0.0f;
    float low_threshold = 0.0f;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* addr */
            case 1 :
            {
                /* set the addr pin */
                if (strcmp("GND", optarg) == 0)
                {
                    addr = ADS1115_ADDR_GND;
                }
                else if (strcmp("VCC", optarg) == 0)
                {
                    addr = ADS1115_ADDR_VCC;
                }
                else if (strcmp("SDA", optarg) == 0)
                {
                    addr = ADS1115_ADDR_SDA;
                }
                else if (strcmp("SCL", optarg) == 0)
                {
                    addr = ADS1115_ADDR_SCL;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* channel */
            case 2 :
            {
                /* set the channel */
                if (strcmp("AIN0_AIN1", optarg) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_AIN1;
                }
                else if (strcmp("AIN0_AIN3", optarg) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_AIN3;
                }
                else if (strcmp("AIN1_AIN3", optarg) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN1_AIN3;
                }
                else if (strcmp("AIN2_AIN3", optarg) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN2_AIN3;
                }
                else if (strcmp("AIN0_GND", optarg) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN0_GND;
                }
                else if (strcmp("AIN1_GND", optarg) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN1_GND;
                }
                else if (strcmp("AIN2_GND", optarg) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN2_GND;
                }
                else if (strcmp("AIN3_GND", optarg) == 0)
                {
                    channel = ADS1115_CHANNEL_AIN3_GND;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* high threshold */
            case 3 :
            {
                high_threshold = atof(optarg);
                
                break;
            }
             
            /* low threshold */
            case 4 :
            {
                low_threshold = atof(optarg);
                
                break;
            }
            
            /* mode */
            case 5 :
            {
                /* set the mode */
                if (strcmp("WINDOW", optarg) == 0)
                {
                    compare = ADS1115_COMPARE_WINDOW;
                }
                else if (strcmp("THRESHOLD", optarg) == 0)
                {
                    compare = ADS1115_COMPARE_THRESHOLD;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* running times */
            case 6 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run the reg test */
        if (ads1115_register_test(addr) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_read", type) == 0)
    {
        /* run the read test */
        if (ads1115_read_test(addr, times) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_muti", type) == 0)
    {
        /* run the multichannel test */
        if (ads1115_multichannel_test(addr, channel, times) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_int", type) == 0)
    {
        uint8_t res;
        
        /* gpio init */
        res = gpio_interrupt_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* run the compare interrupt test */
        res = ads1115_compare_test(addr, channel, compare, high_threshold, low_threshold, times);
        if (res != 0)
        {
            (void)gpio_interrupt_deinit();
            
            return 1;
        }
        (void)gpio_interrupt_deinit();
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float s;
        
        /* basic init */
        res = ads1115_basic_init(addr, channel);
        if (res != 0)
        {
            ads1115_interface_debug_print("ads1115: basic init failed.\n");
            
            return 1;
        }
        for (i = 0; i < times; i++)
        {
            /* read the data */
            res = ads1115_basic_read((float *)&s);
            if (res != 0)
            {
                ads1115_interface_debug_print("ads1115: basic read failed.\n");
                (void)ads1115_basic_deinit();
                
                return 1;
            }
            ads1115_interface_debug_print("ads1115: %d/%d.\n", i + 1, times);
            ads1115_interface_debug_print("ads1115: adc is %0.4fV.\n", s);
            ads1115_interface_delay_ms(1000);
        }
        (void)ads1115_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_shot", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float s;
        
        /* shot init */
        res = ads1115_shot_init(addr, channel);
        if (res != 0)
        {
            ads1115_interface_debug_print("ads1115: basic init failed.\n");
            
            return 1;
        }
        for (i = 0; i < times; i++)
        {
            /* read the data */
            res = ads1115_shot_read((float *)&s);
            if (res != 0)
            {
                ads1115_interface_debug_print("ads1115: basic read failed.\n");
                (void)ads1115_shot_deinit();
                
                return 1;
            }
            ads1115_interface_debug_print("ads1115: %d/%d.\n", i + 1, times);
            ads1115_interface_debug_print("ads1115: adc is %0.4fV.\n", s);
            ads1115_interface_delay_ms(1000);
        }
        (void)ads1115_shot_deinit();
        
        return 0;
    }
    else if (strcmp("e_int", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float s;
        
        /* interrupt init */
        res = ads1115_interrupt_init(addr, channel, compare, high_threshold, low_threshold);
        if (res != 0)
        {
            return 1;
        }
        
        /* gpio init */
        res = gpio_interrupt_init();
        if (res != 0)
        {
            (void)ads1115_interrupt_deinit();
            
            return 1;
        }
        
        g_flag = 0;
        for (i = 0; i < times; i++)
        {
            /* read data */
            ads1115_interface_delay_ms(1000);
            res = ads1115_interrupt_read((float *)&s);
            if (res != 0)
            {
                (void)ads1115_interrupt_deinit();
                (void)gpio_interrupt_deinit();
                
                return 1;
            }
            ads1115_interface_debug_print("ads1115: %d/%d.\n", i + 1, times);
            ads1115_interface_debug_print("ads1115: read is %0.4fV.\n", s);
            
            /* check interrupt */
            if (g_flag != 0)
            {
                ads1115_interface_debug_print("ads1115: find interrupt.\n");
                
                break;
            }
            
        }
        (void)ads1115_interrupt_deinit();
        (void)gpio_interrupt_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        ads1115_interface_debug_print("Usage:\n");
        ads1115_interface_debug_print("  ads1115 (-i | --information)\n");
        ads1115_interface_debug_print("  ads1115 (-h | --help)\n");
        ads1115_interface_debug_print("  ads1115 (-p | --port)\n");
        ads1115_interface_debug_print("  ads1115 (-t reg | --test=reg) [--addr=<VCC | GND | SCL | SDA>]\n");
        ads1115_interface_debug_print("  ads1115 (-t read | --test=read) [--times=<num>] [--addr=<VCC | GND | SCL | SDA>]\n");
        ads1115_interface_debug_print("  ads1115 (-t muti | --test=muti) [--times=<num>] [--addr=<VCC | GND | SCL | SDA>] \n");
        ads1115_interface_debug_print("          [--channel=<AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND>]\n");
        ads1115_interface_debug_print("  ads1115 (-t int | --test=int) [--times=<num>] [--addr=<VCC | GND | SCL | SDA>] \n");
        ads1115_interface_debug_print("          [--channel=<AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND>] \n");
        ads1115_interface_debug_print("          [--low-threshold=<low>] [--high-threshold=<high>]\n");
        ads1115_interface_debug_print("  ads1115 (-e read | --example=read) [--times=<num>] [--addr=<VCC | GND | SCL | SDA>] \n");
        ads1115_interface_debug_print("          [--channel=<AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND>]\n");
        ads1115_interface_debug_print("  ads1115 (-e shot | --example=shot) [--times=<num>] [--addr=<VCC | GND | SCL | SDA>] \n");
        ads1115_interface_debug_print("          [--channel=<AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND>]\n");
        ads1115_interface_debug_print("  ads1115 (-e int | --example=int) [--times=<num>] [--addr=<VCC | GND | SCL | SDA>] \n");
        ads1115_interface_debug_print("          [--channel=<AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND>] \n");
        ads1115_interface_debug_print("          [--mode=<THRESHOLD | WINDOW>] [--low-threshold=<low>] [--high-threshold=<high>]\n");
        ads1115_interface_debug_print("\n");
        ads1115_interface_debug_print("Options:\n");
        ads1115_interface_debug_print("      --addr==<VCC | GND | SCL | SDA>    Set the connection of the addr pin.([default: GND])\n");
        ads1115_interface_debug_print("      --channel=<AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND>\n");
        ads1115_interface_debug_print("                                         Set the ADC channel.([default: AIN0_GND])\n");
        ads1115_interface_debug_print("  -e <read | shot | int>, --example=<read | shot | int>\n");
        ads1115_interface_debug_print("                                         Run the driver example.\n");
        ads1115_interface_debug_print("  -h, --help                             Show the help.\n");
        ads1115_interface_debug_print("      --high-threshold=<high>            Set the ADC interrupt high threshold.([default: 0.0f])\n");
        ads1115_interface_debug_print("  -i, --information                      Show the chip information.\n");
        ads1115_interface_debug_print("      --low-threshold=<low>              Set the ADC interrupt low threshold.([default: 0.0f])\n");
        ads1115_interface_debug_print("      --mode=<THRESHOLD | WINDOW>        Set the ADC interrupt mode.([default: THRESHOLD])\n");
        ads1115_interface_debug_print("  -p, --port                             Display the pin connections of the current board.\n");
        ads1115_interface_debug_print("  -t <reg | read | muti | int>, --test=<reg | read | muti | int>.\n");
        ads1115_interface_debug_print("                                         Run the driver test.\n");
        ads1115_interface_debug_print("      --times=<num>                      Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        ads1115_info_t info;
        
        /* print ads1115 info */
        ads1115_info(&info);
        ads1115_interface_debug_print("ads1115: chip is %s.\n", info.chip_name);
        ads1115_interface_debug_print("ads1115: manufacturer is %s.\n", info.manufacturer_name);
        ads1115_interface_debug_print("ads1115: interface is %s.\n", info.interface);
        ads1115_interface_debug_print("ads1115: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ads1115_interface_debug_print("ads1115: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ads1115_interface_debug_print("ads1115: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ads1115_interface_debug_print("ads1115: max current is %0.2fmA.\n", info.max_current_ma);
        ads1115_interface_debug_print("ads1115: max temperature is %0.1fC.\n", info.temperature_max);
        ads1115_interface_debug_print("ads1115: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print the pin connection */
        ads1115_interface_debug_print("ads1115: SCL connected to GPIO3(BCM).\n");
        ads1115_interface_debug_print("ads1115: SDA connected to GPIO2(BCM).\n");
        ads1115_interface_debug_print("ads1115: INT connected to GPIO17(BCM).\n");
        
        return 0;
    }
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
        ads1115_interface_debug_print("ads1115: unknown status code.\n");
    }

    return 0;
}