#version 330 core

/**
Strange fragment shader that colors fragments by the gl_FragCoord and some of the
GLSL buit-in functions.  The example also shows the use of functions inside a
glsl shader and using a uniform variable to control animation inside the shader.

[in] pos --- vec4 color from vertex array.
[in] color --- vec4 position from vertex array.

[out] col --- vec4 output color to the fragment shader.


*/

in vec4 pos;
in vec4 color;

out vec4 col;

uniform int shadernum = 0;
uniform float time = 0;

// creates circles, one inside another
vec4 setCircles(vec4 p) {
    vec2 pt2 = vec2(p);
    float d = cos(50*length(pt2));
    float d2 = sin(50*length(pt2));
    vec4 col = vec4(1, 0, 0, 1); // sets color of the circles
    vec4 col2 = vec4(0, 1, 0, 1);
    return (d * col) + (d2 * col2);
}

// creates circles, one inside another - different colors
vec4 setCircles2(vec4 p) {
    vec2 pt2 = vec2(p);
    float d = cos(45*length(pt2));
    float d2 = sin(45*length(pt2));
    float d3 = tan(45*length(pt2));
    vec4 col = vec4(1, 0, 0, 1); // sets color of the circles
    vec4 col2 = vec4(0, 1, 0, 1);
    vec4 col3 = vec4(0, 0, 1, 1);
    return (d * col) + (d2 * col2) + (d3 * col3);
}

// creates grid
vec4 setGrid(vec4 p) {
    vec2 pt2 = vec2(p);
    float d1 = 0.5*(cos(90 * pt2.x)+1);
    float d2 = 0.5*(sin(90 * pt2.y)+1);
    vec4 col = d1*vec4(1, 0, 0, 1) + d2*vec4(0, 0, 1, 1);
    return col;
}

// checkerboard
vec4 setChecker(vec4 p) {
    float floorX = floor(p.x);
    float floorY = floor(p.y);
    vec4 col = vec4(0, 0, 0, 1);

    if (mod(floorX + floorY, 2) == 0)
        col = vec4(1, 0, 0, 1);

    return col;
}

// animation of circles
vec4 setCircleAnimation(vec4 p) {
    vec2 pt2 = vec2(p);
    float circles = cos(10*length(pt2) - time * 3); // 3 -> speed scalar
    vec4 col = vec4(0, 0, circles, 1);
    return col;
}

// checkerboard fade: red -> black & black -> green
vec4 setCheckerFade(vec4 p) {
    float floorX = floor(p.x);
    float floorY = floor(p.y);
    vec4 col = vec4(0, sin(time), 0, 1);

    if (mod(floorX + floorY, 2) == 0) {
        col = vec4(cos(time), 0, 0, 1);
    }

    return abs(col);
}

// animation of circles with lines
vec4 setCircleAnimation2(vec4 p) {
    vec2 pt2 = vec2(p);
    float blueCircles = cos(10*length(pt2) - time * 3); // 3 -> speed scalar
    float redCircles = cos(10*length(pt2) + time *3);
    vec4 col = vec4(redCircles, 0, blueCircles, 1);

    return col;
}

// moving green lines
vec4 setLines(vec4 p) {
    vec2 pt2 = vec2(p);
    float d1 = 0.5*(cos(30 * pt2.x)+1);
    vec4 col = d1*vec4(0, 1, 0, 1);

    return col;
}

// another circle animation - this time with 3
vec4 setCircleAnimation3(vec4 p) {
    vec2 pt2 = vec2(p);
    float blueCircles = cos(10*length(pt2) - time * 3); // 3 -> speed scalar
    float redCircles = cos(10*length(pt2) + time * 3);
    float greenCircles = cos(10*length(pt2) + time * 6); // twice as fast as red
    vec4 col = vec4(redCircles, greenCircles, blueCircles, 1);

    return col;
}


// --- MAIN ---
void main() {
    if (shadernum == 0)
        col = color;
    else if (shadernum == 1)
        col = setCircles(pos); // Number 1 Selected -> red, green & black circles
    else if (shadernum == 2)
        col = setCircles2(pos); // Number 2 Selected -> pink, green, blue
    else if (shadernum == 3)
        col = setGrid(pos); // Number 3 Selected -> red and blue grid
    else if (shadernum == 4)
        col = setChecker(pos * 5); // Number 4 Selected -> red/black checkerboard (5 * pos for more checkers)
    else if (shadernum == 5)
        col = setCircleAnimation(pos); // Number 5 -> circle animation
    else if (shadernum == 6)
        col = setCheckerFade(pos * 5); // Number 6 -> checkerboard fade
    else if (shadernum == 7) {
        // Number 7 -> circle & checkerboard combo animation
        col = setCircleAnimation(pos) + setCheckerFade(pos * 5);
    } else if (shadernum == 8) {
        // Number 8 -> blue & red moving circles w/ green lines moving
        col = setCircleAnimation2(pos) + setLines(pos + vec4(time, 0, 0, 0));
    } else if (shadernum == 9) {
        // Number 9 -> blue & red & green moving circles
        col = setCircleAnimation3(pos);
    }
}
