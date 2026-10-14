
#include "main.h"       // main library
#include "timer.h"      // timer software library
#include "debouncer.h"  // debouncer library

DEBOUNCER db1;  //debouncer instance

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){    //system callback for the hardware timer
	if(htim == &htim1){                   //htim1 is the timer hardware, not the software one
		db1.timer.period_reached = true;   //timer software internal flag 
	  }
}

int main(void){

debouncer_init(&db1, GPIO_PIN_5, GPIOB); //initialization of the debouncer instance

 while (1)
  {
    /* USER CODE END WHILE */
	  if(db1.timer.period_reached){               
		  process_bounce(&db1);              //debouncer running by the signal from the ISR
        }
 if(pressed(&db1)){
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);   //turn on a led
	  }
    
    }
}
