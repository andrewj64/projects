
template<class T>
	class SmartLock
{
public:
	SmartLock(T &t);
	~SmartLock();
private:
	T &m_t;
};

template<class T>
SmartLock<T>::SmartLock(T &t)
	: m_t(t)
{
	m_t.lock();
}

template<class T>
SmarLock<T>::~SmartLock()
{
	m_t.unlock();
}