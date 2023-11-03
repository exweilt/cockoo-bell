#include <SFML/Audio.hpp>
#include <iostream>

#define SND_PATH_PRE "C:\\Users\\Nekto\\Desktop\\projects\\repos\\Cuckoo-clock\\pre_bell.wav"
#define SND_PATH_SINGLE "C:\\Users\\Nekto\\Desktop\\projects\\repos\\Cuckoo-clock\\single_bell.wav"
#define SND_PATH_LAST "C:\\Users\\Nekto\\Desktop\\projects\\repos\\Cuckoo-clock\\last_bell.wav"


class Cockoo {
public:
    static Cockoo& getInstance() {
        static Cockoo instance;
        return instance;
    }

private:
    Cockoo
};


void play_bell_sequence(int num) {
    
}

int main() {

    // Preparing sounds
    sf::SoundBuffer buffer1;
    sf::SoundBuffer buffer2;
    sf::SoundBuffer buffer3;

    bool success = true;
    success = buffer1.loadFromFile(SND_PATH_PRE) ? success : false;
    success = buffer2.loadFromFile(SND_PATH_SINGLE) ? success : false;
    success = buffer3.loadFromFile(SND_PATH_LAST) ? success : false;
    if (!success) {
        std::cerr << "Failed to load audio file." << std::endl;
        return 1;
    }

    sf::Sound sound_prep;
    sf::Sound sound_single;
    sf::Sound sound_last;
    
    sound_prep.setBuffer(buffer1);
    sound_single.setBuffer(buffer2);
    sound_last.setBuffer(buffer3);

    // Play the loaded audio
    sound_prep.play();

    // Wait for the audio to finish playing
    while (sound_prep.getStatus() == sf::Sound::Playing) {
    }
    int counter = 0;
    while (counter <= 5) {
        sound_single.play();
        while (sound_single.getStatus() == sf::Sound::Playing) {
        }
        counter++;
    }
    sound_last.play();
    while(sound_last.getStatus() == sf::Sound::Playing) {}
    
    return 0;
}
//void PlayCuckooBells() {
//    const char* filePath = "C:\\Users\\Nekto\\Desktop\\projects\\repos\\Cuckoo-clock\\single_bell.wav";
//
//    PlaySoundA(filePath, NULL, SND_FILENAME);
//}
