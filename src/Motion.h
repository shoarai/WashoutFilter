// Copyright (c) 2017 shoarai

class Motion
{
public:
  Motion(const double &accelerationX,
         const double &accelerationY,
         const double &accelerationZ,
         const double &angularVelocityX,
         const double &angularVelocityY,
         const double &angularVelocityZ)
      : aX(accelerationX), aY(accelerationY), aZ(accelerationZ),
        vPhi(angularVelocityX), vTheta(angularVelocityY), vPsi(angularVelocityZ) {}
  ~Motion(){};

  const double getAccelerationX() const { return aX; };
  const double getAccelerationY() const { return aY; };
  const double getAccelerationZ() const { return aZ; };
  const double getAngularVelocityX() const { return vPhi; };
  const double getAngularVelocityY() const { return vTheta; };
  const double getAngularVelocityZ() const { return vPsi; };

private:
  double aX, aY, aZ, vPhi, vTheta, vPsi;
};
