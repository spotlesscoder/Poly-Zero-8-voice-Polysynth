// This optional setting causes Encoder to use more optimized code,
// It must be defined before Encoder.h is included.
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
#include <Bounce.h>
#include "TButton.h"
#include <ADC.h>
#include <ADC_util.h>

ADC *adc = new ADC();

#define NEOPIXEL_OUTPUT 29

//Teensy 4.1 - Mux Pins
#define MUX_0 30
#define MUX_1 31
#define MUX_2 32

#define MUX1_S A11 // ADC0
#define MUX2_S A10 // ADC0
#define MUX3_S A2  // ADC1
#define MUX4_S A1  // ADC1
#define MUX5_S A0  // ADC1

#define DAC_CS1 10
#define DAC_CS2 19
#define DAC_CS3 18

#define DEMUX_0 36
#define DEMUX_1 35
#define DEMUX_2 34
#define DEMUX_3 33

#define DEMUX_EN_1 39
#define DEMUX_EN_2 38

//Mux 1 Connections
#define MUX1_volumeControl 0
#define MUX1_ampAttack 1
#define MUX1_ampDecay 2
#define MUX1_spare3 3
#define MUX1_ampSustain 4
#define MUX1_effectMix 5
#define MUX1_ampRelease 6
#define MUX1_amDepth 7

//Mux 2 Connections
#define MUX2_filterSustain 0
#define MUX2_filterDecay 1
#define MUX2_filterAttack 2
#define MUX2_filterRelease 3
#define MUX2_Resonance 4
#define MUX2_keyTrack 5 // spare mux output - decouple from DAC
#define MUX2_filterEGlevel 6
#define MUX2_spare7 7 // spare mux output

//Mux 3 Connections
#define MUX3_spare0 0
#define MUX3_tmDepth 1
#define MUX3_filterCutoff 2
#define MUX3_spare3 3
#define MUX3_osc1Level 4
#define MUX3_spare5 5
#define MUX3_osc2Level 6
#define MUX3_effect3 7

//Mux 4 Connections
#define MUX4_spare0 0
#define MUX4_effect2 1
#define MUX4_osc2fmDepth 2
#define MUX4_spare3 3
#define MUX4_osc1fmDepth 4
#define MUX4_effect1 5
#define MUX4_osc1ModDepth 6
#define MUX4_osc2ModDepth 7

//Switches 
//Mux 5 Connections
#define MUX5_lfoDelay 0
#define MUX5_noiseLevel 1
#define MUX5_glideTime 2
#define MUX5_lfoRate 3
#define MUX5_osc1Freq 4
#define MUX5_osc2Mod 5 // spare mux output - decouple from DAC
#define MUX5_osc1Mod 6
#define MUX5_osc2Freq 7 // spare mux output

// New 595 outputs

#define FILTER_LIN_LOG 4
#define AMP_LIN_LOG 5
#define FLOOPBIT1 6
#define FLOOPBIT0 7

#define NOTEPRIORITYA0 8
#define NOTEPRIORITYA2 9
#define ALOOPBIT1 10
#define ALOOPBIT0 11
#define EXTCLOCK 12
#define MIDICLOCK 13
#define AFTERTOUCH_A 14
#define AFTERTOUCH_B 15

#define AFTERTOUCH_C 16
#define FILTER_POLE 17
#define FILTER_EG_INV 18
#define LFO_ALT 19
#define OSC1_OCTA 20  //3.3v
#define OSC1_OCTB 21  //3.3v
#define OSC2_OCTA 22  //3.3v
#define OSC2_OCTB 23  //3.3v

#define OSC1_BANKA 24  //3.3v
#define OSC1_BANKB 25  //3.3v
#define OSC2_BANKA 26  //3.3v
#define OSC2_BANKB 27  //3.3v
#define FILTER_A 28
#define FILTER_B 29
#define FILTER_C 30
//#define SPARE 31

// Panel Buttons

#define EFFECT_BANK_SW 0
#define FILTER_POLE_SW 1
#define FILTER_LOOP_SW 2
#define EG_INVERT_SW 3
#define FILTER_VELOCITY_SW 4
#define FILTER_TYPE_SW 5

#define LFO_WAVE_SW 8
#define LFO_ALT_SW 9
#define LFO_MULT_SW 10
#define GLIDE_SW 11
#define VCA_GATE_SW 12
#define VCA_LOOP_SW 13
#define VCA_VELOCITY_SW 14
#define VCA_LINLOG_SW 15

#define DCO1_OCT_SW 16
#define DCO1_MODE_SW 17
#define DCO1_WAVE_SW 18
#define DCO2_OCT_SW 19
#define DCO2_MODE_SW 20
#define DCO2_WAVE_SW 21
#define FILTER_LINLOG_SW 22

// Panel LEDS
// 1
#define FILTER_VELOCITY_LED 0
#define EG_INV_LED 1
#define FILTER_LOOP_GREEN_LED 2
#define FILTER_LOOP_RED_LED 3
#define FILTER_POLE_GREEN_LED 4
#define FILTER_POLE_RED_LED 5
#define EFFECT_BANK_GREEN_LED 6
#define EFFECT_BANK_RED_LED 7

//2
#define VCA_VELOCITY_LED 8
#define VCA_LOOP_GREEN_LED 9
#define VCA_LOOP_RED_LED 10
#define VCA_GATE_LED 11
#define GLIDE_LED 12

//3
#define LFO_MULT_GREEN_LED 16
#define LFO_MULT_RED_LED 17
#define LFO_ALT_GREEN_LED 18
#define LFO_ALT_RED_LED 19
#define VCA_LINLOG_GREEN_LED 20
#define VCA_LINLOG_RED_LED 21
#define FILTER_LINLOG_GREEN_LED 22
#define FILTER_LINLOG_RED_LED 23

//4
#define DCO1_MODE_GREEN_LED 24
#define DCO1_MODE_RED_LED 25
#define DCO2_MODE_GREEN_LED 26
#define DCO2_MODE_RED_LED 27
#define DCO1_OCT_GREEN_LED 28
#define DCO1_OCT_RED_LED 29
#define DCO2_OCT_GREEN_LED 30
#define DCO2_OCT_RED_LED 31


//Teensy 4.1 Pins

#define RECALL_SW 17
#define SAVE_SW 41
#define SETTINGS_SW 28
#define BACK_SW 20

#define ENCODER_PINA 4
#define ENCODER_PINB 5

#define MUXCHANNELS 8
#define QUANTISE_FACTOR 31

#define DEBOUNCE 30

static byte muxInput = 0;

static int mux1ValuesPrev[MUXCHANNELS] = {};
static int mux2ValuesPrev[MUXCHANNELS] = {};
static int mux3ValuesPrev[MUXCHANNELS] = {};
static int mux4ValuesPrev[MUXCHANNELS] = {};
static int mux5ValuesPrev[MUXCHANNELS] = {};

static int mux1Read = 0;
static int mux2Read = 0;
static int mux3Read = 0;
static int mux4Read = 0;
static int mux5Read = 0;
static int mux1ReadMIDI = 0;
static int mux2ReadMIDI = 0;
static int mux3ReadMIDI = 0;
static int mux4ReadMIDI = 0;
static int mux5ReadMIDI = 0;

static long encPrevious = 0;

//These are pushbuttons and require debouncing

TButton saveButton{ SAVE_SW, LOW, HOLD_DURATION, DEBOUNCE, CLICK_DURATION };
TButton settingsButton{ SETTINGS_SW, LOW, HOLD_DURATION, DEBOUNCE, CLICK_DURATION };
TButton backButton{ BACK_SW, LOW, HOLD_DURATION, DEBOUNCE, CLICK_DURATION };
TButton recallButton{ RECALL_SW, LOW, HOLD_DURATION, DEBOUNCE, CLICK_DURATION };  //On encoder

Encoder encoder(ENCODER_PINB, ENCODER_PINA);  //This often needs the pins swapping depending on the encoder

void setupHardware() {
  //Volume Pot is on ADC0
  adc->adc0->setAveraging(32);                                          // set number of averages 0, 4, 8, 16 or 32.
  adc->adc0->setResolution(12);                                         // set bits of resolution  8, 10, 12 or 16 bits.
  adc->adc0->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_LOW_SPEED);  // change the conversion speed
  adc->adc0->setSamplingSpeed(ADC_SAMPLING_SPEED::MED_SPEED);           // change the sampling speed

  //MUXs on ADC1
  adc->adc1->setAveraging(32);                                          // set number of averages 0, 4, 8, 16 or 32.
  adc->adc1->setResolution(12);                                         // set bits of resolution  8, 10, 12 or 16 bits.
  adc->adc1->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_LOW_SPEED);  // change the conversion speed
  adc->adc1->setSamplingSpeed(ADC_SAMPLING_SPEED::MED_SPEED);           // change the sampling speed

  //Mux address pins

  pinMode(MUX_0, OUTPUT);
  pinMode(MUX_1, OUTPUT);
  pinMode(MUX_2, OUTPUT);

  digitalWrite(MUX_0, LOW);
  digitalWrite(MUX_1, LOW);
  digitalWrite(MUX_2, LOW);

  pinMode(DAC_CS1, OUTPUT);
  digitalWrite(DAC_CS1, HIGH);
  pinMode(DAC_CS2, OUTPUT);
  digitalWrite(DAC_CS2, HIGH);
  pinMode(DAC_CS3, OUTPUT);
  digitalWrite(DAC_CS3, HIGH);

  //Mux ADC
  pinMode(MUX1_S, INPUT_DISABLE);
  pinMode(MUX2_S, INPUT_DISABLE);
  pinMode(MUX3_S, INPUT_DISABLE);
  pinMode(MUX4_S, INPUT_DISABLE);
  pinMode(MUX5_S, INPUT_DISABLE);

  //Switches
  pinMode(RECALL_SW, INPUT_PULLUP);  //On encoder
  pinMode(SAVE_SW, INPUT_PULLUP);
  pinMode(SETTINGS_SW, INPUT_PULLUP);
  pinMode(BACK_SW, INPUT_PULLUP);
}

