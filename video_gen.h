#ifndef VIDEO_GEN_H
#define VIDEO_GEN_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include "spec/video_properties.h"
#include "spec/hardware_setup.h"

typedef struct {
    volatile int scanLine;
    volatile unsigned long frames;
    unsigned char start_render;
    // remove me
    int lines_frame;
    uint8_t vres;
    uint8_t hres;
    // remove me
    uint8_t output_delay;
    // combine me with status switch
    char vscale_const;
    // combine me too.
    char vscale;
    // remove me
    char vsync_end;
    uint8_t* screen;
} TVout_vid;

extern TVout_vid display;

extern void (*hbi_hook)();
extern void (*vbi_hook)();

void render_setup(uint8_t mode, uint8_t x, uint8_t y, uint8_t *scrnptr);

void blank_line();
void active_line();
void vsync_line();
void empty();

// tone generation properties
extern volatile long remainingToneVsyncs;

// 6cycles functions
void render_line6c();
void render_line5c();
void render_line4c();
void render_line3c();
static void inline wait_until(uint8_t time);
#endif
