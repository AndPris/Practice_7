#include <stdio.h>
#include <math.h>

void noCharShort(short *var) { //checking for characters
    char cond, ch;
    do {
        cond = 0;
        scanf("%hd%c", var, &ch);

        if(ch != '\n') {
            printf("Invalid data\n");
            cond = 1;
            fflush(stdin);
        }
    } while(cond);

}

short choice(short *var) {
    char cond;
    do {
        cond = 0;
        noCharShort(var);

        if(*var != 1 && *var != 2) {
            printf("You have to enter 1 or 2\n");
            fflush(stdin);
            cond = 1;
        }
    } while(cond);
}

void noCharFloat(float *var) { //checking for characters
    char cond, ch;
    do {
        cond = 0;
        scanf("%f%c", var, &ch);

        if(ch != '\n') {
            printf("Invalid data\n");
            cond = 1;
            fflush(stdin);
        }
    } while(cond);

}

void borders(float *low, float *top) {
    char cond;
    do {
        cond = 0;
        printf("Low border:\n");
        noCharFloat(low);
        printf("Top border:\n");
        noCharFloat(top);

        if(*low >= *top) {
            printf("Low border is higher then top one or equals to it\n");
            fflush(stdin);
            cond = 1;
        }
    } while(cond);
}

float equation1 (float x, float t) {
    return (cos(t/x) - 2*sin(1.0/x) + 1.0/x);
}

float equation2 (float x, float t) {
    return sin(log(x)) - cos(log(x)) + t*log(x);
}

float root1(float (*func) (float, float), float low, float top, float t, float e) {
    float x, fLow, fx;

    do {
        x = (low + top) / 2;
        fLow = (*func)(low, t);
        fx = (*func)(x, t);
        if( isnan(fLow) || isnan(fx)) {
            printf("Value doesn't belong to the domain of function");
            return 0;
        }
        if ( fLow * fx > 0) {
            low = x;
        } else {
            top = x;
        }
    } while(fabs(top - low) > e);

    if(fabs((*func)(x, t)) > 1) {
        printf("There is no roots in this range");
        return 0;
    }
    return x;
}

float root2(float (*func) (float, float), float top, float t, float e) {
    float b, delta, x = top, der;

    do {
        b = (*func)(x, t);
        der = ( (*func)(x + pow(10, -6), t) - b) / pow(10, -6); // derivative
        if(isnan(b) || isnan(der)) {
            printf("Value doesn't belong to the domain of function");
            return 0;
        }
        delta = b/der;
        x -= delta;
    } while(fabs(delta) > e);

    if(fabs((*func)(x, t)) > 1) {
        printf("There is no roots in this range");
        return 0;
    }
    return x;
}

int main() {
    float a, b, t, accuracy, res;
    short e, equ, method;

    printf("Enter 1 to calculate first equation or 2 to calculate the second one:\n");
    choice(&equ);
    printf("Enter 1 to use half division method or 2 to use Newton's method:\n");
    choice(&method);
    borders(&a, &b);
    printf("Parameter t:\n");
    noCharFloat(&t);
    printf("Enter accuracy:\n");
    noCharShort(&e);
    accuracy = 1.0 / pow(10, e);

    if(method == 1) {
        if(equ == 1) {
            res = root1(equation1, a, b, t, accuracy);
        } else {
            res = root1(equation2, a, b, t, accuracy);
        }
    } else {
        if(equ == 1) {
            res = root2(equation1, b, t, accuracy);
        } else {
            res = root2(equation2, b, t, accuracy);
        }
    }

    if(res != 0) {
        printf("x = %g", res);
    }
    return 0;
}
