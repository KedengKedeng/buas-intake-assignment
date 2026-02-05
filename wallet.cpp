#include "wallet.hpp"

int Wallet::getCurrency() const {
	return currency_;
}

void Wallet::addCurrency(int amount) {
	currency_ += amount;
}

bool Wallet::requestPayment(int amount) {
	if (amount < currency_) return false;
	currency_ -= amount;
	return true;
}