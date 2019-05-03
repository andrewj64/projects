#ifndef LISTKEYVAL_HPP
#define LISTKEYVAL_HPP

#include "KeyVal.hpp"
#include <iostream>
#include <memory>
#include <functional>

/*********************************************************************
 * This is an example header without any implementation that you
 * may find useful in your effort to create an associative array.
 *
 * You are not required to conform to this header in any way, you are
 * only required to conform to the overall interface header provided
 * in KeyVal.hpp.
 *
 * However, there are helpful hints contained here that may make both
 * this PEX and future PEXes which build on the base interface easier
 * for you to implement.  A careful study of this architecture is 
 * highly recommended. *
 ********************************************************************/

//forward declaration
template <class K, class V>
class ListKeyVal;

/**
 * @class ListKeyValNode
 *
 * The purpose of this class is to store key value pairs in a sorted list.
 * Note that all methods and members are private and only accessible by the
 * friend class ListKeyVal.
 *
 * The reason that the ListKeyValNode class and the ListKeyVal class are 
 * separate is to make usage cleaner.  We must be able to create ListKeyVal 
 * objects on the stack just as we would any other object.  Since additions and
 * deletions to the list may change the root node, it is not effective to 
 * create a root node as the base object
 *
 * This separate private class also allows us to remove some default constuctors
 * and use only deep copy assignment in this class while exposing all options
 * in the public class.
 */
template <class K, class V>
class ListKeyValNode : public std::enable_shared_from_this<ListKeyValNode<K, V>>
{
  friend class ListKeyVal<K, V>;

private:
  /**
   * @brief Default Constructor
   */
  ListKeyValNode() = default;

  ListKeyValNode(const K &key, const V &val, std::shared_ptr<ListKeyValNode> prev, std::shared_ptr<ListKeyValNode> next)
  {
    *m_key = key;
    *m_val = val;
    m_next = next;
    m_prev = prev;
  }
  /**
   * @brief Remove the copy constructor
   */
  ListKeyValNode(const ListKeyValNode &other) = delete;
  /**
   * @brief provide an assignment operator which deep copies our
   * data structure
   *
   * @param other Ref to RHS object; deep copy this structure
   * @return ListKeyNodeVal ref for chaining assignments
   */
  ListKeyValNode &operator=(const ListKeyValNode &other)
  {
    auto prev = m_prev.lock();
    auto otherPrev = other.m_prev.lock();
    m_key.reset(new K());
    m_val.reset(new V());
    m_next.reset(new ListKeyValNode<K, V>());
    prev.reset(new ListKeyValNode<K, V>());
    *m_key = *(other.m_key);
    *m_val = *(other.m_val);
    *m_next = *(other.m_next);
    *prev = *(otherPrev);
    return *this;
    //return shared_from_this();
  }
  /** @brief Ptr to key; may be null for last item in list */
  std::shared_ptr<K> m_key;
  /** @brief Ptr to value; may be null for last item in list */
  std::shared_ptr<V> m_val;
  /** @brief Ptr to next node in list; may be null for last item in list */
  std::shared_ptr<ListKeyValNode> m_next;
  /** @brief Weak ptr to prev node in list; may be null for first item in list 
       note that weak ref is used to avoid mem leak islands*/
  std::weak_ptr<ListKeyValNode<K, V>> m_prev;
};

/**
 * @class ListKeyVal
 */
template <class K, class V>
class ListKeyVal : public KeyVal<K, V>
{
public:
  /**
   * @brief Constructor
   * 
   * This ctor creates a valid root node
   */
  ListKeyVal()
  {
    //m_rootNode = NULL; // make empty node with null prev and next
    m_rootNode.reset(new ListKeyValNode<K, V>());
    auto prev = m_rootNode->m_prev.lock();
    m_rootNode->m_val = NULL;
    m_rootNode->m_key = NULL;
    prev = NULL;
    m_rootNode->m_next = NULL;
  }
  /**
   * @brief Copy ctor
   *
   * Creates a deep copy of entire data structure
   *
   * @param other Data structure to copy
   */
  ListKeyVal(const ListKeyVal &that)
  {
    *this = that;
  }
  /**
   * @brief Assignment operator
   *
   * Creates a deep copy of entire data structure
   *
   * @param other Data structure to copy
   * @return ref to populated object for assignment chaining
   */
  ListKeyVal &operator=(const ListKeyVal &other)
  {
#if 0    
    //loop through list and set individual elements equal
    //delete entire tree
    delAll();
    *m_rootNode = *(other.m_rootNode);
    auto cur = m_rootNode->m_next;
    auto otherCur = other.m_rootNode->m_next;
    for (; cur->m_next; cur = cur->m_next)
    {
      insert(*(cur->m_key), *(cur->m_val));
    }
    insert(*(cur->m_key), *(cur->m_val));

    return *this;
#endif
    m_rootNode = other.m_rootNode;    
  }
  /**
   * @brief Insert an object
   *
   * This will place a COPY of the val object
   * into the associative array
   *
   * Note that since an insert may change the root node, I have 
   * created an "internal" function that returns the new root.
   * this function will call the internal version and then reset
   * the root node if needed.  This model will make follow on
   * PEXs where recursion is required more clean/understandable.
   *
   * @param key Key associated with value
   * @param val Value which is stored at location key
   */
  virtual void insert(const K &key,
                      const V &val) override
  {
    m_rootNode = insertInternal(key, val);
  }
  /**
   * @brief Remove an object from the associative array
   *
   * This will remove the key/value pair from the array
   * If the key is not found, no action is taken
   *
   * Note that since a delete may change the root node, I have 
   * created an "internal" function that returns the new root.
   * this function will call the internal version and then reset
   * the root node if needed.  This model will make follow on
   * PEXs where recursion is required more clean/understandable.
   *
   * @param key Key for which key/val pair is removed
   */
  virtual void del(const K &key) override
  {
    m_rootNode = delInternal(key);
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
    for (; *(cur->m_key) != key && !(cur->m_next); cur = cur->m_next)
    {
    };
    if (!cur->m_next)
    {
      std::cout << "Key not found!" << std::endl;
      return NULL;
    }
    return cur->m_val;
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
    auto cur = m_rootNode;
    for (; cur->m_next; cur = cur->m_next)
    {
      callback(*(cur->m_key), *(cur->m_val));
    }
  }

private:
  /**
   * @brief Insert a node and return new root
   *
   * @param key Key to insert
   * @param val Value associated with key
   * @return New root of node list
   */
  std::shared_ptr<ListKeyValNode<K, V>> insertInternal(const K &key, const V &val)
  {
    //delete any possible duplicates
    auto root = m_rootNode;
    //del(key);
    //std::shared_ptr<ListKeyValNode<K, V>> newNode(new ListKeyValNode<K, V>(key, val, NULL, NULL));
    std::shared_ptr<ListKeyValNode<K, V>> newNode(new ListKeyValNode<K, V>());
    newNode->m_key.reset(new K());
    newNode->m_val.reset(new V());
    *(newNode->m_key) = key;
    *(newNode->m_val) = val;

    // empty list
    if (!(root->m_key))
    {
      root = newNode;
      return root;
    }

    //cycle to end of list and insert
    auto cur = root;
    std::shared_ptr<ListKeyValNode<K, V>> prev(NULL);

    for (; cur->m_next && *(cur->m_key) < key; prev = cur, cur = cur->m_next){
      if (!(cur->m_next) && *(cur->m_key) < key)
      {
        //insert at end of list
        auto prev = newNode->m_prev.lock();
        newNode->m_next = NULL;
        prev = cur;
        cur->m_next = newNode;
        return root;
      }
    }
#if 1           // Hi John! If you uncomment this code, it inserts all of the nodes, but it segfaults when you try to delete.
                // so I stuck with the test that made it all the way to the end with only one node :)
    if (!(cur->m_next) && *(cur->m_key) < key)
      {
        //insert at end of list
        auto prev = newNode->m_prev.lock();
        newNode->m_next = NULL;
        prev = cur;
        cur->m_next = newNode;
        return root;
      }
#endif
    newNode->m_next = cur;
    auto prevTemp = cur->m_prev.lock();
    if (!(prevTemp))
    {
      root = newNode;
    }
    else
    {
      prevTemp->m_next = newNode;
      prevTemp = newNode;
    }
    return root;
  }
  /**
   * @brief Delete a node and return new root
   *
   * @param key Key to insert
   * @return New root of node list
   */
  std::shared_ptr<ListKeyValNode<K, V>> delInternal(const K &key)
  {
    auto cur = m_rootNode;
    // find key to be deleted
    if(!(cur->m_key))
    {
      std::cout << "key is null" << std::endl;
    }
    for (; (cur->m_key) && *(cur->m_key) != key && (cur->m_next); cur = cur->m_next)
    {
    };
    if (!(cur->m_next))
    {
      std::cout << "No key to delete" << std::endl;
      return m_rootNode;
    }
    auto nextPrev = cur->m_next->m_prev.lock();
    auto prev = cur->m_prev.lock();
    // delete
    if (prev)
    {
      nextPrev = prev;
      prev->m_next = nextPrev;
      return m_rootNode;
    }
    else
    {
      nextPrev = NULL;
      auto root = cur->m_next;
      return root;
    }
  }

  void delAll()
  {
    m_rootNode = NULL;
    /*
    auto cur = m_rootNode;
    std::shared_ptr<ListKeyValNode<K, V>> prev;
    for (prev = NULL; cur->m_next; prev = cur, cur = cur->m_next)
    {
      if (prev)
      {
        delete (prev);
      }
    }
    delete (cur);
    */
  }

  /** @breif Track root node */
  std::shared_ptr<ListKeyValNode<K, V>> m_rootNode;
};

#endif /* LISTKEYVAL */
