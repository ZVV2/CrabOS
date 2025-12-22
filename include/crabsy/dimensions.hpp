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

    Seg2Coords get_coords_seg2(Seg2Angles angles);

    Seg2Angles get_angles_seg2(Seg2Coords coords);

    // static Seg3Coord get_coords_seg3(Seg3Angles angles) {
    //     Seg2Coord coords = get_coords_seg2(angles);
    //     return {
    //         coords.r,
    //         coords.h,
    //         angles.ang1
    //     };
    // }
}