
# include "SoundEngine.hh"

SoundEngine::SoundEngine() {
    _music_vol = 50;
    _sound_vol = 50;
}

SoundEngine::~SoundEngine() {
    MusicMap::iterator itm;
    SoundMap::iterator its;

    for (itm = _music_map.begin(); itm != _music_map.end(); itm++) {
        delete (itm)->second;
    }
    for (its = _sound_map.begin(); its != _sound_map.end(); its++) {
        delete (its)->second;
    }
}

void SoundEngine::loadMusic(const std::string & name, const std::string & path) {
    sf::Music *tmp = new sf::Music();

    if (!tmp->openFromFile(path)) {
        std::cerr << "Error while loading music" << std::endl;
    }
    _music_map.insert(std::make_pair(name, tmp));
}

void SoundEngine::playMusic(const std::string &name) {
    sf::Music * music;

    music = _music_map.find(name)->second;
    music->setLoop(true);
    music->setVolume(_music_vol);
    music->play();
}

void SoundEngine::stopMusic(const std::string &name) {
    sf::Music * music;

    music = _music_map.find(name)->second;
    music->stop();
}

void SoundEngine::volumeMusic(const size_t vol) {
    _music_vol = vol;
}

void SoundEngine::loadSound(const std::string & name, const std::string & path) {
    sf::SoundBuffer *tmpBuff = new sf::SoundBuffer();
    sf::Sound *tmp = new sf::Sound();

    if (!tmpBuff->loadFromFile(path)) {
        std::cerr << "Error while loading sound" << std::endl;
    }
    tmp->setBuffer(*tmpBuff);
    _sound_map.insert(std::make_pair(name, tmp));
}

void SoundEngine::playSound(const std::string &name) {
    sf::Sound * sound;

    sound = _sound_map.find(name)->second;
    sound->setVolume(_sound_vol);
    sound->play();
}

void SoundEngine::volumeSound(const size_t vol) {
    _sound_vol = vol;
}
