#ifndef BTREE_HPP
#define BTREE_HPP

#include "KeyVal.hpp"
#include "walrus.h"
#include <iostream>
#include <memory>
#include <functional>

//forward declaration
template <class K, class V>
class bTree;
/** 
 * @class node
 *
 * The purpose of this class is to store key value pairs in a sorted binary tree.
 * Note that all methods and members are private and only accessible by the
 * friend class bTree.
 *
 * The reason that the node class and the bTree class are 
 * separate is to make usage cleaner.  We must be able to create bTree 
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
  friend class bTree<K, V>;

private:
  /**
   * @brief Default Constructor
   */
  node() = default;

  /**
   * @brief Remove the copy constructor
   */
  node(const node &other) = delete;
  /**
   * @brief provide an assignment operator which deep copies our
   * data structure
   */
  node &operator=(const node &other)
  {
    m_prev.reset();
    //m_prev = std::weak_ptr<node<K,V>>();
    if (other.m_key == NULL)
    {
      m_left.reset();
      m_right.reset();
      m_key.reset();
      m_val.reset();
    }
    else
    {
      m_key.reset(new K(*other.m_key));
      // m_key = std::make_shared<K>(*other.m_key));
      m_val.reset(new V(*other.m_val));

      m_left.reset(new node<K, V>());
      m_right.reset(new node<K, V>());
      *m_left = *(other.m_left);
      *m_right = *(other.m_right);
      m_left->m_prev = this->shared_from_this();
      m_right->m_prev = this->shared_from_this();
    }

    return *this;
  }
  std::shared_ptr<K> m_key;
  std::shared_ptr<V> m_val;
  std::shared_ptr<node> m_left;
  std::shared_ptr<node> m_right;
  std::weak_ptr<node<K, V>> m_prev;
};

/**
 * @class bTree
 */
template <class K, class V>
class bTree : public KeyVal<K, V>
{
public:
  /**
   * @brief Constructor
   * 
   * This ctor creates a valid root node
   */
  bTree()
  { 
    m_rootNode.reset(new node<K, V>());
  }

  bTree(const bTree &that)
  {
    m_rootNode.reset(new node<K,V>());
    *this = that;
  }

  bTree &operator=(const bTree &other)
  {
    *m_rootNode = *(other.m_rootNode);
  }

  virtual void insert(const K &key, const V &val) override
  {
    m_rootNode = insertInternal(key, val);
  }

  virtual void del(const K &key) override
  {
    m_rootNode = delInternal(key, m_rootNode);
  }

  /**
   * @brief Get a pointer to value
   *
   * Given a key, a shared_ptr to a value is returned.
   * note that if the key did not exist, then the returned
   * ptr is not valid
   *
   * @param key Key for which value is returned
   * @return ptr to value if key existed
   */
  virtual std::shared_ptr<V> get(const K &key) override
  {
    auto cur = m_rootNode;
    // cycle through tree to find key that matches
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

  /**
   * @brief Execute callback for each entry
   *
   * Rather than force students to create an inner iterator class,
   * this functiona allows a callback function to be executed for
   * every item in the associative array.  Note that callbacks should
   * be called in order of keys sorted least to greatest
   *
   * @param callback Function to be called with each item in the associative array
   */
  virtual void forEach(std::function<void(const K &key, V &val)> callback) override
  {
    if (m_rootNode->m_key == NULL)
    {
      std::cout << "Empty list! Here's a walrus instead." << std::endl;
      walrus();
    }
    forEachInt(callback, m_rootNode);
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
  /**
   * @brief Insert a node and return new root
   *
   * @param key Key to insert
   * @param val Value associated with key
   * @return New root of node list
   */
  std::shared_ptr<node<K, V>> insertInternal(const K &key, const V &val)
  {
    //delete any possible duplicates
    auto root = m_rootNode;
    //del(key);
    std::shared_ptr<node<K, V>> newNode(new node<K, V>());
    newNode->m_key.reset(new K());
    newNode->m_val.reset(new V());
    *(newNode->m_key) = key;
    *(newNode->m_val) = val;
    newNode->m_left.reset(new node<K, V>());
    newNode->m_right.reset(new node<K, V>());

    // check for empty tree
    if (!(root->m_key))
    {
      //std::cout << "inserting " << key << " to empty tree" << std::endl;
      root = newNode;
      return root;
    }

    auto cur = m_rootNode;
    // cycle through tree to find insertion spot
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
          return root;
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
  /**
   * @brief Delete a node and return new root
   *
   * @param key Key to insert
   * @return New root of node list
   */
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
        return root;
      }

      auto prev = cur->m_prev.lock();
      if (!prev)
      {
        std::cout << "Previous is null. This should be root node" << std::endl;
        if (cur == m_rootNode)
        {
          std::cout << "Root. Yay!" << std::endl;
        }
        else
        {
          std::cout << "boo. this isn't root" << std::endl;
        }
        //cur == m_rootNode ? std::cout << "Root. Yay!" << std::endl : std::cout << "for some reason this is not root" << std::endl;
      }
      if (*(prev->m_key) < *(cur->m_key))
      {
        prev->m_right.reset(new node<K, V>());
        ;
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

  void delAll()
  {
    m_rootNode.reset();
  }

  /** @breif Track root node */
  std::shared_ptr<node<K, V>> m_rootNode;
};

#endif /* bTree */
