/* ===================================================
C code : test.cpp
* ===================================================
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sched.h>
#include "RCSwitch.h"
#include "RcOok.h"
#include "Sensor.h"

char tw[][31]=
{
    "MAV AA99956A959A59599A55556625",
    "MAV AA999559959A59599A6A666916",
    "MAV AA999559959A995999A9AAAA16",
    "MAV AA99955995A569599A6A569915",
    "MAV AA99955995A559599A99A66915",
    "MAV AA999559959AA9599A55555516",
    "MAV AA999559959A99599AA6A5A516",
    "MAV AA999559959A9959A56566662A",
    "MAV AA999559959A695A5956556525",
    "MAV AA999559959A695A556A695915",
    "MAV AA999559959A69559996A56A2A",
    "MAV AA99955995A59955995A565629",
    "MAV AA99955995A55959AA69569919",
    "MAV AA999559959AA959A9AAAAAA1A",
    ""
};



// int main()
// {
//     int i=0;
//     while (*tw[i])
//     {
//         printf("%s ",tw[i]);
//         Sensor *s = Sensor::getRightSensor(tw[i]);
//         if (s!= NULL)
//         {
// //             if(s->availableTemp())
// //                 printf("Temp : %f\n",s->getTemperature());
// //             if(s->availableTemp2())
// //                 printf("Temp2 : %f\n",s->getTemperature2());
// //             if(s->availableHumidity())
// //                 printf("Humidity : %f\n",s->getHumidity());
// //             if(s->hasChannel())
// //                 printf("Channel : %d\n",s->getChannel());
//         }
//         delete s;
//         i++;
//     }
// }

int main(int argc, char *argv[])
{
    int RXPIN = 1;
    int TXPIN = 0;
    int i=0;

    if(wiringPiSetup() == -1)
        return 0;
// struct sched_param param;
// param.sched_priority = 99;
// if (sched_setscheduler(0, SCHED_FIFO, & param) != 0) {
//     perror("sched_setscheduler");
// exit(EXIT_FAILURE);
// }

    if (argc>1 && *argv[1]=='t')
        while (*tw[i])
        {
            printf("%s ",tw[i]);
            Sensor *s = Sensor::getRightSensor(tw[i]);
            if (s!= NULL)
            {
//             if(s->availableTemp())
//                 printf("Temp : %f\n",s->getTemperature());
//             if(s->availableTemp2())
//                 printf("Temp2 : %f\n",s->getTemperature2());
//             if(s->availableHumidity())
//                 printf("Humidity : %f\n",s->getHumidity());
//             if(s->hasChannel())
//                 printf("Channel : %d\n",s->getChannel());
            }
            delete s;
            i++;
        }
    else
    {
        RCSwitch *rc = new RCSwitch(RXPIN,TXPIN);

        while (1)
        {
            if (rc->OokAvailable())
            {
                char message[100];

                rc->getOokCode(message);
                printf("%s\n",message);

                Sensor *s = Sensor::getRightSensor(message);
                if (s!= NULL)
                {
                    if(s->availableTemp())
                        printf("Temp : %f\n",s->getTemperature());
                    if(s->availableTemp2())
                        printf("Temp2 : %f\n",s->getTemperature2());
                    if(s->availableHumidity())
                        printf("Humidity : %f\n",s->getHumidity());
                    if(s->hasChannel())
                        printf("Channel : %d\n",s->getChannel());
                }
                delete s;
            }
            //delay(1000);
        }
    }
}
