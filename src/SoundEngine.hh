
#ifndef SOUNDENGINE_HH_
# define SOUNDENGINE_HH_

#include <map>
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>

typedef std::map<const std::string, sf::Music*> MusicMap;
typedef std::map<const std::string, sf::Sound*> SoundMap;

class SoundEngine {
protected:
  MusicMap _music_map;
  size_t   _music_vol;
  SoundMap _sound_map;
  size_t   _sound_vol;
public:
  SoundEngine();
  ~SoundEngine();
public:
  void loadMusic(const std::string & name, const std::string & path);
  void playMusic(const std::string & name);
  void stopMusic(const std::string & name);
  void volumeMusic(const size_t vol);
  void loadSound(const std::string & name, const std::string & path);
  void playSound(const std::string & name);
  void volumeSound(const size_t vol);
};

#endif // !SOUNDENGINE_HH_
