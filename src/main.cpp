#include "loopTxT.h"
#include "winTxt.h"

using namespace std;


int main(int argc, char **argv)
{
	world mainWorld;

	srand(time(NULL));
	termClear();

	txtLoop(mainWorld);
	termClear();
	
	return 0;
}
