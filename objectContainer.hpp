#pragma once
#include "object.hpp"
#include "vec2.hpp"
#include "subscriptionManager.hpp"
#include "clickable.hpp"
#include "scrollbar.hpp"
#include <unordered_map>
#include <memory>

enum class Justification {
	NONE,
	VERTICAL,
	HORIZONTAL
};

class ObjectContainer : public Object, public SubscriptionManager, public Clickable {
public:
	ObjectContainer(
		int64_t id,
		vec2<float> pos,
		vec2<float> size,
		Justification justification,
		vec2<float> gap,
		bool scrollable = false
	);

	// containers also need to update the positions of their children
	void setPos(vec2<float> pos) override;
	vec2<float> getSize() const override;

	virtual void draw(Tmpl8::Surface* surface, vec2<float> offset) const override;
	virtual void process(float deltaTime) override;

	virtual void insertObject(std::shared_ptr<Object> object);
	void deleteObject(int64_t id);

	void clearObjects() { objects_.clear(); }

	template<typename T>
	std::shared_ptr<T> getObject(int64_t id) const { return std::dynamic_pointer_cast<T>(objects_.at(id)); }
	virtual std::unordered_map<int64_t, std::shared_ptr<Object>>::iterator begin() { return objects_.begin(); }
	virtual std::unordered_map<int64_t, std::shared_ptr<Object>>::iterator end() { return objects_.end(); }

	virtual void onMouseDown(vec2<float> pos, vec2<float> screenPos) override;
	virtual void onMouseUp(vec2<float> pos, vec2<float> screenPos) override;
	virtual void onMouseMove(vec2<float> pos, vec2<float> screenPos, vec2<float> delta) override;

	virtual void subscribe() override;
	virtual void unsubscribe() override;
protected:
	std::unordered_map<int64_t, std::shared_ptr<Object>> objects_ = {};
private:
	void spreadObjects();

	Justification justification_;
	vec2<float> gap_;
	bool scrollable_;

	std::shared_ptr<Tmpl8::Surface> drawingSurface;
	Scrollbar scrollbar_;
	vec2<float> scrollOffset = vec2(0.0f);
};