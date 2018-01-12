#ifndef __MS8607_h__
#define __MS8607_h__

typedef union   
{
	struct
	{
		unsigned bInit:1;
		unsigned bHold:1;
	};
	unsigned int AllFlag;
} _MS8607_Flags;        // general flags


enum ms8607_humidity_i2c_master_mode { ms8607_i2c_hold, ms8607_i2c_no_hold };

enum ms8607_humidity_resolution {
	ms8607_humidity_resolution_12b = 0,
	ms8607_humidity_resolution_8b,
	ms8607_humidity_resolution_10b,
	ms8607_humidity_resolution_11b
};

enum ms8607_battery_status { ms8607_battery_ok, ms8607_battery_low };

enum ms8607_heater_status { ms8607_heater_off, ms8607_heater_on };

enum ms8607_pressure_resolution {
	ms8607_pressure_resolution_osr_256 = 0,
	ms8607_pressure_resolution_osr_512,
	ms8607_pressure_resolution_osr_1024,
	ms8607_pressure_resolution_osr_2048,
	ms8607_pressure_resolution_osr_4096,
	ms8607_pressure_resolution_osr_8192
};
extern unsigned int MS8607_eeprom[8];
extern _MS8607_Flags MS8607_Flags;
extern ulong MS8607_adcT;
extern ulong MS8607_adcP;
extern uint MS8607_adcRH;
extern float32 MS8607_Temperature;
extern float32 MS8607_Pressure;
extern float32 MS8607_RH;
unsigned char MS8607_Init(void);
unsigned char MS8607_ReadPT(unsigned char resolution_osr);
unsigned char MS8607_I2CProc(unsigned char Addr,unsigned char Command,unsigned char NeedReadLen);
void MS8607_CalculatePT(void);
unsigned char MS8607_ReadRH(void);
#endif // __MS8607_h__