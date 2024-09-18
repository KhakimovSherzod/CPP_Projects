#include <iostream>
#include <ctime>
#include <iomanip>

double startGame(double &balance){
    
    int option;
    int guess;
    
    std::cout << "\nChoose difficulty level!: \n";
    std::cout << "1. Easy (1-10, 5 attempts, $100 price)\n";
    std::cout << "2. Medium (1-50, 4 attempts, $500 price)\n";
    std::cout << "3. Hard (1-100, 3 attempts, $1000 price)\n";

    std::cout << "\nChoice (1-3): ";
    std::cin >> option;

    srand(time(0));
    int num = rand() % 10 + 1;

    switch(option){
        case 1:
            if(balance >= 100){
                std::cout << "Guess the number between 1 and 10: \n";
                for(int i = 1; i < 6; i++){
                    std::cout << "Attempt " << i << ": ";
                    std::cin >> guess;

                    if(guess == num){
                        std::cout << "Congratulations! You guessed the right number.\n";
                        std::cout << "You win $100!\n";
                        balance += 100;
                        break;
                    }
                    else if(guess < num){
                        if(i == 5){
                            std::cout << "Oops! You Lost!\n";
                            balance -= 100;
                            break;
                        }
                        else{
                            std::cout << "Too Low! Try again.\n";
                        }
                    }
                    else if(guess > num){
                        if(i == 5){
                            std::cout << "Oops! You Lost!\n";
                            balance -= 100;
                            break;
                        }
                        else{
                            std::cout << "Too High! Try again.\n";
                        }
                    }
                }
            }
            else{
                std::cout << "Not enough money to play. Minimum required is $100!\n";
            }
            
            break;
        case 2:
            if(balance >= 500){
                std::cout << "Guess the number between 1 and 50: \n";
                for(int i = 1; i < 5; i++){
                    std::cout << "Attempt " << i << ": ";
                    std::cin >> guess;

                    if(guess == num){
                        std::cout << "Congratulations! You guessed the right number.\n";
                        std::cout << "You win $500!\n";
                        balance += 500;
                        break;
                    }
                    else if(guess < num){
                        if(i == 4){
                            std::cout << "Oops! You Lost!\n";
                            balance -= 500;
                            break;
                        }
                        else{
                            std::cout << "Too Low! Try again.\n";
                        }
                    }
                    else if(guess > num){
                        if(i == 4){
                            std::cout << "Oops! You Lost!\n";
                            balance -= 500;
                            break;
                        }
                        else{
                            std::cout << "Too High! Try again.\n";
                        }
                    }
                }
            }
            else{
                std::cout << "Not enough money to play. Minimum required is $500!\n";
            }
            
            break;
        case 3:
            if(balance >= 1000){
                std::cout << "Guess the number between 1 and 100: \n";
                for(int i = 1; i < 4; i++){
                    std::cout << "Attempt " << i << ": ";
                    std::cin >> guess;

                    if(guess == num){
                        std::cout << "Congratulations! You guessed the right number.\n";
                        std::cout << "You win $1000!\n";
                        balance += 1000;
                        break;
                    }
                    else if(guess < num){
                        if(i == 3){
                            std::cout << "Oops! You Lost!\n";
                            balance -= 1000;
                            break;
                        }
                        else{
                            std::cout << "Too Low! Try again.\n";
                        }
                    }
                    else if(guess > num){
                        if(i == 3){
                            std::cout << "Oops! You Lost!\n";
                            balance -= 1000;
                            break;
                        }
                        else{
                            std::cout << "Too High! Try again.\n";
                        }
                    }
                }
            }
            else{
                std::cout << "Not enough money to play. Minimum required is $1000!\n";
            }
            break;
        }

    std::cout << "Your balance is: $"<< std::setprecision(2) << std::fixed << balance;

    return balance;

}

void showBalance(double balance){

    std::cout << "Your balance is: $"<< std::setprecision(2) << std::fixed << balance;

}

void withdrawMoney(double &balance, double &bankBalance){

    int num;

    std::cout << "You have $"<< std::setprecision(2) << std::fixed << bankBalance;
    std::cout << "\nHow much would you like to withdraw?\n$";
    std::cin >> num;
    
    if(num > bankBalance){
        std::cout << "Not enough money in your bank account!\n";
    }
    else{
        bankBalance -= num;
        balance += num;
    }
}

void depositMoney(double &balance, double &bankBalance){

    int num;

    std::cout << "You have $"<< std::setprecision(2) << std::fixed << balance;
    std::cout << "\nHow much would you like to deposit to your bank account?\n$";
    std::cin >> num;

    if(num > balance){
        std::cout << "You don't have enough money in your balance!\n";
    }
    else{
        bankBalance += num;
        balance -= num;
    }

}

void checkBankStatus(double &bankBalance){

    std::cout << "Money in your bank: $" << std::setprecision(2) << std::fixed << bankBalance;

}


int main(){

    double balance = 100;
    double bankBalance = 1000;
    int option;
    std::cout << "\n$$$$$$$$$ Welcome To the Casino Guessing Number! $$$$$$$$$\n";
    do{
        
        std::cout << "\nChoose option: \n";
        std::cout << "1. Start the game\n";
        std::cout << "2. Check balance\n";
        std::cout << "3. Deposit money\n";
        std::cout << "4. Withdraw money\n";
        std::cout << "5. CheckBankStatus\n";
        std::cout << "0. Stop the game\n";

        std::cout << "Choice: ";
        std::cin >> option;

        switch(option){
            case 1:
                startGame(balance);
                break;
            case 2:
                showBalance(balance);
                break;
            case 3:
                depositMoney(balance, bankBalance);
                break;
            case 4:
                withdrawMoney(balance, bankBalance);
                break;
            case 5:
                checkBankStatus(bankBalance);
            default:
                break;
        }

    }while(option != 0);

    return 0;
}