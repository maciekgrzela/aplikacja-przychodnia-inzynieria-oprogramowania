#ifndef POROWNYWALNY_H
#define POROWNYWALNY_H


template<typename T>
class Porownywalny
{
public:
    virtual bool operator==(T &inny) = 0;
    virtual ~Porownywalny(){}
};

#endif // POROWNYWALNY_H
