//
// Created by pumf on 22/06/2025.
//

#include "RenderingSystem.h"

#include "brewEngine/rendering/BackgroundComponent.h"

void scrollBackgroundSprite(gl3::brewEngine::rendering::BackgroundComponent* background, bool isScrollingSideways, bool goesLeftOrUp, float deltaTime) {
    // If isScrollingSideways and goesLeftOrDown is true then the background will scroll to the left
    // If isScrollingSideways is true but goesLeftOrDown is false then the background will scroll to the right
    // If isScrollingSideways is false but goesLeftOrDown is true the background will move up along the y axis
    // If isScrollingSideways and goesLeftOrDown is false, the background will go down
    float offset;
    float sign;
    if(goesLeftOrUp) {
        offset = -1.0f * deltaTime;
        sign = -1;
    }
    else {
        offset = 1.0f * deltaTime;
        sign = 1;
    }

    if(isScrollingSideways) {
        background->position.x += offset * background->scrollingSpeed;
        background->copysPosition.x += offset * background->scrollingSpeed;

        if(background->position.x <= sign * background->scale.x) {
            background->position.x = background->copysPosition.x + background->scale.x;
        }
        else if(background->copysPosition.x <= -background->scale.x) {
            background->copysPosition.x = background->position.x + background->scale.x;
        }
    }
    else {
        background->position.y += offset * background->scrollingSpeed;
        background->copysPosition.y += offset * background->scrollingSpeed;

        if(background->position.y <= sign * background->scale.y) {
            background->position.y = background->copysPosition.y + background->scale.y;
        }
        else if(background->copysPosition.y <= -background->scale.y) {
            background->copysPosition.y = background->position.y + background->scale.y;
        }
    }
}
