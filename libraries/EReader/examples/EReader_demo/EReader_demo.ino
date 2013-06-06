// Copyright 2013 WyoLum, LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at:
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
// express or implied.  See the License for the specific language
// governing permissions and limitations under the License.

#include <inttypes.h>
#include <ctype.h>

#include <SPI.h>
#include <SD.h>
#include "EPD.h"
#include "S5813A.h"
#include "EReader.h"

uint16_t UNICODE_MSG[11] = {25105, 20204, 29233, 30717, 36882, 31185, 25216, 0};

// I/O setup
void setup() {
  Serial.begin(115200);
  Serial.println("WyoLum, LLC 2013");
  Serial.println("Buy Open Source!!");
  Serial.print("SD Chip Select PIN: ");
  Serial.println(SD_CS, DEC);
  Serial.print("Temp count ");
  Serial.println(digitalRead(EPD_TEMPERATURE), DEC);
  Serial.print("Temp ");
  Serial.println(getTemp(), DEC);
  
  ereader.setup(EPD_2_7);
}


// main loop
unsigned long int loop_count = 0;

void loop() {
  if(loop_count % 4 == 0){
    ereader.display_wif("/IMAGES/SEEED.WIF", 0, 0);
  }
  else if(loop_count % 4 == 1){
    ereader.display_wif("/IMAGES/WYOLUM.WIF", 0, 0);
    ereader.put_unicode(30, 40, UNICODE_MSG, true);
  }
  else if(loop_count % 4 == 2){
    ereader.display_wif("/IMAGES/LENA.WIF", 0, 0);
  }
  else{
    ereader.display_wif("/IMAGES/AANDJ.WIF", -264 / 2,  176 / 2);
    ereader.display_wif("/IMAGES/AANDJ.WIF",  264 / 2, -176 / 2);
    ereader.display_wif("/IMAGES/CAT_SM.WIF", 264 / 2, 176 / 2);
    ereader.display_wif("/IMAGES/APHRODIT.WIF", 0, 0);
    ereader.toggle_ellipse(random(0, 264), random(0, 176), 20, 20);
    ereader.put_ascii(random(0, 200), random(16, 150), "WyoLum ROCKS!!", true);
    for(uint8_t yy=0; yy < 6; yy++){
      ereader.setpix(128, yy, true); // draw some pixels
    }
    ereader.put_unicode(10, 140, UNICODE_MSG, true);
    ereader.toggle_line(70, 0, 120, 50);
  }
  loop_count++;
  ereader.show();
  ereader.sleep(4000); // allows EPD to power off gracefully
}

