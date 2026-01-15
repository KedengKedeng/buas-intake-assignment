#pragma once
#include "object.hpp"
#include "vec2.hpp"
#include <map>
#include <memory>

enum class Justification {
	NONE,
	VERTICAL,
	HORIZONTAL
};

class Container : public Object {
public:
	Container(
		int64_t id, 
		vec2<float>& pos, 
		vec2<float>& size,
		Justification justification
	);

	virtual void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override;
	virtual void process(float deltaTime) override;

	virtual void insertObject(std::shared_ptr<Object> object);
	void clearObjects() { objects_.clear(); }

	template<typename T>
	std::shared_ptr<T> getObject(int64_t id) { return std::dynamic_pointer_cast<T>(objects_[id]); }
	virtual std::map<int64_t, std::shared_ptr<Object>>::iterator begin() { return objects_.begin(); }
	virtual std::map<int64_t, std::shared_ptr<Object>>::iterator end() { return objects_.end(); }

	virtual void subscribe() override;
	virtual void unsubscribe() override;
protected:
	std::map<int64_t, std::shared_ptr<Object>> objects_ = {};
private:
	void spreadObjects();

	Justification justification_;
};