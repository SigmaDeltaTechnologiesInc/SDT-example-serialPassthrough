#include "mbed.h"

/*
ESP32_DevKitC_V4            Device
    "TX"            "MBED_CONF_APP_DEV_RX"
    "RX"            "MBED_CONF_APP_DEV_TX"
    "EN"            "MBED_CONF_APP_DEV_EN"
    "0"             "MBED_CONF_APP_DEV_IO0"
*/

#define DELAY       1000        // ms
#define BAUDRATE    115200

RawSerial  pc(USBTX, USBRX, BAUDRATE);
RawSerial  dev(MBED_CONF_APP_DEV_TX, MBED_CONF_APP_DEV_RX, BAUDRATE);
DigitalOut en(MBED_CONF_APP_DEV_EN);
DigitalOut io0(MBED_CONF_APP_DEV_IO0);

DigitalOut led1(MBED_CONF_APP_STATUS_LED, MBED_CONF_APP_LED_OFF);       // Check pin number!!



void dev_recv()
{
    while(dev.readable()) {
        pc.putc(dev.getc());
    }
}

void pc_recv()
{
    while(pc.readable()) {
        dev.putc(pc.getc());
    }
}

int main()
{
    ThisThread::sleep_for(DELAY);
    io0 = 0;
    ThisThread::sleep_for(DELAY);
    en = 0;
    ThisThread::sleep_for(DELAY);
    en = 1;
    ThisThread::sleep_for(DELAY);
    io0 = 1;
    ThisThread::sleep_for(DELAY);

    led1 = MBED_CONF_APP_LED_ON;
 
    pc.attach(&pc_recv, Serial::RxIrq);
    dev.attach(&dev_recv, Serial::RxIrq);
 
    while(1) {
        sleep();
    }
}
