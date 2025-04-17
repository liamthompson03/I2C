#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/i2c.h>
//#include <zephyr/drivers/i2c/target/eeprom.h>

#define I2C0_NODE DT_NODELABEL(adc)
static const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(I2C0_NODE);

int main(void)
{
        if (!device_is_ready(dev_i2c.bus)) {
                printk("I2C bus %s is not ready!\n\r",dev_i2c.bus->name);
                return 1;
        }
        /*
        ADC notes:
         0: First byte written is always to the address pointer.
                First 4 bits are a command if in mode 2, second 4 bits are the address of the register to write to.
                Because of the I2C protocol structure, we won't be writing to this register explicitly, rather it is bundled
                with the write address... changing the 4 MSBs of the write address allows for writing a command. Otherwise, address
                normally.

                Command mode allows a conversion to be initiated on a write operation and is enabled by passing a command other than
                x0 to the address pointer. We'll want to pass x8 to initiate a conversion on channel 1, which can be accessed in the conversion
                result register. Command x7 tells the controller to enqueue sequential conversions from channels specified in the configuration 
                register.

         1: Initialize configuration register (x0) to value xxxx 00000001 0 00 = 0x0008
              (selects analog channel 1, disable I2C filtering, ALERT/BUSY disabled)
              Setting more than 1 bit high on the channel selection is necessary for multiple enqueued conversions when using command x7 on mode 2.

         2: 

        */
        
        uint8_t data = 0x00;
        uint8_t ret;
        printk("Successfully initialized! \n\r");
        while(1) {
                // ret = i2c_read_dt(&dev_i2c, &data, sizeof(data));
                // if(ret != 0){
                //         printk("Failed to read from I2C device address %x \n\r", dev_i2c.addr);
                //         return 1;
                // }
                ret = i2c_reg_read_byte_dt(&dev_i2c, 0x00, &data);
                if(ret != 0){
                        printk("Failed to read I2C device address %x \n\r", dev_i2c.addr);
                }
                printk("Got %x \n\r", data);
                k_msleep(1000);
        }

        return 0;
}