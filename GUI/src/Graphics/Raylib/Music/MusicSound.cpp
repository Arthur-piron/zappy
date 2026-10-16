/*
** EPITECH PROJECT, 2026
** G-YEP-400-LIL-4-1-zappy-13
** File description:
** Music
*/

#include "MusicSound.hpp"
#include <iostream>

namespace Raylib {
    MusicSound::MusicSound(std::string path)
    {
        _music = LoadMusicStream(path.c_str());
        // Music tracks are not shipped in the public repo (copyright):
        // a missing track plays silence instead of stopping the GUI.
        if (_music.ctxType == 0)
            std::cerr << "Warning: music not found, playing silence: " << path << std::endl;
    }

    MusicSound::~MusicSound()
    {
        UnloadMusicStream(_music);
    }

    void MusicSound::play(bool loop)
    {
        _music.looping = loop;
        PlayMusicStream(_music);
        updateStream();
    }

    void MusicSound::updateVolume(float volume)
    {
        SetMusicVolume(_music, volume);
    }
    
    void MusicSound::updateStream()
    {
        UpdateMusicStream(_music);
    }

    Music& MusicSound::getMusic()
    {
        return _music;
    }

    void MusicSound::stop()
    {
        StopMusicStream(_music);
    }

    bool MusicSound::isPlaying()
    {
        return IsMusicStreamPlaying(_music);
    }

    MusicSound& MusicSound::operator=(MusicSound&& other)
    {
        if (this != &other) {
            UnloadMusicStream(_music);
            _music = other._music;
            other._music = {};
        }
        return *this;
    }
}
