/*
 TiLDA Mk2

 RadioTransmitTask

 The MIT License (MIT)

 Copyright (c) 2014 Electromagnetic Field LTD

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include <FreeRTOS_ARM.h>

#include "RadioTransmitTask.h"
#include "DebugTask.h"

RadioTransmitTask::RadioTransmitTask(RadioReceiveTask& aRadioRecieveTask)
	:mRadioReceiveTask(aRadioRecieveTask)
{
}

String RadioTransmitTask::getName() const {
	return "RadioTransmitTask";
}

void RadioTransmitTask::transmit() {
	if( mQueue == 0 ) {
		debug::log("RadioTransmitTask: incomingMessages queue has not been created");
	} else {
		if(xQueueSendToBack(mQueue, NULL, (TickType_t) 0) != pdPASS) {
	        debug::log("RadioTransmitTask: Could not queue incoming message");
	    }
	}
}

void RadioTransmitTask::task() {
	mQueue = xQueueCreate(10, 1);

	while(true) {
		void* message;
		if(xQueueReceive(mQueue, &message, portMAX_DELAY) == pdTRUE) {
			debug::log("RadioTransmitTask: told to transmit");
        }
	}

}
