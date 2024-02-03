#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>


using namespace std;

struct node {
	string item;
	string class_;
	string attribute;
	int count;
	//node* par;
	//node* child;
	node* next;
	node* prev;

};

struct tree_node {
	string item;
	vector<node*> attribute_types;
	vector<tree_node*> sub_attributes;
};

class list {
private:
	node* head;
	node* tail;
public:
	node* begin() {
		return head->next;
	}
	node* end() {
		return tail;
	}
	list() {
		head = new node;
		tail = new node;
		head->next = tail;
		tail->prev = head;
	}
	void addnode(string value, string class_) {
		node* new_node = new node;
		new_node->item = value;
		new_node->count = 1;
		new_node->class_ = class_;
		tail->prev->next = new_node;
		new_node->next = tail;
		new_node->prev = tail->prev;
		tail->prev = new_node;
	}
	void sort_decreasing() {
		node* temp1;
		node* temp2;
		node* cursor1 = head->next;
		while (cursor1->next != tail) {
			node* cursor2 = cursor1->next;
			while (cursor2 != tail) {
				if (cursor1->count < cursor2->count) {
					if (cursor1->next == cursor2) {
						cursor1->next = cursor2->next;
						cursor2->next->prev = cursor1;
						cursor2->next = cursor1;
						cursor2->prev = cursor1->prev;
						cursor1->prev->next = cursor2;
						cursor1->prev = cursor2;
					}
					else {
						temp1 = cursor2->next;
						temp2 = cursor2->prev;
						cursor1->next->prev = cursor2;
						cursor2->next = cursor1->next;
						cursor1->prev->next = cursor2;
						cursor2->prev = cursor1->prev;

						cursor1->next = temp1;
						temp1->prev = cursor1;
						temp2->next = cursor1;
						cursor1->prev = temp2;
					}
					temp1 = cursor1;
					cursor1 = cursor2;
					cursor2 = temp1;
				}
				cursor2 = cursor2->next;
			}
			cursor1 = cursor1->next;
		}
	}

};

void print1D(vector<double> tuple) {
	for (int j = 0; j < tuple.size(); j++) {
		cout << tuple.at(j) << " ";
	}
}

void print2D(vector<vector<string>> tuples) {
	for (int i = 0; i < tuples.size(); i++) {
		for (int j = 0; j < tuples.at(i).size(); j++) {
			cout << tuples.at(i).at(j) << " ";
		}
		cout << endl;
	}
}

vector<string> generate_attribute_list(int size) {
	vector<string> attribute_list;
	string attribute;
	for (int i = 0; i < size - 1; i++) {
		attribute = "attribute";
		attribute_list.push_back(attribute.append(to_string(i)));
	}
	return attribute_list;
}

node* find_majority_class(vector<vector<string>>& tuples) {
	int flag;
	int col;
		col = tuples.at(0).size() - 1;
	
	list classes;
	for (int i = 0; i < tuples.size(); i++) {
		flag = 1;
		for (node* k = classes.begin(); k != classes.end(); k = k->next) {
			if (k->class_ == tuples.at(i).at(col)) {
				k->count++;
				flag = 0;
				break;
			}
		}
		if (flag == 1) {
			classes.addnode("1", tuples.at(i).at(col));
		}
	}


	node* max = new node;
	max->count;
	for (node* cursor = classes.begin(); cursor != classes.end(); cursor = cursor->next) {
		if (cursor->count > max->count) {
			max->count = cursor->count;
			max->class_ = cursor->class_;
		}
	}
	return max;
}

int find_max(vector<double> info_ds) {
	int i = 0;
	double min = info_ds.at(i);
	int place = 0;
	for (i = 1; i < info_ds.size(); i++) {
		if (info_ds.at(i) > min) {
			min = info_ds.at(i);
			place = i;
		}
	}
	return place;
}

int Attribute_selection_method(vector<vector<list>>& tuples) {
	int total_rows = 0;
	for (int i = 0; i < tuples.at(0).size(); i++) {
		for (node* cursor = tuples.at(0).at(i).begin(); cursor != tuples.at(0).at(i).end(); cursor = cursor->next) {
			total_rows += cursor->count;
		}
	}

	int total_type;
	double info_d;
	double info_d_type;
	vector<double> gains;
	vector<node*> classes;
	int flag;

	for (int i = 0; i < tuples.at(0).size(); i++) {
		for (node* cursor = tuples.at(0).at(i).begin(); cursor != tuples.at(0).at(i).end(); cursor = cursor->next) {
			flag = 0;
			for (int j = 0; j < classes.size(); j++) {
				if (cursor->class_ == classes.at(j)->class_) {
					flag = 1;
					classes.at(j)->count += cursor->count;
					break;
				}
			}
			if (flag == 0) {
				node* copy = new node;
				copy->class_ = cursor->class_;
				copy->count = cursor->count;
				classes.push_back(copy);
			}
		}
	}

	double class_info_d = 0;
	for (int j = 0; j < classes.size(); j++) {
		class_info_d += double(classes.at(j)->count) / double(total_rows) * log2(double(classes.at(j)->count) / double(total_rows));
	}
	class_info_d *= -1;

	for (int i = 0; i < tuples.size(); i++) {
		info_d = 0;
		for (int j = 0; j < tuples.at(i).size(); j++) {
			total_type = 0;
			info_d_type = 0;
			for (node* cursor = tuples.at(i).at(j).begin(); cursor != tuples.at(i).at(j).end(); cursor = cursor->next) {
				total_type += cursor->count;
			}
			for (node* cursor = tuples.at(i).at(j).begin(); cursor != tuples.at(i).at(j).end(); cursor = cursor->next) {
				info_d_type += double(cursor->count) / double(total_type) * log2(double(cursor->count) / double(total_type));
			}
			info_d_type *= -1.0 * (double(total_type) / double(total_rows));
			info_d += info_d_type;
		}
		gains.push_back(class_info_d - info_d);
	}
	return find_max(gains);
}



int Attribute_selection_method_gainratio(vector<vector<list>>& tuples) {

	int total_rows = 0;
	for (int i = 0; i < tuples.at(0).size(); i++) {
		for (node* cursor = tuples.at(0).at(i).begin(); cursor != tuples.at(0).at(i).end(); cursor = cursor->next) {
			total_rows += cursor->count;
		}
	}

	int total_type;
	double info_d;
	double info_d_type;
	double splitting_info;
	vector<double> gains;
	vector<node*> classes;
	int flag;

	for (int i = 0; i < tuples.at(0).size(); i++) {
		for (node* cursor = tuples.at(0).at(i).begin(); cursor != tuples.at(0).at(i).end(); cursor=cursor->next) {
			flag = 0;
			for (int j = 0; j < classes.size(); j++) {
				if (cursor->class_ == classes.at(j)->class_) {
					flag = 1;
					classes.at(j)->count+=cursor->count;
					break;
				}
			}
			if (flag == 0) {
				node* copy = new node;
				copy->class_ = cursor->class_;
				copy->count = cursor->count;
				classes.push_back(copy);
			}
		}
	}

	double class_info_d=0;
	for (int j = 0; j < classes.size(); j++) {
		class_info_d += double(classes.at(j)->count) / double(total_rows) * log2(double(classes.at(j)->count) / double(total_rows));
	}
	class_info_d *= -1;

	for (int i = 0; i < tuples.size(); i++) {
		info_d = 0;
		splitting_info = 0;
		for (int j = 0; j < tuples.at(i).size(); j++) {
			total_type = 0;
			info_d_type = 0;
			for (node* cursor = tuples.at(i).at(j).begin(); cursor != tuples.at(i).at(j).end(); cursor = cursor->next) {
				total_type += cursor->count;
			}
			for (node* cursor = tuples.at(i).at(j).begin(); cursor != tuples.at(i).at(j).end(); cursor = cursor->next) {
				info_d_type += double(cursor->count) / double(total_type) * log2(double(cursor->count) / double(total_type));
			}
			info_d_type *= -1.0 * (double(total_type) / double(total_rows));
			info_d += info_d_type;
			splitting_info += double(total_type) / double(total_rows) * log2(double(total_type) / double(total_rows));
		}
		gains.push_back((class_info_d-info_d)/(-1*splitting_info));
	}
	return find_max(gains);
}

vector<vector<list>> sort_tuples(vector<vector<string>>& tuples) {

	int class_col= tuples.at(0).size() - 1;
	int flag;
	int flag2;
	vector<vector<list>> a;

	for (int i =0; i < tuples.at(0).size()-1; i++) {
		vector<list> b;
		a.push_back(b);
		for (int j = 0; j < tuples.size(); j++) {
			flag = 1;
			for (int k = 0; k < a.at(i).size(); k++) {
				flag2 = 1;
				for (node* cursor = a.at(i).at(k).begin(); cursor != a.at(i).at(k).end(); cursor = cursor->next) {
					if (cursor->item == tuples.at(j).at(i)) {
						flag2 = 0;
					}
					if ((cursor->item == tuples.at(j).at(i)) && (cursor->class_ == tuples.at(j).at(class_col))) {
						flag = 0;
						flag2 = 1;
						cursor->count++;
						break;
					}
				}
				if (flag2 == 0) {
					a.at(i).at(k).addnode(tuples.at(j).at(i), tuples.at(j).at(class_col));
					flag = 0;
				}
				if (flag == 0) {
					break;
				}
			}
			if (flag == 1) {
				list type;
				type.addnode(tuples.at(j).at(i), tuples.at(j).at(class_col));
				a.at(i).push_back(type);
			}
		}
	}
	return a;
}

tree_node* Generate_decision_tree(vector<vector<string>> tuples, vector<string> attribute_list2, vector<string>& attribute_list) {
	//specify if the class col is at beg or end
	tree_node* root = new tree_node;
	int flag;
	vector<int> remove_at;
	//ensure that attributes get eliminated in each recursive call and updates D(tuples)
	if (attribute_list.size() != attribute_list2.size()) {
		for (int i = 0; i < attribute_list2.size(); i++) {
			flag = 0;
			for (int j = 0; j < attribute_list.size(); j++) {
				if (attribute_list2.at(i) == attribute_list.at(j)) {
					flag = 1;
				}
			}
			if (flag == 0) {
				remove_at.push_back(i);
			}
		}
		for (int i = remove_at.size() - 1; i >= 0; i--) {
			attribute_list2.erase(attribute_list2.begin() + remove_at.at(i));
			for (int j = 0; j < tuples.size(); j++) {
				tuples.at(j).erase(tuples.at(j).begin() + remove_at.at(i));
			}
		}
	}

	vector<vector<list>> sorted_tuples = sort_tuples(tuples);

	node* majority_class = find_majority_class(tuples);
	tree_node* copy = new tree_node;
	copy->item = majority_class->class_;
	if (majority_class->count == tuples.size()) {
		root = copy;
		return root;
	}
	if (attribute_list.size() == 0) {
		root = copy;
		return root;
	}

	int splitting_attribute = Attribute_selection_method_gainratio(sorted_tuples);
	//int splitting_attribute = Attribute_selection_method_gainratio(sorted_tuples);

	root->item = attribute_list.at(splitting_attribute);
	vector<string>::iterator it = attribute_list.begin();
	attribute_list.erase(it + splitting_attribute);
	it = attribute_list2.begin();
	attribute_list2.erase(it + splitting_attribute);

	vector<vector<vector<string>>> dj;
	vector<vector<string>>::iterator IT;
	//creating the partitions
	for (int j = 0; j < sorted_tuples.at(splitting_attribute).size(); j++) {
		vector<vector<string>> dj_;
		for (int i = 0; i < tuples.size(); i++) {
			if (tuples.at(i).at(splitting_attribute) == sorted_tuples.at(splitting_attribute).at(j).begin()->item) {
				dj_.push_back(tuples.at(i));
				IT = dj_.end() - 1;
				it = IT->begin();
				IT->erase(it + splitting_attribute);
			}
		}
		dj.push_back(dj_);
		root->attribute_types.push_back(sorted_tuples.at(splitting_attribute).at(j).begin());
	}

	for (int i = 0; i < dj.size(); i++) {
		if (dj.at(i).at(0).size() == 1) {
			tree_node* copy = new tree_node;
			copy->item = dj.at(i).at(0).at(0);
			root->sub_attributes.push_back(copy);
		}
		else {
			root->sub_attributes.push_back(Generate_decision_tree(dj.at(i), attribute_list2, attribute_list));
		}
	}
	return root;
}

void printtree(tree_node* root) {
	if (root->sub_attributes.size() != 0) {
		cout << root->item << ": " << endl;
		for (int i = 0; i < root->sub_attributes.size(); i++) {
			cout << root->item << " " << "type " << i << ": " << root->attribute_types.at(i)->item << " ->  " <<root->sub_attributes.at(i)->item << endl;
		}
		cout << endl;
		for (int i = 0; i < root->sub_attributes.size(); i++) {
			printtree(root->sub_attributes.at(i));
		}
	}
}

void predict_class(vector<string>& tuple, tree_node*& root) {
	if (root->sub_attributes.size() == 0) {
	 tuple.push_back(root->item);
	 return;
	}
	int col = stoi(root->item.substr(9, root->item.length() - 9));
	int value=0;
	for (int i = 0; i < root->attribute_types.size(); i++) {
		if (tuple.at(col) == root->attribute_types.at(i)->item) {
			 value= i;
			break;
		}
	}
	predict_class(tuple, root->sub_attributes.at(value));
}


int main() {
	vector <vector<string>> tuples;
	ifstream file("C:/Users/Jake/Documents/DecisionTree/Project1/data.txt");
	//ifstream file("C:/Users/Jake/Documents/FPgrowth/adult/adult.data");

	if (file.fail()) {
		cerr << "error opening file" << endl;
		exit(1);
	}
	string words;//input
	string item;
	int n = 0;

	//reads each order from the input file and puts each in the 2d vector
	//and also keeps track of the different items and their count
	while (!file.eof()) {
		getline(file, words);
		int j = 0, i = 0;
		vector<string> tuple;
		//cout << words.length() << endl;
		while (i < words.length()) {
			if (words[i] == ',' || words[i] == ' ') {
				item = words.substr(j, (i - j));
				tuple.push_back(item);
				j = i + 1;
				if (words[j] == ' ' || words[j] == ',') {
					j++;
				}
				i = j;
			}
			i++;
		}
		item = words.substr(j, (i - j));
		tuple.push_back(item);
		tuples.push_back(tuple);
	}

	string pos = "end";
	if (pos == "start") {
		for (int i = 0; i < tuples.size(); i++) {
			tuples.at(i).push_back(tuples.at(i).at(0));
			tuples.at(i).erase(tuples.at(i).begin());
		}
	}
	else;

	vector<double> numbers;
	vector<double>::iterator it;
	double number;
	double temp;
	//int split_points=3;

	for (int i = 0; i < tuples.at(0).size() - 1; i++) {
		char value = tuples.at(0).at(i)[0];
		if ((value-'0'>=0 && value-'0'<10) || value == 45) {
			numbers.clear();
			for (int j = 0; j < tuples.size(); j++) {
				numbers.push_back(stod(tuples.at(j).at(i)));
			}
			int min=numbers.at(0);
			for (int j = 1; j < numbers.size(); j++) {
				if (numbers.at(j) < min) {
					min = numbers.at(j);
				}
			}
			int max = numbers.at(0);
			for (int j = 1; j < numbers.size(); j++) {
				if (numbers.at(j) > max) {
					max = numbers.at(j);
				}
			}
				double average = (max+min)/2;

				for (int j = 0; j < tuples.size(); j++) {
					if (stod(tuples.at(j).at(i)) <= average) {
						tuples.at(j).at(i) = "<= " + to_string(average);
					}
					else {
						tuples.at(j).at(i) = "> " + to_string(average);
					}
				}
			}
		}

	int split =20;
	vector<vector<string>> test_tuples;
	if (split != 0) {
		for (int i = 0; i < split; i++) {
			test_tuples.push_back(tuples.at(i));
		}

		vector<vector<string>> ::iterator bit = tuples.begin();
		vector<vector<string>> ::iterator end = tuples.begin() + split;
		tuples.erase(bit, end);
	}

	vector<string> attribute_list = generate_attribute_list(tuples.at(0).size());
	tree_node* root = Generate_decision_tree(tuples, attribute_list, attribute_list);
	//printtree(root);
	
	if(split!=0)
	tuples=test_tuples;

	for (int i = 0; i < tuples.size(); i++) {
		predict_class(tuples.at(i), root);
	}
	int correct = 0;
	for (int i = 0; i < tuples.size(); i++) {
		cout << tuples.at(i).at(tuples.at(0).size() - 2) << " " << tuples.at(i).at(tuples.at(0).size() - 1) << endl;
		if (tuples.at(i).at(tuples.at(0).size() - 2) == tuples.at(i).at(tuples.at(0).size() - 1)) {
			correct++;
		}
	}
	cout << "accuracy: " << double(correct )/ double(tuples.size() )<< endl;
}