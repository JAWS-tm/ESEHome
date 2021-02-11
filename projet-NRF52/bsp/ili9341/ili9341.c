/*
 * ili9341.c
 *
 *  Created on: 9 févr. 2021
 *      Author: Nirgal
 */


#include "sdk_common.h"

#if NRF_MODULE_ENABLED(ILI9341)

#include "nrf_lcd.h"
#include "nrfx_spi.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "appli/common/gpio.h"
#include "appli/common/systick.h"

#define ILI9341_delay	SYSTICK_delay_ms

#define ILI9341_RESET				0x01
#define ILI9341_SLEEP_OUT			0x11
#define ILI9341_GAMMA				0x26
#define ILI9341_DISPLAY_OFF			0x28
#define ILI9341_DISPLAY_ON			0x29
#define ILI9341_COLUMN_ADDR			0x2A
#define ILI9341_PAGE_ADDR			0x2B
#define ILI9341_GRAM				0x2C
#define ILI9341_MAC					0x36
#define ILI9341_PIXEL_FORMAT		0x3A
#define ILI9341_WDB					0x51
#define ILI9341_WCD					0x53
#define ILI9341_RGB_INTERFACE		0xB0
#define ILI9341_FRC					0xB1
#define ILI9341_BPC					0xB5
#define ILI9341_DFC					0xB6
#define ILI9341_POWER1				0xC0
#define ILI9341_POWER2				0xC1
#define ILI9341_VCOM1				0xC5
#define ILI9341_VCOM2				0xC7
#define ILI9341_POWERA				0xCB
#define ILI9341_POWERB				0xCF
#define ILI9341_PGAMMA				0xE0
#define ILI9341_NGAMMA				0xE1
#define ILI9341_DTCA				0xE8
#define ILI9341_DTCB				0xEA
#define ILI9341_POWER_SEQ			0xED
#define ILI9341_3GAMMA_EN			0xF2
#define ILI9341_INTERFACE			0xF6
#define ILI9341_PRC					0xF7

typedef enum{				// Division ration for internal clocks
	LCD_FRC_DIVA_1	= 0x00,	// Fosc		(default)
	LCD_FRC_DIVA_2	= 0x01,	// Fosc/2
	LCD_FRC_DIVA_4	= 0x02,	// Fosc/4
	LCD_FRC_DIVA_8	= 0x03	// Fosc/8
}FRC_param1_DIVA;


typedef enum{					// Frame Rate
	LCD_FRC_RTNA_61HZ	= 0x1F,	// 61 Hz
	LCD_FRC_RTNA_63HZ	= 0x1E,	// 63 Hz
	LCD_FRC_RTNA_65HZ	= 0x1D,	// 65 Hz
	LCD_FRC_RTNA_68HZ	= 0x1C,	// 68 Hz
	LCD_FRC_RTNA_70HZ	= 0x1B,	// 70 Hz	(default)
	LCD_FRC_RTNA_73HZ	= 0x1A,	// 73 Hz
	LCD_FRC_RTNA_76HZ	= 0x19,	// 76 Hz
	LCD_FRC_RTNA_79HZ	= 0x18,	// 79 Hz
	LCD_FRC_RTNA_83HZ	= 0x17,	// 83 Hz
	LCD_FRC_RTNA_86HZ	= 0x16,	// 86 Hz
	LCD_FRC_RTNA_90HZ	= 0x15,	// 90 Hz
	LCD_FRC_RTNA_95HZ	= 0x14,	// 95 Hz
	LCD_FRC_RTNA_100HZ	= 0x13,	// 100 Hz
	LCD_FRC_RTNA_106HZ	= 0x12,	// 106 Hz
	LCD_FRC_RTNA_112HZ	= 0x11,	// 112 Hz
	LCD_FRC_RTNA_119HZ	= 0x10	// 119 Hz
}FRC_param2_RTNA;

// Set of commands described in ILI9341 datasheet.
#define ILI9341_NOP         0x00
#define ILI9341_SWRESET     0x01
#define ILI9341_RDDID       0x04
#define ILI9341_RDDST       0x09

#define ILI9341_SLPIN       0x10
#define ILI9341_SLPOUT      0x11
#define ILI9341_PTLON       0x12
#define ILI9341_NORON       0x13

#define ILI9341_RDMODE      0x0A
#define ILI9341_RDMADCTL    0x0B
#define ILI9341_RDPIXFMT    0x0C
#define ILI9341_RDIMGFMT    0x0D
#define ILI9341_RDSELFDIAG  0x0F

#define ILI9341_INVOFF      0x20
#define ILI9341_INVON       0x21
#define ILI9341_GAMMASET    0x26
#define ILI9341_DISPOFF     0x28
#define ILI9341_DISPON      0x29

#define ILI9341_CASET       0x2A
#define ILI9341_PASET       0x2B
#define ILI9341_RAMWR       0x2C
#define ILI9341_RAMRD       0x2E

#define ILI9341_PTLAR       0x30
#define ILI9341_MADCTL      0x36
#define ILI9341_PIXFMT      0x3A

#define ILI9341_FRMCTR1     0xB1
#define ILI9341_FRMCTR2     0xB2
#define ILI9341_FRMCTR3     0xB3
#define ILI9341_INVCTR      0xB4
#define ILI9341_DFUNCTR     0xB6

#define ILI9341_PWCTR1      0xC0
#define ILI9341_PWCTR2      0xC1
#define ILI9341_PWCTR3      0xC2
#define ILI9341_PWCTR4      0xC3
#define ILI9341_PWCTR5      0xC4
#define ILI9341_VMCTR1      0xC5
#define ILI9341_VMCTR2      0xC7
#define ILI9341_PWCTRSEQ    0xCB
#define ILI9341_PWCTRA      0xCD
#define ILI9341_PWCTRB      0xCF

#define ILI9341_RDID1       0xDA
#define ILI9341_RDID2       0xDB
#define ILI9341_RDID3       0xDC
#define ILI9341_RDID4       0xDD

#define ILI9341_GMCTRP1     0xE0
#define ILI9341_GMCTRN1     0xE1
#define ILI9341_DGMCTR1     0xE2
#define ILI9341_DGMCTR2     0xE3
#define ILI9341_TIMCTRA     0xE8
#define ILI9341_TIMCTRB     0xEA

#define ILI9341_ENGMCTR     0xF2
#define ILI9341_INCTR       0xF6
#define ILI9341_PUMP        0xF7

#define ILI9341_MADCTL_MY  0x80
#define ILI9341_MADCTL_MX  0x40
#define ILI9341_MADCTL_MV  0x20
#define ILI9341_MADCTL_ML  0x10
#define ILI9341_MADCTL_RGB 0x00
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_MADCTL_MH  0x04

static const nrfx_spi_t spi = NRFX_SPI_INSTANCE(ILI9341_SPI_INSTANCE);

static inline void spi_write(const void * data, size_t size)
{
	nrfx_spi_xfer_desc_t desc = {
	.p_rx_buffer = NULL,
	.tx_length = size,
	.p_tx_buffer = data,
	.rx_length = 0
	};
    APP_ERROR_CHECK(nrfx_spi_xfer(&spi, &desc, 0));
}



static inline void write_command(uint8_t c)
{
    nrf_gpio_pin_clear(ILI9341_DC_PIN);
    spi_write(&c, sizeof(c));
}

static inline void write_data(uint8_t c)
{
    nrf_gpio_pin_set(ILI9341_DC_PIN);
    spi_write(&c, sizeof(c));
}

static void set_addr_window(uint16_t x_0, uint16_t y_0, uint16_t x_1, uint16_t y_1)
{
    ASSERT(x_0 <= x_1);
    ASSERT(y_0 <= y_1);

    write_command(ILI9341_CASET);
    write_data(x_0 >> 8);
    write_data(x_0);
    write_data(x_1 >> 8);
    write_data(x_1);
    write_command(ILI9341_PASET);
    write_data(y_0 >> 8);
    write_data(y_0);
    write_data(y_1 >> 8);
    write_data(y_1);
    write_command(ILI9341_RAMWR);
}

static void command_list(void)
{
	/*	//command list from driver NRF
    write_command(ILI9341_SWRESET);
    nrf_delay_ms(120);
    write_command(ILI9341_DISPOFF);
    nrf_delay_ms(120);
    write_command(ILI9341_PWCTRB);
    write_data(0x00);
    write_data(0XC1);
    write_data(0X30);

    write_command(ILI9341_TIMCTRA);
    write_data(0x85);
    write_data(0x00);
    write_data(0x78);

    write_command(ILI9341_PWCTRSEQ);
    write_data(0x39);
    write_data(0x2C);
    write_data(0x00);
    write_data(0x34);
    write_data(0x02);

    write_command(ILI9341_PUMP);
    write_data(0x20);

    write_command(ILI9341_TIMCTRB);
    write_data(0x00);
    write_data(0x00);

    write_command(ILI9341_PWCTR1);
    write_data(0x23);

    write_command(ILI9341_PWCTR2);
    write_data(0x10);

    write_command(ILI9341_VMCTR1);
    write_data(0x3e);
    write_data(0x28);

    write_command(ILI9341_VMCTR2);
    write_data(0x86);

    write_command(ILI9341_MADCTL);
    write_data(0x48);

    write_command(ILI9341_PIXFMT);
    write_data(0x55);

    write_command(ILI9341_FRMCTR1);
    write_data(0x00);
    write_data(0x18);

    write_command(ILI9341_DFUNCTR);
    write_data(0x08);
    write_data(0x82);
    write_data(0x27);

    write_command(ILI9341_ENGMCTR);
    write_data(0x00);

    write_command(ILI9341_GAMMASET);
    write_data(0x01);

    write_command(ILI9341_GMCTRP1);
    write_data(0x0F);
    write_data(0x31);
    write_data(0x2B);
    write_data(0x0C);
    write_data(0x0E);
    write_data(0x08);
    write_data(0x4E);
    write_data(0xF1);
    write_data(0x37);
    write_data(0x07);
    write_data(0x10);
    write_data(0x03);
    write_data(0x0E);
    write_data(0x09);
    write_data(0x00);

    write_command(ILI9341_GMCTRN1);
    write_data(0x00);
    write_data(0x0E);
    write_data(0x14);
    write_data(0x03);
    write_data(0x11);
    write_data(0x07);
    write_data(0x31);
    write_data(0xC1);
    write_data(0x48);
    write_data(0x08);
    write_data(0x0F);
    write_data(0x0C);
    write_data(0x31);
    write_data(0x36);
    write_data(0x0F);

    write_command(ILI9341_SLPOUT);
    nrf_delay_ms(120);
    write_command(ILI9341_DISPON);

*/




// Command list from driver F103

    write_command(ILI9341_SLEEP_OUT);
    	ILI9341_delay(7);

    	// Power control A
    	write_command(ILI9341_POWERA);
    	write_data(0x39);
    	write_data(0x2C);
    	write_data(0x00);
    	write_data(0x34);
    	write_data(0x02);

    	//ILI9341_sendMultipleData((Uint8 []){0x39, 0x2C, 0x00, 0x34, 0x02}, 5);

    	// Power control B
    	write_command(ILI9341_POWERB);
    	write_data(0x00);
    	write_data(0xC1);
    	write_data(0x30);

    	//ILI9341_sendMultipleData((Uint8 []){0x00, 0xC1, 0x30}, 3);

    	// Driver timing control A
    	write_command(ILI9341_DTCA);
    	write_data(0x85);
    	write_data(0x00);
    	write_data(0x78);

    	//ILI9341_sendMultipleData((Uint8 []){0x85, 0x00, 0x78}, 3);


    	// Driver timing control B
    	write_command(ILI9341_DTCB);
    	write_data(0x00);
    	write_data(0x00);

    	//ILI9341_sendMultipleData((Uint8 []){0x00, 0x00}, 2);

    	// Power on sequence control
    	write_command(ILI9341_POWER_SEQ);
    	write_data(0x64);
    	write_data(0x03);
    	write_data(0x12);
    	write_data(0x81);

    	//ILI9341_sendMultipleData((Uint8 []){0x64, 0x03, 0x12, 0x81}, 4);

    	// Pump ratio control
    	write_command(ILI9341_PRC);
    	write_data(0x20);

    	// Power control 1
    	write_command(ILI9341_POWER1);
    	write_data(0x03);

    	// Power control 2
    	write_command(ILI9341_POWER2);
    	write_data(0x10);

    	// VCOM control 1
    	write_command(ILI9341_VCOM1);
    	write_data(0x3E);
    	write_data(0x28);

    	//ILI9341_sendMultipleData((Uint8 []){0x3E, 0x28}, 2);

    	// VCOM control 2
    	write_command(ILI9341_VCOM2);
    	write_data(0x86);

    	// Memory access control
    	write_command(ILI9341_MAC);
    	write_data(0x48);

    	// Pixel format set
    	write_command(ILI9341_PIXEL_FORMAT);
    	write_data(0x55);

    	// Frame rate control
    	write_command(ILI9341_FRC);
    	write_data(LCD_FRC_DIVA_1);
    	write_data(LCD_FRC_RTNA_119HZ);

    	//ILI9341_sendMultipleData((Uint8 []){LCD_FRC_DIVA_1, LCD_FRC_RTNA_119HZ}, 2);

    	// Display function control
    	write_command(ILI9341_DFC);
    	write_data(0x08);
    	write_data(0x82);
    	write_data(0x27);

    	//ILI9341_sendMultipleData((Uint8 []){0x08, 0x82, 0x27}, 3);

    	// 3Gamma function disable
    	write_command(ILI9341_3GAMMA_EN);
    	write_data(0x00);

    	// Gamma curve selected
    	write_command(ILI9341_GAMMA);
    	write_data(0x01);

    	// Set positive gamma
    	write_command(ILI9341_PGAMMA);
    	write_data(0x0F);
    	write_data(0x31);
    	write_data(0x2B);
    	write_data(0x0C);
    	write_data(0x0E);
    	write_data(0x08);
    	write_data(0x4E);
    	write_data(0xF1);
    	write_data(0x37);
    	write_data(0x07);
    	write_data(0x10);
    	write_data(0x03);
    	write_data(0x0E);
    	write_data(0x09);
    	write_data(0x00);

    	//ILI9341_sendMultipleData((Uint8 []){0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00}, 15);

    	// Set negative gama
    	write_command(ILI9341_NGAMMA);
    	write_data(0x00);
    	write_data(0x0E);
    	write_data(0x14);
    	write_data(0x03);
    	write_data(0x11);
    	write_data(0x07);
    	write_data(0x31);
    	write_data(0xC1);
    	write_data(0x48);
    	write_data(0x08);
    	write_data(0x0F);
    	write_data(0x0C);
    	write_data(0x31);
    	write_data(0x36);
    	write_data(0x0F);

    	//ILI9341_sendMultipleData((Uint8 []){0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F}, 15);

    	ILI9341_delay(5);

    	write_command(ILI9341_DISPLAY_ON);
}

static ret_code_t hardware_init(void)
{
    ret_code_t err_code;

    nrf_gpio_cfg_output(ILI9341_DC_PIN);
    nrf_gpio_cfg_output(ILI9341_SS_PIN);

    nrfx_spi_config_t spi_config = NRFX_SPI_DEFAULT_CONFIG;

    spi_config.sck_pin  = ILI9341_SCK_PIN;
    spi_config.miso_pin = ILI9341_MISO_PIN;
    spi_config.mosi_pin = ILI9341_MOSI_PIN;
    spi_config.ss_pin   = ILI9341_SS_PIN;

    err_code = nrfx_spi_init(&spi, &spi_config, NULL, NULL);

    //RESET TFT...
    nrf_gpio_cfg_output(ILI9341_RST_PIN);
    GPIO_write(ILI9341_RST_PIN, 0);
    SYSTICK_delay_ms(2);	//> 10us
    GPIO_write(ILI9341_RST_PIN, 1);
    SYSTICK_delay_ms(10);	// > 5 ms before sending command !

    return err_code;
}

static ret_code_t ili9341_init(void)
{
    ret_code_t err_code;

    err_code = hardware_init();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    command_list();

    return err_code;
}

static void ili9341_uninit(void)
{
    nrfx_spi_uninit(&spi);
}

static void ili9341_pixel_draw(uint16_t x, uint16_t y, uint32_t color)
{
    set_addr_window(x, y, x, y);

    const uint8_t data[2] = {color >> 8, color};

    nrf_gpio_pin_set(ILI9341_DC_PIN);

    spi_write(data, sizeof(data));

    nrf_gpio_pin_clear(ILI9341_DC_PIN);
}

static void ili9341_rect_draw(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color)
{
    set_addr_window(x, y, x + width - 1, y + height - 1);

    const uint8_t data[2] = {color >> 8, color};

    nrf_gpio_pin_set(ILI9341_DC_PIN);

    // Duff's device algorithm for optimizing loop.
    uint32_t i = (height * width + 7) / 8;

/*lint -save -e525 -e616 -e646 */
    switch ((height * width) % 8) {
        case 0:
            do {
                spi_write(data, sizeof(data));
        case 7:
                spi_write(data, sizeof(data));
        case 6:
                spi_write(data, sizeof(data));
        case 5:
                spi_write(data, sizeof(data));
        case 4:
                spi_write(data, sizeof(data));
        case 3:
                spi_write(data, sizeof(data));
        case 2:
                spi_write(data, sizeof(data));
        case 1:
                spi_write(data, sizeof(data));
            } while (--i > 0);
        default:
            break;
    }
/*lint -restore */

    nrf_gpio_pin_clear(ILI9341_DC_PIN);
}

static void ili9341_dummy_display(void)
{
    /* No implementation needed. */
}

static void ili9341_rotation_set(nrf_lcd_rotation_t rotation)
{
    write_command(ILI9341_MADCTL);
    switch (rotation) {
        case NRF_LCD_ROTATE_0:
            write_data(ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR);
            break;
        case NRF_LCD_ROTATE_90:
            write_data(ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR);
            break;
        case NRF_LCD_ROTATE_180:
            write_data(ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR);
            break;
        case NRF_LCD_ROTATE_270:
            write_data(ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR);
            break;
        default:
            break;
    }
}

static void ili9341_display_invert(bool invert)
{
    write_command(invert ? ILI9341_INVON : ILI9341_INVOFF);
}

static lcd_cb_t ili9341_cb = {
    .height = ILI9341_HEIGHT,
    .width = ILI9341_WIDTH
};


const nrf_lcd_t nrf_lcd_ili9341 = {
    .lcd_init = ili9341_init,
    .lcd_uninit = ili9341_uninit,
    .lcd_pixel_draw = ili9341_pixel_draw,
    .lcd_rect_draw = ili9341_rect_draw,
    .lcd_display = ili9341_dummy_display,
    .lcd_rotation_set = ili9341_rotation_set,
    .lcd_display_invert = ili9341_display_invert,
    .p_lcd_cb = &ili9341_cb
};

#endif // NRF_MODULE_ENABLED(ILI9341)
