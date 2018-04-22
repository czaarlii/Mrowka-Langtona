#include "Langton.h"

int main()
{
	langton::Langton sym(10, 1);
	sym.losuj_mrowki(8);
	sym.uruchom();

	return 0;
}