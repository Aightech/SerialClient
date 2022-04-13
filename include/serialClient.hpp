#ifndef CLVHDMASTER_H
#define CLVHDMASTER_H

#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

// Linux headers
#include <errno.h>   // Error integer and strerror() function
#include <fcntl.h>   // Contains file controls like O_RDWR
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()

#include <stdio.h>

#define GLOBAL_VERBOSE_LEVEL 0

#define CONFIG_REG 0x00

#define FLEX_CH1_CN_REG 0x01
#define FLEX_CH2_CN_REG 0x02
#define FLEX_CH3_CN_REG 0x03
#define FLEX_PACE_CN_REG 0x04
#define FLEX_VBAT_CN_REG 0x05

#define OSC_CN_REG 0x12

#define AFE_RES_REG 0x13
#define AFE_SHDN_CN_REG 0x14
#define AFE_PACE_CN_REG 0x17

#define ERROR_STATUS_REG 0x19

#define DATA_STATUS_REG 0x30

#define R1_RATE_REG 0x25
#define R2_RATE_REG 0x21
#define R3_RATE_CH1_REG 0x22
#define R3_RATE_CH2_REG 0x23
#define R3_RATE_CH3_REG 0x24

class SerialClient
{
    public:
    SerialClient(const char *path);
    ~SerialClient() { close(m_fd); };

    void
    printBit(int8_t val)
    {
        std::cout << " " << std::flush;
        for(int i = 0; i < 8; i++)
            if(1 & (val >> i))
                std::cout << "[" + std::to_string(i) + "] " << std::flush;
    }

    int
    readSerial(uint8_t *buffer, size_t size)
    {
        return read(m_fd, buffer, size);
    };

    int
    writeSerial(const void *buffer, size_t size)
    {
        return write(m_fd, buffer, size);
    };

    void
    setup()
    {
        // ARDUINO SIDE
        // Serial.write(0x40);
        // char c;
        // while (c != 0xbb)
        // {
        //   c = Serial.read();
        // }

        uint8_t buff[1] = {'.'};
        std::cout << "Connecting" << std::flush;
        while(buff[0] != 0x40) //empty the random char
        {
            int n = this->readSerial(buff, 1);
            std::cout << buff[0] << std::flush;
            usleep(1000);
        }
        buff[0] = 0xbb;
        this->writeSerial(buff, 1);
        usleep(10000);
        std::cout << std::endl;
    };

    private:
    int m_fd;
};

#endif
