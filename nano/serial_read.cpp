//Reference: https://forum.arduino.cc/index.php?topic=178913.0

#include <stdio.h>
#include <string.h>

char serialPortFilename[] = "/dev/ttyACM0";

int main()
{
    char readBuffer[1024];
    int numBytesRead;

    FILE *serPort = fopen(serialPortFilename, "r");

	if (serPort == NULL)
	{
		printf("ERROR");	
		return 0;
	}

	printf(serialPortFilename);
	printf(":\n");
	while(1)
	{
		memset(readBuffer, 0, 1024);
		fread(readBuffer, sizeof(char),1024,serPort);
		if(sizeof(readBuffer) != 0)
		{
			printf(readBuffer);
		}
	}
	return 0;
}
