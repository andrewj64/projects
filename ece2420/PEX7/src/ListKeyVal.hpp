#ifndef LISTKEYVAL_HPP
#define LISTKEYVAL_HPP

#include "KeyVal.hpp"
#include <iostream>
#include <memory>
#include <functional>

template <class K, class V>
class ListKeyVal;

template <class K, class V>
class node : public std::enable_shared_from_this<node<K, V>>
{
  friend class ListKeyVal<K, V>;

private:
  node() = default;

  node(const node &other) = delete;

  node &operator=(const node &other)
  {

    if (other.m_key == NULL)
    {
      m_next.reset();
      m_key.reset();
      m_val.reset();
    }
    else
    {
      m_key.reset(new K(*other.m_key));
      m_val.reset(new V(*other.m_val));

      m_next.reset(new node<K, V>());
      *m_next = *(other.m_next);
    }
    return *this;
  }
  std::shared_ptr<K> m_key;
  std::shared_ptr<V> m_val;
  std::shared_ptr<node<K, V>> m_next;
};

template <class K, class V>
class ListKeyVal : public KeyVal<K, V>
{
public:
  ListKeyVal()
  {
    m_rootNode.reset(new node<K, V>());
  }

  ListKeyVal(const ListKeyVal &that)
  {
    m_rootNode.reset(new node<K, V>());
    *this = that;
  }

  ListKeyVal &operator=(const ListKeyVal &other)
  {
    *m_rootNode = *other.m_rootNode;
  }

  virtual void insert(const K &key, const V &val) override
  {
    m_rootNode = insertInternal(key, val);
  }

  virtual void del(const K &key) override
  {
    m_rootNode = delInternal(key);
  }

  virtual std::shared_ptr<V> get(const K &key) override
  {
    auto cur = m_rootNode;
    while (cur->m_key && *cur->m_key != key )
    {
      cur = cur->m_next;
    }
    if (!cur->m_key)
    {
      std::cout << "Key not found!" << std::endl;
      return NULL;
    }
    return cur->m_val;
  }

  virtual void forEach(std::function<void(const K &key, V &val)> callback) override
  {
    auto cur = m_rootNode;
    for (; cur->m_key; cur = cur->m_next)
    {
      callback(*(cur->m_key), *(cur->m_val));
    }
  }

private:
  std::shared_ptr<node<K, V>> insertInternal(const K &key, const V &val)
  {
    auto root = m_rootNode;
    std::shared_ptr<node<K, V>> newNode(new node<K, V>());
    newNode->m_key.reset(new K(key));
    newNode->m_val.reset(new V(val));


    // empty list
    if (!(root->m_key))
    {
      newNode->m_next.reset(new node<K,V>());
      root = newNode;
      return root;
    }

    //cycle to end of list and insert
    auto cur = root;
    std::shared_ptr<node<K, V>> prev;
    while (cur->m_key && *cur->m_key < key)
    {
      prev = cur;
      cur = cur->m_next;
    }

    if(cur->m_key && *cur->m_key == key)
      return root;

    newNode->m_next = cur;
    prev ? prev->m_next = newNode : root = newNode;
    
    return root;
  }

  std::shared_ptr<node<K, V>> delInternal(const K &key)
  {
    auto root = m_rootNode;
    auto cur = m_rootNode;
    std::shared_ptr<node<K,V>> prev(NULL);
    // find key to be deleted
    while(cur->m_key && *cur->m_key != key)
    {
      prev = cur;
      cur = cur->m_next;
    }

    if(!cur->m_key)
    {
      std::cout << "key doesn't exist" << std::endl;
      return root;
    }

    if(!prev)
    {
      root = cur->m_next;
    }
    else
    {
      prev->m_next = cur->m_next;
    }
    return root;
  }

  void delAll()
  {
    m_rootNode.reset();
  }

  std::shared_ptr<node<K, V>> m_rootNode;
};

#endif /* LISTKEYVAL */
