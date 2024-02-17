[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ADS1115

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ads1115/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

ADS1115は、Texas Instrumentsが発売した超小型パッケージ、低電力、IICバスインターフェイス、16ビット変換精度、内部電圧リファレンス、およびプログラム可能な電圧コンパレータADCチップです。 このチップは、ポータブル計装、バッテリーの電圧と電流の監視、温度測定システム、家庭用電化製品、工場の自動化、プロセス制御などで使用されます。

LibDriver ADS1115は、LibDriverによって起動されたADS1115の全機能ドライバーです。LibDriverADS1115は、連続モードA / D変換、シングルモードA / D変換、マルチチャネルサンプリングスイッチング、プログラム可能な電圧コンパレーターおよびその他の機能を提供します。 LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver ADS1115のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver ADS1115用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver ADS1115ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver ADS1115プログラミング例が含まれています。

/ docディレクトリには、LibDriver ADS1115オフラインドキュメントが含まれています。

/ datasheetディレクトリには、ADS1115データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

```c
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

```c
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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/ads1115/index.html](https://www.libdriver.com/docs/ads1115/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。