#pragma once
#include "screen.hpp"
#include "button.hpp"
#include "screenSignals.hpp"
#include <vector>
#include <memory>

class StartScreen : public Screen {
public:
	StartScreen(Tmpl8::Surface* surface);

	void draw() override;
	void process() override;

	void subscribe() override;
	void unsubscribe() override;
private:
	std::vector<std::unique_ptr<Button>> buttons_ = {};
};