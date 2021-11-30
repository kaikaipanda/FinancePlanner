#include <cstdio> // rename function: https://www.cplusplus.com/reference/cstdio/rename/  and remove function :https://www.cplusplus.com/reference/cstdio/remove/
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h> // for sleep timer: /*https://cboard.cprogramming.com/cplusplus-programming/37862-delay-int-milliseconds-visual-cplusplus.html (use in VS only)to change the color of text, clear screen and Sleep command but only use this on VS code*/

using namespace std;
void welcomePage(); // Jun Yong (text design), kailek (text colour cycle)
void userMenu(); //Jun Yong
void signUpPage(string information[], bool newMember, bool emailDomain); // kailek with reference to https://www.geeksforgeeks.org/how-to-return-multiple-values-from-a-function-in-c-or-cpp/

bool loginPage(bool validAcc, string username, string password, string checkUser, string checkPass); // kailek

string forgetPass(string checkUser, string checkPass, string newPass, string usernameCor, string emailCor); // kailek

double incomeTax(double income, double annualIncome); // kailek

void calculation(double nincome, string username);// Shaun, kailek
void calculations(string username, double nincome); //Shaun
void SpendingsTracker(double nincome, double income, string username); // JunYong
void endPage();											// shaun with reference to ASCIImoji,http://asciimoji.com/

int main() {
	string username, password, email, checkUser, checkPass, checkEmail, newPass, information[3], failRes, loginRes, usernameCor, emailCor, response, choice, responseIncome, date, d, m, y, dateNew;;
	int delay = 300, attempt = 1, age, number, incomeChoice, taxNo = 1, rmvReach = 1, recordRmv, rmvEOF = 0, editReach = 1, recordEdit, editEOF = 0, pos1, pos2, editRes, dInt, mInt, yInt, findPos1, findPos2, findPos3;;
	double income = 0, nincome = 0, cpf, cpfpercentage, annualIncome = 0, tax, incomeNew;;
	bool newMember = false, validAcc = false, validUser = false, emailDomain = false, keepUser = false;
	char oldname[] = "forgetpass.txt";
	char newname[] = "account.txt";
	char oldname2[] = "tempTaxfile.txt";

	ifstream inFile;
	ofstream outFile;
	welcomePage();
	inFile.open("account.txt");
	if (!inFile) {
		outFile.open("account.txt");
		if (!outFile) {
			cout << "Error\n";
		}
		else {
			signUpPage(information, newMember, emailDomain);
			email = information[0];
			username = information[1];
			password = information[2];
			outFile << email << "\t" << username << "\t" << password << endl;
			cout << "Creating account for " << username << "..." << endl;
		}
	}
	else {
		inFile.close();
		system("cls");
	startPage:
		cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
		cout << "$                                     $" << endl;
		cout << "$  WElLCOME TO SP BUDGET PLANNER 101  $" << endl;
		cout << "$                                     $" << endl;
		cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n" << endl;
		cout << "Choose a 1 or 2 to start using our app." << endl;
		cout << "1. Login" << endl;
		cout << "2. Sign Up" << endl;
		cout << "Choose choice 1 or 2: ";
		cin >> loginRes;
		while (loginRes != "1" && loginRes != "2") {
			system("cls");
			cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
			cout << "$                                     $" << endl;
			cout << "$  WElLCOME TO SP BUDGET PLANNER 101  $" << endl;
			cout << "$                                     $" << endl;
			cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n" << endl;
			cout << "Incorrect input. Please choose choice 1 or 2." << endl;
			cout << "1. Login" << endl;
			cout << "2. Sign Up" << endl;
			cout << "Choose choice 1 or 2: ";
			cin >> loginRes;
			system("cls");
		}

		if (loginRes == "1") {
			system("cls");
			cout << "=========================================================" << endl;
			cout << "**                      Login Page                     **" << endl;
			cout << "=========================================================" << endl << endl;
			inFile.open("account.txt");
			cout << "Username: ";
			cin >> checkUser;
			cout << "Password: ";
			cin >> checkPass;
			while (!inFile.eof()) {
				if (inFile.fail()) {
					break;
				}
				inFile >> email >> username >> password;
				validAcc = loginPage(
					validAcc, username, password, checkUser, checkPass);
				if (checkUser == username) {
					validUser = true;
					usernameCor = username;
					emailCor = email;
				}
				if (validAcc == true) {
					break;
				}
			}
			attempt = 1;
			while (validAcc == false && validUser == false) {
				system("cls");
				inFile.close();
				inFile.open("account.txt");
				cout << "=========================================================" << endl;
				cout << "**                      Login Page                     **" << endl;
				cout << "=========================================================" << endl << endl;
				cout << "Username and/or password is wrong." << endl
					<< "Please try again." << endl;
				cout << "Username: ";
				cin >> checkUser;
				cout << "Password: ";
				cin >> checkPass;
				while (!inFile.eof()) {
					if (inFile.fail()) {
						break;
					}
					inFile >> email >> username >> password;
					validAcc = loginPage(
						validAcc, username, password, checkUser, checkPass);
					if (checkUser == username) {
						validUser = true;
						usernameCor = username;
						emailCor = email;
					}
					if (validAcc == true) {
						break;
					}
				}
				if (attempt == 5) {
					attempt = 1;
					system("cls");
					goto startPage;
					break;
				}
				else {
					attempt++;
				}
				system("cls");
			}
			if (validAcc == false && validUser == true) {
				system("cls");
				cout << "=========================================================" << endl;
				cout << "**                      Login Page                     **" << endl;
				cout << "=========================================================" << endl << endl;
				cout << "We have detected that you have an existing account."
					<< endl
					<< "What would you wish to do ? " << endl
					<< "1. Reset password" << endl
					<< "2. Login" << endl
					<< "3. Sign Up" << endl;
				cout << "Choose choice 1 or 2 or 3: ";
				cin >> failRes;
				while (failRes != "1" && failRes != "2" && failRes != "3") {
					system("cls");
					cout << "=========================================================" << endl;
					cout << "**                      Login Page                     **" << endl;
					cout << "=========================================================" << endl << endl;
					cout << "Invalid response." << endl
						<< "Please try again." << endl
						<< "1. Reset password" << endl
						<< "2. Login" << endl
						<< "3. Sign Up" << endl;
					cout << "Choose choice 1 or 2 or 3: ";
					cin >> failRes;
				}
				if (failRes == "1") {
					system("cls");
					cout << "=========================================================" << endl;
					cout << "**                Forget Password Page                 **" << endl;
					cout << "=========================================================" << endl << endl;
					inFile.close();
					inFile.open("account.txt");
					newPass = forgetPass(checkUser, checkPass, newPass, usernameCor, emailCor);
					if (newPass.length() != 0) {
						keepUser = true;
						if (!inFile) {
							cout << "Error.\n";
						}
						else {
							outFile.close();
							outFile.open("forgetpass.txt", ofstream::app);
							if (!outFile) {
								cout << "Error\n" << endl;
							}
							else {
								while (!inFile.eof()) {
									if (inFile.fail()) {
										break;
									}
									inFile >> email >> username >> password;
									if (username.length() > 0 &&
										password.length() > 0) {
										if (email == emailCor && username == usernameCor) {
											outFile << email << "\t" << username
												<< "\t" << newPass << endl;
										}
										else {
											outFile << email << "\t" << username
												<< "\t" << password << endl;
										}
									}
									else {
										break;
									}
									email = "";
									username = "";
									password = "";
								}
							}
						}
					}
					else {
						system("cls");
						cout << "=========================================================" << endl;
						cout << "**                      Login Page                     **" << endl;
						cout << "=========================================================" << endl << endl;
						cout << "You have been denied from making a password reset." << endl
							<< "Please login to start using the app." << endl << endl;
						inFile.close();
						inFile.open("account.txt");
						cout << "Username: ";
						cin >> checkUser;
						cout << "Password: ";
						cin >> checkPass;
						system("cls");
						while (!inFile.eof()) {
							if (inFile.fail()) {
								break;
							}
							inFile >> email >> username >> password;
							validAcc = loginPage(validAcc, username, password, checkUser, checkPass);
							if (validAcc == true) {
								break;
							}
						}
						while (validAcc == false) {
							system("cls");
							cout << "=========================================================" << endl;
							cout << "**                      Login Page                     **" << endl;
							cout << "=========================================================" << endl << endl;
							inFile.close();
							inFile.open("account.txt");
							cout << "Username and/or password is wrong." << endl
								<< "Please try again." << endl;
							cout << "Username: ";
							cin >> checkUser;
							cout << "Password: ";
							cin >> checkPass;
							while (!inFile.eof()) {
								if (inFile.fail()) {
									break;
								}
								inFile >> email >> username >> password;
								validAcc = loginPage(validAcc, username, password, checkUser, checkPass);
								if (validAcc == true) {
									break;
								}
							}
							// system("cls");
						}
					}
				}
				else if (failRes == "2") {
					system("cls");
					cout << "=========================================================" << endl;
					cout << "**                      Login Page                     **" << endl;
					cout << "=========================================================" << endl << endl;
					inFile.close();
					inFile.open("account.txt");
					cout << "Username: ";
					cin >> checkUser;
					cout << "Password: ";
					cin >> checkPass;
					system("cls");
					while (!inFile.eof()) {
						if (inFile.fail()) {
							break;
						}
						inFile >> email >> username >> password;
						validAcc = loginPage(
							validAcc, username, password, checkUser, checkPass);
						if (validAcc == true) {
							break;
						}
					}
					while (validAcc == false) {
						inFile.close();
						inFile.open("account.txt");
						cout << "Username and/or password is wrong." << endl
							<< "Please try again." << endl;
						cout << "Username: ";
						cin >> checkUser;
						cout << "Password: ";
						cin >> checkPass;
						while (!inFile.eof()) {
							if (inFile.fail()) {
								break;
							}
							inFile >> email >> username >> password;
							validAcc = loginPage(validAcc, username, password, checkUser, checkPass);
							if (validAcc == true) {
								break;
							}
						}
						// system("cls");
					}
				}
				else {
					system("cls");
					cout << "=========================================================" << endl;
					cout << "**                    Sign Up Page                     **" << endl;
					cout << "=========================================================" << endl << endl;
					newMember = true;
					signUpPage(information, newMember, emailDomain);
					email = information[0];
					username = information[1];
					password = information[2];
				verifyEmail2:
					inFile.close();
					inFile.open("account.txt");
					if (!inFile) {
						cout << "Error\n";
					}
					else {
						while (!inFile.eof()) {
							if (inFile.fail()) {
								break;
							}
							inFile >> checkEmail >> checkUser >> checkPass;
							cout << email << "\t" << username << "\t" << password << endl;
							cout << checkEmail << "\t" << checkUser << "\t" << checkPass << endl;
							while (checkEmail == email || checkUser == username) {
								system("cls");
								cout << "=========================================================" << endl;
								cout << "**                    Sign Up Page                     **" << endl;
								cout << "=========================================================" << endl << endl;
								cout << "Email has been used." << endl;
								signUpPage(information, newMember, emailDomain);
								email = information[0];
								username = information[1];
								password = information[2];
								goto verifyEmail2;
							}
						}
					}
					inFile.close();
					outFile.open("account.txt", ofstream::app);
					if (outFile.fail()) {
						cout << "Error.\n";
					}

					outFile << email << "\t" << username << "\t" << password
						<< endl;
					cout << "Creating account for " << username << "..."
						<< endl;
				}
			}
		}

		else {
			system("cls");
			cout << "=========================================================" << endl;
			cout << "**                    Sign Up Page                     **" << endl;
			cout << "=========================================================" << endl << endl;
			newMember = true;
			signUpPage(information, newMember, emailDomain);
			email = information[0];
			username = information[1];
			password = information[2];
		verifyEmail:
			inFile.close();
			inFile.open("account.txt");
			if (!inFile) {
				cout << "Error\n";
			}
			else {
				while (!inFile.eof()) {
					if (inFile.fail()) {
						break;
					}
					inFile >> checkEmail >> checkUser >> checkPass;
					cout << email << "\t" << username << "\t" << password << endl;
					cout << checkEmail << "\t" << checkUser << "\t" << checkPass << endl;
					while (checkEmail == email || checkUser == username) {
						system("cls");
						cout << "=========================================================" << endl;
						cout << "**                    Sign Up Page                     **" << endl;
						cout << "=========================================================" << endl << endl;
						cout << "Email has been used." << endl;
						signUpPage(information, newMember, emailDomain);
						email = information[0];
						username = information[1];
						password = information[2];
						goto verifyEmail;
					}
				}
			}
			inFile.close();
			outFile.open("account.txt", ofstream::app);
			if (outFile.fail()) {
				cout << "Error.\n";
			}

			outFile << email << "\t" << username << "\t" << password
				<< endl;
			cout << "Creating account for " << username << "..."
				<< endl;
		}
	}
	inFile.close();
	outFile.close();

	if (keepUser == true) {
		username = usernameCor;
		if (remove("account.txt") != 0) {
		}
		else {
			if (rename(oldname, newname) == 0) {
			}
			else {
			}
		}
	}
	system("cls");
	cout << "Welcome back " << username << "." << endl;

Menu:             //Jun Yong with reference to https://iq.opengenus.org/goto-statement-in-cpp/
	userMenu();
	cout << "Enter your option: ";
	cin >> number;
	system("cls");

	if (number == 1)
	{
		inFile.open(username + "Income.txt");
		cout << fixed << setprecision(2);
		if (!inFile) {
			outFile.open(username + "Income.txt");
			if (!outFile) {
				cout << "Error\n";
			}
			else {
				cout << "Enter gross income : $";
				cin >> income;
				outFile << income << endl;
				outFile.close();
				outFile.open(username + "CPF.txt");
				if (!outFile) {
					cout << "Error\n";
				}
				else {
					cout << "Enter your age : " << endl;
					cin >> age;
					while (age < 0 || age > 100) {
						cout << "Invalid age entered. Please try again." << endl;
						cin >> age;
					}

					if (age <= 55)
					{
						cpf = income * (20.0 / 100);
						cpfpercentage = 20.0;
					}
					else if (age > 55 || age <= 60)
					{
						cpf = income * (13.0 / 100);
						cpfpercentage = 13.0;
					}
					else if (age > 60 || age <= 65)
					{
						cpf = income * (7.5 / 100);
						cpfpercentage = 7.5;
					}
					else
					{
						cpf = income * (5.0 / 100);
						cpfpercentage = 5.0;

					}
					nincome = income - cpf;
					cout << "\n************CPF Reductions************";
					cout << "\n\n";
					cout << " Percentage reduction : " << cpfpercentage << "%" << endl;
					cout << "CPF deducted from  gross income : $" << cpf << endl;
					cout << "Net income after CPF : $" << nincome << endl;
					cout << "\n\n";
					cout << "**************************************" << endl;
					outFile << nincome << endl;
					cout << "Saving data to file..." << endl;
					cout << "Press 8 and enter to return to Main Menu: ";
					cin >> number;
					if (number == 8)
					{
						inFile.close();
						outFile.close();
						system("cls");
						goto Menu;
					}
				}
			}
		}
		else {
			while (!inFile.eof()) {
				if (inFile.fail()) {
					break;
				}
				inFile >> income;
			}
			inFile.close();
			inFile.open(username + "CPF.txt");
			if (!inFile) {
				cout << "Error\n";
			}
			else {
				while (!inFile.eof()) {
					if (inFile.fail()) {
						break;
					}
					inFile >> nincome;
				}
			}
			if (nincome < 0)
				response = "no";

			else {
				cout << "The income saved previously into this program is $" << nincome
					<< endl
					<< endl;
				cout << "Do you want to use this net income that was used previously? (Type yes or no): ";
				cin >> response;
			}
			while (response != "no" && response != "No" && response != "yes" && response != "Yes") {
				system("cls");
				cout << "Invalid response. Please try again.\n\n";
				cout << "Do you want to use this net income that was used" << endl
					<< "previously? (Type yes or no): ";
				cin >> response;
			}
			system("cls");

			if (response == "yes" || response == "Yes")
			{
				outFile.open(username + "CPF.txt");
				cout << "Your previous Net income was : $" << nincome << endl;
				if (age <= 55)
				{
					cpf = income * (20.0 / 100);
					cpfpercentage = 20.0;
				}
				else if (age <= 60)
				{
					cpf = income * (13.0 / 100);
					cpfpercentage = 13.0;
				}
				else if (age <= 65)
				{
					cpf = income * (7.5 / 100);
					cpfpercentage = 7.5;
				}
				else
				{
					cpf = income * (5.0 / 100);
					cpfpercentage = 5.0;

				}
				cout << "************CPF Reductions************";
				cout << "\n";
				cout << endl << "Percentage reduction : " << cpfpercentage << "%" << endl;
				cout << " CPF deducted : $" << cpf << endl;
				cout << "\n";
				cout << "**************************************" << endl;
				outFile << nincome << endl;
				cout << "\n";
				cout << "Press 8 and enter to return to Main Menu: ";
				cin >> number;

				if (number == 8)
				{
					inFile.close();
					outFile.close();
					system("cls");
					goto Menu;
				}
			}


			else
			{
				outFile.close();
				outFile.open(username + "Income.txt");
				cout << "Enter gross income : $";
				cin >> income;
				outFile << income;
				outFile.close();
				outFile.open(username + "CPF.txt");
				cout << "Enter your age : ";
				cin >> age;
				while (age < 0 || age > 100) {
					cout << "Invalid age entered. Please try again." << endl;
					cin >> age;
				}

				if (age <= 55)
				{
					cpf = income * (20.0 / 100);
					cpfpercentage = 20.0;
				}
				else if (age <= 60)
				{
					cpf = income * (13.0 / 100);
					cpfpercentage = 13.0;
				}
				else if (age <= 65)
				{
					cpf = income * (7.5 / 100);
					cpfpercentage = 7.5;
				}
				else
				{
					cpf = income * (5.0 / 100);
					cpfpercentage = 5.0;

				}
				nincome = income - cpf;
				cout << endl << "************CPF Reductions************";
				cout << "\n\n";
				cout << " Percentage reduction : " << cpfpercentage << "%" << endl;
				cout << "CPF deducted from  gross income : $" << cpf << endl;
				cout << "Net income after CPF : $" << nincome << endl;
				cout << "\n\n";
				cout << "**************************************" << endl;
				outFile << nincome;
				cout << "\n";
				cout << "Saving data to file...";
				cout << "\n\n";


				cout << "Press 8 and enter to return to Main Menu: ";
				cin >> number;

				if (number == 8)
				{
					inFile.close();
					outFile.close();
					system("cls");
					goto Menu;
				}
			}
		}
	}

	else if (number == 2)
	{
	IncomeTax:
		cout << "=========================================================" << endl;
		cout << "**              Income Tax Record Interface            **" << endl;
		cout << "=========================================================" << endl << endl;
		cout << "---------------------------------------------------------" << endl;
		cout << "|| 1) View records of income tax                       ||" << endl;
		cout << "|| 2) Add record of income tax                         ||" << endl;
		cout << "|| 3) Remove record of income tax                      ||" << endl;
		cout << "|| 4) Edit record of income tax                        ||" << endl;
		cout << "|| 5) Return to main menu                              ||" << endl;
		cout << "---------------------------------------------------------" << endl;
		cout << "Enter your option: ";
		cin >> incomeChoice;
		while (incomeChoice != 1 && incomeChoice != 2 && incomeChoice != 3 && incomeChoice != 4 && incomeChoice != 5) {
			cout << "Incorrect option chosen." << endl;
			cout << "Enter your option: ";
			cin >> incomeChoice;
		}
		if (incomeChoice == 1) {
			taxNo = 1;
			inFile.open(username + "Tax.txt");
			if (!inFile) {
				cout << "There is no records of income tax.";
			}
			else {
				cout << fixed << setprecision(2);
				cout << "---------------------------------------------------------" << endl;
				cout << left << setw(20) << "Record No." << setw(20) << "Date (dd/mm/yyyy)" << setw(21) << "Monthly Income" << setw(21) << "Annual Income" << "Total Tax Annualy" << endl;
				while (!inFile.eof()) {
					if (inFile.fail()) {
						break;
					}
					inFile >> date >> income >> annualIncome >> tax;
					if (income > 0 && annualIncome > 0) {
						cout << left << setw(20) << taxNo << setw(20) << date << "$" << setw(20) << income << "$" << setw(20) << annualIncome << "$" << tax << endl;
					}
					taxNo++;
					income = 0;
					date = "";
					annualIncome = 0;
					tax = 0;
				}
				cout << "---------------------------------------------------------" << endl;
				taxNo = 1;
			}
		}
		else if (incomeChoice == 2) {
			inFile.close();
			inFile.open(username + "Income.txt");
			cout << fixed << setprecision(2);
			if (!inFile) {
				outFile.open(username + "Income.txt");
				if (!outFile) {

				}
				else {
					cout << "Enter monthly gross income : $";
					cin >> income;
					outFile << income << endl;
					outFile.close();
					outFile.open(username + "Tax.txt", ofstream::app);
					if (!outFile) {
						cout << "Error\n";
					}
					else {
						stringstream ss1, ss2, ss3;
						cout << "Enter date (dd/mm/yyyy) : ";
						cin >> date;
						pos1 = date.find("/");
						findPos1 = pos1 + 1;

						pos2 = date.find("/", findPos1);
						findPos2 = pos2 + 1;
						findPos3 = pos2 - 3;
						d = date.substr(0, pos1);
						m = date.substr(findPos1, findPos3);
						y = date.substr(findPos2);
						ss1 << d;
						ss1 >> dInt;
						ss2 << m;
						ss2 >> mInt;
						ss3 << y;
						ss3 >> yInt;
						while (d.length() != 2 || m.length() != 2 || y.length() != 4 || dInt < 0 || dInt > 31 || mInt < 1 || mInt > 12 || yInt > 2021) {
							ss1.str("");
							ss1.clear();
							ss2.str("");
							ss2.clear();
							ss3.str("");
							ss3.clear();
							cout << "Incorrect date format." << endl;
							cout << "Enter date (dd/mm/yyyy) : ";
							cin >> date;
							pos1 = date.find("/");
							findPos1 = pos1 + 1;

							pos2 = date.find("/", findPos1);
							findPos2 = pos2 + 1;
							findPos3 = pos2 - 3;
							d = date.substr(0, pos1);
							m = date.substr(findPos1, findPos3);
							y = date.substr(findPos2);
							ss1 << d;
							ss1 >> dInt;
							ss2 << m;
							ss2 >> mInt;
							ss3 << y;
							ss3 >> yInt;
						}
						pos1 = 0;
						pos2 = 0;
						d = "";
						m = "";
						y = "";
						if (!outFile) {
							cout << "Error\n";
						}
						else {
							annualIncome = income * 12;
							tax = incomeTax(income, annualIncome);
							cout << "---------------------------------------------------------" << endl;
							cout << left << setw(20) << "Date (dd/mm/yyyy)" << setw(21) << "Monthly Income" << setw(21) << "Annual Income" << "Total Tax Annualy" << endl;
							cout << left << setw(20) << date << "$" << setw(20) << income << setw(20) << date << "$" << setw(20) << annualIncome << "$" << tax << endl;
							cout << "---------------------------------------------------------" << endl;
							outFile << date << "\t" << income << "\t" << annualIncome << "\t" << tax << endl;
							cout << "Saving record to file..." << endl;
							Sleep(1000);
							cout << "Record added." << endl;
							cout << "---------------------------------------------------------" << endl;
						}
					}

				}
			}
			else {
				while (!inFile.eof()) {
					if (inFile.fail()) {
						break;
					}
					inFile >> income;
				}
				if (income <= 0)
					responseIncome = "no";

				else {
					cout << "---------------------------------------------------------" << endl;
					cout << "The income saved previously into this program is $" << income << endl;
					cout << "Do you want to use this gross income that was used previously? (Type yes or no): ";
					cin >> responseIncome;
				}
				while (responseIncome != "no" && responseIncome != "No" && responseIncome != "yes" && responseIncome != "Yes") {
					cout << "---------------------------------------------------------" << endl;
					cout << "Invalid response. Please try again.\n\n";
					cout << "Do you want to use this gross income that was used previously? (Type yes or no): ";
					cin >> responseIncome;
				}

				if (responseIncome == "no" || responseIncome == "No") {
					outFile.open(username + "Income.txt");
					cout << "---------------------------------------------------------" << endl;
					cout << "Enter monthly gross income : $";
					cin >> income;
					outFile << income << endl;
					cout << "Saving data to file..." << endl;
					outFile.close();
				}
				stringstream ss1, ss2, ss3;
				cout << "Enter date (dd/mm/yyyy) : ";
				cin >> date;
				pos1 = date.find("/");
				findPos1 = pos1 + 1;
				pos2 = date.find("/", findPos1);
				findPos2 = pos2 + 1;
				findPos3 = pos2 - 3;
				d = date.substr(0, pos1);
				m = date.substr(findPos1, findPos3);
				y = date.substr(findPos2);
				ss1 << d;
				ss1 >> dInt;
				ss2 << m;
				ss2 >> mInt;
				ss3 << y;
				ss3 >> yInt;
				while (d.length() != 2 || m.length() != 2 || y.length() != 4 || dInt < 0 || dInt > 31 || mInt < 1 || mInt > 12 || yInt > 2021) {
					ss1.str("");
					ss1.clear();
					ss2.str("");
					ss2.clear();
					ss3.str("");
					ss3.clear();
					cout << "Incorrect date format." << endl;
					cout << "Enter date (dd/mm/yyyy) : ";
					cin >> date;
					pos1 = date.find("/");
					findPos1 = pos1 + 1;
					pos2 = date.find("/", findPos1);
					findPos2 = pos2 + 1;
					findPos3 = pos2 - 3;
					d = date.substr(0, pos1);
					m = date.substr(findPos1, findPos3);
					y = date.substr(findPos2);
					ss1 << d;
					ss1 >> dInt;
					ss2 << m;
					ss2 >> mInt;
					ss3 << y;
					ss3 >> yInt;
				}
				pos1 = 0;
				pos2 = 0;
				d = "";
				m = "";
				y = "";
				outFile.open(username + "Tax.txt", ofstream::app);
				if (!outFile) {
					cout << "Error\n";
				}
				else {
					annualIncome = income * 12;
					tax = incomeTax(income, annualIncome);
					cout << "---------------------------------------------------------" << endl;
					cout << left << setw(20) << "Date (dd/mm/yyyy)" << setw(21) << "Monthly Income" << setw(21) << "Annual Income" << "Total Tax Annualy" << endl;
					cout << left << setw(20) << date << "$" << setw(20) << income << "$" << setw(20) << annualIncome << "$" << tax << endl;
					cout << "---------------------------------------------------------" << endl;
					outFile << date << "\t" << income << "\t" << annualIncome << "\t" << tax << endl;
					cout << "Saving record to file..." << endl;
					Sleep(1000);
					cout << "Record added." << endl;
					cout << "---------------------------------------------------------" << endl;
				}
			}
		}
		else if (incomeChoice == 3) {
			inFile.close();
			outFile.close();
			inFile.open(username + "Tax.txt");
			if (!inFile) {
				cout << "There is no records of income tax.";
			}
			else {
				cout << fixed << setprecision(2);
				cout << "---------------------------------------------------------" << endl;
				cout << left << setw(20) << "Record No." << setw(20) << "Date (dd/mm/yyyy)" << setw(21) << "Monthly Income" << setw(21) << "Annual Income" << "Total Tax Annualy" << endl;
				while (!inFile.eof()) {
					if (inFile.fail()) {
						break;
					}
					inFile >> date >> income >> annualIncome >> tax;
					if (income > 0 && annualIncome > 0) {
						cout << left << setw(20) << taxNo << setw(20) << date << "$" << setw(20) << income << "$" << setw(20) << annualIncome << "$" << tax << endl;
					}
					taxNo++;
					income = 0;
					date = "";
					annualIncome = 0;
					tax = 0;
				}
				cout << "---------------------------------------------------------" << endl;
				taxNo = 1;
				inFile.close();
				inFile.open(username + "Tax.txt");
				if (!inFile) {
					cout << "Error.\n";
				}
				else {
					while (!inFile.eof()) {
						if (inFile.fail()) {
							break;
						}
						inFile >> date >> income >> annualIncome >> tax;
						if (income == 0 && annualIncome == 0) {
							break;
						}
						rmvEOF++;
						income = 0;
						annualIncome = 0;
						tax = 0;
					}
				}
				cout << "Enter which record you want to remove: ";
				cin >> recordRmv;
				while (recordRmv > rmvEOF || recordRmv <= 0) {
					cout << rmvEOF;
					cout << "Incorrect value entered." << endl;
					cout << "Enter which record you want to remove: ";
					cin >> recordRmv;
				}
				if (recordRmv <= rmvEOF) {
					inFile.close();
					inFile.open(username + "Tax.txt");
					if (!inFile) {
						cout << "Error.\n";
					}
					else {
						outFile.close();
						outFile.open("tempTaxfile.txt", ofstream::app);
						if (!outFile) {
							cout << "Error\n" << endl;
						}
						else {
							while (!inFile.eof()) {
								if (inFile.fail()) {
									break;
								}
								inFile >> date >> income >> annualIncome >> tax;
								if (income > 0 && annualIncome > 0) {
									if (rmvReach != recordRmv) {
										outFile << date << "\t" << income << "\t" << annualIncome << "\t" << tax << endl;
									}
									else {
										cout << date << income << annualIncome << tax << endl;
										cout << "Removed record " << rmvReach << endl;
									}
								}
								income = 0;
								date = "";
								annualIncome = 0;
								tax = 0;
								rmvReach++;
							}
						}
					}
				}
				taxNo = 1;
				rmvReach = 1;
				rmvEOF = 0;
				inFile.close();
				outFile.close();
				if (remove((username + "Tax.txt").c_str()) != 0) {
					cout << "Remove unsuccessful." << endl;
				}
				else {
					remove((username + "Tax.txt").c_str());
					if (rename(oldname2, ((username + "Tax.txt").c_str())) == 0) {
						cout << "Remove successful." << endl;
						cout << "Saving to file..." << endl;
						Sleep(1000);
					}
					else {
						cout << "Remove unsuccessful." << endl;
					}
				}
			}
		}
		else if (incomeChoice == 4) {
			inFile.close();
			outFile.close();
			inFile.open(username + "Tax.txt");
			if (!inFile) {
				cout << "There is no records of income tax.";
			}
			else {
				cout << fixed << setprecision(2);
				cout << "---------------------------------------------------------" << endl;
				cout << left << setw(20) << "Record No." << setw(20) << "Date (dd/mm/yyyy)" << setw(21) << "Monthly Income" << setw(21) << "Annual Income" << "Total Tax Annualy" << endl;
				while (!inFile.eof()) {
					if (inFile.fail()) {
						break;
					}
					inFile >> date >> income >> annualIncome >> tax;
					if (income > 0 && annualIncome > 0) {
						cout << left << setw(20) << taxNo << setw(20) << date << "$" << setw(20) << income << "$" << setw(20) << annualIncome << "$" << tax << endl;
					}
					taxNo++;
					income = 0;
					date = "";
					annualIncome = 0;
					tax = 0;
				}
				cout << "---------------------------------------------------------" << endl;
				taxNo = 1;
			}
			inFile.close();
			inFile.open(username + "Tax.txt");
			if (!inFile) {
				cout << "Error.\n";
			}
			else {
				while (!inFile.eof()) {
					if (inFile.fail()) {
						break;
					}
					inFile >> date >> income >> annualIncome >> tax;
					if (income == 0 && annualIncome == 0) {
						break;
					}
					editEOF++;
					income = 0;
					annualIncome = 0;
					tax = 0;
				}
				cout << "Enter which record you want to edit: ";
				cin >> recordEdit;
				while (recordEdit > editEOF || recordEdit <= 0) {
					cout << editEOF;
					cout << "Incorrect value entered." << endl;
					cout << "Enter which record you want to edit: ";
					cin >> recordEdit;
				}
				if (recordEdit <= editEOF) {
					cout << "1. Date" << endl;
					cout << "2. Monthly Gross Income" << endl;
					cout << "Enter which you want to edit: ";
					cin >> editRes;
					while (editRes != 1 && editRes != 2) {
						cout << "Incorrect choice." << endl << endl;
						cout << "1. Date" << endl;
						cout << "2. Monthly Gross Income" << endl;
						cout << "Enter which you want to edit: ";
						cin >> editRes;
					}
					if (editRes == 2) {
						cout << "Enter new monthly gross income to edited record: $";
						cin >> incomeNew;
						while (incomeNew <= 0) {
							cout << "Incorrect value entered." << endl << endl;
							cout << "Enter new monthly gross income to edited record: $";
							cin >> incomeNew;
						}
					}
					else {
						stringstream ss1, ss2, ss3;
						cout << "Enter new date to edited record (dd/mm/yyyy): ";
						cin >> dateNew;
						pos1 = dateNew.find("/");
						findPos1 = pos1 + 1;
						pos2 = dateNew.find("/", findPos1);
						findPos2 = pos2 + 1;
						findPos3 = pos2 - 3;
						d = dateNew.substr(0, pos1);
						m = dateNew.substr(findPos1, findPos3);
						y = dateNew.substr(findPos2);
						ss1 << d;
						ss1 >> dInt;
						ss2 << m;
						ss2 >> mInt;
						ss3 << y;
						ss3 >> yInt;
						while (d.length() != 2 || m.length() != 2 || y.length() != 4 || dInt < 0 || dInt > 31 || mInt < 1 || mInt > 12 || yInt > 2021) {
							ss1.str("");
							ss1.clear();
							ss2.str("");
							ss2.clear();
							ss3.str("");
							ss3.clear();
							cout << "Incorrect date format." << endl;
							cout << "Enter new date to edited record (dd/mm/yyyy): ";
							cin >> dateNew;
							pos1 = dateNew.find("/");
							findPos1 = pos1 + 1;
							pos2 = dateNew.find("/", findPos1);
							findPos2 = pos2 + 1;
							findPos3 = pos2 - 3;
							d = dateNew.substr(0, pos1);
							m = dateNew.substr(findPos1, findPos3);
							y = dateNew.substr(findPos2);
							ss1 << d;
							ss1 >> dInt;
							ss2 << m;
							ss2 >> mInt;
							ss3 << y;
							ss3 >> yInt;
						}
						pos1 = 0;
						pos2 = 0;
						d = "";
						m = "";
						y = "";
					}
					inFile.close();
					inFile.open(username + "Tax.txt");
					if (!inFile) {
						cout << "Error.\n";
					}
					else {
						outFile.close();
						outFile.open("tempTaxfile.txt", ofstream::app);
						if (!outFile) {
							cout << "Error\n" << endl;
						}
						else {
							while (!inFile.eof()) {
								if (inFile.fail()) {
									break;
								}
								inFile >> date >> income >> annualIncome >> tax;
								if (income > 0 && annualIncome > 0) {
									if (editReach == recordEdit) {
										if (editRes == 2) {
											income = incomeNew;
										}
										else {
											date = dateNew;
										}
										annualIncome = income * 12;
										tax = incomeTax(income, annualIncome);
										cout << "Making changes..." << endl;
									}

									outFile << date << "\t" << income << "\t" << annualIncome << "\t" << tax << endl;
								}
								income = 0;
								annualIncome = 0;
								tax = 0;
								editReach++;
							}
						}
					}
				}
				editRes = 0;
				editReach = 1;
				editEOF = 0;
				inFile.close();
				outFile.close();
				if (remove((username + "Tax.txt").c_str()) != 0) {
					cout << "Edit unsuccessful." << endl;
				}
				else {
					remove((username + "Tax.txt").c_str());
					if (rename(oldname2, ((username + "Tax.txt").c_str())) == 0) {
						cout << "Edit successful." << endl;
						cout << "Saving to file..." << endl;
						Sleep(1000);
					}
					else {
						cout << "Edit unsuccessful." << endl;
					}
				}
			}

		}

		else {
			system("cls");
			inFile.close();
			outFile.close();
			goto Menu;
		}
		cout << endl << "Press 4 and enter to return to Income Tax Record Interface " << endl;
		cout << "OR" << endl;
		cout << "Press 8 and enter to return to Main Menu " << endl;
		cin >> number;
		while (number != 8 && number != 4) {
			cout << "Invalid input." << endl << endl;
			cout << "Press 4 and enter to return to Income Tax Record Interface " << endl;
			cout << "OR" << endl;
			cout << "Press 8 and enter to return to Main Menu " << endl;
			cin >> number;
		}
		if (number == 8)
		{
			system("cls");
			inFile.close();
			outFile.close();
			goto Menu;
		}
		else {
			system("cls");
			inFile.close();
			outFile.close();
			goto IncomeTax;
		}
	}

	else if (number == 3)
	{
		calculation(nincome, username);
		cout << "\n\n";
		cout << "Press 8 and enter to return to Main Menu: ";
		cin >> number;
		while (number != 8) {
			cout << "Invalid input. Press 8 and enter to return to Main Menu" << endl;
			cin >> number;
		}
		if (number == 8)
		{
			inFile.close();
			outFile.close();
			system("cls");
			goto Menu;
		}
	}

	else if (number == 4)
	{
		calculations(username, nincome);
		cout << "Press 8 and enter to return to Main Menu: ";
		cin >> number;

		while (number != 8) {
			cout << "Invalid input. Press 8 and enter to return to Main Menu" << endl;
			cin >> number;
		}
		if (number == 8)
		{
			inFile.close();
			outFile.close();
			system("cls");
			goto Menu;
		}
	}

	else if (number == 5) {

		SpendingsTracker(nincome, income, username);
		cout << "\n\n";

		cout << "Press 8 and enter to return to Main Menu: ";
		cin >> number;
		if (number == 8)
		{
			inFile.close();
			outFile.close();
			system("cls");
			goto Menu;
		}
	}


	else
	{
	start:
		cout << "=========================================================" << endl;
		cout << "*******************  Log Out Page ***********************" << endl;
		cout << "=========================================================" << endl << endl << endl;
		cout << "< > < > < > < > < > < > < > < > < > < > < > < > < > < > < > < > < >" << endl;
		cout << "< >                                                             < >" << endl;
		cout << "< >    Are you sure u want to Logout from SP Budget Planner?    < >" << endl;
		cout << "< >                                                             < >" << endl;
		cout << "< > < > < > < > < > < > < > < > < > < > < > < > < > < > < > < > < >" << endl;
		cout << "\nPlease Select [YES/NO]: ";
		cin >> choice;

		if (choice == "YES" || choice == "yes")
		{
			system("cls");
			Sleep(1000);
			cout << "\nlogging out of account";
			Sleep(500);
			cout << ".";
			Sleep(500);
			cout << ".";
			Sleep(500);
			cout << "." << endl << endl << endl;
			Sleep(1000);
			cout << "successfully logged out of ur account!" << endl << endl << endl;
			Sleep(1500);
			endPage();
		}

		else if (choice == "NO" || choice == "no")
		{
			cout << "\nReturning to User Menu";
			Sleep(500);
			cout << ".";
			Sleep(500);
			cout << ".";
			Sleep(500);
			cout << ".\n" << endl;
			Sleep(2000);
			system("cls");
			goto Menu;
		}

		else
		{
			cout << "Invalid Input!\n" << endl;
			goto start;
		}


	}

	system("pause");
	return 0;



}






void calculations(string username, double nincome) {

	ofstream outFile;
	ifstream inFile;
	string expName[120], expName2[120];
	int i, size, size2;
	double expAmt[120], expAmt2[120], finalAmt = 0, totalExp = 0, totalExp2 = 0, avgExp, pctng, j, z;


	outFile.open(username + "Expenses.txt");
	inFile.open(username + ".txt");

	if (!inFile)
		cout << "Error,cannot open text file" << endl;
	else {
		while (!inFile.eof())
		{
			inFile >> nincome;
			if (inFile.fail())	break;

			cout << endl << "Note: Income used is $" << nincome << "(after CPF)" << endl;

			cout << endl << "Enter the number of expenses under needs: ";
			cin >> size;
			while (size > 100 || size < 0) {
				cout << "Invalid number entered. Try again: ";
				cin >> size;
			}
			if (size <= 100 && size >= 0)
			{

				for (i = 0; i < size; i++) {
					cout << "Enter needs " << i + 1 << " name and amount: ";
					cin >> expName[i] >> expAmt[i];
					outFile << expName[i] << expAmt[i] << endl;
					totalExp += expAmt[i];
				}

				cout << "_________________________________________________________\n";
				cout << endl << "Enter the number of expenses under wants: ";
				cin >> size2;
				while (size2 > 100 || size2 < 0) {
					cout << "Invalid number entered. Try again: ";
					cin >> size;
				}

				if (!outFile)
					cout << "Error\n";
				else {

					for (int m = 0; m < size2; m++) {
						cout << "Enter wants " << m + 1 << " name and amount: ";
						cin >> expName2[m] >> expAmt2[m];
						outFile << expName2[m] << expAmt2[m] << endl;
						totalExp2 += expAmt2[m];
					}

					j = totalExp + totalExp2;
					finalAmt = nincome - j;
					z = finalAmt * -1;
					avgExp = (totalExp + totalExp2) / size;
					pctng = (finalAmt / nincome) * 100;

					if (finalAmt < 0) {
						cout << "\nWhat the heck, expense exceeded income by $" << fixed << setprecision(2) << z << ", 0% saved" << endl;

						cout << "Your Money was Spent on: \n";

						for (i = 0; i < size; i++)
							cout << expName[i] << endl;

						for (i = 0; i < size; i++)
							cout << expName2[i] << endl;
					}
					else
					{
						cout << "\n~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~" << endl;
						cout << "Your Balance is $" << finalAmt << endl;
						cout << "Your Total Expenses Amount is $" << j << setw(3) << endl;
						cout << "Your Average Expense Amount is $" << avgExp << endl;
						cout << "Percentage saved is " << fixed << setprecision(0) << pctng << "%" << endl;
						cout << "Your Money was Spent on: \n";

						for (i = 0; i < size; i++)
							cout << expName[i] << endl;

						for (i = 0; i < size; i++)
							cout << expName2[i] << endl;

					}
				}
			}
		}
	}
	outFile.close();

	// system("pause");

}
void calculation(double nincome, string username) {
	ofstream outFile;
	ifstream inFile;

	string expName[120], expName2[120];
	int i, size, size2;
	double expAmt[120], expAmt2[120],
		finalAmt = 0, o, totalExp = 0, totalExp2 = 0, avgExp, avgExp2, pctng, needsgoal, needsactual, needsbal, wantsgoal, wantsactual, wantsbal, savingsgoal, savingsactual, savingsbal;

	outFile.open(username + "Expenses.txt");
	inFile.open(username + ".txt");

	if (!inFile)
		cout << "Error,cannot open text file" << endl;
	else {
		while (!inFile.eof())
		{
			inFile >> nincome;
			if (inFile.fail())	break;

			cout << endl << "Note: Income used is $" << nincome << "(after CPF)" << endl;
			cout << endl << "Enter the number of expenses under needs: ";
			cin >> size;
			while (size > 100 || size < 0) {
				cout << "Invalid number entered. Try again: ";
				cin >> size;
			}
			if (size <= 100 && size >= 0)
			{
				for (i = 0; i < size; i++) {
					cout << "Enter needs " << i + 1 << " name and amount: ";
					cin >> expName[i] >> expAmt[i];
					outFile << expName[i] << expAmt[i] << endl;
					totalExp += expAmt[i];
				}

				cout << "_________________________________________________________\n";
				cout << endl << "Enter the number of expenses under wants: ";
				cin >> size2;
				while (size > 100 || size < 0) {
					cout << "Invalid number entered. Try again: ";
					cin >> size;
				}

				if (!outFile)
					cout << "Error\n";
				else {
					for (int m = 0; m < size2; m++) {
						cout << "Enter wants " << m + 1 << " name and amount: ";
						cin >> expName2[m] >> expAmt2[m];
						outFile << expName2[m] << expAmt2[m] << endl;
						totalExp2 += expAmt2[m];
					}
					o = totalExp + totalExp2;
					finalAmt = nincome - o;
					avgExp = totalExp / size;
					avgExp2 = totalExp2 / size2;
					pctng = (finalAmt / nincome) * 100;

					needsgoal = nincome / 2.0;
					needsactual = (totalExp / nincome) * 100.0;
					if (totalExp > needsgoal && needsactual < 70.0)
						needsbal = (totalExp - needsgoal);
					else if (needsactual > 70.0)
						needsbal = (totalExp - needsgoal);
					else
						needsbal = (totalExp - needsgoal)*-1;

					wantsgoal = (30.0 / 100) * nincome;
					wantsactual = (totalExp2 / nincome) * 100.0;
					if (totalExp2 > wantsgoal && wantsactual < 70.0)
						wantsbal = (totalExp2 - wantsgoal);
					else if (wantsactual > 70.0)
						wantsbal = (totalExp2 - wantsgoal);
					else
						wantsbal = (totalExp2 - wantsgoal)*-1;

					savingsgoal = (20.0 / 100) * nincome;
					savingsactual = (finalAmt / nincome) * 100.0;
					savingsbal = finalAmt - savingsgoal;
					cout << "\n";
					cout << "\n~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~" << endl;

					if (finalAmt < 0)
						cout << "Your Balance is $no more lo" << endl << endl;
					else
						cout << "Your Balance is $" << finalAmt << endl << endl;

					if (totalExp < needsgoal) {
						cout << "Needs 50% goal: " << fixed << setprecision(0) << needsactual
							<< "% of 50% , $" << totalExp << " spent, "
							<< "increase needs by $" << needsbal << endl;
					}
					else if (totalExp > needsgoal && needsactual < 70.0) {
						cout << "Needs 50% goal: " << fixed << setprecision(0) << needsactual
							<< "% of 50% , $" << totalExp << " spent,"
							<< "decrease needs by $" << needsbal << endl;
					}
					else if (needsactual > 70.0) {
						cout << "Needs 50% goal: "
							<< "Exceeded too much! , $" << fixed << setprecision(0) << totalExp << " spent,"
							<< "decrease needs by $" << needsbal << endl;
					}
					else {
						cout << "Needs 50% goal: " << fixed << setprecision(0) << needsactual
							<< "% of 50% , $" << totalExp << " spent, Target met. "
							<< endl;
					}
					if (totalExp2 < wantsgoal) {
						cout << "Wants 30% goal: " << fixed << setprecision(0) << wantsactual
							<< "% of 30% , $" << totalExp2 << " spent, "
							<< "increase wants by $" << wantsbal << endl;
					}
					else if (totalExp2 > wantsgoal && wantsactual < 70.0) {
						cout << "Wants 30% goal: " << fixed << setprecision(0) << wantsactual
							<< "% of 30% , $" << totalExp2 << " spent, "
							<< "decrease wants by $" << wantsbal << endl;
					}
					else if (wantsactual > 70.0) {
						cout << "Wants 30% goal: "
							<< "Exceeded too much! , $" << fixed << setprecision(0) << totalExp2 << " spent,"
							<< "decrease wants by $" << wantsbal << endl;
					}
					else {
						cout << "Wants 30% goal: " << setprecision(0) << wantsactual
							<< "% of 30% , $" << totalExp2 << " spent, Target met. "
							<< endl;
					}

					if (finalAmt < savingsgoal && finalAmt > 0) {
						cout << "Savings 20% goal: " << fixed << setprecision(0) << savingsactual << "% of 20% , $" << finalAmt << " saved , adjust expenses accordingly" << endl;
					}
					else if (finalAmt > savingsgoal) {
						cout << "Savings 20% goal: " << fixed << setprecision(0) << savingsactual
							<< "% of 20% , $" << finalAmt << " saved , adjust expenses accordingly " << endl;
					}
					else if (finalAmt < 0) {
						cout << "No savings at all rip, adjust expenses accordingly"
							<< endl;
					}
					else {
						cout << "Savings 20% goal: " << fixed << setprecision(0) << savingsactual
							<< "% of 20% , $" << finalAmt << " saved, Target met. " << endl;
					}


					cout << endl << "Your Total Expenses Amount is $" << o << setw(3) << endl;
					cout << "Your Average Expense Amount on your Needs is $" << avgExp
						<< endl;
					cout << "Your Average Expense Amount on your Wants is $" << avgExp2
						<< endl << endl;
					cout << "Your Money was Spent on: \n";

					for (i = 0; i < size; i++)
						cout << expName[i] << endl;

					for (i = 0; i < size; i++)
						cout << expName2[i] << endl;

				}
			}
		}
	}

	outFile.close();

	// system("pause");
}

void welcomePage() {
	string row1 = "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
		, row2 = "$                                     $\n"
		, row3 = "$  WElLCOME TO SP BUDGET PLANNER 101  $\n"
		, row4 = "$                                     $\n"
		, row5 = "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n";
	int delay = 300;
	system("color 00");
	cout << row1 << row2 << row3 << row4 << row5 << endl;
	Sleep(delay);
	system("cls");

	system("color 01");
	cout << row1 << row2 << row3 << row4 << row5 << endl;
	Sleep(delay);
	system("cls");

	system("color 02");
	cout << row1 << row2 << row3 << row4 << row5 << endl;
	Sleep(delay);
	system("cls");

	system("color 03");
	cout << row1 << row2 << row3 << row4 << row5 << endl;
	Sleep(delay);
	system("cls");

	system("color 04");
	cout << row1 << row2 << row3 << row4 << row5 << endl;
	Sleep(delay);
	system("cls");

	system("color 05");
	cout << row1 << row2 << row3 << row4 << row5 << endl;
	Sleep(delay);
	system("cls");

	system("color 06");
	cout << row1 << row2 << row3 << row4 << row5 << endl;
	Sleep(delay);
	system("cls");

	system("color 07");
	cout << row1 << row2 << row3 << row4 << row5 << endl;
	Sleep(delay);
	system("cls");

	system("color 08");
	cout << row1 << row2 << row3 << row4 << row5 << endl;
	Sleep(delay);
	system("cls");

	system("color 09");
	cout << row1 << row2 << row3 << row4 << row5 << endl;
	Sleep(delay);
	system("cls");

	system("color 0A");
	cout << row1 << row2 << row3 << row4 << row5 << endl;
	Sleep(delay);
	system("cls");

	system("color 0B");
	cout << row1 << row2 << row3 << row4 << row5 << endl;
	Sleep(delay);
	system("cls");

	system("color 0C");
	cout << row1 << row2 << row3 << row4 << row5 << endl;
	Sleep(delay);
	system("cls");

	system("color 0D");
	cout << row1 << row2 << row3 << row4 << row5 << endl;
	Sleep(delay);
	system("cls");

	system("color 0E");
	cout << row1 << row2 << row3 << row4 << row5 << endl;
	Sleep(delay);
	system("cls");

	system("color 0F");
	cout << row1 << row2 << row3 << row4 << row5 << endl;
}

void signUpPage(string information[], bool newMember, bool emailDomain) {
	if (newMember == true) {
		cout << "Type in your Email, username and password to get started." << endl;
	}
	else {
		cout << "Looks like you are new here." << endl
			<< "Create a new account to get started." << endl;
	}
	cout << "Email: ";
	cin >> information[0];
	while (information[0].find("@") == -1 ||
		information[0].find(".com") == -1) {
		system("cls");
		cout << "=========================================================" << endl;
		cout << "**                    Sign Up Page                     **" << endl;
		cout << "=========================================================" << endl << endl;
		cout << "Invalid email address." << endl
			<< "Please try again." << endl
			<< "Email: ";
		cin >> information[0];
	}
	cout << "Username: ";
	cin >> information[1];
	cout << "Password: ";
	cin >> information[2];
}

bool loginPage(bool validAcc, string username, string password, string checkUser, string checkPass) {
	if (checkUser == username && checkPass == password) {
		validAcc = true;
	}
	return validAcc;
}

string forgetPass(string checkUser, string checkPass, string newPass, string usernameCor, string emailCor) {
	string checkEmail, code, checkCode;
	char character;
	int randPos, tries = 1;
	srand(time(NULL));
	cout << "Username: ";
	cin >> checkUser;
	while (checkUser != usernameCor) {
		system("cls");
		cout << "=========================================================" << endl;
		cout << "**                Forget Password Page                 **" << endl;
		cout << "=========================================================" << endl << endl;
		cout << "Invalid username." << endl
			<< "Please try again." << endl
			<< "Username: ";
		cin >> checkUser;
		if (tries == 5) {
			break;
		}
		else {
			tries++;
		}
	}
	if (checkUser == usernameCor) {
		tries = 1;
		cout << "Email: ";
		cin >> checkEmail;
		while (checkEmail != emailCor) {
			system("cls");
			cout << "=========================================================" << endl;
			cout << "**                Forget Password Page                 **" << endl;
			cout << "=========================================================" << endl << endl;
			cout << "Wrong email. Try again." << endl;
			cout << "Email: ";
			cin >> checkEmail;
			if (tries == 5) {
				break;
			}
			else {
				tries++;
			}
		}
		if (checkEmail == emailCor) {
			for (randPos = 0; randPos < 5; randPos++) {
				character = rand() % (90 - 48 + 1) + 48;
				while (character >= 58 && character <= 64) {
					character = rand() % (90 - 48 + 1) + 48;
				}
				code += character;
			}
			cout << endl
				<< "Verfication code for password change is: " << code << endl;
			cout << "Please input the verification code: ";
			cin >> checkCode;
			if (checkCode == code) {
				cout << "New Password: ";
				cin >> checkPass;
				cout << "Confirm Password: ";
				cin >> newPass;
				while (checkPass != newPass) {
					cout << "Password does not match." << endl;
					cout << "New Password: ";
					cin >> checkPass;
					cout << "Confirm Password: ";
					cin >> newPass;
				}
			}
			while (checkCode != code) {
				cout << "Invalid code. Please try again." << endl;
				cout << "Please input the verification code: ";
				cin >> checkCode;
			}
		}
	}
	return newPass;
}


double incomeTax(double income, double annualIncome) {
	double tax;
	if (annualIncome < 30000) {
		tax = 0;
		if ((annualIncome - 20000) > 0) {
			tax += (annualIncome - 20000) * 0.02;
		}
	}
	else if (annualIncome < 40000) {
		tax = 200;
		if ((annualIncome - 30000) > 0) {
			tax += (annualIncome - 30000) * 0.035;
		}
	}
	else if (annualIncome < 80000) {
		tax = 550;
		if ((annualIncome - 40000) > 0) {
			tax += (annualIncome - 40000) * 0.07;
		}
	}
	else if (annualIncome < 120000) {
		tax = 3350;
		if ((annualIncome - 80000) > 0) {
			tax += (annualIncome - 80000) * 0.115;
		}
	}
	else if (annualIncome < 160000) {
		tax = 7950;
		if ((annualIncome - 120000) > 0) {
			tax += (annualIncome - 120000) * 0.15;
		}
	}
	else if (annualIncome < 200000) {
		tax = 13950;
		if ((annualIncome - 160000) > 0) {
			tax += (annualIncome - 160000) * 0.18;
		}
	}
	else if (annualIncome < 240000) {
		tax = 21150;
		if ((annualIncome - 200000) > 0) {
			tax += (annualIncome - 200000) * 0.19;
		}
	}
	else if (annualIncome < 280000) {
		tax = 28750;
		if ((annualIncome - 240000) > 0) {
			tax += (annualIncome - 240000) * 0.195;
		}
	}
	else if (annualIncome < 320000) {
		tax = 36550;
		if ((annualIncome - 280000) > 0) {
			tax += (annualIncome - 280000) * 0.20;
		}
	}
	else {
		tax = 44550;
		if ((annualIncome - 320000) > 0) {
			tax += (annualIncome - 320000) * 0.22;
		}
	}
	return tax;
}

void SpendingsTracker(double nincome, double income, string username) // Bryton
{
	ofstream outFile;
	ifstream inFile;
	const int SIZE = 50;
	double check[SIZE], saved;
	int i, n, sum = 0;
	string amount, month;
	outFile.open("tracker.txt", ofstream::app);
	inFile.open(username + "CPF.txt");

	if (!inFile)
		cout << "Error" << endl;

	else
	{
		while (!inFile.eof())
		{
			inFile >> nincome;
			if (inFile.fail())
				break;
			cout << left << fixed << setprecision(2);
			cout << "\n                             * User Monthly Expenses *" << endl;
			cout << "------------------------------------------------------------------"
				"----------------\n"
				<< endl;
			cout << "======================================" << endl;
			cout << "|                                    |\n";
			cout << "| Username: " << setw(20) << username << "     |" << endl;
			cout << "| Income after CPF deduction: " << nincome << " |" << endl;
			cout << "|                                    |\n";
			cout << "======================================\n" << endl;
			cout << "**********************************" << endl;
			cout << "    Enter number of months: ";
			cin >> n;
			cout << "***********************************\n" << endl;

			if (n < 1 || n > 12)
				cout << "Invalid Month Entered" << endl;
			else {
				if (!outFile)
					cout << "Error, File cannot open." << endl;

				else {
					for (i = 1; i <= n; i++) {
						cout << "=========================================" << endl;
						cout << "Enter month " << i << " total spendings: ";
						cin >> check[i];
						cout << "=========================================" << endl;
					}
					cout << endl
						<< "                           * Monthly Records *" << endl;
					cout << "_________________________________________________________________________\n";
					cout << endl
						<< setw(20) << "Month" << setw(20) << "Spendings" << setw(20)
						<< "Money Left"
						<< "Amount Status" << endl;

					outFile << "_______________________________________________________________________\n";
					outFile << "Username: " << setw(5) << username << "\n";
					outFile << "'Mth'"
						<< "       "
						<< "'Spent'"
						<< "        "
						<< "'Saved'"
						<< "        "
						<< "'Status'"
						<< "\n"
						<< endl;

					for (i = 1; i <= n; i++) {
						saved = nincome - check[i];

						if (saved < 0)
							amount = "Overspent!";

						else if (saved == 0)
							amount = "-";

						else
							amount = "Saved :)";

						cout << "_________________________________________________________________________\n";
						if (i == 1)
							month = "January";
						if (i == 2)
							month = "February";
						if (i == 3)
							month = "March";
						if (i == 4)
							month = "April";
						if (i == 5)
							month = "May";
						if (i == 6)
							month = "June";
						if (i == 7)
							month = "July";
						if (i == 8)
							month = "August";
						if (i == 9)
							month = "September";
						if (i == 10)
							month = "October";
						if (i == 11)
							month = "November";
						if (i == 12)
							month = "December";

						cout << setw(20) << month << setw(20) << check[i] << setw(20)
							<< saved << amount << endl;
						outFile << " " << month << "          " << check[i]
							<< "          " << saved << "         " << amount
							<< "\n"
							<< endl;
					}
				}
			}
			cout << "_________________________________________________________________________\n";
			outFile.close();
			inFile.close();
		}
	}
}
void userMenu()
{
	cout << "=========================================================" << endl;
	cout << "** To start using your budget planner choose a choice! ** " << endl;
	cout << "=========================================================" << endl << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "|| 1) Income after CPF deduction                       || " << endl;
	cout << "|| 2) Income tax calculation                           || " << endl;
	cout << "|| 3) Calculation of expenses with budget              || " << endl;
	cout << "|| 4) Calculation of expenses                          || " << endl;
	cout << "|| 5) Spendings Tracker                                || " << endl;
	cout << "|| 6) Logout                                           || " << endl;
	cout << "---------------------------------------------------------" << endl;

}


void endPage() {
	cout << " <(^^)>     (-(--(-(-(--)-)--)-)_-)-)     _(^-^)/ " << endl;
	cout << " \n         Thank you for using the budget planner! \n" << endl;
	cout << " (^-^)/     (-(--(-(-(--)-)--)-)-)-)     <(^^)>   " << endl << endl;
}