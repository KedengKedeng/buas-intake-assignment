#include "boundingBox.hpp"
#include <algorithm>

// simple aabb bounds checking
bool BoundingBox::isInBounds(BoundingBox& box) {
	auto firstPos = getPos();
	auto firstSize = getSize();
	auto secondPos = box.getPos();
	auto secondSize = box.getSize();

	return (
		firstPos.x < secondPos.x + secondSize.x &&
		firstPos.x + firstSize.x > secondPos.x &&
		firstPos.y < secondPos.y + secondSize.y &&
		firstPos.y + firstSize.y > secondPos.y
	);
}

bool BoundingBox::isInBounds(vec2<float>& point) {
    return isInBounds(BoundingBox(point, vec2<float>(0.0f)));
}

CollisionResult BoundingBox::swept(BoundingBox& box, vec2<float>& velocity) {
    auto firstPos = getPos();
    auto firstSize = getSize();
    auto secondPos = box.getPos();
    auto secondSize = box.getSize();

    // check collisions for each side
    SweptAxisResult resultX = getSweptTimings(firstPos.x, secondPos.x, firstSize.x, secondSize.x, velocity.x);
    SweptAxisResult resultY = getSweptTimings(firstPos.y, secondPos.y, firstSize.y, secondSize.y, velocity.y);

    if (!resultX.collision || !resultY.collision) return { false, 0, 0, 0 };

    // check first possible collision time on each side
    float entryTime = std::max(resultX.timings.x, resultY.timings.x);
    float exitTime = std::min(resultX.timings.y, resultY.timings.y);

    // check if the collision time actually happens in the time frame we are checking for
    if (entryTime > exitTime || entryTime < 0 || entryTime > 1) 
        return { false, 0, 0, 0 };

    // get the normal of the collision
    float normalX = 0, normalY = 0;
    if (resultX.timings.x > resultY.timings.x) normalX = (velocity.x > 0) ? -1.0f : 1.0f;
    else normalY = (velocity.y > 0) ? -1.0f : 1.0f;

    return { normalX, normalY, entryTime, true };
}

SweptAxisResult BoundingBox::getSweptTimings(float firstPos, float secondPos, float firstSize, float secondSize, float velocity) {
    vec2<float> difference(0.0f);
    vec2<float> timings(
        -std::numeric_limits<float>::infinity(),
        std::numeric_limits<float>::infinity()
    );

    if (velocity == 0.0f) {
        // the object can stil be colliding on a side even if it isnt moving.
        // so these if statements have to be seperate to account for that.
        if (firstPos + firstSize < secondPos || secondPos + secondSize < firstPos) return { vec2(1.0f), false};
    }
    else {
        // do slightly different swept checks based on if the collision is forwards or backwards.
        if (velocity > 0.0f) {
            difference.x = secondPos - (firstPos + firstSize);
            difference.y = (secondPos + secondSize) - firstPos;
        }
        else {
            difference.x = (secondPos + secondSize) - firstPos;
            difference.y = secondPos - (firstPos + firstSize);
        }
        timings = difference / velocity;
    }

    return { timings, true };
}
