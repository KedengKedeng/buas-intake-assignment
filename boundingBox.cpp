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

Tmpl8::vec2 BoundingBox::swept(BoundingBox& box, Tmpl8::vec2 velocity) {
    Tmpl8::vec2 firstPos = getPos();
    Tmpl8::vec2 firstSize = getSize();
    Tmpl8::vec2 secondPos = box.getPos();
    Tmpl8::vec2 secondSize = box.getSize();

    Tmpl8::vec2 entryTime(
        getSweptTimings(firstPos.x, secondPos.x, firstSize.x, secondSize.x, velocity.x),
        getSweptTimings(firstPos.y, secondPos.y, firstSize.y, secondSize.y, velocity.y)
    );

    return entryTime;
}

float BoundingBox::getSweptTimings(float firstPos, float secondPos, float firstSize, float secondSize, float velocity) {
    Tmpl8::vec2 difference(0, 0);

    if (velocity > 0.0f) {
        difference.x = secondPos - (firstPos + firstSize);
        difference.y = (secondPos + secondSize) - firstPos;
    }
    else {
        difference.x = (secondPos + secondSize) - firstPos;
        difference.y = secondPos - (firstPos + firstSize);
    }

    Tmpl8::vec2 timings(
        -std::numeric_limits<float>::infinity(),
        std::numeric_limits<float>::infinity()
    );

    if (velocity != 0.0f) timings = difference / velocity;
    
    if (timings.x > timings.y || timings.x > 1.0f || timings.x < 0.0f) timings.x = 1.0f;

    return timings.x;
}
