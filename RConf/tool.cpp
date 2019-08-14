#include "configure.h"

int main()
{
	ConfigureControl control("/test.tmpl");
	control.loadConfigure();
	control.publishConfigure();

	return 0;
}
