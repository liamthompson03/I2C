#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/i2c.h>
//#include <zephyr/drivers/i2c/target/eeprom.h>

#define I2C0_NODE DT_NODELABEL(i2c0)
static const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(I2C0_NODE);

int main(void)
{
        return 0;
}