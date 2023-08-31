#pragma once

#include "common.h"
#include <utility>
#include <QPoint>

class AbstractOffset
{
public:
    [[nodiscard]] std::pair<int, int> toStdPair() const
    {
        return {offset_.first, offset_.second};
    }

    void determineOffset(Direction direction)
    {
        switch(direction)
        {
            case Direction::LEFT:
                offset_ = std::pair{-1, 0};
                break;

            case Direction::RIGHT:
                offset_ = std::pair{+1, 0};
                break;

            case Direction::UP:
                offset_ = std::pair{0, -1};
                break;

            case Direction::DOWN:
                offset_ = std::pair{0, +1};
                break;
        }
    }

    virtual ~AbstractOffset() = default;

protected:
    std::pair<int, int> offset_;
};

class DirectionalOffset : public AbstractOffset
{
public:
    DirectionalOffset()
    {
        offset_ = std::pair{0, 0};
    }

    explicit DirectionalOffset(Direction direction)
    {
        determineOffset(direction);
    }

    DirectionalOffset& operator=(Direction direction)
    {
        determineOffset(direction);
        return *this;
    }
};

class VerticalDirectionalOffset : public AbstractOffset
{
public:
    explicit VerticalDirectionalOffset(Direction direction)
    {
        switch(direction)
        {
            case Direction::UP:
                offset_ = std::pair{0, -1};
                break;

            case Direction::DOWN:
                offset_ = std::pair{0, +1};
                break;

            default:
                throw std::runtime_error("Error, vertical directional offset accepts only UP and DOWN directions");
        }
    }
};
