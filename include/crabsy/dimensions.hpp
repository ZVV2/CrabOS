// #############################
// ##   CRABSY - DIMENSIONS   ##
// #############################
// > Contains all the different sizes and lengths on the crabsy robot for calculations

# pragma once

# include <Arduino.h>
# include <math.h>

# include <sylo/logging.hpp>

/* Lengths of the different leg segments*/
# define CRABSY_LEG_L1 (float)42.0
# define CRABSY_LEG_L2 (float)60.0
# define CRABSY_LEG_L3 (float)92.0

/* X and Y section lengths in neutral position */
# define CRABSY_LEG_X1 (float)42.0
# define CRABSY_LEG_Y1 (float)0.0 

# define CRABSY_LEG_X2 (float)60.0
# define CRABSY_LEG_Y2 (float)0.0

# define CRABSY_LEG_X3 (float)15
# define CRABSY_LEG_Y3 (float)-90.0

# define CRABSY_SEG2_RADIUS (CRABSY_LEG_X2 + CRABSY_LEG_X3)
# define CRABSY_SEG2_HEIGHT (CRABSY_LEG_Y2 + CRABSY_LEG_Y3)


namespace crabsy {
    /* DATATYPES */
        /// Position data for a 2D-Section of the leg
        struct Seg2Coords {
            /// Represents the radius of the leg-endpoint to the core, (X-Coord)
            float r;
            /// Represents the height of the leg-endpoint above the groudn (Y-Coord)
            float h;
        }; 

        struct Seg3Coords : Seg2Coords {
            float phi;
        }; 

        struct Seg2Angles {
            float ang2;
            float ang3;
        };

        struct Seg3Angles : Seg2Angles {
            float ang1;
        };


    /**/

    static Seg2Coords get_coords_seg2(Seg2Angles angles) {
        return {
            CRABSY_LEG_X2 * cos(angles.ang2) + CRABSY_LEG_Y2 * -sin(angles.ang2) + CRABSY_LEG_X3 * cos(angles.ang2 + angles.ang3) + CRABSY_LEG_Y3 * -sin(angles.ang2 + angles.ang3),
            CRABSY_LEG_X2 * sin(angles.ang2) + CRABSY_LEG_Y2 * cos(angles.ang2) + CRABSY_LEG_X3 * sin(angles.ang2 + angles.ang3) + CRABSY_LEG_Y3 * cos(angles.ang2 + angles.ang3)
        };
    }

    static Seg2Angles get_angles_seg2(Seg2Coords coords) {
        // (Adjust coordinates to default position of leg) (removed for now, variable names have been kept)
        float x = coords.r;
        float y = coords.h;

        // Get hypotenuse from adjusted coordinates
        float c = sqrt(x*x + y*y);

        // Get gamma angle of triangle from reversed law of cosines
        float gamma = acos((CRABSY_LEG_L2*CRABSY_LEG_L2 + CRABSY_LEG_L3*CRABSY_LEG_L3 - c*c) / (2.0*CRABSY_LEG_L2*CRABSY_LEG_L3));

        // Calculate the remaining angles using law of sines and complimentation
        float alpha = asin(CRABSY_LEG_L3 * sin(gamma) / c);
        float beta = PI - alpha - gamma;

        // Helper angle out of hypotenuse
        float sigma = atan2(y, x);

        return Seg2Angles {
            sigma + alpha,
            gamma - atan2(CRABSY_LEG_Y3, CRABSY_LEG_X3) - PI
        };
    }

    // static Seg3Coord get_coords_seg3(Seg3Angles angles) {
    //     Seg2Coord coords = get_coords_seg2(angles);
    //     return {
    //         coords.r,
    //         coords.h,
    //         angles.ang1
    //     };
    // }
}