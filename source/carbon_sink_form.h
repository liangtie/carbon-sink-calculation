#ifndef CARBON_SINK_FORM_H
#define CARBON_SINK_FORM_H

struct CarbonSinkForm
{
    int year;
    double area;
    double polygon;
    int floorCount;
    double height;
    int buildingCount;

    [[nodiscard]] double getCarbonSink() const;
};

#endif