// watchX Arduino Code
#include "watchX.h"

int length2;
int LengthSin;
int radius;
int XCenter;
int amplitude;
int xCrossLine;
int frame;
int range;
int speed;
int width;
int height;
int octave;
int frequence;
int padCound;
int mode;
int diameter;
int space;
int YCenter;
int Xsin;
int Ysin;
int Xpoint;
int Ypoint;
int i;
wx_oled_t oled;
wx_input_t input;
wx_tone_t btone;

// Describe this function...
void set_variable() {
	range = 360;
	frame = 1;
	speed = 3;
	width = 128;
	height = 64;
	octave = 440;
	frequence = 2;
	padCound = 1;
	mode = 1;
	diameter = 35;
	space = 2;
	xCrossLine = diameter + space;
	radius = float(diameter) / space;
	amplitude = radius;
	XCenter = radius + 1;
	YCenter = float(height) / 2;
	Xsin = diameter + space;
	Ysin = YCenter;
	length2 = ((width - 1) - diameter) - space;
	LengthSin = float((range * frequence)) / length2;
	Xpoint = diameter + 1;
	Ypoint = YCenter;
}

// Describe this function...
void SetPad() {
	wx_write_text_line(&oled, 0, 2, ((String)"Frequency").c_str());
	wx_write_text_line(&oled, 1, 2, ((String)frequence).c_str());
	wx_write_text_line(&oled, 0, 0, ((String)"Tone").c_str());
	wx_write_text_line(&oled, 1, 0, ((String)(octave * frequence)).c_str());
	wx_write_text_line(&oled, 2, 2, ((String)"Octave").c_str());
	wx_write_text_line(&oled, 3, 2, ((String)octave).c_str());
	wx_write_text_line(&oled, 2, 0, ((String)"Diameter").c_str());
	wx_write_text_line(&oled, 3, 0, ((String)diameter).c_str());
	wx_write_text_line(&oled, 4, 2, ((String)"Speed").c_str());
	wx_write_text_line(&oled, 5, 2, ((String)speed).c_str());
	if (wx_get_input(&input, KEY_B_DOWN)) {
		padCound = padCound + 1;
		if (padCound > 2) {
			padCound = 3;
		}
	}
	if (wx_get_input(&input, KEY_B_UP)) {
		padCound = padCound - 1;
		if (padCound < 2) {
			padCound = 1;
		}
	}
	if (padCound == 1) {
		wx_write_text_line(&oled, 0, 1, ((String)"X").c_str());
		if (wx_get_input(&input, KEY_B_RIGHT)) {
			frequence = frequence + 1;
			if (frequence >= 5) {
				frequence = 5;
			}
		}
		if (wx_get_input(&input, KEY_B_LEFT)) {
			frequence = frequence - 1;
			if (frequence <= 1) {
				frequence = 1;
			}
		}
	} else {
		if (padCound == 2) {
			wx_write_text_line(&oled, 2, 1, ((String)"X").c_str());
			if (wx_get_input(&input, KEY_B_RIGHT)) {
				octave = octave * 2;
				diameter = diameter + 5;
				if (octave >= 1760) {
					octave = 1760;
				}
				if (diameter >= 50) {
					diameter = 50;
				}
			}
			if (wx_get_input(&input, KEY_B_LEFT)) {
				octave = float(octave) / 2;
				diameter = diameter - 5;
				if (octave <= 55) {
					octave = 55;
				}
				if (diameter <= 20) {
					diameter = 20;
				}
			}
		} else {
			if (padCound == 3) {
				wx_write_text_line(&oled, 4, 1, ((String)"X").c_str());
				if (wx_get_input(&input, KEY_B_RIGHT)) {
					speed = speed + 1;
					if (speed > 3) {
						speed = 1;
					}
				}
				if (wx_get_input(&input, KEY_B_LEFT)) {
					speed = speed - 1;
					if (speed < 1) {
						speed = 3;
					}
				}
			}
		}
	}
}

// Describe this function...
void drawBackGround() {
	wx_draw_line(&oled, xCrossLine, 0, xCrossLine, (height - 1));
	wx_draw_line(&oled, 0, YCenter, (width - 1), YCenter);
	wx_draw_line(&oled, XCenter, (float((height - diameter)) / 2), XCenter, (float((height - diameter)) / 2 + diameter));
	int i_end = range * frequence;
	int i_inc = abs(speed + 1);
	if (1 > i_end) {
		i_inc = -i_inc;
	}
	for (i = 1;
	     i_inc >= 0 ? i <= i_end : i >= i_end;
	     i += i_inc) {
		wx_draw_pixel(&oled, (XCenter + cos(((360 - i)) * (M_PI / 180)) * radius), (YCenter + sin(((360 - i)) * (M_PI / 180)) * radius));
		wx_draw_pixel(&oled, (xCrossLine + float(i) / LengthSin), (YCenter - sin((i) * (M_PI / 180)) * radius));
		if (!digitalRead(1)) {
			break;
		}
	}
}

// Part that is refreshed at each frame
void drawFrame() {
	Xpoint = XCenter + cos(((360 - frame)) * (M_PI / 180)) * radius;
	Ypoint = YCenter + sin(((360 - frame)) * (M_PI / 180)) * radius;
	Xsin = xCrossLine + float(frame) / LengthSin;
	Ysin = YCenter - sin((frame) * (M_PI / 180)) * radius;
	wx_draw_line(&oled, XCenter, YCenter, Xpoint, Ypoint);
	wx_draw_line(&oled, XCenter, Ypoint, Xpoint, Ypoint);
	wx_draw_line(&oled, Xpoint, YCenter, Xpoint, Ypoint);
	wx_draw_line(&oled, Xpoint, Ypoint, Xsin, Ysin);
	wx_draw_line(&oled, Xsin, YCenter, Xsin, Ysin);
	wx_draw_pixel(&oled, Xpoint, Ypoint);
	wx_draw_pixel(&oled, Xsin, Ysin);
}

// Describe this function...
void sound() {
	if (!digitalRead(8)) {
		wx_play_tone(&btone, (octave * frequence));
	} else {
		wx_stop_tone(&btone);
	}
}

void update_env() {
	wx_oled_update(&oled);
	wx_update_input(&input);
}

void setup() {
	set_variable();
	pinMode(1, INPUT_PULLUP);
	SPI.begin();
	wx_oled_init(&oled);
	wx_init_input(&input, true);
	pinMode(8, INPUT_PULLUP);
	wx_init_tone(&btone, 60, BUILD_BUZZER);
}

void loop() {
	length2 = ((width - 1) - diameter) - space;
	LengthSin = float((range * frequence)) / length2;
	radius = float(diameter) / space;
	XCenter = radius + 1;
	amplitude = radius;
	xCrossLine = diameter + space;
	if (!digitalRead(1)) {
		SetPad();
	} else {
		int frame_end = range * frequence;
		int frame_inc = abs(speed + 1);
		if (1 > frame_end) {
			frame_inc = -frame_inc;
		}
		for (frame = 1;
		     frame_inc >= 0 ? frame <= frame_end : frame >= frame_end;
		     frame += frame_inc) {
			sound();
			drawBackGround();
			drawFrame();
			wx_delay((float(27) / pow( 3, speed )));
			if (!digitalRead(1)) {
				break;
			}
		}
	}
	update_env();
}
