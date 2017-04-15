
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <MP3Player_KT403A.h>
SoftwareSerial mp3(2, 3);

#define pinPoussoirs A0
#define REDPIN 10
#define GREENPIN 11
#define BLUEPIN 9
#define WHITEPIN 6

#define FADESPEED 10 
#define nbrepet 10

const byte NON_PRESSE = 0;
const byte ENFONCE = 1;
const byte PRESSE = 2;

byte etatAutomate = NON_PRESSE;
int etatPoussoir = -1;

const byte AUCUN_EVENEMENT = 0;
const byte EVENEMENT_PRESSE = 1;
const byte EVENEMENT_RELACHE = 2;


bool endOfSong(){
    int a=mp3.read();
    bool res = (a !=-1);
    if(res){
        Serial.println("end of song ");
        Serial.println(a);
        for(int i = 0; i < 10; ++i){
            int a=mp3.read();
        }
    }
    return res;
}


int lirePoussoirs()
{
    int resultat;
    int numPoussoir = (analogRead(pinPoussoirs) + 64) / 128;

    int nouvelEtatPoussoir = etatPoussoir; /* à priori rien ne change */

    switch (etatAutomate) {
        case NON_PRESSE:
            if (numPoussoir < 8)
                etatAutomate = ENFONCE;
            break;
        case ENFONCE:
            if (numPoussoir < 8) {
                etatAutomate = PRESSE;
                nouvelEtatPoussoir = numPoussoir;
            }
            else {
                etatAutomate = NON_PRESSE;
            }
            break;
        case PRESSE:
            if (numPoussoir == 8) {
                etatAutomate = NON_PRESSE;
                nouvelEtatPoussoir = -1;
            }
            break;
    }

    return nouvelEtatPoussoir;
}

/*
 * construction d'un événement en comparant
 * le nouvel état des poussoirs avec l'état précédent.
 */
byte lireEvenement(int *numPoussoir)
{
    byte evenement;
    int nouvelEtatPoussoir = lirePoussoirs();

    if (nouvelEtatPoussoir == etatPoussoir)
        evenement = AUCUN_EVENEMENT;
    if (nouvelEtatPoussoir >= 0 && etatPoussoir == -1) 
        evenement = EVENEMENT_PRESSE;
    if (nouvelEtatPoussoir == -1 && etatPoussoir >= 0) 
        evenement = EVENEMENT_RELACHE;

    etatPoussoir = nouvelEtatPoussoir;
    *numPoussoir = etatPoussoir;

    return evenement;
}

void inde(){
    Serial.println("inde");
    analogWrite(REDPIN, 0);
    analogWrite(BLUEPIN, 0);
    analogWrite(GREENPIN,0); 

    SpecifyMusicPlay(1);
    bool play = true;
    // fade from red to yellow
    while(play){
        for (int g = 0; g < 256; g++) { 
            analogWrite(GREENPIN, g);
            delay(FADESPEED);
        }
        play = play && !endOfSong(); if(!play){ break; }
        for( int i=0; i<nbrepet;i++){


            // fade from red to yellow
            for (int r = 0 ; r <150 ; r++) { 
                analogWrite(REDPIN, r);
                delay(FADESPEED);
                play = play && !endOfSong(); if(!play){ break; }
            }
            for (int r = 150 ; r >0; r--) { 
                analogWrite(REDPIN, r);
                delay(FADESPEED);
                play = play && !endOfSong(); if(!play){ break; }
            }
        }
        play = play && !endOfSong(); if(!play){ break; }
    }
    analogWrite(REDPIN, 0);
    analogWrite(BLUEPIN, 0);
    analogWrite(GREENPIN,0); 
    Serial.println("fin inde");
}

void belgique(){
    Serial.println("belgique");
    analogWrite(REDPIN, 0);
    analogWrite(BLUEPIN, 0);
    analogWrite(GREENPIN,0); 
    delay(500);
    analogWrite(GREENPIN,255); 
    analogWrite(REDPIN, 200);
    delay(500);

    SpecifyMusicPlay(2);
    bool play = true;
    while(play){
        for (int g = 256; g >0; g--) { 
            analogWrite(GREENPIN, g);
            delay(FADESPEED);
        }
        play = play && !endOfSong(); if(!play){ break; }
        for (int r = 200; r<256; r++) { 
            analogWrite(REDPIN, r);
            delay(FADESPEED);
        }
        play = play && !endOfSong(); if(!play){ break; }
        for (int r = 256; r>200; r--) { 
            analogWrite(REDPIN, r);
            delay(FADESPEED);
        }
        play = play && !endOfSong(); if(!play){ break; }
        for (int g = 0; g < 256; g++) { 
            analogWrite(GREENPIN, g);
            delay(FADESPEED);
        }
    }
    analogWrite(REDPIN, 0);
    analogWrite(BLUEPIN, 0);
    analogWrite(GREENPIN,0);
    Serial.println("finbelgique");
}

void angleterre(){
    Serial.println("angleterre");
    analogWrite(REDPIN, 0);
    analogWrite(BLUEPIN, 0);
    analogWrite(GREENPIN,0); 
    analogWrite(WHITEPIN,0); 
    SpecifyMusicPlay(4);
    bool play = true;
    while(play){
        analogWrite(REDPIN, 255);
        analogWrite(BLUEPIN, 0);
        delay(125);
        analogWrite(REDPIN, 0);
        delay(75);
        analogWrite(REDPIN, 180);
        analogWrite(BLUEPIN, 150);
        analogWrite(GREENPIN,255); 
        analogWrite(WHITEPIN,255); 
        delay(125);
        play = play && !endOfSong(); if(!play){ break; }
        analogWrite(WHITEPIN,0); 
        analogWrite(REDPIN, 0);
        analogWrite(BLUEPIN, 0);
        analogWrite(GREENPIN,0);
        delay(75);
        analogWrite(REDPIN, 0);
        analogWrite(BLUEPIN, 255);
        analogWrite(GREENPIN,0);
        delay(125);
        analogWrite(BLUEPIN, 0);
        delay(75);
        play = play && !endOfSong(); if(!play){ break; }
    }
    delay(1000);
    analogWrite(REDPIN, 125);
    analogWrite(BLUEPIN, 125);
    analogWrite(GREENPIN,255); 
    delay(5000);

    analogWrite(REDPIN, 0);
    analogWrite(BLUEPIN, 0);
    analogWrite(GREENPIN,0);
    analogWrite(WHITEPIN,255); 
    Serial.println("finangleterre");
}


void hawaii(){
    Serial.println("hawaii");
    analogWrite(REDPIN, 0);
    analogWrite(BLUEPIN, 255);
    analogWrite(GREENPIN,0);
    delay(5000);
    analogWrite(REDPIN, 0);
    analogWrite(BLUEPIN, 0);
    analogWrite(GREENPIN,0);

    Serial.println(" fin hawaii");  
}


void mars(){
    Serial.println("mars");
    analogWrite(REDPIN, 255);
    analogWrite(BLUEPIN, 0);
    analogWrite(GREENPIN,0);
    delay(5000);
    analogWrite(REDPIN, 0);
    analogWrite(BLUEPIN, 0);
    analogWrite(GREENPIN,0);

    Serial.println(" fin mars");  
}

void maison(){
    Serial.println("maison");
    int delai =50;
    for(int i=0;i<nbrepet;i++){
        analogWrite(REDPIN, 255);
        analogWrite(BLUEPIN, 0);
        analogWrite(GREENPIN,0);
        delay(delai);
        analogWrite(REDPIN, 0);
        analogWrite(BLUEPIN, 0);
        analogWrite(GREENPIN,255);
        delay(delai);
        analogWrite(REDPIN, 0);
        analogWrite(BLUEPIN, 0);
        analogWrite(GREENPIN,255);
        delay(delai);
        analogWrite(REDPIN,255);
        analogWrite(BLUEPIN, 255);
        analogWrite(GREENPIN,0);
        delay(delai);
        analogWrite(REDPIN, 0);
        analogWrite(BLUEPIN, 255);
        analogWrite(GREENPIN,255);
        delay(delai);
        analogWrite(REDPIN, 255);
        analogWrite(BLUEPIN,0);
        analogWrite(GREENPIN,255);
        delay(delai);
    }
    analogWrite(REDPIN, 0);
    analogWrite(BLUEPIN, 0);
    analogWrite(GREENPIN,0);

    Serial.println(" fin maison");  
}

void setup()
{
    mp3.begin(9600);
    SelectPlayerDevice(0x02);       // Select SD card as the player device.
    SetVolume(0x1E);   // Set the volume, the range is 0x00 to 0x1E.  
    pinMode(REDPIN,OUTPUT);
    pinMode(BLUEPIN,OUTPUT);
    pinMode(GREENPIN,OUTPUT);
    pinMode(WHITEPIN,OUTPUT);
    pinMode(4,INPUT);

    Serial.begin(9600);
    analogWrite(REDPIN, 0);
    analogWrite(BLUEPIN, 0);
    analogWrite(GREENPIN,0);
    analogWrite(WHITEPIN,0);
    while( digitalRead(4)!=0){
        Serial.println( digitalRead(4));
    }
    Serial.println("pret");
    while( digitalRead(4)!=0){
        Serial.println( digitalRead(4));
    }
    for(int i = 0;i<256;i++)
    {
        analogWrite(WHITEPIN,i);
    }
}


void loop(){

    int numPoussoir;
    byte evenement = lireEvenement(&numPoussoir);

    switch (evenement) {
        case EVENEMENT_PRESSE:
            Serial.print("Presse : ");
            Serial.println(numPoussoir);
            switch(numPoussoir){
                case 1 :
                    inde();
                    break;
                case 2 :
                    belgique();
                    break;
                case 3 :
                    angleterre();
                    break;
                case 4 :
                    hawaii();
                    break;
                case 5 :
                    mars();
                    break;
                case 6 :
                    maison();
                    break;
            }
            break;
        case EVENEMENT_RELACHE:
            Serial.print("Relache : ");
            Serial.println(numPoussoir);
            break;
    }

    delay(3);
}





void setup2()
{
    mp3.begin(9600);
    Serial.begin(9600); 
    delay(100);

    SelectPlayerDevice(0x02);       // Select SD card as the player device.
    SetVolume(0x0E);                // Set the volume, the range is 0x00 to 0x1E.
}

void loop2()
{
    char recvChar = 0;
    while(Serial.available())
    {
        recvChar = Serial.read();
    }
    Serial.print("Send: ");
    Serial.println( recvChar );

    switch (recvChar)
    {
        case '1':
            SpecifyMusicPlay(1);
            Serial.println("Specify the music index to play");
            break;
        case '2':
            PlayPause();
            Serial.println("Pause the MP3 player");
            break;
        case '3':
            PlayResume();
            Serial.println("Resume the MP3 player");
            break;
        case '4':
            PlayNext();
            Serial.println("Play the next song");
            break;
        case '5':
            PlayPrevious();
            Serial.println("Play the previous song");
            break;
        case '6':
            PlayLoop();
            Serial.println("Play loop for all the songs");
            break;
        case '7':
            IncreaseVolume();
            Serial.println("Increase volume");
            break;
        case '8':
            DecreaseVolume();
            Serial.println("Decrease volume");
            break;
        default:
            break;
    }

    delay(1000);

    printReturnedData();
}
