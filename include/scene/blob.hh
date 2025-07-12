#pragma once

#include "object/cube.hh"
#include "geometry/point.hh"
#include "object/triangle.hh"

class Blob {
public:
    Blob(const Cube& zone, double discrete, double potential);

    const Cube& getZone() const;
    double getDiscrete() const;
    double getPotential() const;
    const std::map<Point3, double>& getPotentialMap() const;

    void addPotential(const Point3& point, double value);
    void removePotential(const Point3& point, double value);
    double getPotentialAt(const Point3& point) const;
    void clearPotential();

    std::list<Triangle> getTriangles() const;
    Point3 getPointFromEdge(Cube marching, int v);

private:
    Cube zone;
    double discrete;
    double potential;

    std::map<Point3, double> potentialMap;
    int allTriangles[256][15];
};
