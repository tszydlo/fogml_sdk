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

#if defined(__ZEPHYR__)

#include "fogml_ports.h"

int fogml_random(int min, int max)
{
    return (sys_rand32_get() % (max - min)) + min;
}

void fogml_printf(char const *str)
{
    printk("%s", str);
};

void fogml_printf_float(float number)
{
    printk("%.2f", number);
};

void fogml_printf_int(int number)
{
    printk("%d", number);
};

#endif
