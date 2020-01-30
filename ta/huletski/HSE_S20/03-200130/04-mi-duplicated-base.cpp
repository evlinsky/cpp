#include <iostream>

struct BankAccount {
  BankAccount(double balance) : balance_(balance) {}
  virtual ~BankAccount() {}
  BankAccount& operator=(const BankAccount &) = delete;
  BankAccount(const BankAccount &) = delete;

  virtual void withdraw(double amount) = 0;
  /*
  {
    if (amount <= balance_) {
      change_balance(-amount);
    }
  }
  */
  double balance() const { return balance_; }
protected:
  void change_balance(double delta) {
    balance_ += delta;
  }
private:
  double balance_;
};

struct CheckingAccount : BankAccount {
  CheckingAccount(double balance, double overdraft)
    : BankAccount(balance), Overdraft_(overdraft) {}

  void withdraw(double amount) override {
    if (amount <= balance() + Overdraft_) {
      change_balance(-amount);
    }
  }
private:
  const double Overdraft_;
};

struct SavingsAccount : BankAccount {
  SavingsAccount(double balance, double bonus)
    : BankAccount(balance), Bonus_(bonus) {}

  void add(double amount) {
    change_balance(amount * (1.0 + Bonus_));
  };
private:
  const double Bonus_;
};

struct PersonalAccount : CheckingAccount, SavingsAccount {
  PersonalAccount(const std::string &id, double overdraft, double bonus,
                  double balance = 0)
    : CheckingAccount(balance, overdraft)
    , SavingsAccount(balance, bonus), Id(id) {}
  const std::string Id;
  void withdraw(double amount) override { // NB: must override
    CheckingAccount::withdraw(amount);
  }
};

std::ostream& operator<<(std::ostream& os, const PersonalAccount &pa) {
  os << "[" << pa.Id << "]: ";
  //os << pa.balance(); // ambiguous, which balance?
  //os << pa.BankAccount::balance(); // abmiguous, which BankAccount?
  os << pa.CheckingAccount::balance();
  return os;
}

bool has_money(const BankAccount &ba) {
  return 0 < ba.balance();
}

int main(int, char**) {
  PersonalAccount pa("Joe", 100, 0.1, 10);
  // [0] Casts
  //CheckingAccount &ca = static_cast<CheckingAccount&>(pa); // ok
  //BankAccount &ba = static_cast<BankAccount&>(pa); // ambiguous
  //std::cout << "Has money: " << has_money(pa) << std::endl; // ambiguous
  std::cout << "Has money: " << has_money(static_cast<CheckingAccount&>(pa))
            << std::endl;
  
  // [1] Ops
  std::cout << pa << std::endl;
  pa.withdraw(105);
  std::cout << pa << std::endl;
  pa.add(15);
  std::cout << pa << std::endl;
}
