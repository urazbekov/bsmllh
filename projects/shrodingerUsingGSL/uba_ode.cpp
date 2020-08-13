#include <gsl/gsl_complex.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include "uba_ode.h"

double potentialCoul(double R)
{
    double eSquared = 1.43997;
    double Rc       = 1.3;
    if (R > Rc)
    {
        return eSquared * 2. * 6. / R;
    }
    else
    {
        return eSquared * 2 * 6 * 0.5 / Rc * (3.0 - R * R / Rc / Rc);
    }
}

double Vi(double R)
{
    double mMfd = 0.143535;
    return mMfd * 20.0 / (1.0 + exp((R - 1.2) / 0.6));
}

double function(double R)
{
    double kSquared = 1.83007125;
    double mMfd     = 0.143535;
    return kSquared + mMfd * 40.0 / (1.0 + exp((R - 1.25) / 0.6)) - mMfd * potentialCoul(R);
}

struct parameters
{
    double x0;
    double y0;
};

int func_x(double t, const double x[], double f[], void *params)
{
    struct parameters *p   = (struct parameters *)params;
    double             iy0 = p->y0;
    f[0]                   = x[1];
    f[1]                   = -function(t) * x[0] - Vi(t) * iy0;
    return GSL_SUCCESS;
}

int func_y(double t, const double y[], double f[], void *params)
{
    struct parameters *p   = (struct parameters *)params;
    double             ix0 = p->x0;
    f[0]                   = y[1];
    f[1]                   = -function(t) * y[0] + Vi(t) * ix0;
    return GSL_SUCCESS;
}

void solveShrodingerDifferentialEquation()
{
    int                i;
    struct parameters  parametersODE;
    double             t_x      = 1e-6;
    double             t_y      = 1e-6;
    double             t1       = 25.0;
    double             x[2]     = {0.0, 0.4};
    double             y[2]     = {0.0, 0.4};
    gsl_odeiv2_system  system_x = {func_x, NULL, 2, &parametersODE};
    gsl_odeiv2_system  system_y = {func_y, NULL, 2, &parametersODE};
    gsl_odeiv2_driver *driver_x = gsl_odeiv2_driver_alloc_y_new(&system_x, gsl_odeiv2_step_rk8pd, 1e-3, 1e-8, 1e-8);
    gsl_odeiv2_driver *driver_y = gsl_odeiv2_driver_alloc_y_new(&system_y, gsl_odeiv2_step_rk8pd, 1e-3, 1e-8, 1e-8);
    FILE *             pFile;
    pFile = fopen("wfData.txt", "w");
    for (i = 1; i <= 2500; i++)
    {
        double ti      = i / 2500.0 * t1;
        int    statusx = gsl_odeiv2_driver_apply(driver_x, &t_x, ti, x);
        int    statusy = gsl_odeiv2_driver_apply(driver_y, &t_y, ti, y);

        //      status                =
        //      gsl_odeiv2_driver_apply_fixed_step(driver_x, &t_x, 1e-3, 250, x);
        //      status                =
        //      gsl_odeiv2_driver_apply_fixed_step(driver_y, &t_y, 1e-3, 250, y);
        parametersODE.x0 = x[0];
        parametersODE.y0 = y[0];

        if (statusx && statusy != GSL_SUCCESS)
        {
            printf("error: driver returned %d\n", statusx);
            break;
        }

        //    printf("%.5e\t%.5e\t%.5e\n", t_x, y[0], x[0]);
        fprintf(pFile, "%.5e\t%.5e\t%.5e\n", t_x, y[0], x[0]);
    }
    fclose(pFile);
    gsl_odeiv2_driver_free(driver_x);
    gsl_odeiv2_driver_free(driver_y);
}
