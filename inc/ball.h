#pragma once

#include "coordinates.h"

class AbstractBall
{
public:
    explicit AbstractBall(const Coordinates& coordinates);
    virtual ~AbstractBall() = 0;

    [[nodiscard]] const Coordinates& getCoordinates() const
    { return coordinates_; }

    [[nodiscard]] bool isEaten() const
    { return eaten_; }

    void setEaten(bool eaten)
    { eaten_ = eaten; }

private:
    const Coordinates coordinates_;
    bool eaten_;
};

class Foodball : public AbstractBall
{
public:
    explicit Foodball(const Coordinates& coordinates);
    ~Foodball() override = default;
};

class Powerball : public AbstractBall
{
public:
    explicit Powerball(const Coordinates& coordinates);
    ~Powerball() override = default;
};
