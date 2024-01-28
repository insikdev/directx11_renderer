#include "pch.h"
#include "app.h"

int main(int argc, char** argv)
{
    LONG width = 1280;
    LONG height = 720;

    App { width, height }.Run();

    return 0;
}
