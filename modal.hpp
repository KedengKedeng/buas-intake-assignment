#pragma once
#include "objectContainer.hpp"
#include "button.hpp"

class Modal : public Object, public Clickable, public SubscriptionManager {
public:
	Modal(
		int64_t id,
		vec2<float> pos,
		vec2<float> size,
		std::function<void()> onExitHandler,
		Justification justification,
		vec2<float> gap,
		bool scrollable = false
	);

	~Modal();

	void insertObject(std::shared_ptr<Object> object) { innerContainer_.insertObject(std::move(object)); }
	void clearObjects() { innerContainer_.clearObjects(); }

	vec2<float> getPadding() const;

	template<typename T>
	std::shared_ptr<T> getInnerObject(int64_t id) const { return innerContainer_.getObject<T>(id); }
	std::unordered_map<int64_t, std::shared_ptr<Object>>::iterator begin() { return innerContainer_.begin(); }
	std::unordered_map<int64_t, std::shared_ptr<Object>>::iterator end() { return innerContainer_.end(); }

	virtual void onMouseDown(vec2<float> pos, vec2<float> screenPos) override;
	virtual void onMouseUp(vec2<float> pos, vec2<float> screenPos) override;
	virtual void onMouseMove(vec2<float> pos, vec2<float> screenPos, vec2<float> delta) override;

	virtual void draw(Tmpl8::Surface* surface, vec2<float> offset) const override;
	virtual void process(float deltaTime) override;

	virtual void subscribe() override;
	virtual void unsubscribe() override;
private:
	ObjectContainer innerContainer_;
	Button exitButton;
};