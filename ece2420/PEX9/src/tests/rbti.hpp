auto insertN = [&numeric](int N, std::function<int(int)> transform) {
	for (int i = 0; i < N; ++i) {
		int n = transform(i);
		std::cout << "Insert " << n << std::endl;
		numeric.insert(n, numbers[n]);
		numeric.printTree();
		std::cout << std::endl;
	}
};

auto insertSet = [&numeric](std::vector<int> numList) {
	int N = numList.size();
	for (int i = 0; i < N; ++i) {
		int n = numList[i];
		std::cout << "Insert " << n << std::endl;
		numeric.insert(n, numbers[n]);
		numeric.printTree();
		std::cout << std::endl;
	}
};
