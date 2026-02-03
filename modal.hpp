#pragma once
#include "container.hpp"
#include "button.hpp"

class Modal : public Container {
public:
	Modal(
		int64_t id,
		vec2<float>& pos,
		vec2<float>& size,
		std::function<void()> onExitHandler,
		Justification justification,
		vec2<float>& gap,
		bool scrollable = false
	);

	void insertObject(std::shared_ptr<Object> object) override { innerContainer_.insertObject(std::move(object)); }

	vec2<float> getPadding();

	template<typename T>
	std::shared_ptr<T> getInnerObject(int64_t id) { return innerContainer_.getObject<T>(id); }
	std::unordered_map<int64_t, std::shared_ptr<Object>>::iterator begin() override { return innerContainer_.begin(); }
	std::unordered_map<int64_t, std::shared_ptr<Object>>::iterator end() override { return innerContainer_.end(); }

	virtual void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override;
	virtual void process(float deltaTime) override;

	virtual void subscribe() override;
	virtual void unsubscribe() override;
private:
	Container innerContainer_;
	Button exitButton;
};