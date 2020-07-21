EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATmega:ATmega328P-PU U1
U 1 1 5F0F2B2C
P 1500 2900
F 0 "U1" H 856 2946 50  0000 R CNN
F 1 "ATmega328P-PU" H 856 2855 50  0000 R CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 1500 2900 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 1500 2900 50  0001 C CNN
	1    1500 2900
	1    0    0    -1  
$EndComp
$Comp
L CRYSTAL:CRYSTAL X1
U 1 1 5F0F7EA6
P 2500 2350
F 0 "X1" V 2530 2272 30  0000 R CNN
F 1 "16MHz" V 2470 2272 30  0000 R CNN
F 2 "Crystal:Crystal_HC18-U_Vertical" H 2500 2350 60  0000 C CNN
F 3 "" H 2500 2350 60  0000 C CNN
	1    2500 2350
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5F0FA514
P 2850 2200
F 0 "C1" V 2621 2200 50  0000 C CNN
F 1 "22pf" V 2712 2200 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 2850 2200 50  0001 C CNN
F 3 "~" H 2850 2200 50  0001 C CNN
	1    2850 2200
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5F0FB0BE
P 2850 2500
F 0 "C2" V 2621 2500 50  0000 C CNN
F 1 "22pf" V 2712 2500 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 2850 2500 50  0001 C CNN
F 3 "~" H 2850 2500 50  0001 C CNN
	1    2850 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	2500 2200 2750 2200
Wire Wire Line
	2500 2500 2750 2500
Wire Wire Line
	2500 2500 2100 2500
Wire Wire Line
	2100 2500 2100 2400
Connection ~ 2500 2500
Wire Wire Line
	2950 2200 2950 2500
Wire Wire Line
	2950 2500 2950 4400
Wire Wire Line
	2950 4400 1500 4400
Connection ~ 2950 2500
Wire Wire Line
	1600 1400 1500 1400
$Comp
L +5V:+5V #PWR0101
U 1 1 5F0FD6CA
P 1500 900
F 0 "#PWR0101" H 1500 990 20  0001 C CNN
F 1 "+5V" H 1496 1028 30  0000 C CNN
F 2 "" H 1500 900 60  0000 C CNN
F 3 "" H 1500 900 60  0000 C CNN
	1    1500 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 900  1500 1100
Connection ~ 1500 1400
Wire Wire Line
	1500 4400 1500 4800
Connection ~ 1500 4400
$Comp
L power:GND #PWR0102
U 1 1 5F0FEE6E
P 1500 4800
F 0 "#PWR0102" H 1500 4800 30  0001 C CNN
F 1 "GND" H 1500 4730 30  0001 C CNN
F 2 "" H 1500 4800 60  0000 C CNN
F 3 "" H 1500 4800 60  0000 C CNN
	1    1500 4800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J1
U 1 1 5F16156B
P 2900 800
F 0 "J1" V 2962 944 50  0000 L CNN
F 1 "LEDStrip" V 3053 944 50  0000 L CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_1x04_P1.00mm_Vertical" H 2900 800 50  0001 C CNN
F 3 "~" H 2900 800 50  0001 C CNN
	1    2900 800 
	0    1    1    0   
$EndComp
Wire Wire Line
	2100 3700 3650 3700
Wire Wire Line
	3650 3700 3650 1150
Wire Wire Line
	3650 1150 2700 1150
Wire Wire Line
	2700 1150 2700 1000
Wire Wire Line
	1500 1100 2300 1100
Wire Wire Line
	3000 1100 3000 1000
Connection ~ 1500 1100
Wire Wire Line
	1500 1100 1500 1400
Wire Wire Line
	2900 1250 2900 1000
Wire Wire Line
	3550 1250 2900 1250
Wire Wire Line
	2100 4000 3550 4000
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 5F1699E1
P 4100 800
F 0 "J2" V 4162 944 50  0000 L CNN
F 1 "LEDString" V 4253 944 50  0000 L CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_1x04_P1.00mm_Vertical" H 4100 800 50  0001 C CNN
F 3 "~" H 4100 800 50  0001 C CNN
	1    4100 800 
	0    1    1    0   
$EndComp
Wire Wire Line
	2100 1800 3900 1800
Wire Wire Line
	3900 1800 3900 1000
Wire Wire Line
	2100 1900 4000 1900
Wire Wire Line
	4000 1900 4000 1000
Wire Wire Line
	2100 2000 4100 2000
Wire Wire Line
	4100 2000 4100 1000
$Comp
L Device:R R1
U 1 1 5F16F272
P 2300 1250
F 0 "R1" H 2370 1296 50  0000 L CNN
F 1 "10K" H 2370 1205 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 2230 1250 50  0001 C CNN
F 3 "~" H 2300 1250 50  0001 C CNN
	1    2300 1250
	1    0    0    -1  
$EndComp
Connection ~ 2300 1100
Wire Wire Line
	2300 1100 3000 1100
Wire Wire Line
	2300 3200 2100 3200
Wire Wire Line
	2300 1400 2300 3200
Wire Wire Line
	2100 2300 2250 2300
Wire Wire Line
	2250 2300 2250 2200
Wire Wire Line
	2250 2200 2500 2200
Connection ~ 2500 2200
$Comp
L Switch:SW_MEC_5G SW1
U 1 1 5F175F2E
P 5100 950
F 0 "SW1" H 5100 1235 50  0000 C CNN
F 1 "SW_MEC_5G" H 5100 1144 50  0000 C CNN
F 2 "Button_Switch_THT:SW_MEC_5GTH9" H 5100 1150 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=488" H 5100 1150 50  0001 C CNN
	1    5100 950 
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_MEC_5G SW2
U 1 1 5F177088
P 5100 1250
F 0 "SW2" H 5100 1535 50  0000 C CNN
F 1 "SW_MEC_5G" H 5100 1444 50  0000 C CNN
F 2 "Button_Switch_THT:SW_MEC_5GTH9" H 5100 1450 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=488" H 5100 1450 50  0001 C CNN
	1    5100 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 1100 4650 850 
Wire Wire Line
	4650 850  5300 850 
Wire Wire Line
	2100 2100 4900 2100
Wire Wire Line
	4900 2100 4900 1250
Wire Wire Line
	2100 3600 4800 3600
Wire Wire Line
	4800 3600 4800 950 
Wire Wire Line
	4800 950  4900 950 
Connection ~ 4900 950 
Connection ~ 4900 1250
$Comp
L Device:D D1
U 1 1 5F174E0C
P 4900 1100
F 0 "D1" V 4854 1180 50  0000 L CNN
F 1 "D" V 4945 1180 50  0000 L CNN
F 2 "Diode_THT:D_DO-34_SOD68_P2.54mm_Vertical_AnodeUp" H 4900 1100 50  0001 C CNN
F 3 "~" H 4900 1100 50  0001 C CNN
	1    4900 1100
	0    1    1    0   
$EndComp
$Comp
L Device:R_POT_TRIM RV1
U 1 1 5F17D352
P 5650 950
F 0 "RV1" V 5443 950 50  0000 C CNN
F 1 "R_POT_TRIM_10K" V 5534 950 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 5650 950 50  0001 C CNN
F 3 "~" H 5650 950 50  0001 C CNN
	1    5650 950 
	0    1    1    0   
$EndComp
$Comp
L Device:R_POT_TRIM RV2
U 1 1 5F17E19E
P 6050 950
F 0 "RV2" V 5843 950 50  0000 C CNN
F 1 "R_POT_TRIM_10K" V 5934 950 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 6050 950 50  0001 C CNN
F 3 "~" H 6050 950 50  0001 C CNN
	1    6050 950 
	0    1    1    0   
$EndComp
$Comp
L Device:R_POT_TRIM RV3
U 1 1 5F17EDAC
P 6450 950
F 0 "RV3" V 6243 950 50  0000 C CNN
F 1 "R_POT_TRIM_10K" V 6334 950 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 6450 950 50  0001 C CNN
F 3 "~" H 6450 950 50  0001 C CNN
	1    6450 950 
	0    1    1    0   
$EndComp
$Comp
L Device:R_POT_TRIM RV4
U 1 1 5F17F63A
P 6850 950
F 0 "RV4" V 6643 950 50  0000 C CNN
F 1 "R_POT_TRIM_10K" V 6734 950 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 6850 950 50  0001 C CNN
F 3 "~" H 6850 950 50  0001 C CNN
	1    6850 950 
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5F18311C
P 5500 1500
F 0 "R2" V 5293 1500 50  0000 C CNN
F 1 "4.7K" V 5384 1500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 5430 1500 50  0001 C CNN
F 3 "~" H 5500 1500 50  0001 C CNN
	1    5500 1500
	0    1    1    0   
$EndComp
Wire Wire Line
	5300 1500 5350 1500
Wire Wire Line
	5650 1250 5800 1250
Wire Wire Line
	5800 1250 5800 950 
Wire Wire Line
	5800 1250 6200 1250
Wire Wire Line
	6200 1250 6200 950 
Connection ~ 5800 1250
Wire Wire Line
	6200 1250 6600 1250
Wire Wire Line
	6600 1250 6600 950 
Connection ~ 6200 1250
Wire Wire Line
	6600 1250 7000 1250
Wire Wire Line
	7000 1250 7000 950 
Connection ~ 6600 1250
Wire Wire Line
	6700 950  6700 1500
Wire Wire Line
	6700 1500 6300 1500
Wire Wire Line
	6300 1500 6300 1400
Wire Wire Line
	6300 1500 5900 1500
Wire Wire Line
	5900 1500 5900 1350
Connection ~ 6300 1500
Wire Wire Line
	5500 950  5500 1350
Wire Wire Line
	5500 1350 5900 1350
Connection ~ 5900 1350
Wire Wire Line
	5900 1350 5900 950 
Wire Wire Line
	6300 1500 6300 4400
Wire Wire Line
	6300 4400 2950 4400
Connection ~ 2950 4400
Wire Wire Line
	2100 3100 6850 3100
Wire Wire Line
	6850 3100 6850 1100
Wire Wire Line
	6450 1100 6450 3000
Wire Wire Line
	6450 3000 2100 3000
Wire Wire Line
	2100 2800 6050 2800
Wire Wire Line
	6050 2800 6050 1100
Wire Wire Line
	5650 1500 5650 1250
Wire Wire Line
	5650 1100 5750 1100
Wire Wire Line
	5750 1100 5750 2900
Wire Wire Line
	5750 2900 2100 2900
Wire Wire Line
	3000 1100 4650 1100
Connection ~ 3000 1100
Wire Wire Line
	4200 1000 4200 1700
Wire Wire Line
	4200 1700 2100 1700
Wire Wire Line
	2100 2200 2200 2200
Wire Wire Line
	2200 2200 2200 2150
Wire Wire Line
	2200 2150 7150 2150
$Comp
L semi-trans-generic:TIP120 Q1
U 1 1 5F1A28C9
P 7350 2200
F 0 "Q1" H 7594 2299 50  0000 L CNN
F 1 "TIP120" H 7594 2208 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7594 2109 60  0000 L CNN
F 3 "" H 7750 2250 60  0000 C CNN
F 4 "NPN TIP120" H 7350 1800 60  0001 C CNN "BOM"
	1    7350 2200
	1    0    0    -1  
$EndComp
$Comp
L power:+12 #PWR0103
U 1 1 5F1A4451
P 7500 1050
F 0 "#PWR0103" H 7500 1100 30  0001 C CNN
F 1 "+12" H 7500 1183 50  0000 C CNN
F 2 "" H 7500 1050 60  0000 C CNN
F 3 "" H 7500 1050 60  0000 C CNN
	1    7500 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 1050 7500 2000
Wire Wire Line
	7500 2400 7950 2400
Wire Wire Line
	7950 2400 7950 1600
$Comp
L Regulator_Linear:L7805 U2
U 1 1 5F1A9D71
P 8250 1100
F 0 "U2" H 8250 1342 50  0000 C CNN
F 1 "L7805" H 8250 1251 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 8275 950 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 8250 1050 50  0001 C CNN
	1    8250 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 1400 6300 1400
Connection ~ 6300 1400
Wire Wire Line
	6300 1400 6300 950 
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 5F1AD858
P 8900 700
F 0 "J3" V 8864 512 50  0000 R CNN
F 1 "Fountain" V 8773 512 50  0000 R CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x02_P1.27mm_Vertical" H 8900 700 50  0001 C CNN
F 3 "~" H 8900 700 50  0001 C CNN
	1    8900 700 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8550 1100 8650 1100
Wire Wire Line
	8900 1100 8900 900 
Wire Wire Line
	9000 900  9000 1400
Wire Wire Line
	9000 1400 8650 1400
Connection ~ 8250 1400
$Comp
L Device:C C4
U 1 1 5F1B306D
P 8650 1250
F 0 "C4" H 8765 1296 50  0000 L CNN
F 1 "0.1uf" H 8765 1205 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P2.00mm" H 8688 1100 50  0001 C CNN
F 3 "~" H 8650 1250 50  0001 C CNN
	1    8650 1250
	1    0    0    -1  
$EndComp
Connection ~ 8650 1100
Wire Wire Line
	8650 1100 8900 1100
Connection ~ 8650 1400
Wire Wire Line
	8650 1400 8250 1400
$Comp
L Device:C C3
U 1 1 5F1B334B
P 8100 1600
F 0 "C3" V 7848 1600 50  0000 C CNN
F 1 "0.22uf" V 7939 1600 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P2.00mm" H 8138 1450 50  0001 C CNN
F 3 "~" H 8100 1600 50  0001 C CNN
	1    8100 1600
	0    1    1    0   
$EndComp
Connection ~ 7950 1600
Wire Wire Line
	7950 1600 7950 1100
Wire Wire Line
	8250 1600 8250 1400
Wire Wire Line
	7500 2000 7700 2000
Wire Wire Line
	7700 2000 7700 4800
Wire Wire Line
	7700 4800 4050 4800
Wire Wire Line
	4050 4800 4050 5250
Connection ~ 7500 2000
Wire Wire Line
	3950 5250 3950 4800
Wire Wire Line
	3950 4800 3850 4800
Connection ~ 1500 4800
Wire Wire Line
	3750 5250 750  5250
Wire Wire Line
	750  5250 850  1100
Wire Wire Line
	850  1100 1500 1100
Wire Wire Line
	3550 1250 3550 4000
Wire Wire Line
	2100 3900 2800 3900
Wire Wire Line
	2800 3900 2800 1000
Wire Wire Line
	5300 1250 5300 1500
Connection ~ 5300 1250
Wire Wire Line
	5300 950  5300 1250
Wire Wire Line
	5300 850  5300 950 
Connection ~ 5300 950 
$Comp
L Connector:Conn_01x04_Male J4
U 1 1 5F18E76E
P 3950 5050
F 0 "J4" V 4012 5194 50  0000 L CNN
F 1 "Conn_01x04_Male" V 4103 5194 50  0000 L CNN
F 2 "" H 3950 5050 50  0001 C CNN
F 3 "~" H 3950 5050 50  0001 C CNN
	1    3950 5050
	0    1    1    0   
$EndComp
Wire Wire Line
	3850 4800 3850 5250
Connection ~ 3850 4800
Wire Wire Line
	3850 4800 1500 4800
$EndSCHEMATC
