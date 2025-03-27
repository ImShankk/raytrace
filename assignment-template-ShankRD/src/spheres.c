#include "spheres.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Initialize world structure
void worldInit(World *world)
{
    world->spheres = malloc(sizeof(Sphere *) * 1);
    world->size = 0;
    world->capacity = 1;
}

// Free allocated memory for the world structure
void freeWorld(World *world)
{
    for (int i = 0; i < world->size; i++)
    {
        free(world->spheres[i]); // Free each individual sphere
    }
    free(world->spheres); // Free the sphere array
    world->spheres = NULL;
    world->size = 0;
    world->capacity = 0;
}

// Add a sphere to the world
void addSphere(World *world, Sphere *sphere)
{
    // Check if resizing is needed
    if (world->size >= world->capacity)
    {
        world->capacity *= 2; // Double the capacity (maybe should equal to size? but this is good for now to make sure no errors so if both are same just make it double instead)
        // Found out since the spheres header defines it with "**"" and not "*""

        /*
        src/spheres.c: In function ‘addSphere’:
        src/spheres.c:31:24: warning: assignment to ‘Sphere **’ {aka ‘struct <anonymous> **’} from incompatible pointer type ‘Sphere *’ {aka ‘struct <anonymous> *’} [-Wincompatible-pointer-types]
        31 |         world->spheres = newSpheres;
           |                        ^
        */

        // answered above
        // not working ask TA why this requires 2 * instead of 1
        Sphere **newSpheres = realloc(world->spheres, sizeof(Sphere *) * world->capacity); // recheck this maybe broken NOT SURE (WATCH BROCODE) //checked with print statements looks fine but unsore if the reallocation is working perfectly???? was an issue before maybe fixed.
        world->spheres = newSpheres;
    }
    world->spheres[world->size] = sphere; // array spot next to add the sphere there
    world->size++;
}

// Create a new sphere and return a pointer to it
Sphere *createSphere(float radius, Vec3 position, Vec3 color)
{
    Sphere *newSphere = malloc(sizeof(Sphere));
    newSphere->r = radius;
    newSphere->pos = position;
    newSphere->color = color;
    return newSphere;
}

// for the function
float calculateDiscriminant(a, b, c)
{
    return ((b * b) - (4 * a * c));
}

void solveQuadratic(float a, float b, float c, float *t1, float *t2) {
    float discriminant = calculateDiscriminant(a, b, c);
    float sqrtDiscriminant = sqrt(discriminant);
    *t1 = (-b - sqrtDiscriminant) / (2 * a);
    *t2 = (-b + sqrtDiscriminant) / (2 * a);
}

int doesIntersect(const Sphere *sphere, Vec3 rayPos, Vec3 rayDir, float *t)
{
    // Sphere center and radius
    Vec3 spherePos = sphere->pos;
    float sphereRadius = sphere->r;

    // Get a, b, c for the quadratic formula
    Vec3 u = subtract(rayPos, spherePos); // Vector from ray origin to sphere center
    float a = dot(rayDir, rayDir);
    float b = 2 * dot(rayDir, u);
    float c = dot(u, u) - (sphereRadius * sphereRadius);

    // Calculate discriminantA
    float discriminant = calculateDiscriminant(a, b, c); // (b^2 - 4ac)

    // Check the discriminant to determine the nature of the roots
    if (discriminant < 0)
    {
        return 0; // No intersection (complex roots)
    }

    // Discriminant is non-negative; real roots exist
    float t1, t2;
    solveQuadratic(a, b, c, &t1, &t2);

    // Check if intersections are behind or in front of the ray origin
    if (t1 >= 0 && t2 >= 0)
    {
        *t = fmin(t1, t2); // Both intersections are in front; choose the closer one
    }
    else if (t1 >= 0)
    {
        *t = t1; // Only t1 is valid
    }
    else if (t2 >= 0)
    {
        *t = t2; // Only t2 is valid
    }
    else
    {
        return 0; // Both intersections are behind the ray origin
    }

    // We can finally find the intersection and normal if needed (not calculated here)
    Vec3 intersectionPoint = add(rayPos, scalarMultiply(*t, rayDir));
    Vec3 normal = subtract(intersectionPoint, spherePos);
    
    return 1; // Intersection found

    // NOTE: the normal vector is called normal but it
    //   does not need to be normalized.

    // Calculate a colour based on these two vectors
}
