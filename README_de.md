[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ADS1115

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ads1115/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

ADS1115 ist ein ADC-Chip mit ultrakleinem Gehäuse, geringem Stromverbrauch, IIC-Bus-Schnittstelle, 16-Bit-Umwandlungsgenauigkeit, interner Spannungsreferenz und programmierbarem Spannungskomparator-ADC-Chip, der von Texas Instruments auf den Markt gebracht wurde. Der Chip wird in tragbaren Instrumenten, Batteriespannungs- und Stromüberwachung, Temperaturmesssystemen, Unterhaltungselektronik, Fabrikautomation und Prozesssteuerung und so weiter verwendet.

LibDriver ADS1115 ist der Treiber mit vollem Funktionsumfang von ADS1115, der von LibDriver gestartet wurde. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver ADS1115-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver ADS1115 IIC.

/test enthält den Testcode des LibDriver ADS1115-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver ADS1115-Beispielcode.

/doc enthält das LibDriver ADS1115-Offlinedokument.

/Datenblatt enthält ADS1115-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/ads1115/index.html](https://www.libdriver.com/docs/ads1115/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.