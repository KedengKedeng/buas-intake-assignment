#pragma once
#include "screen.hpp"
#include "player.hpp"
#include "inventory.hpp"

class PlayScreen : public Screen {
public:
	PlayScreen(Tmpl8::Surface* surface, std::shared_ptr<Inventory> inventory);
	~PlayScreen();

	void deleteObject(int64_t id);

	void process() override;
	void draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) override;

	void subscribe() override;
	void unsubscribe() override;
private:
	Player player_;
	std::shared_ptr<Inventory> inventory_;

	std::function<void()> deleteObjectSignalUnsub = []() {};
	std::function<void()> itemPickedUpUnsub = []() {};
	std::function<void()> interactionSignalUnsub = []() {};
	std::function<void()> requestMoveUnsub = []() {};
	std::function<void()> escapePressedUnsub = []() {};
	std::function<void()> cauldronInteractedUnsub = []() {};
};