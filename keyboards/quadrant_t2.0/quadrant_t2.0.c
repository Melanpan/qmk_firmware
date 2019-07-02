/* Copyright 2019 Ealdin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "quadrant_t2.0.h"

void quadrant_led_on() {
  writePinLow(D4);
}

void quadrant_led_off() {
  writePinHigh(D4);
}

void keyboard_pre_init_kb(void) {
  // Initialize Caps Lock LED
  setPinOutput(D4);
  keyboard_pre_init_user();
}
