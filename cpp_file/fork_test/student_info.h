#ifndef STUDENT_INFO_
#define STUDENT_INFO_

#include <string>

typedef struct
{
    float chiness;
    float math;
    float english;  
}score_t;

class haha
{
private:
    std::string name;
    int age;

    score_t score;
public:
    haha(std::string name_,int age_);
    void show_data();
    virtual ~haha();
    void hello();
};

#endif