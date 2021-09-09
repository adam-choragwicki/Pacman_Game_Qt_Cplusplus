#include "sounds.h"

Sounds::Sounds()
{
    beginningSound_.setMedia(QUrl("qrc:/sounds/pacman_beginning.wav"));
    eatFoodballSound1_.setMedia(QUrl("qrc:/sounds/pacman_eat.wav"));
    eatFoodballSound2_.setMedia(QUrl("qrc:/sounds/pacman_eat.wav"));
    eatGhostSound_.setMedia(QUrl("qrc:/sounds/pacman_eat_ghost.wav"));
    pacmanDeathSound_.setMedia(QUrl("qrc:/sounds/pacman_death.wav"));
    siren_.setMedia(QUrl("qrc:/sounds/pacman_siren.wav"));
}

void Sounds::playBeginningSound()
{
    beginningSound_.play();
}

void Sounds::playEatFoodballSound1()
{
    if(eatFoodballSound1_.state() == QMediaPlayer::StoppedState)
    {
        eatFoodballSound1_.play();
    }

    if(eatFoodballSound1_.state()  == QMediaPlayer::PlayingState)
    {
        eatFoodballSound2_.play();
    }
}

void Sounds::playEatGhostSound()
{
    eatGhostSound_.play();
}

void Sounds::playPacmanDeathSound()
{
    pacmanDeathSound_.play();
}

void Sounds::playSirenSound()
{
    siren_.play();
}
