### 1. Chip

#### 1.1 Chip Info

chip name : Raspberry Pi 4B.

iic pin: SCL/SDA GPIO3/GPIO2.

gpio pin: INT GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(ads1115 REQUIRED)
```

### 3. ADS1115

#### 3.1 Command Instruction

​          ads1115 is a basic command which can test all ads1115 driver function:

​           -i         show ads1115 chip and driver information.

​           -h        show ads1115 help.

​           -p        show ads1115 pin connections of the current board.

​           -t  (reg -a (VCC | GND | SCL | SDA) | read <times> -a (VCC | GND | SCL | SDA) |muti <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND) | int <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND) -th <low_threshold> <high_threshold>)

​           -t reg -a (VCC | GND | SCL | SDA)        run ads1115 register test. 

​           -t read <times> -a (VCC | GND | SCL | SDA)        run ads1115 read test. times means test times.

​           -t muti <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND)        run ads1115 mutichannel test.times means test times.

​            -t int <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND) -th <low_threshold> <high_threshold>        run ads1115 interrupt test.times means test times.low_threshold and high_threshold means interrupt threshold.

​            -c (read <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND)  | shot <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND)  | int  <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND)  -m (THRESHOLD | WINDOW) -th <low_threshold> <high_threshold>)

​            -c read <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND)        run ads1115 read function.times means read times.

​            -c shot  <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND)        run ads1115 shot function.times means read times.

​            -c  int  <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND) -m (THRESHOLD | WINDOW) -th <low_threshold> <high_threshold>       run ads1115 interrupt function. times means read times.low_threshold and high_threshold means interrupt threshold.

#### 3.2 Command Example

```shell
./ads1115 -i

ads1115: chip is Texas Instruments ADS1115.
ads1115: manufacturer is Texas Instruments.
ads1115: interface is IIC.
ads1115: driver version is 2.0.
ads1115: min supply voltage is 2.0V.
ads1115: max supply voltage is 5.5V.
ads1115: max current is 0.20mA.
ads1115: max temperature is 125.0C.
ads1115: min temperature is -40.0C.
```

```shell
./ads1115 -p

ads1115: SCL connected to GPIO3(BCM).
ads1115: SDA connected to GPIO2(BCM).
ads1115: INT connected to GPIO17(BCM).
```

```shell
./ads1115 -t reg -a GND

ads1115: chip is Texas Instruments ADS1115.
ads1115: manufacturer is Texas Instruments.
ads1115: interface is IIC.
ads1115: driver version is 2.0.
ads1115: min supply voltage is 2.0V.
ads1115: max supply voltage is 5.5V.
ads1115: max current is 0.20mA.
ads1115: max temperature is 125.0C.
ads1115: min temperature is -40.0C.
ads1115: start register test.
ads1115: ads1115_set_addr_pin/ads1115_get_addr_pin test.
ads1115: set addr pin ground.
ads1115: check addr pin ok.
ads1115: set addr pin vcc.
ads1115: check addr pin ok.
ads1115: set addr pin sda.
ads1115: check addr pin ok.
ads1115: set addr pin scl.
ads1115: check addr pin ok.
ads1115: ads1115_set_channel/ads1115_get_channel test.
ads1115: set channel ain0_ground.
ads1115: check channel ok.
ads1115: set channel ain1_ground.
ads1115: check channel ok.
ads1115: set channel ain2_ground.
ads1115: check channel ok.
ads1115: set channel ain3_ground.
ads1115: check channel ok.
ads1115: set channel ain0_ain1.
ads1115: check channel ok.
ads1115: set channel ain0_ain3.
ads1115: check channel ok.
ads1115: set channel ain1_ain3.
ads1115: check channel ok.
ads1115: set channel ain2_ain3.
ads1115: check channel ok.
ads1115: ads1115_set_range/ads1115_get_range test.
ads1115: set range 6.144V.
ads1115: check range ok.
ads1115: set range 4.096V.
ads1115: check range ok.
ads1115: set range 2.048V.
ads1115: check range ok.
ads1115: set range 1.024V.
ads1115: check range ok.
ads1115: set range 0.512V.
ads1115: check range ok.
ads1115: set range 0.256V.
ads1115: check range ok.
ads1115: ads1115_set_alert_pin/ads1115_get_alert_pin test.
ads1115: set alert pin low.
ads1115: check alert pin ok.
ads1115: set alert pin high.
ads1115: check alert pin ok.
ads1115: ads1115_set_compare_mode/ads1115_get_compare_mode test.
ads1115: set compare threshold.
ads1115: check compare ok.
ads1115: set compare window.
ads1115: check compare ok.
ads1115: ads1115_set_rate/ads1115_get_rate test.
ads1115: set rate 8 sps.
ads1115: check rate ok.
ads1115: set rate 16 sps.
ads1115: check rate ok.
ads1115: set rate 32 sps.
ads1115: check rate ok.
ads1115: set rate 64 sps.
ads1115: check rate ok.
ads1115: set rate 128 sps.
ads1115: check rate ok.
ads1115: set rate 250 sps.
ads1115: check rate ok.
ads1115: set rate 475 sps.
ads1115: check rate ok.
ads1115: set rate 860 sps.
ads1115: check rate ok.
ads1115: ads1115_set_comparator_queue/ads1115_get_comparator_queue test.
ads1115: set comparator queue none.
ads1115: check comparator queue ok.
ads1115: set comparator queue 1 conv.
ads1115: check comparator queue ok.
ads1115: set comparator queue 2 conv.
ads1115: check comparator queue ok.
ads1115: set comparator queue 4 conv.
ads1115: check comparator queue ok.
ads1115: ads1115_set_compare_threshold/ads1115_get_compare_threshold test.
ads1115: set high threshold 6424 low threshold -5007.
ads1115: check high threshold ok.
ads1115: check low threshold ok.
ads1115: ads1115_set_compare/ads1115_get_compare test.
ads1115: enable compare.
ads1115: check compare ok.
ads1115: disable compare.
ads1115: check compare ok.
ads1115: ads1115_convert_to_register test.
ads1115: convert to register -0.84V.
ads1115: check convert to register ok.
ads1115: convert to register 2.15V.
ads1115: check convert to register ok.
ads1115: convert to register -1.29V.
ads1115: check convert to register ok.
ads1115: convert to register 0.84V.
ads1115: check convert to register ok.
ads1115: convert to register -0.46V.
ads1115: check convert to register ok.
ads1115: convert to register 0.13V.
ads1115: check convert to register 16256.
ads1115: convert to data 0.13V.
ads1115: finish register test.
```

```shell
./ads1115 -t read 3 -a GND

ads1115: chip is Texas Instruments ADS1115.
ads1115: manufacturer is Texas Instruments.
ads1115: interface is IIC.
ads1115: driver version is 2.0.
ads1115: min supply voltage is 2.0V.
ads1115: max supply voltage is 5.5V.
ads1115: max current is 0.20mA.
ads1115: max temperature is 125.0C.
ads1115: min temperature is -40.0C.
ads1115: start read test.
ads1115: AIN0 to GND.
ads1115: continuous read test.
ads1115: 1 continus mode 0.608V.
ads1115: 2 continus mode 0.607V.
ads1115: 3 continus mode 0.608V.
ads1115: single read test.
ads1115: 1 single mode 0.607V.
ads1115: 2 single mode 0.607V.
ads1115: 3 single mode 0.604V.
ads1115: finish read test.
```

```shell
./ads1115 -t muti 3 -a GND -ch AIN0_GND

ads1115: chip is Texas Instruments ADS1115.
ads1115: manufacturer is Texas Instruments.
ads1115: interface is IIC.
ads1115: driver version is 2.0.
ads1115: min supply voltage is 2.0V.
ads1115: max supply voltage is 5.5V.
ads1115: max current is 0.20mA.
ads1115: max temperature is 125.0C.
ads1115: min temperature is -40.0C.
ads1115: start multichannel test.
ads1115: 1 3.291V.
ads1115: 2 3.291V.
ads1115: 3 3.291V.
ads1115: finish multichannel test.
```

```shell
./ads1115 -t int 3 -a GND -ch AIN0_GND -m THRESHOLD -th 1.1 2.5

ads1115: chip is Texas Instruments ADS1115.
ads1115: manufacturer is Texas Instruments.
ads1115: interface is IIC.
ads1115: driver version is 2.0.
ads1115: min supply voltage is 2.0V.
ads1115: max supply voltage is 5.5V.
ads1115: max current is 0.20mA.
ads1115: max temperature is 125.0C.
ads1115: min temperature is -40.0C.
ads1115: start compare mode test.
ads1115: run 1 times.
ads1115: voltage is over high threshold, please see alert pin.
ads1115: run 2 times.
ads1115: voltage is over high threshold, please see alert pin.
ads1115: run 3 times.
ads1115: voltage is over high threshold, please see alert pin.
ads1115: finish compare mode test.
```

```shell
./ads1115 -c read 3 -a GND -ch AIN0_GND

ads1115: 1/3.
ads1115: adc is 3.2906V.
ads1115: 2/3.
ads1115: adc is 3.2906V.
ads1115: 3/3.
ads1115: adc is 3.2908V.
```

```shell
./ads1115 -c shot 3 -a GND -ch AIN0_GND

ads1115: 1/3.
ads1115: adc is 3.2908V.
ads1115: 2/3.
ads1115: adc is 3.2908V.
ads1115: 3/3.
ads1115: adc is 3.2908V.
```

```shell
./ads1115 -c int 3 -a GND -ch AIN0_GND -m THRESHOLD -th 1.1 2.5

ads1115: 1/3.
ads1115: read is 3.2903V.
ads1115: find interrupt
```

```shell
./ads1115 -h

ads1115 -i
	show ads1115 chip and driver information.
ads1115 -h
	show ads1115 help.
ads1115 -p
	show ads1115 pin connections of the current board.
ads1115 -t reg -a (VCC | GND | SCL | SDA)
	run ads1115 register test.times means test times.
ads1115 -t read <times> -a (VCC | GND | SCL | SDA)
	run ads1115 read test.times means test times.
ads1115 -t muti <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND)
	run ads1115 mutichannel test.times means test times.
ads1115 -t int <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND) -th <low_threshold> <high_threshold>
	run ads1115 interrupt test.times means test times.low_threshold and high_threshold means interrupt threshold.
ads1115 -c read <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND)
	run ads1115 read function.times means read times.
ads1115 -c shot <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND)
	run ads1115 shot function.times means read times.
ads1115 -c int <times> -a (VCC | GND | SCL | SDA) -ch (AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND) -m (THRESHOLD | WINDOW) -th <low_threshold> <high_threshold>
	run ads1115 interrupt function.times means read times.low_threshold and high_threshold means interrupt threshold.
```
