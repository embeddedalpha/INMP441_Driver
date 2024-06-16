/*
 * I2S_Defs.h
 *
 *  Created on: Jun 12, 2024
 *      Author: kunal
 */

#ifndef I2S_DEFS_H_
#define I2S_DEFS_H_


static const struct I2S_Audio_Frequency{

	uint8_t _8000KHz;
	uint8_t _16000Hz;
	uint8_t _22050Hz;
	uint8_t _32000Hz;
	uint8_t _44100Hz;
	uint8_t _48000Hz;
	uint8_t _64000Hz;
	uint8_t _96000Hz;
	uint8_t _192000Hz;
	uint8_t _384000Hz;

}I2S_Audio_Frequency = {
		._8000KHz = 1,
		._16000Hz = 2,
		._22050Hz = 3,
		._32000Hz = 4,
		._44100Hz = 5,
		._48000Hz = 6,
		._64000Hz = 7,
		._96000Hz = 8,
		._192000Hz = 9,
		._384000Hz = 10,
};

static const struct I2S_Standard{

	int8_t Standard_Philips;
	int8_t Left_Justified;
	int8_t Right_Justified;
	int8_t PCM;

}I2S_Standard = {
		.Standard_Philips = 1,
		.Left_Justified =2,
		.Right_Justified = 3,
		.PCM = 4,
};

static const struct I2S_Data_Length{

	int8_t _16_bit;
	int8_t _24_bit;
	int8_t _32_bit;

}I2S_Data_Length = {
		._16_bit = 0x01,
		._24_bit = 0x02,
		._32_bit = 0x03,
};

static const struct I2S_Channel_Length{

	int8_t _16_bit;
	int8_t _32_bit;

}I2S_Channel_Length = {
		._16_bit = 0x01,
		._32_bit = 0x03,
};




static const struct I2S_Port{

	SPI_TypeDef *I2S2;
	SPI_TypeDef *I2S3;

}I2S_Port = {SPI2,SPI3};


static const struct I2S_Mode
{
	struct {
		uint8_t Transmit;
		uint8_t Receive;
	}Master;
	struct {
		uint8_t Transmit;
		uint8_t Receive;
	}Slave;

}I2S_Mode =
		{
			.Master = {
					.Transmit = 0x01,
					.Receive = 0x02,
			},
			.Slave = {
					.Transmit = 0x03,
					.Receive = 0x04,
			},
		};



static const struct I2S_Pin
{
	/*****************************************************************************************/
	const struct
	{
		const struct
		{
			uint8_t Disable;
			uint8_t PC7;
		}I2S2;

		const struct{
			uint8_t Disable;
			uint8_t PC6;
		}I2S3;

	}MCK;
	/*****************************************************************************************/
	const struct SCK
	{
		const struct{

			uint8_t PB10;
			uint8_t PB13;
		}I2S2;

	}SCK;
	/*****************************************************************************************/
	const struct WS
	{
		const struct{

			uint8_t PB12;
			uint8_t PB09;
		}I2S2;

	}WS;
	/*****************************************************************************************/
	const struct SD
	{
		const struct{

			uint8_t PC03;
			uint8_t PB15;
		}I2S2;

	}SD;
	/*****************************************************************************************/
	const struct EXT_SD
	{
		const struct{

			uint8_t PC02;
			uint8_t PB14;
		}I2S2;

	}EXT_SD;


}I2S_Pin = {

		/*****************************************************************************************/
		.MCK =
		{
				.I2S2 = {
						.Disable = 0xFF,
						.PC7 = 37,
				},

				.I2S3 = {
						.Disable = 0xFF,
						.PC6 = 36,
				},
		},
		/*****************************************************************************************/
		.SCK = {

				.I2S2 = {
						.PB10 = 210,
						.PB13 = 213,
				},
		},
		/*****************************************************************************************/
		.WS = {

				.I2S2 = {
						.PB12 = 212,
						.PB09 = 209,
				},
		},
		/*****************************************************************************************/
		.SD = {

				.I2S2 = {
						.PC03 = 223,
						.PB15 = 213,
				},
		},
		/*****************************************************************************************/
		.EXT_SD = {

				.I2S2 = {
						.PC02 = 202,
						.PB14 = 214,
				},
		},

};
/////////////////////////////////////////////////////////////////////////////////////////////////////////








#endif /* I2S_DEFS_H_ */
