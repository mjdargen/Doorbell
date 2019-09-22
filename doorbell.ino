/*
  
  Doorbell
  Michael D'Argenio
  mjdargenio@gmail.com
  https://dargenio.dev
  https://github.com/mjdargen
  September 21, 2019

  Doorbell that plays a random tune! Hook a
  switch of your choice up to a wire and 
  mount it outside your door. Then wire up
  a speaker inside. You can add more tunes
  by following the format in "songs.h".

  Passive Buzzer/Piezoelectric Speaker
  * Digital output 8
  * Other end of speaker connected to GND

  Pushbutton (for doorbell):
  * Digital input 2
  * Pulled down with 10k resistor to GND
  * Other end of switch connected to 5V

*/

#include "pitches.h"
#include "songs.h"

#define BUTTON_PIN 2
#define SPEAKER_PIN 8

/* set up function */
void setup() {
  // put your setup code here, to run once:

  // enable input/output pins
  pinMode(BUTTON_PIN, INPUT);
  pinMode(SPEAKER_PIN, OUTPUT);

  // seed random() function so that we get a different order
  randomSeed(analogRead(0));

}

/* main while loop function */
void loop() {
  // put your main code here, to run repeatedly:

  // check to see if button is pressed
  if (digitalRead(BUTTON_PIN) == HIGH) {
    // delay 50 ms to make sure it's still pressed
    // avoids any stray misreadings
    delay(50);
    if(digitalRead(BUTTON_PIN) == HIGH) {
      // randomly choose a song
      int song_choice = random(5);
      
      // select which song to play
      switch (song_choice) {
        case 0:
          play_song(haircutLength,haircut,haircutDurations,haircutTempo);
          break;
        case 1:
          play_song(marioLength,mario,marioDurations,marioTempo);
          break;
        case 2:
          play_song(miiLength,mii,miiDurations,miiTempo);
          break;
        case 3:
          //play_repository(hp,162,num_hp); //30
          play_song(hpLength,hp,hpDurations,hpTempo);
          break;
        case 4:
          //play_repository(takeonme,144,num_takeonme);
          play_song(takeonmeLength,takeonme,takeonmeDurations,takeonmeTempo);
          break;
        default:
          play_song(miiLength,mii,miiDurations,miiTempo);
          break;
      }
    }
  }
}

/* plays the song */
void play_song(int num_notes, int melody[], int noteDurations[], int tempo) {
  // step through and play all of the notes
  for (int i=0; i<num_notes; i++){
    int duration = 0;
    // calculate the duration of each note
    if (noteDurations[i] > 0) {
      duration = tempo / noteDurations[i];
    }
    // if it's a negative number, means dotted note
    // increases the duration by half for dotted notes
    else if (noteDurations[i] < 0) {
      duration = tempo / abs(noteDurations[i]) * 1.5;
    }
    tone(SPEAKER_PIN, melody[i], duration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(SPEAKER_PIN);
  }
}
