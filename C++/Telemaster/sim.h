#pragma once
#include <cstring>
class sim
{
private:
    struct Internal
    {
        double time;
    } internal;

public:
    struct Input
    {
        double* dt;
    } u;

    struct Output
    {
        double time;
    } y;

    void update();

    double getTime() const;

    double getdt() const;

    static sim& simTime();

private:
    sim();

    static sim instance;
};
