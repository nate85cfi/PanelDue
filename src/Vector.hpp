/*
 * Vector.hpp
 *
 * Created: 09/11/2014 09:50:41
 *  Author: David
 */ 


#ifndef VECTOR_H_
#define VECTOR_H_

// Bounded vector class
template<class T, size_t N> class Vector
{
public:
	Vector() : filled(0) { }
		
	bool full() const { return filled == N; }
		
	size_t capacity() const { return N; }
		
	size_t size() const { return filled; }
		
	const T& operator[](size_t index) const pre(index < N) { return storage[index]; }

	T& operator[](size_t index) pre(index < N) { return storage[index]; }
		
	void add(const T& x) pre(filled < N) { storage[filled++] = x; }
		
	void add(const T* array p, size_t n) pre(filled + n <= N);
		
	void clear() { filled = 0; }
		
	const T* array c_ptr() { return storage; }

protected:
	T storage[N];
	size_t filled;	
};

template<class T, size_t N> void Vector<T, N>::add(const T* array p, size_t n)
{
	while (n != 0 && filled != N)
	{
		storage[filled++] = *p++;
		--n;
	}
}

#if 0
// Compare a vector of char with a null-terminated string
template<size_t N> int compare(Vector<char, N> v, const char * array s)
{
	for (size_t i = 0; i < v.size(); ++i)
	{
		char c1 = v[i];
		char c2 = *s++;
		if (c1 != c2)
		{
			return (c1 > c2) ? 1 : -1;
		}
	}
	return (*s == '\0') ? 0 : -1;
}
#endif

template<size_t N> class String : public Vector<char, N + 1>
{
public:
	String() : Vector<char, N + 1>()
	{
		this->clear();
	}

	// Redefine 'full' so as to make room for a null terminator
	bool full() const { return this->filled == N; }
		
	// Redefine 'add' to add a null terminator
	void add(char x) pre(this->filled < N)
	{
		this->storage[this->filled++] = x; 
		this->storage[this->filled] = '\0';
	}
		
	const char* array c_str() const { return this->storage; }
		
	void clear()
	{
		this->filled = 0;
		this->storage[0] = '\0'; 
	}
	
	void catFrom(const char* s)
	{
		while (*s != '\0' && this->filled < N)
		{
			this->storage[this->filled++] = *s++;
		}
		this->storage[this->filled] = '\0';
	}
	
	void copyFrom(const char* s)
	{
		this->clear();
		this->catFrom(s);
	}
};

#endif /* VECTOR_H_ */