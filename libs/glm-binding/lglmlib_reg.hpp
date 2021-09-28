/*
** GLM Library registration table: see luaL_Reg.
*/

/* Constructors */
{ "vec", glmVec_vec },
{ "vec1", glmVec_vec1 },
{ "vec2", glmVec_vec2 },
{ "vec3", glmVec_vec3 },
{ "vec4", glmVec_vec4 },
{ "ivec", glmVec_ivec },
{ "ivec1", glmVec_ivec1 },
{ "ivec2", glmVec_ivec2 },
{ "ivec3", glmVec_ivec3 },
{ "ivec4", glmVec_ivec4 },
{ "bvec", glmVec_bvec },
{ "bvec1", glmVec_bvec1 },
{ "bvec2", glmVec_bvec2 },
{ "bvec3", glmVec_bvec3 },
{ "bvec4", glmVec_bvec4 },
{ "qua", glmVec_qua },
{ "quat", glmVec_qua },
{ "mat", glmMat_mat },
{ "mat2x2", glmMat_mat2x2 }, { "mat2", glmMat_mat2x2 },
{ "mat2x3", glmMat_mat2x3 },
{ "mat2x4", glmMat_mat2x4 },
{ "mat3x2", glmMat_mat3x2 },
{ "mat3x3", glmMat_mat3x3 }, { "mat3", glmMat_mat3x3 },
{ "mat3x4", glmMat_mat3x4 },
{ "mat4x2", glmMat_mat4x2 },
{ "mat4x3", glmMat_mat4x3 },
{ "mat4x4", glmMat_mat4x4 }, { "mat4", glmMat_mat4x4 },

/* Object Properties */
GLM_LUA_REG(equal),
GLM_LUA_REG(notEqual),
#if GLM_HAS_CXX11_STL
GLM_LUA_REG(hash),
#endif
GLM_LUA_REG(unpack),
GLM_LUA_REG(to_string),
GLM_LUA_REG(up), /* LUA_VECTOR_EXTENSIONS */
GLM_LUA_REG(right),
GLM_LUA_REG(forward),
GLM_LUA_REG(forwardLH),
GLM_LUA_REG(forwardRH),
GLM_LUA_REG(allEqual),
GLM_LUA_REG(anyNotEqual),

/* Functional Operators */
GLM_LUA_REG(mat_add),
GLM_LUA_REG(mat_sub),
GLM_LUA_REG(mat_mul),
GLM_LUA_REG(mat_negate),

/* Constants */
#if defined(CONSTANTS_HPP) || defined(EXT_SCALAR_CONSTANTS_HPP)
{ "cos_one_over_two", GLM_NULLPTR },
{ "e", GLM_NULLPTR },
{ "epsilon", GLM_NULLPTR },
{ "euler", GLM_NULLPTR },
{ "four_over_pi", GLM_NULLPTR },
{ "golden_ratio", GLM_NULLPTR },
{ "half_pi", GLM_NULLPTR },
{ "ln_ln_two", GLM_NULLPTR },
{ "ln_ten", GLM_NULLPTR },
{ "ln_two", GLM_NULLPTR },
{ "one", GLM_NULLPTR },
{ "one_over_pi", GLM_NULLPTR },
{ "one_over_root_two", GLM_NULLPTR },
{ "one_over_two_pi", GLM_NULLPTR },
//{ "pi", GLM_NULLPTR },
{ "quarter_pi", GLM_NULLPTR },
{ "root_five", GLM_NULLPTR },
{ "root_half_pi", GLM_NULLPTR },
{ "root_ln_four", GLM_NULLPTR },
{ "root_pi", GLM_NULLPTR },
{ "root_three", GLM_NULLPTR },
{ "root_two", GLM_NULLPTR },
{ "root_two_pi", GLM_NULLPTR },
{ "third", GLM_NULLPTR },
{ "three_over_two_pi", GLM_NULLPTR },
{ "two_over_pi", GLM_NULLPTR },
{ "two_over_root_pi", GLM_NULLPTR },
{ "two_pi", GLM_NULLPTR },
{ "two_thirds", GLM_NULLPTR },
{ "zero", GLM_NULLPTR },
{ "epsilon", GLM_NULLPTR },
#endif

#if defined(COMMON_HPP)
GLM_LUA_REG(abs),
{ "fabs", GLM_NAME(abs) }, /* lmathlib alias */
GLM_LUA_REG(ceil),
GLM_LUA_REG(floor),
GLM_LUA_REG(floatBitsToInt),
GLM_LUA_REG(floatBitsToUint),
GLM_LUA_REG(fma),
GLM_LUA_REG(fract),
GLM_LUA_REG(frexp),
GLM_LUA_REG(intBitsToFloat),
GLM_LUA_REG(uintBitsToFloat),
GLM_LUA_REG(isinf),
GLM_LUA_REG(isnan),
GLM_LUA_REG(ldexp),
GLM_LUA_REG(mod),
GLM_LUA_REG(modf),
GLM_LUA_REG(round),
GLM_LUA_REG(roundEven),
GLM_LUA_REG(smoothstep),
GLM_LUA_REG(step),
GLM_LUA_REG(trunc),
GLM_LUA_REG(reverse), /* LUA_VECTOR_EXTENSIONS */
{ "tointeger", GLM_NAME(toint) }, /* lmathlib alias */
#if GLM_HAS_CXX11_STL
GLM_LUA_REG(fdim),
GLM_LUA_REG(hypot),
GLM_LUA_REG(isnormal),
GLM_LUA_REG(isunordered),
GLM_LUA_REG(nearbyint),
GLM_LUA_REG(nextafter),
GLM_LUA_REG(remainder),
GLM_LUA_REG(scalbn),
{ "remquo", GLM_NAME(remainder) }, /* c99, ignore quot */
#endif
#if defined(LUA_GLM_ALIASES)
GLM_LUA_REG(toint),
#endif
#endif

#if defined(COMMON_HPP) || defined(EXT_SCALAR_COMMON_HPP)
GLM_LUA_REG(max),
GLM_LUA_REG(min),
GLM_LUA_REG(fmax),
GLM_LUA_REG(fmin),
GLM_LUA_REG(clamp),
#endif

#if defined(COMMON_HPP) || defined(EXT_MATRIX_COMMON_HPP)
GLM_LUA_REG(mix),
#endif

#if defined(COMMON_HPP) || defined(GTX_LOG_BASE_HPP)
GLM_LUA_REG(sign),
GLM_LUA_REG(signP),
GLM_LUA_REG(signN),
{ "signbit", GLM_NAME(sign) }, /* cmath alias */
#if GLM_HAS_CXX11_STL
GLM_LUA_REG(copysign),
GLM_LUA_REG(fpclassify),
#endif
#endif

#if defined(EXPONENTIAL_HPP)
GLM_LUA_REG(exp2),
GLM_LUA_REG(inversesqrt),
#if GLM_HAS_CXX11_STL
GLM_LUA_REG(expm1),
#endif
#endif

#if defined(EXPONENTIAL_HPP) || defined(EXT_QUATERNION_EXPONENTIAL_HPP) || defined(GTX_LOG_BASE_HPP)
GLM_LUA_REG(exp),
GLM_LUA_REG(log),
GLM_LUA_REG(log2),
GLM_LUA_REG(sqrt),
GLM_LUA_REG(pow),
#if GLM_HAS_CXX11_STL
GLM_LUA_REG(cbrt),
GLM_LUA_REG(log10),
GLM_LUA_REG(log1p),
GLM_LUA_REG(logb),
GLM_LUA_REG(ilogb),
#endif
#endif

#if defined(EXPONENTIAL_HPP) || defined(GTX_EXTERIOR_PRODUCT_HPP) || defined(EXT_QUATERNION_GEOMETRIC_HPP)
GLM_LUA_REG(cross),
#endif

#if defined(GEOMETRIC_HPP)
GLM_LUA_REG(distance),
GLM_LUA_REG(faceforward),
GLM_LUA_REG(reflect),
GLM_LUA_REG(refract),
#if defined(LUA_GLM_ALIASES)
{ "distance_to", GLM_NAME(distance) },
#endif
#endif

#if defined(GEOMETRIC_HPP) || defined(EXT_QUATERNION_GEOMETRIC_HPP)
GLM_LUA_REG(dot),
GLM_LUA_REG(length),
GLM_LUA_REG(normalize),
GLM_LUA_REG(clampLength), /* LUA_VECTOR_EXTENSIONS */
GLM_LUA_REG(scaleLength),
GLM_LUA_REG(direction),
#if defined(LUA_GLM_ALIASES)
{ "norm", GLM_NAME(normalize) },
{ "magnitude", GLM_NAME(length) },
{ "direction_to", GLM_NAME(direction) },
{ "clampMagnitude", GLM_NAME(clampLength) },
{ "scaleMagnitude", GLM_NAME(scaleLength) },
#endif
#endif

#if defined(VECTOR_RELATIONAL_HPP)
GLM_LUA_REG(all),
GLM_LUA_REG(any),
GLM_LUA_REG(not_),
#endif

#if defined(VECTOR_RELATIONAL_HPP) || defined(GTC_QUATERNION_HPP)
GLM_LUA_REG(greaterThan),
GLM_LUA_REG(greaterThanEqual),
GLM_LUA_REG(lessThan),
GLM_LUA_REG(lessThanEqual),
GLM_LUA_REG(ult), /* lmathlib */
GLM_LUA_REG(ulte),
#if GLM_HAS_CXX11_STL
{ "isgreater", GLM_NAME(greaterThan) },
{ "isgreaterequal", GLM_NAME(greaterThanEqual) },
{ "isless", GLM_NAME(lessThan) },
{ "islessequal", GLM_NAME(lessThanEqual) },
/* islessgreater */
#endif
#endif

#if defined(TRIGONOMETRIC_HPP)
GLM_LUA_REG(acos),
GLM_LUA_REG(acosh),
GLM_LUA_REG(asin),
GLM_LUA_REG(asinh),
GLM_LUA_REG(atan),
GLM_LUA_REG(atanh),
GLM_LUA_REG(cos),
GLM_LUA_REG(cosh),
GLM_LUA_REG(degrees),
GLM_LUA_REG(radians),
GLM_LUA_REG(sin),
GLM_LUA_REG(sinh),
GLM_LUA_REG(tan),
GLM_LUA_REG(tanh),
GLM_LUA_REG(sincos), /* LUA_VECTOR_EXTENSION */
#if defined(LUA_GLM_ALIASES)
{ "deg", GLM_NAME(degrees) }, /* NOTE: lmathlib compat */
{ "rad", GLM_NAME(radians) }, /* NOTE: lmathlib compat */
#endif
#endif

#if defined(EXT_SCALAR_INTEGER_HPP) || defined(EXT_VECTOR_INTEGER_HPP)
GLM_LUA_REG(isMultiple),
GLM_LUA_REG(isPowerOfTwo),
GLM_LUA_REG(nextMultiple),
GLM_LUA_REG(nextPowerOfTwo),
GLM_LUA_REG(prevMultiple),
GLM_LUA_REG(prevPowerOfTwo),
#endif

#if defined(GTC_EPSILON_HPP)
GLM_LUA_REG(epsilonEqual),
GLM_LUA_REG(epsilonNotEqual),
#if defined(LUA_GLM_ALIASES)
{ "approx", GLM_NAME(epsilonEqual) },
{ "approximately", GLM_NAME(epsilonEqual) },
#endif
#endif

#if defined(GTC_INTEGER_HPP)
GLM_LUA_REG(iround),
GLM_LUA_REG(uround),
#endif

#if defined(GTC_RANDOM_HPP)
GLM_LUA_REG(ballRand),
GLM_LUA_REG(circularRand),
GLM_LUA_REG(diskRand),
GLM_LUA_REG(gaussRand),
GLM_LUA_REG(linearRand),
GLM_LUA_REG(sphericalRand),
#if defined(_DEBUG)
/* Temporary */
GLM_LUA_REG(srand),
#endif
#endif

#if defined(GTC_RECIPROCAL_HPP)
GLM_LUA_REG(acot),
GLM_LUA_REG(acoth),
GLM_LUA_REG(acsc),
GLM_LUA_REG(acsch),
GLM_LUA_REG(asec),
GLM_LUA_REG(asech),
GLM_LUA_REG(cot),
GLM_LUA_REG(coth),
GLM_LUA_REG(csc),
GLM_LUA_REG(csch),
GLM_LUA_REG(sec),
GLM_LUA_REG(sech),
#endif

#if defined(GTC_ROUND_HPP)
GLM_LUA_REG(ceilMultiple),
GLM_LUA_REG(ceilPowerOfTwo),
GLM_LUA_REG(floorMultiple),
GLM_LUA_REG(floorPowerOfTwo),
GLM_LUA_REG(roundMultiple),
GLM_LUA_REG(roundPowerOfTwo),
GLM_LUA_REG(snap), /* LUA_VECTOR_EXTENSIONS */
#endif

#if defined(GTC_COLOR_SPACE_HPP) && !defined(GLM_FORCE_XYZW_ONLY)
GLM_LUA_REG(convertLinearToSRGB),
GLM_LUA_REG(convertSRGBToLinear),
#endif

#if defined(GTC_NOISE_HPP)
GLM_LUA_REG(perlin),
GLM_LUA_REG(simplex),
#endif

#if defined(GTX_BIT_HPP)
GLM_LUA_REG(highestBitValue),
GLM_LUA_REG(lowestBitValue),
/* powerOfTwoAbove */ /* Deprecated */
/* powerOfTwoBelow */ /* Deprecated */
/* powerOfTwoNearest */ /* Deprecated */
#endif

#if defined(GTX_CLOSEST_POINT_HPP)
GLM_LUA_REG(closestPointOnLine),
#endif

#if defined(GTX_COLOR_ENCODING_HPP)
GLM_LUA_REG(convertD65XYZToD50XYZ),
GLM_LUA_REG(convertD65XYZToLinearSRGB),
GLM_LUA_REG(convertLinearSRGBToD50XYZ),
GLM_LUA_REG(convertLinearSRGBToD65XYZ),
#endif

#if defined(GTX_COLOR_SPACE_HPP) && !defined(GLM_FORCE_XYZW_ONLY)
GLM_LUA_REG(hsvColor),
GLM_LUA_REG(luminosity),
GLM_LUA_REG(rgbColor),
GLM_LUA_REG(saturation),
#endif

#if defined(GTX_COLOR_SPACE_YCOCG_HPP) && !defined(GLM_FORCE_XYZW_ONLY)
GLM_LUA_REG(rgb2YCoCg),
GLM_LUA_REG(rgb2YCoCgR),
GLM_LUA_REG(YCoCg2rgb),
GLM_LUA_REG(YCoCgR2rgb),
#endif

#if defined(GTX_COMMON_HPP)
GLM_LUA_REG(closeBounded),
GLM_LUA_REG(fmod),
GLM_LUA_REG(isdenormal),
GLM_LUA_REG(openBounded),
#endif

#if defined(GTX_COMPATIBILITY_HPP)
GLM_LUA_REG(isfinite),
GLM_LUA_REG(atan2),
GLM_LUA_REG(saturate),
#endif

#if defined(GTX_COMPATIBILITY_HPP) || defined(EXT_QUATERNION_COMMON_HPP)
GLM_LUA_REG(lerp),
#endif

#if defined(GTX_COMPONENT_WISE_HPP)
GLM_LUA_REG(compAdd),
GLM_LUA_REG(compMax),
GLM_LUA_REG(compMin),
GLM_LUA_REG(compMul),
GLM_LUA_REG(compNormalize),
GLM_LUA_REG(compScale),
#endif

#if defined(GTX_EASING_HPP)
GLM_LUA_REG(backEaseIn),
GLM_LUA_REG(backEaseInOut),
GLM_LUA_REG(backEaseOut),
GLM_LUA_REG(bounceEaseIn),
GLM_LUA_REG(bounceEaseInOut),
GLM_LUA_REG(bounceEaseOut),
GLM_LUA_REG(circularEaseIn),
GLM_LUA_REG(circularEaseInOut),
GLM_LUA_REG(circularEaseOut),
GLM_LUA_REG(cubicEaseIn),
GLM_LUA_REG(cubicEaseInOut),
GLM_LUA_REG(cubicEaseOut),
GLM_LUA_REG(elasticEaseIn),
GLM_LUA_REG(elasticEaseInOut),
GLM_LUA_REG(elasticEaseOut),
GLM_LUA_REG(exponentialEaseIn),
GLM_LUA_REG(exponentialEaseInOut),
GLM_LUA_REG(exponentialEaseOut),
GLM_LUA_REG(linearInterpolation),
GLM_LUA_REG(quadraticEaseIn),
GLM_LUA_REG(quadraticEaseInOut),
GLM_LUA_REG(quadraticEaseOut),
GLM_LUA_REG(quarticEaseIn),
GLM_LUA_REG(quarticEaseInOut),
GLM_LUA_REG(quarticEaseOut),
GLM_LUA_REG(quinticEaseIn),
GLM_LUA_REG(quinticEaseInOut),
GLM_LUA_REG(quinticEaseOut),
GLM_LUA_REG(sineEaseIn),
GLM_LUA_REG(sineEaseInOut),
GLM_LUA_REG(sineEaseOut),
#endif

#if defined(GTX_EXTEND_HPP)
GLM_LUA_REG(extend),
#endif

#if defined(GTX_FAST_EXPONENTIAL_HPP)
GLM_LUA_REG(fastExp),
GLM_LUA_REG(fastExp2),
GLM_LUA_REG(fastLog),
GLM_LUA_REG(fastLog2),
GLM_LUA_REG(fastPow),
#endif

#if defined(GTX_FAST_SQUARE_ROOT_HPP)
GLM_LUA_REG(fastDistance),
GLM_LUA_REG(fastInverseSqrt),
GLM_LUA_REG(fastLength),
GLM_LUA_REG(fastNormalize),
GLM_LUA_REG(fastSqrt),
#endif

#if defined(GTX_FAST_TRIGONOMETRY_HPP)
GLM_LUA_REG(fastAcos),
GLM_LUA_REG(fastAsin),
GLM_LUA_REG(fastAtan),
GLM_LUA_REG(fastCos),
GLM_LUA_REG(fastSin),
GLM_LUA_REG(fastTan),
GLM_LUA_REG(wrapAngle),
#endif

#if defined(GTX_FUNCTIONS_HPP)
GLM_LUA_REG(gauss),
GLM_LUA_REG(moveTowards), /* LUA_VECTOR_EXTENSIONS */
GLM_LUA_REG(smoothDamp),
GLM_LUA_REG(rotateTowards), /* LUA_QUATERNION_EXTENSIONS */
#if GLM_HAS_CXX11_STL
GLM_LUA_REG(erf),
GLM_LUA_REG(erfc),
GLM_LUA_REG(lgamma),
GLM_LUA_REG(tgamma),
#endif
#if defined(LUA_GLM_ALIASES)
{ "move_toward", GLM_NAME(moveTowards) },
#endif
#endif

#if defined(GTX_GRADIENT_PAINT_HPP)
GLM_LUA_REG(linearGradient),
GLM_LUA_REG(radialGradient),
#endif

#if defined(GTX_HANDED_COORDINATE_SPACE_HPP)
GLM_LUA_REG(leftHanded),
GLM_LUA_REG(rightHanded),
#endif

#if defined(GTX_INTEGER_HPP)
GLM_LUA_REG(factorial),
GLM_LUA_REG(nlz),
#endif

#if defined(GTX_INTERSECT_HPP)
GLM_LUA_REG(intersectLineSphere),
GLM_LUA_REG(intersectLineTriangle),
GLM_LUA_REG(intersectRayPlane),
GLM_LUA_REG(intersectRaySphere),
GLM_LUA_REG(intersectRayTriangle),
#endif

#if defined(GTX_MIXED_PRODUCT_HPP)
GLM_LUA_REG(mixedProduct),
#endif

#if defined(GTX_NORM_HPP)
GLM_LUA_REG(distance2),
GLM_LUA_REG(l1Norm),
GLM_LUA_REG(l2Norm),
GLM_LUA_REG(length2),
GLM_LUA_REG(lxNorm),
GLM_LUA_REG(lMaxNorm),
#if defined(LUA_GLM_ALIASES)
{ "sqrLength", GLM_NAME(length2) },
{ "sqrMagnitude", GLM_NAME(length2) },
{ "lengthSquared", GLM_NAME(length2) },
{ "length_squared", GLM_NAME(length2) },
{ "distanceSquared", GLM_NAME(distance2) },
{ "distance_squared_to", GLM_NAME(distance2) },
#endif
#endif

#if defined(GTX_NORMAL_HPP)
GLM_LUA_REG(triangleNormal),
#endif

#if defined(GTX_NORMAL_HPP) || defined(GTX_NORMALIZE_DOT_HPP)
GLM_LUA_REG(fastNormalizeDot),
#endif

#if defined(GTX_NORMALIZE_DOT_HPP)
GLM_LUA_REG(normalizeDot),
#endif

#if defined(GTX_OPTIMUM_POW_HPP)
GLM_LUA_REG(pow2),
GLM_LUA_REG(pow3),
GLM_LUA_REG(pow4),
#endif

#if defined(GTX_ORTHONORMALIZE_HPP)
GLM_LUA_REG(orthonormalize),
GLM_LUA_REG(orthonormalize3), /* LUA_VECTOR_EXTENSIONS */
#endif

#if defined(GTX_PERPENDICULAR_HPP)
GLM_LUA_REG(perp),
GLM_LUA_REG(isPerpendicular), /* LUA_VECTOR_EXTENSIONS */
GLM_LUA_REG(perpendicular),
GLM_LUA_REG(perpendicular2),
GLM_LUA_REG(perpendicularBasis),
GLM_LUA_REG(perpendicularFast),
#if defined(LUA_GLM_ALIASES)
{ "basis", GLM_NAME(perpendicularBasis) },
{ "from_z", GLM_NAME(perpendicularFast) },
#endif
#endif

#if defined(GTX_POLAR_COORDINATES_HPP)
GLM_LUA_REG(euclidean),
GLM_LUA_REG(polar),
#endif

#if defined(GTX_PROJECTION_HPP)
GLM_LUA_REG(proj),
GLM_LUA_REG(projNorm), /* LUA_VECTOR_EXTENSIONS */
GLM_LUA_REG(projPlane),
GLM_LUA_REG(projDecompose),
#endif

#if defined(GLM_HAS_RANGE_FOR) || defined(GTX_RANGE_HPP)
GLM_LUA_REG(components),
//GLM_LUA_REG(begin),
//GLM_LUA_REG(end),
#endif

#if defined(GTX_ROTATE_VECTOR_HPP)
GLM_LUA_REG(orientation),
GLM_LUA_REG(rotateX),
GLM_LUA_REG(rotateY),
GLM_LUA_REG(rotateZ),
#endif

#if defined(GTX_ROTATE_VECTOR_HPP) || defined(EXT_QUATERNION_COMMON_HPP)
GLM_LUA_REG(slerp),
GLM_LUA_REG(barycentric), /* LUA_VECTOR_EXTENSIONS */
#endif

#if defined(GTX_ROTATE_VECTOR_HPP) || defined(EXT_MATRIX_TRANSFORM_HPP) || defined(GTX_MATRIX_TRANSFORM_2D_HPP) || defined(GTX_QUATERNION_TRANSFORM_HPP)
GLM_LUA_REG(rotate),
GLM_LUA_REG(transformPos), /* LUA_MATRIX_EXTENSIONS */
GLM_LUA_REG(transformPosPerspective),
GLM_LUA_REG(transformDir),
GLM_LUA_REG(rotateFromTo), /* LUA_QUATERNION_EXTENSIONS */
#endif

#if defined(GTX_SPLINE_HPP)
GLM_LUA_REG(catmullRom),
GLM_LUA_REG(cubic),
GLM_LUA_REG(hermite),
#if defined(LUA_GLM_ALIASES)
{ "cubic_interpolate", GLM_NAME(catmullRom) },
#endif
#endif

#if defined(GTX_TEXTURE_HPP)
GLM_LUA_REG(levels),
#endif

#if defined(GTX_TRANSFORM_HPP) || defined(EXT_MATRIX_TRANSFORM_HPP)
GLM_LUA_REG(scale),
GLM_LUA_REG(translate),
GLM_LUA_REG(trs), /* LUA_MATRIX_EXTENSIONS */
#endif

#if defined(GTX_VECTOR_ANGLE_HPP)
GLM_LUA_REG(angle),
GLM_LUA_REG(orientedAngle),
#if defined(LUA_GLM_ALIASES)
{ "angle_to", GLM_NAME(angle) },
{ "signedAngle", GLM_NAME(orientedAngle) },
{ "signed_angle_to", GLM_NAME(orientedAngle) },
#endif
#endif

#if defined(GTX_VECTOR_QUERY_HPP)
GLM_LUA_REG(areCollinear),
GLM_LUA_REG(areOrthogonal),
GLM_LUA_REG(areOrthonormal),
GLM_LUA_REG(isCompNull),
#endif

#if defined(GTX_VECTOR_QUERY_HPP) || defined(GTX_MATRIX_QUERY_HPP)
GLM_LUA_REG(isNormalized),
GLM_LUA_REG(isNull),
GLM_LUA_REG(isUniform), /* LUA_VECTOR_EXTENSIONS */
#if defined(LUA_GLM_ALIASES)
{ "isZero", GLM_NAME(isNull) },
{ "isEmpty", GLM_NAME(isNull) },
{ "is_normalized", GLM_NAME(isNormalized) },
#endif
#endif

#if defined(GTX_WRAP_HPP) || defined(EXT_SCALAR_COMMON_HPP)
GLM_LUA_REG(mirrorClamp),
GLM_LUA_REG(mirrorRepeat),
GLM_LUA_REG(repeat),
GLM_LUA_REG(deltaAngle), /* LUA_VECTOR_EXTENSIONS */
GLM_LUA_REG(loopRepeat),
GLM_LUA_REG(pingPong),
GLM_LUA_REG(lerpAngle),
#endif

/* Bitfield */
#if defined(INTEGER_HPP)
#if LUA_INT_TYPE != LUA_INT_INT || !defined(GLM_FORCE_DEFAULT_ALIGNED_GENTYPES)
GLM_LUA_REG(bitCount),
#endif
GLM_LUA_REG(bitfieldExtract),
GLM_LUA_REG(bitfieldInsert),
#if LUA_INT_TYPE != LUA_INT_INT || !defined(GLM_FORCE_DEFAULT_ALIGNED_GENTYPES)
GLM_LUA_REG(bitfieldReverse),
#endif
GLM_LUA_REG(findLSB),
GLM_LUA_REG(findMSB),
//GLM_LUA_REG(imulExtended),
//GLM_LUA_REG(uaddCarry),
//GLM_LUA_REG(umulExtended),
//GLM_LUA_REG(usubBorrow),
#endif

#if defined(EXT_SCALAR_INTEGER_HPP) || defined(EXT_VECTOR_INTEGER_HPP)
GLM_LUA_REG(findNSB),
#endif

#if defined(GTC_BITFIELD_HPP)
GLM_LUA_REG(bitfieldDeinterleave),
GLM_LUA_REG(bitfieldFillOne),
GLM_LUA_REG(bitfieldFillZero),
GLM_LUA_REG(bitfieldInterleave),
GLM_LUA_REG(bitfieldRotateLeft),
GLM_LUA_REG(bitfieldRotateRight),
GLM_LUA_REG(mask),
#endif

#if defined(GTX_BIT_HPP)
GLM_LUA_REG(highestBitValue),
GLM_LUA_REG(lowestBitValue),
#endif

#if defined(PACKING_HPP)
GLM_LUA_REG(packUnorm2x16),
GLM_LUA_REG(packSnorm2x16),
GLM_LUA_REG(packUnorm4x8),
GLM_LUA_REG(packSnorm4x8),
GLM_LUA_REG(unpackUnorm2x16),
GLM_LUA_REG(unpackSnorm2x16),
GLM_LUA_REG(unpackUnorm4x8),
GLM_LUA_REG(unpackSnorm4x8),
GLM_LUA_REG(packDouble2x32),
GLM_LUA_REG(unpackDouble2x32),
GLM_LUA_REG(packHalf2x16),
GLM_LUA_REG(unpackHalf2x16),
#endif

#if defined(GTC_TYPE_PRECISION_HPP)
GLM_LUA_REG(packUnorm1x8),
GLM_LUA_REG(unpackUnorm1x8),
GLM_LUA_REG(packUnorm2x8),
GLM_LUA_REG(unpackUnorm2x8),
GLM_LUA_REG(packSnorm1x8),
GLM_LUA_REG(unpackSnorm1x8),
GLM_LUA_REG(packSnorm2x8),
GLM_LUA_REG(unpackSnorm2x8),
GLM_LUA_REG(packUnorm1x16),
GLM_LUA_REG(unpackUnorm1x16),
GLM_LUA_REG(packUnorm4x16),
GLM_LUA_REG(unpackUnorm4x16),
GLM_LUA_REG(packSnorm1x16),
GLM_LUA_REG(unpackSnorm1x16),
GLM_LUA_REG(packSnorm4x16),
GLM_LUA_REG(unpackSnorm4x16),
GLM_LUA_REG(packHalf1x16),
GLM_LUA_REG(unpackHalf1x16),
GLM_LUA_REG(packHalf4x16),
GLM_LUA_REG(unpackHalf4x16),
GLM_LUA_REG(packI3x10_1x2),
GLM_LUA_REG(unpackI3x10_1x2),
GLM_LUA_REG(packU3x10_1x2),
GLM_LUA_REG(unpackU3x10_1x2),
GLM_LUA_REG(packSnorm3x10_1x2),
GLM_LUA_REG(unpackSnorm3x10_1x2),
GLM_LUA_REG(packUnorm3x10_1x2),
GLM_LUA_REG(unpackUnorm3x10_1x2),
GLM_LUA_REG(packF2x11_1x10),
GLM_LUA_REG(unpackF2x11_1x10),
GLM_LUA_REG(packF3x9_E1x5),
GLM_LUA_REG(unpackF3x9_E1x5),
GLM_LUA_REG(packRGBM),
GLM_LUA_REG(unpackRGBM),
GLM_LUA_REG(packHalf),
GLM_LUA_REG(unpackHalf),
GLM_LUA_REG(packUnorm),
GLM_LUA_REG(unpackUnorm),
GLM_LUA_REG(packSnorm),
GLM_LUA_REG(unpackSnorm),
GLM_LUA_REG(packUnorm2x4),
GLM_LUA_REG(unpackUnorm2x4),
GLM_LUA_REG(packUnorm4x4),
GLM_LUA_REG(unpackUnorm4x4),
GLM_LUA_REG(packUnorm1x5_1x6_1x5),
GLM_LUA_REG(unpackUnorm1x5_1x6_1x5),
GLM_LUA_REG(packUnorm3x5_1x1),
GLM_LUA_REG(unpackUnorm3x5_1x1),
GLM_LUA_REG(packUnorm2x3_1x2),
GLM_LUA_REG(unpackUnorm2x3_1x2),
GLM_LUA_REG(packInt2x8),
GLM_LUA_REG(unpackInt2x8),
GLM_LUA_REG(packUint2x8),
GLM_LUA_REG(unpackUint2x8),
GLM_LUA_REG(packInt4x8),
GLM_LUA_REG(unpackInt4x8),
GLM_LUA_REG(packUint4x8),
GLM_LUA_REG(unpackUint4x8),
GLM_LUA_REG(packInt2x16),
GLM_LUA_REG(unpackInt2x16),
GLM_LUA_REG(packInt4x16),
GLM_LUA_REG(unpackInt4x16),
GLM_LUA_REG(packUint2x16),
GLM_LUA_REG(unpackUint2x16),
GLM_LUA_REG(packUint4x16),
GLM_LUA_REG(unpackUint4x16),
GLM_LUA_REG(packInt2x32),
GLM_LUA_REG(unpackInt2x32),
GLM_LUA_REG(packUint2x32),
GLM_LUA_REG(unpackUint2x32),
#endif

#if defined(GTC_ULP_HPP)
GLM_LUA_REG(float_distance),
#endif

#if defined(GTC_ULP_HPP) || defined(EXT_SCALAR_ULP_HPP) || defined(EXT_VECTOR_ULP_HPP)
GLM_LUA_REG(next_float),
GLM_LUA_REG(prev_float),
#endif

/* Additional Quaternion */
#if defined(EXT_QUATERNION_COMMON_HPP)
GLM_LUA_REG(conjugate),
#endif

#if defined(EXT_QUATERNION_COMMON_HPP) || defined(MATRIX_HPP)
GLM_LUA_REG(inverse),
GLM_LUA_REG(invertible), /* LUA_MATRIX_EXTENSIONS */
#endif

#if defined(EXT_QUATERNION_TRIGONOMETRIC_HPP)
GLM_LUA_REG(axis),
GLM_LUA_REG(angleAxis),
#endif

#if defined(GTC_QUATERNION_HPP)
GLM_LUA_REG(eulerAngles),
GLM_LUA_REG(mat3_cast),
GLM_LUA_REG(mat4_cast),
GLM_LUA_REG(pitch),
GLM_LUA_REG(roll),
GLM_LUA_REG(yaw),
GLM_LUA_REG(quatLookAt),
GLM_LUA_REG(quatLookAtLH),
GLM_LUA_REG(quatLookAtRH),
GLM_LUA_REG(quatbillboardRH), /* LUA_QUATERNION_EXTENSIONS */
GLM_LUA_REG(quatbillboardLH),
GLM_LUA_REG(quatbillboard),
#if defined(LUA_GLM_ALIASES)
{ "quatlookRotation", glm_quatLookAt },
{ "quatlookRotationRH", glm_quatLookAtRH },
{ "quatlookRotationLH", glm_quatLookAtLH },
#endif
#endif

#if defined(GTX_QUATERNION_HPP)
GLM_LUA_REG(extractRealComponent),
GLM_LUA_REG(fastMix),
GLM_LUA_REG(intermediate),
GLM_LUA_REG(rotation),
GLM_LUA_REG(shortMix),
GLM_LUA_REG(squad),
GLM_LUA_REG(toMat3),
GLM_LUA_REG(toMat4),
GLM_LUA_REG(quat_cast),
GLM_LUA_REG(quat_identity),
{ "toQuat", glm_quat_cast }, /* Invokes quat_cast regardless */
#endif

#if defined(GTX_ROTATE_NORMALIZED_AXIS_HPP)
GLM_LUA_REG(rotateNormalizedAxis),
#endif

#if defined(MATRIX_HPP)
GLM_LUA_REG(determinant),
GLM_LUA_REG(matrixCompMult),
GLM_LUA_REG(outerProduct),
GLM_LUA_REG(transpose),
#endif

#if defined(EXT_MATRIX_CLIP_SPACE_HPP)
GLM_LUA_REG(frustum),
GLM_LUA_REG(frustumLH),
GLM_LUA_REG(frustumLH_NO),
GLM_LUA_REG(frustumLH_ZO),
GLM_LUA_REG(frustumNO),
GLM_LUA_REG(frustumRH),
GLM_LUA_REG(frustumRH_NO),
GLM_LUA_REG(frustumRH_ZO),
GLM_LUA_REG(frustumZO),
GLM_LUA_REG(infinitePerspective),
GLM_LUA_REG(infinitePerspectiveLH),
GLM_LUA_REG(infinitePerspectiveRH),
GLM_LUA_REG(ortho),
GLM_LUA_REG(orthoLH),
GLM_LUA_REG(orthoLH_NO),
GLM_LUA_REG(orthoLH_ZO),
GLM_LUA_REG(orthoNO),
GLM_LUA_REG(orthoRH),
GLM_LUA_REG(orthoRH_NO),
GLM_LUA_REG(orthoRH_ZO),
GLM_LUA_REG(orthoZO),
GLM_LUA_REG(perspective),
GLM_LUA_REG(perspectiveFov),
GLM_LUA_REG(perspectiveFovLH),
GLM_LUA_REG(perspectiveFovLH_NO),
GLM_LUA_REG(perspectiveFovLH_ZO),
GLM_LUA_REG(perspectiveFovNO),
GLM_LUA_REG(perspectiveFovRH),
GLM_LUA_REG(perspectiveFovRH_NO),
GLM_LUA_REG(perspectiveFovRH_ZO),
GLM_LUA_REG(perspectiveFovZO),
GLM_LUA_REG(perspectiveLH),
GLM_LUA_REG(perspectiveLH_NO),
GLM_LUA_REG(perspectiveLH_ZO),
GLM_LUA_REG(perspectiveNO),
GLM_LUA_REG(perspectiveRH),
GLM_LUA_REG(perspectiveRH_NO),
GLM_LUA_REG(perspectiveRH_ZO),
GLM_LUA_REG(perspectiveZO),
GLM_LUA_REG(tweakedInfinitePerspective),
#endif

#if defined(EXT_MATRIX_TRANSFORM_HPP) || defined(GTX_MATRIX_TRANSFORM_2D_HPP)
GLM_LUA_REG(identity),
GLM_LUA_REG(lookAt),
GLM_LUA_REG(lookAtLH),
GLM_LUA_REG(lookAtRH),
GLM_LUA_REG(lookRotation), /* LUA_MATRIX_EXTENSIONS */
GLM_LUA_REG(lookRotationRH),
GLM_LUA_REG(lookRotationLH),
GLM_LUA_REG(billboard),
GLM_LUA_REG(billboardRH),
GLM_LUA_REG(billboardLH),
#endif

#if defined(EXT_MATRIX_PROJECTION_HPP)
GLM_LUA_REG(pickMatrix),
GLM_LUA_REG(project),
GLM_LUA_REG(projectNO),
GLM_LUA_REG(projectZO),
GLM_LUA_REG(unProject),
GLM_LUA_REG(unProjectNO),
GLM_LUA_REG(unProjectZO),
GLM_LUA_REG(rayPicking), /* LUA_VECTOR_EXTENSIONS */
GLM_LUA_REG(containsProjection), /* LUA_MATRIX_EXTENSIONS */
#endif

#if defined(GTC_MATRIX_ACCESS_HPP)
GLM_LUA_REG(column),
GLM_LUA_REG(row),
#if defined(LUA_GLM_ALIASES)
{ "getColumn", GLM_NAME(column) }, /* Unity Alias */
{ "getRow", GLM_NAME(row) }, /* Unity Alias */
#endif
#endif

#if defined(GTC_MATRIX_INVERSE_HPP)
GLM_LUA_REG(affineInverse),
GLM_LUA_REG(inverseTranspose),
#endif

#if defined(GTX_EULER_ANGLES_HPP)
GLM_LUA_REG(orientate2),
GLM_LUA_REG(orientate3),
GLM_LUA_REG(orientate4),
GLM_LUA_REG(yawPitchRoll),
GLM_LUA_REG(derivedEulerAngleX),
GLM_LUA_REG(derivedEulerAngleY),
GLM_LUA_REG(derivedEulerAngleZ),
GLM_LUA_REG(eulerAngleX),
GLM_LUA_REG(eulerAngleXY),
GLM_LUA_REG(eulerAngleXYX),
GLM_LUA_REG(eulerAngleXYZ),
GLM_LUA_REG(eulerAngleXZ),
GLM_LUA_REG(eulerAngleXZX),
GLM_LUA_REG(eulerAngleXZY),
GLM_LUA_REG(eulerAngleY),
GLM_LUA_REG(eulerAngleYX),
GLM_LUA_REG(eulerAngleYXY),
GLM_LUA_REG(eulerAngleYXZ),
GLM_LUA_REG(eulerAngleYZ),
GLM_LUA_REG(eulerAngleYZX),
GLM_LUA_REG(eulerAngleYZY),
GLM_LUA_REG(eulerAngleZ),
GLM_LUA_REG(eulerAngleZX),
GLM_LUA_REG(eulerAngleZXY),
GLM_LUA_REG(eulerAngleZXZ),
GLM_LUA_REG(eulerAngleZY),
GLM_LUA_REG(eulerAngleZYX),
GLM_LUA_REG(eulerAngleZYZ),
GLM_LUA_REG(extractEulerAngleXYX),
GLM_LUA_REG(extractEulerAngleXYZ),
GLM_LUA_REG(extractEulerAngleXZX),
GLM_LUA_REG(extractEulerAngleXZY),
GLM_LUA_REG(extractEulerAngleYXY),
GLM_LUA_REG(extractEulerAngleYXZ),
GLM_LUA_REG(extractEulerAngleYZX),
GLM_LUA_REG(extractEulerAngleYZY),
GLM_LUA_REG(extractEulerAngleZXY),
GLM_LUA_REG(extractEulerAngleZXZ),
GLM_LUA_REG(extractEulerAngleZYX),
GLM_LUA_REG(extractEulerAngleZYZ),
GLM_LUA_REG(quatEulerAngleX), /* LUA_QUATERNION_EXTENSIONS */
GLM_LUA_REG(quatEulerAngleXY),
GLM_LUA_REG(quatEulerAngleXYX),
GLM_LUA_REG(quatEulerAngleXYZ),
GLM_LUA_REG(quatEulerAngleXZ),
GLM_LUA_REG(quatEulerAngleXZX),
GLM_LUA_REG(quatEulerAngleXZY),
GLM_LUA_REG(quatEulerAngleY),
GLM_LUA_REG(quatEulerAngleYX),
GLM_LUA_REG(quatEulerAngleYXY),
GLM_LUA_REG(quatEulerAngleYXZ),
GLM_LUA_REG(quatEulerAngleYZ),
GLM_LUA_REG(quatEulerAngleYZX),
GLM_LUA_REG(quatEulerAngleYZY),
GLM_LUA_REG(quatEulerAngleZ),
GLM_LUA_REG(quatEulerAngleZX),
GLM_LUA_REG(quatEulerAngleZXY),
GLM_LUA_REG(quatEulerAngleZXZ),
GLM_LUA_REG(quatEulerAngleZY),
GLM_LUA_REG(quatEulerAngleZYX),
GLM_LUA_REG(quatEulerAngleZYZ),
#if defined(LUA_GLM_ALIASES)
{ "eulerX", glm_eulerAngleX },
{ "eulerXY", glm_eulerAngleXY },
{ "eulerXYX", glm_eulerAngleXYX },
{ "eulerXYZ", glm_eulerAngleXYZ },
{ "eulerXZ", glm_eulerAngleXZ },
{ "eulerXZX", glm_eulerAngleXZX },
{ "eulerXZY", glm_eulerAngleXZY },
{ "eulerY", glm_eulerAngleY },
{ "eulerYX", glm_eulerAngleYX },
{ "eulerYXY", glm_eulerAngleYXY },
{ "eulerYXZ", glm_eulerAngleYXZ },
{ "eulerYZ", glm_eulerAngleYZ },
{ "eulerYZX", glm_eulerAngleYZX },
{ "eulerYZY", glm_eulerAngleYZY },
{ "eulerZ", glm_eulerAngleZ },
{ "eulerZX", glm_eulerAngleZX },
{ "eulerZXY", glm_eulerAngleZXY },
{ "eulerZXZ", glm_eulerAngleZXZ },
{ "eulerZY", glm_eulerAngleZY },
{ "eulerZYX", glm_eulerAngleZYX },
{ "eulerZYZ", glm_eulerAngleZYZ },
#endif
#endif

#if defined(GTX_MATRIX_CROSS_PRODUCT_HPP)
GLM_LUA_REG(matrixCross3),
GLM_LUA_REG(matrixCross4),
#endif

#if defined(GTX_MATRIX_DECOMPOSE_HPP)
GLM_LUA_REG(decompose),
#endif

#if defined(GTX_MATRIX_FACTORISATION_HPP)
GLM_LUA_REG(fliplr),
GLM_LUA_REG(flipud),
GLM_LUA_REG(qr_decompose),
GLM_LUA_REG(rq_decompose),
#endif

#if defined(GTX_MATRIX_INTERPOLATION_HPP)
GLM_LUA_REG(axisAngle),
GLM_LUA_REG(axisAngleMatrix),
GLM_LUA_REG(extractMatrixRotation),
GLM_LUA_REG(interpolate),
#endif

#if defined(GTX_MATRIX_MAJOR_STORAGE_HPP)
GLM_LUA_REG(colMajor2),
GLM_LUA_REG(colMajor3),
GLM_LUA_REG(colMajor4),
GLM_LUA_REG(rowMajor2),
GLM_LUA_REG(rowMajor3),
GLM_LUA_REG(rowMajor4),
GLM_LUA_REG(colMajor),
GLM_LUA_REG(rowMajor),
#endif

#if defined(GTX_MATRIX_OPERATION_HPP)
GLM_LUA_REG(adjugate),
GLM_LUA_REG(diagonal2x2),
GLM_LUA_REG(diagonal2x3),
GLM_LUA_REG(diagonal2x4),
GLM_LUA_REG(diagonal3x2),
GLM_LUA_REG(diagonal3x3),
GLM_LUA_REG(diagonal3x4),
GLM_LUA_REG(diagonal4x2),
GLM_LUA_REG(diagonal4x3),
GLM_LUA_REG(diagonal4x4),
#endif

#if defined(GTX_MATRIX_QUERY_HPP)
GLM_LUA_REG(isIdentity),
GLM_LUA_REG(isOrthogonal),
GLM_LUA_REG(extractScale), /* LUA_MATRIX_EXTENSIONS */
GLM_LUA_REG(hasUniformScale),
#endif

#if defined(GTX_TRANSFORM2_HPP)
GLM_LUA_REG(proj2D),
GLM_LUA_REG(proj3D),
GLM_LUA_REG(scaleBias),
GLM_LUA_REG(shearX2D),
GLM_LUA_REG(shearX3D),
GLM_LUA_REG(shearY2D),
GLM_LUA_REG(shearY3D),
GLM_LUA_REG(shearZ3D),
#endif

#if defined(GTX_MATRIX_TRANSFORM_2D_HPP)
GLM_LUA_REG(shearX),
GLM_LUA_REG(shearY),
#endif

#if defined(GTX_PCA_HPP)
GLM_LUA_REG(findEigenvaluesSymReal),
GLM_LUA_REG(computeCovarianceMatrix),
#endif
