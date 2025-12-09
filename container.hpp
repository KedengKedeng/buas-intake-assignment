#pragma once
#include "object.hpp"
#include <map>

enum class Justification {
	NONE,
	VERTICAL,
	HORIZONTAL
};

class Container : public Object {
public:
	Container(
		int64_t id, 
		Tmpl8::vec2& pos, 
		Tmpl8::vec2& size,
		Justification justification
	);

	virtual void draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) override;
	virtual void process() override;
	virtual void insertObject(std::unique_ptr<Object> object);

	virtual void subscribe() override;
	virtual void unsubscribe() override;
protected:
	std::map<int64_t, std::unique_ptr<Object>> objects_ = {};
private:
	void spreadObjects();
	Justification justification_;
};