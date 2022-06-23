/*
   Copyright 2021 FogML
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifdef ARDUINO

#include "fogml_ports.h"

int fogml_random(int min, int max) {
    return random(min, max);
}

void fogml_printf(char const *str) { Serial.print(str); };
void fogml_printf_float(float number) { Serial.print(number); };
void fogml_printf_int(int number) { Serial.print(number); };

#endif
