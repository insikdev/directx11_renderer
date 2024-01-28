#include "pch.h"
#include "app.h"

int main(int argc, char** argv)
{
    const uint32_t width = 1280;
    const uint32_t height = 720;

    App { width, height }.Run();

    return 0;
}
