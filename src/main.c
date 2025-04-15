#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/i2c.h>
//#include <zephyr/drivers/i2c/target/eeprom.h>

#define I2C0_NODE DT_NODELABEL(ioexpander)
static const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(I2C0_NODE);

int main(void)
{
        if (!device_is_ready(dev_i2c.bus)) {
                printk("I2C bus %s is not ready!\n\r",dev_i2c.bus->name);
                return 1;
        }
        
        uint8_t data = 0x00;
        uint8_t ret;
        printk("Successfully initialized! \n\r");
        while(1) {
                // ret = i2c_read_dt(&dev_i2c, &data, sizeof(data));
                // if(ret != 0){
                //         printk("Failed to read from I2C device address %x \n\r", dev_i2c.addr);
                //         return 1;
                // }
                uint8_t config[2] = {0x00, data};
                ret = i2c_write_dt(&dev_i2c, config, sizeof(config));
                if(ret != 0){
                        printk("Failed to write to I2C device address %x at reg. %x \n\r", dev_i2c.addr,config[0]);
                }
                k_msleep(1000);
                data = data + 1;
                if(data >= 0x7F)
                        data = 0x00;
        }

        return 0;
}