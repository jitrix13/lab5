#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <sstream>
#include <fstream>
using namespace std;
struct Node
{
	Node() : yes(-1), no(-1) {}
	string q;
	int yes;
	int no;
};
void write(const string filename, const vector<Node> tree) {
	ofstream fout;
	fout.open(filename, ios::binary);
	if (!fout) {
		cout << "Файл для записи не открылся";
		return;
	}
	for (int i = 0; i < tree.size(); ++i) {
		int size = tree[i].q.size();
		fout.write((char*)(&size), sizeof(int));
		for (int j = 0; j < size; ++j) {
			fout.write(tree[i].q.data() + j, sizeof(char));
		}
		fout.write((char*)(&tree[i].yes), sizeof(int));
		fout.write((char*)(&tree[i].no), sizeof(int));
	}
	fout.close();
}
vector<Node> read(const string filename) {
	ifstream fin;
	fin.open(filename, ios::binary);
	if (!fin) {
		cout << "Файл для чтения не открылся";
		return{};
	}
	vector<Node> result;
	while (!fin.eof()) {
		int size;
		fin.read((char*)(&size), sizeof(int));
		Node node;
		node.q.reserve(size);
		std::vector<char>buff(size + 1);
		for (int j = 0; j < size; ++j) {
			fin.read((char*)buff.data() + j, sizeof(char));
		}
		buff[size] = 0;
		node.q = buff.data();
		fin.read((char*)(&node.yes), sizeof(int));

		fin.read((char*)(&node.no), sizeof(int));

		result.push_back(node);
	}
	fin.close();
	return result;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Прочитать файл?(1 - да, 0 - нет)";
	int answ;
	cin >> answ;
	vector<Node> tree;
	if (answ == 1) {
		cout << "Введите имя файла:";
		string filename;
		cin >> filename;

		tree = read(filename);
	}
	else {
		Node n;
		n.q = "Монитор";
		tree.push_back(n);
	}
	for (;;)
	{
		int i = 0;
		while (tree[i].yes != -1 && tree[i].no != -1)
		{
			cout << "Это " << tree[i].q << "? (1 - да, 0 - нет) ";
			int ans;
			cin >> ans;
			if (ans == 1)
				i = tree[i].yes;
			else
				i = tree[i].no;
		}
		cout << "Это " << tree[i].q << "? (1 - да, 0 - нет) ";
		int ans;
		cin >> ans;
		if (ans == 1)
			cout << "Угадали!" << endl;
		else
		{
			cout << "Что это? ";
			string anim;
			cin >> anim;
			cout << "Чем " << tree[i].q << " отличается от " << anim << "? ";
			string diff;
			cin >> diff;
			Node yes = tree[i];
			Node no;
			no.q = anim;
			tree[i].yes = tree.size();
			tree.push_back(yes);
			tree[i].no = tree.size();
			tree.push_back(no);
			tree[i].q = diff;
		}
		cout << "Еще раз? (1 - да, 0 - нет) ";
		cin >> ans;
		if (ans == 0)
			break;
		else
			cout << endl << "-------------------------------------------------" << endl;
	}



	write("C:/Expert2_10/Expert2_10/monitor.txt", tree);
}
