#include <cstdio>
#include <map>

struct Logger {
    virtual ~Logger() = default;

    virtual void log_transfer(long long from, long long to, double amount) const = 0;
};

struct ConsoleLogger : Logger {
    explicit ConsoleLogger(const char *name) : name{name} {}

    void log_transfer(long long from, long long to, double amount) const override {
        printf("%s [console] %lld -> %lld: %f\n", name, from, to, amount);
    }

private:
    const char *name;
};

struct HexLogger : Logger {
    void log_transfer(long long from, long long to, double amount) const override {
        printf("[hex] %llx -> %llx: %a\n", from, to, amount);
    }
};

struct FileLogger : Logger {
    void log_transfer(long long from, long long to, double amount) const override {
        printf("[file] %lld,%lld,%f\n", from, to, amount);
    }
};

struct AccountDatabase {
    virtual ~AccountDatabase() = default;

    [[nodiscard]] virtual double get_amount(long long id) = 0;

    virtual void set_amount(long long id, double new_amount) = 0;

    virtual void print_accounts() = 0;
};

struct InMemoryAccountDatabase : AccountDatabase {
    [[nodiscard]] double get_amount(long long id) override {
        return accounts[id];
    }

    void set_amount(long long id, double new_amount) override {
        accounts[id] = new_amount;
    }

    void print_accounts() override {
        for (auto account: accounts) {
            printf("Amount in %lld: %f\n", account.first, account.second);
        }
    }

private:
    std::map<long long, double> accounts;
};

struct Bank {
    Bank(Logger *logger, AccountDatabase *accountDatabase)
            : logger{logger}, accountDatabase{accountDatabase} {}

    void make_transfer(long long from, long long to, double amount) {
        if (logger) {
            logger->log_transfer(from, to, amount);
        }
        if (accountDatabase) {
            accountDatabase->set_amount(from, accountDatabase->get_amount(from) - amount);
            accountDatabase->set_amount(to, accountDatabase->get_amount(to) + amount);
        }
    }

    void set_logger(Logger *new_logger) {
        logger = new_logger;
    }

    [[nodiscard]] double get_amount(long long id) {
        return accountDatabase->get_amount(id);
    }

    void set_amount(long long id, double amount) {
        accountDatabase->set_amount(id, amount);
    }

    void set_accountDatabase(AccountDatabase *new_accountDatabase) {
        accountDatabase = new_accountDatabase;
    }

    void print_accountDatabase() {
        accountDatabase->print_accounts();
    }

private:
    Logger *logger{};
    AccountDatabase *accountDatabase{};
};

int main() {
    ConsoleLogger consoleLogger{"Logger 1"};
    FileLogger fileLogger;
    HexLogger hexLogger;

    InMemoryAccountDatabase inMemoryAccountDatabase;

    Bank bank{&consoleLogger, &inMemoryAccountDatabase};
    bank.make_transfer(3621, 3926, 420.69);

    bank.set_logger(&hexLogger);
    bank.make_transfer(1989, 1312, 0x9.8p0);

    bank.print_accountDatabase();
    return 0;
}
