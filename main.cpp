#include <iostream>
#include <boost/random.hpp>
#include "sublogics/sublogic1.h"
#include "structures.h"
#include "static.h"

#include <vector>

int main(int, char**) {
    auto test = "test";

    std::cout << "Hello, world! : " << test<< "\n";


    std::vector<int> ee;
    ee.push_back(11);


    std::cout<<ee.size()<<std::endl;
    

    SubLogic1 test1;
    test1.test();

    SampleStruct sample {1,2};
    std::cout << "Sample struct a:"<<sample.a<< "  b:"<<sample.b<<std::endl;

    std::cout << "this is cmake definitions :"<<CMAKE_DEF_SAMPLE<<std::endl;

    boost::random::mt19937 rng;
    rng.seed(time(nullptr));
    boost::random::uniform_int_distribution<int> r(-10,10);
    std::cout <<"boost random 1~8 :"<< r(rng)<<std::endl;

    std::cout<<"Call Static Library : "<<sampleStatic::testStaticAdd10(10)<<std::endl;
}
