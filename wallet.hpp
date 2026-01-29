#pragma once
#include "signal.hpp"

class Wallet {
public:
	int getCurrency();
	void addCurrency(int amount);
	bool requestPayment(int amount);

	Signal<int> currencyUpdated{};
private:
	int currency_ = 0;
};