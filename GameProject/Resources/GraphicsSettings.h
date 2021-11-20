//
// Created by kevin on 20.11.2021.
//
#pragma once
class GraphSettings {
public:
    GraphSettings();
    ~GraphSettings();

    //Variable
    std::string title;
    sf::VideoMode resolution;
    bool fullScreen;
    bool verticalSync;
    unsigned frameRateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;

    //Functions
    void saveFile(const std::string path);
    void loadFile(const std::string path);
};

