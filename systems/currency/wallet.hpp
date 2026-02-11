#pragma once

class Wallet {
public:
	int getCurrency() const;
	void addCurrency(int amount);
	bool requestPayment(int amount);
private:
	int currency_ = 0;
};