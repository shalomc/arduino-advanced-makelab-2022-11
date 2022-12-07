#define SPEAKER_PIN 13

class SpaceBeeper {
  
    int onDuration;
    int offDuration;
    int noteCount;

    int noteIndex;
    unsigned long previousMillis;

  public:

  SpaceBeeper(int on, int off, int notes) {
    onDuration = on;
    offDuration = off;
    noteCount = notes;
    
    noteIndex = 0;
    previousMillis = 0;
  }

  void Update() {
    unsigned long currentMillis = millis();
    if ((currentMillis - previousMillis) >= (offDuration)) {
      tone(SPEAKER_PIN, 3000 + 300 * noteIndex, onDuration);
      noteIndex = noteIndex + 1;
      previousMillis = millis();
      if(noteIndex >= noteCount) { 
        noteIndex = 0;
      }
    }
  }
};
