#pragma once
#include "container.hpp"
#include "button.hpp"

class Modal : public Container {
public:
	Modal(int64_t id, Tmpl8::vec2& pos, Tmpl8::vec2& size, std::function<void()> onExitHandler, Justification justification);

	void insertObject(std::unique_ptr<Object> object) override { innerContainer_.insertObject(std::move(object)); }

	template<typename T>
	T* getInnerObject(int64_t id) { return innerContainer_.getObject<T>(id); }
	std::map<int64_t, std::unique_ptr<Object>>::iterator begin() override { return innerContainer_.begin(); }
	std::map<int64_t, std::unique_ptr<Object>>::iterator end() override { return innerContainer_.end(); }

	virtual void draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) override;

	virtual void subscribe() override;
	virtual void unsubscribe() override;
private:
	Container innerContainer_;
	Button exitButton;
};