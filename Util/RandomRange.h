#pragma once
#ifndef RANDOMRANGE_H_include
#define RANDOMRANGE_H_include

#include <random>
#include <ctime> // -- for time

class Random {
public:
    static void init()
    {
        // seeding for the first time only!
        static bool init = false;
        if (init == false) {
            srand(time(NULL));
            init = true;
        }
    }

    static int Range(int min, int max) {
        init();
        return min + rand() % (max - min + 1);
    }

    static float RangeF(float min, float max) {
        init();
        //return min + static_cast<float>(rand()) / (static_cast <float> (RAND_MAX / (max - min)));
        float scale = rand() / (float)RAND_MAX; /* [0, 1.0] */
        return min + scale * (max - min);      /* [min, max] */
    }

    //TODO: static Vector3D

    static float ZeroToOne() {
        init();
        return rand() / (RAND_MAX + 1.);
    }

    static float ZeroOrOne() {
        init();
        return (float)Random::Range(0, 1);
    }

private:
    // Disallow creating an instance of this object
    Random() {};
};

#endif // RANDOMRANGE_H_include