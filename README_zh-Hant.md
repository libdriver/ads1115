[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ADS1115

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ads1115/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

ADS1115是德州儀器公司推出的一款超小封裝、低功耗、擁有IIC總線接口、16位轉換精度，擁有內部電壓參考和可編程電壓比較器的模數轉換芯片。該芯片被應用於便攜式採集設備、電池電壓電流監控、溫度測量系統、消費類電子產品以及工廠自動化與過程控制。

LibDriver ADS1115是LibDriver推出的ADS1115的全功能驅動，該驅動提供連續模式模數轉換、單次模式模數轉換，多通道採樣切換，可編程電壓比較器等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver ADS1115的源文件。

/interface目錄包含了LibDriver ADS1115與平台無關的IIC總線模板。

/test目錄包含了LibDriver ADS1115驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver ADS1115編程範例。

/doc目錄包含了LibDriver ADS1115離線文檔。

/datasheet目錄包含了ADS1115數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

#### example basic

```C
#include "driver_ads1115_basic.h"

uint8_t res;
uint8_t i;
float s;

res = ads1115_basic_init(ADS1115_ADDR_GND, ADS1115_CHANNEL_AIN0_AIN1);
if (res != 0)
{
    ads1115_interface_debug_print("ads1115: basic init failed.\n");         

    return 1;

}

...

for (i = 0; i < 3; i++)
{
    res = ads1115_basic_read((float *)&s);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: basic read failed.\n");
        (void)ads1115_basic_deinit();

        return 1;
    }
    ads1115_interface_debug_print("ads1115: adc is %0.4fV.\n", s);
    ads1115_interface_delay_ms(1000);
    
    ...

}

...
    
(void)ads1115_basic_deinit();

return 0;
```

#### example shot

```C
#include "driver_ads1115_shot.h"

uint8_t res;
uint8_t i;
float s;

res = ads1115_shot_init(ADS1115_ADDR_GND, ADS1115_CHANNEL_AIN0_AIN1);
if (res != 0)
{
    ads1115_interface_debug_print("ads1115: shot init failed.\n");         

    return 1;

}

...
    
for (i = 0; i < 3; i++)
{
    res = ads1115_shot_read((float *)&s);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: shot read failed.\n");
        (void)ads1115_shot_deinit();

        return 1;
    }
    ads1115_interface_debug_print("ads1115: adc is %0.4fV.\n", s);
    ads1115_interface_delay_ms(1000);
    
    ...

}

...
    
(void)ads1115_shot_deinit();

return 0;
```

#### example interrupt

```C
#include "driver_ads1115_interrupt.h"

uint8_t res;
uint8_t i;
float s;

uint8_t gpio_interrupt_callback(void)
{
    ...
}

res = ads1115_interrup_init(ADS1115_ADDR_GND, ADS1115_CHANNEL_AIN0_AIN1,
                            ADS1115_COMPARE_THRESHOLD, 1.1f, 1.8f);
if (res != 0)
{
    ads1115_interface_debug_print("ads1115: interrupt init failed.\n");         

    return 1;

}
res = gpio_interrupt_init();
if (res != 0)
{
    (void)ads1115_interrupt_deinit();
                    

    return 1;

}

...
    
for (i = 0; i < 3; i++)
{
    res = ads1115_interrupt_read((float *)&s);
    if (res != 0)
    {
        ads1115_interface_debug_print("ads1115: interrupt read failed.\n");
        (void)ads1115_interrupt_deinit();

        return 1;
    }
    ads1115_interface_debug_print("ads1115: adc is %0.4fV.\n", s);
    ads1115_interface_delay_ms(1000);
    
    ...

}

...

(void)ads1115_interrupt_deinit();

return 0;
```

### 文檔

在線文檔: [https://www.libdriver.com/docs/ads1115/index.html](https://www.libdriver.com/docs/ads1115/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。