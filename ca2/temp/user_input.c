#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char modetemp[1024];
    int modenum;
    int frequency;
} setting;

typedef struct
{
    int min;
    int max;
} freqLimit;

int readArrow();
freqLimit getFreqLimit();
setting getfrequency(setting userSetting);
int adjustFreq(setting userSetting);

int main(void)
{
    setting userSetting;
    userSetting.frequency = adjustFreq(userSetting);

    return 0;
}

int readArrow()
{   
    int int_1 = 0;
    int int_2 = 0;
    int int_3 = 0;

    printf("\nPlease using up and down key to adjust the frequency you want.");
    system("/bin/stty raw");
    scanf("%d", &int_3);
    int_1 = getchar();
    if (int_1 == 27)
    {
        int_2 = getchar();
        int_3 = getchar();
    }
    system("/bin/stty edit");

    return int_3;
}


int adjustFreq(setting userSetting)
{
    int input;
    int status = 1;

    freqLimit frequencyRange;
    frequencyRange.min = 1;
    frequencyRange.max = 300;
    userSetting.frequency = 50; //initialized or default 
    while (status)
    {
        input = readArrow();
        switch (input)
        {
        case 65:
            printf("\n");
            if (userSetting.frequency < frequencyRange.max)
            {
                userSetting.frequency=userSetting.frequency+20;
            }
            else
            {
                printf( "[WARN]   Maximum limit reached, can't add more.\n" );
            }
            break;
        case 66:
            printf("\n");
            if (frequencyRange.min < userSetting.frequency)
            {
                userSetting.frequency=userSetting.frequency-20;
            }
            else
            {   
                printf( "[WARN]   Minimum limit reached, can't reduce more.\n" );
            }
            break;
        case 67:
            printf("Right!\n");
            break;
        case 68:
            printf("Left!\n");
            break;
        case 'q':
            status = 0;
            break;
        default:
            status = 0;
            printf("end editing\n");
            break;
        }
        printf("The current frequency is %d.", userSetting.frequency);
        fflush(stdout);
    }

    return userSetting.frequency;
};