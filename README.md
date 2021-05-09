<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver ADS1115

[English](/README.md) | [ 简体中文](/README_CN.md)

### Table of Contents

  - [Description](#Description)
  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)


### Description

ADS1115 is an ultra small package, low power, IIC bus interface, 16 bit conversion accuracy, internal voltage reference and programmable voltage comparator ADC chip launched by Texas Instruments. The chip is used in portable Instrumentation, battery voltage and current monitoring, temperature measurement system, consumer electronics, factory automation and process control and so on.

LibDriver ADS1115 is the full function driver of ADS1115 launched by LibDriver.LibDriver ADS1115 provides continuous mode A / D conversion, single mode A / D conversion, multi-channel sampling switching, programmable voltage comparator and other functions.

### Instruction

/src includes LibDriver ADS1115 source files.

/interface includes LibDriver ADS1115 IIC platform independent template。

/test includes LibDriver ADS1115 driver test code and this code can test the chip necessary function simply。

/example includes LibDriver ADS1115 sample code.

/doc includes LibDriver ADS1115 offline document.

/datasheet includes ADS1115 datasheet。

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add /src, /interface and /example to your project.

### Usage

#### example basic

```C
uint8_t res;
uint8_t i;
float s;

res = ads1115_basic_init(ADS1115_ADDR_GND, ADS1115_CHANNEL_AIN0_AIN1);
if (res)
{
    ads1115_interface_debug_print("ads1115: basic init failed.\n");         

    return 1;

}

...

for (i = 0; i < 3; i++)
{
    res = ads1115_basic_read((float *)&s);
    if (res)
    {
        ads1115_interface_debug_print("ads1115: basic read failed.\n");
        ads1115_basic_deinit();

        return 1;
    }
    ads1115_interface_debug_print("ads1115: adc is %0.4fV.\n", s);
    ads1115_interface_delay_ms(1000);
    
    ...

}

...
    
ads1115_basic_deinit();

return 0;
```

#### example shot

```C
uint8_t res;
uint8_t i;
float s;

res = ads1115_shot_init(ADS1115_ADDR_GND, ADS1115_CHANNEL_AIN0_AIN1);
if (res)
{
    ads1115_interface_debug_print("ads1115: shot init failed.\n");         

    return 1;

}

...
    
for (i = 0; i < 3; i++)
{
    res = ads1115_shot_read((float *)&s);
    if (res)
    {
        ads1115_interface_debug_print("ads1115: shot read failed.\n");
        ads1115_shot_deinit();

        return 1;
    }
    ads1115_interface_debug_print("ads1115: adc is %0.4fV.\n", s);
    ads1115_interface_delay_ms(1000);
    
    ...

}

...
    
ads1115_shot_deinit();

return 0;
```

#### example interrupt

```C
uint8_t res;
uint8_t i;
float s;

uint8_t gpio_interrupt_callback(void)
{
    ...
}

res = ads1115_interrup_init(ADS1115_ADDR_GND, ADS1115_CHANNEL_AIN0_AIN1,
                            ADS1115_COMPARE_THRESHOLD, 1.1f, 1.8f);
if (res)
{
    ads1115_interface_debug_print("ads1115: interrupt init failed.\n");         

    return 1;

}
res = gpio_interrupt_init();
if (res)
{
    ads1115_interrupt_deinit();
                    

    return 1;

}

...
    
for (i = 0; i < 3; i++)
{
    res = ads1115_interrupt_read((float *)&s);
    if (res)
    {
        ads1115_interface_debug_print("ads1115: interrupt read failed.\n");
        ads1115_interrupt_deinit();

        return 1;
    }
    ads1115_interface_debug_print("ads1115: adc is %0.4fV.\n", s);
    ads1115_interface_delay_ms(1000);
    
    ...

}

...

ads1115_interrupt_deinit();

return 0;
```

### Document

Online documents: https://www.libdriver.com/docs/ads1115/index.html

Offline documents: /doc/html/index.html

### Contributing

Please sent an e-mail to lishifenging@outlook.com

### License

Copyright (C) LibDriver 2015-2021 All rights reserved 



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please sent an e-mail to lishifenging@outlook.com