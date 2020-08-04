#pragma once
template < typename T >
class Singleton {
public:
	static T* GetInstance() {
		static MemGuard g; 
		if (!m_instance) {
			m_instance = new T();
		}
		return m_instance;
	}

	Singleton(const Singleton&) = delete;
	Singleton& operator= (const Singleton) = delete;


	Singleton() { };
	virtual ~Singleton() { }

protected:
	static T * m_instance;

	class MemGuard {
	public:
		~MemGuard() {
			delete m_instance;
			m_instance = nullptr;
		}
	};
};

