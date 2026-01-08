# include "crabsy/dimensions.hpp"

namespace crabsy {
    Seg2Angles get_angles_seg2(Seg2Coords coords) {
        // (Adjust coordinates to default position of leg) (removed for now, variable names have been kept)
        float x = coords.r;
        float y = coords.h;

        // Get hypotenuse from adjusted coordinates
        float c = sqrt(x*x + y*y);

        // Get gamma angle of triangle from reversed law of cosines
        float gamma = acosf((CRABSY_LEG_L2*CRABSY_LEG_L2 + CRABSY_LEG_L3*CRABSY_LEG_L3 - c*c) / (2.0*CRABSY_LEG_L2*CRABSY_LEG_L3));

        // Calculate the remaining angles using law of sines and complimentation
        float alpha = asinf(CRABSY_LEG_L3 * sinf(gamma) / c);
        float beta = PI - alpha - gamma;

        // Helper angle out of hypotenuse
        float sigma = atan2(y, x);

        return Seg2Angles {
            sigma + alpha,
            gamma - atan2f(CRABSY_LEG_Y3, CRABSY_LEG_X3) - (float)PI
        };
    }

    Seg2Coords get_coords_seg2(Seg2Angles angles) {
        return {
            CRABSY_LEG_X2 * cosf(angles.ang2) 
                + CRABSY_LEG_Y2 * -sinf(angles.ang2) 
                + CRABSY_LEG_X3 * cosf(angles.ang2 + angles.ang3) 
                + CRABSY_LEG_Y3 * -sinf(angles.ang2 + angles.ang3),
            CRABSY_LEG_X2 * sinf(angles.ang2) 
                + CRABSY_LEG_Y2 * cosf(angles.ang2) 
                + CRABSY_LEG_X3 * sinf(angles.ang2 + angles.ang3) 
                + CRABSY_LEG_Y3 * cosf(angles.ang2 + angles.ang3)
        };
    }

    Seg3Angles get_angles_seg3(Seg3Coords coords) {
        // Convert coordinates
        float x = coords.r;
        float y = coords.h;
        float z = coords.d;

        // Get real length of foot viewed from above
        float c = sqrt(x*x + z*z);
        // Get angle viewed from above, coordinates are switched to get mathematically correct angle direction
        float ang1 = atan2f(z, x);

        // Get angles for section
        Seg2Angles seg2_ang = get_angles_seg2(Seg2Coords { 
            c, y
        });

        return Seg3Angles {
            ang1,
            seg2_ang.ang2,
            seg2_ang.ang3
        };
    }

    Seg3Coords get_coords_seg3(Seg3Angles angles) {
        Seg2Coords seg2_coords = get_coords_seg2(Seg2Angles {
            angles.ang2,
            angles.ang3
        });

        
    }
}