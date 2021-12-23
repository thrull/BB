/*
 * wind.c (ported from wind.cpp)
 *
 *  Created on: Jan 23, 2017
 *      Author: fiala
 *      Ported to Strato by: thrull
 */

#include "wind.h"
#include "fc.h"
#include "../common.h"

void wind_new_gps_fix()
{
    float speed = fc.gnss.ground_speed; // m/s
    float angle = fc.gnss.heading;

    uint8_t sector = (uint8_t) (angle + (360 / WIND_NUM_OF_SECTORS / 2)) % 360 / (360 / WIND_NUM_OF_SECTORS);

    fc.wind.dir[sector] = angle;
    fc.wind.spd[sector] = speed;

    //DBG

    if (sector == (fc.wind.old_sector + 1) % WIND_NUM_OF_SECTORS)
    {	//clockwise move
        if (fc.wind.sectors_cnt >= 0)
            fc.wind.sectors_cnt += 1;
        else
            fc.wind.sectors_cnt = 0;
    }
    else
    {
        if (fc.wind.old_sector == (sector + 1) % WIND_NUM_OF_SECTORS)
        {	//counterclockwise move
            if (fc.wind.sectors_cnt <= 0)
                fc.wind.sectors_cnt -= 1;
            else
                fc.wind.sectors_cnt = 0;
        }
        else
            if (fc.wind.old_sector == sector)
            {	//same sector
            }
            else
                //more than (360 / number_of_sectors), discart data
                fc.wind.sectors_cnt = 0;
    }

    fc.wind.old_sector = sector;

    int8_t min = 0;
    int8_t max = 0;

    if (abs(fc.wind.sectors_cnt) >= WIND_NUM_OF_SECTORS)
    {
        for (uint8_t i = 1; i < WIND_NUM_OF_SECTORS; i++)
        {
            if (fc.wind.spd[i] > fc.wind.spd[max])
                max = i;
            if (fc.wind.spd[i] < fc.wind.spd[min])
                min = i;
        }

        int8_t sectorDiff = abs(max - min);
        DBG(" min=%d max=%d diff=%d\n",min, max, sectorDiff);
        if ((sectorDiff >= ( WIND_NUM_OF_SECTORS / 2 - 1)) && (sectorDiff <= ( WIND_NUM_OF_SECTORS / 2 + 1)))
        {
            fc.wind.speed = (fc.wind.spd[max] - fc.wind.spd[min]) / 2;
            fc.wind.direction = fc.wind.dir[min];
            fc.wind.valid = true;
            fc.wind.valid_from = HAL_GetTick();
            DBG(" #5 wspd=%0.1f wdir=%0.1f\n", fc.wind.speed, fc.wind.direction);
        }
    }

}

void wind_init()
{
    for (int i = 0; i < WIND_NUM_OF_SECTORS; i++)
    {
        fc.wind.spd[i] = 0;
        fc.wind.dir[i] = 0;
    }

    fc.wind.sectors_cnt = 0;
    fc.wind.old_sector = 0;
    fc.wind.valid = false;

    DBG("wind_init\n");
}

void wind_step()
{
	if (fc.gnss.new_sample & FC_GNSS_NEW_SAMPLE_WIND)
	{
        wind_new_gps_fix();

        fc.gnss.new_sample &= ~FC_GNSS_NEW_SAMPLE_WIND;
    }
}
