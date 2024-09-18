#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <limits>
#include <iomanip>

struct Transaction{
    std::string type;
    std::string category;
    std::string description;
    double amount;
    std::string data;
};

class ExpensesTracker{
    private:
        std::vector<Transaction> transactions;
        double totalIncome = 0.0;
        double totalExpenses = 0.0;
        double budget = 0.0;

        std::string getCurrentDate(){
            time_t now = time(0);
            tm *ltm = localtime(&now);
            std::stringstream ss;
            ss << std::setfill('0') << std::setw(2) << ltm->tm_mday << "/"
               << std::setw(2) << 1 + ltm->tm_mon << "/"
               << 1900 + ltm->tm_year;
            return ss.str();
        }
    
    public:
        void setBudget(double amount){
            budget = amount;
            std::cout << "Budget set to $" << budget << std::endl;
        }
        void addIncome(double amount){
            Transaction t = {"Income", "N/A", "Income", amount, getCurrentDate()};
            transactions.push_back(t);
            totalIncome += amount;
            std::cout << "Income of $" << amount << " added successfully!" << std::endl;
        }
        void addExpense(std::string category, std::string description, double amount){
            Transaction t = {"Expense", category, description, amount, getCurrentDate()};
            transactions.push_back(t);
            totalExpenses += amount;
            std::cout << "Expense \"" << description << "\" of $" << amount << " added successfully!" << std::endl;

            if(totalExpenses > budget){
                std::cout << "Warning: You have exceeded your budget!" << std::endl;
            }
        }
        void viewBalance(){
            double balance = totalIncome - totalExpenses;
            std::cout << "Your current balance is: $" << balance << std::endl;
        }
        void viewTransactionHistory(){
            std::cout << "\nTransaction History\n";
            std::cout << "----------------------------\n";
            for(const auto& t : transactions){
                std::cout << t.data << " - " << t.type << ": $" << t.amount;
                if(t.type == "Expense"){
                    std::cout << " (" << t.category << ": $" << t.description << ")";
                }
                std::cout << std::endl;
            }
        }
        void generateMonthlyReport(int month, int year){
            double monthlyIncome = 0.0;
            double monthlyExpense = 0.0;
            std::string monthStr = (month < 10) ? "0" + std::to_string(month) : std::to_string(month);
            std::string yearStr = std::to_string(year);

            for(const auto& t : transactions){
                if(t.data.substr(3, 2) == monthStr && t.data.substr(6, 4) == yearStr){
                    if(t.type == "Income"){
                        monthlyIncome += t.amount;
                    }
                    else if(t.type == "Expense"){
                        monthlyExpense += t.amount;
                    }
                }
            }

            std::cout << "\nMonthly Report for " << monthStr << "/" << yearStr << ":\n";
            std::cout << "---------------------------------\n";
            std::cout << "Total Income: $" << monthlyIncome << std::endl;
            std::cout << "Total Expenses: $" << monthlyExpense << std::endl;
            std::cout << "Balance: $" << (monthlyIncome - monthlyExpense) << std::endl;
        }

};

int main(){

    ExpensesTracker tracker;
    int choice;

    do{
        std::cout << "\n--------------------------\n";
        std::cout << "Personal Expense tracker";
        std::cout << "\n--------------------------\n";
        std::cout << "\n1. Set Budget";
        std::cout << "\n2. Add Income";
        std::cout << "\n3. Add Expenses";
        std::cout << "\n4. View Balance";
        std::cout << "\n5. View Transaction History";
        std::cout << "\n6. Generate Monthly report";
        std::cout << "\n7. Exit";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

         switch (choice) {
            case 1: {
                double budget;
                std::cout << "Enter your monthly budget: $";
                std::cin >> budget;
                tracker.setBudget(budget);
                break;
            }
            case 2: {
                double amount;
                std::cout << "Enter income amount: $";
                std::cin >> amount;
                tracker.addIncome(amount);
                break;
            }
            case 3: {
                std::string category, description;
                double amount;
                std::cout << "Enter expense category (Food, Transportation, Utilities, etc.): ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, category);
                std::cout << "Enter expense description: ";
                std::getline(std::cin, description);
                std::cout << "Enter expense amount: $";
                std::cin >> amount;
                tracker.addExpense(category, description, amount);
                break;
            }
            case 4:
                tracker.viewBalance();
                break;
            case 5:
                tracker.viewTransactionHistory();
                break;
            case 6: {
                int month, year;
                std::cout << "Enter month (1-12): ";
                std::cin >> month;
                std::cout << "Enter year (YYYY): ";
                std::cin >> year;
                tracker.generateMonthlyReport(month, year);
                break;
            }
            case 7:
                std::cout << "Exiting the program. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 7);
    return 0;
}