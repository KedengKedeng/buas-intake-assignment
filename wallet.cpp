#include "wallet.hpp"

int Wallet::getCurrency() {
	return currency_;
}

void Wallet::addCurrency(int amount) {
	currency_ += amount;
	currencyUpdated.emit(currency_);
}

bool Wallet::requestPayment(int amount) {
	if (amount < currency_) return false;
	currency_ -= amount;
	currencyUpdated.emit(currency_);
	return true;
}