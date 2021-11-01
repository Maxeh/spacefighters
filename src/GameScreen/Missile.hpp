#ifndef SPACEFIGHTERS_MISSILE_HPP
#define SPACEFIGHTERS_MISSILE_HPP

enum class MissileOwner {PLAYER, COMPUTER};
enum class MissileDirection {UP, DOWN};

class Missile {
    float x;
    float y;
    MissileDirection missileDirection;
    MissileOwner missileOwner;

    float width = 5;
    float height = 5;
    float velocity = 5;
    bool visible = true;
public:
    Missile(float x, float y, MissileDirection missileDirection, MissileOwner missileOwner);
    ~Missile() = default;
    void move();
    float getX() const;
    float getY() const;
    MissileDirection getMissileDirection() const;
    MissileOwner getMissileOwner() const;
    float getWidth() const;
    float getHeight() const;
    bool isVisible() const;
    void setVisible(bool visible_);
};

#endif