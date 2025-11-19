#include "boundingBox.hpp"

bool BoundingBox::isInBounds(BoundingBox& box) {
	Tmpl8::vec2 firstPos = getPos();
	Tmpl8::vec2 firstSize = getSize();
	Tmpl8::vec2 secondPos = box.getPos();
	Tmpl8::vec2 secondSize = box.getSize();

	return (
		firstPos.x < secondPos.x + secondSize.x &&
		firstPos.x + firstSize.x > secondPos.x &&
		firstPos.y < secondPos.y + secondSize.y &&
		firstPos.y + firstSize.y > secondPos.y
	);
}

CollisionResult BoundingBox::swept(BoundingBox& box, Tmpl8::vec2& velocity) {
    Tmpl8::vec2 firstPos = getPos();
    Tmpl8::vec2 firstSize = getSize();
    Tmpl8::vec2 secondPos = box.getPos();
    Tmpl8::vec2 secondSize = box.getSize();

    SweptAxisResult resultX = getSweptTimings(firstPos.x, secondPos.x, firstSize.x, secondSize.x, velocity.x);
    SweptAxisResult resultY = getSweptTimings(firstPos.y, secondPos.y, firstSize.y, secondSize.y, velocity.y);

    if (!resultX.collision || !resultY.collision) return { false, 0, 0, 0 };

    float entryTime = std::max(resultX.timings.x, resultY.timings.x);
    float exitTime = std::min(resultX.timings.y, resultY.timings.y);

    if (entryTime > exitTime || entryTime < 0 || entryTime > 1) 
        return { false, 0, 0, 0 };

    float normalX = 0, normalY = 0;
    if (resultX.timings.x > resultY.timings.x) normalX = (velocity.x > 0) ? -1.0f : 1.0f;
    else normalY = (velocity.y > 0) ? -1.0f : 1.0f;

    return { true, normalX, normalY, entryTime };
}

SweptAxisResult BoundingBox::getSweptTimings(float firstPos, float secondPos, float firstSize, float secondSize, float velocity) {
    Tmpl8::vec2 difference(0, 0);
    Tmpl8::vec2 timings(
        -std::numeric_limits<float>::infinity(),
        std::numeric_limits<float>::infinity()
    );

    if (velocity == 0.0f) {
        if (firstPos + firstSize < secondPos || secondPos + secondSize < firstPos) return { false, Tmpl8::vec2(1.0f, 1.0f)};
    }
    else {
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

    return { true, timings };
}
