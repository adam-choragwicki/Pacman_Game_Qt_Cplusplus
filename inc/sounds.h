#pragma once

#include <QMediaPlayer>

class Sounds
{
public:
    Sounds();
    void playBeginningSound();
    void playEatFoodballSound1();
    void playEatGhostSound();
    void playPacmanDeathSound();
    void playSirenSound();

private:
    QMediaPlayer beginningSound_;
    QMediaPlayer eatFoodballSound1_;
    QMediaPlayer eatFoodballSound2_;
    QMediaPlayer eatGhostSound_;
    QMediaPlayer pacmanDeathSound_;
    QMediaPlayer siren_;
};
