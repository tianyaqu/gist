#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H


class NonCopyable
{
protected:
    NonCopyable(){}
    ~NonCopyable(){}
private:
    NonCopyable(const NonCopyable&);
    const NonCopyable& operator= (const NonCopyable&);
};

#endif // NONCOPYABLE_H
