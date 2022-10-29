#include "Input.h"

engine::Input& inputHandler()
{
    static engine::Input input;
    return input;
}
