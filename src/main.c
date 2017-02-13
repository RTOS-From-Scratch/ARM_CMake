/*
* Description : Dummy file - red led is HIGH
* Usage	      : using for purpose of testing
* Author	  : Baron Leonardo <mohamedayman.fcis@zoho.com>
* License	  : Copyright (C) 2016 RTOS From Scratch
*
*
*	This program is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "led.h"
#include "tm4c123gh6pm.h"

int main()
{
    LedRed_init();

    while(1)
    {
        LedRed_HIGH();
    }

    return 0;
}
