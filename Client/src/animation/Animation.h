//
// Created by riclui on 17/11/23.
//

#ifndef WORMS_TALLER_1_ANIMATION_H
#define WORMS_TALLER_1_ANIMATION_H


class Animation {
 protected:
    bool m_repeat;
    bool m_isEnded;
    int m_currentFrame;

 public:
    explicit Animation(bool repeat = true);
    virtual void update() = 0;
    bool isEnded() const;
};


#endif  // WORMS_TALLER_1_ANIMATION_H
