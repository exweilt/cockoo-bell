#include <SFML/Audio.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>

#define SND_PATH_PRE "C:\\Users\\Nekto\\Desktop\\projects\\repos\\Cuckoo-clock\\pre_bell.wav"
#define SND_PATH_SINGLE "C:\\Users\\Nekto\\Desktop\\projects\\repos\\Cuckoo-clock\\single_bell.wav"
#define SND_PATH_LAST "C:\\Users\\Nekto\\Desktop\\projects\\repos\\Cuckoo-clock\\last_bell.wav"

#define VOLUME 30


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
private:
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
        
        this->sound_prep.setVolume(VOLUME);
        this->sound_single.setVolume(VOLUME);
        this->sound_last.setVolume(VOLUME);
    }
}; 

int main() {
    Cockoo cockooApp = Cockoo::getInstance();

    //cockooApp.play_bell_sequence(3);

    std::cout << "Cockoo awaits its time" << std::endl;

    // Cockoo cycle
    while (true) {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        struct std::tm timeInfo;
        localtime_s(&timeInfo, &currentTime);

        std::cout << "Cycle, sec " << timeInfo.tm_sec << std::endl;
        
        std::this_thread::sleep_for(std::chrono::seconds(60 - timeInfo.tm_sec));

        cockooApp.play_bell_sequence(((timeInfo.tm_hour - 1) % 12 + 1));
        
    }
 
    return 0;
}
