Tree<std::string, Tree<std::string, int> > outer;
Tree<std::string, int> inner;
std::shared_ptr<KeyVal<std::string, int> > pKeyVal(new Tree<std::string, int>); 
Tree<int, std::string> numeric;
