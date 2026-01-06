#pragma once
#include "object.hpp"
#include "boundingBox.hpp"
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

	virtual void draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) override;
	virtual void process(float deltaTime) override;

	virtual void insertObject(std::unique_ptr<Object> object);
	void clearObjects() { objects_.clear(); }

	template<typename T>
	T* getObject(int64_t id) { return dynamic_cast<T*>(objects_[id].get()); }
	virtual std::map<int64_t, std::unique_ptr<Object>>::iterator begin() { return objects_.begin(); }
	virtual std::map<int64_t, std::unique_ptr<Object>>::iterator end() { return objects_.end(); }

	virtual void subscribe() override;
	virtual void unsubscribe() override;
protected:
	std::map<int64_t, std::unique_ptr<Object>> objects_ = {};
private:
	void spreadObjects();

	Justification justification_;
};