bTree<std::string, bTree<std::string, int> > outer;
bTree<std::string, int> inner;
std::shared_ptr<KeyVal<std::string, int> > pKeyVal(new bTree<std::string, int>); 
bTree<int, std::string> numeric;
