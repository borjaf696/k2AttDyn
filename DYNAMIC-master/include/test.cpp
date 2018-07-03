#include "dynamic.hpp"

int main(int argc, const char* argv[]){
	printf("Hola\n");
	dyn::suc_bv a;
	printf("A size %d\n",a.size());
	a.push_back(true);
	printf("A size post-chagen %d\n", a.size());
}
