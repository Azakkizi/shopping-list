// |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
// | You can create a list and name it. Then you can add products and their amounts in that list. If you create more than one list,  |
// | you can switch between each other. If you write the name or amount wrong, you are able to change them. If you took the product, |
// | you can mark it as taken then if you left it, you can remove its mark. If you want to remove a product that you added before,   |
// | you are able to remove it from the current list. And also you can list all your lists' title and products in the current list.  |
// | You can always write 'help' to see all the commands so you don't have to remember them all the time.							 |
// | ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Line {
public:
	string command;
	string nonCommand;
};

class Product {
public:
	string name;
	int amount;
	bool taken;

	Product(string name, int amount)
	{
		this->name = name;
		this->amount = amount;
		this->taken = false;
	}

	void printInfo() {
		cout << "Name:" + name + " Amount:" << amount;

		if (taken) {
			cout << " -X-"; //alınanların yanına konulan işaret
		}

		cout << endl;
	}
};

class ShoppingList
{
private:
	vector<Product*> products;

public:
	string name;

	ShoppingList(string listName) {
		name = listName;
	}

	int size() {
		return products.size();
	}

	Product* getProduct(string productName) {
		int length = size();
		for (int i = 0; i < length; i++)
		{
			if (products[i]->name == productName) {
				return products[i];
			}
		}
		return NULL;
	}

	void addProduct(string productName, int amount) {  //listeye ürün ekleme
		products.push_back(new Product(productName, amount));
	}

	void setAsTaken(string productName) {  //alındıysa durum: true
		Product* temp = getProduct(productName);
		if (temp == NULL) {
			cout << "There is no product named " + productName + "." << endl;
			return;
		}
		temp->taken = true;
	}

	void setAsLeft(string productName) {  //bırakıldıysa durum: tekrar false
		Product* temp = getProduct(productName);
		if (temp == NULL) {
			cout << "There is no product named " + productName + "." << endl;
			return;
		}
		temp->taken = false;
	}

	void printProducts() {  //mevcuttaki listenin öğelerini gösterme
		map<string, Product*>::iterator it;
		if (size() == 0) {
			cout << "The list is empty." << endl;
		}
		else {
			cout << "Products in " + name + " list." << endl;
			int length = size();
			for (int i = 0; i < length; i++)
			{
				products[i]->printInfo();
			}
		}
	}

	void printInfo() { //ismini ve miktarını yazdırma
		cout << "Name:" + name + " Number of products:" << size() << endl;
	}

	void removeProduct(string productName) { //ebediyetten silme
		int length = size();
		for (int i = 0; i < length; i++)
		{
			if (products[i]->name == productName) {
				products.erase(products.begin() + i);
				return;
			}
		}

		cout << "Product not found." << endl;
	}

	void editProduct(string oldProductName, string newProductName, string newAmount) { //var olanı sil, üstüne benim yazdığımı yaz
		Product* temp = getProduct(oldProductName);

		if (oldProductName != newProductName && newProductName != "") {
			temp->name = newProductName;
		}

		if (newAmount != "") {
			temp->amount = stoi(newAmount);
		}
	}
};

class Planner {
public:
	vector<ShoppingList*> shoppingLists;
	ShoppingList* currentShoppingList;

	void createShoppingList(string listName) {  //liste oluşturma
		currentShoppingList = new ShoppingList(listName);
		shoppingLists.push_back(currentShoppingList);
	}

	void switchShoppingList(string listName) {  //listeler arası gezme
		ShoppingList* temp = getList(listName);
		if (temp == NULL) {
			cout << "There is no list named " + listName + "." << endl;
		}
		else {
			currentShoppingList = temp;
			cout << "Switched to " + listName + " list." << endl;
		}
	}

	void printShoppingLists() {  //listeleri gösterme
		int length = shoppingLists.size();
		for (int i = 0; i < length; i++)
		{
			shoppingLists[i]->printInfo();
		}
	}

	ShoppingList* getList(string listName) {
		int length = shoppingLists.size();
		for (int i = 0; i < length; i++)
		{
			if (shoppingLists[i]->name == listName) {
				return shoppingLists[i];
			}
		}
		return NULL;
	}

	void editList(string oldListName) {
		ShoppingList* temp = getList(oldListName);
		if (temp == NULL) {
			cout << "There is no list named " + oldListName + "." << endl;
		}
		else {
			string newName;
			cout << "New list name:";
			getline(cin, newName);
			temp->name = newName;
			cout << "Done!" << endl;
		}
	}

	void removeList(string listName) {
		int length = shoppingLists.size();
		for (int i = 0; i < length; i++)
		{
			if (shoppingLists[i]->name == listName) {
				shoppingLists.erase(shoppingLists.begin() + i);
				cout << listName + " has been removed." << endl;
				if (currentShoppingList->name == listName) {
					if (shoppingLists.size() != 0) {
						currentShoppingList = shoppingLists[0];
						cout << "Current list is " + currentShoppingList->name + " now." << endl;
					}
					else
					{
						currentShoppingList = NULL;
					}
				}
				return;
			}
		}
		cout << "There is no list named " + listName + "." << endl;
	}
};

Line* getCommand(string text) { //girdideki command-noncommand ayrımı
	int length = text.size();

	Line* result = new Line();

	for (int i = 0; i < length; i++)
	{
		//edit elma suyu => length == 14
		if (text[i] == ' ') {
			result->command = text.substr(0, i);//edit
			result->nonCommand = text.substr(i + 1, length - i - 1);//elma suyu
			return result;
		}
	}
	//add
	result->command = text;
	return result;
}


int main()
{
	//COMMANDS: deneme
	//create shoplist Manav
	//add
	//	name: elma
	//	number: 3
	//switch Market
	//took Ekmek
	//left Portakal
	//list shops
	//list products
	//help

	/* ÖRNEK INPUT deneme
	create Manav
	add Elma 1
	add Portakal 4
	create Market
	add Ekmek 2
	add LightCola1.5Lt(?) 3
	list shops
	list products
	switch Manav
	list products
	add "4 tane cola" 3
	*/

	Planner* planner = new Planner();

	cout << "Please write 'help' to see the commands." << endl;

	string text;

	for (;;) //sürekli girdi alacak, döngü dönmesi lazım
	{
		getline(cin, text);
		try { //doğru commandi try
			Line* line = getCommand(text);
			if (line->command == "help") {
				cout << "Commands: " << endl;
				cout << "	create {listName}" << endl; // {Liste adı} oluştur
				cout << "	switch {listName}" << endl; // {Liste adı}na geç
				cout << "	editlist {listName}" << endl; // {Liste adı}nı düzenle
				cout << "	removelist {listName}" << endl; // {Liste adı} listesini sil
				cout << "	add" << endl; // ekle (sonra cout ürün adı ve miktarı)
				cout << "	took {productName}" << endl; // {Ürün adı} alındı (olarak işaretlendi)
				cout << "	left {productName}" << endl; // {Ürün adı}nı bırak
				cout << "	edit {productName}" << endl; // {Ürün adı}nı düzenleme
				cout << "	remove {productName}" << endl; // {Ürün adı}nı sil
				cout << "	list shoplists" << endl; // Listeleri göster
				cout << "	list products" << endl; // Mevcut listedeki ürünleri göster
				cout << "	exit" << endl;
				continue;
			}
			else if (line->command == "create") {
				planner->createShoppingList(line->nonCommand);
				cout << "The list " + line->nonCommand + " has been created. The current list is " + line->nonCommand + "now." << endl;
				continue;
			}
			else if (line->command == "add") {
				if (planner->currentShoppingList == NULL) {
					cout << "There is no list created. First create a list." << endl;
					continue;
				}
				string productName;
				string amountText;
				cout << "Product name:";
				getline(cin, productName);
				cout << "Amount:";
				getline(cin, amountText);
				planner->currentShoppingList->addProduct(productName, stoi(amountText));
				cout << productName + " has been added to current list." << endl;
				continue;
			}
			else if (line->command == "switch") {
				planner->switchShoppingList(line->nonCommand);
				continue;
			}
			else if (line->command == "editlist") {
				planner->editList(line->nonCommand);
				continue;
			}
			else if (line->command == "removelist") {
				planner->removeList(line->nonCommand);
				continue;
			}
			else if (line->command == "took") {
				if (planner->currentShoppingList == NULL) {
					cout << "There is no list created. First create a list." << endl;
					continue;
				}
				planner->currentShoppingList->setAsTaken(line->nonCommand);
				cout << line->nonCommand + " has been marked as taken. Product will be marked '-X-'" << endl;
				continue;
			}
			else if (line->command == "left") {
				if (planner->currentShoppingList == NULL) {
					cout << "There is no list created. First create a list." << endl;
					continue;
				}
				planner->currentShoppingList->setAsLeft(line->nonCommand);
				cout << "You left " + line->nonCommand + "." << endl;
				continue;
			}
			else if (line->command == "edit") {
				if (planner->currentShoppingList == NULL) {
					cout << "There is no list created. First create a list." << endl;
					continue;
				}
				cout << "You can edit " + line->nonCommand + " and its amount now. (Press enter to leave it same)" << endl;
				string productName;
				string amountText;
				cout << "New product name: ";
				getline(cin, productName);
				cout << "New amount: ";
				getline(cin, amountText);
				planner->currentShoppingList->editProduct(line->nonCommand, productName, amountText);
				cout << "Done!" << endl;
				continue;
			}
			else if (line->command == "remove") {
				if (planner->currentShoppingList == NULL) {
					cout << "There is no list created. First create a list." << endl;
					continue;
				}
				planner->currentShoppingList->removeProduct(line->nonCommand);
				cout << line->nonCommand + " has been removed from list." << endl;
				continue;
			}
			else if (line->command == "list") {
				if (line->nonCommand == "shoplists") {
					if (planner->currentShoppingList == NULL) {
						cout << "You have no list right now." << endl;
						continue;
					}
					cout << "All your lists are down below." << endl;
					planner->printShoppingLists();
					continue;
				}
				else if (line->nonCommand == "products") {
					if (planner->currentShoppingList == NULL) {
						cout << "There is no list created. First create a list." << endl;
						continue;
					}
					planner->currentShoppingList->printProducts();
					continue;
				}
			}
			else if (line->command == "exit") {
				return 0;
			}

			cout << "Invalid command, please write 'help' to see the commands." << endl;
		}
		catch (...) { //yanlış commandi catch
			cout << "Error. Please insert the command again." << endl;
		}
	}

	/* fonksiyon deneme
	createShoppingList("Manav");
	addProduct("Elma", 3);
	addProduct("Armut", 5);
	createShoppingList("Market");
	addProduct("Ekmek", 2);
	addProduct("Light cola 4'lü 1 lt", 2);

	printShoppingLists();

	switchShoppingList("Manav");
	printProducts();

	switchShoppingList("Market");
	printProducts();*/
}