//TO COMPILE: gcc -o example2 example.c -lwiringPi -llirc_client
//TO RUN: sudo ./example2

#include <wiringPi.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lirc/lirc_client.h>
#include <time.h>

void clearLED(void);
void cleanup(void);
void flipLED (int led);
void Record(void);
 
//The WiringPi pin numbers used by our LEDs
#define LED1 4
#define LED2 5
#define LED3 6
#define LED4 0
 
#define ON 1
#define OFF 0

#define BITS 8




int main(int argc, char *argv[])
{
        struct lirc_config *config;
 
        //Timer for our buttons
        int buttonTimer = millis();
 
        char *code;
        char *c;


        //Initiate WiringPi and set WiringPi pins 4, 5 & 6 (GPIO 23, 24 & 25) to output. These are the pins the LEDs are connected to.
        if (wiringPiSetup () == -1)
            exit (1) ;
 
        pinMode(LED1, OUTPUT);
        pinMode(LED2, OUTPUT);
        pinMode(LED3, OUTPUT);

        //Make a recordings folder (if there isn't one).
        system("mkdir -p /home/pi/Desktop/Final_Project/audioboard/ARecord/recordings");

        //Initiate LIRC. Exit on failure
        if(lirc_init("lirc",1)==-1)
                exit(EXIT_FAILURE);

        //Read the default LIRC config at /etc/lirc/lircd.conf  This is the config for your remote.
        if(lirc_readconfig(NULL,&config,NULL)==0)
        {
                //Do stuff while LIRC socket is open  0=open  -1=closed.
                while(lirc_nextcode(&code)==0)
                {
                        //If code = NULL, meaning nothing was returned from LIRC socket,
                        //then skip lines below and start while loop again.
                        if(code==NULL) continue;{
                                //Make sure there is a 400ms gap before detecting button presses.
                                if (millis() - buttonTimer  > 400){
                                        //Check to see if the string "KEY_1" appears anywhere within the string 'code'.
                                        if(strstr (code,"KEY_1")){
                                                printf("-audience laughter-\n");
                                                flipLED(LED1);
						system("mpg123 --quiet /home/pi/Music/laugh.mp3");
						flipLED(LED1);
                                                buttonTimer = millis();
                                        }
                                        else if(strstr (code,"KEY_2")){
                                                printf("-audience pity-\n");
                                                flipLED(LED2);
						system("mpg123 --quiet /home/pi/Music/aww.mp3");
						flipLED(LED2);
                                                buttonTimer = millis();
                                        }
                                        else if(strstr (code,"KEY_3")){
                                                printf("-audience applause-\n");
                                                flipLED(LED3);
						system("mpg123 --quiet /home/pi/Music/applause.mp3");
						flipLED(LED3);
                                                buttonTimer = millis();
                                        }
                                        else if(strstr (code,"KEY_4")){
                                                printf("-seinfeld bassline-\n");
                                                flipLED(LED1);
						system("mpg123 --quiet /home/pi/Music/seinfeld.mp3");
						flipLED(LED1);
                                                buttonTimer = millis();
                                        }
                                        else if(strstr (code,"KEY_5")){
                                                printf("MATCH on KEY_5\n");
                                                flipLED(LED2);
						system("mpg123 --quiet /home/pi/Music/hanzo.mp3");
						flipLED(LED2);
                                                buttonTimer = millis();
                                        }
                                        else if(strstr (code,"KEY_6")){
                                                printf("MATCH on KEY_6\n");
                                                flipLED(LED3);
						system("mpg123 --quiet /home/pi/Music/hanzo.mp3");
						flipLED(LED3);
						buttonTimer = millis();
					}
                                        else if(strstr (code,"KEY_7")){
                                                printf("MATCH on KEY_7\n");
                                                flipLED(LED3);
						system("mpg123 --quiet /home/pi/Music/hanzo.mp3");
						flipLED(LED3);
						buttonTimer = millis();
					}
                                        else if(strstr (code,"KEY_8")){
                                                printf("MATCH on KEY_8\n");
                                                flipLED(LED3);
						system("mpg123 --quiet /home/pi/Music/hanzo.mp3");
						flipLED(LED3);
						buttonTimer = millis();
					}
                                        else if(strstr (code,"KEY_9")){
                                                printf("MATCH on KEY_9\n");
                                                flipLED(LED3);
						system("mpg123 --quiet /home/pi/Music/hanzo.mp3");
						flipLED(LED3);
						buttonTimer = millis();
					}
                                        else if(strstr (code,"KEY_PLAYPAUSE")){
						printf("-Recording-\n");

						flipLED(LED1);
						flipLED(LED2);
						flipLED(LED3);

						Record();

   						clearLED();
					}
                                }
                        }
                        //Need to free up code before the next loop
                        free(code);
                }
                //Frees the data structures associated with config.
                lirc_freeconfig(config);
        }
        //lirc_deinit() closes the connection to lircd and does some internal clean-up stuff.
        lirc_deinit();
	cleanup();
	system("./cleanup.py");
        exit(EXIT_SUCCESS);
}

void clearLED(void){
	if(digitalRead(LED1)==ON)
                digitalWrite(LED1, OFF);
	if(digitalRead(LED2)==ON)
                digitalWrite(LED2, OFF);
	if(digitalRead(LED3)==ON)
                digitalWrite(LED3, OFF);
}

void cleanup(){
	clearLED();
	pinMode(LED1, INPUT);
        pinMode(LED2, INPUT);
        pinMode(LED3, INPUT);
}

void flipLED (int led)
{
        //If LED is on, turn it off. Otherwise it is off, so thefore we need to turn it on.
        if(digitalRead(led)==ON)
                digitalWrite(led, OFF);
        else
                digitalWrite(led, ON);
}

//Record with Arecord to a recordings folder.
void Record(void){
    system("./save_record.sh");
    sleep (2);
}