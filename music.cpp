#include <windows.h>
#include <mmsystem.h>

int main() {
	PlaySound(TEXT("exit.wav"), NULL, SND_SYNC);
	return 0;
}
