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

    void play_bell_sequence(int num) {
        if (num <= 0)
            return;

        this->sound_prep.play();
        wait_sound(&(this->sound_prep));

        for (int cnt = 0; cnt < num - 1; cnt++) {
            this->sound_single.play();
            wait_sound(&(this->sound_single));
        }

        this->sound_last.play();
        wait_sound(&(this->sound_last));
    }
    Cockoo() {
        load_sounds();
    }

    sf::SoundBuffer buffer1;
    sf::SoundBuffer buffer2;
    sf::SoundBuffer buffer3;

    sf::Sound sound_prep;
    sf::Sound sound_single;
    sf::Sound sound_last;

    // Passes when the sound ends
    void wait_sound(sf::Sound *snd) {
        while (snd->getStatus() == sf::Sound::Playing) {}
    }

    // Preparing sounds
    bool load_sounds() {

        bool success = true;
        success = this->buffer1.loadFromFile(SND_PATH_PRE) ? success : false;
        success = this->buffer2.loadFromFile(SND_PATH_SINGLE) ? success : false;
        success = this->buffer3.loadFromFile(SND_PATH_LAST) ? success : false;
        if (!success) {
            std::cerr << "Failed to load audio file." << std::endl;
            return false;
        }

        this->sound_prep.setBuffer(this->buffer1);
        this->sound_single.setBuffer(this->buffer2);
        this->sound_last.setBuffer(this->buffer3);
    }
}; 

int main() {
    Cockoo cockooApp = Cockoo::getInstance();

    cockooApp.play_bell_sequence(3);

 
    return 0;
}
