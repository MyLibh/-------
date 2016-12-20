#pragma once

#ifndef __UNCOPYABLE_HPP_INCLUDED__
#define __UNCOPYABLE_HPP_INCLUDED__

class Uncopyable 
{
private:
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);

protected:
	explicit Uncopyable() {}
	virtual ~Uncopyable() {}
};

class UncopyableFull : private Uncopyable
{
private:
	UncopyableFull(UncopyableFull&&);
	UncopyableFull& operator=(UncopyableFull&&);

public:
	explicit UncopyableFull() {}
	virtual ~UncopyableFull() {}
};

#endif // __UNCOPYABLE_HPP_INCLUDED__