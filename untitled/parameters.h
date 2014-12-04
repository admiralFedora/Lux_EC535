typedef struct parameters_bag
{
    double iso;
    double aperture;
    double shutter;
    double exposure;
}parameters;

extern parameters parameter;

void set_parameter(double iso, double aperture, double shutter, double exposure)
{
    parameter.iso = iso;
    parameter.aperture = aperture;
    parameter.shutter = shutter;
    parameter.exposure = exposure;
}
