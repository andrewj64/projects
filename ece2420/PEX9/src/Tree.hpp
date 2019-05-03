#ifndef TREE_HPP
#define TREE_HPP

#include "KeyVal.hpp"
#include "walrus.h"
#include <iostream>
#include <memory>
#include <functional>
#include <list>      
#include <iomanip>  // for print function
#include <unistd.h>


//forward declaration
template <class K, class V>
class Tree;

enum color
{
    BLACK,
    RED
};
/** 
 * @class node
 *
 * The purpose of this class is to store key value pairs in a sorted binary tree.
 * Note that all methods and members are private and only accessible by the
 * friend class Tree.
 *
 * The reason that the node class and the Tree class are 
 * separate is to make usage cleaner.  We must be able to create Tree 
 * objects on the stack just as we would any other object.  Since additions and
 * deletions to the list may change the root node, it is not effective to 
 * create a root node as the base object
 *
 * This separate private class also allows us to remove some default constuctors
 * and use only deep copy assignment in this class while exposing all options
 * in the public class.
 */
template <class K, class V>
class node : public std::enable_shared_from_this<node<K, V>>
{
    friend class Tree<K, V>;

  private:
    node() = default;
    node(const node &other) = delete;
    node &operator=(const node &other)
    {
        m_prev.reset();
        //m_prev = std::weak_ptr<node<K,V>>();
        if (other.m_key == NULL)
        {
            m_color = BLACK;
            m_left.reset();
            m_right.reset();
            m_key.reset();
            m_val.reset();
        }
        else
        {
            m_key.reset(new K(*other.m_key));
            m_val.reset(new V(*other.m_val));
            m_color = other.m_color;

            m_left.reset(new node<K, V>());
            m_right.reset(new node<K, V>());
            *m_left = *(other.m_left);
            *m_right = *(other.m_right);
            m_left->m_prev = this->shared_from_this();
            m_right->m_prev = this->shared_from_this();
        }

        return *this;
    }

    std::shared_ptr<node<K, V>> parent()
    {
        return m_prev.lock();
    }

    std::shared_ptr<node<K, V>> grandparent()
    {
        auto p = parent();
        if (!p)
        {
            return NULL;
        }
        return p->parent();
    }

    std::shared_ptr<node<K, V>> aunt()
    {
        auto gp = grandparent();
        auto p = parent();
        if (!gp)
        {
            return NULL;
        }

        return parent()->sibling();
    }

    std::shared_ptr<node<K, V>> sibling()
    {
        auto p = parent();
        if (!p)
        {
            return NULL;
        }
        if (*m_key < *p->m_key)
            return p->m_right;
        else
            return p->m_left;
    }

    bool isRed()
    {
        return m_color;
    }

    std::shared_ptr<K> m_key;
    std::shared_ptr<V> m_val;
    color m_color;
    std::shared_ptr<node> m_left;
    std::shared_ptr<node> m_right;
    std::weak_ptr<node<K, V>> m_prev;
};

/**
 * @class Tree
 */
template <class K, class V>
class Tree : public KeyVal<K, V>
{
  public:
    /**
   * @brief Constructor
   * 
   * This ctor creates a valid root node
   */
    Tree()
    {
        m_rootNode.reset(new node<K, V>());
        m_rootNode->m_color = BLACK; // don't need this?
    }

    Tree(const Tree &that)
    {
        m_rootNode.reset(new node<K, V>());
        *this = that;
    }

    Tree &operator=(const Tree &other)
    {
        *m_rootNode = *(other.m_rootNode);
    }

    virtual void insert(const K &key, const V &val) override
    {
        // m_rootNode = insertInternal(key, val);
        insertInternal(key, val);
    }

    virtual void del(const K &key) override
    {
        m_rootNode = delInternal(key, m_rootNode);
    }

    virtual std::shared_ptr<V> get(const K &key) override
    {
        auto cur = m_rootNode;
        // cycle through Tree to find key that matches
        while (cur->m_key)
        {
            if (*(cur->m_key) == key)
                return cur->m_val;
            else if (key < *(cur->m_key))
                cur = cur->m_left;
            else
                cur = cur->m_right;
        }

        std::cout << "Key not found!" << std::endl;
        return NULL;
    }

    virtual void forEach(std::function<void(const K &key, V &val)> callback) override
    {
        if (m_rootNode->m_key == NULL)
        {
            std::cout << "Empty list! Here's a walrus instead." << std::endl;
            walrus();
        }
        forEachInt(callback, m_rootNode);
    }

    void printTree()
    {
        //postorder(m_rootNode);
        #if 1
        //create some working variables on stack
        //and initially populate
        std::list<std::shared_ptr<node<K, V>>> workList;
        std::list<int> levelList;
        workList.push_back(m_rootNode);
        levelList.push_back(0);

        //while more nodes exist for BFS
        while (!workList.empty())
        {
            //determine information for current vertex
            auto pCurrent = workList.front();
            auto level = levelList.front();
            auto pParent = pCurrent->parent();
            auto color = (pCurrent->isRed()) ? "RED" : "BLACK";

            //remove current vertex from working lists
            workList.pop_front();
            levelList.pop_front();

            //print the node
            std::cout << "{K:" << *(pCurrent->m_key) << ", "; //KEY
            std::cout << "C:" << color << ", ";               //COLOR
            std::cout << "L:" << level << ", ";               //LEVEL
            if (pParent)
                std::cout << "PK:" << *(pParent->m_key) << "}"; //PARENT KEY
            else
                std::cout << "PK:NULL}";

            //add left child to work list if valid
            if (pCurrent->m_left->m_key)
            {
                workList.push_back(pCurrent->m_left);
                levelList.push_back(level + 1);
            }

            //add right child to work list if valid
            if (pCurrent->m_right->m_key)
            {
                workList.push_back(pCurrent->m_right);
                levelList.push_back(level + 1);
            }

            //print new line when level changes
            if (!levelList.empty() && (level != levelList.front()))
                std::cout << std::endl;
        }
        //new line at end of traversal
        std::cout << std::endl;
        #endif
    }

void postorder(std::shared_ptr<node<K,V>> p, int indent=0)
{
    if(p->m_key) {
        if(p->m_left->m_key) postorder(p->m_left, indent+4);
        if(p->m_right->m_key) postorder(p->m_right, indent+4);
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        cout<< *p->m_key << "\n ";
    }
}

void cleanup_checker(std::shared_ptr<node<K,V>> node) {
    if (node == nullptr) {
        return;
    }



    // Recurse!
    cleanup_checker(node->m_left);
    if (node->parent() != nullptr && node->isRed() && node->parent()->isRed()) {
        std::cout << "\n\nDouble reds!\n";
        printTree();
        sleep(2);
	}
	cleanup_checker(node->m_right);
}

int intTreeChecker(shared_ptr<node<K,V>> node)
{
        if (node == NULL)
       return 0;

    if(node == m_rootNode && node->m_color == RED)
    {
        cout<<"Red Root!"<<endl;
        return -1;
    }

    
    if(node->m_key == NULL  &&  node->m_color == RED)
    {
        cout<<"red null!"<<endl;
        printTree();
        return -1;
    }

    
    if (node->m_color ==  RED && node->parent()->m_color == RED)
    {
       std::cout << "\n\nDouble reds!\n";
       printTree();
       return -1;
    }

    

   // Computes the height for the left and right child recursively
   int leftHeight = intTreeChecker(node->m_left);
   int rightHeight = intTreeChecker(node->m_right);
   int add = node->m_color == BLACK ? 1 : 0;
   // The current subtree is not a red black tree if and only if
   // one or more of current node's children is a root of an invalid tree
   // or they contain different number of black nodes on a path to a null node.
   if (leftHeight == -1 || rightHeight == -1 || leftHeight != rightHeight)
       return -1;
   else
       return leftHeight + add;
    
}


void treeChecker()
{
    if(m_rootNode->m_key == NULL)
    {
        cout<<"empty list"<<endl;
        return;
    }
    
    if(intTreeChecker(m_rootNode) != -1)
    {
        cout<<"valid Tree. Congrats"<<endl;
    }
}
    

  private:
    void forEachInt(std::function<void(const K &key, V &val)> callback, std::shared_ptr<node<K, V>> cur)
    {
        // std::cout << "Current Key, Val: " << *cur->m_key << ", " << *cur->m_val << std::endl;
        if (cur->m_left->m_key)
        {
            forEachInt(callback, cur->m_left);
        }
        callback(*(cur->m_key), *(cur->m_val));
        if (cur->m_right->m_key)
        {
            forEachInt(callback, cur->m_right);
        }
    }

    std::shared_ptr<node<K, V>> insertInternal(const K &key, const V &val)
    {
        //delete any possible duplicates
        auto root = m_rootNode;
        std::shared_ptr<node<K, V>> newNode(new node<K, V>());
        newNode->m_key.reset(new K());
        newNode->m_val.reset(new V());
        *(newNode->m_key) = key;
        *(newNode->m_val) = val;
        newNode->m_color = RED;
        newNode->m_left.reset(new node<K, V>());
        newNode->m_right.reset(new node<K, V>());
        newNode->m_left->m_color = BLACK;
        newNode->m_right->m_color = BLACK;
        // std::cout << "inserting " << key << std::endl;
        // check for empty Tree
        if (!(root->m_key))
        {
            //std::cout << "inserting " << key << " to empty Tree" << std::endl;
            newNode->m_color = BLACK;
            m_rootNode = newNode;
            return root;
        }

        auto cur = m_rootNode;
        // cycle through Tree to find insertion spot
        while (cur->m_key)
        {
            if (key < *(cur->m_key))
            {
                if (cur->m_left->m_key)
                {
                    cur = cur->m_left;
                }
                else
                {
                    //std::cout << "inserting key " << key << " to the left" << std::endl;
                    cur->m_left = newNode;
                    newNode->m_prev = cur;
                    //printTree();
                    rebalance(newNode);
                    //std::cout << "rebalanced" << std::endl;
                    //printTree();
                    return root; // segfault key equals 1, left of 2
                }
            }
            else if (key > *(cur->m_key)) 
            {
                if (cur->m_right->m_key)
                {
                    cur = cur->m_right;
                }
                else
                {
                    //std::cout << "inserting key " << key << " to the right" << std::endl;
                    cur->m_right = newNode;
                    newNode->m_prev = cur;
                    //printTree();
                    rebalance(newNode);
                    // std::cout << "rebalanced" << std::endl;
                    //printTree();
                    return root;
                }
            }
            else
            {
                //std::cout << "Node already exists ya doofus" << std::endl;
                return root;
            }
        }
    } 

    std::shared_ptr<node<K, V>> delInternal(const K &key, std::shared_ptr<node<K, V>> start)
    {
        std::cout << "Deleting " << key << std::endl;
        auto cur = start;
        auto root = m_rootNode;
        // find key to be deleted
        if (!(cur->m_key))
        {
            std::cout << "empty list! So here's a walrus instead :)" << std::endl;
            walrus();
            return root;
        }

        while (cur->m_key && *(cur->m_key) != key) // find node to be deleted TODO: fix case where desired node doesn't exist!!
        {
            if (key < *(cur->m_key))
                cur = cur->m_left;
            else
                cur = cur->m_right;
        }
        if (!cur->m_key)
        {
            return root;
        }

        if (!(cur->m_left->m_key) && !(cur->m_right->m_key)) // no childs
        {
            if (cur == root) // root with no childs
            {
                cur.reset(new node<K, V>());
                root = cur;
                delRebalance(root);
                return root;
            }

            auto prev = cur->m_prev.lock();
        
            if (*(prev->m_key) < *(cur->m_key))
            {
                prev->m_right.reset(new node<K, V>());
                // delRebalance();
            }
            else
            {
                prev->m_left.reset(new node<K, V>());
            }
            return root;
        }
        else if (cur->m_left->m_key && cur->m_right->m_key) // two chilluns
        {
            // find in order predecessor
            auto temp = cur->m_left;
            //std::cout << key << " has two chilluns" << std::endl;
            //std::cout << "Left key: " << *cur->m_left->m_key << std::endl;
            while (temp->m_right->m_key)
            {
                temp = temp->m_right;
            }
            *(cur->m_key) = *(temp->m_key);
            *(cur->m_val) = *(temp->m_val);
            root = delInternal(*(temp->m_key), temp);
            return root;
        }
        else // one child
        {
            //if left child
            if (cur->m_left->m_key)
            {
                if (cur == root)
                {
                    root = cur->m_left;
                    return root;
                }
                auto prev = cur->m_prev.lock();
                cur->m_left->m_prev = prev;
                if (*(prev->m_key) < *(cur->m_key))
                {
                    prev->m_right = cur->m_left; // set previous?
                }
                else
                {
                    prev->m_left = cur->m_left;
                }
                return root;
            }
            //if right child
            if (cur->m_right->m_key)
            {
                if (cur == root)
                {
                    root = cur->m_right;
                    return root;
                }
                auto prev = cur->m_prev.lock();
                cur->m_right->m_prev = prev;
                if (*(prev->m_key) < *(cur->m_key))
                {
                    prev->m_right = cur->m_right;
                }
                else
                {
                    prev->m_left = cur->m_right;
                }
                return root;
            }
        }
    }

    void delRebalance(std::shared_ptr<node<K,V>> node)
    {
        if (node == m_rootNode)
        {
            node->m_color = BLACK;
            return;
        }
    }

    void rebalance(std::shared_ptr<node<K, V>> node)
    {
        if (node == m_rootNode) // root
        {
            node->m_color = BLACK;
            return;
        }
        auto parent = node->parent();
        auto uncle = node->aunt();
        auto grandparent = node->grandparent();
        if (parent->m_color == BLACK) //do nothing
            return;
        else if (uncle->isRed()) // red uncle
        {
            parent->m_color = BLACK;
            uncle->m_color = BLACK;
            grandparent->m_color = RED;
            
            rebalance(grandparent);
            //std::cout << "red uncle" << std::endl;
            //getchar();
        }
        else if (node == grandparent->m_right->m_left) // right left
        {
            leftRotate(parent);

            rebalance(parent);
            //std::cout << "right left" << std::endl;
            
            //getchar();
        }
        else if (node == grandparent->m_left->m_right) // left right
        {
            rightRotate(parent);
            rebalance(parent);
            //std::cout << "red uncle" << std::endl;
            
            //getchar();
        }
        else if (node == grandparent->m_left->m_left)
        {
            swapColors(parent, grandparent);
            rightRotate(parent);
            //std::cout << "red uncle" << std::endl;
            
            //getchar();
        }
        else if (node == grandparent->m_right->m_right)
        {
            swapColors(parent, grandparent);
            leftRotate(parent);
            //std::cout << "red uncle" << std::endl;
            
            //getchar();
        }
        // cleanup_checker(m_rootNode);
        // treeChecker();
        return;
    }

    std::shared_ptr<node<K, V>> rotation2(std::shared_ptr<node<K, V>> node)
    {
        auto parent = node->parent();
        auto grandparent = node->grandparent();
        if (!grandparent)
            return NULL;

        swapColors(parent, grandparent);
        color pColor = parent->m_color;
        parent->m_color = grandparent->m_color; // swap colors?
        grandparent->m_color = pColor;
        if (node == grandparent->m_left->m_left) //left/left
            rightRotate(parent);
        else //right/right
            leftRotate(parent);
    }

    void leftRotate(std::shared_ptr<node<K, V>> node)
    {
        auto parent = node->parent();
        if (parent == m_rootNode)
        {
            node->m_prev.reset();
            m_rootNode = node;
        }
            
        parent->m_right = node->m_left;
        node->m_left->m_prev = parent;

        //if == parent right
        auto gp = parent->parent();
        if (gp)
        {
            if (*node->m_key < *parent->m_key)
            {
                gp->m_left = node;
                node->m_prev = gp;
            }
            else if (*node->m_key > *parent->m_key)
            {
                gp->m_right = node;
                node->m_prev = gp;
            }
        }

        node->m_left = parent;
        parent->m_prev = node;
    }

    void rightRotate(std::shared_ptr<node<K, V>> node)
    {
        auto parent = node->parent();
        // redefine reference node to right child similar
        if (parent == m_rootNode)
            m_rootNode = node;

        parent->m_left = node->m_right;
        node->m_right->m_prev = parent;

        auto gp = parent->parent();
        if (gp)
        {
            //if == parent right
            if (*node->m_key < *parent->m_key)
            {
                gp->m_left = node;
                node->m_prev = gp;
            }

            //if == parentleft
            if (*node->m_key > *parent->m_key)
            {
                gp->m_right = node;
                node->m_prev = gp;
            }
        }
        node->m_right = parent;
        parent->m_prev = node;
    }

    void swapColors(std::shared_ptr<node<K, V>> node1, std::shared_ptr<node<K, V>> node2)
    {
        color pColor = node1->m_color;
        node1->m_color = node2->m_color; // swap colors?
        node2->m_color = pColor;
    }

    void delAll()
    {
        m_rootNode.reset();
    }

    /** @breif Track root node */
    std::shared_ptr<node<K, V>> m_rootNode;
};

#endif /* Tree */
