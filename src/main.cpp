#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <stdio.h>

#include "serialClient.hpp"
#include <lsl_cpp.h>

int
main()
{
    std::cout << "CleverHand Serial Interface:" << std::endl;

    SerialClient device = SerialClient("/dev/ttyACM0");
    device.setup();
    int16_t val16[8 * 8];

    try
    {
        int nb_ch = 8 * 8;
        lsl::stream_info info_sample("pressure", "sample", nb_ch, 0,
                                     lsl::cf_int32);
        lsl::stream_outlet outlet_sample(info_sample);
        std::vector<int32_t> sample(nb_ch);
        std::cout << "[INFOS] Now sending data... " << std::endl;
        for(int t = 0;; t++)
        {
            //val8 = clvHd.readReg<uint8_t>(15, 0x30);

            if(true) //val8 & 0b00100100)
            {
                //std::cout << " hoy " << std::endl;
	      uint8_t buff[128] = { '\n'};
	      int m = 0;
                device.writeSerial(buff, 1);
                int n = 0;
                while(n < 128)
                {
                    n += device.readSerial(buff + n, 128 - n);
		}
                for(int i = 0; i < 8; i++)
                {
                    for(int j = 0; j < 8; j++)
                    {

                        std::cout << "  " << ((int16_t *)buff)[i * 8 + j];
                        sample[i * 8 + (8-j)] = ((int16_t *)buff)[i * 8 + j];
                    }
                    std::cout << std::endl;
                }
                std::cout << std::endl;
                std::cout << std::endl;
                for(int i = 0; i < 8 * 8; i++)
                { sample[i] = ((int16_t *)buff)[i]; }

                //std::cout << std::hex << val16 << std::endl;
                outlet_sample.push_sample(sample);
            }
        }
    }
    catch(std::exception &e)
    {
        std::cerr << "[ERROR] Got an exception: " << e.what() << std::endl;
    }
    uint8_t b[1] = {'n'};
    device.writeSerial(b, 1);

    return 0; // success
}
