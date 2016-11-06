class Uncopyable
{
private:
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);

protected:
	Uncopyable() {}
	~Uncopyable() {}
};