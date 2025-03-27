#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "spheres.h"

/*refrences: 
https://www.geeksforgeeks.org/basics-file-handling-c/
https://users.cs.utah.edu/~germain/PPS/Topics/C_Language/file_IO.html
https://www.programiz.com/c-programming/c-structures-pointers
https://www.reddit.com/r/C_Programming/comments/p8ksv1/what_is_the_difference_between_structs_and/
https://www.youtube.com/watch?v=iAxVfDVBie8
https://www.youtube.com/watch?v=x85upiss898
https://www.youtube.com/watch?v=ezXGTRSx1g8
https://web.cs.wpi.edu/~emmanuel/courses/cs563/write_ups/zackw/realistic_raytracing.html  -didn't really help but read it
For Make File - UNIVERSITY OF ALBERTA CMPUT 201, Lecture 23
https://www.w3schools.com/c/c_files_write.php
*/

Vec3 cameraPos = {0, 0, 0};
float viewportHeight, viewportWidth, focalLength, lightBrightness;
int imageWidth, imageHeight, numOfColours, backgroundColourIndex, numOfSpheres;
Vec3 lightPosition;
Vec3 blackSphere = {1, 1, 1};  //why does this work and not {0,0,0}
Vec3 backgroundColour = {0,0,0};

int main(int argc, char *argv[]) {
    // Open input and output files
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("ERROR: Could not open input file.\n");  //ilya said not to worry but good practice
        return 1;
    }

    fscanf(inputFile, "%d %d", &imageWidth, &imageHeight);
    fscanf(inputFile, "%f", &viewportHeight);
    fscanf(inputFile, "%f", &focalLength);
    fscanf(inputFile, "%f %f %f %f", &lightPosition.x, &lightPosition.y, &lightPosition.z, &lightBrightness);
    fscanf(inputFile, "%d", &numOfColours);

    //colur
    unsigned int allColours[numOfColours];

    for (int i = 0; i < numOfColours; i++) {
        fscanf(inputFile, "%x", &allColours[i]);  //so you can get more colours depending on how many
    }

    fscanf(inputFile, "%d", &backgroundColourIndex);
    fscanf(inputFile, "%d", &numOfSpheres);

    // use world easier for later
    World newWorld;
    worldInit(&newWorld);

    // Loop through the number of spheres and read each sphere's data
    for (int i = 0; i < numOfSpheres; i++) {
        Vec3 spherePosition;
        float sphereRadius;
        int colorIndex;

        // Read sphere data
        fscanf(inputFile, "%f %f %f %f %d", &spherePosition.x, &spherePosition.y, &spherePosition.z, &sphereRadius, &colorIndex);

        // Create and add sphere to the world
        Sphere *newSphere = createSphere(sphereRadius, spherePosition, blackSphere);
        addSphere(&newWorld, newSphere);
    }

    fclose(inputFile);  //like python? close after open????

    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        printf("ERROR: Could not open output file.\n"); //ilya said not to worry but good practice
        freeWorld(&newWorld);
        free(allColours);
        fclose(inputFile);
        return 1;
    }

    // Print vector operations results
    Vec3 result;

    viewportWidth = (((float)imageWidth / imageHeight) * viewportHeight);  // finally done right i think

    // 1. Add
    result = add(backgroundColour, lightPosition);
    fprintf(outputFile, "(%.1f, %.1f, %.1f) + (%.1f, %.1f, %.1f) = (%.1f, %.1f, %.1f)\n",backgroundColour.x, backgroundColour.y, backgroundColour.z, lightPosition.x, lightPosition.y, lightPosition.z,result.x, result.y, result.z);

    // 2. Subtract
    result = subtract(backgroundColour, lightPosition);
    fprintf(outputFile, "(%.1f, %.1f, %.1f) - (%.1f, %.1f, %.1f) = (%.1f, %.1f, %.1f)\n",backgroundColour.x, backgroundColour.y, backgroundColour.z,lightPosition.x, lightPosition.y, lightPosition.z,result.x, result.y, result.z);

    // 3. Scalar Multiply
    result = scalarMultiply(viewportWidth, lightPosition);
    fprintf(outputFile, "%.1f * (%.1f, %.1f, %.1f) = (%.1f, %.1f, %.1f)\n",viewportWidth, lightPosition.x, lightPosition.y, lightPosition.z,result.x, result.y, result.z);

    // 4. Normalize
    result = normalize(lightPosition);
    fprintf(outputFile, "normalize(%.1f, %.1f, %.1f) = (%.1f, %.1f, %.1f)\n",lightPosition.x, lightPosition.y, lightPosition.z,result.x, result.y, result.z);

    // Loop through each sphere and print the required operations
    for (int i = 0; i < newWorld.size; i++) {
        Sphere *sphere = newWorld.spheres[i];

        // 1. Scalar Divide
        result = scalarDivide(sphere->color, sphere->r);
        fprintf(outputFile, "\n(%.1f, %.1f, %.1f) / %.1f = (%.1f, %.1f, %.1f)",sphere->color.x, sphere->color.y, sphere->color.z,sphere->r, result.x, result.y, result.z);

        // 2. Dot Product
        float dotResult = dot(lightPosition, sphere->pos);
        // fprintf(outputFile, "\n%.1f\n",dotResult);  //fix the dotproduct in vector.c
        fprintf(outputFile, "\ndot((%.1f, %.1f, %.1f), (%.1f, %.1f, %.1f)) = %.1f",lightPosition.x, lightPosition.y, lightPosition.z,sphere->pos.x, sphere->pos.y, sphere->pos.z,dotResult);

        // 3. Distance
        float distanceResults = distance(lightPosition, sphere->pos);
        fprintf(outputFile, "\ndistance((%.1f, %.1f, %.1f), (%.1f, %.1f, %.1f)) = %.1f",lightPosition.x, lightPosition.y, lightPosition.z,sphere->pos.x, sphere->pos.y, sphere->pos.z,distanceResults);

        // 4. Length
        float legnthResults = length(sphere->pos);
        fprintf(outputFile, "\nlength(%.1f, %.1f, %.1f) = %.1f",sphere->pos.x, sphere->pos.y, sphere->pos.z,legnthResults);
        fprintf(outputFile, "\n");

        //why printing wrong (extra space)  **fixed ilya said \n before the things not after
    }

    // Close output file and free (no memory leaks)
    fclose(outputFile);
    freeWorld(&newWorld);

    return 0;
}
