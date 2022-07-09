#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class ATM
{
private:
  // vector variable to store the names users whose cards have been registered
  vector<string> usersNames;
  // vector variable to store the corresponding users cards numbers
  vector<unsigned long long> usersCardNumbers;
  // vector variable to store the corresponding cards numbers pins
  vector<int> usersPins;
  // vector variable to store the corresponding users cards balance
  vector<float> userAccountBalance;
  // variables to help us iterate through the registered cards and also performs some validations
  int cardIndex = 0, pinIndex = 0;

public:
  // Function to register card
  void addCardDetails();
  // Function to allow already registered card to access various operations like check balance, deposit, etc.
  void login();
  // Function that display a menu
  void accountMenu();
  // Function that checks the validity of the user name(i.e the argument pass to it), i.e it ensures the user name contains only alphabets and maybe one hyphen(-) 
  void isValidName(string &);
  // Function that checks validity the argument pass to it, i.e it ensures the argument contains only numbers
  void isDigit(string &);
  // Function that displays a menu 
  void mainMenu();
  // Function that exit the program
  void exitMenu();
  // Fucntion that takes the program back to the accountMenu() function
  void Back();
  // Function that displays users account balance
  void checkBalance();
  // Function that allow the card user to deposit some amount into his or her account
  void deposit();
  // Function that allow the card user to withdraw some amount from his or her account
  void withdraw();
  // Function that  allow the card user to transfer some amount from his or her account to different registered account
  void transfer();
  // Function that checks the validity of the amount entered by the user.
  void isValidAmount(string &);
  // Function to display error message if the length of the card number is less than or greater than the expected length
  void isInvalidCardLength(const string);
  // Function to display error message if the length of the pin is less than or greater than the expected length
  void isInvalidPinLength(const string);
  // Declaring classs destructor
  ~ATM();
};

void ATM::isInvalidCardLength(const string number)
{
  if (number.length() < 10)
      {
        system("cls");
        cout << "ERROR: Card number length cannot be less than 10\n";
      }
      if (number.length() > 10)
      {
        system("cls");
        cout << "ERROR: Card number length cannot be greater than 10\n";
      }
}

void ATM::isInvalidPinLength(string pin)
{
  if (pin.length() < 4)
      {
        system("cls");
        cout << "ERROR: Pin length cannot be less than 4\n";
      }
      if (pin.length() > 4)
      {
        system("cls");
        cout << "ERROR: Pin length cannot be greater than 4\n";
      }
}

void ATM::accountMenu()
{
  system("cls");
  string option;
  cout << "**********MENU**********" << endl
       << "* 1. Add Card Details  *" << endl
       << "* 2. Login Account     *" << endl
       << "* 0. Exit Menu         *" << endl
       << "************************" << endl;

  do
  {
    cout << "Enter option... ";
    getline(cin >> ws, option);
    if (option != "0" && option != "1" && option != "2")
      cout << "Invalid option\n";
  } while (option != "0" && option != "1" && option != "2"); // Ensures the user enter a valid option, i.e either 1, 2, or 0.
  if (option == "1")
    addCardDetails(); // Calling the addCardDetails function if the user enter 1
  else if (option == "2")
    login(); // Calling the login function if the user enter 2
  else
    exitMenu(); // Calling the exitMenu function is the user enter 0
}

void ATM::addCardDetails()
{
  system("cls");
  string number, pin, name;
  unsigned long long card_num;
  int pin_num, pinNum;
  bool cardNumberAlreadyExist;
  do
  {
    cout << "Enter user name... ";
    getline(cin >> ws, name);
    isValidName(name);
    if (name.length() < 3)
    {
      system("cls");
      cout << "User name length cannot be less than 3\n";
    }
    if (name.length() > 30)
    {
      system("cls");
      cout << "User name length cannot be greater than 30\n";
    }
  } while (name.length() < 3 || name.length() > 30); // Ensures that the length of user name is neither less than 3 nor greater than 30
  usersNames.push_back(name);  // adding name to the vector variable usersNames using the the push_back member function of string class
  system("cls");
  do
  {
    cardNumberAlreadyExist = false;
    do
    {
      cout << "Enter card number(must contain 10 digits)... ";
      getline(cin >> ws, number);
      isDigit(number);
      isInvalidCardLength(number);
    } while (number.length() < 10 || number.length() > 10); // Ensures that the user enter exactly 10 digits
    card_num = stoull(number); // Convert number of string type to unsigned long long using stoull and stores it in card_num of unsigned long long type
    if (cardIndex == 0) // This condition ensures that there is no check for existing card number at first registration of card number
      break;
    else
    {
      for (int index = 0; index < cardIndex; index++)
      {
        if (card_num == usersCardNumbers[index])
        {
          system("cls");
          cout << "Card Number has already been registered\n";
          cardNumberAlreadyExist = true;
          break;
        }
      }
    }
  } while (cardNumberAlreadyExist); // ensures that the user enter card number that has not been registered yet
  usersCardNumbers.push_back(card_num);

  do
  {
    system("cls");
    do
    {
      cout << "Enter your four digit pin... ";
      getline(cin >> ws, pin);
      isDigit(pin);
      isInvalidPinLength(pin);
    } while (pin.length() < 4 || pin.length() > 4); // ensures user enter exactly four digits
    pin_num = stoi(pin); // conver pin of string type to integer with the help of the stoi and stores it in the pin_num of int type
    system("cls");
    // checks whether the user is familiar with the pin He or She is using to setup his or her card pin
    do
    {
      cout << "Enter the 4 digit pin again to confirm... ";
      getline(cin >> ws, pin);
      isDigit(pin);
      isInvalidPinLength(pin);
    } while (pin.length() < 4 || pin.length() > 4);
    pinNum = stoi(pin);
    if (pin_num != pinNum)
    {
      system("cls");
      cout << "ERROR: The pin does not match\n";
      system("PAUSE");
    }
  } while (pin_num != pinNum); // ensures that the user enters pins which match before he or she can continue the process
  usersPins.push_back(pin_num);
  userAccountBalance.push_back(1000); // Initially deposited $1000 to card which has been register
  cardIndex += 1; // increasing the cardIndex to help stores information about users seperately;
  accountMenu();
}

void ATM::isValidName(string &user_name)
{
  bool isValidName = false;
  while (!isValidName) // ensures the user enters a valid name
  {
    isValidName = true;
    int hyphen = 0;
    for (int y = 0; y < user_name.length(); y++)
    {
      if (!(isalpha(user_name[y]) || user_name[y] == ' ' || user_name[y] == '-'))
      {
        isValidName = false;
        break;
      }
      if (user_name[y] == '-')
        hyphen++;
    }
    if (hyphen > 1)
      isValidName = false;
    if (!isValidName)
    {
      system("cls");
      cout << "ERROR : Name can only contains alphabets\nEnter user name again... ";
      getline(cin >> ws, user_name);
    }
  }
}

void ATM::isDigit(string &score)
{
  bool isInteger = false;
  while (!isInteger) // ensures the user enters a valid number
  {
    isInteger = true;
    for (int i = 0; i < score.length(); i++)
    {
      if (!isdigit(score[i]))
      {
        isInteger = false;
        break;
      }
    }
    if (!isInteger)
    {
      system("cls");
      cout << "ERROR: invalid number\n";
      cout << "Enter number...";
      getline(cin >> ws, score);
    }
  }
}

void ATM::login()
{
  system("cls");
  string number, pin;
  unsigned long long card_num;
  int pin_num, counter = 3;
  bool cardNumberAlreadyExist, isPinValid = 0;
  do
  {
    system("cls");
    cout << "You have " << counter << " attempts" << endl; // prompting the user about the number of chances he or she can attempt for that operation
    cardNumberAlreadyExist = 0;
    do
    {
      cout << "Enter card number(must contain 10 digits)... ";
      getline(cin >> ws, number);
      isDigit(number);
      isInvalidCardLength(number);
    } while (number.length() < 10 || number.length() > 10);
    card_num = stoull(number);
    for (int index = 0; index < cardIndex; index++)
    {
      if (card_num == usersCardNumbers[index])
      {
        cardNumberAlreadyExist = 1;
        pinIndex = index;  // assigning index to pinIndex in order to know the card the user is trying to use to login. 
        break;
      }
    }
    if (!cardNumberAlreadyExist)
    {
      cout << "ERROR: Card number has not been registered\n";
      system("PAUSE");
    }
    --counter;
  } while (!cardNumberAlreadyExist && counter > 0); // ensures the user does not login in with unregistered card
  system("cls");
  if (cardNumberAlreadyExist) // This block of codes will be executed if the user enters a register card number
  {
    for (int i = 3; i > 0; i--)
    {
      cout << "You have " << i << " attempts\n";
      isPinValid = 0;
      do
      {
        cout << "Enter your 4 digit pin... ";
        getline(cin >> ws, pin);
        isDigit(pin);
        isInvalidPinLength(pin);
      } while (pin.length() < 4 || pin.length() > 4);
      pin_num = stoi(pin);
      if (pin_num == usersPins[pinIndex]) // checks whether the user has enter a valid pin than correspond to the card number with the help of pinIndex
      {
        isPinValid = 1;
        break;
      }
      else
      {
        system("cls");
        cout << "ERROR: Invalid Pin\n";
      }
    }

    if (isPinValid)
      mainMenu(); // calling the mainMenu function if the user enters a valid pin that correspond to the card number used
    else
      accountMenu(); // calling the accountMenu function if the user fails to enter a valid pin that correspond to the card number used
  }
  else
    accountMenu(); // calling the accountMenu function if the user fails to enter a regustered card number
}

void ATM::mainMenu()
{
  system("cls");
  string option;
  int opt;
  cout << "**********MENU**********" << endl
       << "*   1. Check Balance   *" << endl
       << "*   2. Deposit         *" << endl
       << "*   3. Withdraw        *" << endl
       << "*   4. Transfer        *" << endl
       << "*   0. Back            *" << endl
       << "************************" << endl;
  do
  {
    cout << "Enter option... ";
    getline(cin >> ws, option);
    if (option != "0" && option != "1" && option != "2" && option != "3" && option != "4")
      cout << "Invalid option\n";
  } while (option != "0" && option != "1" && option != "2" && option != "3" && option != "4");
  opt = stoi(option);
  switch (opt)
  {
  case 1:
    checkBalance();
    break;
  case 2:
    deposit();
    break;
  case 3:
    withdraw();
    break;
  case 4:
    transfer();
    break;

  default:
    Back();
    break;
  }
}

void ATM::checkBalance()
{
  system("cls");
  cout << usersNames[pinIndex] << " your balance is : $" << fixed << setprecision(2) << userAccountBalance[pinIndex] << endl
       << "Press any key to continue...";
  cin.get();
  mainMenu();
}

void ATM::isValidAmount(string &amt)
{
  bool isValidAmount = 0;
  while (!isValidAmount)
  {
    isValidAmount = 1;
    int dot_count = 0;
    for (int i = 0; i < amt.length(); i++)
    {
      if (!isdigit(amt[i]) && amt[i] != '.' && amt[i] != '+' && amt[i] != '-')
      {
        isValidAmount = 0;
        break;
      }
      if (amt[i] == '.')
        dot_count += 1;

      if (i == 0)
        continue;
      else
      {
        if (amt[i] == '+' || amt[i] == '-' || dot_count > 1)
        {
          isValidAmount = 0;
          break;
        }
      }
    }
    if (amt == "-" || amt == "+" || amt == ".")
      isValidAmount = 0;
    if (!isValidAmount)
    {
      system("cls");
      cout << "ERROR : Invalid amount\nEnter amount again... ";
      getline(cin, amt);
    }
  }
}

void ATM::deposit()
{
  system("cls");
  string amount;
  float cashDeposited;
  do
  {
    cout << "Enter amount you want to deposit... ";
    getline(cin >> ws, amount);
    isValidAmount(amount);
    cashDeposited = stof(amount);
    if (cashDeposited < 1)
    {
      system("cls");
      cout << "ERROR: amount cannot be less than $1.00\n";
    }
  } while (cashDeposited < 1);
  userAccountBalance[pinIndex] += cashDeposited; // updating user account balance after the operation
  system("cls");
  cout << "Congratulation " << usersNames[pinIndex] << ',' << endl
       << "You have succesfully deposited an amount of $" << fixed << setprecision(2) << cashDeposited << " to your account." << endl
       << "Your current balance is $" << userAccountBalance[pinIndex] << endl
       << "Press any key to continue...";
  cin.get();
  mainMenu();
}

void ATM::withdraw()
{
  system("cls");
  if (userAccountBalance[pinIndex] > 0)
  {
    string amount;
    float cashWithdraw;
    do
    {
      cout << "Enter amount you want to withdraw... ";
      getline(cin >> ws, amount);
      isValidAmount(amount);
      cashWithdraw = stof(amount);
      if (cashWithdraw < 1)
      {
        system("cls");
        cout << "ERROR: amount cannot be less than $1.00\n";
      }
      if (cashWithdraw > userAccountBalance[pinIndex])
      {
        system("cls");
        cout << "ERROR: Amount cannot be greater than account balance\n";
      }
    } while (cashWithdraw < 1 || cashWithdraw > userAccountBalance[pinIndex]); // ensures that the user enters a valid amount which is not more than current balance
    string pin;
    int pin_num;
    bool isPinValid;
    for (int i = 3; i > 0; i--) // This block of code inside this loop ensures that is the actual user who is performing the operation by requesting for the user pin
    {
      cout << "You have " << i << " attempts\n";
      isPinValid = 0;
      do
      {
        cout << "Enter your 4 digit pin to confirm the operation... ";
        getline(cin >> ws, pin);
        isDigit(pin);
        isInvalidPinLength(pin);
      } while (pin.length() < 4 || pin.length() > 4);
      pin_num = stoi(pin);
      if (pin_num == usersPins[pinIndex])
      {
        isPinValid = 1;
        break;
      }
      else
      {
        system("cls");
        cout << "ERROR: Invalid Pin\n";
      }
    }
    if (isPinValid)
    {
      userAccountBalance[pinIndex] -= cashWithdraw; // updating user account balance after the operation
      system("cls");
      cout << "Congratulation " << usersNames[pinIndex] << ',' << endl
           << "You have succesfully withdraw an amount of $" << fixed << setprecision(2) << cashWithdraw << " from your account." << endl
           << "Your current balance is $" << userAccountBalance[pinIndex] << endl
           << "Press any key to continue...";
      cin.get();
    }
    else
      accountMenu();
  }
  else
  {
    system("cls");
    cout << "Sorry " << usersNames[pinIndex] << ',' << endl
         << "Your balance is insufficient for this operation" << endl
         << "Press any key to continue...";
    cin.get();
  }
  mainMenu();
}

void ATM::transfer()
{
  system("cls");
  if (userAccountBalance[pinIndex] > 0)
  {
    string number;
    unsigned long long card_num;
    int pin_index;
    bool cardNumberAlreadyExist, isPinValid;
    int count = 0;

    do
    {
      cardNumberAlreadyExist = false;
      do
      {
        cout << "Enter card number you want to transfer the money to... ";
        getline(cin >> ws, number);
        isDigit(number);
        isInvalidCardLength(number);
      } while (number.length() < 10 || number.length() > 10);
      card_num = stoull(number);
      for (int index = 0; index < cardIndex; index++)
      {
        pin_index = -1;
        if (card_num == usersCardNumbers[index])
        {
          cardNumberAlreadyExist = true;
          pin_index = index;
          break;
        }
      }
      if (!cardNumberAlreadyExist)
      {
        system("cls");
        cout << "ERROR: The card number you are trying to send money to has not been registered yet\n";
      }
      if(card_num == usersCardNumbers[pinIndex])
      {
        system("cls");
        cout << "Sorry "<<usersNames[pinIndex]<<','<<endl
             <<"You can't transfer money to yourself"<<endl;
      }
      ++count;
      if(count == 3 && (!cardNumberAlreadyExist  || (card_num == usersCardNumbers[pinIndex]))) 
        system("PAUSE");
    } while ((!cardNumberAlreadyExist  || (card_num == usersCardNumbers[pinIndex])) && count < 3);// ensures that the user don't transfer money to himself or herself or to unregistered card
    system("cls");
    if (cardNumberAlreadyExist && (card_num != usersCardNumbers[pinIndex])) // ensures that the registered card number entered by the user is not the same as his or her card number, before the block of codes under it is executed
    {
      string amount;
      float cashTransfer;
      do
      {
        cout << "Enter amount you want to transfer... ";
        getline(cin >> ws, amount);
        isValidAmount(amount);
        cashTransfer = stof(amount);
        if (cashTransfer < 1)
        {
          system("cls");
          cout << "ERROR: amount cannot be less than $1.00\n";
        }
        if (cashTransfer > userAccountBalance[pinIndex])
        {
          system("cls");
          cout << "ERROR: Amount cannot be greater than account balance\n";
        }
      } while (cashTransfer < 1 || cashTransfer > userAccountBalance[pinIndex]);
      system("cls");
      string select;
      cout << usersNames[pinIndex] << " are you sure you want to tranfer an amount of \n$"
           << fixed << setprecision(2) << cashTransfer << " to " << usersNames[pin_index] << endl
           << "1. YES" << endl
           << "2. NO" << endl;
      do
      {
        cout<<"Enter choice... ";
        getline(cin >> ws, select);
        if (select != "1" && select != "2")
        {
          cout << "ERROR: Invalid choice\n";
        }
      } while (select != "1" && select != "2");
      if (select == "1")
      {
        system("cls");
        string pin;
        int pin_num;
        for (int i = 3; i > 0; i--)
        {
          cout << "You have " << i << " attempts\n";
          isPinValid = 0;
          do
          {
            cout << "Enter your 4 digit pin to confirm the operation... ";
            getline(cin >> ws, pin);
            isDigit(pin);
            isInvalidPinLength(pin);
          } while (pin.length() < 4 || pin.length() > 4);
          pin_num = stoi(pin);
          if (pin_num == usersPins[pinIndex])
          {
            isPinValid = 1;
            break;
          }
          else
          {
            system("cls");
            cout << "ERROR: Invalid Pin\n";
          }
        }
        if (isPinValid)
        {
          userAccountBalance[pinIndex] -= cashTransfer;
          userAccountBalance[pin_index] += cashTransfer;
          system("cls");
          cout << "Congratulation " << usersNames[pinIndex] << ',' << endl
               << "You have succesfully transfer an amount of $" << fixed << setprecision(2) << cashTransfer << " from your account to" << endl
               << usersNames[pin_index] << ", your current balance is $" << userAccountBalance[pinIndex] << endl
               << "Press any key to continue...";
          cin.get();
        }
        else
          accountMenu();
      }
      else
        mainMenu();
    }
  }
  else
  {
    system("cls");
    cout << "Sorry " << usersNames[pinIndex] << ',' << endl
         << "Your balance is insufficient for this operation" << endl
         << "Press any key to continue...";
    cin.get();
  }
  mainMenu();
}

void ATM::Back()
{
  accountMenu();
}

void ATM::exitMenu()
{
  system("cls");
  cout << "*************************************************" << endl
       << "*  THANKS FOR USING HACKERSGODDEST ATM MACHINE  *" << endl
       << "*************************************************" << endl
       << "Press any key to continue...";
  cin.get();
  exit(0); // terminates the program
}

ATM::~ATM()
{
  // deleting various information stored in the variables
  usersNames.clear(), userAccountBalance.clear(), usersCardNumbers.clear(), usersPins.clear();
  cardIndex = pinIndex = 0;
}

int main()
{
  // created a pointer object that is dynamically allocated
  ATM *account = new ATM;
  account->accountMenu();
  //deallocating pointer object
  delete account;
  account = nullptr;
  return 0;
}