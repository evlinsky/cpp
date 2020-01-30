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

struct CheckingAccount : virtual BankAccount {
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

struct SavingsAccount : virtual BankAccount {
  SavingsAccount(double balance, double bonus)
    : BankAccount(balance), Bonus_(bonus) {}

  //void withdraw(double amount) override {}

  void add(double amount) {
    change_balance(amount * (1.0 + Bonus_));
  };
private:
  const double Bonus_;
};

struct PersonalAccount : CheckingAccount, SavingsAccount {
  PersonalAccount(const std::string &id, double overdraft, double bonus,
                  double balance = 0)
    : BankAccount(balance)
    , CheckingAccount(10e7, overdraft)
    , SavingsAccount(10e-7, bonus), Id(id) {}
  const std::string Id;
  /*
  void withdraw(double amount) override {
    CheckingAccount::withdraw(amount);
  }
  */
};

std::ostream& operator<<(std::ostream& os, const PersonalAccount &pa) {
  os << "[" << pa.Id << "]: ";
  os << pa.balance(); // no ambiguity
  return os;
}

bool has_money(const BankAccount &ba) {
  return 0 < ba.balance();
}

int main(int, char**) {
  PersonalAccount pa("Joe", 100, 0.1, 10);
  // [0] Casts
  BankAccount &ba = static_cast<BankAccount&>(pa); // no ambiguity
  std::cout << "Has money: " << has_money(ba) << std::endl;
  
  // [1] Ops
  std::cout << pa << std::endl;
  pa.withdraw(105);
  std::cout << pa << std::endl;
  pa.add(15);
  std::cout << pa << std::endl;
}
