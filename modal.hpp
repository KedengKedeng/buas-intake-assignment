#pragma once
#include "container.hpp"
#include "button.hpp"

class Modal : public Container {
public:
	Modal(int64_t id, Tmpl8::vec2& pos, Tmpl8::vec2& size, std::function<void()> onExitHandler, Justification justification);

	void insertObject(std::unique_ptr<Object> object) override { innerContainer_.insertObject(std::move(object)); }

	virtual void draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) override;

	virtual void subscribe() override;
	virtual void unsubscribe() override;
private:
	Container innerContainer_;
	Button exitButton;
};