#pragma once
#include "PathBuilder.h"

int PathBuilder::buildPatch(Algorithm* algorithm, Field& f)
{
    if (!f.canBuild())
        return -1;
    if (!algorithm->buildPath(f.getList()))
        return -1;
    algorithm->findPath(f.getList());
    return 0;
}
