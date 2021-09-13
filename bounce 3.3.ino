// watchX Arduino Code
#include "watchX.h"

float Gravity_X;
float Gravity_Y;
float Obj1_Elasticity;
float Obj1_Friction;
float Obj1_X_Position;
float Obj1_Y_Position;
float Obj1_X_Velocity;
float Obj1_Y_Velocity;
int pad_count;
float acceleration;
int Obj1_Size;
int Count_Obj;
float Obj2_Elasticity;
float Obj2_Friction;
int Obj2_Size;
float Obj2_X_Position;
float Obj2_Y_Position;
float Obj2_X_Velocity;
float Obj2_Y_Velocity;
int select_Gravity;
int i;
int j;
int Obj1_X_Acceleration;
int Obj1_Y_Acceleration;
int Obj2_X_Acceleration;
int Obj2_Y_Acceleration;
wx_oled_t oled;
wx_mpu_t mpu;

int mathRandomInt(int min, int max) {
  if (min > max) {
    // Swap min and max to ensure min is smaller.
    int temp = min;
    min = max;
    max = temp;
  }
  return min + (rand() % (max - min + 1));
}

// Describe this function...
void set_variables() {
	Gravity_X = 9.9;
	Gravity_Y = 9.9;
	Obj1_Elasticity = 0.9;
	Obj1_Friction = 0.999;
	Obj1_X_Position = 0.5 + mathRandomInt(2, 127);
	Obj1_Y_Position = 0.5 + mathRandomInt(2, 63);
	Obj1_X_Velocity = 0.5 + mathRandomInt(2, 10);
	Obj1_Y_Velocity = 0.5 + mathRandomInt(2, 10);
	pad_count = 1;
	acceleration = 0.3;
	Obj1_Size = 2;
	Count_Obj = 2;
	Obj2_Elasticity = 0.9;
	Obj2_Friction = 0.999;
	Obj2_Size = 3;
	Obj2_X_Position = 0.5 + mathRandomInt(2, 127);
	Obj2_Y_Position = 0.5 + mathRandomInt(2, 63);
	Obj2_X_Velocity = 0.5 + mathRandomInt(2, 10);
	Obj2_Y_Velocity = 0.5 + mathRandomInt(2, 10);
	select_Gravity = 2;
}

// Describe this function...
void randomize() {
	if (!digitalRead(8)) {
		Obj1_X_Position = mathRandomInt(2, 127) - 0.5;
		Obj1_Y_Position = mathRandomInt(2, 63) - 0.5;
		Obj1_X_Velocity = mathRandomInt(2, 10) - 0.5;
		Obj1_Y_Velocity = mathRandomInt(2, 10) - 0.5;
	}
}

// Describe this function...
void randomize2() {
	if (!digitalRead(8)) {
		Obj1_X_Position = mathRandomInt(2, 127) - 0.5;
		Obj1_Y_Position = mathRandomInt(2, 63) - 0.5;
		Obj1_X_Velocity = mathRandomInt(2, 10) - 0.5;
		Obj1_Y_Velocity = mathRandomInt(2, 10) - 0.5;
		Obj2_X_Position = mathRandomInt(2, 127) - 0.5;
		Obj2_Y_Position = mathRandomInt(2, 63) - 0.5;
		Obj2_X_Velocity = mathRandomInt(2, 10) - 0.5;
		Obj2_Y_Velocity = mathRandomInt(2, 10) - 0.5;
	}
}

// Describe this function...
void pad() {
	if (!digitalRead(4)) {
		if (pad_count <= 8) {
			pad_count = pad_count + 1;
		} else {
			pad_count = 9;
		}
		wx_delay(50);
	}
	if (!digitalRead(A0)) {
		if (pad_count >= 1) {
			pad_count = pad_count - 1;
		} else {
			pad_count = 0;
		}
		wx_delay(50);
	}
	if (pad_count == 1) {
		wx_write_text_line(&oled, 0, 0, ((String)".").c_str());
		wx_write_text_line(&oled, 0, 2, ((String)".").c_str());
	} else {
		if (pad_count == 2) {
			wx_write_text_line(&oled, 1, 0, ((String)".").c_str());
			wx_write_text_line(&oled, 1, 2, ((String)".").c_str());
		} else {
			if (pad_count == 3) {
				wx_write_text_line(&oled, 2, 0, ((String)".").c_str());
				wx_write_text_line(&oled, 2, 2, ((String)".").c_str());
			} else {
				if (pad_count == 4) {
					wx_write_text_line(&oled, 4, 0, ((String)".").c_str());
				} else {
					if (pad_count == 5) {
						wx_write_text_line(&oled, 4, 2, ((String)".").c_str());
					} else {
						if (pad_count == 6) {
							wx_write_text_line(&oled, 5, 0, ((String)".").c_str());
						} else {
							if (pad_count == 7) {
								wx_write_text_line(&oled, 5, 2, ((String)".").c_str());
							} else {
								if (pad_count == 8) {
									wx_write_text_line(&oled, 6, 0, ((String)".").c_str());
								} else {
									if (pad_count == 9) {
										wx_write_text_line(&oled, 6, 2, ((String)".").c_str());
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if (pad_count == 1) {
		if (!digitalRead(10)) {
			Count_Obj = 2;
		}
		if (!digitalRead(11)) {
			Count_Obj = 1;
		}
	} else {
		if (pad_count == 2) {
			if (!digitalRead(10)) {
				acceleration = acceleration + 0.01;
			}
			if (!digitalRead(11)) {
				acceleration = acceleration - 0.01;
			}
			if (acceleration <= 0.001) {
				acceleration = 0.001;
			}
			if (acceleration >= 1) {
				acceleration = 1;
			}
		} else {
			if (pad_count == 3) {
				if (!digitalRead(11)) {
					select_Gravity = 1;
				}
				if (!digitalRead(10)) {
					select_Gravity = 2;
				}
			} else {
				if (pad_count == 4) {
					if (!digitalRead(10)) {
						Obj1_Size = Obj1_Size + 1;
					}
					if (!digitalRead(11)) {
						Obj1_Size = Obj1_Size - 1;
					}
					if (Obj1_Size <= 1) {
						Obj1_Size = 1;
					}
					if (Obj1_Size >= 10) {
						Obj1_Size = 10;
					}
				} else {
					if (pad_count == 5) {
						if (!digitalRead(10)) {
							Obj2_Size = Obj2_Size + 1;
						}
						if (!digitalRead(11)) {
							Obj2_Size = Obj2_Size - 1;
						}
						if (Obj2_Size <= 1) {
							Obj2_Size = 1;
						}
						if (Obj2_Size >= 10) {
							Obj2_Size = 10;
						}
					} else {
						if (pad_count == 6) {
							if (!digitalRead(10)) {
								Obj1_Elasticity = Obj1_Elasticity + 0.05;
							}
							if (!digitalRead(11)) {
								Obj1_Elasticity = Obj1_Elasticity - 0.05;
							}
							if (Obj1_Elasticity <= 0.1) {
								Obj1_Elasticity = 0.1;
							}
							if (Obj1_Elasticity >= 1.9) {
								Obj1_Elasticity = 1.9;
							}
						} else {
							if (pad_count == 7) {
								if (!digitalRead(10)) {
									Obj2_Elasticity = Obj2_Elasticity + 0.05;
								}
								if (!digitalRead(11)) {
									Obj2_Elasticity = Obj2_Elasticity - 0.05;
								}
								if (Obj2_Elasticity <= 0.1) {
									Obj2_Elasticity = 0.1;
								}
								if (Obj2_Elasticity >= 1.9) {
									Obj2_Elasticity = 1.9;
								}
							} else {
								if (pad_count == 8) {
									if (!digitalRead(10)) {
										Obj1_Friction = Obj1_Friction + 0.0005;
									}
									if (!digitalRead(11)) {
										Obj1_Friction = Obj1_Friction - 0.0005;
									}
									if (Obj1_Friction <= 0.9) {
										Obj1_Friction = 0.9;
									}
									if (Obj1_Friction >= 1) {
										Obj1_Friction = 1;
									}
								} else {
									if (pad_count == 9) {
										if (!digitalRead(10)) {
											Obj2_Friction = Obj2_Friction + 0.0005;
										}
										if (!digitalRead(11)) {
											Obj2_Friction = Obj2_Friction - 0.0005;
										}
										if (Obj2_Friction <= 0.9) {
											Obj2_Friction = 0.9;
										}
										if (Obj2_Friction >= 1) {
											Obj2_Friction = 1;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	wx_write_text_line(&oled, 0, 1, ((String)(String("# Objects : ") + String(Count_Obj))).c_str());
	wx_write_text_line(&oled, 1, 1, ((String)(String("acceleration : ") + String(acceleration))).c_str());
	if (select_Gravity == 1) {
		wx_write_text_line(&oled, 2, 1, ((String)"gravity fix").c_str());
		wx_write_text_line(&oled, 2, 2, ((String)(Gravity_Y * acceleration)).c_str());
	} else {
		wx_write_text_line(&oled, 2, 1, ((String)"acceleromet").c_str());
		wx_write_text_line(&oled, 2, 2, ((String)(wx_mpu_get_value(&mpu, WX_MPU_ACCEL_Y) * acceleration)).c_str());
	}
	wx_write_text_line(&oled, 3, 0, ((String)"\\/ Obj 1").c_str());
	wx_write_text_line(&oled, 3, 2, ((String)"Obj 2 \\/").c_str());
	wx_write_text_line(&oled, 4, 0, ((String)Obj1_Size).c_str());
	wx_write_text_line(&oled, 4, 1, ((String)" : Size : ").c_str());
	wx_write_text_line(&oled, 4, 2, ((String)Obj2_Size).c_str());
	wx_write_text_line(&oled, 5, 0, ((String)(Obj1_Elasticity * 100)).c_str());
	wx_write_text_line(&oled, 5, 1, ((String)" : elast : ").c_str());
	wx_write_text_line(&oled, 5, 2, ((String)(Obj2_Elasticity * 100)).c_str());
	wx_write_text_line(&oled, 6, 0, ((String)(Obj1_Friction * 100)).c_str());
	wx_write_text_line(&oled, 6, 1, ((String)" : Frict : ").c_str());
	wx_write_text_line(&oled, 6, 2, ((String)(Obj2_Friction * 100)).c_str());
}

// Describe this function...
void draw() {
	wx_draw_pixel(&oled, (round(Obj1_X_Position) + 0), (round(Obj1_Y_Position) + 0));
	int i_inc = 1;
	if (1 > Obj1_Size) {
		i_inc = -i_inc;
	}
	for (i = 1;
	     i_inc >= 0 ? i <= Obj1_Size : i >= Obj1_Size;
	     i += i_inc) {
		wx_draw_pixel(&oled, (round(Obj1_X_Position) + i), (round(Obj1_Y_Position) + 0));
		wx_draw_pixel(&oled, (round(Obj1_X_Position) - i), (round(Obj1_Y_Position) + 0));
		wx_draw_pixel(&oled, (round(Obj1_X_Position) + 0), (round(Obj1_Y_Position) + i));
		wx_draw_pixel(&oled, (round(Obj1_X_Position) + 0), (round(Obj1_Y_Position) - i));
		wx_draw_pixel(&oled, (round(Obj1_X_Position) + i), (round(Obj1_Y_Position) + i));
		wx_draw_pixel(&oled, (round(Obj1_X_Position) - i), (round(Obj1_Y_Position) - i));
		wx_draw_pixel(&oled, (round(Obj1_X_Position) + i), (round(Obj1_Y_Position) - i));
		wx_draw_pixel(&oled, (round(Obj1_X_Position) - i), (round(Obj1_Y_Position) + i));
	}
}

// Describe this function...
void draw2() {
	wx_draw_pixel(&oled, (round(Obj2_X_Position) + 0), (round(Obj2_Y_Position) + 0));
	int j_inc = 1;
	if (1 > Obj2_Size) {
		j_inc = -j_inc;
	}
	for (j = 1;
	     j_inc >= 0 ? j <= Obj2_Size : j >= Obj2_Size;
	     j += j_inc) {
		wx_draw_pixel(&oled, (round(Obj2_X_Position) + j), (round(Obj2_Y_Position) + 0));
		wx_draw_pixel(&oled, (round(Obj2_X_Position) - j), (round(Obj2_Y_Position) + 0));
		wx_draw_pixel(&oled, (round(Obj2_X_Position) + 0), (round(Obj2_Y_Position) + j));
		wx_draw_pixel(&oled, (round(Obj2_X_Position) + 0), (round(Obj2_Y_Position) - j));
	}
}

// Describe this function...
void calculate_position() {
	if (select_Gravity == 2) {
		Obj1_X_Acceleration = wx_mpu_get_value(&mpu, WX_MPU_ACCEL_Y) * acceleration;
		Obj1_Y_Acceleration = wx_mpu_get_value(&mpu, WX_MPU_ACCEL_X) * acceleration;
	} else {
		if (select_Gravity == 1) {
			Obj1_X_Acceleration = Gravity_X * acceleration;
			Obj1_Y_Acceleration = Gravity_Y * acceleration;
		}
	}
	Obj1_X_Velocity = Obj1_X_Velocity + Obj1_X_Acceleration;
	Obj1_X_Velocity = Obj1_X_Velocity * Obj1_Friction;
	Obj1_X_Position = Obj1_X_Position + Obj1_X_Velocity;
	Obj1_Y_Velocity = Obj1_Y_Velocity + Obj1_Y_Acceleration;
	Obj1_Y_Velocity = Obj1_Y_Velocity * Obj1_Friction;
	Obj1_Y_Position = Obj1_Y_Position + Obj1_Y_Velocity;
}

// Describe this function...
void calculate_position2() {
	if (select_Gravity == 2) {
		Obj2_X_Acceleration = wx_mpu_get_value(&mpu, WX_MPU_ACCEL_Y) * acceleration;
		Obj2_Y_Acceleration = wx_mpu_get_value(&mpu, WX_MPU_ACCEL_X) * acceleration;
	} else {
		if (select_Gravity == 1) {
			Obj2_X_Acceleration = Gravity_X * acceleration;
			Obj2_Y_Acceleration = Gravity_Y * acceleration;
		}
	}
	Obj2_X_Velocity = Obj2_X_Velocity + Obj2_X_Acceleration;
	Obj2_X_Velocity = Obj2_X_Velocity * Obj2_Friction;
	Obj2_X_Position = Obj2_X_Position + Obj2_X_Velocity;
	Obj2_Y_Velocity = Obj2_Y_Velocity + Obj2_Y_Acceleration;
	Obj2_Y_Velocity = Obj2_Y_Velocity * Obj2_Friction;
	Obj2_Y_Position = Obj2_Y_Position + Obj2_Y_Velocity;
}

// Describe this function...
void calculate_collision() {
	if (Obj1_Y_Position + Obj1_Size > 63) {
		Obj1_Y_Position = 62 - Obj1_Size;
		Obj1_Y_Velocity = (-1 * Obj1_Y_Velocity) * Obj1_Elasticity;
		Obj1_Y_Acceleration = 0;
	}
	if (Obj1_Y_Position - Obj1_Size < 0) {
		Obj1_Y_Position = 1 + Obj1_Size;
		Obj1_Y_Velocity = (-1 * Obj1_Y_Velocity) * Obj1_Elasticity;
		Obj1_Y_Acceleration = 0;
	}
	if (Obj1_X_Position + Obj1_Size > 127) {
		Obj1_X_Position = 126 - Obj1_Size;
		Obj1_X_Velocity = (-1 * Obj1_X_Velocity) * Obj1_Elasticity;
		Obj1_X_Acceleration = 0;
	}
	if (Obj1_X_Position - Obj1_Size < 0) {
		Obj1_X_Position = 1 + Obj1_Size;
		Obj1_X_Velocity = (-1 * Obj1_X_Velocity) * Obj1_Elasticity;
		Obj1_X_Acceleration = 0;
	}
}

// Describe this function...
void calculate_collision2() {
	if (Obj2_Y_Position + Obj2_Size > 63) {
		Obj2_Y_Position = 62 - Obj2_Size;
		Obj2_Y_Velocity = (-1 * Obj2_Y_Velocity) * Obj2_Elasticity;
		Obj2_Y_Acceleration = 0;
	}
	if (Obj2_Y_Position - Obj2_Size < 0) {
		Obj2_Y_Position = 1 + Obj2_Size;
		Obj2_Y_Velocity = (-1 * Obj2_Y_Velocity) * Obj2_Elasticity;
		Obj2_Y_Acceleration = 0;
	}
	if (Obj2_X_Position + Obj2_Size > 127) {
		Obj2_X_Position = 126 - Obj2_Size;
		Obj2_X_Velocity = (-1 * Obj2_X_Velocity) * Obj2_Elasticity;
		Obj2_X_Acceleration = 0;
	}
	if (Obj2_X_Position - Obj2_Size < 0) {
		Obj2_X_Position = 1 + Obj2_Size;
		Obj2_X_Velocity = (-1 * Obj2_X_Velocity) * Obj2_Elasticity;
		Obj2_X_Acceleration = 0;
	}
}

// Describe this function...
void my_2_collision() {
	if (Count_Obj == 2) {
		if ((Obj1_X_Position - Obj2_X_Position <= (Obj2_Size - Obj1_Size > 0 ? Obj2_Size : Obj1_Size) && Obj1_X_Position - Obj2_X_Position >= (Obj2_Size - Obj1_Size > 0 ? Obj2_Size : Obj1_Size) * -1) && (Obj1_Y_Position - Obj2_Y_Position <= (Obj2_Size - Obj1_Size > 0 ? Obj2_Size : Obj1_Size) && Obj1_Y_Position - Obj2_Y_Position >= (Obj2_Size - Obj1_Size > 0 ? Obj2_Size : Obj1_Size) * -1)) {
			Obj1_X_Velocity = (-1 * Obj1_X_Velocity) * Obj1_Elasticity;
			Obj2_X_Velocity = (-1 * Obj2_X_Velocity) * Obj2_Elasticity;
			Obj1_Y_Velocity = (-1 * Obj1_Y_Velocity) * Obj1_Elasticity;
			Obj2_Y_Velocity = (-1 * Obj2_Y_Velocity) * Obj2_Elasticity;
		}
	}
}

void update_env() {
	wx_oled_update(&oled);
	wx_mpu_update(&mpu);
}

void setup() {
	set_variables();
	pinMode(8, INPUT_PULLUP);
	pinMode(1, INPUT_PULLUP);
	pinMode(4, INPUT_PULLUP);
	pinMode(A0, INPUT_PULLUP);
	SPI.begin();
	wx_oled_init(&oled);
	pinMode(10, INPUT_PULLUP);
	pinMode(11, INPUT_PULLUP);
	wx_mpu_init(&mpu);
}

void loop() {
	if (!digitalRead(1)) {
		pad();
	} else {
		calculate_position();
		calculate_collision();
		randomize();
		draw();
		if (Count_Obj == 2) {
			calculate_position2();
			calculate_collision2();
			my_2_collision();
			randomize2();
			draw2();
		}
	}
	wx_delay(20);
	update_env();
}
