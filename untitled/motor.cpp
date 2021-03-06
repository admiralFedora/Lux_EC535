#include "motor.h"
#include <stdlib.h>
#include <cstring>
motor::motor(int max, const char* device)
{
    char buffR[4];
    char buffW[5];
    this->dev = fopen(device,"rw");
    this->save = fopen("/etc/lux/stepsData","r");
    if(!this->save)
    {
        this->steps = 0;
    }
    else
    {
        fread(buffR,4,1,this->save);
        this->steps = atoi(buffR);
        buffW[0] = 'w';
        strcpy(buffW+1,buffR);
        fwrite(buffW,5,1,dev);
    }
    fclose(this->save);
    this->maxStep = max;
}

int motor::getSteps()
{
    return steps;
}

motor::~motor()
{
    char buffer[10];

    fopen("/etc/lux/stepsData","w");
    // write current position to file
    fread(buffer,10,1,this->dev);
    fwrite(buffer,10,1,save);

    fclose(this->dev);
    fclose(this->save);
}


// error codes
// -1 can't move motor past pos 0
// 0 a-okay
// 1 can't move motor past max pos
// 2 write error
int motor::moveMotor(char dir, int step)
{
    // commanding the motor
    // EX: 'f10' - foward 10 steps
    // EX: 'b50' - backwards 50 steps
    char command[4];

    if(dir == 'b' && steps == 0)
    {
        return -1;
    }
    else if(dir == 'f' && steps == maxStep)
    {
        return 1;
    }


    if(dir == 'b' && steps-step < 0) // prevent the motor from going beyond off pos
    {
        step = steps;
    }
    else if(dir == 'f' && steps+step >= maxStep) // prevent the motor from going beyond the max pos
    {
        step = maxStep - steps;
    }
    sprintf(command,"%c%d",dir,step);
    if(fwrite(command,4,1,dev) != 4)
    {
        return 2;
    }
    return 0;
}
