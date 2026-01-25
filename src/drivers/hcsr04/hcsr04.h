#ifndef DRIVER_DISTANCE_H
#define DRIVER_DISTANCE_H

#include <stdbool.h>

typedef struct {
    int trig_gpio;
    int echo_gpio;
} distance_sensor_t;

void distance_init(const distance_sensor_t *s);
bool distance_read_cm(const distance_sensor_t *s, float *out_cm);

#endif
