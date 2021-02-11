/*
 * RC522.C
 *
 *  Created on: 11 févr. 2021
 *      Author: paulq
 */

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


static inline void spi_read( void * data, size_t size)
{
	nrfx_spi_xfer_desc_t desc = {
	.p_rx_buffer = data,
	.tx_length = 0,
	.p_tx_buffer = NULL,
	.rx_length = size
	};
    APP_ERROR_CHECK(nrfx_spi_xfer(&spi, &desc, 0));
}


static ret_code_t hardware_init(void)
{
    ret_code_t err_code;


    nrf_gpio_cfg_output(RC522_CS_PIN);

    nrfx_spi_config_t spi_config = NRFX_SPI_DEFAULT_CONFIG;

    spi_config.sck_pin  = ILI9341_SCK_PIN;
    spi_config.miso_pin = ILI9341_MISO_PIN;
    spi_config.mosi_pin = ILI9341_MOSI_PIN;
    spi_config.ss_pin   = ILI9341_SS_PIN;

    err_code = nrfx_spi_init(&spi, &spi_config, NULL, NULL);

void spi_event_handler(nrfx_spi_evt_t const * p_event,
                       void *                    p_context)
{
    spi_xfer_done = true;
//    NRF_LOG_INFO("Transfer completed.");
//    if (m_rx_buf[0] != 0)
//    {
//        NRF_LOG_INFO(" Received:");
//        NRF_LOG_HEXDUMP_INFO(m_rx_buf,1);
//    }
}
void PCD_WriteRegister(PCD_Register reg, byte value){
        nrf_gpio_pin_write(RC522_CS_PIN,0);
        m_tx_buf[0] = reg &0x7E;
        m_tx_buf[1] = value;
        memset(m_rx_buf, 0, m_length);
        spi_xfer_done = false;

        nrf_drv_spi_transfer(&spi,&m_tx_buf[0], m_length, NULL, 0);

        while (!spi_xfer_done)
        {
            __WFE();
        }

        nrf_gpio_pin_write(RC522_CS_PIN,1);
}
void PCD_WriteRegister_long(PCD_Register reg, byte count, byte *values){
nrf_gpio_pin_write(SPI_SS_PIN,0);
        m_tx_buf[0] = reg & 0x7E;
        memset(m_rx_buf, 0, m_length);
        spi_xfer_done = false;

        nrf_drv_spi_transfer(&spi,&m_tx_buf[0], m_length, NULL, 0);

        while (!spi_xfer_done)
        {
            __WFE();
        }
        NRF_LOG_FLUSH();

	for (byte index = 0; index < count; index++) {
	  memset(m_rx_buf, 0, m_length);
          spi_xfer_done = false;
          debug_info("long value[%d]:%x",index,values[index]);
          nrf_drv_spi_transfer(&spi, &values[index], m_length, NULL, 0);

          while (!spi_xfer_done)
          {
              __WFE();
          }
          NRF_LOG_FLUSH();
	}

nrf_gpio_pin_write(SPI_SS_PIN,1);
}
byte PCD_ReadRegister(PCD_Register reg){
        nrf_gpio_pin_write(SPI_SS_PIN,0);
        m_tx_buf[0] = (0x80 | (reg & 0x7E));
        memset(m_rx_buf, 0, m_length);
        spi_xfer_done = false;

        nrf_drv_spi_transfer(&spi,&m_tx_buf[0], m_length, m_rx_buf, m_length);

        while (!spi_xfer_done)
        {
            __WFE();
        }
        memset(m_rx_buf, 0, m_length);
        spi_xfer_done = false;
        _reg = 0x00;
        nrf_drv_spi_transfer(&spi,&_reg, m_length, m_rx_buf, m_length);

        while (!spi_xfer_done)
        {
            __WFE();
        }
        NRF_LOG_FLUSH();
        nrf_gpio_pin_write(SPI_SS_PIN,1);
        return m_rx_buf[0];

}
void PCD_ReadRegister_long(PCD_Register reg, byte count, byte *values, byte rxAlign){
    nrf_gpio_pin_write(SPI_SS_PIN,0);
	if (count == 0) {
		return;
	}
        byte address = 0x80 | (reg& 0x7E);				// MSB == 1 is for reading. LSB is not used in address. Datasheet section 8.1.2.3.
	    byte index = 0;
        count--;

        memset(m_rx_buf, 0, m_length);
        spi_xfer_done = false;

        nrf_drv_spi_transfer(&spi,&address, m_length, m_rx_buf, m_length);

        while (!spi_xfer_done)
        {
            __WFE();
        }
        NRF_LOG_FLUSH();

        if (rxAlign) {		// Only update bit positions rxAlign..7 in values[0]
		// Create bit mask for bit positions rxAlign..7
		byte mask = (0xFF << rxAlign) & 0xFF;
		// Read value and tell that we want to read the same address again.
                memset(m_rx_buf, 0, m_length);
                spi_xfer_done = false;

                nrf_drv_spi_transfer(&spi,&address, m_length, m_rx_buf, m_length);

                while (!spi_xfer_done)
                {
                  __WFE();
                }
                byte value = m_rx_buf[0];
		// Apply mask to both current value of values[0] and the new data in value.
		values[0] = (values[0] & ~mask) | (value & mask);
		index++;
	}

        while (index < count) {
        memset(m_rx_buf, 0, m_length);
        spi_xfer_done = false;

        nrf_drv_spi_transfer(&spi,&address, m_length, m_rx_buf, m_length);

        while (!spi_xfer_done)
        {
          __WFE();
        }
        values[index] = m_rx_buf[0];
        index++;
	}
        memset(m_rx_buf, 0, m_length);
        spi_xfer_done = false;
        uint8_t _reg = 0x00;
        nrf_drv_spi_transfer(&spi,&_reg, m_length, m_rx_buf, m_length);

        while (!spi_xfer_done)
        {
          __WFE();
        }
        values[index] = m_rx_buf[0];
nrf_gpio_pin_write(SPI_SS_PIN,1);
}


